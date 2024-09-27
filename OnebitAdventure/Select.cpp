// ------------------------------------------------------------------------------
// Inclusões

#include "OneBitAdventure.h"
#include "Sprite.h"
#include "Select.h"
#include "Home.h"
#include "Level1.h"

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
