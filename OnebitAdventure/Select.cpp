// ------------------------------------------------------------------------------
// Inclusões

#include "Select.h"
#include "OneBitAdventure.h"
#include "Home.h"
#include "Level1.h"
#include "Warrior.h"
#include "Card.h"

// ------------------------------------------------------------------------------

Scene     * Select::scene   = nullptr;
Hud       * Select::hud     = nullptr;
Character * Select::player  = nullptr;

// ------------------------------------------------------------------------------

void Select::Init()
{
	backg = new Sprite("Resources/selecao.png", window->Width(), window->Height());

    cardWidth = (backg->Width() / 1920.0f) * 360.0f;
    cardHeight = (backg->Height() / 1080.0f) * 495.0f;

    dist = cardWidth + 10.0f;

    scene = new Scene();
    scene->Add(OneBitAdventure::mouse, MOVING);
    scene->Add(new Card(window->CenterX(), window->CenterY(), cardWidth, cardHeight), STATIC);

    // Adiciona 5 cards para teste
    /*for (float x = window->CenterX(); x <= 5.0f * dist; x += dist)
    {
        scene->Add(new Card(x, window->CenterY(), cardWidth, cardHeight), STATIC);
    }*/

    character = WARRIOR;
}

// ------------------------------------------------------------------------------

void Select::Update()
{
    scene->Update();
    scene->CollisionDetection();

    if (window->KeyPress('B'))
        viewBbox = !viewBbox;

    // volta para a tela inicial
    if (window->KeyPress(VK_ESCAPE))
    {
        OneBitAdventure::NextLevel<Home>();
    }

    // passa ao primeiro nível com ENTER
    if (window->KeyPress(VK_RETURN))
    {
        hud = new Hud();

        // Cria um novo player baseado na seleção do usuário
        switch (character)
        {
        case WARRIOR:
            player = new Warrior(5, 7);
            break;
        case MAGE:
            // player = new Mage(...); // Lógica para o MAGE
            break;
        case ARCHER:
            // player = new Archer(...); // Lógica para o ARCHER
            break;
        case ROGUE:
            // player = new Rogue(...); // Lógica para o ROGUE
            break;
        default:
            player = new Warrior(5, 7);
            break;
        }

        // Adiciona o novo player à cena e inicia o nível 1
        OneBitAdventure::audio->Stop(MENU);
        OneBitAdventure::NextLevel<Level1>();
    }
}

// ------------------------------------------------------------------------------

void Select::Draw()
{
	backg->Draw(window->CenterX(), window->CenterY());
    scene->Draw();

	if (viewBbox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Select::Finalize()
{
    scene->Remove(OneBitAdventure::mouse, MOVING);
	delete backg;
    delete scene;
}

// ------------------------------------------------------------------------------