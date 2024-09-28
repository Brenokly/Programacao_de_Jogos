// Boss.cpp
// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Boss.h"
#include "Level1.h"

// ------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Boss::InitializeBBox()
{
    // Inicializa a BBox
    BBox(new Rect(
        x - tileSet->TileWidth() / 2,
        y - tileSet->TileHeight() / 2,
        x + tileSet->TileWidth() / 2,
        y + tileSet->TileHeight() / 2)
    );
}

// ------------------------------------------------------------------------------

Boss::Boss() : Enemy() // Chamada do construtor da classe base
{
    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de dimensão e tile set


    // --------------------------------------------------------------------------------------------
    // Inicializa o temporizador de dano e as sequências de animação


    // --------------------------------------------------------------------------------------------
    // Inicializa variáveis de status do boss Hydra (nível, vida e ataque)


    // --------------------------------------------------------------------------------------------
    // Inicializa bounding box e posição dos Bosses


	// --------------------------------------------------------------------------------------------
	// Variáveis auxiliares

	contadorMovimento = 0; // Inicializa o contador de movimento
}

// ------------------------------------------------------------------------------

Boss::~Boss()
{
}

// ------------------------------------------------------------------------------

void Boss::ConstrainToScreen()
{
    // Verifica o limite direito
    if (x + tileSet->TileWidth() / 2.0f > Level1::hud->mainRightSide - Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite esquerdo
    if (x - tileSet->TileWidth() / 2.0f < Level1::hud->mainLeftSide + Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite inferior
    if (y - tileSet->TileHeight() > window->Height()) {
        targetY = prevY;
    }
}

// ------------------------------------------------------------------------------

void Boss::UpdateAnimation()
{
    anim->Select(animState);
    anim->NextFrame();
}

// ------------------------------------------------------------------------------
