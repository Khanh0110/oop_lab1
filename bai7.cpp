#include <iostream>
#include <vector>
#include <regex>
#include <iomanip>
#include <algorithm>

using namespace std;

// Cấu trúc để lưu trữ thông tin chuyến bay
struct Chuyenbay {
    string mcb;      // Mã chuyến bay
    string ngaybay;  // Ngày bay
    string giobay;   // Giờ bay
    string noidi;    // Nơi đi
    string noiden;   // Nơi đến
};

// Hàm kiểm tra tính hợp lệ của mã chuyến bay
bool KTCB(const string &mcb) {
    regex pattern("^[A-Z]{2}\\d{1,3}$"); // Định dạng mã chuyến bay: VD: VN123
    return regex_match(mcb, pattern);
}

// Hàm kiểm tra tính hợp lệ của ngày bay
bool KTNB(const string &date) {
    // Kiểm tra định dạng ngày (DD/MM/YYYY)
    regex pattern("^\\d{2}/\\d{2}/\\d{4}$");
    if (!regex_match(date, pattern)) return false;

    int day = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int year = stoi(date.substr(6, 4));

    // Kiểm tra tháng
    if (month < 1 || month > 12) return false;
    // Kiểm tra ngày
    if (day < 1 || day > 31) return false;

    // Kiểm tra tháng 2
    if (month == 2) {
        bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        return day <= (leap ? 29 : 28);
    }

    // Kiểm tra tháng có 30 ngày
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }

    return true; // Ngày hợp lệ
}

// Hàm kiểm tra tính hợp lệ của giờ bay
bool KTGB(const string &time) {
    regex pattern("^(2[0-3]|[01]?[0-9]):[0-5][0-9]$"); // Định dạng giờ
    return regex_match(time, pattern);
}

// Hàm kiểm tra tính hợp lệ của tên địa điểm
bool KTNDi(const string &location) {
    regex pattern("^[A-Za-z\\s]{1,20}$"); // Tên địa điểm không chứa số và ký tự đặc biệt
    return regex_match(location, pattern);
}

// Hàm nhập thông tin chuyến bay
void inputChuyenBay(Chuyenbay &cb) {
    do {
        cout << "Nhap ma chuyen bay (VD: VN123): ";
        cin >> cb.mcb;
        if (!KTCB(cb.mcb)) {
            cout << "Ma chuyen bay khong hop le! Xin vui long nhap lai." << endl;
        }
    } while (!KTCB(cb.mcb)); // Nhập lại nếu không hợp lệ

    do {
        cout << "Nhap ngay bay (DD/MM/YYYY): ";
        cin >> cb.ngaybay;
        if (!KTNB(cb.ngaybay)) {
            cout << "Ngay bay khong hop le! Xin vui long nhap lai." << endl;
        }
    } while (!KTNB(cb.ngaybay)); // Nhập lại nếu không hợp lệ

    do {
        cout << "Nhap gio bay (HH:MM): ";
        cin >> cb.giobay;
        if (!KTGB(cb.giobay)) {
            cout << "Gio bay khong hop le! Xin vui long nhap lai." << endl;
        }
    } while (!KTGB(cb.giobay)); // Nhập lại nếu không hợp lệ

    do {
        cout << "Nhap noi di: ";
        cin.ignore(); // Bỏ qua ký tự newline còn lại
        getline(cin, cb.noidi);
        if (!KTNDi(cb.noidi)) {
            cout << "Noi di khong hop le! Xin vui long nhap lai." << endl;
        }
    } while (!KTNDi(cb.noidi)); // Nhập lại nếu không hợp lệ

    do {
        cout << "Nhap noi den: ";
        getline(cin, cb.noiden);
        if (!KTNDi(cb.noiden)) {
            cout << "Noi den khong hop le! Xin vui long nhap lai." << endl;
        }
    } while (!KTNDi(cb.noiden)); // Nhập lại nếu không hợp lệ
}

