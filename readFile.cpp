#include <vector>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//função responsável por carregar os arquivos txt e formatar os dados
//essa função retorna um array data, onde usas colunas representam x e y
vector<vector<double>> readFile(string file)
{
    string myText;
    ifstream MyReadFile(file);
    vector<vector<double>> data;

    while (getline(MyReadFile, myText))
    {
        string dataText = "";
        vector<double> aux;
        for (int i = 0; i <= myText.length(); i++)
        {
            if (myText[i] != ' ' && i != myText.length())
            {
                dataText += myText[i];
            }
            else
            {
                if (dataText != "")
                    aux.push_back(stof(dataText));
                dataText = "";
            }
        }
        data.push_back(aux);
    }
    MyReadFile.close();
    return data;
}