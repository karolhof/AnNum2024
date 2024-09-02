#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const double EPSILON = 1e-6; // Tolerancia para la comprobación de resultados

// Definir la matriz y el vector B
const vector<vector<double>> matriz = {
    //EJ1
    /*
    {3, -0.1,-0.2},
    {0.1, 7,-0.3},
    {0.3, -0.2, 10}
    */
    //EJ2
    /*
    {10, -3, 6},
    {1, 8, -2},
    {-2, 4, -9}
    */
    //EJ3
    /*
    {1, 7, -3},
    {4, -4, 9},
    {12, -1, 3}
    */
    //EJ4
    /*
    {-6, 0, 12},
    {4, -1, -1},
    {6, 8, 0}
    */
    //EJ5
    /*
    {5, 4, 0},
    {4, -3, 7},
    {0, 12, 2}
    */
};
// Definir los vectores B correspondientes
const vector<double> B = {
    // EJ1
    /*
    7.85, 19.30, 71.40
    */
    // EJ2
    /*
    24.5, -9, -50
    */
    // EJ3
    /*
    -51, 61, 8
    */
    // EJ4
    /*
    60, -2, 44
    */
    // EJ5
    /*
    25, 3, 36
    */
};
// Función para realizar la factorización LU
void luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U) {
    int n = A.size();
    
    // Inicializar L como la matriz identidad y U como la matriz A
    L = vector<vector<double>>(n, vector<double>(n, 0.0));
    U = vector<vector<double>>(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0; // Diagonal de L es 1
        for (int j = 0; j < n; ++j) {
            U[i][j] = A[i][j];
        }
    }

    // Factorización LU usando eliminación Gaussiana
    for (int k = 0; k < n; ++k) {
        for (int i = k + 1; i < n; ++i) {
            double factor = U[i][k] / U[k][k];
            L[i][k] = factor;
            for (int j = k; j < n; ++j) {
                U[i][j] -= factor * U[k][j];
            }
        }
    }
}

// Función para resolver L * y = B usando sustitución hacia adelante
vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& B) {
    int n = L.size();
    vector<double> y(n);

    for (int i = 0; i < n; ++i) {
        y[i] = B[i];
        for (int j = 0; j < i; ++j) {
            y[i] -= L[i][j] * y[j];
        }
    }

    return y;
}

// Función para resolver U * x = y usando sustitución hacia atrás
vector<double> backSubstitution(const vector<vector<double>>& U, const vector<double>& y) {
    int n = U.size();
    vector<double> x(n);

    for (int i = n - 1; i >= 0; --i) {
        x[i] = y[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }

    return x;
}

// Función para comprobar la solución
bool checkSolution(const vector<vector<double>>& A, const vector<double>& B, const vector<double>& X) {
    int n = A.size();
    vector<double> AX(n, 0.0);

    // Calcular A * X
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            AX[i] += A[i][j] * X[j];
        }
    }

    // Comparar A * X con B
    for (int i = 0; i < n; ++i) {
        if (fabs(AX[i] - B[i]) > EPSILON) {
            return false; // La solución no es correcta
        }
    }

    return true; // La solución es correcta
}

int main() {
    // Copiar la matriz y el vector B para no modificar los originales
    vector<vector<double>> A = matriz;
    vector<double> B_mod = B;

    int n = A.size();

    // Factorización LU
    vector<vector<double>> L(n, vector<double>(n, 0.0));
    vector<vector<double>> U(n, vector<double>(n, 0.0));
    luDecomposition(A, L, U);

    // Resolver L * y = B
    vector<double> y = forwardSubstitution(L, B_mod);

    // Resolver U * x = y
    vector<double> X = backSubstitution(U, y);

    // Mostrar el resultado
    cout << "Resultado del sistema de ecuaciones:" << endl;
    for (size_t i = 0; i < X.size(); ++i) {
        cout << "X" << i + 1 << " = " << X[i] << endl;
    }

    // Comprobar la solución
    if (checkSolution(matriz, B, X)) {
        cout << "La solución es correcta." << endl;
    } else {
        cout << "La solución no es correcta." << endl;
    }

    return 0;
}