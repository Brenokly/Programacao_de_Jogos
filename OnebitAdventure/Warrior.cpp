// ---------------------------------------------------------------------------------
// Inclusões

#include "Warrior.h"
#include "Level1.h"

// ---------------------------------------------------------------------------------

// Construtor da classe Warrior, inicializa tudo especifico do Warrior
Warrior::Warrior(int col, int line)
	: Character() // Chamada do construtor da classe base
{
	// Cria o TileSet do Warrior
	tileSet = new TileSet("Resources/WarriorSprite2.png", width * 4, height * 2, 
		width, height, 4, 8);

	// Cria a animação do Warrior
	anim = new Animation(tileSet, 0.125f, true);
	damageTimer = new Timer();

    uint Left[4]  = { 0, 1, 2, 3 };
    uint Right[4] = { 4, 5, 6, 7 };

	// Adiciona as combinações de estado de animação e direção em que a sequência de animações muda
	anim->Add(WALK | RIGHT, Right, 4);
    anim->Add(WALK | LEFT, Left, 4);

	animState = WALK;
	direction = LEFT;

	maxLife = 52 + (10 * (level - 1));	// Vida máxima do Warrior por nível
	life = maxLife;						// Vida padrão do Warrior
	attack = 2;							// Dano de ataque de 2
	criticalChance = 2.0f;				// Chance de crítico de 2%

    // Inicialize BBox após walking ser definido
    InitializeBBox();

	// Inicializa a posição
	MoveTo(Hud::Col(col), Hud::Line(line), Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Warrior::~Warrior()
{
	delete damageTimer;
	delete anim;
	delete tileSet;
}

// ---------------------------------------------------------------------------------

void Warrior::UpdateAnimation()
{
	anim->Select(animState | direction);	// Seleciona a sequência de animação
	anim->NextFrame();                      // Atualiza a animação
}

// ---------------------------------------------------------------------------------

void Warrior::OnCollision(Object* obj)
{
	if (isDead) return;

	uint type = obj->Type();

	// Se o objeto colidido for um inimigo
	if (type == ENEMY)
	{
		if (!isHit) {
			return;						// Se o Warrior já foi atingido, não faz nada
		}

		Enemy* enemy = (Enemy*)obj;		// Converte o objeto para Enemy

		enemyTreatment(enemy);			// Trata a colisão com o inimigo
	}
	else if (type == BOSS) {

		if (!isHit) {
			return;						// Se o Warrior já foi atingido, não faz nada
		}

		Boss* boss = (Boss*)obj;		// Converte o objeto para Boss

		bossTreatment(boss);			// Trata a colisão com o boss
	}
	else if (type == COIN)
	{
		Level1::scene->Delete(obj, STATIC);
		OneBitAdventure::audio->Play(MOEDA);
		coins++;
	}
	else if (type != DOOR && type != BOSSATACK)
	{
		// Se o objeto colidido for diferente de uma porta, o Warrior volta para a posição anterior
		Move(BACK);
	}
	else if (type == BOX)
	{
		// Implementar interação com a caixa: sprite de vida e itens dropados
		Move(BACK);
	}
}

// ---------------------------------------------------------------------------------

void Warrior::bossTreatment(Boss*& boss)
{
	txtTimer->Start();				// Inicia o timer para o cálculo de tempo de exibição da mensagem!

	// Reinicia o timer de ataque
	attackTimer->Reset();			// Inicia o timer para o cálculo de tempo de pausa entre os ataques!

	// Pega a direção em que o inimigo está se movendo
	Direction enemyDirection = boss->GetDirection();

	// Verifica se o Warrior e o inimigo estão se colidindo em direções opostas
	bool verticalCollision = (direction == UP && enemyDirection == DOWN)
		|| (direction == DOWN && enemyDirection == UP);

	bool horizontalCollision = (direction == LEFT && enemyDirection == RIGHT)
		|| (direction == RIGHT && enemyDirection == LEFT);

	// Calcula a distância entre os destinos do Warrior e o inimigo
	int prevDist = PrevDistance(boss);

	// Player realiza o ataque se tiverem direções opostas ou o ghost estiver parado
	if (verticalCollision || horizontalCollision || enemyDirection == STILL)
	{
		// Se estiverem a menos de 1 tile de distância, o Warrior ataca
		if (prevDist <= 2.2f * height)
		{
			// Gera um número aleatório entre 0 e 100
			int randomValue = rand() % 100;

			float dano = attack; // Dano normal

			// Se o valor gerado for menor que a chance crítica, aplica o crítico
			if (randomValue < criticalChance)
			{
				dano *= 2; // Dano crítico, multiplicado por 2
			}

			// Aplica o dano ao inimigo
			boss->SetDamage(dano);

			// seta a mensagem de dano no unordered_map
			// Dano que o personagem causou
			text.insert({ std::to_string(boss->GetDamage()), Color(1.0f,1.0f,1.0f,1.0f) });

			// Inicia a contagem de tempo de exibição de dano
			damageTimer->Reset();

			Move(BACK); // Volta para a posição anterior
		}
	}

	// Inicia a contagem de tempo de exibição de dano
	damageTimer->Reset();

	// Evita que o Warrior continue a ser atingido até que a próxima colisão seja registrada
	isHit = false;
	OneBitAdventure::audio->Play(ATAQUE);
}

// ---------------------------------------------------------------------------------

void Warrior::enemyTreatment(Enemy*& enemy)
{
	txtTimer->Start();				// Inicia o timer para o cálculo de tempo de exibição da mensagem!

	// Reinicia o timer de ataque
	attackTimer->Reset();			// Inicia o timer para o cálculo de tempo de pausa entre os ataques!

	// Pega a direção em que o inimigo está se movendo
	Direction enemyDirection = enemy->GetDirection();

	// Verifica se o Warrior e o inimigo estão se colidindo em direções opostas
	bool verticalCollision = (direction == UP && enemyDirection == DOWN)
		|| (direction == DOWN && enemyDirection == UP);

	bool horizontalCollision = (direction == LEFT && enemyDirection == RIGHT)
		|| (direction == RIGHT && enemyDirection == LEFT);

	// Calcula a distância entre os destinos do Warrior e o inimigo
	int prevDist = PrevDistance(enemy);

	// Player realiza o ataque se tiverem direções opostas ou o ghost estiver parado
	if (verticalCollision || horizontalCollision || enemyDirection == STILL)
	{
		// Se estiverem a menos de 1 tile de distância, o Warrior ataca
		if (prevDist < 1.5f * height)
		{
			// Gera um número aleatório entre 0 e 100
			int randomValue = rand() % 100;

			float dano = attack; // Dano normal

			// Se o valor gerado for menor que a chance crítica, aplica o crítico
			if (randomValue < criticalChance)
			{
				dano *= 2; // Dano crítico, multiplicado por 2
			}

			// Aplica o dano ao inimigo
			enemy->SetDamage(dano);

			// seta a mensagem de dano no unordered_map
			// Dano que o personagem causou
			text.insert({ std::to_string(enemy->GetDamage()), Color(1.0f,1.0f,1.0f,1.0f) });

			// Inicia a contagem de tempo de exibição de dano
			damageTimer->Reset();

			Move(BACK); // Volta para a posição anterior
		}
	}

	// Inicia a contagem de tempo de exibição de dano
	damageTimer->Reset();

	// Evita que o Warrior continue a ser atingido até que a próxima colisão seja registrada
	isHit = false;

	OneBitAdventure::audio->Play(ATAQUE);
}

// ---------------------------------------------------------------------------------