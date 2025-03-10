/*----------------------------------------------------------
# Name file     : data.cpp
# Subject       : Định nghĩa nội dung của phương thức
#                 bên ngoài lớp DATA
# Phương thức   : DATA::readFile
-----------------------------------------------------------*/
#include "data.h"

DATA::DATA() {
    c = 200;
    n = 150;
    d = 4;
}

/* 2. Method to read data from data.txt */
void DATA::readFile() {
    ifstream file("./iris.txt");

    if (!file) {
        cerr << "Khong the mo file!\n";
    }
    string line;

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
            cerr << "Error: '" << value << "' khong phai so hop le!\n";
        }
    }
    size_t n = x.size();
    size_t d = x[0].size();

    file.close();
}