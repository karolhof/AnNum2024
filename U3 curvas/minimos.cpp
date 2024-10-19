#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

// Variables globales
vector<double> x_vals = {1, 2, 3, 4, 5, 6, 7}; // Valores de X
vector<double> y_vals = {0.5, 2.5, 2.0, 4.0, 3.5, 6.0, 5.5}; // Valores de Y
int n = x_vals.size(); // Número de puntos

// Función para calcular la regresión lineal
void regresionLineal() {
    double sum_x = 0, sum_y = 0, sum_x2 = 0, sum_xy = 0;

    // Cálculo de sumas necesarias
    for (int i = 0; i < n; i++) {
        sum_x += x_vals[i];
        sum_y += y_vals[i];
        sum_x2 += x_vals[i] * x_vals[i];
        sum_xy += x_vals[i] * y_vals[i];
    }

    // Cálculo de los coeficientes de la recta
    double a1 = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double a0 = (sum_y - a1 * sum_x) / n;

    // Mostrar la tabla y la recta final
    cout << "Tabla de valores y cálculos:\n";
    cout << setw(10) << "Xi" << " | " << setw(10) << "Yi" << " | " << setw(10) << "Xi^2" << " | " << setw(10) << "XiYi" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << x_vals[i] << " | " << setw(10) << y_vals[i] << " | " 
             << setw(10) << x_vals[i] * x_vals[i] << " | " 
             << setw(10) << x_vals[i] * y_vals[i] << endl;
    }

    cout << "\nRecta de regresión: y = " << a0 << " + " << a1 << " * x" << endl;
}

int main() {
    regresionLineal();
    return 0;
}
