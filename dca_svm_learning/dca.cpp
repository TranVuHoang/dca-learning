#include "dca.h"
#include <random>
#include <cassert>

/*------------- Hàm khởi tạo random start ---------------*/
void DCA::initRandom() {
	// Cấp phát kích thước cho w, b, e
	w.resize(q, vector<double>(d, 0.0)); // khai báo biến w - kích thước (Q × d)
    b.resize(q, 0.0); // Khai báo biến b - kích thước (Q x 1)
	e.resize(n, vector<double>(q, 0.0)); // Khai báo biến e(xi) - kích thước (nxQ)

    // Tạo bộ khởi tạo ngẫu nhiên theo phân phối Gaussian N(0, 0.01)
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> dist(0.1, 1.0);  // N(0, 0.01)

    // Khởi tạo giá trị cho w
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < d; j++) {
            w[i][j] = dist(gen);  
        }
    }

    // Khởi tạo giá trị cho e(xi)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            e[i][j] = dist(gen);  
        }
    }

    // Khởi tạo giá trị cho b
    for (int i = 0; i < q; i++) {
        b[i] = dist(gen);  
    }
}

/*------------- Hàm khởi tạo random end ---------------*/