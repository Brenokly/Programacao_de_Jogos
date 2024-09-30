#include "Hud.h"
#include "Select.h"

// ---------------------------------------------------------------------------------

uint  Hud::tileWidth        = 0;
uint  Hud::tileHeight       = 0;
float Hud::mainLeftSide     = 0.0f;
float Hud::mainRightSide    = 0.0f;
float Hud::mainBottomSide   = 0.0f;
float Hud::offset           = 0.0f;

// ---------------------------------------------------------------------------------

Hud::Hud() : player(Select::player)
{
	// Dimensões comuns aos 3 huds
    width = window->Width() / 3.0f;     // Largura da área central
	height = window->Height();          // Altura da área central

    // Descontando as bordas laterais de 5% da largura total
    offset = width * 0.05f;                                 // Exemplo de 5% de borda em cada lado

    // Área útil de movimento, sem contar as bordas
    tileWidth = (width - (2.0f * offset)) / 11.0f;         // Largura e passada horizontal de um tile
    tileHeight = height / 19.0f;  				           // Altura e passada vertical de um tile

    // Imagem do background principal
    mainBackg = new Sprite("Resources/Hud/mapa.png", width, height);

    // Lado esquerdo e direito do background principal
    mainLeftSide = window->CenterX() - 0.5f * mainBackg->Width();
    mainRightSide = window->CenterX() + 0.5f * mainBackg->Width();
    mainBottomSide = window->Height() - 0.5f * tileHeight;       // Posição da primeira linha do background

	// Hud do player com vida, mana, xp, etc
    playerHud = new Sprite("Resources/Hud/hud2.png", width, 2.8f * tileHeight);
    tileSet = new TileSet("Resources/Hud/hud3.png", width, 4.0f * 2.8f * tileHeight,
        width, 2.8f * tileHeight, 1, 4);
    life = new Animation(tileSet, 0.0f, false);

    xpBar = new Sprite("Resources/xpBar.png");

    uint seq1[1] = { 0 };
	uint seq2[1] = { 1 };
	uint seq3[1] = { 2 };
	uint seq4[1] = { 3 };

    life->Add(QUARTER, seq4, 1);
    life->Add(HALF, seq3, 1);
    life->Add(THREE_QUARTERS, seq2, 1);
    life->Add(FULL, seq1, 1);

	// Fonte para exibir texto na tela
    consolas = new Font("Resources/press12.png");
    consolas->Spacing("Resources/press12.dat");
}

// ---------------------------------------------------------------------------------

Hud::~Hud()
{
    delete consolas;
    delete life;
    delete tileSet;
    delete playerHud;
    delete mainBackg;
}

// ---------------------------------------------------------------------------------

void Hud::Update()
{
    // Pega a vida do player e atualiza hud da vida
    float ratio = (float) player->GetLife() / player->GetMaxLife();
    if (ratio >= 0.99f)
        life->Select(FULL);
    else if (ratio >= 0.75f)
        life->Select(THREE_QUARTERS);
    else if (ratio >= 0.5f)
        life->Select(HALF);
    else
        life->Select(QUARTER);
}

// ---------------------------------------------------------------------------------

void Hud::Draw()
{
    mainBackg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
    playerHud->Draw(window->CenterX(), window->Height() - 0.5f * playerHud->Height(), Layer::FRONT);

    // Desenha vida se o player estiver vivo
    if (!((Entity*)player)->IsDead())
        life->Draw(window->CenterX(), window->Height() - 0.5f * playerHud->Height(), Layer::FRONT);

    DrawExperienceBar();
    DrawLevelAndXp();

    // Desenha o texto do indicador de vida
    string lifeTxt = "";
    lifeTxt.append(std::to_string(player->GetLife()));
    lifeTxt.append("/");
    lifeTxt.append(std::to_string(player->GetMaxLife()));

	float positionX = mainLeftSide + offset + 0.25f * tileWidth;
    float positionY = mainBottomSide - 0.8f * tileHeight;

    consolas->Draw(positionX, positionY, lifeTxt, Color(1.0f, 1.0f, 1.0f, 1.0f), 0.001f, 0.7f, 0.0f);
}

// ---------------------------------------------------------------------------------

void Hud::DrawExperienceBar()
{
    // Percentuais para a posição desejada
    float xPercent = 0.53f;  // 53% da largura da tela
    float yPercent = 0.85f;  // 85% da altura do player hud

    // Calcula a porcentagem de xp atual em relação ao máximo
    float percent = (float)player->GetXp() / player->GetMaxXp();

    // Calcula a largura máxima da barra de experiência
    float maxWidth = xPercent * width;
    float currentWidth = maxWidth * percent;

    // Calcula a posição X e Y com base nas dimensões da tela
    float centerX = window->CenterX();                                // Posição x da barra
    float posY = window->Height() - playerHud->Height() * yPercent;   // Posição y da barra

    // Ajusta a posição X para simular a barra expandindo da esquerda
    float adjustedX = centerX - (maxWidth / 2) + (currentWidth / 2); // Corrige o ponto de origem da barra de XP

    // Desenha a barra de experiência do jogador
    xpBar->DrawResize(adjustedX, posY, currentWidth, 5.0f);
}

// ---------------------------------------------------------------------------------

void Hud::DrawLevelAndXp()
{
    // Percentuais para a posição desejada
    float xPercent = 0.475f;	// 47.5% da largura da tela
    float yPercent = 0.886f;	// 88.6% da altura da tela

    // Calcula a posição X e Y com base nas dimensões da tela
    float definirX = window->Width() * xPercent;
    float definirY = window->Height() * yPercent;

    int level = player->GetLevel();
    int xp = player->GetXp();
    int maxXp = player->GetMaxXp();

    consolas->Draw(definirX - (9 + level % 10), definirY - 45, "Nv:" + std::to_string(level), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.2f);
    consolas->Draw(definirX, definirY - 25, std::to_string(xp) + "/" + std::to_string(maxXp), Color(1.0f, 1.0f, 1.0f, 1.0f), Layer::FRONT, 1.0f);
}

// ---------------------------------------------------------------------------------
