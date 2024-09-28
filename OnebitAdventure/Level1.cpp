// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Warrior.h"
#include "Hydra.h"
#include "Select.h"
#include <cstdlib>
#include <ctime>
#include "Ghost.h"

// ------------------------------------------------------------------------------

Scene     *  Level1::scene   = nullptr;
Hud       *& Level1::hud     = OneBitAdventure::hud;
Map        * Level1::map     = nullptr;
Character *& Level1::player  = OneBitAdventure::player;

// ------------------------------------------------------------------------------

void Level1::Init()
{
	OneBitAdventure::audio->Play(GAME, true);                                       // inicia música de fundo

	scene = new Scene();                                                            // cria nova cena

    std::srand(static_cast<unsigned int>(std::time(0)));
    //map = new Map(std::rand() % 100);

    Hydra* hydra = new Hydra(8, 10);

    scene->Add(hud, STATIC);
    scene->Add(hydra, MOVING);
	scene->Add(OneBitAdventure::player, MOVING);
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
        OneBitAdventure::audio->Stop(GAME);
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
    scene->Remove(OneBitAdventure::player, MOVING);
	scene->Remove(hud, STATIC);
    delete scene;
}

// ------------------------------------------------------------------------------