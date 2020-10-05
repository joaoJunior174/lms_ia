

/*Olá professor, tudo bem? para realizar os programas deste e dos próximos trabalhos,
esterei deixando o mais padronizado possível, e em todos os  arquivos principais,
estarei deixando comentários também. Tentarei deixar o nome das varáveis e funções
o mais intuitivo possível, para não poluir com comentários. 

Este programa calcula o LMS para os três casos que o senhor colocou como exercício.
Vale ressaltar, que cada arquivo foi tratado para ler em C++ (o senhor colocou um tab,
e isso prejudicou a leitura, ai eu apaguei e dei um space entre cada dado). Eu não fiz
o cálculo para encontrar os determinates de matrizes 4x4, então na forma quadrática,
o arquivo 'Books_attend_grande.txt' não vai funcionar para este método.
Para o cálculo dos pesos e método robusto, utilizei o MAD e Bisquare weighting,
pegando como referência esses sites https://www.itl.nist.gov/div898/handbook/mpc/section6/mpc6522.htm
 e https://en.wikipedia.org/wiki/Median_absolute_deviation 

 */

#include <cstdlib>
#include <iostream>
#include <cmath>
#include "readFile.cpp"
#include "lms.cpp"
#include <bits/stdc++.h>

using namespace std;
//função para inicializar todas as posições da matriz passada com 1
void initializeInput(vector<vector<double>> &x)
{
    for (int i = 0; i < x.size(); i++)
    {
        for (int j = 0; j < x[i].size(); j++)
        {
            x[i][j] = 1;
        }
    }
}
//função resposnável por separar os dados x e y em vetores diferentes
void copyFromData(vector<vector<double>> &x, vector<vector<double>> &y, vector<vector<double>> data)
{
    //aqui copia os dados
    for (int i = 0; i < data.size(); i++)
    {
        int j = 0;
        for (j = 0; j < data[i].size() - 1; j++)
        {
            x[i][j + 1] = data[i][j];
        }
        y[i][0] = data[i][j];
    }
}
//essa função calcula os residuos, ou seja, retorna uma matriz (com uma coluna)
//representando a diferença (yi-ŷi)
vector<vector<double>> findResiduals(vector<vector<double>> input, vector<vector<double>> output, vector<vector<double>> b)
{
    vector<double> colres(output[0].size());
    vector<vector<double>> res(output.size(), colres);

    for (int i = 0; i < input.size(); i++)
    {
        double out = 0;
        for (int j = 0; j < input[i].size(); j++)
        {
            out += b[j][0] * input[i][j];
        }
        res[i][0] = out;
    }

    for (int i = 0; i < res.size(); i++)
    {

        res[i][0] = abs(output[i][0] - res[i][0]);
    }

    return res;
}
//essa função é responsável por colocar uma coluna a mais com x*x
vector<vector<double>> buildQuadraticArray(vector<vector<double>> x)
{

    vector<double> colx(x[0].size() + 1);
    vector<vector<double>> aux(x.size(), colx);

    for (int i = 0; i < x.size(); i++)
    {
        int j = 0;
        for (j = 0; j < x[i].size(); j++)
        {
            aux[i][j] = x[i][j];
        }
        aux[i][j] = aux[i][j - 1] * aux[i][j - 1];
    }

    return aux;
}
//aqui é o cálculo do mad, vide link no topo deste arquivo
double findMedianAbsoluteDeviation(vector<vector<double>> array)
{

    //vetor auxiliar que pega os residuos
    vector<double> numbers;

    for (int i = 0; i < array.size(); i++)
    {
        numbers.push_back(array[i][0]);
    }

    //ordena para fazer a mediana
    sort(numbers.begin(), numbers.end());

    double index = numbers.size();
    double median;
    //começo conta mediana
    if (numbers.size() % 2 == 0)
    {

        median = (numbers[round(index / 2) - 1] + numbers[round(index / 2)]) / 2;
    }
    else
    {
        median = numbers[round(index / 2) - 1];
    }
    //fim conta mediana
    for (int i = 0; i < numbers.size(); i++)
    {
        numbers[i] = abs(numbers[i] - median);
    }
    //comeco mad
    sort(numbers.begin(), numbers.end());

    if (numbers.size() % 2 == 0)
    {
        median = (numbers[round(index / 2) - 1] + numbers[round(index / 2)]) / 2;
    }
    else
    {
        median = numbers[round(index / 2) - 1];
    }
    //fim mad
    return median;
}
//essa função recalcula os pesos pela utilizando MAD e Bisquare weighting
void recalculateWeights(vector<vector<double>> residual, double mad, vector<double> &weights)
{

    for (int j = 0; j < weights.size(); j++)
    {
        if (residual[j][0] <= (6 * mad))
            weights[j] = pow(1 - pow(residual[j][0] / (6 * mad), 2), 2);
        else
            weights[j] = 0;
    }
}
int main()
{

    //vector<vector<double>> data = readFile("files/shoes.txt");
    vector<vector<double>> data = readFile("files/US-Census.txt");
    //vector<vector<double>> data = readFile("files/alpswater.txt");
    //vector<vector<double>> data = readFile("files/Books_attend_grade.txt");

    vector<double> colx(data[0].size());
    vector<double> colWeights(data[0].size());
    vector<double> coly(1);
    vector<vector<double>> x(data.size(), colx);
    vector<vector<double>> y(data.size(), coly);
    vector<double> weights(data.size(), 1);

    initializeInput(x);
    copyFromData(x, y, data);

    //descomenta caso queira testar os valores para a forma quadrática
    //atente-se,o arquivo Books_attend_grade.txt não funciona para este método
    //pois a matrix 4x4 não foi calculada
    //x = buildQuadraticArray(x);

    vector<vector<double>> b = basicLMS(x, y, weights);

    //aqui recalcula os pesos e fazer a forma robusta utilizando o MAD
    //a formula para o bisquare está aqui: https://www.itl.nist.gov/div898/handbook/mpc/section6/mpc6522.htm

    vector<vector<double>> residual = findResiduals(x, y, b);
    double mad = findMedianAbsoluteDeviation(residual);
    recalculateWeights(residual, mad, weights);
    vector<vector<double>> b_weighted = basicLMS(x, y, weights);

    cout << "Coeficientes sem peso:" << endl;
    printMatrix(b);
    cout << "Coeficientes com peso:" << endl;
    printMatrix(b_weighted);

    return 0;
}