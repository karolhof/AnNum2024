#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Declaraciones en el encabezado
const double h = 0.2;       // Tamaño del paso
const double xcero = 1.0;   // Valor inicial de x
const double ycero = -2.0;  // Valor inicial de y
const double x_final = 3.0; // Valor final de x
const int steps = (x_final - xcero) / h + 1; // Número de pasos

// Derivada de la función (definida por el usuario)
double dydx(double x, double y) {
    return (1 / x) * (pow(y, 2) + y); // dy/dx = (1/x) * (y^2 + y)
}

// Método de Euler
void euler() {
    double x = xcero;
    double y = ycero;

    // Encabezado de la tabla
    cout << setw(5) << "i" << " | " 
         << setw(15) << "xi" << " | " 
         << setw(20) << "y(i+1)" << endl;
    cout << "------------------------------------------------------------" << endl;

    // Ciclo para el método de Euler
    for (int i = 0; i < steps; i++) {
        double dy = dydx(x, y); // Calcula dy/dx en (x, y)
        
        // Mostrar el cálculo detallado
        cout << setw(5) << i << " | "
             << setw(15) << fixed << setprecision(5) << x << " | "
             << setw(20) << y << "   <- Calculado como: "
             << y << " + (" << dy << " * " << h << ")" << endl;

        // Actualizar y y x para el siguiente paso
        y += dy * h;
        x += h;
    }

    // Mostrar el resultado final claramente
    cout << "\nResultado Final:\n";
    cout << "Para x = " << x - h << ", y (aproximado) = " << fixed << setprecision(5) << y << endl;
}

int main() {
    cout << string(60, '-') << endl;
    cout << "Método de Euler" << endl;
    cout << string(60, '-') << endl;

    euler(); // Ejecutar el método de Euler
    return 0;
}
