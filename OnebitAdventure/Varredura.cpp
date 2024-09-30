// Varredura.cpp

//----------------------------------------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Varredura.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

void Varredura::InitializeBBox()
{
    // Inicializa a BBox
    BBox(mixed);
}

// ------------------------------------------------------------------------------

Varredura::Varredura(float x, float y, float baseDamage)
{
	// ------------------------------------------------------------------------------------------
	// Inicializando a largura e altura
	width = Level1::player->GetWidth();
	height = Level1::player->GetHeight();

	//--------------------------------------------------------------------------------------------
	// Inicializa a animação do ataque

    // Ataque1 que precisa ser instanciado na frente do boss junto com os alertas
    tileSet = new TileSet("Resources/bosses/ataque.png", (width * 5) * 3, height * 2, width * 5, height * 2, 3, 3);
    anim = new Animation(tileSet, 0.3f, false);

    uint SeqAtaque1[3] = { 0, 1, 2};

    anim->Add(0, SeqAtaque1, 3);
    anim->Select(0);

	//--------------------------------------------------------------------------------------------
	// Inicializa a BBox

    mixed = new Mixed();
    InitializeBBox();

	//--------------------------------------------------------------------------------------------
	// Inicialização de variáveis auxiliares

	type = BOSSATACK;
	timer = new Timer();
	timer->Start();
	isDamage = true;
	contador = 4;
	this->baseDamage = baseDamage;

	// Cria os alertas (Serão 7 para esse ataque)
	CreateAlert(SMALLWARNING, x + (width * 2), y + height, 1);			// primeiro alerta (canto direito)
	CreateAlert(SMALLWARNING, x + (width * 2), y + (height * 2), 1);	// segundo alerta 
	CreateAlert(SMALLWARNING, x + (width * 1), y + (height * 2), 1);	// terceiro alerta
	CreateAlert(SMALLWARNING, x				 , y + (height * 2), 1);	// quarto alerta
	CreateAlert(SMALLWARNING, x - (width * 1), y + (height * 2), 1);	// quinto alerta
	CreateAlert(SMALLWARNING, x - (width * 2), y + (height * 2), 1);	// sexto alerta
	CreateAlert(SMALLWARNING, x - (width * 2), y + height, 1);			// sétimo alerta (canto direito)

	// Define quais próximos alertas estão prestes a "atacar"
	alerts[0]->UpdateAnimation();
	alerts[1]->UpdateAnimation();

	//--------------------------------------------------------------------------------------------
	// Inicializa a posição do ataque

	MoveTo(x, y + (height * 1.5), Layer::FRONT);
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
	 
    if (timer->Elapsed(0.2f) && Level1::player->IsMoving()) {
		contador--;

		if (contador == 3) {
			anim->Select(0);

			// Lógica de criar a primeira bbox do atack
			Rect* rect = new Rect(
				x - tileSet->TileWidth() / 8.5f,
				y - tileSet->TileHeight() / 2.2f,
				x + tileSet->TileWidth() / 10.5f,
				y + tileSet->TileHeight() / 2.3f);

			rect->MoveTo(0 + (width * 2), 0);

			mixed->Insert(rect);

			// Define quais próximos alertas estão prestes a "atacar"
			alerts[2]->UpdateAnimation();
			alerts[3]->UpdateAnimation();

			// Remove os alertas que já atacaram
			alerts[0]->draw = false;
			alerts[1]->draw = false;
		}
		else {
			anim->NextFrame();

			if (contador == 2) {
				Rect* rect = new Rect(
					x - tileSet->TileWidth() / 3.6f,
					y - tileSet->TileHeight() / 5.0f,
					x + tileSet->TileWidth() / 3.6f,
					y + tileSet->TileHeight() / 5.0f);

				rect->MoveTo(0, 0 + 26);

				mixed->Insert(rect);

				// Define quais próximos alertas estão prestes a "atacar"
				alerts[4]->UpdateAnimation();
				alerts[5]->UpdateAnimation();
				alerts[6]->UpdateAnimation();

				// Remove os alertas que já atacaram
				alerts[2]->draw = false;
				alerts[3]->draw = false;
			}
			else if (contador == 1) {
				Rect* rect = new Rect(
					x - tileSet->TileWidth() / 10.5f,
					y - tileSet->TileHeight() / 2.2f,
					x + tileSet->TileWidth() / 8.5f,
					y + tileSet->TileHeight() / 2.3f);

				rect->MoveTo(0 - (width * 2), 0);

				mixed->Insert(rect);


				// Remove os alertas que já atacaram
				alerts[4]->draw = false;
				alerts[5]->draw = false;
				alerts[6]->draw = false;
			}
		}

		if (isDelete) {
			Level1::scene->Delete();
		}

        if (anim->Frame() == 2) {
            isDelete = true;
        }

		timer->Reset();
    }
}

// ------------------------------------------------------------------------------

void Varredura::Draw()
{
	if (contador != 4) {
		anim->Draw(anim->Frame(), x, y, Layer::BACK, 1.0f, 0.0f, Color(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// ------------------------------------------------------------------------------

void Varredura::OnCollision(Object* obj)
{
    if (isDamage) {
		if (obj->Type() == PLAYER) {

			// Verifica se o player se encontra no centro do ataque, se sim, aplica 300% do dano base da hydra
			if (Level1::player->X() >= (x - width) && Level1::player->X() + 20 <= (x + width)) {

				Level1::player->SetDamage(baseDamage * 3);  // Aplica 300% do dano base
			}
			else {

				// Está nas laterais do ataque, logo, aplica 200% do dano base da hydra
				Level1::player->SetDamage(baseDamage * 2);  // Aplica 200% do dano base

			}

			// Dano que o inimigo causou
			((Character*)obj)->text.insert({ std::to_string(Level1::player->GetDamage()), Color(0.941f, 0.318f, 0.459f, 1.0f)});
			

			isDamage = false;
		}
    }
}

// ------------------------------------------------------------------------------