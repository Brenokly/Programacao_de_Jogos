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
#include "Boss.h"						// Classe do Boss

// ------------------------------------------------------------------------------

class Attack : public Object
{
protected:
	// --------------------------------------------------------------------------------------------
	// Atributos de lógica

	Boss* boss;										// Ponteiro para o boss

	// --------------------------------------------------------------------------------------------
	// Atributos de Sprites e Animação

	// --------------------------------------------------------------------------------------------
	// Atributos de Dimensão e Movimentação

	bool isDelete;									// Indica se a animação do ataque já finalizou
	bool isDamage;									// Indica se o ataque já causou dano
	int contador;									// Contador de movimento do player
	float width, height;							// Largura e altura de um quadrado de movimento
	float baseDamage;								// Guarda o dano base do ataque do boss
	float limiarDist;								// Distância do player até o limiar

	// --------------------------------------------------------------------------------------------
	// Atributos de Colisão

	Timer* timer;									// Temporizador de duração do ataque
	Mixed* mixed;									// Caixa de colisão mista
	std::deque<Alerts*> alerts;						// Deque de alertas

	// --------------------------------------------------------------------------------------------
	// Métodos Protegidos

	void CameraMovement();								// realiza a movimentação da câmera
	virtual void InitializeBBox() = 0;				// Inicializa a caixa de colisão (BBox)
public:
	Attack();										// Construtor
	virtual ~Attack();								// Destrutor virtual puro

	// --------------------------------------------------------------------------------------------

	// Método para criar Alertas
	void DrawAlerts();												// Desenha os alertas
	void UpdateAlerts();											// Atualiza os alertas
	void CreateAlert(float x, float y, int scala);					// Cria um alerta
	virtual void OnCollision(Object* obj) = 0;						// Resolução da colisão
	virtual void Update() = 0;										// Atualiza o estado do ataque
	virtual void Draw() = 0;										// Desenha o ataque
	bool compareTo(int px1, int px2, int py1, int py2);		// Compara se o ataque já finalizou
};

#endif
// ------------------------------------------------------------------------------