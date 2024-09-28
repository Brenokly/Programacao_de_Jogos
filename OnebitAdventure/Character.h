// Character.h

#ifndef CHARACTER_H
#define CHARACTER_H

// ------------------------------------------------------------------------------

#include "OneBitAdventure.h"
#include "Object.h"
#include "Entity.h"
#include "Types.h"
#include "Font.h"
#include <string>
#include <unordered_map>

// ------------------------------------------------------------------------------
// Classe Character : É a classe base para todos os personagens (classes) do jogo

class Character : public Entity
{
protected:
	// Objetos auxiliares para construções de lógicas
	Timer* txtTimer;						// timer para controlar o tempo de exibição do texto
	Timer* attackTimer;						// timer para controlar o tempo de ataque do jogador
	Font* press12;							// fonte para exibir texto na tela

	// Atributos básicos de todo jogador
	int progress;						// quantos tiles andou
	int coins;							// moedas capturadas
	int level;							// nível do jogador
	int xp;								// experiência do jogador
	int maxXp;							// experiência máxima do jogador
	float criticalChance;				// chance de dano crítico

	// --------------------------------------------------------------------------------------------
	// Métodos protegidos 

	void Update() override;							// atualização
	void Draw() override;							// desenho
	void InitializeBBox() override;					// inicializa a BBox

	// Métodos de movimentação e animação
	void HandleInput();										// movimentação do jogador
	void DrawTextGet();										// desenha o texto na tela

public:
	Character();											// construtor
	virtual ~Character();									// destrutor

	std::unordered_map<string, Color> text; // unordered_map para armazenar o texto a ser exibido na tela

	// Métodos de recuperação e modificação de atributos
	int GetLevel() const;
	int GetMaxXp() const;
	int GetXp() const;
	void SetXp(int xp);										// define a experiência do jogador
};

// --------------------------------------------------------------------------------------------------
// Métodos Inline

inline int Character::GetLevel() const
{
	return level;
}

inline int Character::GetMaxXp() const
{
	return maxXp;
}

inline int Character::GetXp() const
{
	return xp;
}

inline void Character::SetXp(int xp)
{
	this->xp += xp;
}

// -----------------------------------------------------------------------------

#endif // CHARACTER_H
