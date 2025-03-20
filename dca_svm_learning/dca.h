/*-------------------------------------------------
# Name file : dca.h
# Subject   : Định nghĩa khung của lớp DCA
# Methods	: 1. GradientH, 2. GradientG, 3. Obj
-------------------------------------------------*/
#include "data.h"

class DCA :public DATA {
public:
	vector<vector<double>> w; // biến w
	vector<vector<double>> e; // biến cờ xi
	vector<double> b; // biến b

	vector<vector<double>> w_new;
	vector<vector<double>> e_new;

	vector<vector<double>> w_2;
	vector<vector<double>> e_2;

	double beta; // Tham số của bài báo The Algorithm 2: l2 - l0 - DCA1 
	// beta = 0.1✅
	double alpha; // Tham số của bài báo The Algorithm 2: l2 - l0 - DCA1 
	// alpha = 0.9✅
	double lambda; // tham số cho  SCAD penalty function

	void initRandom(); // Hàm khởi tạo mảng ngẫu nhiên
	//void gradientH(); // Hàm tính đạo hàm của  H
};
