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
    DCA dca;
    dca.q = 3; // số class của iris dataset
    dca.readFile();
    // w, b, e khởi tạo random
    dca.initRandom();
    int iter = 0;
    
    while (iter < 10000)
    {
        dca.GradientH();
        bool k = dca.solveCPlex();
        cout << k << endl;
        //float obj = DCA.getOBJ()

    }
   

    cout << "Solver: DCA-EXP starts to solve the model: " << "MSVM" << "\n";

    return 0;
}