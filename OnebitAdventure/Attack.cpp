// Attack.cpp
//--------------------------------------------------------------------------------------------

#include "Attack.h"

// ------------------------------------------------------------------------------

// Construtor
Attack::Attack() : tileSet(nullptr), anim(nullptr), isDelete(false), isDamage(false), timer(nullptr), mixed(nullptr)
{
	contador = 0;		// Inicializa o contador
	width = 0;			// Inicializa a largura
	height = 0;			// Inicializa a altura
	baseDamage = 0.0f;	// Inicializa o dano base
}

//-------------------------------------------------------------------------------

Attack::~Attack()
{
	// Libere a memória dos alertas
	for (Alerts* alert : alerts) {
		delete alert; // Libera cada alerta do vetor
	}
}

// ------------------------------------------------------------------------------

void Attack::UpdateAnimation()
{
	anim->NextFrame();
}

// ------------------------------------------------------------------------------

void Attack::DrawAlerts()
{
	for (Alerts* alert : alerts) {
		if (alert->draw) {
			alert->Draw();
		}
	}
}

// ------------------------------------------------------------------------------

void Attack::CreateAlert(AlertType alertType, float x, float y, int scala) {
	Alerts* newAlert = new Alerts(alertType, x, y, scala);
	alerts.push_back(newAlert);  // Adiciona o novo alerta ao deque
}

// ------------------------------------------------------------------------------