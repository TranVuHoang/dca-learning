#include "dca.h"

/*------------- Hàm khởi tạo random start ---------------*/
void DCA::initRandom() {
	// Cấp phát kích thước cho w, b, xi
	w.resize(q, vector<double>(d, 0.0)); // khai báo biến w - kích thước (Q × d)
    b.resize(q, 0.0); // Khai báo biến b - kích thước (Q x 1)
	xi.resize(n, vector<double>(q, 0.0));

    // Cấp phát kích thước cho w_2, b_2, xi_2
    w_2.resize(q, vector<double>(d, 0.0)); // khai báo biến w - kích thước (Q × d)
    b_2.resize(q, 0.0); // Khai báo biến b_2 - kích thước (Q x 1)
	xi_2.resize(n, vector<double>(q, 0.0)); // Khai báo biến xi_2 - kích thước (nxQ)

    // Tạo bộ khởi tạo ngẫu nhiên
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> dist(0.1, 1.0);

    // Khởi tạo giá trị cho w
    for (int i = 0; i < q; i++) {
        for (int j = 0; j < d; j++) {
            w[i][j] = dist(gen);  
        }
    }

    // Khởi tạo giá trị cho xi
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < q; j++) {
            xi[i][j] = dist(gen);  
        }
    }

    // Khởi tạo giá trị cho b
    for (int i = 0; i < q; i++) {
        b[i] = dist(gen);  
    }
}
/*------------- Hàm khởi tạo random end ---------------*/

/*------------- Step 1️: Hàm tính đạo hàm của H theo công thức (16) start ------------------*/
void DCA::GradientH() {
    w_new.resize(q, vector<double>(d)); // Khai báo w_new có kích thước: (qxd)✅
    //tinh xi_new, b_new
    b_new.resize(q, 0.0);
    xi_new.resize(n, vector<double>(q, 0.0));
    // Công thức (16)
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
    //for (int i = 0; i < q; i++)
    //{
    //    for (int j = 0; j < d; j++)
    //        cout << w_new[i][j] << " ";
    //    cout << endl;
    //}
    //cout << endl;
    //for (int i = 0; i < n; i++)
    //{
    //    for (int j = 0; j < q; j++)
    //        cout << xi_new[i][j] << " ";
    //    cout << endl;
    //}

    //cout << endl;
    //for (int i = 0; i < q; i++)
    //{
    //    cout << b_new[i] << " ";
    //}
}
/*------------- Hàm tính đạo hàm của H theo công thức (16) end ------------------*/

/*------------- Step 2: Compute Xl+1 theo công thức (18) start ------------------*/
bool DCA::solveCPlex() {
    IloModel model(env); // Khởi tạo mô hình 

    // 1. Khai báo các biến quyết định
    IloArray<IloNumVarArray> w(env, q); // ma trận trọng số (biến w) ✅
    IloNumVarArray b(env, q, -IloInfinity, IloInfinity); // vector bias (biên b) ✅
    IloArray<IloNumVarArray> xi(env, n);// biến slack (biến xi) ✅
    IloArray<IloNumVarArray> t(env, q); // biến trung gian (biến t) ✅

    for (int i = 0; i < q; ++i) {
        w[i] = IloNumVarArray(env, d, -IloInfinity, IloInfinity); //✅
        t[i] = IloNumVarArray(env, d, -IloInfinity, IloInfinity); // ✅  
    }
    
    for (int i = 0; i < n; ++i) {
        xi[i] = IloNumVarArray(env, q); //✅
    }

    /*for (int i = 0; i < q; ++i) {
        t[i] = IloNumVarArray(env, d, -IloInfinity, IloInfinity);
    }*/

    // 2. Xây dựng hàm mục tiêu theo công thức (18)
    IloExpr objective(env);

    // vế đầu trong hàm mục tiêu công thức (18) ✅
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i]) {
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

    model.add(IloMinimize(env, objective)); // Thêm hàm mục tiêu
    objective.end(); // Giải phóng bộ nhớ

    // 3. `Thêm các ràng buộc (constraints) của công thức (18)
    // constraints 1: tính Omega: Phân loại đa lớp MSVM
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i]) { // chỉ áp dụng với lớp khác nhãn thực tế
                IloExpr constraint1(env);

                for (int j = 0; j < d; j++)
                {
                    constraint1 += (w[y[i]][j] - w[k][j]) * x[i][j];
                }
                constraint1 += (b[y[i]] - b[k]);
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
    
    // Lấy kết quả đầu ra: xi_2
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            xi_2[i][k] = cplex.getValue(xi[i][k]);
        }
    }
    
    // Lấy kết quả đầu ra: b_2
    for (int i = 0; i < q; i++)
        b_2[i] = cplex.getValue(b[i]);
}
/*------------- Step 2: Compute Xl+1 theo công thức (18) end ------------------*/