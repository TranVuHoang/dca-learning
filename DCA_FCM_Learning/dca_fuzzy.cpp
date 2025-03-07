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
        /*Tính đạo hàm của H*/
        data.GradientH(); //✅

        /*Tính đạo hàm của G*/
        data.GradientG(); // 

        if (data.Stop()) {
            break;
        }

        // gán u_2 = u
        // gán v_2 = v
        //cout << data.Objective();
        iter++;
    }
    /* Hàm mục tiêu của bài toán*/

    return 0;
}