// ------------------------------------------------------------------------------
// Inclusões

#include "Engine.h"
#include "Resources.h"
#include "Home.h"
#include "OneBitAdventure.h"

//-------------------------------------------------------------------------------

Game* OneBitAdventure::level = nullptr;
Character* OneBitAdventure::player = nullptr;
Audio* OneBitAdventure::audio = nullptr;

//-------------------------------------------------------------------------------

void OneBitAdventure::Init()
{
	audio = new Audio();
    audio->Add(MENU, "Resources/Audios/Menu.wav");
    audio->Add(GAME, "Resources/Audios/Game.wav");
	audio->Add(PORTA, "Resources/Audios/Porta.wav");
	audio->Add(ATAQUE, "Resources/Audios/Ataque.wav");
	audio->Add(CLICK, "Resources/Audios/Click.wav");
	audio->Add(MOEDA, "Resources/Audios/Moeda.wav");

	level = new Home();
	level->Init();
}

//-------------------------------------------------------------------------------

void OneBitAdventure::Update()
{
    // atualiza nível
    level->Update();
}

//-------------------------------------------------------------------------------

void OneBitAdventure::Draw()
{
    // desenha nível
    level->Draw();
}

//-------------------------------------------------------------------------------

void OneBitAdventure::Finalize()
{
    level->Finalize();

    delete player;
    delete audio;
    delete level;
}

// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine* engine = new Engine();

    // configura a janela do jogo
    engine->window->Mode(WINDOWED);
    //engine->window->Size(1366, 768);          // testando uma resolução diferente
    engine->window->Color(25, 25, 25);
    engine->window->Title("OneBit Adventure");
    engine->window->Icon(IDI_ICON);
    engine->window->Cursor(IDC_CURSOR);
    //engine->graphics->VSync(true);

    // inicia o jogo
    int status = engine->Start(new OneBitAdventure());

    delete engine;
    return status;
}

// ------------------------------------------------------------------------------