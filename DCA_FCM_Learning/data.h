/*-------------------------------------------------
# Name file : data.h 
# Subject   : Định nghĩa khung của lớp DATA
#             (thuộc tính-phương thức)
-------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class DATA {
    public:
        /* Khai báo các thuộc tính: biến, tham sô đầu vào */
        vector<vector<double>> x; // biến x để lưu mảng data
        vector<double> y; // biến y: để lưu mảng class(cột class)

        int n; // số hàng của data
        int d; // số cột của data
        int c; // số tâm cần phân nhóm

        double rho;

        /* ---- Methods start --- */
        // 1. Constructor Method ✅
        DATA();

        // 2. Method to read data from data.txt✅
        void readFile();
        /* ---- Methods end --- */
};