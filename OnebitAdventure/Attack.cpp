// Attack.cpp
//--------------------------------------------------------------------------------------------

#include "Attack.h"
#include "OneBitAdventure.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// Construtor
Attack::Attack() : isDelete(false), isDamage(false), timer(nullptr), mixed(nullptr)
{
	type = BOSSATACK;
	contador = 0;		// Inicializa o contador
	width = 0;			// Inicializa a largura
	height = 0;			// Inicializa a altura
	baseDamage = 0.0f;	// Inicializa o dano base
	limiarDist = 0.0f;	// Inicializa a distância do limiar
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

//-------------------------------------------------------------------------------

void Attack::UpdateAlerts()
{
	for (Alerts* alert : alerts) {
		if (alert->draw) {
			alert->Update();
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

// O movimento da câmera consiste em aplicar uma força que puxa para baixo todas as entidades,
// dando a ilusão de que o player está subindo
void Attack::CameraMovement()
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