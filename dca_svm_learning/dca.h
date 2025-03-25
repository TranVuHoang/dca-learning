/*-------------------------------------------------
# Name file : dca.h
# Subject   : Định nghĩa khung của lớp DCA
# Methods	: 1. GradientH, 2. GradientG, 3. Obj
-------------------------------------------------*/
/*
|--------------------------------------------------------------------------
| Model Factories
|--------------------------------------------------------------------------
|
| This directory should contain each of the model factory definitions for
| your application. Factories provide a convenient way to generate new
| model instances for testing / seeding your application's database.
|
*/
#include "data.h"
#include <random>
#include <cassert>
#include <ilcplex/ilocplex.h>

ILOSTLBEGIN

class DCA :public DATA {
public:
	vector<vector<double>> w; // biến w
	vector<vector<double>> xi; // biến ξ(xi)
	vector<double> b; // biến b

	IloEnv env;
	vector<vector<double>> w_new;
	vector<vector<double>> xi_new;
	vector<double> b_new;

	vector<vector<double>> w_2;
	vector<vector<double>> xi_2;
	vector<double> b_2;

	double epsilon = 0.00001;
	double beta = 0.1; // Tham số của bài báo The Algorithm 2: l2 - l0 - DCA1 
	// beta = 0.1✅
	double alpha = 1.5; // Tham số của bài báo The Algorithm 2: l2 - l0 - DCA1 
	// với hàm xấp xỉ PiE alpha thuộc (1.5, 5) bước nhảy 0.5

	void initRandom(); // Hàm khởi tạo mảng ngẫu nhiên

	void GradientH(); // Hàm tính đạo hàm của  H
	void solveCPlex(); // giải bài toán con = CPLEX
	
	void getOBJ_EXP(double& obj); // hàm mục tiêu ban đầu
	void getOBJ2_EXP(double& obj); // hàm mục tiêu mỗi vòng lặp

	void checkFrobeniusNorm(double& norm_frobenius); // điều kiện dừng
	void updateMembership(); // cập nhật w, b, xi

	void featureselection(vector<vector<double>> w, vector<double>& feature, double threshoud = 0.01);
	int  featurecount(vector<vector<double>> w, double threshoud, vector<double>& feature);

	void preparetestset(vector<double> feature);
	void Export(string filename, vector<vector<double>> w, vector<double> b, vector<double> feature, vector<int> y_pred);
	double getAccracy(const vector<int>& y_test, const vector<int>& y_pred);
};
