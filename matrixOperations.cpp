
#include <vector>
#include <iostream>

using namespace std;

//aqui estão todas as funções principais para o funcionamento do algoritmo
//todas as funções fazem exatamente o que seus nomes dizem, nada além

void printMatrix(vector<vector<double>> x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[i].size(); j++)
        {
            cout << x[i][j] << " ";
        }
        cout << endl;
    }
}
//cálculo do Wx ou Wy
vector<vector<double>> multiplyMatrixWeights(vector<vector<double>> matrix, vector<double> vet)
{

    vector<double> v(matrix[0].size());
    vector<vector<double>> aux(matrix.size(), v);

    for (int i = 0; i < matrix[0].size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            aux[j][i] = matrix[j][i] * vet[j];
        }
    }

    return aux;
}

vector<vector<double>> transposeMatrix(vector<vector<double>> X)
{

    vector<double> v(X.size());
    vector<vector<double>> aux(X[0].size(), v);

    for (int i = 0; i < X.size(); i++)
    {
        for (int j = 0; j < X[i].size(); j++)
        {
            aux[j][i] = X[i][j];
        }
    }

    return aux;
}

double findDet2x2(vector<vector<double>> X)
{
    return (X[0][0] * X[1][1]) - (X[0][1] * X[1][0]);
}

vector<vector<double>> findInverseOf2x2(vector<vector<double>> X)
{

    vector<double> v(X[0].size());
    vector<vector<double>> aux(X.size(), v);

    double det = findDet2x2(X);

    aux[0][0] = X[1][1] * (1 / det);
    aux[0][1] = -X[0][1] * (1 / det);
    aux[1][0] = -X[1][0] * (1 / det);
    aux[1][1] = X[0][0] * (1 / det);

    return aux;
}
double findDet3x3(vector<vector<double>> X)
{
    return (((X[1][0] * X[2][1] * X[0][2]) + (X[0][0] * X[1][1] * X[2][2]) + (X[0][1] * X[1][2] * X[2][0])) - ((X[0][1] * X[1][0] * X[2][2]) + (X[0][2] * X[1][1] * X[2][0]) + (X[1][2] * X[2][1] * X[0][0])));
}

vector<vector<double>> findInverseOf3x3(vector<vector<double>> X)
{

    vector<double> v(X[0].size());
    vector<vector<double>> aux(X.size(), v);

    double det = findDet3x3(X);

    vector<vector<double>> mt = transposeMatrix(X);

    //matriz dos cofatores (sim, fiz um a um na mão kkkk)
    aux[0][0] = ((mt[1][1] * mt[2][2]) - (mt[1][2] * mt[2][1])) * (1 / det); //11 22 12 21
    aux[0][1] = ((mt[1][0] * mt[2][2]) - (mt[1][2] * mt[2][0])) * (1 / det); //10 22 12 20
    aux[0][2] = ((mt[1][0] * mt[2][1]) - (mt[1][1] * mt[2][0])) * (1 / det); //10 21 11 20
    aux[1][0] = ((mt[0][1] * mt[2][2]) - (mt[0][2] * mt[2][1])) * (1 / det); //01 22 02 21
    aux[1][1] = ((mt[0][0] * mt[2][2]) - (mt[0][2] * mt[2][0])) * (1 / det); // 00 22 02 20
    aux[1][2] = ((mt[0][0] * mt[2][1]) - (mt[2][0] * mt[0][1])) * (1 / det); //00 21 01 21
    aux[2][0] = ((mt[0][1] * mt[1][2]) - (mt[0][2] * mt[1][1])) * (1 / det); //01 12 02 11
    aux[2][1] = ((mt[0][0] * mt[1][2]) - (mt[0][2] * mt[1][0])) * (1 / det); //00 12 02 10
    aux[2][2] = ((mt[0][0] * mt[1][1]) - (mt[0][1] * mt[1][0])) * (1 / det); //00 11 01 10

    vector<vector<double>> aux2 = transposeMatrix(aux);

    aux2[0][1] *= -1;
    aux2[1][0] *= -1;
    aux2[1][2] *= -1;
    aux2[2][1] *= -1;

    return aux2;
}

vector<vector<double>> multiplyMatrix(vector<vector<double>> x, vector<vector<double>> y)
{

    vector<double> v(y[0].size());
    vector<vector<double>> aux(x.size(), v);

    for (int i = 0; i < x.size(); i++)
    {
        double soma = 0;
        for (int j = 0; j < y[0].size(); j++)
        {

            for (int k = 0; k < y.size(); k++)
            {
                soma += x[i][k] * y[k][j];
            }
            aux[i][j] = soma;
            soma = 0;
        }
    }
    return aux;
}
