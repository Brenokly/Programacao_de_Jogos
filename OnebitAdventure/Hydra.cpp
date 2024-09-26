// Hydra.cpp

#ifndef HYDRA_H
#define HYDRA_H

// ------------------------------------------------------------------------------

// Inclusões de Arquivos

#include "Hydra.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Hydra::InitializeBBox()
{
    // Inicializa a BBox
    BBox(new Rect(
        x - tileSet->TileWidth() / 2,
        y - tileSet->TileHeight() / 2,
        x + tileSet->TileWidth() / 2,
        y + tileSet->TileHeight() / 2)
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

    // Ataque1 que precisa ser instanciado na frente do boss junto com os alertas
    ataque1 = new TileSet("Resources/bosses/ataque.png", 960.0f, 120.0f, 240.0f, 120.0f, 4, 4);
    animAtaque1 = new Animation(ataque1, 0.145f, true);

	// Inicializa TileSet com a animação do Hydra
    tileSet = new TileSet("Resources/bosses/Hydra/HydraSprite.png", 960.0f, 192.0f, 192.0f, 192.0f, 5, 5);
	anim = new Animation(tileSet, 0.1f, true);

    // --------------------------------------------------------------------------------------------
    // Inicializa o temporizador de dano e as sequências de animação

    //Animação do ataque
	uint SeqAtaque1[4] = { 0, 1, 3 }; 		    // Sequência de ataque, não está errado, e 0,1,3 mesmo.
	animAtaque1->Add(ATAQUE1, SeqAtaque1, 4);
	animAtaque1->Select(ATAQUE1);

    // Animação do boss
    uint Seq1[5] = { 0, 1, 2, 3, 4 };           // Sequência de caminhada
    uint Seq2[5] = { 5, 6, 7, 8, 9 };           // Sequência de ataque

    anim->Add(WALK, Seq1, 5);
    anim->Add(ATACK, Seq2, 5);
    animSeq = WALK;                             // Define sequência inicial como caminhada
    animState = WALK;
    anim->Select(animSeq);

    damageTimer = new Timer();

    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de status do boss Hydra (nível, vida e ataque)

    level = 1;  // Ajuste o nível conforme necessário
    maxLife = (int)(120 * pow(level, 1.697));   // Vida máxima da Hydra
    life = maxLife;  // Vida atual da Hydra
    attack = (int)(2.72 * pow(level, 1.644));   // Dano da Hydra cresce exponencialmente

    // --------------------------------------------------------------------------------------------
    // Inicializa bounding box e posição do Hydra

    InitializeBBox();
    MoveTo(Level1::hud->Col(col), Level1::hud->Line(line), Layer::MIDDLE);

	//---------------------------------------------------------------------------------------------
	// Inicializa as variáveis auxiliares

	proximityThreshold = 3.0f * width;          // Define a distância de proximidade

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
        Level1::player->SetXp(100 * level);	                // Adiciona a experiência ao player
    }

    UpdateAnimation();                                      // Atualiza a animação do inimigo
}

// ------------------------------------------------------------------------------

void Hydra::OnCollision(Object* obj)
{
    uint type = obj->Type();

    // Se o objeto colidido for o player
    if (type == PLAYER)
    {
        if (!isHit) return;

        Entity* player = (Entity*)(obj);

        float targetDist = TargetDistance(player);	// Diferença entre os targets

        // Se o ghost e o player tiverem o mesmo destino (targetX e targetY)
        if (targetDist < 4.0f || direction != STILL)
        {
            player->SetDamage(attack);		// Ataca o player

            // Dano que o inimigo causou
            ((Character*)player)->text.insert({ std::to_string(player->GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f) });

            Move(BACK);								// Volta o ghost para trás
        }

        isHit = false;
    }
    else if (type == ENEMY) {
        Move(BACK);
    }
}

// ------------------------------------------------------------------------------

void Hydra::UpdateAnimation()
{
    anim->Select(animState);
    anim->NextFrame();
}

// ------------------------------------------------------------------------------

// Varredura
void Hydra::Varredura()
{
	// Esse ataque é um ataque de varredura que atinge o jogador fazendo uma varredura de 180 graus
	// Ele só usa esse ataque se o jogador estiver abaixo da Hydra, ou seja, se o Y do jogador for maior que o Y da Hydra

	// Se o jogador estiver abaixo da Hydra e a distância entre eles for menor que 5 blocos
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

#endif // HYDRA_H

// ------------------------------------------------------------------------------