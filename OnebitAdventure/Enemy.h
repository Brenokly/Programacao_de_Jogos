// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Types.h"                      // Tipos específicos da engine
#include "Entity.h"                     // Interface base para objetos
#include "Font.h"                       // Fonte para exibir texto na tela
#include "OneBitAdventure.h"            // Classe principal do jogo
#include <string>                       // Biblioteca para manipulação de strings

// ------------------------------------------------------------------------------
// Classe Enemy : Representa um inimigo no jogo

class Enemy : public Entity
{
protected:
    // --------------------------------------------------------------------------------------------
    // Atributos de Sprites e Animação

    Sprite* lifeSprite;                                 // Animação para representar a vida do inimigo
    Sprite* hudLife;                                    // Sprite para representar a vida do inimigo

    // --------------------------------------------------------------------------------------------
    // Objetos Auxiliares

    float proximityThreshold;                           // Distância para iniciar a perseguição ao jogador
    Font* press12;					                    // fonte para exibir texto na tela

    // --------------------------------------------------------------------------------------------
    // Atributos Básicos do Inimigo

    string name; 				                        // nome do inimigo apenas para identificar

    // --------------------------------------------------------------------------------------------
    // Métodos Protegidos 

    virtual void InitializeBBox() override;             // Inicializa a caixa de colisão (BBox)
    void MoveRandomly();                                // Move o inimigo aleatoriamente
	void HandleMovement(float moveToPlayer);			// Controla a movimentação do inimigo

public:
    // --------------------------------------------------------------------------------------------
    // Construtor e Destrutor

    Enemy();                                            // Construtor
    virtual ~Enemy() = 0;                               // Destrutor virtual puro

    // --------------------------------------------------------------------------------------------
    // Métodos Virtuais Puras

    virtual void UpdateAnimation() = 0;                 // Atualiza a animação do inimigo

    // --------------------------------------------------------------------------------------------
    // Métodos Principais

    virtual void Update() override;                     // Atualiza o estado e a movimentação do inimigo
    virtual void Draw() override;                       // Desenha o inimigo na tela
	virtual void DrawHealthBar();                       // Desenha a barra de vida do inimigo 
	virtual void DrawHealthText();                      // Desenha o texto de vida do inimigo
	virtual void DrawLevel();                           // Desenha o nível do inimigo
	virtual void DrawName();                            // Desenha o nome do inimigo   
    virtual void DisplayEnemyHealth();                  // Exibe a vida do inimigo na tela
    virtual void MoveTowardsPlayer();                   // Movimenta o inimigo em direção ao jogador
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Enemy::Draw()
{
    // Desenha o sprite do inimigo na cor vermelha por um tempo se tiver recebido dano
    if (damageTimer->Elapsed(0.25f))
        anim->Draw(x, y);
    else
        anim->Draw(x, y, Layer::FRONT, Color(1.0f, 0.0f, 0.0f, 1.0f));
}

// ---------------------------------------------------------------------------------

#endif // ENEMY_H