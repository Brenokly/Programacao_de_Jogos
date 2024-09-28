// Varredura.h
// ------------------------------------------------------------------------------

#ifndef VARREDURA_H
#define VARREDURA_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Attack.h"
#include "Timer.h"
#include "Character.h"

// ------------------------------------------------------------------------------

class Varredura : public Attack
{
protected:
	// --------------------------------------------------------------------------------------------
	// Atributos de Sprites e Animação e etc

	// --------------------------------------------------------------------------------------------
	// Métodos Protegidos

	void InitializeBBox() override;				// Inicializa a caixa de colisão (BBox)
public:
	Varredura(float x, float y);				// Construtor
	~Varredura();								// Destrutor

	// --------------------------------------------------------------------------------------------

	void Update() override;						// Atualiza o estado do ataque
	void Draw() override;						// Desenha o ataque
	void OnCollision(Object* obj) override;		// Resolução da colisão
};

#endif
// ------------------------------------------------------------------------------