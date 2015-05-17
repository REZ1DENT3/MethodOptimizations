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


double dichotomy(tInfo info, double x[2], double dk[2]) {
    double s, x0, y0, fx[2], fy[2];
    double two_eps = 2 * info.eps;
    while ((info.b - info.a) >= two_eps) {
        s = (info.b - info.a) / 20;
        x0 = (info.a + info.b - s) / 2;
        y0 = (info.a + info.b + s) / 2;
        fx[0] = x[0] - x0 * dk[0];
        fx[1] = x[1] - x0 * dk[1];
        fy[0] = x[0] - y0 * dk[0];
        fy[1] = x[1] - y0 * dk[1];
        if ((fun(fx[0], fx[1], 0)) > (fun(fy[0], fy[1], 0))) {
            info.a = x0;
        }
        else {
            info.b = y0;
        }
    }
    return (info.a + info.b) / 2;
}

double x[2];

void steepest_descent(tInfo info) {
    double norma_grad, norma_grad_pred, l, grad[2], newx[2];
    int k = 0; //шаг 2
    int f = -1;
    bool g = true, fFinal = false;
    while ((g) && (!fFinal)) {

        grad[0] = fun(x[0], x[1], 1);
        grad[1] = fun(x[0], x[1], 2);

        norma_grad = sqrt(grad[0] * grad[0] + grad[1] * grad[1]);

        if (norma_grad > info.delta) {

            tInfo _info(-1, 1, 0, 1E-5);

            l = dichotomy(_info, x, grad);

            newx[0] = x[0] - l * grad[0];

            newx[1] = x[1] - l * grad[1];

            if ((sqrt(pow(newx[0] - x[0], 2) + pow(newx[1] - x[1], 2)) < info.eps) &&
                (fabs(fun(newx[0], newx[1], 0) - fun(x[0], x[1], 0)) < info.eps)) {

                if ((k - f) == 1) {
                    fFinal = true;
                }
                else {
                    f = k;
                }
            }
        }
        else {
            g = false;
        }
        x[0] = newx[0];
        x[1] = newx[1];
        k++;
    }
    cout << "Количество итераций: " << k << endl;
    cout << "Норма градиента: " << norma_grad << endl;
}


int main() {

    double e, s;

    tInfo info(0, 0, 0.2, 0.5);

    cin >> x[0];
    cin >> x[1];
//    cout << "s=";
//    cin >> s;
//    cout << "e=";
//    cin >> e;

    steepest_descent(info);

    cout << "Точка минимума:" << endl;
    cout << x[0] << endl;
    cout << x[1] << endl;

    system("pause");

    return 0;
}
