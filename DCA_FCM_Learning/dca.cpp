/*----------------------------------------------------------
# Name file     : dca.cpp
# Subject       : Định nghĩa nội dung của phương thức
#                 bên ngoài lớp DCA
# ClassName		: DCA
# Method: 
#	1. void GradientH()
#	2. void GradientG()
#	3. void Objective()
-----------------------------------------------------------*/
#include "dca.h"
//#include "func.h"
#include <random>

// Hàm tính khoảng cách Euclid bình phương giữa hai vector(tính chuẩn 2)bình phương
double SquareEuclidean(const vector<double>& vector1, const vector<double>& vector2) {
	if (vector1.size() != vector2.size()) {
		cerr << "Error: Vectors must have the same size!" << endl;
		return -1; // Trả về -1 để báo lỗi
	}

	double distance = 0.0;

	// Tính tổng bình phương hiệu của từng phần tử
	for (size_t i = 0; i < vector1.size(); i++) {
		distance += pow(vector1[i] - vector2[i], 2);
	}

	return distance;
}

/* Khởi tạo random u, v ✅*/
void DCA::InitRandom() {
	// Cấp phát kích thước cho u, v
	u.resize(c, vector<double> (n, 0.0)); // Khai báo u có kích thước: (cxn)
	v.resize(c, vector<double> (d, 0.0)); // Khai báo v có kích thước: (cxd)

	// Tạo bộ khởi tạo ngẫu nhiên 0.1-1.0
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist(0.1, 1);

	// Khởi tạo giá trị cho u: ✅
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < n; j++) {
			u[i][j] = dist(gen);
		}
	}

	// Khởi tạo giá trị cho v: ✅
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < d; j++) {
			v[i][j] = dist(gen);
		}
	}
}

/* Tính đạo hàm của H ✅*/
void DCA::GradientH() {
	u_new.resize(c, vector<double>(n)); // Khai báo u_new có kích thước: (cxn)✅
	v_new.resize(c, vector<double>(d)); // Khai báo v_new có kích thước: (cxd)✅
	// input: x✅, v✅, u✅, m✅, rho✅
	/*double	temp = 0;*/

	// Tính u_new ✅
	for (int i = 0; i < c; i++) {
		for (int k = 0; k < n; k++) {
			double dtemp = SquareEuclidean(x[k], v[i]); // Tính khoảng cách Euclid bình phương
			u_new[i][k] = rho * u[i][k] - (2 * m * pow(u[i][k], (2 * m - 1.0))) * dtemp;
		}
	}

	vector<vector<double>> temp(c, vector<double>(d, 0.0)); // Khởi tạo vector temp với d phần tử 0.0

	// Tính v_new ✅
	//for (int i = 0; i < c; i++) {
	//	// Tính temp = ∑(k, n)[(V(i,l) - xk) * pow(t(i, k), 2m)]
	//	for (int l = 0; l < d; l++) {
	//		for (int k = 0; k < n; k++) { // Duyệt qua từng chiều dữ liệu
	//			temp[i][l] += (v[i][l] - x[k][l]) * pow(u[i][l], (2 * m));
	//		}
	//	}

	//	for (int l = 0; l < d; l++) { // Cập nhật v_new
	//		v_new[i][l] = rho * v[i][l] - 2 * temp[i][l];
	//	}
	//}
	//vector<vector<double>> temp(c, vector<double>(d, 0.0)); // Khởi tạo vector temp với d phần tử 0.0

	// Tính v_new ✅
	for (int i = 0; i < c; i++) {
		// Tính temp = ∑(k, n)[(V(i,l) - xk) * pow(t(i, k), 2m)]
		for (int l = 0; l < d; l++) {
			for (int k = 0; k < n; k++) {
				temp[i][l] += (v[i][l] - x[k][l]) * pow(u[i][l], (2 * m));
			}
			v_new[i][l] = rho * v[i][l] - 2 * temp[i][l];
		}
	}
	// ouput: u_new, v_new ✅
}

/* Tính đạo hàm của G */
void DCA::GradientG() {
	// input: u_new, v_new
	int r = 0;
	u_2.resize(c, vector<double>(n)); // Khai báo u_2 có kích thước: (cxn)✅
	v_2.resize(c, vector<double>(d)); // Khai báo v_2 có kích thước: (cxd)✅

	// Tính v_2
	for (int i = 0; i < c; i++) {
		double norm = 0;
		double result = 0;

		for (int l = 0; l < d; l++) {
			result += v[i][l] * v[i][l];  // Tính norm2(v[i])
		}
		norm = sqrt(result);  // tính norm

		double factor = (norm <= rho * r) ? (1.0 / rho) : (r / norm);
		
		for (int l = 0; l < d; l++) {
			v_2[i][l] = v[i][l] * factor;
		}

	}

	// Tính u_2
	for (int i = 0; i < c; i++) {
		double norm = 0;

		for (int k = 0; k < n; k++) {
			norm += u[i][k] * u[i][k];  // Tính norm2 của u_new
		}

		if ( norm > 1) {  // Chỉ chuẩn hóa nếu norm > 1
			double norm_inv = 1.0 / sqrt(norm); // Tính 1/norm để tránh chia nhiều lần
			
			for (int k = 0; k < n; k++) {
				u_2[i][k] *= norm_inv; 
			}
		}
	}

	// Gán lại giá trị cập nhật
	//u = u_new;
	//v = v_new;
	//vector<vector<double>> u_2 = u;
	//vector<vector<double>> v_2 = v;


	// output: u_2, v_2
	// Kiểm tra điều kiện dừng: || u_2 -u, v_2 - v|| <= epsilon
	// u = u_2, v = v_2;
}

/* Kiểm tra điều kiện dừng*/
bool DCA::Stop() {
	// Tính d = chuẩn 2 của ||(u_2, v_2) -(u, v)|| 
	//return (d < epsilon);
	return 1;
}

void DCA::Objective() {

}