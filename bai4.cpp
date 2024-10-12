#include <iostream>
#include <cmath>

using namespace std;

// Hàm tính giai thừa
long long giaithua(int n) {
    long long gt = 1;
    for (int i = 2; i <= n; i++) {
        gt *= i;
    }
    return gt;
}

// Hàm tính Sin(x) theo khai triển Taylor với độ chính xác DCS
double tinhSin(double x, double DCS) {
    double term = x; // Số hạng đầu tiên
    double sinx = term; // Kết quả ban đầu
    int n = 1; // Bắt đầu từ số hạng thứ 1 (x^1)

    while (fabs(term) >= DCS) {
        term *= -x * x / ((2 * n) * (2 * n + 1)); // Cập nhật số hạng tiếp theo
        sinx += term; // Cộng số hạng vào kết quả
        n++;
    }

    return sinx;
}

int main() {
    double x;
    cout << "Nhập giá trị của x: ";
    cin >> x;
    // Độ chính xác 0.00001
    double DCS = 0.00001;
    // Tính sin(x)
    double gt = tinhSin(x, DCS);
    // In kết quả
    cout << "Giá trị của sin(" << x << ") là: " << gt << endl;
    return 0;
}
