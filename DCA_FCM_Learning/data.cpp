/*----------------------------------------------------------
# Name file     : data.cpp
# Subject       : Định nghĩa nội dung của phương thức 
#                 bên ngoài lớp DATA
# Phương thức   : DATA::readFile
-----------------------------------------------------------*/
#include "data.h"

/* 1. Method Constructor  */
DATA::DATA() {
    c = 3;
    rho = 1;
    d = 4;
    n = 150;
}

//DATA::DATA(int ce, int ro) {
//    c = ce;
//    rho = ro;
//}


/* 2. Method to read data from data.txt */
void DATA::readFile() {
    ifstream file("./iris.txt");

    if (!file) {
        cerr << "Khong the mo file!\n";
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
            y.push_back(stod(values.back()));
        }
        catch (const invalid_argument&) {
            cerr << "Loi: '" << value << "' khong phai so hop le!\n";
        }
    }
    size_t n = x.size(); // n = 150
    size_t d = x[0].size(); // d = 4

    file.close();
}