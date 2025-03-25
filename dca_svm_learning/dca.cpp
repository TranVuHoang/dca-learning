#include "dca.h"

/*------------- Hàm khởi tạo random start -------------*/
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

/*------------- Step 1️: Hàm tính đạo hàm của H theo công thức (16) start --------*/
void DCA::GradientH() {
    w_new.resize(q, vector<double>(d, 0.0)); // Khai báo w_new có kích thước: (qxd)✅
    b_new.resize(q, 0.0); // Khai báo b_new có kích thước: (qx1)✅
    xi_new.resize(n, vector<double>(q, 0.0)); // Khai báo xi_new có kích thước: (nxq)✅

    w_2.resize(q, vector<double>(d, 0.0)); // khai báo biến w - kích thuớc (Q × d)
    b_2.resize(q, 0.0); // Khai báo bi?n b_2 - kích thuớc (Q x 1)
    xi_2.resize(n, vector<double>(q, 0.0)); // Khai báo biến xi_2 - kích thước (nxQ)

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

/*------------- Step 2: Compute Xl+1 theo công th?c (18) start ------------------*/
void DCA::solveCPlex() {
    IloModel model(env); // Kh?i t?o mô hình 

    // 1. Khai báo các bi?n quy?t d?nh
    IloArray<IloNumVarArray> w(env, q); // ma tr?n tr?ng s? (bi?n w) ?
    IloNumVarArray b(env, q, -IloInfinity, IloInfinity); // vector bias (biên b) ?
    IloArray<IloNumVarArray> xi(env, n);// bi?n slack (bi?n xi) ?
    IloArray<IloNumVarArray> t(env, q); // bi?n trung gian (bi?n t) ?

    for (int i = 0; i < q; ++i) {
        w[i] = IloNumVarArray(env, d, -IloInfinity, IloInfinity); //?
        t[i] = IloNumVarArray(env, d, -IloInfinity, IloInfinity); // ?  
    }

    for (int i = 0; i < n; ++i) {
        xi[i] = IloNumVarArray(env, q, 0, IloInfinity, ILOFLOAT); //?
    }

    // 2. Xây dựng hàm mục tiêu theo công thức (18)
    IloExpr objective(env);

    // v? d?u trong hàm m?c tiêu công th?c (18) ?
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i] - 1) {
                objective += c * xi[i][k];
            }
        }
    }

    // vế thứ 2 trong hàm mục tiêu công thức (18) 
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            objective += t[k][j]; // t?ng bi?n trung gian
        }
    }

    // v? cu?i trong hàm mục tiêu công th?c (18) 
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            objective -= w_new[k][j] * w[k][j];
        }
    }

    model.add(IloMinimize(env, objective)); // Thêm hàm m?c tiêu
    objective.end(); // Gi?i phóng b? nh?

    // 3. `Thêm các ràng bu?c (constraints) c?a công th?c (18)
    // constraints 1: tính Omega: Phân lo?i da l?p MSVM
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            if (k != y[i] - 1) { // ch? áp d?ng v?i l?p khác nhãn th?c t?
                IloExpr constraint1(env);

                for (int j = 0; j < d; j++)
                {
                    constraint1 += (w[y[i] - 1][j] - w[k][j]) * x[i][j];
                }
                constraint1 += (b[y[i] - 1] - b[k]);
                model.add(constraint1 >= 1 - xi[i][k]); // di?u ki?n phân lo?i
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


    // Gi?i bài toán
    IloCplex cplex(model);
    cplex.setParam(IloCplex::Param::MIP::Display, 0);
    cplex.exportModel("D:/CPLEX.LP");
    cplex.setOut(env.getNullStream()); // Suppress solver output
    

    if (!cplex.solve())
    {
        env.error() << "Failed to solve the problem" << endl;
        return ;
    }

    // Lấy kêt quả: w_2[][]
    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            w_2[k][j] = cplex.getValue(w[k][j]);
        }
    }

    //for (int i = 0; i < n; i++)
    //    for (int k = 0; k < q; k++)
    //        xi_2[i][k] = 0;

    // Lấy kết quả đầu ra: xi_2[][]
    for (int i = 0; i < n; i++)
        for (int k = 0; k < q; k++)
            if (cplex.isExtracted(xi[i][k]) != 0)
                xi_2[i][k] = cplex.getValue(xi[i][k]);

    // Lấy kết quả đầu ra: b_2[]
    for (int i = 0; i < q; i++)
        b_2[i] = cplex.getValue(b[i]);

    //debug kết quả w_2[][]
    //cout << endl << "=== Matrix w_2[][] ====" << endl;
    //for (int i = 0; i < q; i++)
    //{
    //    for (int k = 0; k < d; k++)
    //        cout << w_2[i][k] << " ";
    //    cout << endl;
    //}
}
/*------------- Step 2: Compute Xl+1 theo công th?c (18) end ------------------*/

