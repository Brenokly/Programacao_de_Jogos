#include "Entity.h"
#include "Level1.h"
#include "Character.h"
#include <cmath>

Entity::Entity()
    : tileSet(nullptr), anim(nullptr), animState(IDLE), animSeq(0), damageTimer(nullptr),
	targetX(x), targetY(y), prevX(x), prevY(y),
    deltaX(0), deltaY(0), newX(0), newY(0), 
    distance(0), limiarDist(0), pullStrength(0), direction(STILL),
    life(0), maxLife(0), attack(0), defense(0), damage(0),
	isHit(false), isDead(false), isMoving(false), isMovingBack(false), level(0), tileHeight(0), tileWidth(0)
{
    width = Level1::hud->tileWidth;
    height = Level1::hud->tileHeight;

    limiar = window->CenterY();

	speed = 400.0f;                 // Velocidade de movimento

    // Raio de distância na qual começa a desaceleração
    slowDownRadius = width * 0.3f;  // Desacelera a 30% da largura do tile

    state = IDLE;                   // Estado inicial
    isAttacked = false;             // Flag para indicar que o personagem está atacando ou não
}

Entity::~Entity()
{
}

void Entity::Move(Direction direction)
{
    if (direction != BACK) this->direction = direction;
    else isMovingBack = true;
    switch (direction)
    {
    case UP:
        prevY = y;
        targetY = y - height;
        break;
    case DOWN:
        prevY = y;
        targetY = y + height;
        break;
    case LEFT:
        prevX = x;
        targetX = x - width;
        break;
    case RIGHT:
        prevX = x;
        targetX = x + width;
        break;
    case BACK:
        targetX = prevX;
        targetY = prevY;
        break;
    default:
        targetX = prevX = x;
        targetY = prevY = y;
        break;
    }

	isHit = true;                   // Flag para indicar que o personagem atacou
	state = WALK;				    // Estado de movimento
}

// O movimento da câmera consiste em aplicar uma força que puxa para baixo todas as entidades,
// dando a ilusão de que o player está subindo
void Entity::CameraMovement()
{
    // Verifica se o player passou do limiar
    if (Level1::player->Y() >= limiar) return;

    // Calcula a distância entre o player e o limiar
    limiarDist = fabs(Level1::player->Y() - limiar);

    // Se o jogador passou do limiar, começa a aplicar a força de gravidade
    if (limiarDist > 0) {
        // A força de puxar aumenta proporcionalmente à distância do limiar
        pullStrength = limiarDist;

        // Aplica essa força para todas as entidades (inclusive o próprio jogador)
        targetY += pullStrength * gameTime;
        prevY += pullStrength * gameTime;
        Translate(0, pullStrength * gameTime);
    }
    else {
        // Se o jogador não está acima do limiar, a força é zero
        pullStrength = 0.0f;
    }
}

void Entity::Movement()
{
    // Calcular a distância até o destino (magnitude)
    distance = sqrt((targetX - x) * (targetX - x) + (targetY - y) * (targetY - y));

    // Se a distância for muito pequena, considere que a entidade chegou ao destino
    if (distance < 0.5f) {
        MoveTo(targetX, targetY, z);
		prevX = targetX;
        prevY = targetY;
        isMoving = isMovingBack = false;
        isAttacked = false;
        state = IDLE;
        animState = IDLE;
        return;
    }

    isMoving = true;
    animState = WALK;
	state = WALK;

    // Calcula a direção (vetor unitário)
    deltaX = (targetX - x) / distance;
    deltaY = (targetY - y) / distance;

    float currentSpeed = speed;  // Velocidade ajustada

    // Calcula a velocidade com base na distância euclidiana
    if (distance < slowDownRadius) currentSpeed *= (distance / slowDownRadius);

    // Ajusta a movimentação com base no delta e na força de retorno
    newX = (deltaX != 0) ? (deltaX / fabs(deltaX)) * currentSpeed * gameTime : 0;
    newY = (deltaY != 0) ? (deltaY / fabs(deltaY)) * currentSpeed * gameTime : 0;

    // Atualizar a posição com base na velocidade
    Translate(newX, newY);
}

void Entity::ConstrainToScreen()
{
    // Verifica o limite direito
    if (x > Level1::hud->mainRightSide - Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite esquerdo
    if (x < Level1::hud->mainLeftSide + Level1::hud->offset) {
        targetX = prevX;
    }

    // Verifica o limite inferior
    if (y > window->Height()) {
        targetY = prevY;
    }
}