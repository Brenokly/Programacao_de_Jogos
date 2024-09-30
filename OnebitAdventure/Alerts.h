// Alerts.h
// ------------------------------------------------------------------------------

#ifndef ALERTS_H
#define ALERTS_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Object.h"
#include "TileSet.h"
#include "Animation.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

enum AlertType{BIGWARNING, SMALLWARNING};

// ------------------------------------------------------------------------------

class Alerts
{
protected:
	// --------------------------------------------------------------------------------------------
	// Atributos de Sprites e Animação e etc

	Sprite * spriteAlerts;													// Sprite dos alertas

	// --------------------------------------------------------------------------------------------
	// Métodos Auxiliares

	AlertType type;															// Tipo de alerta
	bool nextFrame;															// Próximo frame
	float x, y, scala;														// Posição do alerta

public:
	bool draw;																// Desenha o alerta

	Alerts(AlertType alertType, float x, float y, float scala);				// Construtor
	~Alerts();																// Destrutor

	// --------------------------------------------------------------------------------------------

	void UpdateAnimation();													// Atualiza a animação
	void Draw();															// Desenha o ataque
};

// ------------------------------------------------------------------------------

inline void Alerts::Draw()
{
	if (nextFrame) {
		// Desenha o alerta mais claro, indicando que o ataque é o próximo
		spriteAlerts->Draw(x ,y , Layer::MIDDLE, scala, 0.0f, Color(0.941f, 0.318f, 0.459f, 1.0f));
	}
	else {
		// Desenha o alerta mais escuro, indicando que o ataque não é o próximo
		spriteAlerts->Draw(x, y, Layer::MIDDLE, scala, 0.0f, Color(0.592f, 0.0f, 0.224f, 1.0f));
	}
}

// ------------------------------------------------------------------------------

inline void Alerts::UpdateAnimation()
{
	nextFrame = true;
}

#endif
// ------------------------------------------------------------------------------