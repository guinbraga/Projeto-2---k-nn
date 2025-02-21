#include <iostream>
#include <cmath>
using namespace std;

class knn {
private:
    int k;
    int** treino_dados_i;
    int** treino_rotulos_i;
    float** treino_dados_f;
    int** treino_rotulos_f;
    int qtd_amostras;
    int qtd_features;

    float distancia_euclidiana(float* a, float* b) {
        float distancia = 0;
        for (int i = 0; i < qtd_features; ++i) {
            distancia += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(distancia);
    }

    float distancia_euclidiana(int* a, int* b) {
        float distancia = 0;
        for (int i = 0; i < qtd_features; ++i) {
            distancia += (a[i] - b[i]) * (a[i] - b[i]);
        }
        return sqrt(distancia);
    }

public:
    knn() {
        k = 5;
        treino_rotulos_f = nullptr;
        treino_dados_f = nullptr;
        treino_rotulos_i = nullptr;
        treino_dados_i = nullptr;
    }

    knn(int k) {
        this->k = k;
        treino_dados_f = nullptr;
        treino_rotulos_f = nullptr;
        treino_rotulos_i = nullptr;
        treino_dados_i = nullptr;
    }

    void fit(float** dados, int** rotulos, int qtd_amostras, int qtd_features) {
        this->qtd_amostras = qtd_amostras;
        this->qtd_features = qtd_features;

        treino_dados_f = new float*[qtd_amostras];
        for (int i = 0; i < qtd_amostras; ++i) {
            treino_dados_f[i] = new float[qtd_features];
            for (int j = 0; j < qtd_features; ++j) {
                treino_dados_f[i][j] = dados[i][j];
            }
        }

        treino_rotulos_f = new int*[qtd_amostras];
        for (int i = 0; i < qtd_amostras; ++i) {
            treino_rotulos_f[i] = new int[1];
            treino_rotulos_f[i][0] = rotulos[i][0];
        }
    }

    void fit(int** dados, int** rotulos, int qtd_amostras, int qtd_features) {
        this->qtd_amostras = qtd_amostras;
        this->qtd_features = qtd_features;

        treino_dados_i = new int*[qtd_amostras];
        for (int i = 0; i < qtd_amostras; ++i) {
            treino_dados_i[i] = new int[qtd_features];
            for (int j = 0; j < qtd_features; ++j) {
                treino_dados_i[i][j] = dados[i][j];
            }
        }

        treino_rotulos_i = new int*[qtd_amostras];
        for (int i = 0; i < qtd_amostras; ++i) {
            treino_rotulos_i[i] = new int[1];
            treino_rotulos_i[i][0] = rotulos[i][0];
        }
    }

    int* predict(int** classificar, int qtd_classificar) {
        int* previsoes = new int[qtd_classificar];

        for (int i = 0; i < qtd_classificar; ++i) {
            float* distancias = new float[qtd_amostras];
            int* indices = new int[qtd_amostras];
            for (int j = 0; j < qtd_amostras; ++j) {
                distancias[j] = distancia_euclidiana(treino_dados_i[j], classificar[i]);
                indices[j] = j;
            }

            for (int x = 0; x < qtd_amostras - 1; ++x) {
                for (int y = 0; y < qtd_amostras - x - 1; ++y) {
                    if (distancias[y] > distancias[y + 1]) {
                        swap(distancias[y], distancias[y + 1]);
                        swap(indices[y], indices[y + 1]);
                    }
                }
            }

            int* contagem_rotulos = new int[10]();
            for (int x = 0; x < k; ++x) {
                int rotulo = treino_rotulos_i[indices[x]][0];
                contagem_rotulos[rotulo]++;
            }

            int rotulo_frequente = -1, maior_contagem = 0;
            for (int x = 0; x < 10; ++x) {
                if (contagem_rotulos[x] > maior_contagem) {
                    rotulo_frequente = x;
                    maior_contagem = contagem_rotulos[x];
                }
            }

            previsoes[i] = rotulo_frequente;

            delete[] distancias;
            delete[] indices;
            delete[] contagem_rotulos;
        }

        return previsoes;
    }

    int* predict(float** classificar, int qtd_classificar) {
        int* previsoes = new int[qtd_classificar];

        for (int i = 0; i < qtd_classificar; ++i) {
            float* distancias = new float[qtd_amostras];
            int* indices = new int[qtd_amostras];
            for (int j = 0; j < qtd_amostras; ++j) {
                distancias[j] = distancia_euclidiana(treino_dados_f[j], classificar[i]);
                indices[j] = j;
            }

            for (int x = 0; x < qtd_amostras - 1; ++x) {
                for (int y = 0; y < qtd_amostras - x - 1; ++y) {
                    if (distancias[y] > distancias[y + 1]) {
                        swap(distancias[y], distancias[y + 1]);
                        swap(indices[y], indices[y + 1]);
                    }
                }
            }

            int* contagem_rotulos = new int[10]();
            for (int x = 0; x < k; ++x) {
                int rotulo = treino_rotulos_f[indices[x]][0];
                contagem_rotulos[rotulo]++;
            }

            int rotulo_frequente = -1, maior_contagem = 0;
            for (int x = 0; x < 10; ++x) {
                if (contagem_rotulos[x] > maior_contagem) {
                    rotulo_frequente = x;
                    maior_contagem = contagem_rotulos[x];
                }
            }

            previsoes[i] = rotulo_frequente;

            delete[] distancias;
            delete[] indices;
            delete[] contagem_rotulos;
        }

        return previsoes;
    }

    ~knn() {
        if (treino_dados_i) {
            for (int i = 0; i < qtd_amostras; ++i) {
                delete[] treino_dados_i[i];
            }
            delete[] treino_dados_i;
        }

        if (treino_dados_f) {
            for (int i = 0; i < qtd_amostras; ++i) {
                delete[] treino_dados_f[i];
            }
            delete[] treino_dados_f;
        }

        delete[] treino_rotulos_i;
        delete[] treino_rotulos_f;
    }
};
