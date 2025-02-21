#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class csv {
private:
    string nome_arquivo;
    string *cabecalho;
    char sep;
    float** matriz_float = nullptr;
    int** matriz_int = nullptr; 


    void contar_dimensoes() {
        ifstream file(nome_arquivo);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return;
        }

        string linha_arquivo;
        while (getline(file, linha_arquivo)) {
            stringstream ss(linha_arquivo);
            string celula;
            int colunas_atuais = 0;
            while (getline(ss, celula, sep)) {
                colunas_atuais++;
            }
            colunas = max(colunas, colunas_atuais);
            linhas++;
        }

        cabecalho = new string[colunas];
        file.close();
    }

public:
    int linhas = -1, colunas = 0; // inicio linhas = -1 para considerar o cabecalho.          
    int max_linhas = 1000, max_cols = 1000;
    
    csv(string nome_arquivo, char sep = ',', int max_linhas = 1000, int max_cols = 1000, int header = 0){
        this->nome_arquivo = nome_arquivo;
        this->sep = sep;
        this->max_linhas = max_linhas;
        this->max_cols = max_cols;
    }

    ~csv() {
        if (matriz_float) {
            for (int i = 0; i < linhas; i++) {
                delete[] matriz_float[i];
            }
            delete[] matriz_float;
        }
        if (matriz_int) {
            for (int i = 0; i < linhas; i++) {
                delete[] matriz_int[i];
            }
            delete[] matriz_int;
        }
    }

    float** read_float() {
        
        // Aloca dinamicamente a matriz:
        contar_dimensoes();
        matriz_float = new float*[linhas];
        for (int i = 0; i < linhas; i++) {
            matriz_float[i] = new float[colunas]();
        }

        // Abre o arquivo:
        ifstream file(nome_arquivo);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return nullptr;
        }

        // preenche o cabecalho:
        string linha_arquivo;
        if (getline(file, linha_arquivo)) { 
            stringstream ss(linha_arquivo); 
            string celula;
            int coluna_atual = 0;

            while (getline(ss, celula, sep) && coluna_atual < colunas) { 
                cabecalho[coluna_atual] = celula; 
                coluna_atual++;
            }
        }


        // preenche a matriz:
        int linha_matriz = 0;
        while (getline(file, linha_arquivo) && linha_matriz < max_linhas) {
            stringstream ss(linha_arquivo);
            string celula;
            int coluna_atual = 0;
            while (getline(ss, celula, sep) && coluna_atual < max_cols) {
                    if (celula.empty()) { // trata o caso de dados faltantes
                        matriz_float[linha_matriz][coluna_atual] = 0.0;
                    } else {
                        matriz_float[linha_matriz][coluna_atual] = stof(celula);
                    }
                coluna_atual++;
            }
            linha_matriz++;
        }

        file.close();
        return matriz_float;
    }

    int** read_int() {
        
        // Aloca dinamicamente a matriz:
        contar_dimensoes();
        matriz_int = new int*[linhas];
        for (int i = 0; i < linhas; i++) {
            matriz_int[i] = new int[colunas]();
        }

        // Abre o arquivo:
        ifstream file(nome_arquivo);
        if (!file.is_open()) {
            cerr << "Error opening file!" << endl;
            return nullptr;
        }

        // preenche o cabecalho:
        string linha_arquivo;
        if (getline(file, linha_arquivo)) { 
            stringstream ss(linha_arquivo); 
            string celula;
            int coluna_atual = 0;

            while (getline(ss, celula, sep) && coluna_atual < colunas) { 
                cabecalho[coluna_atual] = celula; 
                coluna_atual++;
            }
        }


        // preenche a matriz:
        int linha_matriz = 0;
        while (getline(file, linha_arquivo) && linha_matriz < max_linhas) {
            stringstream ss(linha_arquivo);
            string celula;
            int coluna_atual = 0;
            while (getline(ss, celula, sep) && coluna_atual < max_cols) {
                    if (celula.empty()) { // trata o caso de dados faltantes;
                        matriz_int[linha_matriz][coluna_atual] = 0.0;
                    } else {
                        matriz_int[linha_matriz][coluna_atual] = stoi(celula);
                    }
                coluna_atual++;
            }
            linha_matriz++;
        }

        file.close();
        return matriz_int;
    }

    void print_matriz_float() {
        for (int i = 0; i<colunas; i++){
            cout << cabecalho[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) { 
                cout << matriz_float[i][j] << " ";
            }
            cout << endl;
        }
    }

    void print_matriz_int() {
        for (int i = 0; i<colunas; i++){
            cout << cabecalho[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) { 
                cout << matriz_int[i][j] << " ";
            }
            cout << endl;
        }
    }

};
