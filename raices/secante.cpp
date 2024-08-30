#include <iostream>
#include <cmath>
#include <iomanip> // Para controlar la precisión de la salida

using namespace std; // Usar el espacio de nombres estándar

// Definir la función de la cual queremos encontrar la raíz
double funcion(double x) {
    return exp(-x) - x; // Ejemplo: f(x) = e^(-x) - x
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
    cout << string(40, '-') << endl;
    cout << setw(5) << iter 
         << setw(10) << x2 
         << setw(10) << funcion(x2) 
         << setw(10) << error 
         << "  <- Raíz encontrada" << endl;

    return x2;
}

int main() {
    double x0 = 0.4; // Primer valor inicial
    double x1 = 0.8; // Segundo valor inicial
    double tolerancia = 0.001; // Tolerancia para la convergencia
    int maxIter = 100; // Número máximo de iteraciones
    
    double raiz = metodoSecante(x0, x1, tolerancia, maxIter);
    cout << "Aproximación de la raíz: " << raiz << endl;
    
    return 0;
}

