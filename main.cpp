#include "Header.h"


int main() {
    const int r = 3;
    int g_x[r + 1] = { 1, 1, 0, 1 }; //g(x) = x^3 + x + 1
    const int k = 4; 
    int m[k] = { 1, 0, 1, 0 }; 
    /*int* m = new int[k];
    generate_random_m(m, k);*/

    int size_cx = k + (r + 1) - 1;

    double eps = 0.01;
    double N = 9 / (4 * (eps * eps));
    double Ne = 0.0;
    for (int i = 0; i < N; i++) {
        int* ax = coder(r, g_x, k, m);
        if (decoder(ax, size_cx, size_cx, g_x, r) == 1) {
            Ne += 1;
        }
    }
    double Pe = Ne / N;

    cout << "Ne = " << Ne << endl;
    cout << "N = " << N << endl;
    cout << "Pe = " << Pe << endl;


    return 0;
}