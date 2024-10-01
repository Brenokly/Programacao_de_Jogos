// Hydra.cpp
// ------------------------------------------------------------------------------

// Inclusões de Arquivos

#include "Hydra.h"
#include "Level1.h"
#include <cstdlib>
#include <ctime>
#include <random>

// ------------------------------------------------------------------------------

std::random_device rt;                              // Inicializa o gerador de números aleatórios
std::mt19937 rnt(rt());                             // Inicializa o Mersenne Twister com uma semente aleatória
std::uniform_int_distribution<int> dist(1, 100);    // Distribuição de 1.0 a 100.0

//-------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Hydra::InitializeBBox()
{
    // Inicializa a BBox
    BBox(new Rect(
        x - tileSet->TileWidth() / 2.3,
        y - tileSet->TileHeight() / 2.1,
        x + tileSet->TileWidth() / 2.3,
        y + tileSet->TileHeight() / 2.1));
}

// ------------------------------------------------------------------------------

Hydra::Hydra(float col, float line) : Boss() // Chamada do construtor da classe base
{
    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de dimensão e tile set

    width = Level1::player->GetWidth();
    height = Level1::player->GetHeight();

	// Inicializa TileSet com a animação do Hydra
    tileSet = new TileSet("Resources/bosses/Hydra/HydraSprite.png", (width * 3) * 5, height * 3, width * 3, height * 3, 5, 5);
	anim = new Animation(tileSet, 0.1f, true);

    // --------------------------------------------------------------------------------------------
    // Inicializa o temporizador de dano e as sequências de animação

    // Animação do boss
    uint Seq1[5] = { 0, 1, 2, 3, 4 };           // Sequência de caminhada
    uint Seq2[5] = { 5, 6, 7, 8, 9 };           // Sequência de ataque

    anim->Add(WALK, Seq1, 5);
    anim->Add(ATACK, Seq2, 5);
    animSeq = WALK;                             // Define sequência inicial como caminhada
    animState = WALK;
    anim->Select(animSeq);

	damageTimer = new Timer();				    // Inicializa o temporizador de dano
	moveTimer = new Timer();                    // Inicializa o temporizador de movimento
	moveTimer->Start();						    // Inicia o temporizador de movimento

    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de status do boss Hydra (nível, vida e ataque)

    level = 1;                                  // Ajuste o nível conforme necessário

    maxLife = (int)(120 * pow(level, 1.697));   // Vida máxima da Hydra
    life = 10;                                  // Vida atual da Hydra

    attack = (int)(2.72 * pow(level, 1.644));   // Dano da Hydra cresce exponencialmente

    // --------------------------------------------------------------------------------------------
    // Inicializa bounding box e posição do Hydra

    InitializeBBox();
    MoveTo(Level1::hud->Col(col), Level1::hud->Line(line), Layer::MIDDLE);

	//---------------------------------------------------------------------------------------------
	// Inicializa as variáveis auxiliares

	proximityThreshold = 4.0f * width;          // Define a distância de proximidade
	state = IDLE;                               // Define o estado inicial do Hydra como IDLE
	isMoving = false;   			            // Define que o Hydra não está se movendo
	isAttacked = false;                         // Define que o Hydra não está atacando

	// Limpa a memória dos sprites de vida e hud para evitar vazamento de memória
    if (hudLife) {
		delete hudLife;
    }

    if (lifeSprite) {
		delete lifeSprite;
    }

    lifeSprite = new Sprite("Resources/sangue.png", 415.0f, 6.0f);
    hudLife = new Sprite("Resources/vida.png", 455.0f, 17.0f);

	tileHeight = tileSet->TileHeight();
	tileWidth = tileSet->TileWidth();

    // --------------------------------------------------------------------------------------------
    // Inicializa o nome do Hydra

    name = "Hydra";  // Nome do Hydra
}

// ------------------------------------------------------------------------------

Hydra::~Hydra()
{
	delete damageTimer;
	delete anim;
	delete tileSet;
}

// ------------------------------------------------------------------------------

void Hydra::Update()
{
    float distance = PrevDistance(Level1::player);

    if (y > 0) {
        if (moveTimer->Elapsed(0.3f) && Level1::player->IsMoving()) {
            if (rand() % 100 < 90 && contadorMovimento == 0 && !isAttacked) {
                HandleMovement(100.0f);
            }
            else if (rand() % 100 < 70 && contadorMovimento == 0 && !isAttacked) {
                Ataque2();
            }
            else if (rand() % 100 <= 60 && contadorMovimento == 0 && !isAttacked) {
                if (distance < (2.4f * height) && Level1::player->X() >= x - width && Level1::player->X() <= x + width) {
                    contadorMovimento = 4;
                    Ataque1();
                }
            }
            else if (contadorMovimento > 0) {
                contadorMovimento--;

                if (contadorMovimento == 0) {
                    isAttacked = false;
                    isMoving = false;
                }
            }

            moveTimer->Reset();
        }
    }

    CameraMovement();									    // Atualiza a movimentação da câmera
    Movement();											    // Atualiza a movimentação do inimigo

    ConstrainToScreen();                                    // Garante que o inimigo não ultrapasse os limites da tela

    // Se o inimigo está a um bloco de distância do jogador, é exibido a vida do inimigo
    if (distance < (12.0f * height))
    {
        DisplayEnemyHealth();
    }

    // Verifica se o Boss morreu após receber o dano
    if (life <= 0) {

        Level1::scene->Delete(this, MOVING);                // Remove o boss da cena
        Level1::player->SetXp(100 * level);	                // Adiciona a experiência ao player
    }

    UpdateAnimation();                                      // Atualiza a animação do inimigo
}

