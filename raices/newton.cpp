#include <iostream>
#include <cmath>
#include <iomanip> // Para controlar la precisión de la salida

using namespace std; // Usar el espacio de nombres estándar
double newtonRaphson(double x0, double tolerancia, int maxIter);

int main() {
    double x0 = 3; // Valor inicial similar al ejemplo de la tabla
    double tolerancia = 0.001; // Tolerancia para la convergencia
    int maxIter = 100; // Número máximo de iteraciones
    
    double raiz = newtonRaphson(x0, tolerancia, maxIter);
    cout << "Aproximación de la raíz: " << raiz << endl;
    
    return 0;
}

// Definir la función de la cual queremos encontrar la raíz
double funcion(double x) {
    return (-23.330) + (79.350 * x) - (88.09 * pow(x, 2)) + (41.6 * pow(x, 3)) - (8.68 * pow(x, 4)) + (0.658 * pow(x, 5));
}

// Definir la derivada de la función
double derivada(double x) {
    return 79.350 - 176.18 * x + 124.8 * pow(x, 2) - 34.4 * pow(x, 3) + 3.29 * pow(x, 4);
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
