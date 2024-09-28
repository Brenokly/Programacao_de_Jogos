// Mouse.cpp

#include "Mouse.h"
#include "OneBitAdventure.h"

Mouse::Mouse()
{
	tileSet = new TileSet("Resources/Cursor.png", 3, 4);
	anim = new Animation(tileSet, 0.05f, false);

	uint idle[] = { 3 };
	uint idleClick[] = { 0, 1, 2, 3 };
	uint drag[] = { 7 };
	uint dragClick[] = { 4, 5, 6, 7 };
	uint loading[] = { 8, 9, 10, 11 };

	anim->Add(LOADING, loading, 4);
	anim->Add(DRAG_CLICK, dragClick, 4);
	anim->Add(DRAG, drag, 1);
	anim->Add(MOUSE_CLICK, idleClick, 4);
	anim->Add(MOUSE_IDLE, idle, 1);

	BBox(new Point(window->MouseX(), window->MouseY()));
}

Mouse::~Mouse()
{
	delete anim;
	delete tileSet;
}

void Mouse::Update()
{
	MoveTo(window->MouseX() + 8, window->MouseY() + 15, Layer::FRONT);
	
	if (window->KeyPress(VK_LBUTTON))
	{
		anim->Select(MOUSE_CLICK);
		OneBitAdventure::audio->Play(AUDIO_CLICK);
	}
	
	anim->NextFrame();
}

void Mouse::Draw()
{
	anim->Draw(x, y, z, 0.4f);
}