/*------------- Tính hàm mục tiêu ban đầu công thức (4) - start -----------*/
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
                total += (1 - exp(-alpha * w[k][j]));
            else
                total += (1 - exp(alpha * w[k][j]));
    obj = total;
}
/*------------- Tính hàm mục tiêu ban đầu công thức (4) - end -------------*/

/*------------- Tính hàm mục tiêu ở mỗi bước lặp công thức (4) - start -----------*/
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
    int l2 = 1;
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
                total += (1 - exp(-alpha * w_2[k][j]));
            else
                total += (1 - exp(alpha * w_2[k][j]));
    obj = total;
}
/*------------- Tính hàm mục tiêu ở mỗi bước lặp công thức (4) - end -------------*/

/*------------- Điều kiện dừng start -----------*/
void DCA::checkFrobeniusNorm(double& norm_frobenius) {
    // tính vế trái của điều kiện dừng: || X(l-1) - X(l) || 
    double norm_left = 0.0;

    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            double diff = w_2[k][j] - w[k][j];
            norm_left += diff * diff; 
        }
    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            double diff = xi_2[i][k] - xi[i][k];
            norm_left += diff * diff;
        }
    }

    for (int i = 0; i < q; i++) {
        double diff = b_2[i] - b[i];
        norm_left += diff * diff;
    }

    norm_left = sqrt(norm_left);

    // tính về phải của điều kiện dừng: || X(l) ||
    double norm_right = 0.0;

    for (int k = 0; k < q; k++) {
        for (int j = 0; j < d; j++) {
            norm_right = w[k][j] * w[k][j];
        }
    }

    for (int i = 0; i < q; i++) {
        norm_right += b[i] * b[i];
    }

    for (int i = 0; i < n; i++) {
        for (int k = 0; k < q; k++) {
            norm_right = xi[i][k] * xi[i][k];
        }
    }
    norm_right = sqrt(norm_right);

    // Kiểm tra chia cho 0 để tránh lỗi
    if (norm_right > 1e-10) {
        norm_frobenius = norm_left / norm_right; // trả về giá trị điều kiện dừng
    }
    else {
        norm_frobenius = norm_left;  // Nếu norm_right ≈ 0 thì chỉ xét norm_left
    }
}
/*------------- Điều kiện dừng end -------------*/

/* ------------ Step 3: Update w, b, xi start ------------ */
//void DCA::updateMembership() {
//    // cập nhật w2
//    for (int k = 0; k < q; k++) {
//        for (int j = 0; j < d; j++) {
//            w[k][j] = w_2[k][j];
//        }
//    }
//    
//    // cập nhật xi_2
//    for (int i = 0; i < n; i++) {
//        for (int k = 0; k < q; k++) {
//            xi[i][k] = xi_2[i][k];
//        }
//    }
//
//    // cập nhật b_2
//    for (int i = 0; i < q; i++) {
//        b[i] = b_2[i];
//    }
//}
void DCA::updateMembership() {
    w = w_2;   // Gán toàn bộ ma trận w_2 vào w
    xi = xi_2; // Gán toàn bộ ma trận xi_2 vào xi
    b = b_2;   // Gán toàn bộ vector b_2 vào b
}
/* ------------ Step 3: Update w, b, xi end ------------ */

