#include "dca.h"

/*------------- Hàm khởi tạo random start ---------------*/
void DCA::initRandom() {
	// Cấp phát kích thước cho w, b, xi
	w.resize(q, vector<double>(d, 0.0)); // khai báo biến w - kích thước (Q × d)
    b.resize(q, 0.0); // Khai báo biến b - kích thước (Q x 1)
	xi.resize(n, vector<double>(q, 0.0)); // Khai báo biến 𝜉 (xi) - kích thước (nxQ)

    // Tạo bộ khởi tạo ngẫu nhiên
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> dist(0.1, 1.0);

    // Khởi tạo giá trị ngẫu nhiên cho w
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < d; j++) {
            w[i][j] = dist(gen);  
        }
    }

    // Khởi tạo giá trị ngẫu nhiên cho b
    for (int i = 0; i < q; i++) {
        b[i] = dist(gen);
    }

    // Khởi tạo giá trị ngẫu nhiên cho xi
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            xi[i][j] = dist(gen);  
        }
    }

    /* Debug kết quả w[][], b[], xi[][] start*/
    //cout << "Matrix random w(" << q << "x" << d << ")" << endl;
    //for (int i = 0; i < q; i++) {
    //    for (int j = 0; j < d; j++) {
    //        cout << w[i][j] << " ";
    //    }
    //    cout << endl;
    //}

    //cout << endl << "Vector radom b[]: " << endl;
    //for (int i = 0; i < q; i++) {
    //    cout << b[i] << " ";
    //}
    //cout << endl;
    //
    //cout << "Matrix random xi(" << n << "x" << q << ")" << endl;
    //for (int i = 0; i < n; i++) {
    //    for (int j = 0; j < q; j++) {
    //        cout << xi[i][j] << " ";
    //    }
    //    cout << endl;
    //}
    /* Debug kết quả w[][], b[], xi[][] end*/
}
/*------------- Hàm khởi tạo random end ---------------*/

/*------------- Step 1️: Hàm tính đạo hàm của H theo công thức (16) start ------------------*/
void DCA::GradientH() {
    w_new.resize(q, vector<double>(d, 0.0)); // Khai báo w_new có kích thước: (qxd)✅
    b_new.resize(q, 0.0); // Khai báo b_new có kích thước: (qx1)✅
    xi_new.resize(n, vector<double>(q, 0.0)); // Khai báo xi_new có kích thước: (nxq)✅

    // Công thức (16) tính w_new
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            if (w[k][j] >= 0) {
                w_new[k][j] = alpha * (1 - exp(-alpha * w[k][j]));
            }
            else {
                w_new[k][j] = -alpha * (1 - exp(alpha * w[k][j]));
            }
        }
    }

    /*Debug kết quả w_new, b_new, xi_new start*/
    //w_new
    //cout << endl << "Matrix w_new[][]:" << endl;
    //for (int i = 0; i < q; i++)
    //{
    //    for (int j = 0; j < d; j++)
    //        cout << w_new[i][j] << " ";
    //    cout << endl;
    //}

    //// b_new
    //cout << endl << "Vector b_new[]:" << endl;
    //for (int i = 0; i < q; i++)
    //{
    //    cout << b_new[i] << " ";
    //}

    ////xi_new
    //cout << endl << "Matrix xi_new[][]:" << endl;
    //for (int i = 0; i < q; i++) {
    //    for (int i = 0; i < n; i++)
    //    {
    //        for (int j = 0; j < q; j++)
    //            cout << xi_new[i][j] << " ";
    //        cout << endl;
    //    }
    //}
    /*Debug kết quả w_new, b_new, xi_new end*/
}
/*------------- Hàm tính đạo hàm của H theo công thức (16) end ------------------*/

