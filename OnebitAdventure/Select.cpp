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

	if (!OneBitAdventure::audio->isPlaying(MENU)) {
		OneBitAdventure::audio->Play(MENU, true);
	}
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
        // Verifica se já existe um player alocado
        if (OneBitAdventure::player != nullptr) {
            // Libera o player atual antes de criar um novo
            delete OneBitAdventure::player;
            OneBitAdventure::player = nullptr;
        }

        // Cria um novo player baseado na seleção do usuário
        switch (character)
        {
        case WARRIOR:
            OneBitAdventure::player = new Warrior(5, 7);
            break;
        case MAGE:
            // OneBitAdventure::player = new Mage(...); // Lógica para o MAGE
            break;
        case ARCHER:
            // OneBitAdventure::player = new Archer(...); // Lógica para o ARCHER
            break;
        case ROGUE:
            // OneBitAdventure::player = new Rogue(...); // Lógica para o ROGUE
            break;
        default:
            OneBitAdventure::player = new Warrior(5, 7);
            break;
        }

        // Adiciona o novo player à cena e inicia o nível 1
        //OneBitAdventure::scene->Add(OneBitAdventure::player, MOVING);
        OneBitAdventure::audio->Stop(MENU);
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