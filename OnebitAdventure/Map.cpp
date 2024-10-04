// ------------------------------------------------------------------------------
// Inclusões

#include "Map.h"
#include "Level1.h"
#include "Ghost.h"
#include "Prop.h"
#include "Types.h"
#include "Hydra.h"
#include <algorithm>

// ------------------------------------------------------------------------------

array<Image*, Map::propsLength> Map::images;
vector<Map::Biome> Map::biomes(4);
Map::intMatrix Map::firstChunk;

// ------------------------------------------------------------------------------

// Função lambda que retorna o minimo
auto minLambda = [](int a, int b) {
    return (a < b) ? a : b;
};

// Função lambda que retorna o maximo
auto maxLambda = [](int a, int b) {
    return (a > b) ? a : b;
};

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
        0.01f, // fence
        0.01f, // fenceRotten
        0.175f, // grass
        0.087f, // grass2
        0.0f,  // pilar
        0.0f,  // pilar2
        0.03f, // rock
        0.01f,  // tree
        0.01f, // tree2
        0.0f,  // wall
        0.5f,  // espaço vazio
        0.03f, // ghost
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
        0.25f,  // tree
        0.25f,  // tree2
        0.0f,  // wall
        0.35f, // espaço vazio
        0.03f  // ghost
    };
    forest.BuildRoulette();
    biomes[1] = forest;

    // Inicializa o bioma RUIN
    Biome ruin{};
    ruin.weights = {
        0.0f,  // box
        0.0f,  // campfire
        0.0f, // chest
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
        0.03f   // ghost
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

void Map::InitializeAutomatons()
{
	// Inicializa a fila de autômatos celulares com 50 autômatos
    for (int i = 0; i < 50; ++i)
    {
        CellularAutomaton automaton(11, chunkSize, 0.9f);   // Cria um automato celular
        automaton.Run(5);						            // Executa o automato por 5 gerações
        automatons.push(automaton);                         // Adiciona o automato na fila
    }
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

	return EMPTY;  // Retorna espaço vazio
}

Map::intMatrix Map::GenerateBiome(int biome)
{
	// Seleciona um bioma aleatório
	int idx = biome < 4 ? biome : intDistribution(0, 3)(rng);
    intMatrix chunk;

    // escolher o caminho

    // Se o bioma selecionado for FOREST, gera o bioma totalmente aleatorio
    if (idx == FOREST)
    {
        if (automatons.empty())
            InitializeAutomatons();

        chunk = automatons.front().GetMap();    // Pega um automato da fila
        automatons.pop();					    // Remove o automato da fila

        // Gera a matriz de props do chunk
        for (size_t i = 0; i < chunk.size(); ++i) {
            for (size_t j = 0; j < chunk.at(i).size(); j++) {

				uint cell = chunk.at(i).at(j);  // Seleciona a célula
                if (cell == 1)    // Se for 1, gera um prop aleatório
                {
                    // Gira a roleta e seleciona um prop
                    chunk.at(i).at(j) = SpinRoulette(biomes.at(idx).roulette);
                }
                else
                {
                    chunk.at(i).at(j) = EMPTY;
                }
            }
        }

		//GenerateStructuresForest(chunk);    // Gera as estruturas do bioma FOREST
    }
    else if (idx == FIELD)
    {
        if (automatons.empty()) 
            InitializeAutomatons();

        chunk = automatons.front().GetMap();  // Pega um automato da fila
		automatons.pop();					  // Remove o automato da fila

		// Converte 1's em props aleatórios e 0's em espaço vazio
		for (size_t i = 0; i < chunk.size(); ++i) {
			for (size_t j = 0; j < chunk.at(i).size(); ++j) {

				uint cell = chunk.at(i).at(j);  // Seleciona a célula
				if (cell == 1)  // Se for 1, gera um prop aleatório
                {
                    // Gira a roleta e seleciona um prop
                    uint prop = SpinRoulette(biomes.at(idx).roulette);
                    if (prop == FENCE || prop == FENCEROTTEN) {
                        // Se for uma cerca, gera estrutura
						chunk.at(i).at(j) = prop;
                        GenerateStructuresField(chunk, i, j); // implementar logica
                    }
                    else {
                        chunk.at(i).at(j) = prop;  // Prop aleatório
                    }
                }
				else if (cell == 0)  // Se for 0, gera espaço vazio
                {
					chunk.at(i).at(j) = EMPTY;  // Espaço vazio
                }
			}
		}
    }
    else if (idx == RUIN)
    {
        // Caso contrário, usa um automato celular para gerar as estruturas
        if (automatons.empty())
            InitializeAutomatons();

        chunk = automatons.front().GetMap();  // Pega um automato da fila
        automatons.pop();					  // Remove o automato da fila

        // Converte 1's em props aleatórios e 0's em espaço vazio
        for (size_t i = 0; i < chunk.size(); ++i) {
            for (size_t j = 0; j < chunk.at(i).size(); ++j) {

                uint cell = chunk.at(i).at(j);  // Seleciona a célula
                if (cell == 1)  // Se for 1, gera um prop aleatório
                {
                    // Gira a roleta e seleciona um prop
                    uint prop = SpinRoulette(biomes.at(idx).roulette);
                    if (prop == DOOR) {
                        // Se for uma porta, gera estrutura
                        chunk.at(i).at(j) = prop;
                        GenerateStructuresRuin(chunk, i, j);
                    }
                    else {
                        chunk.at(i).at(j) = prop;  // Prop aleatório
                    }
                }
                else if (cell == 0)  // Se for 0, gera espaço vazio
                {
                    chunk.at(i).at(j) = EMPTY;  // Espaço vazio
                }
            }
        }
    }

    return chunk;
}

// ------------------------------------------------------------------------------

Map::Map(uint seed) : rng(seed), bossProgress(0), bossArea(false)
{
    // Inicializa as propriedades do mapa
	lastPos = Hud::Line(0);         // Posição inicial na primeira linha

    InitializeImages();
    InitializeBiomes();
	InitializeFirstChunk();
    InitializeAutomatons();

    // Gera dois chunks, o inicial e um aleatorio
    // Primeiro chunk é sempre igual
    Generate(firstChunk);
    lastPos = Hud::Line(11);		// Atualiza a última posição

    Generate(GenerateBiome());      // Gera um bioma aleatorio
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

	lastPos = lastProp->Y() - Level1::hud->tileHeight;  // Atualiza a última posição

    // Se o player estiver próximo do final do chunk, gera um novo chunk
	if (lastPos > -500.0f) {
        Generate(GenerateBiome());
	}

    // Atualiza o progresso
	bossProgress = Level1::player->Progress() % 100;

    // Reseta area do boss quando o player passar
    if (bossProgress == 0)
        bossArea = false;

    // Se o player chegar nos 100 tiles e o boss não foi gerado ainda
    if (bossProgress == 99 && !bossArea) 
    {
		bossArea = true;	// Marca a área do boss
        // Gera o boss hydra

        // Posiciona a hydra na coluna 5
        Hydra* hydra = new Hydra(5, 0);

        // Ajusta a posição y
        lastPos = lastPos - 2.0f * hydra->GetHeight();
        hydra->MoveTo(hydra->X(), lastPos - 2.0f * hydra->GetHeight(), Layer::MIDDLE);
        Level1::scene->Add(hydra, MOVING);

		// Gera cenário do boss com gramas e pedras
        Generate(GenerateBiome(3));

        // Gera muros ao final do mapa
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
}

// ------------------------------------------------------------------------------

void Map::Generate(const intMatrix& chunk)
{
    // Gera um chunk, percorrendo cada linha e coluna da matriz gerando os props e inimigos
    for (int y = 0; y < chunk.size(); ++y) {
        for (int x = 0; x < chunk.at(y).size(); ++x) {

			uint idx = chunk.at(y).at(x);	    // Seleciona o indice do chunk
			if (idx == 15) continue;		    // Se for espaço vazio, pula para o próximo
            
            // Gera um ghost
            if (idx == 16) {
                Ghost* ghost = new Ghost(x, -lastPos);
                ghost->MoveTo(ghost->X(), lastPos, Layer::MIDDLE);
                Level1::scene->Add(ghost, MOVING);
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
            case 9: type = OneBitObjects::PILLAR; break;
            case 10: type = OneBitObjects::PILLAR2; break;
            default: type = PROP;
            }

            float col = Level1::hud->Col(x);                // Coluna do prop
            float line = lastPos;                           // Linha continua da última posição

			bool interactable = type != PROP;               // Tipo prop não é interagível
            bool bbox = idx != 7 && idx != 8 && idx != 11;  // Gramas e pedras não possuem bbox

            // Adiciona o prop gerado na cena
            lastProp = new Prop(type, img, col, line, interactable, bbox);
            Level1::scene->Add(lastProp, STATIC);
        }
        lastPos -= Level1::hud->tileHeight;     // Passa para a próxima linha
    }
}

void Map::GenerateStructuresField(intMatrix& chunk, size_t i, size_t j) {
    bool leftDirection;

    // Se a cerca estiver na esquerda, gera cercas à direita
    if (j == 0) {
        leftDirection = false; // Direção direita
    }
    else if (j == 10) { // se estiver da direita, gera cercas à esquerda
        leftDirection = true; // Direção esquerda
    }
    else {
        // Determina aleatoriamente a direção: 0 = esquerda, 1 = direita
        leftDirection = rand() % 2 == 0;
    }

    // Define a posição da porta
    size_t doorPosition = leftDirection ? j - 1 : j + 1; // Posiciona a porta
    chunk.at(i).at(doorPosition) = DOOR;

    // Gera cercas ou cercas podres para a esquerda ou direita
    int maxFences = leftDirection ? j : (10 - doorPosition); // Máximo de cercas que podem ser geradas
    if (doorPosition == 0 || doorPosition == 10) return;
    size_t fenceCount = rand() % maxFences + 1; // Gera um número aleatório de cercas entre 1 e maxFences

    int currentX = doorPosition;
    if (leftDirection) {
        // Gera cercas para a esquerda
        while (fenceCount > 0 && currentX > 0) {
            chunk.at(i).at(--currentX) = (fenceCount % 3 == 0) ? FENCEROTTEN : FENCE; // Alterna entre cercas e cercas podres
            fenceCount--;
        }
    }
    else {
        // Gera cercas para a direita
        while (fenceCount > 0 && currentX < 10) {
            chunk.at(i).at(++currentX) = (fenceCount % 3 == 0) ? FENCEROTTEN : FENCE; // Alterna entre cercas e cercas podres
            fenceCount--;
        }
    }
}

void Map::GenerateStructuresForest(intMatrix& chunk, size_t i, size_t j)
{

}

void Map::GenerateStructuresRuin(intMatrix& chunk, size_t i, size_t j)
{
    // Se a porta estiver em um canto, apaga ela e coloca uma parede
    if (i == 0 || i == 21 || j == 0 || j == 10) {
        chunk.at(i).at(j) = WALL;
        return;
    }

    // Limpa o caminho acima e abaixo da porta
    if (i > 0 && chunk.at(i - 1).at(j) != DOOR) {
        chunk.at(i - 1).at(j) = EMPTY;  // Limpa acima
    }
    if (i < chunk.size() - 1 && chunk.at(i + 1).at(j) != DOOR) {
        chunk.at(i + 1).at(j) = EMPTY;  // Limpa abaixo
    }

    int currentX = j;
    int currentY = i;

    // Gera paredes à esquerda da porta
    int leftWallCount = minLambda(rand() % 4 + 1, j); // Gera entre 1 e 4 paredes
    int leftCount = leftWallCount;
    while (leftWallCount > 0) {
        chunk.at(currentY).at(--currentX) = WALL;
        leftWallCount--;
    }

    // Gera paredes para cima a partir da última parede gerada
    int topWallCount = rand() % 5 + 2;  // Gera entre 2 e 6 paredes para cima
    topWallCount = minLambda(topWallCount, currentY);  // Garante que não ultrapasse o limite superior
    int topCount = topWallCount;
    while (topWallCount > 0) {
        chunk.at(--currentY).at(currentX) = WALL;
        topWallCount--;
    }

    // Gera paredes à direita a partir da última parede gerada
    int rightWallCount = maxLambda(leftCount + 1, rand() % (10 - currentX)); // Garante pelo menos leftCount + 1 paredes

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
    while (currentY < i) { // Volta para baixo até a linha original
        chunk.at(++currentY).at(currentX) = WALL;
    }

    // Volta para a esquerda a partir da última parede gerada para se conectar com a porta
    while (currentX > j + 1) { // Conecta a parede de volta à porta
        chunk.at(currentY).at(--currentX) = WALL;
    }

    // Gera moedas dentro da estrutura
    int coinCount = rand() % 5 + 1; // Gera entre 1 e 5 moedas
    while (coinCount > 0) {
        int coinX = rand() % (leftCount + 1) + (j - leftCount); // Entre o limite esquerdo e j
        int coinY = rand() % (topCount + 1) + (i - topCount); // Entre o limite superior e i

        chunk.at(coinY).at(coinX) = COIN; // Adiciona a moeda
        coinCount--;
    }

    // Calcula uma chance de gerar um baú dentro da estrutura
    int randomChest = rand() % 2; // 50% de chance de gerar um baú
    if (randomChest == 0) {
        bool chestGenerated = false;
        while (!chestGenerated) {
            int chestX = rand() % (leftCount + 1) + (j - leftCount); // Entre o limite esquerdo e j
            int chestY = rand() % (topCount + 1) + (i - topCount); // Entre o limite superior e i

            // Certifica-se de que o local não está ocupado por uma parede, moeda ou porta
			int up = chestY - 1, down = chestY + 1; // Verifica acima e abaixo do baú
            if (up < 0 || down > 21) break;
            if (chunk.at(up).at(chestX) != DOOR && chunk.at(down).at(chestX) != DOOR) {
                chunk.at(chestY).at(chestX) = CHEST; // Adiciona o baú
                chestGenerated = true;
            }
        }
    }
}

// ------------------------------------------------------------------------------