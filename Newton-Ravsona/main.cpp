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

        fx[0] = info.x0 + x0 * dk[0];
        fx[1] = info.x1 + x0 * dk[1];
        fy[0] = info.x0 + y0 * dk[0];
        fy[1] = info.x1 + y0 * dk[1];

        if ((fun(fx[0], fx[1], 0)) > (fun(fy[0], fy[1], 0))) {
            _info.x0 = x0;
        }
        else {
            _info.x1 = y0;
        }
    }

    return (_info.x0 + _info.x1) / 2;

}

void newton_revson(tvecDouble hessian, tInfo &info) {

    tvecDouble gradient(2), dk(2), newx(2);

    double norma_gradienta, tk;
    int k = 0, f = -1;

    double rrr = (-1) * (1 / (hessian.at(0) * hessian.at(2) - pow(hessian.at(1), 2)));

    while (true) {

        gradient[0] = fun(info.x0, info.x1, 1);
        gradient[1] = fun(info.x0, info.x1, 2);

        norma_gradienta = sqrt(gradient[0] * gradient[0] + gradient[1] * gradient[1]);

        if (norma_gradienta > info.delta) {

            dk[0] = rrr * (hessian.at(2) * gradient[0] - hessian.at(1) * gradient[1]);

            dk[1] = rrr * (-hessian.at(1) * gradient[0] + hessian.at(0) * gradient[1]);

            tInfo _info(-1, 1, 0, 1E-5);

            tk = dichotomy(_info, info, dk);

            newx[0] = info.x0 + tk * dk[0];
            newx[1] = info.x1 + tk * dk[1];

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

    tvecDouble hessian;

    hessian.push_back(16);
    hessian.push_back(-1);
    hessian.push_back(2);

    tInfo info(2, 2, 0.5, 0.2);

    newton_revson(hessian, info);

    cout << "мин. точка:" << endl;
    cout << info.x0 << endl;
    cout << info.x1 << endl;

    system("pause");

    return 0;
}
