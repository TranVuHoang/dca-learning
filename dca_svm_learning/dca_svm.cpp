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
    // w, b, e input random
    dca.initRandom();

    return 0;
}