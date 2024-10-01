// Salto.h
// ------------------------------------------------------------------------------

#ifndef SALTO_H
#define SALTO_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Attack.h"
#include "Timer.h"
#include "Boss.h"

// ------------------------------------------------------------------------------

class Salto : public Attack
{
protected:
	// --------------------------------------------------------------------------------------------
	// Atributos de Sprites e Animação e etc

	// --------------------------------------------------------------------------------------------
	// Métodos Protegidos

	void InitializeBBox() override;					// Inicializa a caixa de colisão (BBox)
public:
	Salto(Boss* boss);								// Construtor
	~Salto();										// Destrutor

	// --------------------------------------------------------------------------------------------

	void Update() override;							// Atualiza o estado do ataque
	void Draw() override;							// Desenha o ataque
	void OnCollision(Object* obj) override;			// Resolução da colisão
};

// ------------------------------------------------------------------------------

#endif