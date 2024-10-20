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

// Función para derivada con fórmula de cinco puntos progresiva
double derivadaCincoPuntosProgresiva(int i) {
    if (i < n - 4) {
        return (-25 * fxi[i] + 48 * fxi[i + 1] - 36 * fxi[i + 2] + 16 * fxi[i + 3] - 3 * fxi[i + 4]) / (12 * h);
    } else {
        return NAN;
    }
}

// Función para derivada con fórmula de cinco puntos centrada
double derivadaCincoPuntosCentrada(int i) {
    if (i >= 2 && i < n - 2) {
        return (fxi[i - 2] - 8 * fxi[i - 1] + 8 * fxi[i + 1] - fxi[i + 2]) / (12 * h);
    } else {
        return NAN;
    }
}

// Función para derivada con fórmula de cinco puntos regresiva
double derivadaCincoPuntosRegresiva(int i) {
    if (i >= 4) {
        return (25 * fxi[i] - 48 * fxi[i - 1] + 36 * fxi[i - 2] - 16 * fxi[i - 3] + 3 * fxi[i - 4]) / (12 * h);
    } else {
        return NAN;
    }
}

// Función para imprimir la tabla
void imprimirTablaCincoPuntos() {
    cout << setw(10) << "Xi" << " | "
         << setw(10) << "f(Xi)" << " | "
         << setw(10) << "Progresiva" << " | "
         << setw(10) << "Centrada" << " | "
         << setw(10) << "Regresiva" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < n; i++) {
        double progresiva = derivadaCincoPuntosProgresiva(i);
        double centrada = derivadaCincoPuntosCentrada(i);
        double regresiva = derivadaCincoPuntosRegresiva(i);

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
    cout << "Derivadas con fórmula de cinco puntos" << endl;
    cout << string(60, '-') << endl;
    imprimirTablaCincoPuntos();

    return 0;
}