/*------------- Step 2: Compute Xl+1 theo công thức (18) start ------------------*/
bool DCA::solveCPlex() {
    // Cấp phát kích thước cho w_2, b_2, xi_2
    w_2.resize(q, vector<double>(d, 0.0)); // khai báo biến w - kích thước (Q × d) ✅
    b_2.resize(q, 0.0); // Khai báo biến b_2 - kích thước (Q x 1) ✅
    xi_2.resize(n, vector<double>(q, 0.0)); // Khai báo biến xi_2 - kích thước (nxQ) ✅

    IloModel model(env); // Khởi tạo mô hình 

    // Khai báo biến w ✅
    IloArray<IloNumVarArray> w(env, q); // ma trận trọng số (biến w) ✅
    for (int i = 0; i < q; ++i) {
        w[i] = IloNumVarArray(env, d, -IloInfinity, IloInfinity); // Biến w có miền xác định thuộc R(-vô cùng, +vô cùng) ✅ 
    }

    // Khai báo biến b ✅
    IloNumVarArray b(env, q, -IloInfinity, IloInfinity); // Biến b có miền xác định thuộc R(-vô cùng, +vô cùng) ✅

    // Khai báo biến 𝜉(xi) ✅
    IloArray<IloNumVarArray> xi(env, n);// ma trận biến slack (biến xi) ✅
    for (int i = 0; i < n; ++i) {
        xi[i] = IloNumVarArray(env, q, 0, IloInfinity, ILOFLOAT); // Biến xi có miền xác định R+ (0, +vô cùng) ✅
    }

    // Khai báo biến trung gian (biến t) ✅
    IloArray<IloNumVarArray> t(env, q);
    for (int i = 0; i < q; ++i) {
        t[i] = IloNumVarArray(env, d, -IloInfinity, IloInfinity);
    }

    // 2. Xây dựng hàm mục tiêu theo công thức (18)
    IloExpr objective(env);

    // vế đầu trong hàm mục tiêu công thức (18) ✅
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i] - 1) {
                objective += c * xi[i][k];
            }
        }
    }

    // vế thứ 2 trong hàm mục tiêu công thức (18) ✅
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            objective += t[k][j]; // tổng biến trung gian
        }
    }

    // vế cuối trong hàm mục tiêu công thức (18) ✅
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            objective -= w_new[k][j] * w[k][j];
        }
    }

    // add chuẩn l2-l0  công thức (4) ✅
    int l2 = 0;
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            if (l2 == 1) {
                objective += beta * w[k][j] * w[k][j];
            }
        }
    }

    model.add(IloMinimize(env, objective)); // Thêm hàm mục tiêu
    objective.end(); // Giải phóng bộ nhớ

    // 3. `Thêm các ràng buộc (constraints) của công thức (18)
    // constraints 1: tính Omega theo công thức (2): Phân loại đa lớp MSVM
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i] - 1) { // chỉ áp dụng với lớp khác nhãn thực tế
                IloExpr constraint1(env);

                for (int j = 0; j < d; j++)
                {
                    constraint1 += (w[y[i] - 1][j] - w[k][j]) * x[i][j];
                }
                constraint1 += (b[y[i] - 1] - b[k]);

                model.add(constraint1 >= 1 - xi[i][k]); // điều kiện phân loại
                constraint1.end();
            }
        }
    }

    // constraints 2: tính t >= alpha * w
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            IloExpr constraint2(env);
            constraint2 = t[k][j];
            model.add(constraint2 >= alpha * w[k][j]);
            constraint2.end();
        }
    }

    // constraints 3: tính t >= -alpha * w
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            IloExpr constraint3(env);
            constraint3 = t[k][j];
            model.add(constraint3 >= -alpha * w[k][j]);
            constraint3.end();
        }
    }

    // Giải bài toán
    IloCplex cplex(model);
    cplex.exportModel("D:/CPLEX.LP");
    cplex.setOut(env.getNullStream()); // Suppress solver output

    if (!cplex.solve())
    {
        env.error() << "Failed to solve the problem" << endl;
        return false;
    }

    // Lấy kết quả đầu ra: w_2
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            w_2[k][j] = cplex.getValue(w[k][j]);
        }
    }

    for (int i = 0; i < n; i++)
        for (int k = 0; k < q; k++)
            xi_2[i][k] = 0;

    // Lấy kết quả đầu ra: xi_2
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            xi_2[i][k] = cplex.getValue(xi[i][k]);
        }
    }

    // Lấy kết quả đầu ra: b_2
    for (int i = 0; i < q; i++) {
        b_2[i] = cplex.getValue(b[i]);
    }

    //cout << endl << "Matrix w_2:" << endl;
    //for (int i = 0; i < q; i++)
    //{
    //    for (int k = 0; k < d; k++)
    //        cout << w_2[i][k] << " ";
    //    cout << endl;
    //}
}
/*------------- Step 2: Compute Xl+1 theo công thức (18) end ------------------*/

