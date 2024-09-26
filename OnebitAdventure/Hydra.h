// Hydra.h
// ------------------------------------------------------------------------------
// Inclusões de Arquivos

#include "Boss.h"

// ------------------------------------------------------------------------------

enum HydraAtaques{ ATAQUE1, ATAQUE2,ATAQUE3 };

class Hydra : public Boss
{
protected:
	// atributos específicos do Ghost (Ghost, pelo que vi, não tem muitos atributos diferentes não!
	// A hydra terá 3 tipos de ataques diferentes, cada um com um dano diferente e range diferente
	// Então a minha ideia inicial é criar métodos de ataques e chamar eles no update!

	TileSet* ataque1;													// TileSet da Hydra
	Animation* animAtaque1;												// Animação do ataque

	void InitializeBBox() override;										// Inicializa a caixa de colisão (BBox)
public:
	Hydra(float col, float line);
	~Hydra() override;

	void OnCollision(Object* obj) override;								// resolução da colisão
	void UpdateAnimation() override;									// atualização da animação do Ghost

	// Métodos de Ataque
	void Varredura();
	void Ataque2();
	void Ataque3();

	void Update() override;												// atualização do estado do Boss
	void DrawHealthBar() override;										// Desenha a barra de vida do inimigo 
	void DrawHealthText() override;										// Desenha o texto de vida do inimigo
	void DrawLevel() override;											// Desenha o nível do inimigo
	void DrawName() override;											// Desenha o nome do inimigo 
};