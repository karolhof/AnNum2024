#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <functional>

using namespace std; // Usar el espacio de nombres estándar

const double EPSILON = 1.0e-3; // Tolerancia para el criterio de parada

// Definir la función de la cual queremos encontrar la raíz
double funcion(double x) {
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

// Definir la derivada de la función
double derivada(double x) {
    //EJ1
    // return -exp(-x) - 1;
    //EJ2
    // return -1.748*x + 1.750;
    //EJ3
    // return 79.350 - 176.18*x + 124.8*pow(x, 2) - 34.72*pow(x, 3) + 3.29*pow(x, 4);
    //EJ4
    // return 1/x;
    //EJ5
    // return -1 / (x * x);
}

// Función para encontrar un intervalo donde ocurre un cambio de signo
pair<double, double> findSignChangeInterval(function<double(double)> f, double start, double end, double increment) {
    double x1 = start;
    double f1 = f(x1);
    
    while (x1 <= end) {
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

// Implementación del método de Newton-Raphson con tabla de iteraciones
double newtonRaphson(double x0, double tolerancia, int maxIter) {
    double x = x0;
    int iter = 0;
    
    // Configurar salida para mostrar números en notación decimal normal con 4 decimales
    cout << fixed << setprecision(4);

    // Imprimir encabezado de la tabla
    cout << setw(5) << "i" 
         << setw(10) << "Xi" 
         << setw(10) << "f(Xi)" 
         << setw(10) << "f'(Xi)" 
         << setw(10) << "|E|" 
         << endl;
    cout << string(45, '-') << endl;
    
    double error = tolerancia + 1; // Iniciar error mayor que tolerancia para entrar en el bucle

    while (iter < maxIter && error > tolerancia) {
        double fx = funcion(x);
        double dfx = derivada(x);
        
        if (fabs(dfx) < 1e-10) { // Evitar división por cero
            cerr << "Error: derivada muy cercana a cero." << endl;
            return x;
        }
        
        double xNuevo = x - fx / dfx;
        error = fabs(xNuevo - x);
        
        // Imprimir fila de la tabla
        cout << setw(5) << iter 
             << setw(10) << x 
             << setw(10) << fx 
             << setw(10) << dfx;
        
        if (iter == 0) {
            cout << setw(10) << "-" << endl;
        } else {
            cout << setw(10) << error << endl;
        }
        
        x = xNuevo;
        iter++;
    }
    
    if (error <= tolerancia) {
        cout << "Raíz encontrada: " << x << " en " << iter << " iteraciones." << endl;
    } else {
        cerr << "El método no converge después de " << maxIter << " iteraciones." << endl;
    }
    
    return x;
}

int main() {
    double start, end, increment;
    
    cout << "Ingresa el valor inicial del dominio: ";
    cin >> start;
    cout << "Ingresa el valor final del dominio: ";
    cin >> end;
    cout << "Ingresa el incremento para buscar el cambio de signo: ";
    cin >> increment;

    while (start < end) {
        // Buscar un intervalo con cambio de signo
        auto intervalo = findSignChangeInterval(funcion, start, end, increment);
        
        if (isnan(intervalo.first) || isnan(intervalo.second)) {
            cerr << "No se encontraron más raíces en el intervalo especificado." << endl;
            break;
        }

        double x0 = intervalo.first;
        int maxIter = 100; // Número máximo de iteraciones
        
        // Encontrar la raíz usando el método de Newton-Raphson
        double raiz = newtonRaphson(x0, EPSILON, maxIter);
        cout << "Aproximación de la raíz: " << raiz << endl;
        
        // Pausa antes de buscar la siguiente raíz
        system("pause");
        
        // Actualizar el valor de start para buscar la siguiente raíz
        start = intervalo.second + increment;
    }

    return 0;
}