/* Tính hàm mục tiêu ban đầu công thức (4) - start*/
void DCA::getOBJ_EXP(double& obj)
{
    double total = 0;

    // vế đầu của công thức (4)
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i] - 1) {
                total += c * xi[i][k];
            }
        }
    }

    // vế 2 của công thức (4)
    int l2 = 0;
    if (l2 == 1)
    {
        for (int k = 0; k < q; k++)
            for (int j = 0; j < d; j++)
                total += beta * w[k][j] * w[k][j];
    }

    // vế 3 của công thức (4) phải tính theo công thức (13)
    for (int k = 0; k < q; k++)
        for (int j = 0; j < d; j++)
            if (w[k][j] >= 0)
                total += alpha * (1 - exp(-alpha * w[k][j]));
            else
                total += -alpha * (1 - exp(alpha * w[k][j]));
}
/* Tính hàm mục tiêu ban đầu - end*/

/* Tính hàm mục tiêu ở mỗi bước lặp công thức (4) - start*/
void DCA::getOBJ2_EXP(double& obj)
{
    double total = 0;

    // vế đầu của công thức (4)
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i] - 1) {
                total += c * xi_2[i][k];
            }
        }
    }

    // vế 2 của công thức (4)
    int l2 = 0;
    if (l2 == 1)
    {
        for (int k = 0; k < q; k++)
            for (int j = 0; j < d; j++)
                total += beta * w_2[k][j] * w_2[k][j];
    }

    // vế 3 của công thức (4) phải tính theo công thức (13)
    for (int k = 0; k < q; k++)
        for (int j = 0; j < d; j++)
            if (w[k][j] >= 0)
                total += alpha * (1 - exp(-alpha * w_2[k][j]));
            else
                total += -alpha * (1 - exp(alpha * w_2[k][j]));
}
/* Tính hàm mục tiêu ban đầu - end*/

/* Điều kiện dừng start */
void DCA::checkFrobeniusNorm(double& norm_frobenius) {
    // tính vế trái của điều kiện dừng: || X(l-1) - X(l) || 
    double norm_left = 0.0;
    double norm_left_w = 0.0;
    double norm_left_b = 0.0;
    double norm_left_xi = 0.0;

    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            double diff = w_2[k][j] - w[k][j];
            norm_left_w += diff * diff;
        }         
    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            double diff = xi_2[i][k] - xi[i][k];
            norm_left_xi += diff * diff;
        }
    }

    for (int i = 0; i < q; i++) {
        double diff = b_2[i] - b[i];
        norm_left_b += diff * diff;
    }

    norm_left = sqrt(norm_left_w + norm_left_b + norm_left_xi);

    // tính về phải của điều kiện dừng
    double norm_right = 0.0;
    double norm_right_w = 0.0;
    double norm_right_b = 0.0;
    double norm_right_xi = 0.0;

    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            norm_right_w = w[k][j] * w[k][j];
        }
    }

    for (int i = 0; i < q; i++) {
        norm_right_b += b[i] * b[i];
    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            norm_right_xi = xi[i][k] * xi[i][k];
        }
    }
    norm_right = sqrt(norm_right_w + norm_right_b + norm_right_xi);

    norm_frobenius = norm_left / norm_right;
}
/* Điều kiện dừng end */

/* ------------------ Update w, b, xi start ------------------- */
void DCA::updateMembership() {
    // cập nhật w2
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            w[k][j] = w_2[k][j];
        }
    }
    
    // cập nhật xi_2
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            xi[i][k] = xi_2[i][k];
        }
    }

    // cập nhật b_2
    for (int i = 0; i < d; i++) {
        b[i] = b_2[i];
    }
}
/* ------------------ Update w, b, xi end ------------------- */