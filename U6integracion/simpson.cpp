#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>

using namespace std;

// Parámetros de la integral
const double a = 0;               // Límite inferior de integración
const double b = M_PI;            // Límite superior de integración
const int n = 10;                 // Número de subintervalos (par)

// Función que quieres integrar
double funcion(double x) {
    return sin(x);  // Puedes cambiarla por cualquier otra función
}

// Función que implementa el método de Simpson
double simpson(double a, double b, int n, function<double(double)> f) {
    if (n % 2 != 0) {
        n++;  // Simpson requiere un número par de subintervalos
    }
    
    double h = (b - a) / n;  // Ancho de cada subintervalo
    double sum = f(a) + f(b);

    // Mostrar encabezado de la tabla con el formato solicitado
    cout << setw(10) << "i" << " | "
         << setw(15) << "xi" << " | "
         << setw(15) << "f(xi)" << " | "
         << setw(15) << "Peso" << " | " << endl;
    cout << string(78, '-') << endl;

    // Mostrar la fila para x0
    cout << setw(10) << 0 << " | "
         << setw(15) << fixed << setprecision(5) << a << " | "
         << setw(15) << f(a) << " | "
         << setw(15) << 1 << " | " << endl;

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        int peso = (i % 2 == 0) ? 2 : 4;
        sum += peso * f(x);
        
        // Mostrar las filas para los valores intermedios con el formato solicitado
        cout << setw(10) << i << " | "
             << setw(15) << fixed << setprecision(5) << x << " | "
             << setw(15) << f(x) << " | "
             << setw(15) << peso << " | " << endl;
    }
    
    // Mostrar la fila para xn
    cout << setw(10) << n << " | "
         << setw(15) << fixed << setprecision(5) << b << " | "
         << setw(15) << f(b) << " | "
         << setw(15) << 1 << " | " << endl;

    cout << string(78, '-') << endl;

    return (h / 3) * sum;
}

int main() {
    cout<<endl;
    cout<<string(30,'-')<<"Método de Simpson"<<string(30,'-')<<endl;
    cout<<endl;

    // Llamada al método de Simpson y resultado
    double resultado = simpson(a, b, n, funcion);

    // Mostrar el resultado final
    cout << "\nLa aproximación final de la integral es: " << fixed << setprecision(5) << resultado << endl;

    return 0;
}
