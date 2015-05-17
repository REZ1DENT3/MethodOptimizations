#include <iostream>
#include <math.h>
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

double golden_section(tInfo info) {
    double x, y;
    x = info.a + (3 - sqrt(5)) * (info.b - info.a) / 2;
    y = info.a + info.b - x;
    double two_eps = 2 * info.eps;
    while ((info.b - info.a) > two_eps) {
        if (f(x) < f(y)) {
            info.b = y;
            y = x;
            x = info.a + info.b - y;
        }
        else {
            info.a = x;
            x = y;
            y = info.a + info.b - x;
        }
    }
    return (info.a + info.b) / 2;
}

int main() {

    tInfo info(-3, 7, 0.2, 0.5);

    double x = golden_section(info);

    cout << "мин. точка: " << x << endl;
    cout << "мин.: " << f(x) << endl;

    system("pause");
    return 0;

}