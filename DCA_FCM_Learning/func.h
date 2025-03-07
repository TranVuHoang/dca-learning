/*-------------------------------------------------
# Name file : func.h
# Subject   : Định nghĩa khung của lớp FUNC
# Methods	: 1. GradientH, 2. GradientG, 3. Obj
-------------------------------------------------*/
#include "data.h"

class CALCULATE :public DATA {
public:
    static double SquareEuclidean(const std::vector<double>& vector1, const std::vector<double>& vector2);
};

