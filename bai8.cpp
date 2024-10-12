#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

struct Date {
    int day, month, year;

    // Kiem tra ngay hop le
    bool OkDate() {
        if (year < 0 || month < 1 || month > 12 || day < 1) return false;
        vector<int> daysInMonth = { 31, (isLeapYear() ? 29 : 28), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        return day <= daysInMonth[month - 1];
    }

    bool isLeapYear() {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
};

struct SoTietKiem {
    string maSo, loaiTietKiem, hoTenKhachHang;
    string cmnd;  // Changed to string to handle leading zeros or non-numeric characters
    Date ngayMoSo;
    float soTienGui;
    float laiSuat;

    // kiem tra ma so hop le
    bool OkMaSo() {
        if (maSo.size() > 5 || maSo.empty()) return false;
        for (char ch : maSo) {
            if (!isalnum(ch)) return false;
        }
        return true;
    }

    // kiem tra cmmd hop le
    bool OkCMND() {
        int length = cmnd.size();  // Changed to cmnd.size() since cmnd is now a string
        return length == 9 || length == 12;
    }

    // kiem tra ho ten hop le 
    bool OkHoTen() {
        if (hoTenKhachHang.size() > 30 || hoTenKhachHang.empty()) return false;
        for (char ch : hoTenKhachHang) {
            if (!isalpha(ch) && ch != ' ') return false;
        }
        return true;
    }

    // kiem tra so tien gui hop le
    bool OkSoTienGui() {
        return soTienGui > 0;
    }

    // Tinh lai xuat
    float tinhLaiSuat(int soThangGui) const {
        return soTienGui * laiSuat * soThangGui / 12 / 100;
    }
    
    void xuatThongTin() const {
        cout << "Ma so: " << maSo << endl;
        cout << "Loai tiet kiem: " << loaiTietKiem << endl;
        cout << "Ho ten khach hang: " << hoTenKhachHang << endl;
        cout << "CMND: " << cmnd << endl;
        cout << "Ngay mo so: " << ngayMoSo.day << "/" << ngayMoSo.month << "/" << ngayMoSo.year << endl;
        cout << "So tien gui: " << soTienGui << endl;
        cout << "----------------------------" << endl;
    }
};

// nhap ngay
Date nhapNgay() {
    Date date;
    while (true) {
        cout << "Nhap ngay (dd mm yyyy): ";
        cin >> date.day >> date.month >> date.year;
        if (date.OkDate()) break;
        cout << "Ngay khong hop le! Vui long nhap lai." << endl;
    }
    return date;
}

// nhap thong tin so tiet kiem
SoTietKiem nhapThongTinSoTietKiem() {
    SoTietKiem stk;
    cin.ignore();
    while (true) {
        cout << "Nhap ma so: ";
        getline(cin, stk.maSo);
        if (stk.OkMaSo()) break;
        cout << "Ma so khong hop le! Vui long nhap lai." << endl;
    }
    cout << "Nhap loai tiet kiem: ";
    getline(cin, stk.loaiTietKiem);
    while (true) {
        cout << "Nhap ho ten khach hang: ";
        getline(cin, stk.hoTenKhachHang);
        if (stk.OkHoTen()) break;
        cout << "Ho ten khong hop le! Vui long nhap lai." << endl;
    }
    while (true) {
        cout << "Nhap CMND: ";
        getline(cin, stk.cmnd); // Use getline for CMND
        if (stk.OkCMND()) break;
        cout << "CMND khong hop le! Vui long nhap lai." << endl;
    }
    stk.ngayMoSo = nhapNgay();
    while (true) {
        cout << "Nhap so tien gui: ";
        cin >> stk.soTienGui;
        if (stk.OkSoTienGui()) break;
        cout << "So tien gui khong hop le! Vui long nhap lai." << endl;
    }
    cout << "Nhap lai suat (%/nam): ";
    cin >> stk.laiSuat;
    return stk;
}

// tinh tien lai
// input 1 so tiet kiem 
// output tinh tien la
float tinhTienLai(const SoTietKiem& stk, const Date& ngayHienTai) {
    int soThangGui = (ngayHienTai.year - stk.ngayMoSo.year) * 12 + (ngayHienTai.month - stk.ngayMoSo.month);
    return stk.tinhLaiSuat(soThangGui);
}

// tim kiem so tiet kiem
// input: danh sach, keyword la mã
// output: đưa ra stk cần tìm
SoTietKiem* timSoTietKiem(vector<SoTietKiem>& danhSach, const string& keyword) {
    for (SoTietKiem& stk : danhSach) {
        if (stk.maSo == keyword || stk.cmnd == keyword) { // Compare with cmnd as string
            return &stk;
        }
    }
    return nullptr;
}

// liet ke 
// input danh
void lietKeSoTietKiemTheoKhoangThoiGian(const vector<SoTietKiem>& danhSach, const Date& tuNgay, const Date& denNgay) {
    for (const SoTietKiem& stk : danhSach) {
        if ((stk.ngayMoSo.year > tuNgay.year || (stk.ngayMoSo.year == tuNgay.year && stk.ngayMoSo.month >= tuNgay.month)) &&
            (stk.ngayMoSo.year < denNgay.year || (stk.ngayMoSo.year == denNgay.year && stk.ngayMoSo.month <= denNgay.month))) {
            stk.xuatThongTin();
        }
    }
}

int main() {
    int soLuongSoTietKiem;
    cout << "Nhap so luong so tiet kiem: ";
    cin >> soLuongSoTietKiem;
    vector<SoTietKiem> danhSachSoTietKiem;
    
    for (int i = 0; i < soLuongSoTietKiem; i++) {
        cout << "Nhap thong tin so tiet kiem thu " << i + 1 << endl;
        danhSachSoTietKiem.push_back(nhapThongTinSoTietKiem());
    }

    string keyword;
    cout << "Nhap CMND hoac ma so de tim kiem: ";
    cin >> keyword;
    SoTietKiem* timKiemKetQua = timSoTietKiem(danhSachSoTietKiem, keyword);
    if (timKiemKetQua) {
        cout << "Thong tin so tiet kiem tim thay:" << endl;
        timKiemKetQua->xuatThongTin();
    } else {
        cout << "Khong tim thay so tiet kiem voi CMND hoac ma so: " << keyword << endl;
    }

    cout << "Nhap khoang thoi gian de liet ke so tiet kiem:" << endl;
    Date tuNgay = nhapNgay();
    Date denNgay = nhapNgay();
    cout << "Danh sach so tiet kiem mo trong khoang thoi gian:" << endl;
    lietKeSoTietKiemTheoKhoangThoiGian(danhSachSoTietKiem, tuNgay, denNgay);

    return 0;
}
