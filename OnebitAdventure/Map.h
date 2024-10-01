#ifndef MAP_H
#define MAP_H

// ------------------------------------------------------------------------------

#include "Image.h"
#include "Types.h"
#include <array>
#include <cstdlib>
#include <ctime>
#include <numeric>
#include <random>
#include <string>
#include <vector>

// ------------------------------------------------------------------------------

using std::array;
using std::vector;

// ------------------------------------------------------------------------------

class Map
{
private:
    typedef vector<vector<uint>> intMatrix;
    typedef vector<vector<float>> floatMatrix;
    typedef vector<vector<std::string>> stringMatrix;
    typedef vector<floatMatrix> chunkMatrix;
    typedef std::uniform_int_distribution<int> intDistribution;
    typedef std::uniform_real_distribution<double> doubleDistribution;

    std::random_device rd;      // Inicializa o gerador de números aleatórios
    std::mt19937 rng;           // Inicializa o Mersenne Twister com uma semente aleatória

    // Estrutura para armazenar um prop com seu intervalo na roleta
    struct PropInterval {
        uint type;         // Tipo do prop
        float start;       // Início do intervalo
        float end;         // Fim do intervalo

        PropInterval(uint type, float start, float end) : type(type), start(start), end(end) {}
    };

    // Estrutura de um bioma
    struct Biome {
        std::array<float, 17> weights;        // Array de pesos para a roleta do bioma
        std::vector<PropInterval> roulette;   // Vetor de intervalos na roleta

        void BuildRoulette() {
            // Calcular a soma total dos pesos
            float totalWeight = std::accumulate(weights.begin(), weights.end(), 0.0f);

            // Normalizar os pesos se totalWeight for maior que 0
            if (totalWeight > 0) {
                for (size_t i = 0; i < weights.size(); ++i) {
                    weights[i] /= totalWeight; // Normaliza cada peso
                }
            }

            // Recria a roleta com os pesos normalizados
            float cumulativeWeight = 0.0f;
            roulette.clear(); // Limpa a roleta antes de adicionar os novos intervalos

            for (size_t i = 0; i < weights.size(); ++i) {
                // Atualizar o peso acumulado
                cumulativeWeight += weights[i];

                // Calcular o limite superior do intervalo
                float upperLimit = cumulativeWeight;

                // Adicionar o intervalo à roleta
                if (i == 0) {
                    roulette.emplace_back(i, 0.0f, upperLimit);
                }
                else {
                    float lowerLimit = roulette[i - 1].end; // Limite inferior é o limite superior do intervalo anterior
                    roulette.emplace_back(i, lowerLimit, upperLimit);
                }
            }
        }
    };

    // Estrutura de um chunk
    struct Chunk
    {
        Biome biome;               // Bioma do chunk
        intMatrix chunk;           // Matriz de tipos props
    };

    // Constantes
    const uint BOX = 0;
	const uint CAMPFIRE = 1;
    const uint CHEST = 2;
    const uint COIN = 3;
    const uint DOOR = 4;
    const uint FENCE = 5;
    const uint FENCEROTTEN = 6;
    const uint GRASS = 7;
    const uint GRASS2 = 8;
    const uint PILAR = 9;
    const uint PILAR2 = 10;
    const uint ROCK = 11;
    const uint TREE = 12;
    const uint TREE2 = 13;
    const uint WALL = 14;
    const uint EMPTY = 15;
    const uint GHOST = 16;

    const int chunkSize = 22;      // Número de linhas de cada chunk
    const int nChunks = 20;        // Quantidade de chunks no mapa
    float lastPos;                 // Posição do último prop desenhado

public:
    static const int propsLength = 15;                  // Tamanho do vetor de props
    static array<Image*, propsLength> images;           // Vetor de imagens de props
    static vector<Biome> biomes;                        // Vetor de biomas
    static intMatrix firstChunk;                        // Primeiro chunk do mapa

    Map(uint seed);
    ~Map();

	void Update();									    // Atualiza o mapa

    void InitializeImages();                            // Inicializa o vetor de imagens de props
    void InitializeBiomes();                            // Inicializa o vetor de biomas
    void InitializeFirstChunk();                        // Inicializa o primeiro chunk
    intMatrix GenerateBiome(int biome = 4);             // Escolhe um bioma aleatório
    uint SpinRoulette(const vector<PropInterval>& roulette);  // Gira a roleta e seleciona um prop
    void Generate(const intMatrix& chunk);              // Gera um chunk a partir da matriz de props

	void GenerateStructuresField(intMatrix& chunk);     // Gera campos
	void GenerateStructuresForest(intMatrix& chunk);    // Gera florestas
	void GenerateStructuresRuin(intMatrix& chunk);      // Gera ruínas
};

// ------------------------------------------------------------------------------

#endif // MAP_H
