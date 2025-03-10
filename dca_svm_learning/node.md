### Biến (Variables):

✅w: Tập hợp các vector trọng số trong không gian Rd. Trong các mô hình MSVM, w thường được biểu diễn dưới dạng ma trận W chứa Q vector wi.

✅b: Vector bias trong không gian RQ. Trong các mô hình MSVM, b thường được biểu diễn dưới dạng vector B chứa Q giá trị bias bk.

✅ξ: Tập hợp các vector biến slack (slack variables) trong không gian RQ. Mỗi vector ξ chứa các thành phần ξik.

wi: Vector trọng số thứ i của một siêu phẳng, thuộc tập W.
•
wk: Một trong Q vector trọng số.
•
bk: Thành phần thứ k của vector bias B.
•
ξik: Biến slack cho mẫu thứ i và lớp thứ k (k khác lớp thực yi).
•
wij: Giá trị trọng số của siêu phẳng thứ i liên kết với đặc trưng thứ j.
•
uij: Biến nhị phân, uij = 1 nếu wij ≠ 0 và uij = 0 nếu wij = 0.
•
tij: Biến được giới thiệu trong các bài toán tối ưu hóa sau khi xấp xỉ chuẩn l0.


### Tham số (Parameters - những yếu tố được thiết lập hoặc điều chỉnh): 

✅C: Tham số điều chỉnh (regularization parameter) kiểm soát sự đánh đổi giữa mục tiêu tối đa hóa biên và mục tiêu giảm thiểu lỗi phân loại.

✅Q: Số lượng vector trong tập W (có thể liên quan đến số lượng lớp trong bài toán MSVM).

✅d: Số chiều của không gian đầu vào (số lượng đặc trưng).

✅n: Số lượng vector trong tập đầu vào X (số lượng mẫu huấn luyện).

✅✅p: Tham số trong chuẩn lp của thành phần phạt C‖ξ‖pp. Trong bài báo này, xét trường hợp p=1.

✅✅q: Tham số trong chuẩn lq của thành phần chính ‖w‖rq. Trong trường hợp q=2, r=2; trong các trường hợp khác, r=1.

K1, K2, K3: Các hằng số xác định các mô hình MSVM cụ thể (Weston & Watkins, Cramer & Singer, Lee & Lin).
•
β: Tham số điều chỉnh cho thành phần chuẩn l2 trong bài toán tối ưu hóa l2l0-norm.
•
α: Tham số trong hàm xấp xỉ η(x) cho chuẩn l0 và trong hàm phạt SCAD fλ(t) cũng như trong hàm xấp xỉ mới t(x).
•
ε: Một giá trị nhỏ dương được sử dụng làm điều kiện dừng cho các thuật toán lặp DCA.
•
λ: Tham số trong hàm phạt SCAD fλ(t).
•
ρ: Ngưỡng (threshold) để loại bỏ các đặc trưng dựa trên điểm số ranking cj.
•
t: Tham số trong kỹ thuật phạt chính xác (exact penalty technique).
•
aij: Giới hạn dưới cho wij liên quan đến uij trong kỹ thuật phạt chính xác. Thường được đặt bằng ε > 0 hoặc -b.
•
bij: Giới hạn trên cho wij liên quan đến uij trong kỹ thuật phạt chính xác. Thường được đặt bằng maxij(wij) hoặc một giá trị đủ lớn.

### Các ký hiệu khác:
X: Tập hợp các vector đầu vào xi.

Y: Vector chứa các nhãn lớp yi.

‖w‖0: Chuẩn l0 của vector w, đếm số lượng thành phần khác không của w.
•
‖w‖rq: Chuẩn lq của vector w với số mũ r.
•
‖ξ‖pp: Chuẩn lp của vector ξ với số mũ p.
•
〈.,.〉: Tích vô hướng.
•
e: Cơ số của logarit tự nhiên.
•
w*: Vector bước, w*i = 1 nếu wi ≠ 0, và 0 ngược lại.
•
η(x): Hàm xấp xỉ cho bước (step).
•
fλ(t): Hàm phạt SCAD.
•
t(x): Hàm xấp xỉ mới cho chuẩn l0.
•
∇H(X): Subgradient của hàm H(X).