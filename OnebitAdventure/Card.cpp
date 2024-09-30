#include "Card.h"
#include "OneBitAdventure.h"

Card::Card(float x, float y, float width, float height, bool created) 
	: created(created)
{
	backg = new Sprite("Resources/card.png", width, height);
	font = new Font("Resources/press12.png");
	font->Spacing("Resources/press12.dat");

	speed = new Vector();

	BBox(new Rect
	(
		x - width / 2.0f,
		y - height / 2.0f,
		x + width / 2.0f,
		y + height / 2.0f
	));

	MoveTo(x, y, Layer::FRONT);
}

Card::~Card()
{
	delete speed;
	delete font;
	delete backg;
}

void Card::Update()
{

}

void Card::Draw()
{
	backg->Draw(x, y, z);

	if (!created)
	{
		font->Draw(x, y - 20.0f, "+");
		font->Draw(x - 70.0f, y, "Criar novo");
		font->Draw(x - 70.0f, y + 20.0f, "personagem");
	}
}

void Card::OnCollision(Object* obj)
{
	OneBitAdventure::mouse->SetHover();
}
