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
	limiarDist = 0.0f;
	draw = true;
	this->scala = scala;
	color = new Color{ 0.592f, 0.0f, 0.224f, 1.0f };

	spriteAlerts = new Sprite("Resources/bosses/smallWarning2.png", width, height);

	MoveTo(x, y, Layer::MIDDLE);
}

// ------------------------------------------------------------------------------

Alerts::~Alerts()
{
	delete spriteAlerts;
	if (this->color != &defaultColor && this->color != nullptr) {
		delete color;
	}
}

// --------------------------------------------------------------------------------

void Alerts::Update()
{
	CameraMovement();
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

// O movimento da câmera consiste em aplicar uma força que puxa para baixo todas as entidades,
// dando a ilusão de que o player está subindo
void Alerts::CameraMovement()
{
	// Verifica se o player passou do limiar
	if (Level1::player->Y() > window->CenterY()) return;

	// Calcula a distância entre o player e o limiar
	limiarDist = fabs(Level1::player->Y() - window->CenterY());

	// Se o jogador passou do limiar, começa a aplicar a força de gravidade
	if (limiarDist > 0) {
		Translate(0, limiarDist * gameTime);
	}
}

//-------------------------------------------------------------------------------------