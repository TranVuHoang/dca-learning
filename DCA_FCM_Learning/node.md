### Quy tắc đặt tên file trong C++

- 1. Định dạng đặt tên file

     ✅ Tên file nên mô tả nội dung của file
     Tên file nên phản ánh chính xác nội dung bên trong nó, tránh đặt tên chung chung như file1.cpp, test.cpp.
     Ví dụ:
     math\*utils.cpp → Chứa các hàm toán học.
     file_manager.h → Quản lý file I/O.
     main.cpp → File chứa hàm main() của chương trình.

     ✅ Sử dụng chữ thường hoặc Pascal Case
     Cách phổ biến nhất: Dùng chữ thường và dấu gạch dưới (\*), gọi là `snake_case`.
     Một số dự án cũng dùng PascalCase, đặc biệt nếu file đại diện cho một class.

     📌 Không nên đặt tên quá chung chung hoặc khó hiểu

     - ❌ sort.cpp, algorithm.cpp (quá chung chung)
     - ✅ heap_sort.cpp, bellman_ford.cpp (rõ ràng)

- 2.  Đặt tên function trong C++

      Trong C++, quy tắc đặt tên hàm được sử dụng nhiều nhất là Camel Case `(camelCase)`. Đây là quy tắc phổ biến trong cộng đồng lập trình C++ vì tính dễ đọc, ngắn gọn và phù hợp với phong cách lập trình hướng đối tượng.

      Tại sao Camel Case phổ biến nhất?

      ✔ Dễ đọc: Các từ trong tên hàm được phân tách rõ ràng mà không cần dấu gạch dưới.
      ✔ Ngắn gọn: So với snake*case, Camel Case ngắn hơn do không có ký tự *.
      ✔ Thống nhất: Được sử dụng rộng rãi trong các thư viện tiêu chuẩn và framework C++.

### Đẩy file lên github vs Visual Studio

- Cần bỏ qua folder .vs, đây là do quyền truy cập bị từ chối khi Git cố gắng thêm tệp Browse.VC.opendb trong thư mục .vs/. Đây là file tạm của Visual Studio, không nên được đưa vào Git.
  ✅ Cách khắc phục

1.  Bỏ qua file trong .gitignore

    - Mở file .gitignore trong thư mục dự án của bạn (hoặc tạo mới nếu chưa có).
    - Nếu file .gitignore chưa tồn tại trong thư mục của bạn, hãy tạo nó:
      ```
          touch .gitignore
      ```
    - Thêm nội dung vào .gitignore để bỏ qua file không cần thiết:
      ```
      .vs/
      _.opendb
      _.exe
      _.obj
      _.dll
      \*.log
      ```
