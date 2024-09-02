#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>
#include <functional>

using namespace std; // Usar el espacio de nombres estándar

const double EPSILON = 1.0e-3; // Tolerancia para el criterio de parada

// Definir la función de la cual queremos encontrar la raíz
double funcion(double x) {
    return (-23.330) + (79.350 * x) - (88.09 * pow(x, 2)) + (41.6 * pow(x, 3)) - (8.68 * pow(x, 4)) + (0.658 * pow(x, 5));
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

// Implementación del método de la secante con tabla de iteraciones
double metodoSecante(double x0, double x1, double tolerancia, int maxIter) {
    double x2;
    int iter = 0;
    
    // Configurar salida para mostrar números en notación decimal normal con 4 decimales
    cout << fixed << setprecision(4);

    // Imprimir encabezado de la tabla
    cout << setw(5) << "i" 
         << setw(10) << "Xi" 
         << setw(10) << "f(Xi)" 
         << setw(10) << "|E|" 
         << endl;
    cout << string(40, '-') << endl;

    double error = tolerancia + 1; // Iniciar error mayor que tolerancia para entrar en el bucle

    while (iter < maxIter && error > tolerancia) {
        double fx0 = funcion(x0);
        double fx1 = funcion(x1);
        
        if (fabs(fx1 - fx0) < 1e-10) { // Evitar división por cero
            cerr << "Error: denominador muy cercano a cero." << endl;
            return x1;
        }
        
        x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        error = fabs(x2 - x1);

        // Imprimir fila de la tabla
        cout << setw(5) << iter 
             << setw(10) << x1 
             << setw(10) << fx1;
        if (iter == 0) {
            cout << setw(10) << "-" << endl; // En la primera iteración, no hay error previo
        } else {
            cout << setw(10) << error << endl;
        }

        // Actualizar valores para la siguiente iteración
        x0 = x1;
        x1 = x2;
        iter++;
    }

    // Imprimir la raíz encontrada en la última fila

    cout << setw(5) << iter 
         << setw(10) << x2 
         << setw(10) << funcion(x2) 
         << setw(10) << error 
         << "  <- Raíz encontrada" << endl;

    return x2;
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
        double x1 = intervalo.second;
        int maxIter = 100; // Número máximo de iteraciones
        
        // Encontrar la raíz usando el método de la secante
        double raiz = metodoSecante(x0, x1, EPSILON, maxIter);
        cout << "Aproximación de la raíz: " << raiz << endl;
        
        // Pausa antes de buscar la siguiente raíz
        system("pause");
        cout<<endl;
        // Actualizar el valor de start para buscar la siguiente raíz
        start = x1 + increment;
    }

    return 0;
}