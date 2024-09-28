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

public:
	Mouse();
	~Mouse();

	void Update() override;
	void Draw() override;
};

#endif // MOUSE_H
