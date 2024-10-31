#include <iostream>
#include <iomanip>
#include <cmath>
#include <functional>

using namespace std;

// Parámetros de la integral
const double b = 5;            // Límite superior de integración
const double a = 0;            // Límite inferior de integración
const int n = 10;              // Número de subintervalos (par)

// Función que quieres integrar
double funcion(double x) {
    return 2 - ((x + 2) / exp(x));  // Puedes cambiarla por cualquier otra función
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
         << setw(10) << "Peso" << " | "
         << setw(20) << "Cálculo de Término" << " | "
         << setw(20) << "Suma Acumulada" << " | " << endl;
    cout << string(110, '-') << endl;

    // Mostrar la fila para x0
    cout << setw(10) << 0 << " | "
         << setw(15) << fixed << setprecision(5) << a << " | "
         << setw(15) << f(a) << " | "
         << setw(10) << 1 << " | "
         << setw(20) << f(a) << " | "
         << setw(20) << f(a) << " | " << endl;

    // Suma acumulada
    double acumulada = f(a);

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        int peso = (i % 2 == 0) ? 2 : 4;
        double termino = peso * f(x);
        acumulada += termino;

        // Mostrar las filas para los valores intermedios con el formato solicitado
        cout << setw(10) << i << " | "
             << setw(15) << fixed << setprecision(5) << x << " | "
             << setw(15) << f(x) << " | "
             << setw(10) << peso << " | "
             << setw(20) << termino << " | "
             << setw(20) << acumulada << " | " << endl;
    }
    
    // Mostrar la fila para xn
    cout << setw(10) << n << " | "
         << setw(15) << fixed << setprecision(5) << b << " | "
         << setw(15) << f(b) << " | "
         << setw(10) << 1 << " | "
         << setw(20) << f(b) << " | "
         << setw(20) << acumulada + f(b) << " | " << endl;

    cout << string(110, '-') << endl;

    // Resultado final de la integral aplicando la fórmula de Simpson
    double resultado_final = (h / 3) * (acumulada + f(b));
    cout << "\nCálculo final: (" << h << " / 3) * " << acumulada + f(b)
         << " = " << fixed << setprecision(5) << resultado_final << endl;

    return resultado_final;
}

int main() {
    cout << string(60, '-') << endl;
    cout << "Método de Simpson" << endl;
    cout << string(60, '-') << endl;

    // Llamada al método de Simpson y resultado
    double resultado = simpson(a, b, n, funcion);

    // Mostrar el resultado final
    cout << "\nLa aproximación final de la integral es: " << fixed << setprecision(5) << resultado << endl;

    return 0;
}