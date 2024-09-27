// Attack.h
// ------------------------------------------------------------------------------

#ifndef ATTACK_H
#define ATTACK_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "TileSet.h"                    // Folha de sprite
#include "Animation.h"                  // Animações de sprites
#include "Object.h"						// Classe base para objetos

// ------------------------------------------------------------------------------

class Attack : public Object
{
protected:
	// --------------------------------------------------------------------------------------------
	// Atributos de Sprites e Animação

	TileSet* tileSet;							// Folha de sprite
	Animation* anim;							// Animação de sprite

	TileSet* alerts;							// Folha de sprite
	Animation* animAlerts;						// Animação de sprite

	// --------------------------------------------------------------------------------------------
	// Atributos de Dimensão e Movimentação

	bool movementPlayer;						// Indica se o player se moveu
	bool isDelete;								// Indica se a animação do ataque já finalizou
	bool isDamage;								// Indica se o ataque causou dano

	// --------------------------------------------------------------------------------------------
	// Atributos de Colisão

	Timer* timer;								// Temporizador de duração do ataque
	Mixed* mixed;								// Caixa de colisão mista

	// --------------------------------------------------------------------------------------------
	// Métodos Protegidos

	virtual void InitializeBBox() = 0;			// Inicializa a caixa de colisão (BBox)
public:
	Attack();									// Construtor
	virtual ~Attack() = 0;						// Destrutor virtual puro

	// --------------------------------------------------------------------------------------------

	void UpdateAnimation();						// Atualiza a animação do ataque
	virtual void OnCollision(Object* obj) = 0;	// Resolução da colisão
	virtual void Update();				        // Atualiza o estado do ataque
	virtual void Draw();                        // Desenha o ataque
};

#endif
// ------------------------------------------------------------------------------