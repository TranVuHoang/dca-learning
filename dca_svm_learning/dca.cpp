#include "dca.h"
#include <random>
#include <cassert>

/*------------- Hàm khởi tạo random start ---------------*/
void DCA::initRandom() {
	// Cấp phát kích thước cho w, e
	w.resize(c, vector<double>(n, 0.0)); // khai báo w có kích thước (cxn)
	e.resize(d, vector<double>(n, 0.0)); // Khai báo e có kích thước (dxn)

	// Tạo bộ khởi tạo ngẫu nhiên
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<double> dist(0.1, 1);

	//Khởi tạo giá trị cho w

}

/*------------- Hàm khởi tạo random end ---------------*/