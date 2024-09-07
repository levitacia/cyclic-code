#include "Header.h"

int* multiply(int* arr1, int* arr2, int p1, int p2) {
    int* cx_temp = new int[p1 + p2 - 1] {0};
    for (int i = 0; i < p1; i++) {
        for (int j = 0; j < p2; j++) {
            cx_temp[i + j] += arr1[i] * arr2[j];
        }
    }

    for (int i = 0; i < p1 + p2 - 1; i++) {
        cx_temp[i] = cx_temp[i] % 2;
    }
    return cx_temp;
} //m(x) * x^r

void division(int* arr1, int p1, int* arr2, int p2, int* result) {
    for (int i = p1 - p2; i >= 0; i--) {
        int j = i + p2 - 1;
        result[i] = arr1[i + p2] / arr2[p2];
        for (j; j >= i; j--) {
            arr1[j] = arr1[j] - arr2[j - i] * result[i];
        }
    }
}

void reverse(int* arr, int size) {
    for (int i = 0; i < size / 2; ++i) {
        swap(arr[i], arr[size - i - 1]);
    }
}

void generate_e(int* errors, int size) {
    double p = 0.1;
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    for (int i = 0; i < size; i++) {
        errors[i] = dist(gen) <= p ? 1 : 0;
    }
}

void generate_random_m(int* m, int k) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 1);
    for (int i = 0; i < k; i++) {
        m[i] = dist(gen);
    }
}

int* coder(const int r, int* g_x, const int k, int* m) {
    //создаем x^r
    int* x_r = new int[r + 1] {0};
    x_r[0] = 1;

    int* cx_temp = multiply(m, x_r, k, r + 1); //считаем m(x) * x^r
    int size_cx = k + (r + 1) - 1;
    int degcx = size_cx - 1;
    //c(x) = m(x) * 1^r mod g(x)

    //разворачиваем для корректного деления
    reverse(cx_temp, size_cx);

    int size_ax = size_cx;
    int* ax = new int[size_cx];
    for (int i = 0; i < size_ax; i++) {
        ax[i] = cx_temp[i];
    }

    int* result = new int[degcx - r + 1];
    division(cx_temp, degcx, g_x, r, result);

    //формируем a(x) - вектор а
    for (int i = r - 1; i >= 0; i--) {
        ax[i] = cx_temp[i];
    }
    for (int i = 0; i < size_ax; i++) {
        ax[i] %= 2;
        if (ax[i] < 0)
            ax[i] *= -1;
    }

    return ax;
}


bool decoder(int* ax, int size_ax, int size_cx, int* g_x, int r) {
    bool resu = 0;
    //формируем веkтор ошибок
    int size_e = size_ax;
    int* errors = new int[size_ax] {0};
    generate_e(errors, size_e);

    int* bx = new int[size_e] {0};
    for (int i = 0; i < size_e; i++) {
        bx[i] = ax[i] ^ errors[i];
    }


    //декодер проверяет остаток
    int* res1 = new int[(size_cx - 1) - r + 1] {0};
    division(bx, size_cx - 1, g_x, r, res1);

    bool E = 0;
    bool check_e = 0;

    for (int i = r - 1; i >= 0; i--) {
        bx[i] %= 2;
        if (bx[i] < 0)
            bx[i] *= -1;
        if (bx[i] != 0)
            E = 1;
    }
    for (int i = 0; i < size_e; i++) {
        if (errors[i] != 0)
            check_e = 1;
    }
    if (check_e == 1 && E == 0)
        resu = 1;//декодер ошибся
    else
        resu = 0;


    return resu;
}