// ------------------------------------------------------------------------------
// Inclusões

#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"					// interface de Player
#include "Enemy.h"						// interface de Enemy
#include "Boss.h"						// interface de Boss

// ------------------------------------------------------------------------------

class Warrior : public Character
{
public:
	Warrior(int col, int line);
	~Warrior() override;

	void OnCollision(Object* obj) override;					// resolução de colisões
	void UpdateAnimation() override;						// atualização da animação do Warrior
	void bossTreatment(Boss *& boss);						// tratamento de colisão com o boss
	void enemyTreatment(Enemy *& enemy);					// tratamento de colisão com inimigos
};

// ---------------------------------------------------------------------------------

#endif // WARRIOR_H
