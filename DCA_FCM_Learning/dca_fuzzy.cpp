/*---------------------------------------------------
# Author	: TRAN VU HOANG                        
# Date		: 05-03-2025                            
# Language	: Cplusplus		                        				
# Version	: 1.00		                            					
# Subject	: Fuzzy Clustering Algorithm            
# Name		: dca_fuzzy.cpp	                        					
----------------------------------------------------*/
#include "dca.h"

int main() {
    DCA data;

    data.readFile();
    // u,v input random
    data.InitRandom();

    int iter = 0;
    int maxIter = 1000;

    /* Repeat*/
    while (iter < maxIter)
    {
        data.GradientH(); //✅
        data.GradientG(); // 
        data.m;

        //if (data.Stop()) {
        //    break;
        //}

        // gán u_2 = u`
        // gán v_2 = v
        iter++;

        //obj = calculation.getObjFCM(self.data, u, v, self.m, self.n, self.k, self.param['t']);
        if (1 < data.epsilon) {
            break;
        }
    }

    cout << "Solving..................Done." << endl;
    cout << "Number of iterations: " << iter << endl;
    //cout << " Final Objective value: " << obj;
    /* Hàm mục tiêu của bài toán*/

    return 0;
}