/*=======================================================================================
 * Hàm chọn lọc đặc trưng (Feature Selection)
 * Mục đích: Loại bỏ các đặc trưng có trọng số nhỏ, chỉ giữ lại các đặc trưng quan trọng.
 * - Tính tổng trọng số tuyệt đối của mỗi đặc trưng trên tất cả các lớp.
 * - Chuẩn hóa trọng số về khoảng [0,1].
 * - Loại bỏ các đặc trưng có trọng số nhỏ hơn ngưỡng `threshoud`.
 * - Trả về ma trận trọng số `w_tmp` sau khi lọc đặc trưng.
========================================================================================*/
void DCA::featureselection(vector<vector<double>> w, vector<double>& feature, double threshoud)
{
    if (w.empty() || w[0].empty()) {
        cerr << "Error: Ma trận w không hợp lệ!" << endl;
        return;
    }

    int q = w.size();
    int d = w[0].size();
    feature.assign(d, 0.0); // Khởi tạo feature với giá trị 0

    // Tính tổng trọng số tuyệt đối của từng đặc trưng
    for (int i = 0; i < q; i++)
        for (int j = 0; j < d; j++)
            feature[j] += abs(w[i][j]);

    // Tìm giá trị lớn nhất
    double max_value = *max_element(feature.begin(), feature.end());

    // Chuẩn hóa và lọc đặc trưng nhỏ
    if (max_value > 1e-9) {
        for (int i = 0; i < d; i++) {
            feature[i] /= max_value;
            if (feature[i] < threshoud) feature[i] = 0; // Loại bỏ đặc trưng yếu
        }
    }

    // Tạo ma trận w_tmp chỉ chứa các đặc trưng quan trọng
    vector<vector<double>> w_tmp;
    for (int i = 0; i < q; i++)
    {
        vector<double> row;
        for (int j = 0; j < d; j++)
            if (feature[j] > 0)
                row.push_back(w[i][j]);
        w_tmp.push_back(row);
    }
}

/* ------------ Lọc và cập nhật tập test dựa trên các đặc trưng được chọn ------------*/
void DCA::preparetestset(vector<double> feature) {
    int new_d = 0;
    vector<int> selected_features;

    // Xác định các cột cần giữ lại
    for (int j = 0; j < d; j++) {
        if (feature[j] > 1e-6) {  // Dùng 1e-6 thay vì 0e-6 để tránh lỗi số học dấu phẩy động
            selected_features.push_back(j);
            new_d++;
        }
    }

    // Cập nhật x_test chỉ giữ lại các cột đã chọn
    for (auto& row : x_test) {
        vector<double> new_row;
        new_row.reserve(new_d);  // Tối ưu bộ nhớ
        for (int j : selected_features) {
            new_row.push_back(row[j]);
        }
        row = std::move(new_row);  // Tránh copy không cần thiết
    }

    // Cập nhật lại số chiều đặc trưng
    d = new_d;
}

/*
 * Hàm đếm số đặc trưng quan trọng (Feature Count)
 * Mục đích: Xác định số lượng đặc trưng có trọng số lớn hơn hoặc bằng `threshoud`.
 * - Tính tổng trọng số tuyệt đối của mỗi đặc trưng trên tất cả các lớp.
 * - Chuẩn hóa trọng số về khoảng [0,1].
 * - Đếm số đặc trưng có trọng số >= `threshoud` và đánh dấu chúng.
 * - Trả về số lượng đặc trưng quan trọng.
 */
