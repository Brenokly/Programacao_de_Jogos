// ------------------------------------------------------------------------------
// Inclusões

#include "Character.h"
#include "Level1.h"
#include <cmath>

// ------------------------------------------------------------------------------

// Inicializa a BBox para colisão
void Character::InitializeBBox()
{
    BBox(new Rect(
        x - tileSet->TileWidth() / 4.0f,
        y - tileSet->TileHeight() / 4.0f,
        x + tileSet->TileWidth() / 4.0f,
        y + tileSet->TileHeight() / 4.0f));
}

// ---------------------------------------------------------------------------------

// construtor para inicializar os atributos genéricos do jogador
Character::Character() : Entity()
{
    txtTimer = new Timer();
    attackTimer = new Timer();

    press12 = new Font("Resources/press12.png");
    press12->Spacing("Resources/press12.dat");

    progress = 0;
    down = 0;
    isMovingUp = false;
    isMovingDown = false;
    coins = 0;
    level = 1;
    maxXp = 60 + (6 * (level - 1));
    xp = 56;
	criticalChance = 0.1f;
    itMoved = false;
}

// ---------------------------------------------------------------------------------

Character::~Character()
{
    delete press12;
    delete attackTimer;
    delete txtTimer;
}

// ---------------------------------------------------------------------------------

void Character::Update()
{
    HandleInput();              // Define a direção de movimento

    CameraMovement();           // Aplica a movimentação da câmera
    Movement();                 // Executa a movimentação

    // Lógica de contagem do progresso do player
    if (isMovingBack)
    {
        isMovingUp = isMovingDown = false;
    }
    
    if (isMovingUp && !isMoving) {
        if (down > 0) {
            down--;
        }
        else {
            progress++;
        }
        isMovingUp = false;
    }
    else if (isMovingDown && !isMoving)
    {
        down++;
        isMovingDown = false;
    }

    UpdateAnimation();

	ConstrainToScreen();        // Limita o personagem à tela

    if (xp >= maxXp) {
        level++;							// Aumenta o nível do jogador
        xp = 0;								// Reseta a experiência do jogador
        maxXp = 60 + (6 * (level - 1));		// Aumenta a experiência máxima do jogador

        maxLife = 52 + (10 * (level - 1));
        life = maxLife;
    }

	// Atualiza estado de vida do jogador
    if (life <= 0)
    {
        OneBitAdventure::audio->Stop(GAME);
        OneBitAdventure::audio->Play(MORTE);
        // Cria o TileSet de morte
        tileSet = new TileSet("Resources/morte.png", width, height, width, height, 1, 1);
        anim = new Animation(tileSet, 0.0f, false); 		   //
        isDead = true;										   // foi de base

        press12->Draw(window->CenterX() - 50.0f, window->CenterY(), "Game Over", Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.2f);
    }
}

// ---------------------------------------------------------------------------------

void Character::HandleInput()
{
    // Ignora a movimentação se estiver morto ou já estiver se movendo
    if (isDead || isMoving) {
        itMoved = false;
        return;
    }

    if ((window->KeyDown('W') || window->KeyDown(VK_UP))) {
        Move(UP);
        isMovingUp = true;
    }
    else if ((window->KeyDown('S') || window->KeyDown(VK_DOWN))) {
        Move(DOWN);
        isMovingDown = true;
    }
    else if ((window->KeyDown('A') || window->KeyDown(VK_LEFT))) {
        Move(LEFT);
    }
    else if ((window->KeyDown('D') || window->KeyDown(VK_RIGHT))) {
        Move(RIGHT);
    }
}

// ---------------------------------------------------------------------------------

void Character::Draw()
{
    // Desenha o progresso
    press12->Draw(window->CenterX() - 10.0f, 20.0f, std::to_string(progress));

    // Desenha o sprite do player na cor vermelha por um tempo se tiver recebido dano
    if (damageTimer->Elapsed(0.25f)) {
        anim->Draw(x, y);
    }
    else {
        anim->Draw(x, y, Layer::FRONT, Color(1.0f, 0.0f, 0.0f, 1.0f));
    }

    DrawTextGet();
}

// ---------------------------------------------------------------------------------

void Character::DrawTextGet()
{
    if (!text.empty() && !txtTimer->Elapsed(0.7f)) {
        int i = 40;
        for (auto& it : text) {
            press12->Draw(x, y - i, it.first, it.second, Layer::FRONT, 1.0f);
            i += 40;
        }
    }
    else {
        text.clear();
    }
}

// ---------------------------------------------------------------------------------
