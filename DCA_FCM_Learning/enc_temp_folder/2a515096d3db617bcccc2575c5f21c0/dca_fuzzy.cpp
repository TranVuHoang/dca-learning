/*------------------------------------------------
# Author	: TRAN VU HOANG
# Date		: 01-03-2025
# Language	: Cplusplus						
# Version	: 1.00							
# Subject	: Fuzzy Clustering Algorithm
# Name		: dca_fuzzy.cpp							
--------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Hàm đọc file và trả về mảng 2D
void readFile(vector<vector<double>> & x, vector<double> & y) {
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

    file.close();
}

int main() {
    /*----------------------------
    # Đọc dữ liệu data.txt
    ----------------------------*/
    vector<vector<double>> x;
    vector<double> y;
    readFile(x, y);

    
    /*----------------------------
    # Định nghĩa các tham số
    ----------------------------*/
    int numIter = 0;

    /*Tính đạo hàm của H*/

    /*Tính đạo hàm của G*/

    return 0;
}