void Hydra::Draw()
{
    // Desenha o sprite do inimigo na cor vermelha por um tempo se tiver recebido dano
    if (damageTimer->Elapsed(0.25f)) {
        anim->Draw(x, y);
    }
    else {
        anim->Draw(x, y, Layer::FRONT, Color(1.0f, 0.0f, 0.0f, 1.0f));
    }
}

// ------------------------------------------------------------------------------

void Hydra::OnCollision(Object* obj)
{
    if (isAttacked) return;

	uint type = obj->Type();						                // Tipo do objeto colidido

    // Se o objeto colidido for o player
    if (type == PLAYER)
    {
        if (!isHit) return;

        Entity* player = (Entity*)(obj);

        float targetDist = TargetDistance(player);	                // Diferença entre os targets

        // Se o inimigo e o player tiverem o mesmo destino (targetX e targetY)
        if (targetDist < 5.0f || direction != STILL)
        {
            player->SetDamage(attack);		                        // Ataca o player

            // Dano que o inimigo causou
            ((Character*)player)->text.insert({ std::to_string(player->GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f) });

            Move(BACK);								                // Volta o boss para trás
        }

        // Verifica se o boss morreu após receber o dano
        if (life <= 0)
        {
            // Morreu
            // Deleta o objeto
            OneBitAdventure::audio->Play(MORTE);					// Toca o som de morte do inimigo
            Level1::scene->Delete((Object*)this, MOVING);
            ((Character*)player)->SetXp(200 * (level));	            // Adiciona a experiência ao player
        }

        isHit = false;
    }
    else if (type != ENEMY)
    {
        Level1::scene->Delete(obj, STATIC);
    }
}

//-------------------------------------------------------------------------------
// Ataque varredura, ataque de área na frente do boss que atinge o player em uma linha reta

void Hydra::Ataque1() {
	// Bloqueia o movimento do boss até o final do ataque
    isAttacked = true;

	// Cria um novo ataque de varredura
    varredura = new Varredura(this);

	// Adiciona o ataque à cena
    Level1::scene->Add(varredura, MOVING);
}

// ------------------------------------------------------------------------------
// Move para frente em direção ao player

void Hydra::Ataque2()
{
	// Bloqueia o movimento do boss até o final do ataque
    isAttacked = true;

	// Cria um novo ataque de salto
	salto = new Salto(this);

	// Adiciona o ataque à cena
    Level1::scene->Add(salto, MOVING);
}

// ------------------------------------------------------------------------------

void Hydra::Ataque3()
{
    // Não tem, ainda
}

// ------------------------------------------------------------------------------

void Hydra::DrawHealthBar()
{
    float barWidth = 415.0f;
    float barHeight = 6.0f;
    float percent = (float)life / maxLife;
    float currentWidth = barWidth * percent;
    float offset = (window->Width() * 0.50f) - (barWidth - currentWidth) / 2;

    hudLife->Draw(window->Width() * 0.50f, window->Height() * 0.07f, Layer::MIDDLE);
    lifeSprite->DrawResize(offset, window->Height() * 0.07f, currentWidth, barHeight, Layer::FRONT);
}

// ------------------------------------------------------------------------------

void Hydra::DrawHealthText()
{
    std::string vidaTexto = std::to_string(life) + "/" + std::to_string(maxLife);

    // Pego o tamanho do espaço ocupado pelo texto do level e ajusto a posição do nome
    text.str("");
    text << vidaTexto;
    int length = int(text.tellp());

    press12->Draw((window->Width() * 0.61f) - (11.0f * length), window->Height() * 0.09f, vidaTexto, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 0.8f);
}

// ------------------------------------------------------------------------------

void Hydra::DrawLevel()
{
    press12->Draw(window->Width() * 0.39f, window->Height() * 0.05f, "Lv:" + std::to_string(level), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f);
}

// ------------------------------------------------------------------------------

void Hydra::DrawName()
{
	// Pego o tamanho do espaço ocupado pelo texto do level e ajusto a posição do nome
    text.str("");
    text << level;
    int length = int(text.tellp());

    press12->Draw(window->Width() * 0.429f + (9.0f * length), window->Height() * 0.05f, name, Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f);
}

// ------------------------------------------------------------------------------