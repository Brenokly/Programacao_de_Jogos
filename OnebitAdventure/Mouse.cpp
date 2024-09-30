// Mouse.cpp

#include "Mouse.h"
#include "OneBitAdventure.h"

Mouse::Mouse()
{
	type = MOUSE;

	tileSet = new TileSet("Resources/Cursor.png", 3, 4);
	anim = new Animation(tileSet, 0.08f, false);
	click = false;
	hover = false;
	isLoading = false;

	uint idle[]		 = { 3 };
	uint idleClick[] = { 0, 1, 2 };
	uint drag[]		 = { 7 };
	uint dragClick[] = { 4, 5, 6 };
	uint loading[]	 = { 8, 9, 10, 11 };

	anim->Add(LOADING, loading, 4);
	anim->Add(DRAG_CLICK, dragClick, 3);
	anim->Add(DRAG, drag, 1);
	anim->Add(MOUSE_CLICK, idleClick, 3);
	anim->Add(MOUSE_IDLE, idle, 1);

	MoveTo();
	BBox(new Point(x, y));
}

Mouse::~Mouse()
{
	delete anim;
	delete tileSet;
}

void Mouse::Update()
{
	MoveTo();
	
	if (window->KeyPress(VK_LBUTTON))
	{
		click = true;

		if (!hover)
		{
			anim->Select(MOUSE_CLICK, true);
		}

		OneBitAdventure::audio->Play(AUDIO_CLICK);
	}
	
	if (hover)
	{
		if (click)
		{
			anim->Select(DRAG_CLICK, true);
		}
		else
		{
			anim->Select(DRAG, true);
		}
	}
	else if (isLoading)
	{
		anim->Select(LOADING);
	}

	if (anim->Inactive())
	{
		click = hover = false;
		anim->Select(MOUSE_IDLE);
	}
	
	anim->NextFrame();
}

void Mouse::Draw()
{
	anim->Draw(x, y, z, 0.4f);
}

void Mouse::OnCollision(Object* obj)
{
	
}

// ------------------------------------------------------------------------------
