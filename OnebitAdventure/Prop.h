// Prop.h

#ifndef PROP_H
#define PROP_H

// ----------------------------------------------------------------------------------
// Inclusões

#include "Entity.h"
#include "OneBitAdventure.h"

// ----------------------------------------------------------------------------------

class Prop : public Entity
{
private:
	Sprite* sprite = nullptr;										// Ponteiro para sprite do objeto

public:
	bool interactable;												// Flag para indicar se o objeto é interagível

	Prop(uint type, Image *& image, float col, float line, bool interactable, bool bbox = true);
	~Prop();

	void Update() override;
	void Draw() override;
	void OnCollision(Object* obj) override;
	void UpdateAnimation() override;
	void InitializeBBox() override;
};

// ----------------------------------------------------------------------------------

inline void Prop::Draw()
{
	if (type == DOOR || type == CHEST || type == CAMPFIRE)
		anim->Draw(x, y, z);
	else
		sprite->Draw(x, y, z);
}

// ----------------------------------------------------------------------------------

#endif // PROP_H
