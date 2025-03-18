/*---------------------------------------------------
# Author		: TRAN VU HOANG                        
# Start date	: 05-03-2025                            
# Start update	: 18-03-2025                            
# Language		: Cplusplus		                        				
# Version		: 1.00		                            					
# Subject		: Fuzzy Clustering Algorithm            
# Name			: dca_fuzzy.cpp	                        					
----------------------------------------------------*/
#include "dca.h"

int main() {
	DCA dca;

	dca.readFile();
	// u,v input random
	dca.InitRandom();

	int iter = 0;
	int maxIter = 1000;
	
	double J2m_original = 0.0;
	double J2m_final = 0.0;
	double check = 0.0;

	dca.computeJ2mOriginal(J2m_original); 	// Tính giá trị hàm mục tiêu ban đầu
	
	/* Repeat*/
	while (iter < maxIter or iter == maxIter)
	{
		dca.GradientH(); //✅
		dca.GradientG(); //✅
		dca.m;

		// Tính giá trị hàm mục tiêu sau khi cập nhật
		dca.computeJ2m(J2m_final);
		cout << "Updated Objective Value (J2m_new) " << iter << ": " << J2m_final << endl;

		// Until
		dca.checkFrobeniusNorm(check);

		// Điều kiện dừng
		if (check < dca.epsilon) {
			break;
		}
		// 3. Cập nhật u và v cho vòng lặp tiếp theo
		dca.updateMembership();
		iter++;
	}

	cout << "Solving..................Done." << endl;
	cout << "Gia tri ham muc tieu ban dau: " << J2m_original << endl;
	cout << "Gia tri ham muc tieu trong vong lap: " << J2m_final << endl;
	cout << "Number of iterations: " << iter << endl;

	return 0;
}