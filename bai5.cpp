#include <iostream>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};
// Hàm kiểm tra năm nhuận
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// Hàm trả về số ngày trong tháng
int daysInMonth(int month, int year) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
        case 4: case 6: case 9: case 11:
            return 30;
        case 2:
            return isLeapYear(year) ? 29 : 28;
        default:
            return 0; // Tháng không hợp lệ
    }
}

// Hàm tìm ngày kế tiếp
Date nextDay(const Date& date) {
    Date next = date;
    if (next.day < daysInMonth(next.month, next.year)) {
        next.day++;
    } else {
        next.day = 1;
        if (next.month == 12) {
            next.month = 1;
            next.year++;
        } else {
            next.month++;
        }
    }
    return next;
}

// Hàm tìm ngày trước
Date previousDay(const Date& date) {
    Date previous = date;
    if (previous.day > 1) {
        previous.day--;
    } else {
        if (previous.month == 1) {
            previous.month = 12;
            previous.year--;
            previous.day = 31;
        } else {
            previous.month--;
            previous.day = daysInMonth(previous.month, previous.year);
        }
    }
    return previous;
}

// Hàm tính ngày thứ bao nhiêu trong năm
int dayOfYear(const Date& date) {
    int dayCount = 0;
    for (int m = 1; m < date.month; m++) {
        dayCount += daysInMonth(m, date.year);
    }
    dayCount += date.day;
    return dayCount;
}

int main() {
    Date date;
    cout << "Nhập ngày : ";
    cin >> date.day >> date.month >> date.year;

    // Kiểm tra ngày hợp lệ
    if (date.day < 1 || date.month < 1 || date.month > 12 || date.day > daysInMonth(date.month, date.year)) {
        cout << "Ngày không hợp lệ!" << endl;
        return 1;
    }

    // Tính toán và xuất kết quả
    Date next = nextDay(date);
    Date previous = previousDay(date);
    int dayOfYearValue = dayOfYear(date);

    cout << "Ngày kế tiếp: " << next.day << "/" << next.month << "/" << next.year << endl;
    cout << "Ngày trước: " << previous.day << "/" << previous.month << "/" << previous.year << endl;
    cout << "Ngày thứ " << dayOfYearValue << " trong năm." << endl;

    return 0;
}
