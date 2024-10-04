// Salto.cpp
// ------------------------------------------------------------------------------
// Inclus�es de Arquivos

#include "Salto.h"
#include "Level1.h"
#include "Character.h"

// ------------------------------------------------------------------------------

void Salto::InitializeBBox()
{
	// Inicializa a BBox
	BBox(mixed);
}

// ------------------------------------------------------------------------------

Salto::Salto(Boss* boss)
{
	//--------------------------------------------------------------------------------------------
	// Inicializa��o de vari�veis auxiliares

	this->baseDamage = boss->GetAttack();
	contador = 3;
	type = BOSSATACK;
	isDamage = true;
	timer = new Timer();
	timer->Start();
	this->boss = boss;

	//--------------------------------------------------------------------------------------------
	// Inicializa a posição

	MoveTo(Level1::player->X(), Level1::player->Y(), Layer::MIDDLE);

	//--------------------------------------------------------------------------------------------
	// Inicializa a BBox

	mixed = new Mixed();
	InitializeBBox();

	//---------------------------------------------------------------------------
	// Criação do alerta (nesse ataque ter� apenas 1 alerta)

	CreateAlert(x, y, 4);
}

// ------------------------------------------------------------------------------

Salto::~Salto()
{
	delete timer;
}

// ------------------------------------------------------------------------------

void Salto::Update()
{
	// Desenha os alertas
	if (contador != 3) {
		DrawAlerts();
	}

	if (timer->Elapsed(0.3f) && Level1::player->IsMoving()) {
		// Contador = 2 ele n�o faz nada, somente no 3 movimento do player ele ataca

		if (contador == 3) {
			contador--;
		}
		else if (contador == 2) {
			// Define quais pr�ximos alertas est�o prestes a "atacar"
			alerts[0]->UpdateAnimation();
			contador--;
		}
		else if (contador == 1) {
			// Cria a bounding box do ataque

			float width = Level1::player->GetWidth();
			float height = Level1::player->GetHeight();

			// Inicializa a BBox
			Rect* rect = new Rect(
				x - boss->GetTileWidth() / 2.3,
				y - boss->GetTileHeight() / 2.1,
				x + boss->GetTileWidth() / 2.3,
				y + boss->GetTileHeight() / 2.1);

			rect->MoveTo(0, 0 + 50);

			// Adiciona a BBox ao mixed
			mixed->Insert(rect);

			// Define a posição antiga dele para atual
			// Isso evita dele atacar o player e voltar para a posi��o antiga antes de saltar
			boss->SetPrevX(alerts[0]->GetX());
			boss->SetPrevY(alerts[0]->GetY());

			boss->MoveTo(x, y, Layer::FRONT);

			// Desativa o aviso de ataque
			alerts[0]->draw = false;

			contador--;
		}
		else if (contador == 0) {
			boss->SetIsMoving(false);
			boss->SetIsAttacked(false);
			contador--;
		}
		else if (contador == -1) {
			boss->contadorMovimento = 3;
			Level1::scene->Delete(this, MOVING);
		}

		timer->Reset();
	}

	CameraMovement();
	UpdateAlerts();
}

// ------------------------------------------------------------------------------

void Salto::OnCollision(Object* obj)
{
	// Verifica se o ataque colidiu com o player
	if (obj->Type() == PLAYER && isDamage) {
		// Converte o objeto para character
		Character* entity = (Character*)obj;

		// Verifica se o player esta se movendo ou se atacando ou andando
		if (entity->GetState() != IDLE) {
			return;
		}

		// Causa 200% do dano base do boss ao dano ao player
		Level1::player->SetDamage(baseDamage * 2);

		//--------------------------------------------------------------------------------------------
		// Verifica onde o player estão para empurr�-lo para fora do ataque

		// Player pode estão em 9 posiçães diferentes, já que o ataque tem área de 3x3
		// Posicao: (X,Y) é o centro do ataque, com essa informa��o podemos saber onde o player est�

		float xp = Level1::player->X();
		float yp = Level1::player->Y();
		float w = Level1::player->GetWidth();
		float h = Level1::player->GetHeight();

		if (compareTo(x, xp, y, yp)) {
			Level1::player->MoveTo(xp, yp - (h * 2), Layer::FRONT);	// Empurra o player para cima
		}
		if (compareTo(x - w, xp, y - h, yp) || compareTo(x - w, xp, y, yp) || compareTo(x - w, xp, y + h, yp)) {
			Level1::player->MoveTo(xp - w, yp, Layer::FRONT);		// Empurra o player para a esquerda
		}
		if (compareTo(x + w, xp, y - h, yp) || compareTo(x + w, xp, y, yp) || compareTo(x + w, xp, y + h, yp)) {
			Level1::player->MoveTo(xp + w, yp, Layer::FRONT);		// Empurra o player para a direita
		}
		if (compareTo(x, xp, y + h, yp)) {
			Level1::player->MoveTo(xp, yp + h, Layer::FRONT);		// Empurra o player para baixo
		}
		if (compareTo(x, xp, y - h, yp)) {
			Level1::player->MoveTo(xp, yp - h, Layer::FRONT);		// Empurra o player para cima
		}

		//--------------------------------------------------------------------------------------------
		// Desativa o dano

		isDamage = false;
	}
}

// ------------------------------------------------------------------------------

void Salto::Draw()
{
}

// ------------------------------------------------------------------------------