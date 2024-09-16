// ---------------------------------------------------------------------------------
// Inclusões

#include "Ghost.h"
#include "OneBitAdventure.h"
#include "Character.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Ghost, inicializa tudo especifico do Ghost
Ghost::Ghost(float col, float line)
	: Enemy() // Chamada do construtor da classe base
{
	width = Level1::hud->tileWidth;
	height = Level1::hud->tileHeight;

	// Inicializa TileSet a animação do Ghost
	tileSet = new TileSet("Resources/GhostFolha.png", width * 3, height * 2,
		width, height, 3, 6);
	anim = new Animation(tileSet, 0.145f, true);
	damageTimer = new Timer();

	// Cria as sequências de animação
	uint Seq1[3] = { 0,1,2 };
	uint Seq2[3] = { 3,4,5 };
	anim->Add(WALK, Seq1, 3);
	anim->Add(ATACK, Seq2, 3);

	animSeq = WALK;
	anim->Select(animSeq);

	level = 1;								// Nível do Ghost
	maxLife = 5 + (10 * (level - 1));		// Vida máxima do Ghost por nível
	life = maxLife;							// Vida padrão do fastasma (Não tem na wiki informando o máximo nem quanto aumenta)
	attack = 3 + (2 * (level - 1));		// Dano de ataque de 1	(Não tem na wiki informando o máximo nem quanto aumenta)

	// Inicialize BBox após walking ser definido
	InitializeBBox();

	// Inicializa a posição
	MoveTo(Level1::hud->Col(col), Level1::hud->Line(line), Layer::MIDDLE);

	name = "Ghost";							// Nome do Ghost
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

		// Verifica se o ghost morreu após receber o dano
		if (life <= 0)
		{
			// Morreu
			// Deleta o objeto
			Level1::scene->Remove((Object*)this, MOVING);
			((Character*)player)->SetXp(20 * (level));	            // Adiciona a experiência ao player
		}

		isHit = false;
	}
	else if (type == ENEMY) {
		Move(BACK);
	}
}

// ---------------------------------------------------------------------------------