int DCA::featurecount(vector<vector<double>> w, double threshoud, vector<double>& feature)
{
    if (w.empty() || w[0].empty()) {
        cerr << "Error: Ma trận w không hợp lệ!" << endl;
        return 0;
    }

    int q = w.size();  // Số lớp
    int d = w[0].size();  // Số đặc trưng ban đầu
    feature.assign(d, 0.0); // Khởi tạo vector feature với giá trị 0

    // Bước 1: Tính tổng trọng số tuyệt đối của từng đặc trưng
    for (int i = 0; i < q; i++)
        for (int j = 0; j < d; j++)
            feature[j] += abs(w[i][j]);

    // Bước 2: Tìm giá trị lớn nhất trong feature để chuẩn hóa
    double max_value = *max_element(feature.begin(), feature.end());

    // Bước 3: Chuẩn hóa và đếm số đặc trưng quan trọng
    int count = 0;
    if (max_value > 1e-9) { // Tránh chia cho 0
        for (int i = 0; i < d; i++) {
            feature[i] /= max_value;
            if (feature[i] >= threshoud) {
                count++;
                feature[i] = 1; // Đánh dấu đặc trưng quan trọng
            }
            else {
                feature[i] = 0; // Loại bỏ đặc trưng không quan trọng
            }
        }
    }
    return count; // Trả về số lượng đặc trưng quan trọng
}

/* ------------------ Xuất kết quả mô hình ra file -------------------
 * Hàm này lưu trọng số mô hình, bias, lựa chọn đặc trưng và nhãn dự đoán vào file.
 * -------------------------------------------------------------------- */
void DCA::Export(string filename, vector<vector<double>> w, vector<double> b, vector<double> feature, vector<int> y_pred) {
    ofstream w_file(filename);

    if (!w_file.is_open())
    {
        cerr << "❌ Error: Không thể mở file '" << filename << "' để ghi." << endl;
        return; // Ngăn ghi dữ liệu vào file nếu mở thất bại
    }

    w_file << fixed << setprecision(6); // Định dạng số thực
    w_file << "Solver name: DCA-PiE" << endl;
    w_file << "Model name : MSVM-l2-l0" << endl;
    w_file << "Optimal hyperplanes :" << endl;

    // Kiểm tra và ghi trọng số w
    if (!w.empty() && !w[0].empty()) {
        for (int k = 0; k < q; k++)
        {
            for (int j = 0; j < d; j++)
            {
                if (abs(w[k][j]) > 1e-9) // Chỉ in những giá trị khác 0
                {
                    w_file << "w[" << k << "][" << j << "] = " << w[k][j] << endl;
                }
            }
        }
    }
    else {
        w_file << "⚠️ Cảnh báo: Trọng số w chưa được khởi tạo!" << endl;
    }

    w_file << "All other variables are equal to 0." << endl;

    // Kiểm tra và ghi bias b
    if (!b.empty()) {
        for (int i = 0; i < q; i++)
        {
            w_file << "b[" << i << "] = " << b[i] << endl;
        }
    }
    else {
        w_file << "⚠️ Cảnh báo: Bias b chưa được khởi tạo!" << endl;
    }


    // Kiểm tra kích thước feature
    if (feature.size() != w[0].size()) {
        cerr << "❌ Lỗi: Kích thước feature không khớp với số chiều của w!" << endl;
        w_file.close();
        return;
    }

    // Ghi thông tin chọn đặc trưng
    w_file << "Feature selection (0 : Unselected, 1 : Selected):" << endl << "[";
    for (int i = 0; i < d; ++i)
    {
        w_file << (feature[i] != 0 ? "1 " : "0 ");
    }
    w_file << "]\n";

    // Kiểm tra và ghi nhãn dự đoán
    if (y_pred.empty()) {
        w_file << "⚠️ Cảnh báo: Không có nhãn dự đoán nào được tạo!" << endl;
    }
    else {
        w_file << "Predicted labels: \n";
        for (int prediction : y_pred)
        {
            w_file << prediction << "\n";
        }
    }

    w_file.close();
}

/* ------------ Tính accuracy(độ chính xác) start ------------ */
double DCA::getAccracy(const vector<int>& y_test, const vector<int>& y_pred) {
    int count = 0;
    for (size_t i = 0; i < y_test.size(); i++)
        if (y_test[i] == y_pred[i]) count++;
    return static_cast<double>(count) / y_test.size();
}
/* ------------ Tính accuracy(độ chính xác) end ------------ */
