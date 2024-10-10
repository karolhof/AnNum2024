#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const double TOLERANCIA = 1.0e-3;
const int MAX_ITERACIONES = 100;

// Función original: f(x) = 2 - (x + 2) / e^x
double f(double x) {
    return 2 - (x + 2) / exp(x);
}

// Derivada de la función: f'(x) = (x + 1) / e^x
double f_prime(double x) {
    return (x + 1) / exp(x);
}

// Segunda derivada de la función: f''(x) = (1 - x) / e^x
double f_double_prime(double x) {
    return (1-x) / exp(x);
}

// Método de Bisección para encontrar un intervalo donde está el mínimo
void buscarIntervaloMinimo(double a, double b) {
    double fa_prime = f_prime(a);
    double fb_prime = f_prime(b);

    if (fa_prime * fb_prime > 0) {
        cout << "No hay cambio de signo en la derivada en este intervalo. Intente con otro intervalo." << endl;
        return;
    }

    cout << "Intervalo inicial: [" << a << ", " << b << "]" << endl;

    int iteraciones = 0;
    while (fabs(b - a) > TOLERANCIA) {
        double c = (a + b) / 2.0;
        double fc_prime = f_prime(c);

        cout << "Iteración " << ++iteraciones << ": " << endl;
        cout << "  a = " << a << ", b = " << b << ", c = " << c << endl;
        cout << "  f'(a) = " << fa_prime << ", f'(b) = " << fb_prime << ", f'(c) = " << fc_prime << endl;

        if (fa_prime * fc_prime < 0) {
            b = c; // El cambio de signo está en el intervalo [a, c]
            fb_prime = fc_prime;
        } else {
            a = c; // El cambio de signo está en el intervalo [c, b]
            fa_prime = fc_prime;
        }

        cout << "  Nuevo intervalo: [" << a << ", " << b << "]" << endl << endl;
    }

    cout << "Intervalo encontrado donde está el mínimo: [" << a << ", " << b << "]" << endl << endl;
}

// Método de Newton para refinar el mínimo
double newton(double x0) {
    int iteraciones = 0;
    double x = x0;
    double error = fabs(f_prime(x));

    cout << "Método de Newton:" << endl;

    while (error > TOLERANCIA && iteraciones < MAX_ITERACIONES) {
        double x_new = x - f_prime(x) / f_double_prime(x); // Newton's update
        error = fabs(x_new - x);

        cout << "Iteración " << ++iteraciones << ": " << endl;
        cout << "  x = " << x << ", f'(x) = " << f_prime(x) << ", f''(x) = " << f_double_prime(x) << endl;
        cout << "  x_new = " << x_new << ", error = " << error << endl << endl;

        x = x_new;
    }

    if (iteraciones == MAX_ITERACIONES) {
        cout << "El método de Newton no ha convergido tras " << MAX_ITERACIONES << " iteraciones." << endl;
    } else {
        cout << "Mínimo encontrado en x = " << setprecision(6) << x << " después de " << iteraciones << " iteraciones." << endl;
        cout << "Valor de f(x) en el mínimo: " << setprecision(6) << f(x) << endl;
    }

    return x;
}

int main() {
    cout<<"ingrese el intervalo [a,b] donde se buscará el mínimo: ";
    double a, b;
    cin >> a >> b;
    // Paso 1: Búsqueda del intervalo mediante el método de Bisección
    buscarIntervaloMinimo(a, b);

    // Paso 2: Aplicar el método de Newton a un punto inicial cercano al mínimo
    double x0 = (a + b) / 2.0;
    double minimo = newton(x0);

    return 0;
}