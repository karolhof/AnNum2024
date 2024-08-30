#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

// Función para evaluar la función en un punto dado
double evaluarFuncion(const function<double(double)>& funcion, double x) {
    return funcion(x);
}

// Método de Bisección
double biseccion(const function<double(double)>& funcion, double a, double b, double tolerancia) {
    double c;  // Punto medio del intervalo

    // Mientras la mitad del intervalo sea mayor que la tolerancia, seguimos iterando
    while ((b - a) / 2.0 > tolerancia) {
        c = (a + b) / 2.0;  // Calcular el punto medio

        // Si f(c) es exactamente 0, hemos encontrado la raíz
        if (evaluarFuncion(funcion, c) == 0.0) {
            break;
        }
        // Si f(a) y f(c) tienen signos opuestos, la raíz está en [a, c]
        else if (evaluarFuncion(funcion, a) * evaluarFuncion(funcion, c) < 0) {
            b = c;
        }
        // Si no, la raíz está en [c, b]
        else {
            a = c;
        }
    }

    return c;  // Retornar la aproximación de la raíz
}

int main() {
    double longitudIntervalo, tolerancia;
    double dominioInicio = 0.001, dominioFin = 1000.0;  // Definimos el dominio de búsqueda

    auto funcion = [](double x) {
        return (-23.330) + (79.350 * x) - (88.09 * pow(x, 2)) + (41.600 * pow(x, 3)) - (8.68 * pow(x, 4)) + (0.658 * pow(x, 5)); // Definición de la función
    };

    // Solicitar al usuario la longitud del intervalo y la tolerancia de error
    cout << "Método de Bisección para encontrar las raíces de la función.\n";
    cout << "Ingrese la longitud del intervalo de búsqueda: ";
    cin >> longitudIntervalo;

    cout << "Ingrese la tolerancia de error: ";
    cin >> tolerancia;

    double a = dominioInicio;  // Comenzar desde el inicio del dominio
    bool raizEncontrada = false;

    // Recorrer el dominio por intervalos de longitud especificada
    while (a + longitudIntervalo <= dominioFin) {
        double b = a + longitudIntervalo;

        // Verificar si hay un cambio de signo en el intervalo [a, b]
        if (evaluarFuncion(funcion, a) * evaluarFuncion(funcion, b) < 0) {
            // Si hay un cambio de signo, aplicar el método de bisección
            double raiz = biseccion(funcion, a, b, tolerancia);
            cout << "Raíz encontrada en el intervalo [" << a << ", " << b << "]: " << raiz << endl;
            raizEncontrada = true;
        }

        a = b;  // Avanzar al siguiente subintervalo
    }

    // Si no se encuentran raíces, informar al usuario
    if (!raizEncontrada) {
        cout << "No se encontraron raíces en el dominio dado." << endl;
    }

    return 0;
}