// Hàm in thông tin chuyến bay
void printChuyenBay(const Chuyenbay &cb) {
    cout << "Ma chuyen bay: " << cb.mcb 
         << ", Ngay bay: " << cb.ngaybay 
         << ", Gio bay: " << cb.giobay 
         << ", Noi di: " << cb.noidi 
         << ", Noi den: " << cb.noiden << endl;
}

// Hàm chính
int main() {
    vector<Chuyenbay> danhSachChuyenBay; // Danh sách các chuyến bay
    int n;

    cout << "Nhap so luong chuyen bay: ";
    cin >> n; // Nhập số lượng chuyến bay
    for (int i = 0; i < n; i++) {
        cout << "Nhap thong tin chuyen bay " << i + 1 << ":" << endl;
        Chuyenbay cb;
        inputChuyenBay(cb); // Nhập thông tin chuyến bay
        danhSachChuyenBay.push_back(cb); // Thêm vào danh sách
    }

    // Hiển thị menu
    int choice;
    do {
        cout << "\nMENU\n"
             << "1. Nhap xuat du lieu cho mot chuyen bay\n"
             << "2. Tim kiem chuyen bay\n"
             << "3. Sap xep danh sach chuyen bay\n"
             << "4. Hien thi tat ca cac chuyen bay\n"
             << "5. Dem so luong chuyen bay\n"
             << "0. Thoat\n"
             << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Chuyenbay cb;
                inputChuyenBay(cb); // Nhập thông tin chuyến bay
                danhSachChuyenBay.push_back(cb); // Thêm vào danh sách
                break;
            }
            case 2: {
                // Tìm kiếm chuyến bay theo mã chuyến bay
                string searchMcb;
                cout << "Nhap ma chuyen bay de tim kiem: ";
                cin >> searchMcb;
                bool found = false;
                for (const auto &cb : danhSachChuyenBay) {
                    if (cb.mcb == searchMcb) {
                        printChuyenBay(cb); // In thông tin chuyến bay nếu tìm thấy
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Khong tim thay ma chuyen bay: " << searchMcb << endl; // Thông báo nếu không tìm thấy
                }
                break;
            }
            case 3: {
                // Sắp xếp danh sách chuyến bay theo ngày và giờ khởi hành
                sort(danhSachChuyenBay.begin(), danhSachChuyenBay.end(), [](const Chuyenbay &a, const Chuyenbay &b) {
                    return (a.ngaybay < b.ngaybay) || (a.ngaybay == b.ngaybay && a.giobay < b.giobay);
                });

                cout << "Danh sach chuyen bay sau khi sap xep:\n";
                for (const auto &cb : danhSachChuyenBay) {
                    printChuyenBay(cb); // In danh sách chuyến bay đã sắp xếp
                }
                break;
            }
            case 4: {
                // Hiển thị danh sách tất cả chuyến bay
                cout << "\nDanh sach chuyen bay:\n";
                for (const auto &cb : danhSachChuyenBay) {
                    printChuyenBay(cb); // In thông tin từng chuyến bay
                }
                break;
            }
            case 5: {
                // Đếm số lượng chuyến bay từ một nơi đi đến một nơi đến nhất định
                string noidi, noiden;
                cout << "Nhap noi di: ";
                cin.ignore();
                getline(cin, noidi);
                cout << "Nhap noi den: ";
                getline(cin, noiden);

                int count = 0;
                for (const auto &cb : danhSachChuyenBay) {
                    if (cb.noidi == noidi && cb.noiden == noiden) {
                        count++;
                    }
                }
                cout << "So luong chuyen bay tu " << noidi << " den " << noiden << ": " << count << endl; // In số lượng chuyến bay
                break;
            }
            case 0: {
                cout << "Thoat chuong trinh." << endl;
                break;
            }
            default: {
                cout << "Chuc nang khong hop le! Xin vui long nhap lai." << endl; // Thông báo nếu chọn chức năng không hợp lệ
                break;
            }
        }
    } while (choice != 0); // Kết thúc chương trình khi chọn 0

    return 0; // Kết thúc chương trình
}
