#include <iostream>
#include <iomanip>
#include<cmath>

using namespace std;

// Declaraciones en el encabezado
const double h = 0.1; // Tamaño del paso
const double xcero = 0.0; // Valor inicial de x
const double ycero = 2.0; // Valor inicial de y
const double x_final = 4.0; // Valor final de x
const int steps = (x_final - xcero) / h + 1; // Número de pasos

// Derivada de la función (definida por el usuario)
double dydx(double x, double y) {
    return (exp(0.8*x))-(0.50*y); // Ejemplo: dy/dx = x * y
}

// Método de Euler
void euler() {
    double x = xcero;
    double y = ycero;

    // Encabezado de la tabla
    cout << setw(5) << "i" << " | " 
         << setw(15) << "xi" << " | " 
         << setw(20) << "y(i+1)" << endl;
    cout << "---------------------------------------------" << endl;

    // Ciclo para el método de Euler
    for (int i = 0; i < steps-1; i++) {
        cout << setw(5) << i << " | "
             << setw(15) << fixed << setprecision(5) << x << " | "
             << setw(20) << y << endl;
        y += dydx(x, y)*h; // Actualización de y
        x += h; // Actualización de x
    }

    // Mostrar el resultado final claramente
    cout << "\nResultado Final:\n";
    cout << "Para x = " << x << ", y (aproximado) = " << fixed << setprecision(5) << y << endl;
}

int main() {
    euler(); // Ejecutar el método de Euler
    return 0;
}
