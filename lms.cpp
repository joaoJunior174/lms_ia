#include <iostream>
#include <vector>
#include "matrixOperations.cpp"

using namespace std;

//embora o nome seja basicLMS, ela é a função básica para o cálculo do LMS
//tanto a forma quadrática, a ponderada ou a normal são feitas aqui
//caso de queira o lms normal, os pesos passados são 1
//de qualquer forma, os pesos também são calculados
//caso não queira esse comportamento, comente a parte da ponderação na main.cpp
//aqui não vou comentar as funções, pelo fato de seus nomes já estarem falando sobre o
//que fazem
vector<vector<double>> basicLMS(vector<vector<double>> x, vector<vector<double>> y, vector<double> weights)
{
    vector<vector<double>> result1 = multiplyMatrix(transposeMatrix(x), multiplyMatrixWeights(x, weights));

    vector<vector<double>> inv1;

    if (result1[0].size() > 2)
    {
        inv1 = findInverseOf3x3(result1);
    }
    else
    {
        inv1 = findInverseOf2x2(result1);
    }

    vector<vector<double>> result2 = multiplyMatrix(transposeMatrix(x), multiplyMatrixWeights(y, weights));
    vector<vector<double>> finalResult = multiplyMatrix(inv1, result2);

    return finalResult;
}
