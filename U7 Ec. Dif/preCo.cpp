#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

using namespace std;

// Definición de constantes
const double xcero = 0.0;
const double ycero = 2.0;
const double xfinal = 4.0;
const double paso = 0.1;  // Cambia este valor para influir en el orden

// Función editable dy/dx
double f(double x, double y) {
    return exp(0.8*x)-0.50*y; // Cambia esta función según el problema
}

// Función para determinar el orden según el tamaño de paso o criterio específico
int determinarOrden(double h) {
    if (h >= 0.5) return 1;         // Si h es grande, usar un método de orden 1 (menos preciso)
    else if (h >= 0.2) return 2;    // Para h moderado, usar orden 2
    else if (h >= 0.1) return 3;    // Para h pequeño, usar orden 3
    else return 4;                  // Para h muy pequeño, usar orden 4 o superior
}

// Coeficientes de Adams-Bashforth (hasta orden 6)
vector<vector<string>> coef_bashforth_str = {
    {"1"},                                      // Orden 1
    {"3/2", "-1/2"},                            // Orden 2
    {"23/12", "-16/12", "5/12"},                // Orden 3
    {"55/24", "-59/24", "37/24", "-9/24"},      // Orden 4
    {"1901/720", "-2774/720", "2616/720", "-1274/720", "251/720"},  // Orden 5
    {"4277/1440", "-7923/1440", "9982/1440", "-7298/1440", "2877/1440", "-475/1440"} // Orden 6
};

// Coeficientes de Adams-Moulton (hasta orden 6)
vector<vector<string>> coef_moulton_str = {
    {"1"},                                      // Orden 1
    {"1/2", "1/2"},                             // Orden 2
    {"5/12", "8/12", "-1/12"},                  // Orden 3
    {"9/24", "19/24", "-5/24", "1/24"},         // Orden 4
    {"251/720", "646/720", "-264/720", "106/720", "-19/720"}, // Orden 5
    {"475/1440", "1427/1440", "-798/1440", "482/1440", "-173/1440", "27/1440"} // Orden 6
};

// Errores de truncamiento (hasta orden 6)
vector<string> errores_truncamiento_str = {
    "1/2 h^2 f''(ε)",        // Orden 1
    "5/12 h^3 f'''(ε)",       // Orden 2
    "9/24 h^4 f''''(ε)",      // Orden 3
    "251/720 h^5 f^IV(ε)",    // Orden 4
    "475/1440 h^6 f^V(ε)",    // Orden 5
    "19087/60480 h^7 f^VI(ε)" // Orden 6
};

// Método de Adams-Bashforth
double adamsBashforth(const vector<double>& x, const vector<double>& y, int i, int orden) {
    if (i < orden - 1) return y[i]; // Retorna si no hay suficientes puntos previos

    vector<double> coef_bashforth = {1, 3.0/2, -1.0/2, 23.0/12, -16.0/12, 5.0/12}; // Cambia los coeficientes aquí según el orden

    double sum = 0.0;
    for (int k = 0; k < orden; k++) {
        sum += coef_bashforth[k] * f(x[i-k], y[i-k]);
    }
    return y[i] + paso * sum;
}

// Método de Adams-Moulton (implícito)
double adamsMoulton(const vector<double>& x, const vector<double>& y, int i, int orden) {
    if (i == 0) return y[0]; // Retorna el primer valor

    double predictor = adamsBashforth(x, y, i, orden);
    vector<double> coef_moulton = {1, 1.0/2, 1.0/2, 5.0/12, 8.0/12, -1.0/12}; // Cambia los coeficientes aquí según el orden

    double sum = 0.0;
    for (int k = 0; k < orden; k++) {
        if (k == 0) {
            sum += coef_moulton[k] * f(x[i+1], predictor); // Predictor
        } else {
            sum += coef_moulton[k] * f(x[i+1-k], y[i+1-k]);
        }
    }
    return y[i] + paso * sum;
}

// Imprimir coeficientes en formato de tabla
void imprimirCoeficientes(int orden) {
    cout << "Coeficientes Beta para Adams-Bashforth y Adams-Moulton (Orden " << orden << "):\n";
    cout << "-------------------------------------------------------------\n";
    for (int k = 0; k < coef_bashforth_str[orden-1].size(); k++) {
        cout << "Beta_" << k << " (AB) = " << coef_bashforth_str[orden-1][k] << " | "
             << "Beta_" << k << " (AM) = " << coef_moulton_str[orden-1][k] << '\n';
    }
    cout << "-------------------------------------------------------------\n\n";
}

// Imprimir errores de truncamiento
void imprimirErrores(int orden) {
    cout << "Errores de truncamiento (Orden " << orden << "):\n";
    cout << "-------------------------------------------------------------\n";
    cout << errores_truncamiento_str[orden-1] << '\n';
    cout << "-------------------------------------------------------------\n\n";
}

// Imprimir encabezado de la tabla de resultados
void imprimirTablaHeader() {
    cout << "-------------------------------------------------------------\n";
    cout << setw(10) << "i" << " | " 
         << setw(10) << "x" << " | " 
         << setw(10) << "y (AB)" << " | " 
         << setw(10) << "y (AM)\n";
    cout << "-------------------------------------------------------------\n";
}

// Imprimir fila de la tabla de resultados
void imprimirFila(int i, double x, double yAB, double yAM) {
    cout << setw(10) << i << " | "
         << setw(10) << x << " | "
         << setw(10) << yAB << " | "
         << setw(10) << yAM << '\n';
}

// Método principal
int main() {

    cout << string(60, '-') << endl;
    cout << "Método de Adamas-Bashforth y Adams-Moulton" << endl;
    cout << string(60, '-') << endl;

    // Determinar el orden según el paso
    int orden = determinarOrden(paso);
    
    int steps = (xfinal - xcero) / paso;
    vector<double> x(steps + 1), y(steps + 1);

    // Condiciones iniciales
    x[0] = xcero;
    y[0] = ycero;

    // Llenar los valores de x
    for (int i = 1; i <= steps; i++) {
        x[i] = x[i-1] + paso;
    }

    // Imprimir coeficientes
    imprimirCoeficientes(orden);

    // Imprimir errores de truncamiento
    imprimirErrores(orden);

    // Imprimir encabezado de la tabla de resultados
    imprimirTablaHeader();

    // Calcular y mostrar los resultados
    for (int i = 0; i < steps; i++) {
        double yAB = adamsBashforth(x, y, i, orden);
        double yAM = adamsMoulton(x, y, i, orden);

        // Imprimir fila con los valores
        imprimirFila(i, x[i], yAB, yAM);

        y[i+1] = yAM; // Usamos el valor de Adams-Moulton para el siguiente paso
    }

    return 0;
}
