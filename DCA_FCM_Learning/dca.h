/*-------------------------------------------------
# Name file : dca.h
# Subject   : Định nghĩa khung của lớp DCA
# Methods	: 1. GradientH, 2. GradientG, 3. Obj
-------------------------------------------------*/
#include "data.h"
class DCA :public DATA {

public:
	vector<vector<double>> u;
	vector<vector<double>> v;

	vector<vector<double>> u_new;
	vector<vector<double>> v_new;
	vector<vector<double>> u_2;
	vector<vector<double>> v_2;

	double m = 1.2; // m là tham số chỉ độ mờ, giá trị [1.1 - 5] tuỳ chỉnh theo từng bộ dữ liệu
	double epsilon = 0.00001;

	void InitRandom();
	void GradientH();
	void GradientG();
	bool Stop();
	void Objective();
};