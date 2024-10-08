#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // Para configurar la precisión de salida

using namespace std;

const double EPSILON = 1e-6; // Tolerancia para la comprobación de resultados

// Definir la matriz y el vector B
const vector<vector<double>> matriz = {
    // Prueba 4x4
    {0, 1, 2, 1},
    {3, 15, 1, 0},
    {1, 2, 20, 4},
    {5, 4, 3, 25}
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

// Definir el vector B correspondiente
const vector<double> B = {
    1, 2, 3, 4
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

// Función para mostrar una matriz
void printMatrix(const vector<vector<double>>& mat) {
    for (const auto& row : mat) {
        for (double val : row) {
            cout << setw(10) << val << " ";
        }
        cout << endl;
    }
}

// Función para realizar la factorización LU con permutación de filas
bool luDecomposition(vector<vector<double>>& A, vector<vector<double>>& L, vector<vector<double>>& U, vector<int>& perm) {
    int n = A.size();

    // Inicializar L como la matriz identidad y U como la matriz A
    L = vector<vector<double>>(n, vector<double>(n, 0.0));
    U = A; // U es una copia inicial de A
    perm = vector<int>(n); // Vector de permutación de filas

    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
        perm[i] = i; // Inicializar permutaciones
    }

    // Factorización LU con permutación parcial de filas
    for (int k = 0; k < n; ++k) {
        // Búsqueda del pivote máximo en la columna k
        int maxRow = k;
        for (int i = k + 1; i < n; ++i) {
            if (fabs(U[i][k]) > fabs(U[maxRow][k])) {
                maxRow = i;
            }
        }

        // Permutar filas en U, L y el vector de permutación
        if (maxRow != k) {
            cout << "Permutando filas " << k + 1 << " y " << maxRow + 1 << "..." << endl;
            swap(U[k], U[maxRow]);
            swap(perm[k], perm[maxRow]);
            if (k > 0) {
                swap(L[k], L[maxRow]);
            }
            cout << "Matriz U después de permutar filas:" << endl;
            printMatrix(U);
            cout << "----------------------------------------" << endl;
            cout << "Matriz L después de permutar filas:" << endl;
            printMatrix(L);
            cout << "----------------------------------------" << endl;
        }

        // Verificar si el elemento pivote es cero (para detectar singularidad)
        if (fabs(U[k][k]) < EPSILON) {
            cout << "Matriz singular detectada." << endl;
            return false;
        }

        // Realizar la eliminación Gaussiana
        for (int i = k + 1; i < n; ++i) {
            double factor = U[i][k] / U[k][k];
            L[i][k] = factor;
            for (int j = k; j < n; ++j) {
                U[i][j] -= factor * U[k][j];
            }
        }

        // Mostrar los pasos de la eliminación
        cout << "Matriz U después de eliminar fila " << k + 1 << ":" << endl;
        printMatrix(U);
        cout << "----------------------------------------" << endl;
        cout << "Matriz L después de eliminar fila " << k + 1 << ":" << endl;
        printMatrix(L);
        cout << "----------------------------------------" << endl;
    }
    return true;
}

// Función para resolver L * y = P * B usando sustitución hacia adelante
vector<double> forwardSubstitution(const vector<vector<double>>& L, const vector<double>& B, const vector<int>& perm) {
    int n = L.size();
    vector<double> y(n);

    for (int i = 0; i < n; ++i) {
        y[i] = B[perm[i]];
        for (int j = 0; j < i; ++j) {
            y[i] -= L[i][j] * y[j];
        }
    }

    cout << "Vector y después de sustitución hacia adelante:" << endl;
    for (size_t i = 0; i < y.size(); ++i) {
        cout << "y" << i + 1 << " = " << y[i] << endl;
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

    cout << "Vector x después de sustitución hacia atrás:" << endl;
    for (size_t i = 0; i < x.size(); ++i) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
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
    cout << "Comparación de A * X con B:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "A * X[" << i + 1 << "] = " << AX[i] << ", B[" << i + 1 << "] = " << B[i] << endl;
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

    // Factorización LU con permutación de filas
    vector<vector<double>> L, U;
    vector<int> perm;
    if (!luDecomposition(A, L, U, perm)) {
        return -1; // Terminar si no se puede realizar la factorización
    }

    // Resolver L * y = P * B
    vector<double> y = forwardSubstitution(L, B_mod, perm);

    // Resolver U * x = y
    vector<double> X = backSubstitution(U, y);

    // Mostrar el resultado con precisión ajustada
    cout << fixed << setprecision(6);
    cout << "Resultado del sistema de ecuaciones:" << endl;
    for (size_t i = 0; i < X.size(); ++i) {
        cout << "X" << i + 1 << " = " << X[i] << endl;
    }

    // Comprobar la solución
    if (checkSolution(matriz, B, X)) {
        cout << "La solución es correcta." << endl;
    } else {
        cout << "La solución es incorrecta." << endl;
    }

    return 0;
}
