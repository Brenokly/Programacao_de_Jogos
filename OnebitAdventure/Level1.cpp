// ------------------------------------------------------------------------------
// Inclusões

#include "Level1.h"
#include "Character.h"
#include "Warrior.h"
#include "Hydra.h"
#include "Select.h"
#include <cstdlib>
#include <ctime>
#include "Ghost.h"
#include "Map.h"

// ------------------------------------------------------------------------------

Scene       *  Level1::scene    = nullptr;
Hud         *& Level1::hud      = Select::hud;
Character   *& Level1::player   = Select::player;

// ------------------------------------------------------------------------------

void Level1::Init()
{
    this->hud = hud;													// inicializa o hud
	this->player = player;											    // inicializa o player

	OneBitAdventure::audio->Play(GAME, true);                           // inicia música de fundo
	
    scene = new Scene();								                // cria nova cena
    scene->Add(hud, STATIC);
    scene->Add(player, MOVING);
    
	std::srand(static_cast<unsigned int>(std::time(0)));				// semente para números aleatórios
	map = new Map(std::rand());								            // cria um novo mapa aleatório
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
        scene->CollisionDetection();
        scene->Update();

        map->Update();
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
    delete map;
}

// ------------------------------------------------------------------------------