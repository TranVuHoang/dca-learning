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
	u.resize(c, vector<double> (n)); // Khai báo u có kích thước: (cxn)
	v.resize(c, vector<double> (d)); // Khai báo v có kích thước: (cxd)

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

/* Tính đạo hàm của H*/
void DCA::GradientH() {
	u_new.resize(c, vector<double>(n)); // Khai báo u_new có kích thước: (cxn)✅
	v_new.resize(c, vector<double>(d)); // Khai báo v_new có kích thước: (cxd)✅
	// input: x✅, v✅, u✅, m✅, rho✅
	/*double	temp = 0;*/

	// Tính u_new ✅
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < n; j++) {
			double dtemp = SquareEuclidean(x[j], v[i]); // Tính khoảng cách Euclid bình phương
			u_new[i][j] = rho * u[i][j] - (2 * m * pow(u[i][j], (2 * m - 1.0))) * dtemp;
		}
	}

	// Tính v_new ✅
	for (int i = 0; i < c; i++) {
		vector<double> temp(d, 0.0); // Khởi tạo vector temp với d phần tử 0.0

		for (int j = 0; j < n; j++) {
			for (int k = 0; k < d; k++) { // Duyệt qua từng chiều dữ liệu
				temp[k] += (v[i][k] - x[j][k]) * pow(u[i][j], (2 * m));
			}
		}

		for (int k = 0; k < d; k++) { // Cập nhật v_new
			v_new[i][k] = rho * v[i][k] - 2 * temp[k];
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

	// Cập nhật v_new
	for (int i = 0; i < c; i++) {
		double norm = 0.0;

		for (int j = 0; j < d; j++) {
			norm += v[i][j] * v[i][j];  // Tính norm2(v[i])
		}
		norm = sqrt(norm);  // Lấy căn bậc 2

		
		if (norm <= r * rho) {
			for (int j = 0; j < d; j++) {
				v_2[i][j] = v[i][j] / rho;
			}
		}
		else {
			for (int j = 0; j < d; j++) {
				v_2[i][j] = v[i][j] * (r / norm);
			}
		}
	}

	// Cập nhật u_new
	for (int j = 0; j < n; j++) {
		double norm = 0.0;

		for (int i = 0; i < c; i++) {
			norm += u[i][j] * u[i][j];  // Tính norm2 của cột u[:, j]
		}
		norm = sqrt(norm);

		if (norm > 1) {
			for (int i = 0; i < c; i++) {
				u_2[i][j] /= norm;  // Chuẩn hóa nếu norm > 1
			}
		}
	}


	// Gán lại giá trị cập nhật
	//u = u_new;
	//v = v_new;
	vector<vector<double>> u_2 = u;
	vector<vector<double>> v_2 = v;


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