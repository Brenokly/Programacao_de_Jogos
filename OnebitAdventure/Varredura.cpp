// Varredura.cpp

//----------------------------------------------------------------------------------------------------------------
// Incluoes de Arquivos

#include "Varredura.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Varredura::InitializeBBox()
{
	// Inicializa a BBox
	BBox(mixed);
}

// ------------------------------------------------------------------------------

Varredura::Varredura(Boss* boss)
{
	// ------------------------------------------------------------------------------------------
	// Inicializando a largura e altura
	width = Level1::player->GetWidth();
	height = Level1::player->GetHeight();

	//--------------------------------------------------------------------------------------------
	// Inicializa a anima��o do ataque

	// Ataque1 que precisa ser instanciado na frente do boss junto com os alertas
	tileSet = new TileSet("Resources/bosses/ataque.png", (width * 5) * 3, height * 2, width * 5, height * 2, 3, 3);
	anim = new Animation(tileSet, 0.3f, false);

	uint SeqAtaque1[3] = { 0, 1, 2 };

	anim->Add(0, SeqAtaque1, 3);
	anim->Select(0);

	//--------------------------------------------------------------------------------------------
	// Inicializa a posi��o do ataque

	MoveTo(boss->X(), boss->Y() + (height * 2), Layer::MIDDLE);

	//--------------------------------------------------------------------------------------------
	// Inicializa a BBox

	mixed = new Mixed();
	InitializeBBox();

	//--------------------------------------------------------------------------------------------
	// Inicializa��o de vari�veis auxiliares

	type = BOSSATACK;
	timer = new Timer();
	timer->Start();
	isDamage = true;
	contador = 3;
	this->baseDamage = boss->GetAttack();
	this->boss = boss;

	// Cria os alertas (Ser�o 7 para esse ataque)
	CreateAlert(x + (width * 2), y - height, 1);		// primeiro alerta (canto direito)
	CreateAlert(x + (width * 2), y, 1);					// segundo alerta 
	CreateAlert(x + (width * 1), y, 1);					// terceiro alerta
	CreateAlert(x, y, 1);								// quarto alerta
	CreateAlert(x - (width * 1), y, 1);					// quinto alerta
	CreateAlert(x - (width * 2), y, 1);					// sexto alerta
	CreateAlert(x - (width * 2), y - height, 1);		// s�timo alerta (canto direito)

	// Define quais pr�ximos alertas est�o prestes a "atacar"
	alerts[0]->UpdateAnimation();
	alerts[1]->UpdateAnimation();
}

// ------------------------------------------------------------------------------

Varredura::~Varredura()
{
	delete anim;
	delete tileSet;
	delete timer;
}

// ------------------------------------------------------------------------------

void Varredura::Update()
{
	DrawAlerts();

	if (timer->Elapsed(0.3f) && Level1::player->IsMoving()) {
		if (contador == 3) {
			anim->Select(0);

			// L�gica de criar a primeira bbox do atack
			Rect* rect = new Rect(
				x - tileSet->TileWidth() / 8.5f,
				y - tileSet->TileHeight() / 2.2f,
				x + tileSet->TileWidth() / 10.5f,
				y + tileSet->TileHeight() / 2.3f);

			rect->MoveTo(0 + (width * 2), 0 - (height * 0.48));

			mixed->Insert(rect);

			// Define quais pr�ximos alertas est�o prestes a "atacar"
			alerts[2]->UpdateAnimation();
			alerts[3]->UpdateAnimation();

			// Remove os alertas que j� atacaram
			alerts[0]->draw = false;
			alerts[1]->draw = false;

			contador--;
		}
		else if (contador == 2) {
			anim->NextFrame();

			Rect* rect = new Rect(
				x - tileSet->TileWidth() / 7.5f,
				y - tileSet->TileHeight() / 5.0f,
				x + tileSet->TileWidth() / 3.6f,
				y + tileSet->TileHeight() / 5.0f);

			rect->MoveTo(0, 0);

			mixed->Insert(rect);

			// Define quais pr�ximos alertas est�o prestes a "atacar"
			alerts[4]->UpdateAnimation();
			alerts[5]->UpdateAnimation();
			alerts[6]->UpdateAnimation();

			// Remove os alertas que j� atacaram
			alerts[2]->draw = false;
			alerts[3]->draw = false;

			contador--;
		}
		else if (contador == 1) {
			anim->NextFrame();

			Rect* rect = new Rect(
				x - tileSet->TileWidth() / 12.0f,
				y - tileSet->TileHeight() / 5.0f,
				x + tileSet->TileWidth() / 15.0f,
				y + tileSet->TileHeight() / 5.0f);

			rect->MoveTo(0 - width, 0);

			mixed->Insert(rect);

			rect = new Rect(
				x - tileSet->TileWidth() / 10.5f,
				y - tileSet->TileHeight() / 2.2f,
				x + tileSet->TileWidth() / 8.5f,
				y + tileSet->TileHeight() / 2.3f);

			rect->MoveTo(0 - (width * 2), 0 - (height * 0.48));

			mixed->Insert(rect);


			// Remove os alertas que j� atacaram
			alerts[4]->draw = false;
			alerts[5]->draw = false;
			alerts[6]->draw = false;

			contador--;
		}
		else if (contador == 0) {
			boss->contadorMovimento = 3;
			boss->SetIsMoving(false);
			boss->SetIsAttacked(false);
			Level1::scene->Delete(this, MOVING);
		}

		timer->Reset();
	}

	CameraMovement();
	UpdateAlerts();
}

// ------------------------------------------------------------------------------

void Varredura::Draw()
{
	if (contador != 3) {
		anim->Draw(anim->Frame(), x, y - (height * 0.5), Layer::BACK, 1.0f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// ------------------------------------------------------------------------------

void Varredura::OnCollision(Object* obj)
{
	if (isDamage) {
		if (obj->Type() == PLAYER) {

			Character* entity = (Character*)obj;

			if (entity->IsMoving()) return;

			// Verifica se o player se encontra no centro do ataque, se sim, aplica 300% do dano base da hydra
			if (Level1::player->X() >= (x - width) && Level1::player->X() + 20 <= (x + width)) {

				Level1::player->SetDamage(baseDamage * 3);  // Aplica 300% do dano base
				entity->Move(DOWN);
			}
			else {
				// Est� nas laterais do ataque, logo, aplica 200% do dano base da hydra
				Level1::player->SetDamage(baseDamage * 2);  // Aplica 200% do dano base

				// Lateral direita
				if (entity->X() > x) {
					entity->Move(RIGHT);
				}
				else {
					entity->Move(LEFT);
				}
			}

			// Dano que o inimigo causou
			((Character*)obj)->text.insert({ std::to_string(Level1::player->GetDamage()), Color(0.941f, 0.318f, 0.459f, 1.0f) });


			isDamage = false;
		}
	}
}

// ------------------------------------------------------------------------------