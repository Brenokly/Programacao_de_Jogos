// ONEBITADVENTURE_H

#ifndef ONEBITADVENTURE_H
#define ONEBITADVENTURE_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Resources.h"
#include "Engine.h"
#include "Game.h"
#include "Audio.h"
#include "Mouse.h"

// ------------------------------------------------------------------------------

enum OneBitObjects // Enumeração dos tipos de objetos
{
    PLAYER,
    ENEMY,
    PROP,
    BOX,
    DOOR,
    CHEST,
    COIN,
	CAMPFIRE,
    PILLAR,
    PILLAR2,
    BOSSATACK,
    ITEM,
    MOUSE,
    BOSS,
};

// ------------------------------------------------------------------------------

enum Sounds { MENU, GAME, PORTA, ATAQUE, AUDIO_CLICK, MOEDA, MORTE };

// ------------------------------------------------------------------------------

class Character; // Declaração antecipada da classe Character

class OneBitAdventure : public Game
{
private:
    static Game * level;                // nível atual do jogo

public:
    static Audio * audio;               // sistema de áudio
    static Mouse * mouse;				// mouse do jogo

    void Init();                        // inicializa jogo
    void Update();                      // atualiza lógica do jogo
    void Draw();                        // desenha jogo
    void Finalize();                    // finaliza jogo

    template<class T>
    static void NextLevel()
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

// ------------------------------------------------------------------------------

#endif // ONEBITADVENTURE_H