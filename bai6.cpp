#include <iostream>
#include <vector>
#define ll long long
using namespace std;

// Hàm nhập hai mảng
void input(vector<ll>& a, vector<ll>& b) {
    int pta, ptb; // số phần tử trong mảng a và b
    cout << "Nhap so phan tu trong a va b: ";
    cin >> pta >> ptb;

    // Resize vector để chứa số phần tử nhập vào
    a.resize(pta);
    b.resize(ptb);

    cout << "Nhap phan tu mang a: ";
    for (int i = 0; i < pta; i++) {
        cin >> a[i];
    }

    cout << "Nhap phan tu mang b: ";
    for (int i = 0; i < ptb; i++) {
        cin >> b[i];
    }
}

// Hàm tính toán bảng LPS
void LPS(const vector<ll>& a, vector<int>& lps) {
    int m = a.size();
    int length = 0; // Độ dài của tiền tố dài nhất cũng là hậu tố
    lps[0] = 0;     // lps[0] luôn bằng 0

    int i = 1;
    while (i < m) {
        if (a[i] == a[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Hàm tìm kiếm mảng con và lưu vị trí
vector<int> KMPSearch(const vector<ll>& a, const vector<ll>& b) {
    int m = a.size();
    int n = b.size();

    // Tạo bảng LPS
    vector<int> lps(m);
    LPS(a, lps);

    vector<int> con; // Mảng lưu các vị trí xuất hiện
    int i = 0; // Chỉ số cho mảng b
    int j = 0; // Chỉ số cho mảng a

    while (i < n) {
        if (a[j] == b[i]) {
            i++;
            j++;
        }

        if (j == m) {
            con.push_back(i - j); // Lưu vị trí xuất hiện vào mảng
            j = lps[j - 1]; // Tiếp tục tìm kiếm
        } else if (i < n && a[j] != b[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return con; // Trả về mảng chứa các vị trí xuất hiện
}

// Hàm xuất thông tin về số lần xuất hiện và vị trí
void output(const vector<int>& con) {
    cout << "So lan mang con xuat hien: " << con.size() << endl;
    if (!con.empty()) {
        cout << "Vi tri xuat hien cua mang con: ";
        for (int pos : con) {
            cout << pos << " ";
        }
        cout << endl;
    } else {
        cout << "Khong tim thay mang con." << endl;
    }
}

int main() {
    vector<ll> a, b;

    // Nhập hai mảng
    input(a, b);
    if( a.size() == 0 )
    {
        cout << "không xuất hiện mảng con" ;
    }

    // Tìm kiếm mảng con và lưu vị trí xuất hiện
    vector<int> con = KMPSearch(a, b);

    // Xuất kết quả
    output(con);

    return 0;
}
// có tham khảo phần cài đặt