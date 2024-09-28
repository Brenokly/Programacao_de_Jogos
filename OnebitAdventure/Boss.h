// Boss.h

#ifndef BOSS_H
#define BOSS_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Enemy.h"                      // Interface base para inimigos

// ------------------------------------------------------------------------------

class Boss : public Enemy
{
protected:
	int contadorMovimento;												// Essa variável serve para contar quantos movimentos o player deu!
	virtual void InitializeBBox() override;								// Inicializa a caixa de colisão (BBox)

public:
	Boss();
	virtual ~Boss() = 0;

	void ConstrainToScreen() override;
	void UpdateAnimation() override;					// atualização da animação do Boss
};

// ------------------------------------------------------------------------------

#endif		// BOSS_H
