/*----------------------------------------------------------
# Name file     : func.cpp
# Subject       : Định nghĩa nội dung của phương thức
#                 bên ngoài lớp CALCULATE
# ClassName		: DCA
# Method:
#	1. void Calculate()
-----------------------------------------------------------*/
#include "func.h"

/* Tính chuẩn 2*/
double CALCULATE::SquareEuclidean(const std::vector<double>& vector1, const std::vector<double>& vector2) {
    if (vector1.size() != vector2.size()) {
        std::cerr << "Error: Vectors must have the same size!" << std::endl;
        return -1;
    }
    double distance = 0.0;

    for (size_t i = 0; i < vector1.size(); i++) {
        distance += std::pow(vector1[i] - vector2[i], 2);
    }

    return distance;
}
