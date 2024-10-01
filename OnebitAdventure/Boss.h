// Boss.h

#pragma once
#ifndef BOSS_H
#define BOSS_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Enemy.h"         // Interface base para inimigos

// ------------------------------------------------------------------------------

enum BossState { MOVENDO, ATACANDO, PARADO};

// ------------------------------------------------------------------------------

class Boss : public Enemy
{
protected:
	// Atributos protegidos específicos do Boss
	bool isAttacked;									// Essa variável serve para indicar se o Boss está atacando ou não
	Timer* moveTimer;									// Timer para controlar o tempo de ataque

	virtual void InitializeBBox() override;				// Inicializa a caixa de colisão (BBox)
public:
	// Atributos publicos específicos do Boss
	int contadorMovimento;								// Essa variável serve para contar quantos movimentos o player deu!

	Boss();
	virtual ~Boss();

	// Métodos públicos auxiliares

	//--------------------------------------------------------------------------------------------
	// Métodos virtuais puros

	void ConstrainToScreen() override;					// Restringe o Boss à tela
	void UpdateAnimation() override;					// atualização da animação do Boss
};

// ------------------------------------------------------------------------------

#endif		// BOSS_H
