#include <iostream>
#include <functional>
#include <cmath>
#include <limits>
#include <vector>

using namespace std;

// Definir la función f(x)
double f(double x) {
    //EJ1
    // return exp(-x) - x;
    //EJ2
    // return -0.874*pow(x,2)+1.750*x+2.627;
    //EJ3
    // return (-23.330) + (79.350 * x) - (88.09 * pow(x, 2)) + (41.6 * pow(x, 3)) - (8.68 * pow(x, 4)) + (0.658 * pow(x, 5));
    //EJ4
    // return ln(x) - 5;
    //EJ5
    // return (1-0.6*x)/x 
}

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

