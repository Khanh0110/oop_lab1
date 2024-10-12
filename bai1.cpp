#include<iostream>
#include<cmath>

using namespace std;

struct phanso {
    int tu;
    int mau;
};

// Hàm tìm ước chung lớn nhất
int txUCLN(int a, int b) {
    if (b == 0) return a;
    return txUCLN(b, a % b);
}

// Hàm rút gọn phân số
void rut_gon(phanso& ps) {
    int ucln = txUCLN(abs(ps.tu), abs(ps.mau));
    ps.tu /= ucln;
    ps.mau /= ucln;
}

int main() {
    phanso phanso1;
    // Sử dụng do-while để đảm bảo nhập mẫu hợp lệ
    do {
       
        cin >> phanso1.tu >> phanso1.mau;

        if (phanso1.mau == 0) {
            cout << "Mẫu số không hợp lệ. Vui lòng nhập lại." << endl;
        }

    } while (phanso1.mau == 0); // Lặp lại nếu mẫu bằng 0

    rut_gon(phanso1);
    cout << "Phân số đã rút gọn: " << phanso1.tu << '/' << phanso1.mau << endl;
    return 0;
}
