/*---------------------------------------------------
# Author	: TRAN VU HOANG
# Date start: 09-03-2025
# Language	: Cplusplus
# Version	: 1.00
# Subject	: MSVM Algorithm
# Name		: dca_svm.cpp
----------------------------------------------------*/
#include "dca.h"

int main() {
    DCA dca_piE;
    dca_piE.q = 3; // số class của iris dataset
    dca_piE.readFile();

    // w, b, e khởi tạo random
    dca_piE.initRandom();
    int iter = 0;
    int maxIter = 10000;

    double obj_original = 0.0;
    double obj_final = 0.0;
    double check = 0.0;

    dca_piE.getOBJ_EXP(obj_original); // tính giá trị hàm mục tiêu ban đầu
    cout << "Gia tri ham muc tieu ban dau: " << obj_original << endl;

    while (iter < maxIter)
    {
        // Step 1: tính đạo hàm H
        dca_piE.GradientH(); // ✅

        // Step 2: tính đạo hàm G, giải bài toán con bằng CPLEX
        dca_piE.solveCPlex();

        // Tính giá trị hàm mục tiêu sau khi cập nhật
        dca_piE.getOBJ2_EXP(obj_final);
        cout << "Gia tri ham muc tieu trong vong lap thu " << iter + 1 << ": " << obj_final << endl;
        
        // Ultil(điều kiện dừng)
        dca_piE.checkFrobeniusNorm(check);
        if (check < dca_piE.epsilon) {
            break;
        }

        // Step 3: Cập nhật w, b, xi cho vòng lặp tiếp theo
        dca_piE.updateMembership();
        iter++;
    }
    cout << endl << "Solving..................................Done." << endl;
    cout << "Initialization...........................Done" << endl;
    cout << "Solver: DCA-PiE starts to solve the model: " << "MSVM-l2-l0" << endl;
    cout << "Gia tri ham muc tieu ban dau: " << obj_original << endl;
    cout << "Gia tri ham muc tieu trong vong lap:" << obj_final << endl;
    cout << "Iter: " << iter + 1 << endl;
    cout << "Accuracy on test set:";

    return 0;
}