#include <iostream>
#include <functional>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

// Función para encontrar todos los intervalos donde f(x) cambia de signo
vector<pair<double, double>> findSignChangeIntervals(function<double(double)> f, double start, double end, double increment) {
    vector<pair<double, double>> intervals;
    double x1 = start;
    double f1 = f(x1);

    while (x1 < end) {
        double x2 = x1 + increment;
        if (x2 > end) {
            x2 = end;
        }
        double f2 = f(x2);

        if (f1 * f2 < 0) {
            // Se encontró un cambio de signo
            intervals.push_back({x1, x2});
        }

        // Actualizar para la siguiente iteración
        x1 = x2;
        f1 = f2;
    }

    return intervals;
}

int main() {
    // Definir la función a evaluar, por ejemplo f(x) = exp(-x) - x
    auto f = [](double x) {
        return (-23.330) + (79.350 * x) - (88.09 * pow(x, 2)) + (41.6 * pow(x, 3)) - (8.68 * pow(x, 4)) + (0.658 * pow(x, 5));
    };

    // Pedir al usuario los valores inicial, final e incremento
    double start, end, increment;
    
    cout << "Ingresa el valor inicial: ";
    cin >> start;
    
    cout << "Ingresa el valor final: ";
    cin >> end;
    
    cout << "Ingresa el incremento: ";
    cin >> increment;

    // Llamar a la función para encontrar los intervalos donde cambia el signo
    vector<pair<double, double>> intervals = findSignChangeIntervals(f, start, end, increment);

    if (intervals.empty()) {
        cout << "No se encontraron cambios de signo en el intervalo especificado." << endl;
    } else {
        cout << "Se encontraron cambios de signo en los siguientes intervalos:" << endl;
        for (const auto& interval : intervals) {
            cout << "Entre " << interval.first << " y " << interval.second << "." << endl;
        }
    }

    return 0;
}
