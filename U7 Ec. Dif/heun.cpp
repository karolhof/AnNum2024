#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Declaraciones en el encabezado
const double h = 0.1; // Tamaño del paso
const double xcero = 0.0; // Valor inicial de x
const double ycero = 2.0; // Valor inicial de y
const double x_final = 4.0; // Valor final de x
const int steps = static_cast<int>((x_final - xcero) / h); // Número de pasos

// Derivada de la función (definida por el usuario)
double dydx(double x, double y) {
    return exp(0.8 * x) - 0.50 * y; // Ejemplo: dy/dx = e^(0.8x) - 0.50*y
}

// Método de Heun
void heun() {
    double x = xcero;
    double y = ycero;
    double y_predict; // Variable para el valor predictivo

    // Encabezado de la tabla
    cout << setw(5) << "i" << " | " 
         << setw(15) << "xi" << " | " 
         << setw(20) << "y^0(i+1)" << " | "
         << setw(20) << "y(i+1)" << " |" << endl;
    cout << "---------------------------------------------------------------" << endl;

    // Ciclo para el método de Heun
    int i = 0;
    while (x < x_final) { // Mantener x < x_final
        // Mostrar la fila de la tabla
        if (i > 0) {
            cout << setw(5) << i << " | "
                 << setw(15) << fixed << setprecision(5) << x << " | "
                 << setw(20) << fixed << setprecision(5) << y_predict << " | "
                 << setw(20) << fixed << setprecision(5) << y << " |" << endl;
        }

        // Predicción con Euler (y^0(i+1))
        y_predict = y + h * dydx(x, y); // Asignar valor a y_predict

        // Calcular el siguiente x
        double x_next = x + h;

        // Corrección con Heun (y(i+1))
        y = y + ((dydx(x, y) + dydx(x_next, y_predict)) / 2.0) * h;

        // Actualización de x
        x = x_next;
        i++;
    }

    // Asegurarse de que se imprima x_final correctamente
    cout << setw(5) << i << " | "
         << setw(15) << fixed << setprecision(5) << x_final << " | "
         << setw(20) << fixed << setprecision(5) << y_predict << " | "
         << setw(20) << fixed << setprecision(5) << y << " |" << endl;

    // Mostrar el resultado final claramente
    cout << "\nResultado Final:\n";
    cout << "Para x = " << fixed << setprecision(5) << x_final 
         << ", y (Euler) = " << fixed << setprecision(5) << y_predict 
         << ", y (Heun) = " << fixed << setprecision(5) << y << endl;
}

int main() {

    cout << string(60, '-') << endl;
    cout << "Método de Hunn" << endl;
    cout << string(60, '-') << endl;

    heun(); // Ejecutar el método de Heun
    return 0;
}
