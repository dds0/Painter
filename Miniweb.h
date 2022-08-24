#ifndef MINIWEB_H
#define MINIWEB_H


#include "Matrix.h"
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>
#define displacement_neuron 1

enum class IsPlusNeouron
{
    Yes, No
};

class MiniWeb
{
public:
    MiniWeb(){};
    Matrix Solve(Matrix m);
    void ParseDataFromFile(const std::string& fileName);

private:
    Matrix Sigmoid(Matrix m, const IsPlusNeouron& Plus);

    std::vector<Matrix> Weights =
    {
        Matrix(24,784), Matrix(48,24), Matrix(24,48), Matrix(10,24)
    };
};

#endif // MINIWEB_H
