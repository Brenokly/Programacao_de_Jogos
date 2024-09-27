// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Select.h"
#include "Warrior.h"
#include "Ghost.h"
#include "OneBitAdventure.h"
#include <cstdlib>
#include <ctime>
#include "Hydra.h"

// ------------------------------------------------------------------------------

Scene     * Level1::scene   = nullptr;
Hud       * Level1::hud     = nullptr;
Map       * Level1::map     = nullptr;
Character * Level1::player  = nullptr;

// ------------------------------------------------------------------------------

void Level1::Init(Characters character)
{
	OneBitAdventure::audio->Play(GAME);

    std::srand(static_cast<unsigned int>(std::time(0)));

    scene = new Scene();
    hud = new Hud();
    //map = new Map(std::rand() % 100);

    switch (character)
    {
    case WARRIOR:
        player = new Warrior(5, 7);
        break;
    case MAGE:
        break;
    case ARCHER:
        break;
    case ROGUE:
        break;
    default:
        player = new Warrior(5, 7);
        break;
    }


    Hydra* hydra = new Hydra(8, 10);

    scene->Add(hud, STATIC);
    scene->Add(player, MOVING);
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