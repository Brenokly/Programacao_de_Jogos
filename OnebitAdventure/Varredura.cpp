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

Varredura::Varredura(float x, float y)
{
	int width = Level1::player->GetWidth();
	int height = Level1::player->GetHeight();

	//--------------------------------------------------------------------------------------------
	// Inicializa TileSet com a animação dos alertas

	alerts = new TileSet("Resources/bosses/smallWarning.png", width * 2, height, width, height, 2, 2);
	animAlerts = new Animation(alerts, 0.2f, false);

	uint SeqAlerts[2] = { 0, 1 };
	animAlerts->Add(0, SeqAlerts, 2);
	animAlerts->Select(1);

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

	// Inicialização de variáveis auxiliares
	type = BOSSATACK;
	timer = new Timer();

	//--------------------------------------------------------------------------------------------
	// Inicializa a posição do ataque

	MoveTo(x, y, Layer::FRONT);
}

// ------------------------------------------------------------------------------

Varredura::~Varredura()
{
	delete anim;
	delete tileSet;
}

// ------------------------------------------------------------------------------

void Varredura::Update()
{
    if (timer->Elapsed(0.2f) && Level1::player->IsMoving()) {
        movementPlayer = true;
	}
	else {
		movementPlayer = false;
	}

    if (movementPlayer) {
        anim->NextFrame();

		if (isDelete && movementPlayer) {
			Level1::scene->Delete();
		}

        if (anim->Frame() == 2) {
            isDelete = true;
            timer->Start();
        }
    }
}

// ------------------------------------------------------------------------------

void Varredura::Draw()
{
	anim->Draw(anim->Frame(),x, y, Layer::FRONT, 1.0f, 0.0f, Color(1.0f,1.0f,1.0f,1.0f));
}

// ------------------------------------------------------------------------------

void Varredura::OnCollision(Object* obj)
{
    if (isDamage) {
		if (obj->Type() == PLAYER) {
            Level1::player->SetDamage(200);
		}
    }
}

// ------------------------------------------------------------------------------