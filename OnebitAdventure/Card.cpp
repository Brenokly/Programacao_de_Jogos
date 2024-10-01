#include "Card.h"
#include "OneBitAdventure.h"

Card::Card(float x, float y, float width, float height, bool created) 
	: created(created)
{
	// --------------------------------------------------------------------
	// Inicialização de tilesets, fontes, velocidade e bounding box

	backg = new Sprite("Resources/card.png", width, height);
	font = new Font("Resources/press12.png");
	font->Spacing("Resources/press12.dat");

	speed = new Vector();

	// --------------------------------------------------------------------
	// Inicialização de variáveis de posição e bounding box

	MoveTo(x, y, Layer::FRONT);

	
	mixed = new Mixed();		// Criando um novo Mixed para a BBox

	Rect* rect = new Rect		// Criando um novo Rect para a BBox
	(
		x - width / 2.0f,
		y - height / 2.0f,
		x + width / 2.0f,
		y + height / 2.0f
	);

	rect->MoveTo(-x, -y);	// Movendo o Rect para a posição do objeto

	mixed->Insert(rect);		// Inserindo o Rect no Mixed

	BBox(mixed);				// Definindo a BBox do objeto


	// Não me pergunte do porque só funciona com mixed, eu não sei!
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
	if (OneBitAdventure::mouse->Click())
	{

	}
}
