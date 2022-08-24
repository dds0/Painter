#include "Miniweb.h"


Matrix MiniWeb::Solve(Matrix m)
{
    m = this->Sigmoid(m, IsPlusNeouron::No);
    m = this->Sigmoid(Weights[0] * m, IsPlusNeouron::Yes);

    for(size_t i = 1; i < Weights.size(); ++i)
        m = this->Sigmoid(Weights[i] * m, IsPlusNeouron::Yes);

    return m;
}

Matrix MiniWeb::Sigmoid(Matrix m, const IsPlusNeouron& Plus)
{
    std::pair<size_t, size_t> temp = m.GetSize();

    for (size_t i = 0; i < temp.first; ++i)
    {
        if (Plus == IsPlusNeouron::Yes)
            m[i][0] = 1 / (1 + exp(-(displacement_neuron + m[i][0])));
        else
            m[i][0] = 1 / (1 + exp(-m[i][0]));
    }

    return m;
}

void MiniWeb::ParseDataFromFile(const std::string &fileName)
{
    std::fstream file;
    file.open(fileName + ".txt", std::ios::in);
    std::string temp;

    if (file.is_open())
    {
        for(size_t id_current_W = 0; id_current_W < Weights.size(); ++id_current_W)
        {
            auto matrixSizes = Weights[id_current_W].GetSize();
            size_t trash = matrixSizes.second;
            int a = 0;
            while (trash > 0)
            {
                file >> temp;
                --trash;
                ++a;
            }

            for(size_t i = 0; i < matrixSizes.first; ++i)
            {
                for(size_t j = 0; j < matrixSizes.second; ++j)
                {
                    file >> temp;
                    Weights[id_current_W][i][j] = std::stof(temp);
                }
            }
        }

    }
    else
        qDebug() <<"Can't open file.";

    file.close();
}
