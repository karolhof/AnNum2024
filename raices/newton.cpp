#include <iostream>
#include <cmath>
#include <iomanip> // Para controlar la precisión de la salida

using namespace std; // Usar el espacio de nombres estándar
double newtonRaphson(double x0, double tolerancia, int maxIter);

int main() {
    double x0 = 9; // Valor inicial similar al ejemplo de la tabla
    double tolerancia = 0.001; // Tolerancia para la convergencia
    int maxIter = 100; // Número máximo de iteraciones
    
    double raiz = newtonRaphson(x0, tolerancia, maxIter);
    cout << "Aproximación de la raíz: " << raiz << endl;
    
    return 0;
}

// Definir la función de la cual queremos encontrar la raíz
double funcion(double x) {
    return exp(0.1*x) * sin(x); // Ejemplo: f(x) = e^(-x) - x
}

// Definir la derivada de la función
double derivada(double x) {
    return exp(0.1*x) * (0.1 * sin(x) + cos(x)); // Ejemplo: f'(x) = -e^(-x) - 1
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
