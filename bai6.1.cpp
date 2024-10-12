#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

struct Hocsinh {
    string hovaten;
    float diemvan;
    float diemtoan;
    float diemnn;

    float TinhDiemTrungBinh() const {
        return (2 * diemtoan + diemvan + diemnn) / 4; // Trọng số cho điểm toán
    }
};

// Vector chứa danh sách học sinh
vector<Hocsinh> danhSachHocsinh;

// Hàm kiểm tra tên học sinh hợp lệ
bool isValidName(const string& name) {
    if (name.length() < 1 || name.length() > 100) {
        return false;
    }
    for (char c : name) {
        if (isdigit(c)) {
            return false; // Tên không được chứa ký tự số
        }
    }
    return true;
}

// Hàm nhập thông tin học sinh
void input() {
    int n;
    cout << "Nhap so luong hoc sinh: ";
    cin >> n;
    danhSachHocsinh.resize(n); // Thiết lập kích thước cho danh sách

    for (int i = 0; i < n; i++) {
        string name;
        do {
            cout << "Nhap ho va ten hoc sinh " << i + 1 << ": ";
            cin.ignore();
            getline(cin, name);
        } while (!isValidName(name)); // Kiểm tra tính hợp lệ của tên
        danhSachHocsinh[i].hovaten = name;

        // Nhập điểm toán
        do {
            cout << "Nhap diem toan (0-10): ";
            cin >> danhSachHocsinh[i].diemtoan;
        } while (danhSachHocsinh[i].diemtoan < 0 || danhSachHocsinh[i].diemtoan > 10);
        
        // Nhập điểm văn
        do {
            cout << "Nhap diem van (0-10): ";
            cin >> danhSachHocsinh[i].diemvan;
        } while (danhSachHocsinh[i].diemvan < 0 || danhSachHocsinh[i].diemvan > 10);

        // Nhập điểm ngoại ngữ
        do {
            cout << "Nhap diem ngoai ngu (0-10): ";
            cin >> danhSachHocsinh[i].diemnn;
        } while (danhSachHocsinh[i].diemnn < 0 || danhSachHocsinh[i].diemnn > 10);
    }
}

// Hàm tính điểm trung bình và phân loại học sinh
void phanloai() {
    for (const auto& hs : danhSachHocsinh) {
        float avg = hs.TinhDiemTrungBinh();
        cout << "Hoc sinh " << hs.hovaten << " - Diem trung binh: " << avg << " - Phan loai: ";
        if (avg >= 9) {
            cout << "Xuat sac" << endl;
        } else if (avg >= 8) {
            cout << "Gioi" << endl;
        } else if (avg >= 6.5) {
            cout << "Kha" << endl;
        } else if (avg >= 5) {
            cout << "Trung binh" << endl;
        } else {
            cout << "Yeu" << endl;
        }
    }
}

// Hàm tìm học sinh có điểm trung bình cao nhất
void DTBC() {
    float maxAvg = numeric_limits<float>::lowest();
    Hocsinh topStudent;

    for (const auto& hs : danhSachHocsinh) {
        float avg = hs.TinhDiemTrungBinh();
        if (avg > maxAvg) {
            maxAvg = avg;
            topStudent = hs;
        }
    }

    cout << "Hoc sinh co diem trung binh cao nhat: " << topStudent.hovaten
         << " - Diem TB: " << maxAvg << endl;
}

// Hàm tìm kiếm học sinh theo tên
void TK() {
    string ten;
    cout << "Nhap ten hoc sinh can tim: ";
    cin.ignore(); // Đảm bảo xóa ký tự newline còn lại
    getline(cin, ten);
    transform(ten.begin(), ten.end(), ten.begin(), ::tolower); // Chuyển đổi sang chữ thường

    bool found = false;
    for (const auto& hs : danhSachHocsinh) {
        string nameLower = hs.hovaten;
        transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower); // Chuyển đổi tên học sinh sang chữ thường
        if (nameLower.find(ten) != string::npos) { // Tìm kiếm không phân biệt hoa thường
            cout << "Thong tin hoc sinh: " << hs.hovaten << ", Diem Van: "
                 << hs.diemvan << ", Diem Toan: " << hs.diemtoan
                 << ", Diem Ngoai ngu: " << hs.diemnn << endl;
            found = true; // Đánh dấu là đã tìm thấy
        }
    }

    if (!found) {
        cout << "Khong tim thay hoc sinh co ten: " << ten << endl;
    }
}



// Hàm xuất danh sách học sinh có điểm toán thấp nhất
void DTTN() {
    float minDiemToan = numeric_limits<float>::max();
    for (const auto& hs : danhSachHocsinh) {
        if (hs.diemtoan < minDiemToan) {
            minDiemToan = hs.diemtoan;
        }
    }

    cout << "Danh sach hoc sinh co diem toan thap nhat (" << minDiemToan << "):" << endl;
    for (const auto& hs : danhSachHocsinh) {
        if (hs.diemtoan == minDiemToan) {
            cout << hs.hovaten << endl;
        }
    }
}

int main() {
    input() ;
    cout << "1. Nhap thong tin n hoc sinh." << '\n'
         << "2. Phan loai hoc sinh." << '\n'
         << "3. Tim kiem hoc sinh co diem trung binh cao nhat." << '\n'
         << "4. Tim kiem hoc sinh theo ten." << '\n'
         << "5. Xuat danh sach hoc sinh co diem toan thap nhat." << '\n'
         << "6. Thoat chuong trinh." << '\n';

    while (true) {
        int cn;
        cout << "Chon chuc nang (1 -> 6): ";
        cin >> cn;
        if (cn == 1) {
            input();
        } else if (cn == 2) {
            phanloai();
        } else if (cn == 3) {
            DTBC();
        } else if (cn == 4) {
            TK();
        } else if (cn == 5) {
            DTTN();
        } else if (cn == 6) {
            break;  // Thoát chương trình
        } else {
            cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    }

    cout << "Chuong trinh ket thuc" << endl;
    return 0;
}
