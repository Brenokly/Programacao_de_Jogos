#include "CellularAutomaton.h"

// ------------------------------------------------------------------------------

CellularAutomaton::CellularAutomaton(int width, int height, float fillProbability) 
    : width(width), height(height), fillProbability(fillProbability) 
{
    // Inicializa o mapa
    grid.resize(height, vector<unsigned int>(width));
    InitializeMap();
}

// ------------------------------------------------------------------------------

void CellularAutomaton::Run(int iterations)
{
    for (int i = 0; i < iterations; ++i) {
        Step();
    }
}

// ------------------------------------------------------------------------------

void CellularAutomaton::InitializeMap()
{
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid.at(y).at(x) = (static_cast<float>(rand()) / RAND_MAX) < fillProbability ? 0 : 1;
        }
    }
}

// ------------------------------------------------------------------------------

void CellularAutomaton::Step()
{
    vector<vector<uint>> newGrid = grid;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int aliveNeighbors = CountAliveNeighbors(x, y);

            // Célula viva
            if (grid.at(y).at(x) == 1) {
                // Aumenta a probabilidade de sobreviver conforme o número de vizinhos
                float survivalChance = aliveNeighbors * 0.15f; // Aumenta a chance por vizinho
                if (static_cast<float>(rand()) / RAND_MAX > survivalChance) {
                    newGrid.at(y).at(x) = 0; // Morre
                }
            }
            // Célula morta
            else {
                // Aumenta a probabilidade de nascer conforme o número de vizinhos
                float birthChance = aliveNeighbors * 0.2f; // Aumenta a chance por vizinho
                if (static_cast<float>(rand()) / RAND_MAX < birthChance) {
                    newGrid.at(y).at(x) = 1; // Nasce
                }
            }
        }
    }

    grid = newGrid; // Atualiza o mapa
}

// ------------------------------------------------------------------------------

int CellularAutomaton::CountAliveNeighbors(int x, int y)
{
    int count = 0;

    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            if (dy == 0 && dx == 0) continue; // Ignora a célula central
            int nx = x + dx;
            int ny = y + dy;

            // Verifica os limites do mapa
            if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                count += grid.at(ny).at(nx); // Adiciona o estado da célula vizinha
            }
        }
    }

    return count;
}

// ------------------------------------------------------------------------------
