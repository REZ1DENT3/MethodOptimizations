#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>

using namespace std;

typedef vector<long> tvecInt;

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

double fibonacci(tvecInt fib, tInfo info) {
    unsigned int n = fib.size() - 1;
    double x, y, k = 0;
    x = info.a + (info.b - info.a) * fib.at(n - 2) / fib.at(n);
    y = info.a + info.b - x;
    double two_eps = 2 * info.eps;
    while (fabs(info.a - info.b) >= two_eps) {
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

        if (k == (n - 3)) {
            x = (info.a + info.b) / 2;
            y = x + info.delta;
            if (f(x) <= f(y)) {
                info.b = y;
            }
            else {
                info.a = x;
            }
            break;
        }
        else {
            k++;
        }

    }

    return (info.a + info.b) / 2;
}

int main() {

    tInfo info(-3, 7, 0.2, 0.5);

    tvecInt fib;
    fib.push_back(1); // 0
    fib.push_back(1); // 1

    double _end = (info.b - info.a) / (2 * info.eps);
    unsigned int _temp;
    do {
        _temp = fib.size();
        fib.push_back(fib.at(_temp - 2) + fib.at(_temp - 1));
    } while (fib.at(_temp) <= _end);

    cout << fib.at(_temp - 2) << endl;

    double x = fibonacci(fib, info);

    cout << "мин. точка: " << x << endl;
    cout << "мин.: " << f(x) << endl;

    system("PAUSE");

    return 0;
}

