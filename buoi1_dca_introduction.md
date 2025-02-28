# Giới thiệu DCA - Lý thuyết

### 1. DCA là gì?

    DCA là thuật toán để giải các bài toán tối ưu không lồi (tính min hàm f(x) không lồi -> phân rã thành hiệu của 2 hàm lồi):
    Min F(x) = G(x) - H(x) Different of Convex function Algorithm

    Min f(X) trong đó:
    Với x thuộc D
    X: là một vector (x1, x2, x3, x4,..., xn, y1, y2,.., ym, z1, z2, z3,..zk)
    X có thể là nhiều biến x, y, z -> gọi chung là X
    => Kích thước: n + m + k

    => giải bài này dùng phương pháp DCA để giải

    `Bước 1: khởi tạo 1 điểm x0`

    - X(x1, x2, x3, x4, x5) x0(0.1, 0.2, 0.3, 0.4, 0.5)

    `Bước 2: repeat`

    '''
    1. tính đạo hàm của H <=> xk = GradientH(x0)

    '''


    '''
    2. Tính đạo hàm của G tại điểm xk
        <=> xk+1 = GradientG(xk)
    '''
