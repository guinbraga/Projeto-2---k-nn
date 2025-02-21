#include <iostream>
#include "knn.h" 
#include "read_csv.h"

using namespace std;

// Função para calcular a acurácia do modelo
float calcular_acuracia(int* previsoes, int** rotulos_reais, int qtd_classificar) {
    int acertos = 0;
    for (int i = 0; i < qtd_classificar; ++i) {
        if (previsoes[i] == rotulos_reais[i][0]) {
            acertos++;
        }
    }
    return (float)acertos / qtd_classificar * 100;
}



int main() {
    // usamos, aqui, nossa classe que lê csv para ler as matrizes de treino
    // e também de previsão. Anexei no trabalho os arquivos de acordo, além de um link
    // no github com todos os arquivos, caso seja mais fácil para rodar.

    csv amostras("amostras_treino.csv");
    csv labels("labels_treino.csv");
    float** treino_dados_f = amostras.read_float();
    int** treino_rotulos = labels.read_int();

    csv amostras_prever("prever.csv");
    float** prever = amostras_prever.read_float();
    csv rotulos_reais("labels_prever.csv");
    int** rotulos_certos = rotulos_reais.read_int();


    knn modelo(6); 



    modelo.fit(treino_dados_f, treino_rotulos, amostras.linhas, amostras.colunas);  

    
    int* previsoes = modelo.predict(prever, amostras_prever.linhas);  

    float acuracia = calcular_acuracia(previsoes, rotulos_certos, amostras_prever.linhas);

    // Exibindo as previsões e a acurácia
    cout << "Previsões: ";
    for (int i = 0; i < amostras_prever.linhas; ++i) {
        cout << previsoes[i] << " ";
    }
    cout << endl;

    cout << "Acurácia: " << acuracia << "%" << endl;

    delete[] previsoes;
}
