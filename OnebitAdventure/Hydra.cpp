// Hydra.cpp
// ------------------------------------------------------------------------------

// Inclusões de Arquivos

#include "Hydra.h"
#include "Varredura.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Hydra::InitializeBBox()
{
    // Inicializa a BBox
    BBox(new Rect(
        x - tileSet->TileWidth() / 2.3,
        y - tileSet->TileHeight() / 2.1,
        x + tileSet->TileWidth() / 2.3,
        y + tileSet->TileHeight() / 2.1)
    );
}

// ------------------------------------------------------------------------------

Hydra::Hydra(float col, float line) : Boss() // Chamada do construtor da classe base
{
    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de dimensão e tile set

    width = Level1::player->GetWidth();
    height = Level1::player->GetHeight();

	// Inicializa os TileSets usados pela Hydra

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

    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de status do boss Hydra (nível, vida e ataque)

    level = 1;                                  // Ajuste o nível conforme necessário

    maxLife = (int)(120 * pow(level, 1.697));   // Vida máxima da Hydra
    life = maxLife;                             // Vida atual da Hydra

    attack = (int)(2.72 * pow(level, 1.644));   // Dano da Hydra cresce exponencialmente

    // --------------------------------------------------------------------------------------------
    // Inicializa bounding box e posição do Hydra

    InitializeBBox();
    MoveTo(Level1::hud->Col(col), Level1::hud->Line(line), Layer::MIDDLE);

	//---------------------------------------------------------------------------------------------
	// Inicializa as variáveis auxiliares

	proximityThreshold = 3.0f * width;          // Define a distância de proximidade
	indexAtaque1 = 0;						    // Inicializa o índice do ataque

    // --------------------------------------------------------------------------------------------
    // Inicializa o nome do Hydra

    name = "Hydra";  // Nome do Hydra
}

// ------------------------------------------------------------------------------

Hydra::~Hydra()
{
    delete ataque1;
    delete animAtaque1;
	delete damageTimer;
	delete anim;
	delete tileSet;
}

// ------------------------------------------------------------------------------

void Hydra::Update()
{
    if (Level1::player->IsMoving())
    {
        HandleMovement(100.0f);                             // Define a direção de movimento com 100% de chance de seguir o jogador
    }

    CameraMovement();									    // Atualiza a movimentação da câmera
    Movement();											    // Atualiza a movimentação do inimigo

    ConstrainToScreen();                                    // Garante que o inimigo não ultrapasse os limites da tela

    // Se o inimigo está a um bloco de distância do jogador, é exibido a vida do inimigo
    if (Distance(Level1::player) <= height + 2.25f)
    {
        DisplayEnemyHealth();
    }

    // Verifica se o Boss morreu após receber o dano
    if (life <= 0) {

        Level1::scene->Remove(this, MOVING);                // Remove o boss da cena
        Level1::player->SetXp(100 * level);	              // Adiciona a experiência ao player
    }

    UpdateAnimation();                                        // Atualiza a animação do inimigo
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
	uint type = obj->Type();						// Tipo do objeto colidido

    // Se o objeto colidido for o player
    if (type == PLAYER)
    {
        if (!isHit) return;

        Entity* player = (Entity*)(obj);

        float targetDist = TargetDistance(player);	// Diferença entre os targets

        // Se o ~inimigo e o player tiverem o mesmo destino (targetX e targetY)
        if (targetDist < 4.0f || direction != STILL)
        {
            player->SetDamage(attack);		        // Ataca o player

            // Dano que o inimigo causou
            ((Character*)player)->text.insert({ std::to_string(player->GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f) });

            Move(BACK);								// Volta o boss para trás
        }

        isHit = false;
    }
    else if (type == ENEMY) {
        Move(BACK);
    }
}

//-------------------------------------------------------------------------------

void Hydra::Ataque1() {

    if (window->KeyPress(VK_SPACE)) {
        Level1::scene->Add(new Varredura(x, y, attack), MOVING);
    }
}

// ------------------------------------------------------------------------------

void Hydra::Ataque2()
{

}

// ------------------------------------------------------------------------------

void Hydra::Ataque3()
{

}

// ------------------------------------------------------------------------------

void Hydra::DrawHealthBar()
{
}

// ------------------------------------------------------------------------------

void Hydra::DrawHealthText()
{
}

// ------------------------------------------------------------------------------

void Hydra::DrawLevel()
{
}

// ------------------------------------------------------------------------------

void Hydra::DrawName()
{
}

// ------------------------------------------------------------------------------
