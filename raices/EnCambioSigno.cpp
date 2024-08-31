#include <iostream>
#include <functional>
#include <cmath>
#include <limits>

using namespace std;

// Función para encontrar el intervalo donde f(x) cambia de signo
pair<double, double> findSignChangeInterval(function<double(double)> f, double start, double increment, int maxSteps) {
    double x1 = start;
    double f1 = f(x1);
    
    for (int i = 0; i < maxSteps; ++i) {
        double x2 = x1 + increment;
        double f2 = f(x2);

        if (f1 * f2 < 0) {
            // Se encontró un cambio de signo
            return {x1, x2};
        }

        // Actualizar para la siguiente iteración
        x1 = x2;
        f1 = f2;
    }

    // Si no se encuentra un cambio de signo
    return {std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::quiet_NaN()};
}

int main() {
    // Definir la función a evaluar, por ejemplo f(x) = x^2 - 4
    auto f = [](double x) {
        return exp(-x) - x;
    };

    // Pedir al usuario el valor inicial y el incremento
    double start, increment;
    int maxSteps;
    
    cout << "Ingresa el valor inicial: ";
    cin >> start;
    
    cout << "Ingresa el incremento: ";
    cin >> increment;

    cout << "Ingresa el número máximo de pasos: ";
    cin >> maxSteps;

    // Llamar a la función para encontrar el intervalo donde cambia el signo
    pair<double, double> interval = findSignChangeInterval(f, start, increment, maxSteps);

    if (isnan(interval.first)) {
        cout << "No se encontró un cambio de signo en el intervalo especificado." << endl;
    } else {
        cout << "El cambio de signo ocurre entre " << interval.first << " y " << interval.second << "." << endl;
    }

    return 0;
}
