// Boss.h
// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Enemy.h"                      // Interface base para inimigos

// ------------------------------------------------------------------------------

class Boss : public Enemy
{
protected:
	int contadorMovimento;												// Essa variável serve para contar quantos movimentos o player deu!
	virtual void InitializeBBox() override = 0;							// Inicializa a caixa de colisão (BBox)

public:
	Boss();
	virtual ~Boss() = 0;

	void ConstrainToScreen() override;
	virtual void OnCollision(Object* obj) override = 0;					// resolução da colisão
	void UpdateAnimation();												// atualização da animação do Ghost
	virtual void Update() override = 0;									// atualização do estado do Boss
};

// ------------------------------------------------------------------------------