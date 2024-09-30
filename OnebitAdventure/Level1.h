// Level1.h

#ifndef LEVEL1_H
#define LEVEL1_H

// ------------------------------------------------------------------------------
// Inclusões

#include "Scene.h"
#include "Hud.h"
#include "Map.h"
#include "Game.h"

// ------------------------------------------------------------------------------

class Character;		// declaração antecipada da classe Character

// ------------------------------------------------------------------------------

class Level1 : public Game
{
private:
	bool viewBox = false;				// controle de visualização de caixas de colisão
	Map * map;							// gerenciador do mapa do jogo

public:
	static Scene * scene;				// gerenciador de cena
	static Hud *& hud;					// gerenciador do hud do jogo
	static Character *& player;			// personagem do jogador

	void Init();						// inicialização
	void Update();						// atualização
	void Draw();						// desenho
	void Finalize();					// finalização
};

// -----------------------------------------------------------------------------

#endif // LEVEL1_H
