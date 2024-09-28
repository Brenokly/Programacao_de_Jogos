// ------------------------------------------------------------------------------
// Inclusões

#include "Select.h"
#include "OneBitAdventure.h"
#include "Home.h"
#include "Level1.h"
#include "Warrior.h"

// ------------------------------------------------------------------------------

void Select::Init()
{
	backg = new Sprite("Resources/TelaEscolha5.png", window->Width(), window->Height());
}

// ------------------------------------------------------------------------------

void Select::Update()
{
	// volta para a tela inicial
	if (window->KeyPress(VK_ESCAPE))
	{
		OneBitAdventure::NextLevel<Home>();
	}

	// passa ao primeiro nível com ENTER
	if (window->KeyPress(VK_RETURN))
	{
		if (OneBitAdventure::player)
		{
			delete OneBitAdventure::player;
		}
		OneBitAdventure::player = new Warrior(5, 7);
		OneBitAdventure::scene->Add(OneBitAdventure::player, MOVING);
		OneBitAdventure::NextLevel<Level1>();
	}
}

// ------------------------------------------------------------------------------

void Select::Draw()
{
	backg->Draw(window->CenterX(), window->CenterY());
}

// ------------------------------------------------------------------------------

void Select::Finalize()
{
	delete backg;
}

// ------------------------------------------------------------------------------
