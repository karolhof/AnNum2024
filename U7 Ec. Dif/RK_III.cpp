#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Definición de las variables globales
double xcero = 0.0;  // Valor inicial de x
double ycero = 2.0;  // Valor inicial de y
double xfinal = 4.0; // Valor final de x
double h = 0.1;      // Paso
int steps = static_cast<int>((xfinal - xcero) / h); // Número de pasos

// Función que define la ecuación diferencial
double dydx(double x, double y) {
    return exp(0.8 * x) - 0.5 * y; // Ecuación diferencial
}

// Método de Runge-Kutta de tercer orden
void rungeKutta() {
    double x = xcero;
    double y = ycero;

    // Encabezado de la tabla
    cout << setw(5) << "i" << " | "
         << setw(15) << "xi" << " | "
         << setw(15) << "yi" << " | "
         << setw(15) << "k1" << " | "
         << setw(15) << "k2" << " | "
         << setw(15) << "k3" << " | "
         << setw(15) << "y(i+1)" << endl;

    cout << string(100, '-') << endl;

    // Ciclo para el método de Runge-Kutta de tercer orden
    for (int i = 0; i <= steps; i++) {
        // Calculo de k1
        double k1 = dydx(x, y);
        // Calculo de k2
        double k2 = dydx(x + h / 2, y + (h*k1) / 2);
        // Calculo de k3
        double k3 = dydx(x + h, y - (h*k1) + (2*h*k2));

        // Mostrar la fila de la tabla
        cout << setw(5) << i << " | "
             << setw(15) << fixed << setprecision(5) << x << " | "
             << setw(15) << fixed << setprecision(5) << y << " | "
             << setw(15) << fixed << setprecision(5) << k1 << " | "
             << setw(15) << fixed << setprecision(5) << k2 << " | "
             << setw(15) << fixed << setprecision(5) << k3 << " | ";

        // Calcular el nuevo valor de y
        y = y + ((k1 + 4 * k2 + k3) / 6)*h; // Actualiza y utilizando la combinación de k1, k2, k3

        // Actualizar el valor de x
        x = x + h; // Incrementa x

        // Mostrar el nuevo valor de y
        cout << setw(15) << fixed << setprecision(5) << y << endl;
    }
}

// Función principal
int main() {
    rungeKutta(); // Llamada al método Runge-Kutta de tercer orden
    return 0;
}
