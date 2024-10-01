// CellularAutomaton.h

#ifndef CELLULARAUTOMATON_H
#define CELLULARAUTOMATON_H

#include "Types.h"
#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

// ------------------------------------------------------------------------------

class CellularAutomaton
{
private:
    int width, height;
    float fillProbability;
    vector<vector<uint>> grid;

    // Preenche aleatoriamente a matriz com células vivas
    void InitializeMap();
    void Step();
    int CountAliveNeighbors(int x, int y);

public:
    CellularAutomaton(int width, int height, float fillProbability);

    void Run(int iterations);
    vector<vector<uint>> GetMap() { return grid; }
};

// ------------------------------------------------------------------------------

#endif
