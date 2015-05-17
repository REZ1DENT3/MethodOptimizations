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

double dichotomy(double a, double b, double e, double x[2], double dk[2]) {
    double s, x0, y0, fx[2], fy[2];
    while ((b - a) >= 2 * e) {
        s = (b - a) / 20;
        x0 = (a + b - s) / 2;
        y0 = (a + b + s) / 2;
        fx[0] = x[0] + x0 * dk[0];
        fx[1] = x[1] + x0 * dk[1];
        fy[0] = x[0] + y0 * dk[0];
        fy[1] = x[1] + y0 * dk[1];
        if ((fun(fx[0], fx[1], 0)) > (fun(fy[0], fy[1], 0)))
            a = x0;
        else

            b = y0;
    }
    return (a + b) / 2;
}

double x[2];

void metod(double s, double e) {
    double norma_grad, norma_grad_pred, l, grad[2], dk[2], newx[2];
    int k = 0; //шаг 2
    int f = -1;
    bool g = true, fFinal = false;
    while ((g) && (!fFinal)) {
        //-------шаг 3----------------
        grad[0] = fun(x[0], x[1], 1);//шаг 3
        grad[1] = fun(x[0], x[1], 2);//шаг3

        if (k == 0)
            norma_grad = sqrt(grad[0] * grad[0] + grad[1] * grad[1]);//начальное вычисление нормы
        else {
            norma_grad_pred = norma_grad;
            //-----шаг 4--------------
            norma_grad = sqrt(grad[0] * grad[0] + grad[1] * grad[1]);//вычисление нормы
        }
        if (norma_grad > s) {
            //----шаг 6-------------
            if (k == 0) {
                dk[0] = -grad[0];
                dk[1] = -grad[1];
            }
            else {
                //---------шаг 8----------------
                dk[0] = -grad[0] + ((norma_grad * norma_grad) / (norma_grad_pred * norma_grad_pred)) * dk[0];
                dk[1] = -grad[1] + ((norma_grad * norma_grad) / (norma_grad_pred * norma_grad_pred)) * dk[1];
            }
            //-----------шаг 9-------------
            l = dichotomy(-1, 1, 0.00001, x, dk);

            //----------шаг 10------------------
            newx[0] = x[0] + l * dk[0];

            newx[1] = x[1] + l * dk[1];


            //----------шаг 11------------------------
            if ((sqrt(pow(newx[0] - x[0], 2) + pow(newx[1] - x[1], 2)) < s) &&
                (fabs(fun(newx[0], newx[1], 0) - fun(x[0], x[1], 0)) < e)) {

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
    cout << " оличество итераций: " << k << endl;
    cout << "?орма градиента: " << norma_grad << endl;
}


int main() {

    double e, s;
    cout << "x0[1]=";
    cin >> x[0];
    cout << "x0[2]=";
    cin >> x[1];
    cout << "s=";
    cin >> s;
    cout << "e=";
    cin >> e;
    metod(s, e);
    cout << "?очка минимума:" << endl;
    cout << x[0] << endl;
    cout << x[1] << endl;
    system("pause");

    return 0;
}
