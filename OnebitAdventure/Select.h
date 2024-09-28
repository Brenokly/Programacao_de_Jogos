// ------------------------------------------------------------------------------
// Inclusões

#ifndef SELECT_H
#define SELECT_H

#include "Game.h"
#include "Sprite.h"
#include "Character.h"

// ------------------------------------------------------------------------------

enum Characters { WARRIOR, MAGE, ARCHER, ROGUE };

// ------------------------------------------------------------------------------

class Select : public Game
{
private:
	Sprite* backg;				// plano de fundo
	Characters character;		// personagem selecionado
	Character* player;			// personagem do jogador

public:

	void Init();                // inicialização
	void Update();              // atualização
	void Draw();                // desenho
	void Finalize();            // finalização
};

// ------------------------------------------------------------------------------

#endif // SELECT_H
