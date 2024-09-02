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

// Función para realizar la eliminación gaussiana
void gaussianElimination(vector<vector<double>>& A, vector<double>& B) {
    int n = A.size();

    // Triangulación de la matriz A
    for (int i = 0; i < n; ++i) {
        // Buscar el máximo elemento en la columna i para la pivote
        double maxEl = fabs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (fabs(A[k][i]) > maxEl) {
                maxEl = fabs(A[k][i]);
                maxRow = k;
            }
        }

        // Intercambiar la fila actual con la fila de pivote
        if (i != maxRow) {
            swap(A[i], A[maxRow]);
            swap(B[i], B[maxRow]);
        }

        // Hacer cero todos los elementos debajo del pivote
        for (int k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            B[k] -= factor * B[i];
        }
    }
}

// Función para realizar la sustitución hacia atrás
vector<double> backSubstitution(const vector<vector<double>>& A, const vector<double>& B) {
    int n = A.size();
    vector<double> X(n);

    for (int i = n - 1; i >= 0; --i) {
        X[i] = B[i];
        for (int j = i + 1; j < n; ++j) {
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];
    }

    return X;
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

    // Realizar la eliminación gaussiana
    gaussianElimination(A, B_mod);

    // Realizar la sustitución hacia atrás
    vector<double> X = backSubstitution(A, B_mod);

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