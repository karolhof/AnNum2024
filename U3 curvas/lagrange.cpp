#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Variables globales
vector<double> x_vals = {0, 1, 2, 3}; // Valores de X
vector<double> y_vals = {1, 2.7182, 7.3891, 20.0855}; // Valores de Y
int n = x_vals.size(); // Número de puntos

// Función para evaluar el polinomio de Lagrange
double polinomioLagrange(double x) {
    double resultado = 0.0;

    for (int i = 0; i < n; i++) {
        double termino = y_vals[i];
        for (int j = 0; j < n; j++) {
            if (i != j) {
                termino *= (x - x_vals[j]) / (x_vals[i] - x_vals[j]);
            }
        }
        resultado += termino;
    }

    return resultado;
}

// Método de Interpolación de Lagrange
void interpolacionLagrange() {
    double x_eval = 2.5;
    double resultado = polinomioLagrange(x_eval);

    cout << "El valor del polinomio de Lagrange en x = " << x_eval << " es " << resultado << endl;
}

int main() {
    interpolacionLagrange();
    return 0;
}
