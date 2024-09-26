// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Types.h"                      // Tipos específicos da engine
#include "Entity.h"                     // Interface base para objetos
#include "Animation.h"                  // Animações de sprites
#include "Font.h"                       // Fonte para exibir texto na tela
#include "TileSet.h"                    // Folha de sprite
#include "Level1.h"
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

    virtual void InitializeBBox();                      // Inicializa a caixa de colisão (BBox)
    void MoveRandomly();                                // Move o inimigo aleatoriamente
	void HandleMovement(float moveToPlayer);			// Controla a movimentação do inimigo

public:
    // --------------------------------------------------------------------------------------------
    // Construtor e Destrutor

    Enemy();                                            // Construtor
    virtual ~Enemy() = 0;                               // Destrutor virtual puro

    // --------------------------------------------------------------------------------------------
    // Métodos Virtuais Puras

    virtual void OnCollision(Object* obj) = 0;          // Resolução de colisão com outros objetos
    virtual void UpdateAnimation() = 0;                 // Atualiza a animação do inimigo

    // --------------------------------------------------------------------------------------------
    // Métodos de Movimentação e Animação

    void MoveTowardsPlayer();                           // Movimenta o inimigo em direção ao jogador

    // --------------------------------------------------------------------------------------------
    // Métodos Principais

    void Update();                                      // Atualiza o estado e a movimentação do inimigo
    virtual void Draw();                                // Desenha o inimigo na tela
	virtual void DrawHealthBar();                       // Desenha a barra de vida do inimigo 
	virtual void DrawHealthText();                      // Desenha o texto de vida do inimigo
	virtual void DrawLevel();                           // Desenha o nível do inimigo
	virtual void DrawName();                            // Desenha o nome do inimigo   
    void DisplayEnemyHealth();                          // Exibe a vida do inimigo na tela
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Enemy::Draw()
{
    // Desenha o sprite do inimigo na cor vermelha por um tempo se tiver recebido dano
    if (damageTimer->Elapsed(0.25f))
        anim->Draw(x, y, z);
    else
        anim->Draw(x, y, z, Color(1.0f, 0.0f, 0.0f, 1.0f));
}

// ---------------------------------------------------------------------------------

#endif // ENEMY_H