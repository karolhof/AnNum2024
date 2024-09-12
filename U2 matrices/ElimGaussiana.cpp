#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // Para setw

using namespace std;

const double EPSILON = 1e-6; // Tolerancia para la comprobación de resultados

// Definir la matriz y el vector B
const vector<vector<double>> matriz = {
    //Prueba 4x4
    
    {10,1,2,1},
    {3,15,1,0},
    {5,4,3,25},
    {1,2,20,4}
    
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
    {0, 12, 2},
    {4, -3, 7},
    */
};
const vector<double> B = {
    //Prueba 4x4
    1,2,4,3
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
    25,36, 3
    */
   };

// Función para imprimir una matriz y su correspondiente vector B
void printMatrix(const vector<vector<double>>& A, const vector<double>& B_mod) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(10) << A[i][j] << " "; // Establecer ancho de 10 caracteres para cada elemento
        }
        cout << "| " << setw(10) << B_mod[i] << endl; // También para el vector B
    }
    cout << endl;
}

// Función para realizar la eliminación gaussiana
void gaussianElimination(vector<vector<double>>& A, vector<double>& B_mod) {
    int n = A.size();

    cout << "Inicio de la eliminación gaussiana:" << endl;
    printMatrix(A, B_mod);

    // Triangulación de la matriz A
    for (int i = 0; i < n; ++i) {
        // Verificar si el elemento en la diagonal es 0
        if (fabs(A[i][i]) < EPSILON) {
            cout << "Hay un 0 en la diagonal principal." << endl;
            
            // Buscar una fila debajo que tenga un elemento no cero en la columna i
            int maxRow = i;
            for (int k = i + 1; k < n; ++k) {
                if (fabs(A[k][i]) > EPSILON) {
                    maxRow = k;
                    break;
                }
            }

            // Si encontramos una fila con un elemento no cero, la intercambiamos
            if (maxRow != i) {
                cout << "Permutando filas..." << endl;
                swap(A[i], A[maxRow]);
                swap(B_mod[i], B_mod[maxRow]);
                cout << "Las filas han sido permutadas exitosamente." << endl;
            } else {
                cout << "No se puede encontrar una solución única." << endl;
                return;
            }
        }

        // Continuar con la eliminación gaussiana
        for (int k = i + 1; k < n; ++k) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; ++j) {
                A[k][j] -= factor * A[i][j];
            }
            B_mod[k] -= factor * B_mod[i];
        }

        // Imprimir la matriz en cada paso de la triangulación
        cout << "Paso " << i + 1 << " de triangulación:" << endl;
        printMatrix(A, B_mod);
    }
}

// Función para realizar la sustitución hacia atrás
vector<double> backSubstitution(const vector<vector<double>>& A, const vector<double>& B_mod) {
    int n = A.size();
    vector<double> X(n);

    cout << "Inicio de la sustitución hacia atrás:" << endl;

    for (int i = n - 1; i >= 0; --i) {
        X[i] = B_mod[i];
        cout << "X" << i + 1 << " = " << B_mod[i];
        
        // Mostrar las operaciones para cada valor de X[i]
        for (int j = i + 1; j < n; ++j) {
            cout << " - (" << A[i][j] << " * X" << j + 1 << " = " << A[i][j] * X[j] << ")";
            X[i] -= A[i][j] * X[j];
        }
        X[i] /= A[i][i];
        cout << " / " << A[i][i] << " = " << X[i] << endl; // Imprimir resultado final de X[i]
    }

    return X;
}

// Función para comprobar la solución
bool checkSolution(const vector<vector<double>>& A, const vector<double>& B, const vector<double>& X) {
    int n = A.size();
    vector<double> AX(n, 0.0);

    cout << "Verificación de la solución:" << endl;

    // Calcular A * X
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            AX[i] += A[i][j] * X[j];
        }
        cout << "A * X[" << i + 1 << "] = " << AX[i] << ", B[" << i + 1 << "] = " << B[i] << endl;
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

    // Mostrar el resultado final
    cout << "Resultado final del sistema de ecuaciones:" << endl;
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