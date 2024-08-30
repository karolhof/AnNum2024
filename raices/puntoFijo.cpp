#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

using namespace std;

// Función recursiva para ejecutar el método de punto fijo
void punto_fijo_recursivo(function<double(double)> g, double Xi, double tol, int iteracion, int max_iter) {
    double gx = g(Xi);
    double error = fabs(gx - Xi);

    // Imprimir los resultados de la iteración actual
    cout << setw(10) << iteracion
         << setw(15) << Xi 
         << setw(15) << gx 
         << setw(15) << error << endl;

    // Condición de parada por tolerancia o máximo de iteraciones
    if (error < tol || iteracion >= max_iter) {
        cout << "------------------------------------------\n";
        cout << "Última iteración:\n";
        cout << setw(10) << iteracion
             << setw(15) << Xi 
             << setw(15) << gx 
             << setw(15) << error << endl;
        cout << "------------------------------------------\n";
        return;
    }

    punto_fijo_recursivo(g, gx, tol, iteracion + 1, max_iter);
}

int main() {
    cout << "Elige una función predefinida:\n";
    cout << "1. g(x) = cos(x)\n";
    cout << "2. g(x) = exp(-x)\n";
    cout << "3. g(x) = (1 + x) / 2\n";
    cout << "4. Introducir una función modificar el código.\n";
    int opcion;
    cin >> opcion;

    function<double(double)> g;

    switch (opcion) {
        case 1:
            g = [](double x) { return cos(x); };
            break;
        case 2:
            g = [](double x) { return exp(-x); };
            break;
        case 3:
            g = [](double x) { return (1 + x) / 2; };
            break;
        case 4:
            g = [](double x) { return exp(5); };
            break;
        default:
            cout << "Opción no válida.\n";
            return 0;
    }

    double x0;
    cout << "Introduce el valor inicial x0: ";
    cin >> x0;

    double tol;
    cout << "Introduce la tolerancia (error): ";
    cin >> tol;

    // Imprimir la cabecera de la tabla
    cout << setw(10) << "Iteración" 
         << setw(15) << "Xi" 
         << setw(15) << "g(Xi)" 
         << setw(15) << "Error" << endl;

    // Ejecutar el método de punto fijo recursivo
    punto_fijo_recursivo(g, x0, tol, 1, 100);

    return 0;
}