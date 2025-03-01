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
vector<vector<double>> readFile() {
    ifstream file("./iris.txt");

    if (!file) {
        cerr << "Khong the mo file!\n";
        return {}; // Trả về mảng rỗng nếu không mở được file
    }

    vector<vector<double>> x;  // Mảng động 2D
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;  // Bỏ qua dòng trống

        stringstream ss(line);
        string value;
        vector<double> row;

        // Xác định dấu phân tách: Nếu có dấu ',' thì dùng ',', ngược lại dùng '\t'
        char delimiter = (line.find(',') != string::npos) ? ',' : '\t';

        while (getline(ss, value, delimiter)) {
            try {
                row.push_back(stod(value)); // Chuyển thành số
            }
            catch (const invalid_argument&) {
                cerr << "Lỗi: '" << value << "' không phải số hợp lệ!\n";
            }
        }

        if (!row.empty()) {
            x.push_back(row);
        }
    }

    file.close();
    return x;  // Trả về mảng đã đọc
}

int main() {
    // Đọc dữ liệu data.txt
    vector<vector<double>> x = readFile();

    // Hiển thị dữ liệu đã đọc
    //cout << "Mang x[][] doc tu file:\n";
    //for (const auto& row : x) {
    //    for (double num : row) {
    //        cout << num << " ";
    //    }
    //    cout << endl;
    //}
    /// <summary>
    /// Xác định các tham số:
    /// 
    /// </summary>
    /// <returns></returns>


    /// <summary>
    /// Step 1: Initialize x0
    /// </summary>
    /// <returns></returns>
    int numIter = 0;

    /// <summary>
    /// Step 2: Reapeat
    /// </summary>
    /// <returns></returns>
    /*Tính đạo hàm của H*/

    /*Tính đạo hàm của G*/

    return 0;
}