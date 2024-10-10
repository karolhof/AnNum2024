#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // Para std::setw
using namespace std;

// Definición de los vectores
vector<double> x = {1, 2, 3, 4, 5};
vector<double> y = {0.5, 1.7, 3.4, 5.7, 8.4};

// Función para sumar los elementos de un vector (regresión lineal)
double sumLin(const vector<double>& v) {
    double suma = 0.0;
    int n = v.size();
    for (int i = 0; i < n; i++) {
        suma += v[i];
    }
    return suma;
}

// Función para sumar logaritmos en base 10 (modelo potencial)
double sumPot(const vector<double>& v) {
    double suma = 0.0;
    int n = v.size();
    for (int i = 0; i < n; i++) {
        suma += log10(v[i]);
    }
    return suma;
}

// Función para sumar logaritmos naturales (modelo exponencial)
double sumExp(const vector<double>& v) {
    double suma = 0.0;
    int n = v.size();
    for (int i = 0; i < n; i++) {
        suma += log(v[i]);
    }
    return suma;
}

// Función para realizar la regresión lineal
void regresionLineal(const vector<double>& x, const vector<double>& y, double& a0, double& a1) {
    int n = x.size();
    double sumX = sumLin(x);
    double sumY = sumLin(y);
    double sumXY = 0.0;
    double sumX2 = 0.0;

    for (int i = 0; i < n; ++i) {
        sumXY += x[i] * y[i];
        sumX2 += x[i] * x[i];
    }

    a1 = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    a0 = (sumY - a1 * sumX) / n;
}

// Función para realizar el ajuste exponencial
void regresionLinealExponencial(const vector<double>& x, const vector<double>& y, double& a0, double& a1) {
    int n = x.size();
    double sumX = sumLin(x);
    double sumLnY = sumExp(y);
    double sumXY = 0.0;
    double sumX2 = 0.0;

    for (int i = 0; i < n; ++i) {
        sumXY += x[i] * log(y[i]);
        sumX2 += x[i] * x[i];
    }

    a1 = (n * sumXY - sumX * sumLnY) / (n * sumX2 - sumX * sumX);
    a0 = (sumLnY - a1 * sumX) / n;
}

// Función para realizar el ajuste potencial
void regresionLinealPotencial(const vector<double>& x, const vector<double>& y, double& a0, double& a1) {
    int n = x.size();
    double sumLnX = sumPot(x);
    double sumLnY = sumPot(y);
    double sumXY = 0.0;
    double sumX2 = 0.0;

    for (int i = 0; i < n; ++i) {
        sumXY += log10(x[i]) * log10(y[i]);
        sumX2 += log10(x[i]) * log10(x[i]);
    }

    a1 = (n * sumXY - sumLnX * sumLnY) / (n * sumX2 - sumLnX * sumLnX);
    a0 = (sumLnY - a1 * sumLnX) / n;
}

// Función para mostrar la tabla de regresión lineal
void mostrarTablaRegresionLineal(const vector<double>& x, const vector<double>& y) {
    cout << "\nTabla de Regresión Lineal:\n";
    cout << setw(10) << "X" << "|" << setw(10) << "Y" << "|" << setw(10) << "X^2" << "|" << setw(10) << "XY" << endl;
    cout << "----------------------------------------" << endl;
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < x.size(); i++) {
        double xy = x[i] * y[i];
        double x2 = x[i] * x[i];
        sumX += x[i];
        sumY += y[i];
        sumXY += xy;
        sumX2 += x2;

        cout << setw(10) << fixed << setprecision(5) << x[i] 
             << "|" << setw(10) << fixed << setprecision(5) << y[i] 
             << "|" << setw(10) << fixed << setprecision(5) << x2 
             << "|" << setw(10) << fixed << setprecision(5) << xy << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << setw(10) << "Sumas:" << "|" 
         << setw(10) << fixed << setprecision(5) << sumY << "|" 
         << setw(10) << fixed << setprecision(5) << sumX2 << "|" 
         << setw(10) << fixed << setprecision(5) << sumXY << endl;
}

// Función para mostrar la tabla del modelo exponencial
void mostrarTablaExponencial(const vector<double>& x, const vector<double>& y) {
    cout << "\nTabla de Modelo Exponencial:\n";
    cout << setw(10) << "X" << "|" << setw(10) << "Y" << "|" << setw(10) << "ln(Y)" << "|" << setw(10) << "X^2" << "|" << setw(10) << "XY" << endl;
    cout << "----------------------------------------" << endl;
    double sumX = 0, sumLnY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < x.size(); i++) {
        double lnY = log(y[i]);
        double xy = x[i] * lnY;
        double x2 = x[i] * x[i];
        sumX += x[i];
        sumLnY += lnY;
        sumXY += xy;
        sumX2 += x2;

        cout << setw(10) << fixed << setprecision(5) << x[i] 
             << "|" << setw(10) << fixed << setprecision(5) << y[i] 
             << "|" << setw(10) << fixed << setprecision(5) << lnY 
             << "|" << setw(10) << fixed << setprecision(5) << x2 
             << "|" << setw(10) << fixed << setprecision(5) << xy << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << setw(10) << "Sumas:" << "|" 
         << setw(10) << fixed << setprecision(5) << sumLnY << "|" 
         << setw(10) << fixed << setprecision(5) << sumX2 << "|" 
         << setw(10) << fixed << setprecision(5) << sumXY << endl;
}

