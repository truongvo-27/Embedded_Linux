# Linux File System

## BT1. Mở File và Sử dụng O\_APPEND

### Mô tả

Viết một chương trình mở một file bất kỳ và sử dụng cờ `O_APPEND`. Sau đó thực hiện `lseek()` về đầu file rồi ghi một vài dữ liệu vào file đó.

### Câu hỏi

* Dữ liệu sẽ xuất hiện ở vị trí nào của file và tại sao lại như vậy?

---

## BT2. Chương Trình Xử Lý Command-Line Arguments

### Mô tả

Viết một chương trình có số lượng command-line arguments là 3, có dạng như sau:

```bash
$ ./example_program filename num-bytes [r/w] "Hello"
```

Trong đó:

1. `example_program`: Tên file thực thi
2. `filename`: Tên file
3. `num-bytes`: Số byte muốn read/write
4. `[r/w]`:

   * `r` -> Thực hiện đọc từ `filename` và in ra màn hình
   * `w` -> Thực hiện ghi vào `filename`
5. `"Hello"`: Nội dung bất kỳ muốn read/write vào `filename`

---

## BT3. Thông Tin File với struct stat

### Mô tả

* Tạo file bất kỳ và ghi một đoạn dữ liệu vào file đó.
* Thực hiện ghi ra màn hình các thông tin sau:

  * Loại file
  * Tên file
  * Thời gian chỉnh sửa file lần cuối
  * Kích thước file

### Yêu cầu

* Sử dụng `struct stat` để lấy thông tin file.

---


