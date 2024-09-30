// Mouse.h

#ifndef MOUSE_H
#define MOUSE_H

#include "Object.h"
#include "Animation.h"

enum MouseState
{
	MOUSE_IDLE, MOUSE_CLICK, DRAG, DRAG_CLICK, LOADING
};

class Mouse : public Object
{
private:
	TileSet * tileSet;
	Animation * anim;
	bool click;
	bool hover;
	bool isLoading;

public:
	Mouse();
	~Mouse();

	void Update() override;
	void Draw() override;
	void OnCollision(Object* obj) override;
	void MoveTo();								// Move mouse para a posição do cursor e ajusta a bbox

	bool Click();								// Retorna se o mouse realizou um clique
	void SetHover();							// Define estado do mouse para hover
	void SetLoading();							// Define estado do mouse para carregando
	void SetNotLoading();						// Define estado do mouse para não carregando
};

inline void Mouse::MoveTo()	
{
	float px = window->MouseX();
	float py = window->MouseY();

	Object::MoveTo(px, py, Layer::FRONT);
	if (BBox()) BBox()->MoveTo(px - 3, py - 9);
}

inline bool Mouse::Click()
{
	if (click)
	{
		click = false;
		return true;
	}
	return click;
}

inline void Mouse::SetHover()
{
	hover = true;
}

inline void Mouse::SetLoading()
{
	isLoading = true;
}

inline void Mouse::SetNotLoading()
{
	isLoading = false;
}

#endif // MOUSE_H