// Función para mostrar la tabla del modelo potencial
void mostrarTablaPotencial(const vector<double>& x, const vector<double>& y) {
    cout << "\nTabla de Modelo Potencial:\n";
    cout << setw(10) << "X" << "|" << setw(10) << "Y" << "|" << setw(10) << "ln(X)" << "|" << setw(10) << "ln(Y)" << "|" << setw(10) << "X^2" << "|" << setw(10) << "XY" << endl;
    cout << "----------------------------------------" << endl;
    double sumLnX = 0, sumLnY = 0, sumXY = 0, sumX2 = 0;

    for (int i = 0; i < x.size(); i++) {
        double lnX = log10(x[i]);
        double lnY = log10(y[i]);
        double xy = x[i] * y[i];
        double x2 = x[i] * x[i];

        sumLnX += lnX;
        sumLnY += lnY;
        sumXY += xy;
        sumX2 += x2;

        cout << setw(10) << fixed << setprecision(5) << x[i] 
             << "|" << setw(10) << fixed << setprecision(5) << y[i] 
             << "|" << setw(10) << fixed << setprecision(5) << lnX 
             << "|" << setw(10) << fixed << setprecision(5) << lnY 
             << "|" << setw(10) << fixed << setprecision(5) << x2 
             << "|" << setw(10) << fixed << setprecision(5) << xy << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << setw(10) << "Sumas:" << "|" 
         << setw(10) << fixed << setprecision(5) << sumLnX << "|" 
         << setw(10) << fixed << setprecision(5) << sumLnY << "|" 
         << setw(10) << fixed << setprecision(5) << sumX2 << "|" 
         << setw(10) << fixed << setprecision(5) << sumXY << endl;
}

// Función para mostrar la tabla del modelo de crecimiento
void mostrarTablaCrecimiento(const vector<double>& x, const vector<double>& y) {
    cout << "\nTabla de Modelo de Crecimiento:\n";
    cout << setw(10) << "X" << "|" << setw(10) << "Y" << "|" << setw(10) << "1/Y" << "|" << setw(10) << "X^2" << "|" << setw(10) << "X*1/Y" << endl;
    cout << "----------------------------------------" << endl;
    double sumX = 0, sumInvY = 0, sumXInvY = 0, sumX2 = 0;

    for (int i = 0; i < x.size(); i++) {
        double invY = 1 / y[i];
        double x2 = x[i] * x[i];
        double xInvY = x[i] * invY;

        sumX += x[i];
        sumInvY += invY;
        sumXInvY += xInvY;
        sumX2 += x2;

        cout << setw(10) << fixed << setprecision(5) << x[i] 
             << "|" << setw(10) << fixed << setprecision(5) << y[i] 
             << "|" << setw(10) << fixed << setprecision(5) << invY 
             << "|" << setw(10) << fixed << setprecision(5) << x2 
             << "|" << setw(10) << fixed << setprecision(5) << xInvY << endl;
    }

    cout << "----------------------------------------" << endl;
    cout << setw(10) << "Sumas:" << "|" 
         << setw(10) << fixed << setprecision(5) << sumX << "|" 
         << setw(10) << fixed << setprecision(5) << sumInvY << "|" 
         << setw(10) << fixed << setprecision(5) << sumX2 << "|" 
         << setw(10) << fixed << setprecision(5) << sumXInvY << endl;
}
int main() {
    int opcion;

    do {
        cout << "\nSeleccione el modelo de ajuste:\n";
        cout << "1. Regresión Lineal\n";
        cout << "2. Modelo Exponencial\n";
        cout << "3. Modelo Potencial\n";
        cout << "4. Modelo de Crecimiento\n";
        cout << "5. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        double a0 = 0.0, a1 = 0.0;

        switch (opcion) {
            case 1:
                cout << "\n--- Regresión Lineal ---\n";
                regresionLineal(x, y, a0, a1);
                mostrarTablaRegresionLineal(x, y);
                cout << "La ecuación de la recta es: y = " << a0 << " + " << a1 << "x" << endl;
                break;
            case 2:
                cout << "\n--- Modelo Exponencial ---\n";
                regresionLinealExponencial(x, y, a0, a1);
                mostrarTablaExponencial(x, y);
                cout << "La ecuación del modelo exponencial es: y = " << exp(a0) << " * e^(" << a1 << " * x)" << endl;
                break;
            case 3:
                cout << "\n--- Modelo Potencial ---\n";
                regresionLinealPotencial(x, y, a0, a1);
                mostrarTablaPotencial(x, y);
                cout << "La ecuación del modelo potencial es: y = " << pow(10, a0) << " * x^" << a1 << endl;
                break;
            case 4:
                cout << "\n--- Modelo de Crecimiento ---\n";
                mostrarTablaCrecimiento(x, y);
                // Aquí podrías implementar la lógica para el modelo de crecimiento si es necesario.
                break;
            case 5:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
    } while (opcion != 5);

    return 0;
}