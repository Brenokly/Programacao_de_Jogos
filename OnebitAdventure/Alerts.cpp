// Alerts.cpp
// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Alerts.h"
#include "Level1.h"
#include "Character.h"

// ------------------------------------------------------------------------------

Alerts::Alerts(AlertType alertType, float x, float y, float scala)
{
	int width = Level1::player->GetWidth();
	int height = Level1::player->GetHeight();

	//--------------------------------------------------------------------------------------------
	// Variáveis auxiliares
	nextFrame = false;
	draw = true;
	type = alertType;
	this->x = x;
	this->y = y;
	this->scala = scala;

	spriteAlerts = new Sprite("Resources/bosses/smallWarning2.png", width, height);
}

// ------------------------------------------------------------------------------

Alerts::~Alerts()
{
	delete spriteAlerts;
}

// ------------------------------------------------------------------------------