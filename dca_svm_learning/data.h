/*---------------------------------------------------------
# Name file : data.h
# Subject   : Định nghĩa khung của lớp DATA
#             define (attributes-methods) in the Data class
----------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class DATA {
public:
	/*-----------------------------------------------------
	# INPUT:
	#	Matrix: X(n, d) 
	#	Vector: Y(n)
	#
	# PARAMETER:
	#	C: tham số tuỳ chỉnh(đặt là c)
	#	Q: số k - class của từng data đối với MSVM(đặt là k)
	#	
	------------------------------------------------------*/
	int n; // number of rows in data✅
	int d; // number of columns in data✅
	vector<vector<double>> x; // biến x để lưu mảng data 
	vector<double> y; // biến y: để lưu mảng class(cột class)

	int c; // tham số điều chỉnh✅
	int q; // số class của từng bộ dữ liệu✅
	
	/*-----------------------------------------------------
	# METHODS:
	#	Data(): Constructor Method ✅
	#	readFile(): hàm đọc file data input
	-------------------------------------------------------*/
	DATA();
	void readFile();
};

