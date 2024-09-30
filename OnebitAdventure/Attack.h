// Attack.h
// ------------------------------------------------------------------------------

#ifndef ATTACK_H
#define ATTACK_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include <deque>						// Deque
#include "TileSet.h"                    // Folha de sprite
#include "Animation.h"                  // Animações de sprites
#include "Object.h"						// Classe base para objetos
#include "Alerts.h"						// Alertas

// ------------------------------------------------------------------------------

class Attack : public Object
{
protected:
	// --------------------------------------------------------------------------------------------
	// Atributos de Sprites e Animação

	TileSet* tileSet;							// Folha de sprite
	Animation* anim;							// Animação de sprite

	// --------------------------------------------------------------------------------------------
	// Atributos de Dimensão e Movimentação

	bool isDelete;								// Indica se a animação do ataque já finalizou
	bool isDamage;								// Indica se o ataque causou dano
	int contador;								// Contador de movimento do player
	float width, height;						// Largura e altura
	float baseDamage;							// Guarda o dano base do ataque do boss

	// --------------------------------------------------------------------------------------------
	// Atributos de Colisão

	Timer* timer;								// Temporizador de duração do ataque
	Mixed* mixed;								// Caixa de colisão mista
	std::deque<Alerts*> alerts;					// Deque de alertas

	// --------------------------------------------------------------------------------------------
	// Métodos Protegidos

	virtual void InitializeBBox() = 0;			// Inicializa a caixa de colisão (BBox)
public:
	Attack();									// Construtor
	virtual ~Attack();							// Destrutor virtual puro

	// --------------------------------------------------------------------------------------------

	// Método para criar Alertas
	void DrawAlerts();
	void CreateAlert(AlertType alertType, float x, float y, int scala);
	void UpdateAnimation();						// Atualiza a animação do ataque
	virtual void OnCollision(Object* obj) = 0;	// Resolução da colisão
	virtual void Update() = 0;				    // Atualiza o estado do ataque
	virtual void Draw() = 0;                    // Desenha o ataque

};

#endif
// ------------------------------------------------------------------------------