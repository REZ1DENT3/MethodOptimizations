#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

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

double f(double x) {
    return pow(x, 2) + 5 * x - 1;
}

double dichotomy(tInfo info) {
    double x0, y0, fx, fy, ab;
    double two_eps = 2 * info.eps;
    while ((info.b - info.a) >= two_eps) {
        ab = info.a + info.b;
        x0 = (ab - info.delta) / 2;
        y0 = (ab + info.delta) / 2;
        fx = f(x0);
        fy = f(y0);
        if (fx >= fy) {
            info.a = x0;
        }
        else {
            info.b = y0;
        }
    }
    return (info.a + info.b) / 2;
}

int main() {

    tInfo info(-3, 7, 0.2, 0.5);

    double x = dichotomy(info);

    cout << "мин. точка: " << x << endl;
    cout << "мин.: " << f(x) << endl;

    system("pause");

    return 0;
}

