#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct SplineCubico {
    double a, b, c, d, x;
};

const vector<double> x = {0, 1, 2, 3};
const vector<double> y = {1, 2.7182, 7.3891, 20.0855};


vector<SplineCubico> splineCubicoNatural(const vector<double>& x, const vector<double>& y) {
    int n = x.size() - 1;
    vector<double> h(n), alpha(n);
    for (int i = 0; i < n; ++i) {
        h[i] = x[i + 1] - x[i];
    }

    // Paso 2: Calcular valores alpha
    for (int i = 1; i < n; ++i) {
        alpha[i] = (3 / h[i]) * (y[i + 1] - y[i]) - (3 / h[i - 1]) * (y[i] - y[i - 1]);
    }

    // Paso 3: Resolver el sistema tridiagonal
    vector<double> l(n + 1), mu(n), z(n + 1);
    l[0] = 1.0;
    mu[0] = z[0] = 0.0;

    for (int i = 1; i < n; ++i) {
        l[i] = 2 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n] = 1.0;
    z[n] = 0.0;

    vector<double> c(n + 1), b(n), d(n);
    for (int j = n - 1; j >= 0; --j) {
        c[j] = z[j] - mu[j] * c[j + 1];
        b[j] = (y[j + 1] - y[j]) / h[j] - h[j] * (c[j + 1] + 2 * c[j]) / 3;
        d[j] = (c[j + 1] - c[j]) / (3 * h[j]);
    }

    // Paso 7: Construir los coeficientes del spline
    vector<SplineCubico> splines(n);
    for (int i = 0; i < n; ++i) {
        splines[i] = {y[i], b[i], c[i], d[i], x[i]};
    }

    return splines;
}

double evaluarSpline(const vector<SplineCubico>& splines, double x) {
    int n = splines.size();
    SplineCubico s;
    for (int i = 0; i < n; ++i) {
        if (x >= splines[i].x && (i == n - 1 || x < splines[i + 1].x)) {
            s = splines[i];
            break;
        }
    }

    double dx = x - s.x;
    return s.a + s.b * dx + s.c * dx * dx + s.d * dx * dx * dx;
}

void imprimirPolinomiosReducidos(const vector<SplineCubico>& splines) {
    cout << fixed << setprecision(4);
    for (int i = 0; i < splines.size(); ++i) {
        double a = splines[i].a;
        double b = splines[i].b;
        double c = splines[i].c;
        double d = splines[i].d;
        double x0 = splines[i].x;

        // Expandir el polinomio S_i(x) = a + b * (x - x0) + c * (x - x0)^2 + d * (x - x0)^3
        double a_reducido = a - b * x0 + c * x0 * x0 - d * x0 * x0 * x0;
        double b_reducido = b - 2 * c * x0 + 3 * d * x0 * x0;
        double c_reducido = c - 3 * d * x0;
        double d_reducido = d;

        if (i < splines.size() - 1) {
            cout << "Polinomio " << i << " en el intervalo [" << x0 << ", " << splines[i + 1].x << "]:" << endl;
        } else {
            // Último polinomio, el intervalo termina en el último valor de x
            cout << "Polinomio " << i << " en el intervalo [" << x0 << ", " << x0 + 1 << "]:" << endl;
        }

        cout << "S_" << i << "(x) = " << a_reducido
             << " + " << b_reducido << " * x"
             << " + " << c_reducido << " * x^2"
             << " + " << d_reducido << " * x^3" << endl;
        cout << endl;
    }
}

int main() {

    cout<<string(60,'-')<<endl;
    cout<<"Interpolación con splines cúbicos naturales"<<endl;
    cout<<string(60,'-')<<endl;

    vector<SplineCubico> splines = splineCubicoNatural(x, y);

    // Mostrar los polinomios reducidos
    imprimirPolinomiosReducidos(splines);

    // Evaluar el spline en un punto
    double x_eval = 1.5;
    double y_eval = evaluarSpline(splines, x_eval);
    cout << "El valor interpolado en x = " << x_eval << " es y = " << y_eval << endl;

    return 0;
}