#include <iostream>
#include <vector>
#include <cmath> // Para usar fabs
using namespace std;

const vector<double> X = {
    0.0, 1.0, 2.0, 3.0
};
const vector<double> Y = {
    1.0, 2.7182, 7.3891, 20.0855
};

// Función para calcular las diferencias divididas
vector<vector<double>> diferenciasDivididas(const vector<double>& X, const vector<double>& Y) {
    int n = X.size();
    vector<vector<double>> tabla(n, vector<double>(n));

    // Rellena la primera columna con los valores de Y
    for (int i = 0; i < n; i++) {
        tabla[i][0] = Y[i];
    }

    // Calcula las diferencias divididas
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            tabla[i][j] = (tabla[i + 1][j - 1] - tabla[i][j - 1]) / (X[i + j] - X[i]);
        }
        // Imprime la tabla paso a paso
        cout << "Paso " << j << ":\n";
        for (int i = 0; i < n - j; i++) {
            for (int k = 0; k <= j; k++) {
                cout << tabla[i][k] << "\t";
            }
            cout << endl;
        }
        cout << endl;
    }

    return tabla;
}

// Función de interpolación de Newton
double interpolarNewton(const vector<double>& X, const vector<vector<double>>& tabla, double x) {
    double resultado = tabla[0][0];
    double producto = 1.0;

    for (int i = 1; i < X.size(); i++) {
        producto *= (x - X[i - 1]);
        resultado += tabla[0][i] * producto;
    }

    return resultado;
}

int main() {
    vector<vector<double>> tabla = diferenciasDivididas(X, Y);
    double x = 1.5;  // Valor a interpolar
    double yInterpolado = interpolarNewton(X, tabla, x);

    cout << "El valor interpolado en x = " << x << " es: " << yInterpolado << endl;

    // Verificación de resultados
    double valorEsperado = 4.4817; // Valor esperado para x = 1.5
    double tolerancia = 0.0001; // Tolerancia para la comparación

    if (fabs(yInterpolado - valorEsperado) < tolerancia) {
        cout << "La interpolación es correcta." << endl;
    } else {
        cout << "La interpolación es incorrecta." << endl;
    }

    return 0;
}