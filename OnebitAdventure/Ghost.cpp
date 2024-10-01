// ---------------------------------------------------------------------------------
// Inclusões

#include "Ghost.h"
#include "OneBitAdventure.h"
#include "Character.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Ghost
Ghost::Ghost(float col, float line) : Enemy() // Chamada do construtor da classe base
{
    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de dimensão e tile set

    width = Level1::hud->tileWidth;
    height = Level1::hud->tileHeight;

    // Inicializa TileSet com a animação do Ghost
    tileSet = new TileSet("Resources/GhostFolha.png", width * 3, height * 2, width, height, 3, 6);
    anim = new Animation(tileSet, 0.145f, true);

    // --------------------------------------------------------------------------------------------
    // Inicializa o temporizador de dano e as sequências de animação

    damageTimer = new Timer();

    uint Seq1[3] = { 0, 1, 2 };  // Sequência de caminhada
    uint Seq2[3] = { 3, 4, 5 };  // Sequência de ataque

    anim->Add(WALK, Seq1, 3);
    anim->Add(ATACK, Seq2, 3);
    animSeq = WALK;  // Define sequência inicial como caminhada
    anim->Select(animSeq);

    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de status do Ghost (nível, vida e ataque)

    level = Level1::player->Progress() / 50.0f; // Nível do Ghost
    if (level == 0) level = 1;
    maxLife = 5 + (10 * (level - 1));      // Vida máxima do Ghost por nível
    life = maxLife;                        // Vida atual do Ghost
    attack = 3 + (2 * (level - 1));        // Dano de ataque do Ghost

    // --------------------------------------------------------------------------------------------
    // Inicializa bounding box e posição do Ghost

    InitializeBBox();
    MoveTo(Level1::hud->Col(col), Level1::hud->Line(line), Layer::MIDDLE);

    // --------------------------------------------------------------------------------------------
    // Inicializa o nome do Ghost

    name = "Ghost";  // Nome do Ghost
}

// ---------------------------------------------------------------------------------

Ghost::~Ghost()
{
	delete damageTimer;
	delete anim;
	delete tileSet;
}

// ---------------------------------------------------------------------------------

void Ghost::UpdateAnimation()
{
	anim->Select(animState);
	anim->NextFrame();
}

// ---------------------------------------------------------------------------------

void Ghost::OnCollision(Object* obj)
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
			((Character*)player)->text.insert({std::to_string(player->GetDamage()), Color(1.0f, 0.0f, 0.0f, 1.0f)});

			Move(BACK);								// Volta o ghost para trás
		}

		isHit = false;

        // Verifica se o ghost morreu após receber o dano
        if (life <= 0) {
            OneBitAdventure::audio->Play(MORTE);				// Toca o som de morte do inimigo
            Level1::scene->Delete(this, MOVING);
            Level1::player->SetXp(40 * level);	                // Adiciona a experiência ao player
        }
	}
	else if (type == ENEMY || type == BOSS) {
		Move(BACK);
	}
	else if (type == BOSSATACK) {
		Move(BACK);
	}
}

// ---------------------------------------------------------------------------------