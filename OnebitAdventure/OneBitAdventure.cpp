// ------------------------------------------------------------------------------
// Inclusões

#include "OneBitAdventure.h"
#include "Home.h"

//-------------------------------------------------------------------------------

Game        * OneBitAdventure::level    = nullptr;
Audio       * OneBitAdventure::audio    = nullptr;
Mouse       * OneBitAdventure::mouse    = nullptr;

//-------------------------------------------------------------------------------

void OneBitAdventure::Init()
{
	audio = new Audio();
    audio->Add(MENU, "Resources/Audios/Menu.wav");
    audio->Add(GAME, "Resources/Audios/Game.wav");
	audio->Add(PORTA, "Resources/Audios/Porta.wav", 3);
	audio->Add(ATAQUE, "Resources/Audios/Ataque.wav", 3);
	audio->Add(AUDIO_CLICK, "Resources/Audios/Click.wav", 3);
	audio->Add(MOEDA, "Resources/Audios/Moeda.wav", 3);
	audio->Add(MORTE, "Resources/Audios/Morte.wav");

    audio->Volume(MOEDA, 0.5f);

    mouse = new Mouse();
	level = new Home();
	level->Init();
}

//-------------------------------------------------------------------------------

void OneBitAdventure::Update()
{
    // atualiza nível
    level->Update();

    // atualiza mouse
	mouse->Update();
}

//-------------------------------------------------------------------------------

void OneBitAdventure::Draw()
{
    // desenha nível
    level->Draw();

    // desenha mouse
    mouse->Draw();
}

//-------------------------------------------------------------------------------

void OneBitAdventure::Finalize()
{
    if (level != nullptr) {
        level->Finalize();
        delete level;
        level = nullptr;
    }

    if (mouse != nullptr) {
        delete mouse;
        mouse = nullptr;
    }

    if (audio != nullptr) {
        delete audio;
        audio = nullptr;
    }
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

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