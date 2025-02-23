# Assignment 2

**Description**

1. **`fd1 = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);`**
   * Mở file "file" ở chế độ đọc-ghi (O_RDWR).
   * Nếu file chưa tồn tại thì tạo mới (O_CREAT).
   * Nếu file đã tồn tại thì xóa toàn bộ nội dung trước khi ghi (O_TRUNC).
   * Quyền truy cập: Chủ sở hữu có quyền đọc và ghi (S_IRUSR | S_IWUSR).
   * **Nội dung sau khi thực hiện dòng này:** File "file" sẽ được tạo mới (nếu chưa có) hoặc bị xóa sạch nội dung.

2. **`fd3 = open(file, O_RDWR);`**
   * Mở lại file "file" ở chế độ đọc-ghi.
   * Vì file đã được tạo ở bước trước nên ở đây chỉ mở file để truy cập.
   * **Lưu ý:** Việc mở file nhiều lần như vậy thường không cần thiết và có thể gây ra các vấn đề về quản lý tài nguyên.

3. **`write(fd1, "Hello,", 6);`**
   * Ghi chuỗi "Hello," vào file được mở bởi descriptor `fd1`.
   * **Nội dung file:** "Hello,"

4. **`write(fd2, "world", 6);`**
   * **Lỗi:** Ở đây có một lỗi nhỏ. Biến `fd2` chưa được khai báo hoặc khởi tạo giá trị. Nếu dòng này được thực thi, chương trình sẽ gặp lỗi segmentation fault do truy cập vào một vùng nhớ không hợp lệ.

5. **`lseek(fd2, 0, SEEK_SET);`**
   * Dòng này sẽ gây ra lỗi vì `fd2` chưa được khởi tạo. 
   * Nếu `fd2` được khởi tạo đúng cách, lệnh này sẽ di chuyển con trỏ đọc/ghi của file đến vị trí đầu tiên.

6. **`write(fd1, "HELLO,", 6);`**
   * Ghi chuỗi "HELLO," vào file được mở bởi descriptor `fd1`.
   * **Nội dung file:** Hello,HELLO, vì lúc này con trỏ file đang ở cuối file

7. **`write(fd3, "Gidday", 6);`**
   * Ghi chuỗi "Gidday" vào file được mở bởi descriptor fd3.
   * **Nội dung file:** GiddayHELLO, lúc này con trỏ file ở đầu nên sẽ ghi đè 6B do sử dụng new descriptor để thao tác với file
