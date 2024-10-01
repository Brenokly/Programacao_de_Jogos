#include "Prop.h"
#include "Level1.h"
#include "Character.h"

// ----------------------------------------------------------------------------------

Prop::Prop(uint type, Image *& image, float col, float line, bool interactable, bool bbox)
	: Entity(), interactable(interactable)
{
	this->type = type;

	uint width, height;

	if (type == DOOR || type == CHEST)
	{
		width = image->Width() / 2;
		height = image->Height();

		tileSet = new TileSet(image, width, height, 2, 2);
		anim = new Animation(tileSet, 0.0f, false);

		uint seq1[1] = { 0 };
		uint seq2[1] = { 1 };

		// Sequência 0 padrão, 1 quando player interage
		anim->Add(0, seq1, 1);
		anim->Add(1, seq2, 1);
		anim->Select(0);
	}
	else if (type == CAMPFIRE)
	{
		width = image->Width() / 2;
		height = image->Height();

		tileSet = new TileSet(image, width, height, 2, 2);
		anim = new Animation(tileSet, 1.0f, true);
	}
	else
	{
		sprite = new Sprite(image);
		width = sprite->Width();
		height = sprite->Height();
	}

	if (bbox)
	{
		InitializeBBox();
	}

	if (type == PILLAR)
	{
		MoveTo(col, line, Layer::MIDDLE - 0.1f);
	}
	else if (type == PILLAR2)
	{
		MoveTo(col, line, Layer::MIDDLE - 0.2f);
	}
	else
	{
		MoveTo(col, line, Layer::LOWER);
	}
}

// ----------------------------------------------------------------------------------

Prop::~Prop()
{
	if (sprite) delete sprite;
	if (anim) delete anim;
	if (tileSet) delete tileSet;
}

// ----------------------------------------------------------------------------------

void Prop::InitializeBBox()
{
	if (type == PILLAR || type == PILLAR2)
	{
		Mixed* mixed = new Mixed();
		Rect * rect = new Rect(
			x - width / 2.4f,
			y - height / 2.3f,
			x + width / 2.4f,
			y + height / 2.3f);
		rect->MoveTo(-x, height);
		mixed->Insert(rect);
		BBox(mixed);
	}
	else
	{
		BBox(new Rect(
			x - width / 2.4f,
			y - height / 2.3f,
			x + width / 2.4f,
			y + height / 2.3f)
		);
	}
}

// ----------------------------------------------------------------------------------

void Prop::Update()
{
	CameraMovement();

	UpdateAnimation();

	if (type == PILLAR)
	{
		if (y - 1.5f * height >= window->Height()) {
			Level1::scene->Delete();
		}
	}
	else
	{
		if (y - (height / 2.0f) >= window->Height()) {
			Level1::scene->Delete();
		}
	}
}

// ----------------------------------------------------------------------------------

void Prop::UpdateAnimation()
{
	// Verifica se o player passou pela porta
	if (type == DOOR && anim->Frame() == 1)
	{
		if (!Level1::hud->Collision(this, Level1::player))
		{
			// Fecha a porta
			anim->Select(0);
			OneBitAdventure::audio->Play(PORTA);
		}
	}

	if (type == CAMPFIRE)
	{
		anim->NextFrame();
	}
}

// ----------------------------------------------------------------------------------

void Prop::OnCollision(Object* obj)
{
	if (!interactable) return;
	if (type == DOOR || type == CHEST)
	{
		// Se player interagir com a porta
		if (obj->Type() == PLAYER)
		{
			// Se a porta estiver fechada
			if (anim->Frame() == 0)
			{
				// Abre a porta
				anim->Select(1);
				OneBitAdventure::audio->Play(PORTA);
			}
		}
	}
}

// ----------------------------------------------------------------------------------
