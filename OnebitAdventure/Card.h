// Card.h

#ifndef CARD_H
#define CARD_H

#include "Object.h"
#include "Sprite.h"
#include "Font.h"
#include "Vector.h"

// ------------------------------------------------------------------------------

class Card : public Object
{
private:
	Sprite * backg;
	Font * font;
	Vector * speed;
	bool created;				// Indica se é um card de personagem já criado
	Mixed* mixed;				// Caixa de colisão mista 

public:
	Card(float x, float y, float width, float height, bool created = false);
	~Card();

	void Update();
	void Draw();
	void OnCollision(Object* obj);
};

// ------------------------------------------------------------------------------

#endif
