#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

// Función que calcula la norma de la matriz (Norma 1)
double calcularNormaMatriz(const vector<vector<double>>& matriz) {
    int n = matriz.size();
    double norma = 0.0;

    for (int i = 0; i < n; ++i) {
        double sumaFila = 0.0;
        for (int j = 0; j < n; ++j) {
            sumaFila += abs(matriz[i][j]);
        }
        norma = max(norma, sumaFila);
    }

    return norma;
}

// Función que calcula la inversa de una matriz (usando el método de Gauss-Jordan)
bool calcularInversaMatriz(const vector<vector<double>>& matriz, vector<vector<double>>& inversa) {
    int n = matriz.size();
    inversa = matriz;
    vector<vector<double>> identidad(n, vector<double>(n, 0.0));

    // Crear la matriz identidad
    for (int i = 0; i < n; ++i) {
        identidad[i][i] = 1.0;
    }

    // Augmentar la matriz con la identidad para aplicar Gauss-Jordan
    for (int i = 0; i < n; ++i) {
        inversa[i].insert(inversa[i].end(), identidad[i].begin(), identidad[i].end());
    }

    // Aplicar el método de Gauss-Jordan
    for (int i = 0; i < n; ++i) {
        // Buscar el pivote y normalizar la fila
        double pivote = inversa[i][i];
        if (pivote == 0) {
            cout << "La matriz no tiene inversa." << endl;
            return false;
        }
        for (int j = 0; j < 2 * n; ++j) {
            inversa[i][j] /= pivote;
        }

        // Eliminar las otras filas
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = inversa[k][i];
                for (int j = 0; j < 2 * n; ++j) {
                    inversa[k][j] -= factor * inversa[i][j];
                }
            }
        }
    }

    // Extraer la matriz inversa
    for (int i = 0; i < n; ++i) {
        inversa[i].erase(inversa[i].begin(), inversa[i].begin() + n);
    }

    return true;
}

// Función que calcula el exponente de la notación científica
int obtenerExponente(double numero) {
    if (numero == 0) return 0;
    return static_cast<int>(floor(log10(abs(numero))));
}

int main() {
    // Matriz de 2x2
    vector<vector<double>> matriz = {
        {0.835, 0.667},
        {0.333, 0.266}
    };

    // Calcular la norma de la matriz
    double normaMatriz = calcularNormaMatriz(matriz);
    cout << "La norma de la matriz original es: " << normaMatriz << endl;

    // Calcular la inversa de la matriz
    vector<vector<double>> inversa;
    if (!calcularInversaMatriz(matriz, inversa)) {
        return 1;
    }

    // Calcular la norma de la matriz inversa
    double normaInversa = calcularNormaMatriz(inversa);
    cout << "La norma de la matriz inversa es: " << normaInversa << endl;

    // Calcular el producto de las normas
    double productoNormas = normaMatriz * normaInversa;

    // Obtener el exponente de la notación científica del producto
    int exponente = obtenerExponente(productoNormas);
    cout << "El exponente de la notación científica del producto es: " << exponente << endl;

    // Solicitar el valor de t
    int t;
    cout << "Introduce un valor entero t: ";
    cin >> t;

    // Calcular n = t - exponente
    int n = t - exponente;
    cout << "El valor de n es: " << n << endl;

    return 0;
}

