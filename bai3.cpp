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

// Hàm tính tích
phanso Tich(phanso& p1, phanso& p2) {
    phanso kq;
    kq.tu = p1.tu * p2.tu;
    kq.mau = p1.mau * p2.mau;
    rut_gon(kq);
    return kq;
}

// Hàm tính tổng
phanso Tong(phanso& p1, phanso& p2) {
    phanso kq;
    kq.tu = p1.tu * p2.mau + p2.tu * p1.mau;
    kq.mau = p1.mau * p2.mau;
    rut_gon(kq);
    return kq;
}

// Hàm tính thương
phanso Thuong(phanso& p1, phanso& p2) {
    phanso kq;
    kq.tu = p1.tu * p2.mau;
    kq.mau = p1.mau * p2.tu;
    rut_gon(kq);
    return kq;
}

// Hàm tính hiệu
phanso Hieu(phanso& p1, phanso& p2) {
    phanso kq;
    kq.tu = p1.tu * p2.mau - p2.tu * p1.mau;
    kq.mau = p1.mau * p2.mau;
    rut_gon(kq);
    return kq;
}

int main() {
    phanso a, b;

    // Nhập phân số a với vòng lặp do-while để mẫu số khác 0
    do {
        cout << "Nhập tử số và mẫu số của phân số a: ";
        cin >> a.tu >> a.mau;
        if (a.mau == 0) {
            cout << "Lỗi: Mẫu số của phân số a không được bằng 0. Vui lòng nhập lại." << endl;
        }
    } while (a.mau == 0);

    // Nhập phân số b với vòng lặp do-while để mẫu số khác 0
    do {
        cout << "Nhập tử số và mẫu số của phân số b: ";
        cin >> b.tu >> b.mau;
        if (b.mau == 0) {
            cout << "Lỗi: Mẫu số của phân số b không được bằng 0. Vui lòng nhập lại." << endl;
        }
    } while (b.mau == 0);

    // Tính toán và xuất kết quả
    phanso kqTich = Tich(a, b);
    cout << "Tích: " << kqTich.tu << '/' << kqTich.mau << endl;
    phanso kqTong = Tong(a, b);
    cout << "Tổng: " << kqTong.tu << '/' << kqTong.mau << endl;
    phanso kqHieu = Hieu(a, b);
    cout << "Hiệu: " << kqHieu.tu << '/' << kqHieu.mau << endl;
    if (b.tu == 0) {
        cout << "Không thể chia cho phân số có tử số bằng 0." << endl;
    } else {
        phanso kqThuong = Thuong(a, b);
        cout << "Thương: " << kqThuong.tu << '/' << kqThuong.mau << endl;
    }
    return 0;
}
