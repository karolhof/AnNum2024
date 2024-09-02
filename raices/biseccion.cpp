#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

const double EPSILON = 1.0e-3;  // Tolerancia para el método de bisección

// Definición de la función a evaluar
double f(double x) {
    //EJ1
    // return exp(-x) - x;
    //EJ2
    // return -0.874*pow(x,2)+1.750*x+2.627;
    //EJ3
    // return (-23.330) + (79.350 * x) - (88.09 * pow(x, 2)) + (41.6 * pow(x, 3)) - (8.68 * pow(x, 4)) + (0.658 * pow(x, 5));
    //EJ4
    // return log(x) - 5;
    //EJ5
    // return (1-0.6*x)/x;
}

// Función para encontrar los intervalos donde f(x) cambia de signo
vector<pair<double, double>> findSignChangeIntervals(function<double(double)> f, double start, double end, double increment) {
    vector<pair<double, double>> intervals;
    double x1 = start;
    double f1 = f(x1);

    while (x1 < end) {
        double x2 = x1 + increment;
        if (x2 > end) x2 = end; // Asegurar que el último intervalo sea exactamente hasta 'end'
        double f2 = f(x2);

        if (f1 * f2 < 0) {
            intervals.push_back({x1, x2});
        }

        // Actualizar para la siguiente iteración
        x1 = x2;
        f1 = f2;
    }

    return intervals;
}

// Función para encontrar la raíz en un intervalo usando el método de bisección
double bisection(const function<double(double)>& funcion, double a, double b, double tolerancia) {
    double fa = funcion(a);
    double fb = funcion(b);

    // Verificar si el intervalo inicial contiene un cambio de signo
    if (fa * fb > 0) {
        cerr << "Error: No hay cambio de signo en el intervalo dado [" << a << ", " << b << "]." << endl;
        return numeric_limits<double>::quiet_NaN();
    }

    double c;
    while ((b - a) / 2.0 > tolerancia) {
        c = (a + b) / 2.0;  // Calcular el punto medio
        double fc = funcion(c);

        // Si f(c) es exactamente 0, hemos encontrado la raíz
        if (fc == 0.0 || fabs(b - a) < tolerancia) {
            return c;
        } else if (fa * fc < 0) {
            b = c;
            fb = fc;
        } else {
            a = c;
            fa = fc;
        }
    }

    return (a + b) / 2.0;
}

// Función principal para encontrar todas las raíces en un intervalo dado
vector<double> findAllRoots(function<double(double)> f, double start, double end, double increment) {
    vector<double> roots;

    // Encontrar todos los intervalos donde hay un cambio de signo
    vector<pair<double, double>> intervals = findSignChangeIntervals(f, start, end, increment);

    // Aplicar el método de bisección en cada intervalo encontrado
    for (const auto& interval : intervals) {
        double root = bisection(f, interval.first, interval.second, EPSILON);
        if (!isnan(root)) {
            // Evitar duplicados con un pequeño margen
            bool isDuplicate = false;
            for (const auto& r : roots) {
                if (fabs(r - root) < EPSILON) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                roots.push_back(root);
            }
        }
    }

    return roots;
}

int main() {
    // Pedir al usuario el intervalo de búsqueda y el incremento
    double start, end, increment;
    
    cout << "Ingresa el valor inicial del intervalo: ";
    cin >> start;
    
    cout << "Ingresa el valor final del intervalo: ";
    cin >> end;

    cout << "Ingresa el incremento: ";
    cin >> increment;

    // Llamar a la función para encontrar todas las raíces en el intervalo
    vector<double> roots = findAllRoots(f, start, end, increment);

    // Mostrar los resultados
    cout << "Raíces encontradas:" << endl;
    if (roots.empty()) {
        cout << "No se encontraron raíces en el intervalo especificado." << endl;
    } else {
        for (size_t i = 0; i < roots.size(); ++i) {
            cout << "Raíz " << i + 1 << " = " << roots[i] << endl;
        }
    }

    return 0;
}