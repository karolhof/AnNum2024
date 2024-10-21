#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath> // Para usar fabs() en la verificación de errores

using namespace std;

// Variables globales
const vector<double> X = {0.0, 1.0, 2.0, 3.0}; // Valores de X
const vector<double> Y = {1.0, 2.7182, 7.3891, 20.0855}; // Valores de Y
const int n = X.size(); // Número de puntos

// Función para calcular las diferencias divididas
void calcularDiferenciasDivididas(vector<vector<double>>& dif) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            dif[i][j] = (dif[i - 1][j + 1] - dif[i - 1][j]) / (X[j + i] - X[j]);
        }
    }
}

// Función para evaluar el polinomio en un valor dado
double evaluarPolinomioNewton(double x, const vector<vector<double>>& dif) {
    double resultado = dif[0][0]; // Inicializa con el primer coeficiente
    double prod = 1.0; // Producto acumulativo
    for (int i = 1; i < n; i++) {
        prod *= (x - X[i - 1]); // Calcula el producto (x - X[i-1])
        resultado += dif[i][0] * prod; // Suma el término correspondiente
    }
    return resultado;
}

// Función para verificar los resultados interpolados
void verificarResultados(const vector<vector<double>>& diferencias) {
    cout << "\nVerificación de los resultados:\n";
    cout << setw(10) << "Xi" << " | " << setw(10) << "Yi (Real)" << " | " 
         << setw(15) << "P(Xi) (Interpolado)" << " | " 
         << setw(10) << "Error" << endl;
    cout << string(60, '-') << endl;

    // Verificar el polinomio en los puntos dados de X
    for (int i = 0; i < n; i++) {
        double valorInterpolado = evaluarPolinomioNewton(X[i], diferencias);
        double error = fabs(valorInterpolado - Y[i]); // Error absoluto
        cout << setw(10) << X[i] << " | " << setw(10) << Y[i] << " | " 
             << setw(15) << valorInterpolado << " | " 
             << setw(10) << error << endl;
    }
}

// Función para obtener el polinomio expandido y simplificado
void obtenerPolinomioSimplificado(const vector<vector<double>>& diferencias) {
    // Los coeficientes se obtienen expandiendo cada término
    double a = diferencias[3][0]; // Coeficiente de x^3
    double b = diferencias[2][0] - diferencias[3][0] * (X[0] + X[1] + X[2]); // Coeficiente de x^2
    double c = diferencias[1][0] - diferencias[2][0] * (X[0] + X[1]) + diferencias[3][0] * (X[0] * X[1] + X[0] * X[2] + X[1] * X[2]); // Coeficiente de x^1
    double d = diferencias[0][0] - diferencias[1][0] * X[0] + diferencias[2][0] * X[0] * X[1] - diferencias[3][0] * X[0] * X[1] * X[2]; // Coeficiente constante

    // Mostrar el polinomio simplificado
    cout << "\nEl polinomio interpolador en su forma mínima es: f_3(x) = ";
    cout << fixed << setprecision(4)
         << a << "x^3 + " 
         << b << "x^2 + " 
         << c << "x + " 
         << d << endl;
}

// Método de Interpolación Polinomial de Newton
void interpolacionNewton() {
    vector<vector<double>> diferencias(n, vector<double>(n, 0.0));

    // Llenar la primera columna con los valores de Y
    for (int i = 0; i < n; i++) {
        diferencias[0][i] = Y[i];
    }

    // Calcular las diferencias divididas
    calcularDiferenciasDivididas(diferencias);

    // Mostrar tabla de diferencias divididas
    cout << "Tabla de diferencias divididas:\n";
    cout << setw(10) << "Xi" << " | " << setw(10) << "Yi" << " | " 
         << setw(15) << "f[X1;X0]" << " | " 
         << setw(15) << "f[X2;X1]" << " | " 
         << setw(15) << "f[X3;X2]" << " | " 
         << setw(15) << "f[X2;X1;X0]" << " | "
         << setw(15) << "f[X3;X2;X1;X0]" << endl;
    cout << string(100, '-') << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(10) << X[i] << " | " << setw(10) << Y[i] << " | ";
        for (int j = 0; j < n - i; j++) {
            cout << setw(15) << diferencias[j][i] << " ";
        }
        cout << endl;
    }
    
    // Obtener y mostrar el polinomio simplificado
    obtenerPolinomioSimplificado(diferencias);

    // Verificar los resultados interpolados
    verificarResultados(diferencias);
}

int main() {

    cout<<string(60,'-')<<endl;
    cout<<"Interpolación de Newton"<<endl;
    cout<<string(60,'-')<<endl;

    interpolacionNewton();
    return 0;
}
