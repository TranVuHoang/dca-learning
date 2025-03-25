/*----------------------------------------------------------
# Name file     : data.cpp
# Subject       : Định nghĩa nội dung của phương thức
#                 bên ngoài lớp DATA
# Phương thức   : 
#   1. DATA::DATA(); Phương thức khởi tạo
#   2. DATA::readFile(); Phương thức đọc file data
-----------------------------------------------------------*/
#include "data.h"

/* Phương thức khởi tạo DATA*/
//DATA::DATA() {
//    c = 200; // tham số tuỳ chỉnh
//    n(0); // số hàng của data 
//    d; // số cột của data
//    q; // số lớp của từng bộ data
//}
DATA::DATA() : c(100), n(0), d(0), q(0) {}

/* 2. Method to read data from data.txt */
void DATA::readFile() {
    ifstream file("./iris.txt");

    if (!file) {
        cerr << "Khong the mo file!\n";
        return;
    }
    string line;

    // Duyệt qua các dòng 
    while (getline(file, line)) {
        if (line.empty()) continue;  // Bỏ qua dòng trống

        stringstream ss(line);
        vector<string> values;
        string value;
        vector<double> row;

        // Xác định dấu phân tách: Nếu có dấu ',' thì dùng ',', ngược lại dùng '\t'
        char delimiter = (line.find(',') != string::npos) ? ',' : '\t';

        while (getline(ss, value, delimiter))
            values.push_back(value);

        try {
            for (int i = 0; i < values.size() - 1; i++)
                row.push_back(stod(values[i])); // Chuyển thành số

            x.push_back(row);
            y.push_back(stoi(values.back()));
        }
        catch (const invalid_argument&) {
            cerr << "Loi: '" << value << "' khong phai so hop le!\n";
        }
    }

    if (!x.empty()) {
        n = (int)x.size();
        d = (int)x[0].size();
    }
    else {
        cerr << "Dữ liệu không hợp lệ hoặc trống!\n";
    }

    file.close();
}