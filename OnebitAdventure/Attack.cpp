// Attack.cpp
//--------------------------------------------------------------------------------------------

#include "Attack.h"

// ------------------------------------------------------------------------------

// Construtor
Attack::Attack() : tileSet(nullptr), anim(nullptr), isDelete(false), isDamage(false), timer(nullptr), mixed(nullptr)
{
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
		alert->Draw();
	}
}

// ------------------------------------------------------------------------------

// Função para remover um alerta do vetor
void Attack::RemoveAlert(size_t index) {
	if (index < alerts.size()) { // Verifique se o índice está dentro dos limites
		delete alerts[index]; // Deleta o alerta e libera a memória
		alerts.erase(alerts.begin() + index); // Remove o alerta do vetor
	}
}

// ------------------------------------------------------------------------------

void Attack::CreateAlert(AlertType alertType, float x, float y, int scala) {
	Alerts* newAlert = new Alerts(alertType, x, y, scala);
	alerts.push_back(newAlert); // Adiciona o novo alerta ao vetor
}

// ------------------------------------------------------------------------------