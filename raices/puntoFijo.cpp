#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>
#include <limits>

using namespace std;

const double EPSILON = 1.0e-3; // Tolerancia para el criterio de parada
const int MAX_ITER = 100; // Número máximo de iteraciones para validación
const double ERROR_THRESHOLD = 1.0e-6; // Umbral para la validación de convergencia

// Función para encontrar intervalos con cambio de signo
pair<double, double> findSignChangeInterval(function<double(double)> f, double start, double end, double increment) {
    double x1 = start;
    double f1 = f(x1);

    while (x1 < end) {
        double x2 = x1 + increment;
        double f2 = f(x2);

        if (f1 * f2 < 0) {
            return {x1, x2};
        }

        x1 = x2;
        f1 = f2;
    }

    return {numeric_limits<double>::quiet_NaN(), numeric_limits<double>::quiet_NaN()};
}

// Verificar la condición de convergencia para el método de punto fijo
bool validateConvergence(function<double(double)> g, double a, double b) {
    const double h = 1.0e-6; // Tamaño de paso para la derivada numérica

    // Verificar que g(a, b) está en (a, b)
    double ga = g(a);
    double gb = g(b);
    if (ga < a || ga > b || gb < a || gb > b) {
        cerr << "La función g(x) no mapea el intervalo [a, b] dentro de (a, b)." << endl;
        return false;
    }

    // Verificar que |g'(x)| < 1
    for (double x = a; x <= b; x += (b - a) / 100) {
        double gx = g(x);
        double g_prime = (g(x + h) - g(x - h)) / (2 * h); // Derivada numérica
        if (fabs(g_prime) >= 1) {
            cerr << "La derivada |g'(x)| >= 1 en x = " << x << ". El método puede no converger." << endl;
            return false;
        }
    }

    return true;
}

// Función para ejecutar el método de punto fijo con validación de convergencia
bool punto_fijo_recursivo(function<double(double)> g, double Xi, double tol, int iteracion, int max_iter) {
    double gx = g(Xi);
    double error = fabs(gx - Xi);
    double prev_error = numeric_limits<double>::max(); // Inicializar error previo

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
        cout << "Raíz: " << gx << endl;
        cout << "------------------------------------------\n";
        system("pause"); // Pausar para que el usuario pueda ver los resultados
        return error < tol; // Retornar si la convergencia se logró
    }

    // Validación de convergencia
    bool convergencia = punto_fijo_recursivo(g, gx, tol, iteracion + 1, max_iter);

    // Verificar la convergencia basándose en la comparación de errores en las últimas iteraciones
    if (iteracion >= (max_iter - 10)) {
        double current_error = fabs(gx - g(gx));
        if (prev_error - current_error < ERROR_THRESHOLD) {
            cerr << "Advertencia: El método de punto fijo puede no estar convergiendo." << endl;
            cerr << "El error no disminuye significativamente en las últimas iteraciones." << endl;
            return false; // Retornar si la convergencia no se logró
        }
        prev_error = current_error;
    }

    return convergencia;
}

int main() {
    cout << "Método de Punto Fijo\n";
    
    // Definir una función g(x) adecuada para el método de punto fijo
    function<double(double)> g;
    g = [](double x) { 
        return 0.5 * (23.330 + 88.09 * pow(x, 2) - 79.350 * x - 41.6 * pow(x, 3) + 8.68 * pow(x, 4)) / 0.658;
    };

    double start, end, increment;
    cout << "Introduce el valor inicial del dominio: ";
    cin >> start;
    cout << "Introduce el valor final del dominio: ";
    cin >> end;
    cout << "Introduce el incremento para buscar el cambio de signo: ";
    cin >> increment;

    // Encontrar intervalos con cambio de signo
    pair<double, double> interval = findSignChangeInterval(g, start, end, increment);

    if (isnan(interval.first)) {
        cout << "No se encontró un cambio de signo en el intervalo especificado." << endl;
    } else {
        while (!isnan(interval.first)) {
            cout << "Intervalo con cambio de signo: [" << interval.first << ", " << interval.second << "]\n";

            // Verificar la convergencia antes de aplicar el método
            if (!validateConvergence(g, interval.first, interval.second)) {
                cerr << "La función g(x) no cumple con las condiciones de convergencia en el intervalo [" << interval.first << ", " << interval.second << "]." << endl;
                break;
            }

            // Ejecutar el método de punto fijo en el intervalo encontrado
            cout << setw(10) << "Iteración" 
                 << setw(15) << "Xi" 
                 << setw(15) << "g(Xi)" 
                 << setw(15) << "Error" << endl;

            bool convergencia = punto_fijo_recursivo(g, interval.first, EPSILON, 1, MAX_ITER);

            if (!convergencia) {
                cerr << "El método no converge en el intervalo [" << interval.first << ", " << interval.second << "]." << endl;
                break; // Terminar el programa si no hay convergencia
            }

            // Buscar el siguiente intervalo
            interval = findSignChangeInterval(g, interval.second, end, increment);
        }
    }

    return 0;
}
