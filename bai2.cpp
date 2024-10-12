#include<iostream>
using namespace std;

struct PhanSo {
    int tu;
    int mau;
};

// Hàm chuẩn hóa phân số (mẫu số luôn dương)
void chuanHoa(PhanSo &p) {
    if (p.mau < 0) {
        p.tu = -p.tu;
        p.mau = -p.mau;
    }
}

// Hàm so sánh hai phân số, trả về 1 nếu p1 > p2, -1 nếu p1 < p2, và 0 nếu p1 = p2
int soSanh(PhanSo p1, PhanSo p2) {
    if (p1.tu * p2.mau > p2.tu * p1.mau) {
        return 1;  // p1 > p2
    } else if (p1.tu * p2.mau < p2.tu * p1.mau) {
        return -1; // p1 < p2
    } else {
        return 0;  // p1 = p2
    }
}

int main() {
    PhanSo phanSo1, phanSo2;

    // Nhập phân số 1 với vòng lặp do-while để mẫu số khác 0
    do {
        cout << "Nhập tử số và mẫu số của phân số 1: ";
        cin >> phanSo1.tu >> phanSo1.mau;
        if (phanSo1.mau == 0) {
            cout << "Lỗi: Mẫu số của phân số 1 không được bằng 0. Vui lòng nhập lại." << endl;
        }
    } while (phanSo1.mau == 0);

    // Nhập phân số 2 với vòng lặp do-while để mẫu số khác 0
    do {
        cout << "Nhập tử số và mẫu số của phân số 2: ";
        cin >> phanSo2.tu >> phanSo2.mau;
        if (phanSo2.mau == 0) {
            cout << "Lỗi: Mẫu số của phân số 2 không được bằng 0. Vui lòng nhập lại." << endl;
        }
    } while (phanSo2.mau == 0);

    // Chuẩn hóa phân số
    chuanHoa(phanSo1);
    chuanHoa(phanSo2);

    // So sánh hai phân số
    int result = soSanh(phanSo1, phanSo2);

    // Hiển thị kết quả
    if (result == 0) {
        cout << "Hai phân số bằng nhau." << endl;
    } else if (result == -1) {
        cout << "Phân số lớn hơn: " << phanSo2.tu << '/' << phanSo2.mau << endl;
    } else {
        cout << "Phân số lớn hơn: " << phanSo1.tu << '/' << phanSo1.mau << endl;
    }

    return 0;
}
