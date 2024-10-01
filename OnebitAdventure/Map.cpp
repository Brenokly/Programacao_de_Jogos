// ------------------------------------------------------------------------------
// Inclusões

#include "Map.h"
#include "Level1.h"
#include "Ghost.h"
#include "Prop.h"
#include "Types.h"
#include "Hydra.h"
#include "CellularAutomaton.h"
#include <algorithm>

// ------------------------------------------------------------------------------

array<Image*, Map::propsLength> Map::images;
vector<Map::Biome> Map::biomes(4);
Map::intMatrix Map::firstChunk;

// ------------------------------------------------------------------------------

void Map::InitializeImages()
{
    images[0] = new Image("Resources/Props/box.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[1] = new Image("Resources/Props/campfireanim.png", Level1::hud->tileWidth * 2, Level1::hud->tileHeight);
    images[2] = new Image("Resources/Props/chest.png", Level1::hud->tileWidth * 2, Level1::hud->tileHeight);
    images[3] = new Image("Resources/Props/coin.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[4] = new Image("Resources/Props/door.png", Level1::hud->tileWidth * 2, Level1::hud->tileHeight);
    images[5] = new Image("Resources/Props/fence.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[6] = new Image("Resources/Props/fenceRotten.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[7] = new Image("Resources/Props/grass.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[8] = new Image("Resources/Props/grass2.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[9] = new Image("Resources/Props/pilar.png", Level1::hud->tileWidth, Level1::hud->tileHeight * 3);
    images[10] = new Image("Resources/Props/pilar2.png", Level1::hud->tileWidth, Level1::hud->tileHeight * 3);
    images[11] = new Image("Resources/Props/rock.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[12] = new Image("Resources/Props/tree.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[13] = new Image("Resources/Props/tree2.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
    images[14] = new Image("Resources/Props/wall.png", Level1::hud->tileWidth, Level1::hud->tileHeight);
}

void Map::InitializeBiomes() {
    // Inicializa o bioma FIELD
    Biome field{};
    field.weights = {
        0.01f,  // box
        0.0f,  // campfire
        0.01f,  // chest
        0.05f,  // coin
        0.0f,  // door
        0.025f, // fence
        0.025f, // fenceRotten
        0.175f, // grass
        0.087f, // grass2
        0.0f,  // pilar
        0.0f,  // pilar2
        0.03f, // rock
        0.01f,  // tree
        0.01f, // tree2
        0.0f,  // wall
        0.5f,  // espaço vazio
        0.086f, // ghost
    };
    field.BuildRoulette();
    biomes[0] = field;

    // Inicializa o bioma FOREST
    Biome forest{};
    forest.weights = {
        0.0f,  // box
        0.0f,  // campfire
        0.0f,  // chest
        0.05f, // coin
        0.0f,  // door
        0.0f,  // fence
        0.0f,  // fenceRotten
        0.1f,  // grass
        0.1f,  // grass2
        0.0f,  // pilar
        0.0f,  // pilar2
        0.0f,  // rock
        0.1f,  // tree
        0.1f,  // tree2
        0.0f,  // wall
        0.5f, // espaço vazio
        0.066f  // ghost
    };
    forest.BuildRoulette();
    biomes[1] = forest;

    // Inicializa o bioma RUIN
    Biome ruin{};
    ruin.weights = {
        0.0f,  // box
        0.0f,  // campfire
        0.01f, // chest
        0.05f,  // coin
        0.01f, // door
        0.0f,  // fence
        0.0f,  // fenceRotten
        0.015f,  // grass
        0.015f,  // grass2
        0.015f, // pilar
        0.015f, // pilar2
        0.15f,  // rock
        0.0f,  // tree
        0.0f,  // tree2
        0.01f, // wall
        0.35f,  // espaço vazio
        0.06f   // ghost
    };
    ruin.BuildRoulette();
    biomes[2] = ruin;

    // Inicializa o bioma BOSS
    Biome boss{};
    boss.weights = {
        0.0f,  // box
        0.0f,  // campfire
        0.0f, // chest
        0.0f,  // coin
        0.0f, // door
        0.0f,  // fence
        0.0f,  // fenceRotten
        0.15f,  // grass
        0.15f,  // grass2
        0.0f, // pilar
        0.0f, // pilar2
        0.15f,  // rock
        0.0f,  // tree
        0.0f,  // tree2
        0.0f, // wall
        0.45f,  // espaço vazio
        0.0f   // ghost
    };
    boss.BuildRoulette();
    biomes[3] = boss;
}

void Map::InitializeFirstChunk()
{
    firstChunk = intMatrix(chunkSize, vector<uint>(11, 15));

    firstChunk.at(2).at(0) = TREE;
    firstChunk.at(2).at(1) = TREE;
    firstChunk.at(2).at(2) = GRASS2;
    firstChunk.at(2).at(3) = GRASS;
    firstChunk.at(2).at(6) = GRASS2;
    firstChunk.at(2).at(8) = TREE;
    firstChunk.at(2).at(9) = TREE;
    firstChunk.at(2).at(10) = TREE;

    firstChunk.at(3).at(0) = TREE;
    firstChunk.at(3).at(1) = TREE;
    firstChunk.at(3).at(2) = WALL;
    firstChunk.at(3).at(3) = WALL;
    firstChunk.at(3).at(4) = WALL;
    firstChunk.at(3).at(5) = WALL;
    firstChunk.at(3).at(6) = WALL;
    firstChunk.at(3).at(7) = WALL;
    firstChunk.at(3).at(8) = WALL;
    firstChunk.at(3).at(9) = TREE;
    firstChunk.at(3).at(10) = TREE;

    firstChunk.at(4).at(0) = GRASS;
    firstChunk.at(4).at(1) = PILAR;
    firstChunk.at(4).at(8) = GRASS;
    firstChunk.at(4).at(9) = TREE;
    firstChunk.at(4).at(10) = TREE;

    firstChunk.at(5).at(0) = TREE2;
    firstChunk.at(5).at(5) = GRASS;

    firstChunk.at(6).at(0) = TREE2;
    firstChunk.at(6).at(1) = GRASS2;

    firstChunk.at(7).at(0) = TREE;
    firstChunk.at(7).at(1) = TREE;
    firstChunk.at(7).at(5) = CAMPFIRE;
    firstChunk.at(7).at(8) = WALL;
    firstChunk.at(7).at(9) = WALL;
    firstChunk.at(7).at(10) = PILAR2;

    firstChunk.at(8).at(2) = GRASS2;

    firstChunk.at(9).at(0) = TREE;
    firstChunk.at(9).at(1) = TREE;
    firstChunk.at(9).at(2) = TREE;
    firstChunk.at(9).at(8) = ROCK;
    firstChunk.at(9).at(9) = ROCK;

    firstChunk.at(10).at(0) = TREE;
    firstChunk.at(10).at(1) = TREE2;
    firstChunk.at(10).at(2) = GRASS2;
    firstChunk.at(10).at(9) = TREE;
    firstChunk.at(10).at(10) = ROCK;
}

uint Map::SpinRoulette(const vector<PropInterval>& roulette)
{
    doubleDistribution dist(0.0, 1.0);
	float r = dist(rng);  // Gera um número aleatório entre 0 e 1

    for (const auto& prop : roulette) {
        if (r >= prop.start && r < prop.end) {
            return prop.type;   // Retorna o prop selecionado
        }
    }

	return 15;  // Retorna espaço vazio
}

Map::intMatrix Map::GenerateBiome(int biome)
{
	// Seleciona um bioma aleatório
	int idx = biome < 4 ? biome : intDistribution(0, 3)(rng);
    intMatrix chunk;

    // Se o bioma selecionado for FOREST, gera o bioma totalmente aleatorio
    if (idx == 1)
    {
        chunk = intMatrix(chunkSize, vector<uint>(11, 15));  // Cria uma matriz vazia

        // Gera a matriz de props do chunk
        for (size_t i = 0; i < chunk.size(); ++i)
        {
            for (size_t j = 0; j < chunk.at(i).size(); j++)
            {
                // Gira a roleta e seleciona um prop
                chunk.at(i).at(j) = SpinRoulette(biomes.at(idx).roulette);
            }
        }
    }
    else
    {
        // Caso contrário, usa um automato celular para gerar as estruturas
		CellularAutomaton automaton(11, chunkSize, 0.9f); // Cria um automato celular
		automaton.Run(5);						   // Executa o automato por 5 gerações
        chunk = automaton.GetMap();				   // Pega a matriz gerada pelo automato

		// Converte 1's em props aleatórios e 0's em espaço vazio
		for (size_t i = 0; i < chunk.size(); ++i)
		{
			for (size_t j = 0; j < chunk.at(i).size(); j++)
			{
                if (chunk.at(i).at(j) == 1)
                {
                    // Gira a roleta e seleciona um prop
                    chunk.at(i).at(j) = SpinRoulette(biomes.at(idx).roulette);
                }
                else
                {
					chunk.at(i).at(j) = 15;  // Espaço vazio
                }
			}
		}

		GenerateStructuresRuin(chunk);      	   // Gera as estruturas do bioma RUIN
    }

    return chunk;
}

// ------------------------------------------------------------------------------

Map::Map(uint seed) : rng(seed)
{
    // Inicializa as propriedades do mapa
	lastPos = Hud::Line(0);         // Posição inicial na primeira linha

    InitializeImages();
    InitializeBiomes();
	InitializeFirstChunk();

    // Gera os chunks do mapa
    // Primeiro chunk é sempre igual
    Generate(firstChunk);
    lastPos = Hud::Line(11);		// Atualiza a última posição

    // Gera os demais chunks do mapa
    for (int i = 0; i < 20; ++i) {
        Generate(GenerateBiome());
    }

    // Gera o boss hydra no final do mapa
    Hydra* hydra = new Hydra(5, 0);                     // Posiciona a hydra na coluna 5
    hydra->MoveTo(hydra->X(), lastPos - 2.0f * hydra->GetHeight(), Layer::MIDDLE); // Ajusta a posição y para que fique no final do mapa
	Level1::scene->Add(hydra, MOVING);				    // Adiciona a hydra na cena
    
    // Gera cenário do boss
    Generate(GenerateBiome(3));
    intMatrix mat = intMatrix(chunkSize, vector<uint>(11, 15));
    mat.at(0).at(0) = WALL;
    mat.at(0).at(1) = WALL;
    mat.at(0).at(2) = WALL;
    mat.at(0).at(3) = WALL;
    mat.at(0).at(4) = WALL;
    mat.at(0).at(5) = WALL;
    mat.at(0).at(6) = WALL;
    mat.at(0).at(7) = WALL;
    mat.at(0).at(8) = WALL;
    mat.at(0).at(9) = WALL;
    mat.at(0).at(10) = WALL;
    Generate(mat);
}

// ------------------------------------------------------------------------------

Map::~Map()
{
    for (Image* img : images) { 
        delete img;
    }
}

void Map::Update()
{
	// Atualiza o mapa
    // Se o player passar de uma certa posição, gera um novo chunk
	if (Level1::player->Y() + lastPos * -1 < 22.0f * Level1::player->GetHeight()) {
        OneBitAdventure::audio->Play(MENU);
	}
}

// ------------------------------------------------------------------------------

void Map::Generate(const intMatrix& chunk)
{
    // Gera um chunk, percorrendo cada linha e coluna da matriz gerando os props e inimigos
    for (int y = 0; y < chunk.size(); ++y) 
    {
        for (int x = 0; x < chunk.at(y).size(); ++x) 
        {
			uint idx = chunk.at(y).at(x);	    // Seleciona um prop/inimigo do chunk
			if (idx == 15) continue;		    // Se for espaço vazio, pula para o próximo
            
            // Gera um ghost
            if (idx == 16)
            {
                if (lastPos > -500.0f && lastPos < 0.0f)
                {
                    Ghost* ghost = new Ghost(x, -lastPos);
                    ghost->MoveTo(ghost->X(), lastPos, Layer::MIDDLE);
                    Level1::scene->Add(ghost, MOVING);
                }
                continue;
            }
            
            // Carrega as informações do prop selecionado
			Image * img = images[idx];			        // Imagem do prop
            uint type;
            switch (idx)
            {
            case 0: type = OneBitObjects::BOX; break;
            case 1: type = OneBitObjects::CAMPFIRE; break;
            case 2: type = OneBitObjects::CHEST; break;
            case 3: type = OneBitObjects::COIN; break;
            case 4: type = OneBitObjects::DOOR; break;
            case 9: case 10: type = OneBitObjects::PILLAR; break;
            default: type = PROP;
            }

            float col = Level1::hud->Col(x);                // Coluna do prop
            float line = lastPos;                           // Linha continua da última posição

			bool interactable = type != PROP;               // Tipo prop não é interagível
            bool bbox = idx != 7 && idx != 8 && idx != 11;  // Gramas e pedras não possuem bbox

            // Adiciona o prop gerado na cena
            Level1::scene->Add(new Prop(type, img, col, line, interactable, bbox), STATIC);
        }
        lastPos -= Level1::hud->tileHeight;     // Passa para a próxima linha
    }
}

void Map::GenerateStructuresField(intMatrix& chunk)
{
}

void Map::GenerateStructuresForest(intMatrix& chunk)
{
}

void Map::GenerateStructuresRuin(intMatrix& chunk) {
    // Função lambda que retorna o minimo
	auto minLambda = [](int a, int b) {
		return (a < b) ? a : b;
    };

    // Função lambda que retorna o maximo
    auto maxLambda = [](int a, int b) {
        return (a > b) ? a : b;
    };

    for (int y = 0; y < chunk.size(); ++y) {
        for (int x = 0; x < chunk.at(y).size(); ++x) {
            // Verifica se o prop atual é uma porta
            if (chunk.at(y).at(x) == DOOR) {
                // Se a porta estiver em um canto, apaga ela e coloca uma parede
                if (x == 0 || x == 10 || y == 0 || y == 21) {
                    chunk.at(y).at(x) = WALL;
                    continue;
                }

                // Limpa o caminho acima e abaixo da porta
                if (y > 0 && chunk.at(y - 1).at(x) != DOOR) {
                    chunk.at(y - 1).at(x) = EMPTY;  // Limpa acima
                }
                if (y < chunk.size() - 1 && chunk.at(y + 1).at(x) != DOOR) {
                    chunk.at(y + 1).at(x) = EMPTY;  // Limpa abaixo
                }

                int currentX = x;
                int currentY = y;

                // Gera paredes à esquerda da porta
                int leftWallCount = minLambda(rand() % 4 + 1, x); // Gera entre 1 e 4 paredes
                int leftCount = leftWallCount;
                while (leftWallCount > 0) {
                    chunk.at(currentY).at(--currentX) = WALL;
                    leftWallCount--;
                }

                // Gera paredes para cima a partir da última parede gerada
                int topWallCount = rand() % 5 + 2;  // Gera entre 2 e 6 paredes para cima
				topWallCount = minLambda(topWallCount, currentY);  // Garante que não ultrapasse o limite superior
                while (topWallCount > 0) {
                    chunk.at(--currentY).at(currentX) = WALL;
                    topWallCount--;
                }

                // Gera paredes à direita a partir da última parede gerada
                int rightWallCount = maxLambda(leftCount + 1, rand() % (10 - currentX) + 1); // Garante pelo menos leftCount + 1 paredes
                bool porta = false;

                while (rightWallCount > 0) {
                    // Se ainda não gerou uma porta na parte de cima, gera uma chance de 25%
                    if (!porta) {
                        int random = rand() % 4; // 25% de chance de gerar uma porta
                        if (random == 0) { // Gera a porta
                            chunk.at(currentY).at(++currentX) = DOOR; // Adiciona a porta
                            porta = true;

                            // Após gerar a porta da parte superior da estrutura, garante que a parte superior e inferior da porta esteja vazia
                            if (currentY > 0) {
                                chunk.at(currentY - 1).at(currentX) = EMPTY; // Limpa acima da porta
                            }
                            if (currentY < chunk.size() - 1) {
                                chunk.at(currentY + 1).at(currentX) = EMPTY; // Limpa abaixo da porta
                            }
                        }
                        else {
                            chunk.at(currentY).at(++currentX) = WALL; // Adiciona uma parede
                        }
                    }
                    else {
                        // Se a porta já foi gerada, apenas adiciona paredes à direita
                        chunk.at(currentY).at(++currentX) = WALL; // Gera parede
                    }
                    rightWallCount--; // Decrementa o contador
                }

                // Gera paredes para baixo a partir da última parede gerada
                while (currentY > y) {
                    chunk.at(--currentY).at(currentX) = WALL;
                }

                // Volta para a esquerda a partir da última parede gerada para se conectar com a porta
                while (currentX - 1 != x) {
                    chunk.at(currentY).at(--currentX) = WALL;
                }

                // Preenche com moedas e baús aleatoriamente dentro da estrutura
                //int coinCount = 5;  // Número de moedas
                //for (int i = 0; i < coinCount; ++i) {
                //    int randX = x + (rand() % (rightWallCount + 1)) - (rand() % (leftWallCount + 1));  // Posição aleatória horizontal
                //    int randY = y + (rand() % (bottomWallCount + 1)) - (rand() % (topWallCount + 1));   // Posição aleatória vertical

                //    // Verifica os limites antes de colocar uma moeda
                //    if (randX >= 0 && randY >= 0 && randX < chunk.at(y).size() && randY < chunk.size()) {
                //        if (chunk.at(randY).at(randX) == EMPTY) {  // Se for espaço vazio
                //            chunk.at(randY).at(randX) = COIN;  // Coloca uma moeda
                //        }
                //    }
                //}

                // Adiciona um baú em uma posição aleatória dentro da estrutura
                //int chestPosX = x + (rand() % (rightWallCount + 1)) - (rand() % (leftWallCount + 1));
                //int chestPosY = y + (rand() % (bottomWallCount + 1)) - (rand() % (topWallCount + 1));

                //if (chestPosX >= 0 && chestPosY >= 0 && chestPosX < chunk.at(y).size() && chestPosY < chunk.size()) {
                //    if (chunk.at(chestPosY).at(chestPosX) == EMPTY) {  // Se for espaço vazio
                //        chunk.at(chestPosY).at(chestPosX) = CHEST;  // Coloca um baú
                //    }
                //}
            }
        }
    }
}

// ------------------------------------------------------------------------------
