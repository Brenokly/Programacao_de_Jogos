// ------------------------------------------------------------------------------
// Inclusões

#ifndef SELECT_H
#define SELECT_H

#include "Game.h"
#include "Scene.h"
#include "Sprite.h"
#include "Hud.h"

// ------------------------------------------------------------------------------

enum Characters { WARRIOR, MAGE, ARCHER, ROGUE };

// ------------------------------------------------------------------------------

class Select : public Game
{
private:
	Sprite* backg;				// plano de fundo
	Characters character;		// personagem selecionado
	bool viewBbox = false;

	float lastCardX;			// posição do ultimo card desenhado
	float lastCardY;
	float dist;					// distância entre os cards
	float cardWidth;			// largura do card
	float cardHeight;			// altura do card

public:
	static Scene * scene;		// gerenciador de cena
	static Hud * hud;			// gerenciador do hud do jogo
	static Character * player;	// personagem do jogador

	void Init();                // inicialização
	void Update();              // atualização
	void Draw();                // desenho
	void Finalize();            // finalização
};

// ------------------------------------------------------------------------------

#endif // SELECT_H
