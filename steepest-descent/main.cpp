#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef vector<double> tvecDouble;

struct tInfo {
public:
    tInfo(double x0, double x1, double delta, double eps) {
        this->x0 = x0;
        this->x1 = x1;
        this->delta = delta;
        this->eps = eps;
    }

public:
    double x0, x1;
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

double dichotomy(tInfo _info, tInfo info, tvecDouble dk) {

    tvecDouble fx(2), fy(2);

    double x0, y0;
    double two_eps = 2 * _info.eps;

    while ((_info.x1 - _info.x0) >= two_eps) {

        _info.delta = (_info.x1 - _info.x0) / 20;
        x0 = (_info.x0 + _info.x1 - _info.delta) / 2;
        y0 = (_info.x0 + _info.x1 + _info.delta) / 2;

        fx[0] = info.x0 - x0 * dk[0];
        fx[1] = info.x1 - x0 * dk[1];
        fy[0] = info.x0 - y0 * dk[0];
        fy[1] = info.x1 - y0 * dk[1];

        if ((fun(fx[0], fx[1], 0)) > (fun(fy[0], fy[1], 0))) {
            _info.x0 = x0;
        }
        else {
            _info.x1 = y0;
        }
    }

    return (_info.x0 + _info.x1) / 2;

}

void steepest_descent(tInfo &info) {

    tvecDouble grad(2), newx(2);
    double norma_grad, l;
    int k = 0;
    int f = -1;
    while (true) {

        grad[0] = fun(info.x0, info.x1, 1);
        grad[1] = fun(info.x0, info.x1, 2);

        norma_grad = sqrt(pow(grad[0], 2) + pow(grad[1], 2));

        if (norma_grad > info.delta) {

            tInfo _info(-1, 1, 0, 1E-5);

            l = dichotomy(_info, info, grad);

            newx[0] = info.x0 - l * grad[0];
            newx[1] = info.x1 - l * grad[1];

            if ((sqrt(pow(newx[0] - info.x0, 2) + pow(newx[1] - info.x1, 2)) < info.eps) &&
                (fabs(fun(newx[0], newx[1], 0) - fun(info.x0, info.x1, 0)) < info.eps)) {

                if ((k - f) == 1) {

                    info.x0 = newx[0];
                    info.x1 = newx[1];
                    k++;
                    break;
                }
                else {
                    f = k;
                }
            }
        }
        else {

            info.x0 = newx[0];
            info.x1 = newx[1];
            k++;
            break;
        }
        info.x0 = newx[0];
        info.x1 = newx[1];
        k++;
    }

}


int main() {

    tInfo info(2, 2, 0.5, 0.2);

    steepest_descent(info);

    cout << "мин. точка:" << endl;
    cout << info.x0 << endl;
    cout << info.x1 << endl;

    system("pause");

    return 0;
}
