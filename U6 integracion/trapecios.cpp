#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>  // Para la tabla

using namespace std;

// Constantes definidas en el encabezado para fácil acceso
const double b = 5;                // Límite superior de integración
const double a = -3;               // Límite inferior de integración
const int tramos = 10;             // Número de tramos para la integración por trapecios

// Puntos de muestra
const vector<double> xi = {1.0, 1.5, 2.0, 2.5, 3.0};
const vector<double> fi = {0.84147098, 1.22167687, 1.28594075, 0.94626755, 0.24442702};

// Función fx (modificable)
double fx(double x) {
    // return 8 + 5 * cos(x);    
    return 1 - x - 4 * pow(x, 3) + 3 * pow(x, 5);
    // return sin(5*x+1);
    // return x*exp(2*x);
}

// Regla de Trapecios para una función fx con salida detallada
double reglaTrapecios(double a, double b, int tramos) {
    double h = (b - a) / tramos;
    double xi = a;
    double suma = fx(xi);
    
    // Cabecera de la tabla
    cout << setw(10) << "x" << " | "
         << setw(15) << "f(x)" << " | "
         << setw(15) << "suma parcial" << " | " << endl;
    cout << "---------------------------------------------------" << endl;
    cout << setw(10) << xi << " | " 
         << setw(15) << fx(xi) << " | " 
         << setw(15) << suma << " | " << endl;

    for (int i = 0; i < tramos - 1; ++i) {
        xi += h;
        suma += 2 * fx(xi);
        cout << setw(10) << xi << " | " 
             << setw(15) << fx(xi) << " | " 
             << setw(15) << suma << " | " << endl;
    }
    
    suma += fx(b);
    cout << setw(10) << b << " | " 
         << setw(15) << fx(b) << " | " 
         << setw(15) << suma << " | " << endl;

    double area = h * (suma / 2);
    return area;
}

// Regla de Trapecio para puntos de datos xi y fi con salida detallada
double reglaTrapeciosMuestras(const vector<double>& xi, const vector<double>& fi) {
    int n = xi.size();
    double suma = 0.0;

    // Cabecera de la tabla
    cout << setw(10) << "x[i]" << " | " 
         << setw(15) << "f(x[i])" << " | " 
         << setw(15) << "dx" << " | " 
         << setw(15) << "Área del trapecio" << " | " << endl;
    cout << "-------------------------------------------------------------"
         << "-------------------------------" << endl;

    // Proceso de integración usando muestras
    for (int i = 0; i < n - 1; ++i) {
        double dx = xi[i + 1] - xi[i];
        double trapecio = dx * (fi[i + 1] + fi[i]) / 2.0;
        suma += trapecio;

        // Mostramos los valores de cada paso
        cout << setw(10) << xi[i] << " | " 
             << setw(15) << fi[i] << " | " 
             << setw(15) << dx << " | " 
             << setw(15) << trapecio << " | " << endl;
    }

    // Último valor para f(x[n])
    cout << setw(10) << xi[n - 1] << " | " 
         << setw(15) << fi[n - 1] << " | " 
         << setw(15) << "---" << " | " 
         << setw(15) << "---" << " | " << endl;

    return suma;
}

int main() {
    // Parte 1: Usando una función fx
    cout<<endl;
    cout << "--- Integración por Trapecios (Función F(X) ---" << endl;
    cout<<endl;
    double area = reglaTrapecios(a, b, tramos);

    // SALIDA FINAL
    cout << "\nTramos: " << tramos << endl;
    cout << "Integral (fx): " << area << endl;

    // Parte 2: Usando muestras de xi y fi
    cout<<endl;
    cout << "\n--- Integración por Trapecios (Muestras) ---" << endl;
    cout<<endl;
    // Salida detallada (tabla para muestras)
    double area_muestras = reglaTrapeciosMuestras(xi, fi);

    // SALIDA FINAL
    cout << "\nTramos: " << xi.size() - 1 << endl;
    cout << "Integral (muestras): " << area_muestras << endl;

    return 0;
}
