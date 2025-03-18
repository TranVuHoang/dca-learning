/*----------------------------------------------------------
# Name file     : dca.cpp
# Subject       : Định nghĩa nội dung của phương thức
#                 bên ngoài lớp DCA
# ClassName		: DCA
# Main method: 
#	1. void GradientH()
#	2. void GradientG()
#	3. void Objective()
#   ...
-----------------------------------------------------------*/
#include "dca.h"
//#include "func.h"
#include <random>
#include <cassert> // Để kiểm tra điều kiện

// Hàm tính khoảng cách Euclid - bình phương giữa hai vector(tính chuẩn 2 của hiệu 2 vector - bình phương)
// || xk - vi ||^2
double SquareEuclidean(const vector<double>& vector1, const vector<double>& vector2) {
	// Kiểm tra kích thước hai vector
	assert(vector1.size() == vector2.size() && "Vectors must have the same size!");

	double distance = 0.0;
	int sizeVector = (int)vector1.size();

	// Tính tổng bình phương hiệu của từng phần tử
	for (int i = 0; i < sizeVector; i++) {
		double diff = vector1[i] - vector2[i];
		distance += diff * diff;
	}
	return distance;
}

/* Tính tham số bán kính r theo công thức 3.2 */
//Hàm tính tổng bình phương của một vector(chuẩn 2 bình phương của 1 vector)
double SquareNormVector(vector<double>& vec) {
	double sum = 0.0;
	int sizeVector = (int)vec.size();

	for (int i = 0; i < sizeVector; i++)
		sum += vec[i] * vec[i];
	return sum;
}

// Hàm tính r ✅
double	R_Calculated(vector<vector<double>>& vec) {
	double result = 0.0;
	int sizeVector = (int)vec.size();

	for (int i = 0; i < sizeVector; i++) {
		result += SquareNormVector(vec[i]);
	}
	return sqrt(result);
}

// Hàm tính alpha theo công thức α = r + max ‖xₖ‖ ✅
double CalculateAlpha(vector<vector<double>>& vec) {
	double r = R_Calculated(vec);  // Gọi hàm tính r

	double max_norm = 0.0;

	for (auto& v : vec) {
		max_norm = max(max_norm, sqrt(SquareNormVector(v)));  // Lấy norm-2
	}

	return r + max_norm;
}

// Hàm tính rho theo công thức (29) ✅
double CaclulateRho(double m, vector<vector<double>>& vec) {
	int n = (int) vec.size();
	double alpha_squared = CalculateAlpha(vec) * CalculateAlpha(vec);
	double temp = m * (2 * m - 1) * alpha_squared / n;

	return temp + sqrt(temp * temp + 16 * m * m * alpha_squared / n);
}

/*---------- Hàm khởi tạo random u, v start----------*/
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
/*---------- Hàm khởi tạo random u, v end----------*/

/*---------- Hàm tính đạo hàm của H start----------*/
void DCA::GradientH() {
	u_new.resize(c, vector<double>(n)); // Khai báo u_new có kích thước: (cxn)✅
	v_new.resize(c, vector<double>(d)); // Khai báo v_new có kích thước: (cxd)✅
	// input: x✅, v✅, u✅, m✅, rho✅

	double rho = CaclulateRho(m, x);

	// Tính u_new ✅
	for (int i = 0; i < c; i++) {
		for (int k = 0; k < n; k++) {
			double dtemp = SquareEuclidean(x[k], v[i]); // Khoảng cách Euclid bình phương
			double u_pow = pow(u[i][k], (2 * m - 1.0)); // Tính trước giá trị mũ
			u_new[i][k] = rho * u[i][k] - (2 * m * u_pow * dtemp);
		}
	}

	vector<vector<double>> temp(c, vector<double>(d, 0.0)); // Khởi tạo vector temp với d phần tử 0.0

	// Tính v_new ✅
	for (int i = 0; i < c; i++) {
		vector<double> temp(d, 0.0);
			
		for (int k = 0; k < n; k++) {
			double u_pow = pow(u[i][k], (2 * m)); // Tính trước giá trị mũ

			for (int l = 0; l < d; l++) {
				temp[l] += (v[i][l] - x[k][l]) * u_pow;
			}
		}

		for (int l = 0; l < d; l++) {
			v_new[i][l] = rho * v[i][l] - 2 * temp[l]; // Cập nhật V_l+1 sau khi tính xong temp
		}
	}

}
/*---------- Hàm tính đạo hàm của H end----------*/

