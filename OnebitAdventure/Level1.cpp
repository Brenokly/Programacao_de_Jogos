// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Warrior.h"
#include "Hydra.h"
#include "Select.h"
#include <cstdlib>
#include <ctime>

// ------------------------------------------------------------------------------

Scene     *& Level1::scene   = OneBitAdventure::scene;
Hud       *& Level1::hud     = OneBitAdventure::hud;
Character *& Level1::player  = OneBitAdventure::player;
Map        * Level1::map     = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init()
{
	OneBitAdventure::audio->Play(GAME);

    std::srand(static_cast<unsigned int>(std::time(0)));
    //map = new Map(std::rand() % 100);

    Hydra* hydra = new Hydra(8, 10);

    scene->Add(hud, STATIC);
    scene->Add(hydra, MOVING);
    //scene->Add(new Ghost(8, 10), MOVING);
    //scene->Add(new Ghost(5, 12), MOVING);
    //scene->Add(new Ghost(2, 2), MOVING);
    //scene->Add(new Ghost(1, 7), MOVING);
    //scene->Add(new Ghost(8, 14), MOVING);
    //scene->Add(new Ghost(5, 15), MOVING);
    //scene->Add(new Ghost(2, 12), MOVING);
    //scene->Add(new Ghost(1, 17), MOVING);
}

// ------------------------------------------------------------------------------

void Level1::Update()
{   
    // volta para a tela de inicio
    if (window->KeyPress(VK_ESCAPE))
    {
        OneBitAdventure::NextLevel<Select>();
    }
    else if (window->KeyPress('B'))
    {
        viewBox = !viewBox;
    }
    else
    {
        scene->Update();
        scene->CollisionDetection();
    }
}

// ------------------------------------------------------------------------------

void Level1::Draw()
{
    // desenha cena
    scene->Draw();

    if (viewBox)
        scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Level1::Finalize()
{
    delete scene;
}

// ------------------------------------------------------------------------------