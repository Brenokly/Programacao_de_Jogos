// Alerts.cpp
// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Alerts.h"
#include "Level1.h"
#include "Character.h"

// ------------------------------------------------------------------------------

// Definição do membro estático
Color Alerts::defaultColor{ 0.941f, 0.318f, 0.459f, 1.0f };

// ------------------------------------------------------------------------------

Alerts::Alerts(float x, float y, float scala)
{
	int width = Level1::player->GetWidth();
	int height = Level1::player->GetHeight();

	//--------------------------------------------------------------------------------------------
	// Variáveis auxiliares
	nextFrame = false;
	draw = true;
	this->x = x;
	this->y = y;
	this->scala = scala;
	color = new Color{ 0.592f, 0.0f, 0.224f, 1.0f };

	spriteAlerts = new Sprite("Resources/bosses/smallWarning2.png", width, height);
}

// ------------------------------------------------------------------------------

Alerts::~Alerts()
{
	delete spriteAlerts;
	if (this->color != &defaultColor && this->color != nullptr) {
		delete color;
	}
}

// ------------------------------------------------------------------------------

void Alerts::UpdateAnimation(Color* color) {
	if (color == nullptr) {
		color = &defaultColor; // Usa o padrão se nenhum valor for fornecido
	}

	// Lógica de atualização

	// Deleta apenas se this->color não aponta para o defaultColor
	if (this->color != &defaultColor && this->color != nullptr) {
		delete this->color;
	}

	this->color = color;
}

// ------------------------------------------------------------------------------