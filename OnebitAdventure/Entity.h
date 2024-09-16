// Entity.h

#ifndef ENTITY_H
#define ENTITY_H

// ----------------------------------------------------------------------------------
// Inclusões

#include "Object.h"
#include "Animation.h"
#include "OneBitAdventure.h"
#include "Timer.h"

enum Direction				// Enumeração das direções de uma movimentação
{
	STILL = 0,				// 00000000
	UP = 1 << 0,			// 00000001
	DOWN = 1 << 1,			// 00000010
	LEFT = 1 << 2,			// 00000100
	RIGHT = 1 << 3,			// 00001000
	BACK = 1 << 4,			// 00010000
};

enum AnimationState			// Enumeração dos estados de animação
{
	IDLE = 1 << 5,			// 00100000
	WALK = 1 << 6,			// 01000000
	ATACK = 1 << 7			// 10000000
};

// ----------------------------------------------------------------------------------

class Entity : public Object
{
protected:
	// TileSet e animação
	TileSet* tileSet;			        // folha de sprites da entidade
	Animation* anim;					// animação da entidade
	AnimationState animState;			// estado atual da animação
	uint animSeq;						// sequência de animação atual
	Timer* damageTimer;					// controla tempo de execução da animação de dano

	// Atributos de dimensão e movimentação
	Direction direction;				// direção do movimento
	float width, height;				// largura e altura
	float speed;						// velocidade de movimento
	float targetX;						// posição x do destino
	float targetY;						// posição y do destino
	float deltaX;						// deslocamento do x até o destino
	float deltaY;						// deslocamento do y até o destino
	float distance;						// distância euclidiana até o destino
	float slowDownRadius;				// raio de desaceleração
	float newX;							// interpolação do deltaX
	float newY;							// interpolação do deltaY
	float prevX;						// posição x anterior
	float prevY;						// posição y anterior
	float limiar;						// posição do limiar
	float limiarDist;					// distância até o limiar
	float pullStrength;					// força de retorno

	bool isHit;							// Flag para indicar se o personagem já atacou
	bool isDead;						// Flag para indicar se o personagem está morto
	bool isMoving;						// verifica se está executando um movimento

	// Atributos de combate
	int level;
	int maxLife;
	int life;
	int attack;
	int defense;
	int damage;

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void OnCollision(Object* obj) = 0;	// resolução da colisão
	virtual void UpdateAnimation() = 0;			// atualização da animação

	// Combina a direção e o estado da animação para retornar uma sequência de animação única
	uint GetAnimSeq(Direction direction, AnimationState animState);

	void Movement();							// realiza a movimentação da entidade
	void CameraMovement();						// realiza a movimentação da câmera
	void ConstrainToScreen();					// limita a movimentação da entidade à tela

public:
	Entity();
	~Entity();

	void Move(Direction direction);						// define a direção do próximo movimento
	void MoveTo(float x, float y, float z) override;	// move a entidade para a posição (x, y, z)
	
	// Métodos Get
	bool IsMoving() const;						// retorna se está executando um movimento
	bool IsHit() const;
	bool IsDead() const;
	float GetTargetX() const;
	float GetTargetY() const;
	float GetPrevX() const;
	float GetPrevY() const;
	int GetLife() const;
	int GetMaxLife() const;
	int GetDamage() const;						// retorna dano recebido
	Direction GetDirection() const;				// retorna a direção atual

	// calcula a distância entre duas entidades
	float Distance(Entity* entity) const;

	// calcula a diferença entre os destinos de duas entidades
	float TargetDistance(Entity* entity) const;

	// calcula a diferença entre as posições anteriores de duas entidades
	float PrevDistance(Entity* entity) const;

	void SetDamage(int damage);					// recebe o dano causado por outra entidade
};

// ----------------------------------------------------------------------------------

inline void Entity::MoveTo(float x, float y, float z)
{
	Object::MoveTo(x, y, z);
	targetX = prevX = x;
	targetY = prevY = y;
}

inline uint Entity::GetAnimSeq(Direction direction, AnimationState animState)
{
	return direction | animState;
}

inline bool Entity::IsHit() const
{
	return isHit;
}

inline bool Entity::IsMoving() const
{
	return isMoving;
}

inline bool Entity::IsDead() const
{
	return isDead;
}

inline float Entity::GetTargetX() const
{
	return targetX;
}

inline float Entity::GetTargetY() const
{
	return targetY;
}

inline float Entity::GetPrevX() const
{
	return prevX;
}

inline float Entity::GetPrevY() const
{
	return prevY;
}

inline int Entity::GetLife() const
{
	return life;
}

inline int Entity::GetMaxLife() const
{
	return maxLife;
}

inline int Entity::GetDamage() const
{
	return damage;
}

inline Direction Entity::GetDirection() const
{
	return direction;
}

inline float Entity::Distance(Entity* entity) const
{
	float deltaX = x - entity->X();
	float deltaY = y - entity->Y();
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

inline float Entity::TargetDistance(Entity* entity) const
{
	float deltaX = targetX - entity->GetTargetX();
	float deltaY = targetY - entity->GetTargetY();
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

inline float Entity::PrevDistance(Entity* entity) const
{
	float deltaX = prevX - entity->GetPrevX();
	float deltaY = prevY - entity->GetPrevY();
	return sqrt(deltaX * deltaX + deltaY * deltaY);
}

inline void Entity::SetDamage(int damage)
{
	this->damage = damage - defense;
	if (this->damage > 0)
		life -= this->damage;

	damageTimer->Reset();
}

// ---------------------------------------------------------------------------------

#endif // ENTITY_H
