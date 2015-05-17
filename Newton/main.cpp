#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef vector<double> tvecDouble;

struct tInfo {
public:
    tInfo(double a, double b, double delta, double eps) {
        this->a = a;
        this->b = b;
        this->delta = delta;
        this->eps = eps;
    }

public:
    double a, b;
    double delta;
    double eps;
};

double fun(double x1, double x2, int flag) {
    /**
     * 0 - функция
     * 1 - производная по х
     * 2 - производная по у.
     */
    switch (flag) {
        case 0:
            return 8 * pow(x1, 2) + pow(x2, 2) - x1 * x2 + x1;
        case 1:
            return 16 * x1 - x2 + 1;
        case 2:
            return 2 * x2 - x1;
        default:
            return 0.;
    }
}

const bool GesT = true;

double Gesse(int flag) {
    switch (flag) {
        case 0:
            return 16;
            break;
        case 1:
            return -1;
            break;
        case 2:
            return 2;
            break;
        default:
            break;
    }
}

double x[2];

void metod(double E1, double E2) {
    double norma_gradienta, gradient[2], dk[2], newx[2];
    int k = 0, f = -1;
    bool g = true, fFinal = false;
    while ((g) && (!fFinal)) {
        gradient[0] = fun(x[0], x[1], 1);
        gradient[1] = fun(x[0], x[1], 2);

        norma_gradienta = sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1]);

        if (norma_gradienta > E1) {
            if (GesT) {
                //dk=-1/|H|*(aljH)*gradient
                dk[0] = (-1) * (1 / (Gesse(0) * Gesse(2) - pow(Gesse(1), 2))) *
                        (Gesse(2) * gradient[0] + (-Gesse(1)) * gradient[1]);
                dk[1] = (-1) * (1 / (Gesse(0) * Gesse(2) - pow(Gesse(1), 2))) *
                        ((-Gesse(1)) * gradient[0] + Gesse(0) * gradient[1]);

                newx[0] = x[0] + dk[0];
                newx[1] = x[1] + dk[1];
            }

            if ((sqrt(pow(newx[0] - x[0], 2) + pow(newx[1] - x[1], 2)) < E2) &&
                (fabs(fun(newx[0], newx[1], 0) - fun(x[0], x[1], 0)) < E2)) {
                if ((k - f) == 1) { fFinal = true; }
                else { f = k; }
            }
        }
        else
            g = false;
        x[0] = newx[0];
        x[1] = newx[1];
        k++;
    }
    cout << "Количество итераций: " << k << endl;
    cout << "Норма градиента: " << norma_gradienta << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    double E1, E2;
    cout << "x0[1]=";
    cin >> x[0];
    cout << "x0[2]=";
    cin >> x[1];
    cout << "E1=";
    cin >> E1;
    cout << "E2=";
    cin >> E2;
    metod(E1, E2);

    cout << "Точка минимума:";
    cout << x[0] << endl;
    cout << x[1] << endl;
    system("pause");

    return 0;

}



