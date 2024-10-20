#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Constantes en el encabezado
const double h = 0.1; // Paso
double xi[] = {0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7}; // Puntos
const int n = sizeof(xi) / sizeof(xi[0]); // Número de puntos

// Función modificable por el usuario
double f(double x) {
    return exp(x) * cos(x); // Ejemplo de función: exp(x) * cos(x)
}

// Vector fxi que se carga automáticamente con los valores evaluados de f en xi
double fxi[n];

// Función para cargar los valores de f en fxi
void cargarValores() {
    for (int i = 0; i < n; i++) {
        fxi[i] = f(xi[i]);
    }
}

// Función para derivada con fórmula de tres puntos progresiva
double derivadaTresPuntosProgresiva(int i) {
    if (i < n - 2) {
        return (-3 * fxi[i] + 4 * fxi[i + 1] - fxi[i + 2]) / (2 * h);
    } else {
        return NAN;
    }
}

// Función para derivada con fórmula de tres puntos centrada
double derivadaTresPuntosCentrada(int i) {
    if (i >= 1 && i < n - 1) {
        return (fxi[i + 1] - fxi[i - 1]) / (2 * h);
    } else {
        return NAN;
    }
}

// Función para derivada con fórmula de tres puntos regresiva
double derivadaTresPuntosRegresiva(int i) {
    if (i >= 2) {
        return (3 * fxi[i] - 4 * fxi[i - 1] + fxi[i - 2]) / (2 * h);
    } else {
        return NAN;
    }
}

// Función para imprimir la tabla
void imprimirTablaTresPuntos() {
    cout << setw(10) << "Xi" << " | "
         << setw(10) << "f(Xi)" << " | "
         << setw(10) << "Progresiva" << " | "
         << setw(10) << "Centrada" << " | "
         << setw(10) << "Regresiva" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < n; i++) {
        double progresiva = derivadaTresPuntosProgresiva(i);
        double centrada = derivadaTresPuntosCentrada(i);
        double regresiva = derivadaTresPuntosRegresiva(i);

        cout << setw(10) << xi[i] << " | "
             << setw(10) << fxi[i] << " | "
             << setw(10) << (isnan(progresiva) ? "N/A" : to_string(progresiva)) << " | "
             << setw(10) << (isnan(centrada) ? "N/A" : to_string(centrada)) << " | "
             << setw(10) << (isnan(regresiva) ? "N/A" : to_string(regresiva)) << endl;
    }
}

int main() {
    // Cargar los valores de f en fxi
    cargarValores();

    // Imprimir la tabla de derivadas
    cout << string(60, '-') << endl;
    cout << "Derivadas con fórmula de tres puntos" << endl;
    cout << string(60, '-') << endl;
    imprimirTablaTresPuntos();

    return 0;
}
