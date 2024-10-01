// Attack.cpp
//--------------------------------------------------------------------------------------------

#include "Attack.h"

// ------------------------------------------------------------------------------

// Construtor
Attack::Attack() : isDelete(false), isDamage(false), timer(nullptr), mixed(nullptr)
{
	contador = 0;		// Inicializa o contador
	width = 0;			// Inicializa a largura
	height = 0;			// Inicializa a altura
	baseDamage = 0.0f;	// Inicializa o dano base
	boss = nullptr;		// Inicializa o ponteiro do boss
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

void Attack::DrawAlerts()
{
	for (Alerts* alert : alerts) {
		if (alert->draw) {
			alert->Draw();
		}
	}
}

// ------------------------------------------------------------------------------

void Attack::CreateAlert(float x, float y, int scala) {
	Alerts* newAlert = new Alerts(x, y, scala);
	alerts.push_back(newAlert);  // Adiciona o novo alerta ao deque
}

// ------------------------------------------------------------------------------

bool Attack::compareTo(int px1, int px2, int py1, int py2)
{
	return px1 == px2 && py1 == py2;
}

// ------------------------------------------------------------------------------