/*---------- Hàm tính đạo hàm của G start----------*/
void DCA::GradientG() {
	// input: u_new, V_l+1
	u_2.resize(c, vector<double>(n)); // Khai báo u_2 có kích thước: (cxn)✅
	v_2.resize(c, vector<double>(d)); // Khai báo v_2 có kích thước: (cxd)✅

	double r = R_Calculated(x); // 97,67
	double alpha = CalculateAlpha(x); // 108.78
	double rho = CaclulateRho(m, x); // 271.75

	// Tính v_2
	for (int i = 0; i < c; i++) {
		double norm = 0;
		double result = 0;

		for (int l = 0; l < d; l++) {
			result += v_new[i][l] * v_new[i][l];  // Tính norm2(v[i])
		}
		norm = sqrt(result);  // tính norm

		double factor = (norm <= rho * r) ? (1.0 / rho) : (r / norm);
		
		for (int l = 0; l < d; l++) {
			v_2[i][l] = v_new[i][l] * factor;
		}

	}

	// Tính u_2
	for (int i = 0; i < c; i++) {
		double norm = 0;

		for (int k = 0; k < n; k++) {
			norm += u_new[i][k] * u_new[i][k];  // Tính norm2 của u_new
		}
		// Nếu norm > 1, chuẩn hóa; ngược lại, sao chép trực tiếp
		double norm_inv = (norm > 1.0) ? 1.0 / sqrt(norm) : 1.0;

		for (int k = 0; k < n; k++) {
			u_2[i][k] = u_new[i][k] * norm_inv;// kết quả trả về mảng u_2
		}
	}
}
/*---------- Hàm tính đạo hàm của G end ----------*/

/*---------- Hàm mục tiêu start ----------*/
// Hàm mục tiêu ban đầu
void DCA::computeJ2mOriginal(double& J2m) {
	J2m = 0.0;

	// Duyệt qua từng điểm dữ liệu x_k
	for (int k = 0; k < n; k++) {
		// Duyệt qua từng tâm cụm v_i
		for (int i = 0; i < c; i++) {
			double t_power = pow(u[i][k], 2 * m);  // u_2^{2m}
			double dist2 = SquareEuclidean(x[k], v[i]); // ||x_k - v_i||^2
			J2m += t_power * dist2; // kết quả trả về giá trị hàm mục tiêu
		}
	}
}

// Hàm mục tiêu: tính J_{2m}(T, V)
void DCA::computeJ2m(double& J2m) { // Truyền J2m vào để cập nhật giá trị
	J2m = 0.0;

	// Duyệt qua từng điểm dữ liệu x_k
	for (int k = 0; k < n; k++) {
		// Duyệt qua từng tâm cụm v_i
		for (int i = 0; i < c; i++) {
			double t_power = pow(u_2[i][k], 2 * m);  // u_2^{2m}
			double dist2 = SquareEuclidean(x[k], v_2[i]); // ||x_k - v_i||^2
			J2m += t_power * dist2; // kết quả trả về giá trị hàm mục tiêu
		}
	}
}
/*---------- Hàm mục tiêu end ----------*/

/*---------- Điều kiện dừng start ----------*/
void DCA::checkFrobeniusNorm(double& norm_frobenius) {
	double norm_diff = 0.0;
	double norm_diff1 = 0.0; // Chuẩn 2 của T_l+1 - T_l
	double norm_diff2 = 0.0; // Chuẩn 2 của V_l+1 - V_l

	// Tính ||T_l+1 - T_l||^2
	for (int i = 0; i < c; i++) {
		for (int k = 0; k < n; k++) {
			double diff = u_2[i][k] - u[i][k];
			norm_diff1 += diff * diff;
		}
	}

	// Tính ||V_l+1 - V_l||^2
	for (int i = 0; i < c; i++) {
		for (int j = 0; j < d; j++) {
			double diff = v_2[i][j] - v[i][j];
			norm_diff2 += diff * diff;
		}
	}
	// Tổng hai chuẩn bình phương
	norm_diff = norm_diff1 + norm_diff2;

	// Lấy chuẩn Frobenius
	norm_frobenius = sqrt(norm_diff);
}
/*---------- Điều kiện dừng end ----------*/

/*---------- Update U,V start ----------*/
void DCA::updateMembership() {
    // Cập nhật tâm cụm v_2
    for (int i = 0; i < c; i++) {
        for (int k = 0; k < d; k++) {
			v[i][k] = v_2[i][k];
        }
    }

    // Cập nhật ma trận thành viên u_2
    for (int i = 0; i < c; i++) {
        for (int k = 0; k < n; k++) {
			u[i][k] = u_2[i][k];
        }
    }
}
/*---------- Update U,V end ----------*/
