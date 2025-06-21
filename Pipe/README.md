# IPC Pipe

## BT1: Sử dụng Pipe để giao tiếp giữa Parent và Children Process

### Yêu cầu

* Viết một chương trình sử dụng pipe để giao tiếp giữa hai tiến trình.
* Tạo một pipe và fork một tiến trình con.
* Tiến trình cha sẽ gửi một chuỗi văn bản vào pipe.
* Tiến trình con sẽ đọc chuỗi văn bản từ pipe và in ra màn hình.

### Gợi ý

* Sử dụng hàm `pipe()` để tạo pipe, `fork()` để tạo tiến trình con, và `read()`/`write()` để giao tiếp giữa các tiến trình.

---

## BT2: Sử dụng nhiều Pipe để giao tiếp giữa nhiều tiến trình

### Yêu cầu

* Mở rộng bài tập trước để sử dụng nhiều pipe cho ba tiến trình.
* Tạo hai pipe:

  * Một cho giao tiếp từ tiến trình cha đến tiến trình con 1.
  * Một từ tiến trình con 1 đến tiến trình con 2.
* Tiến trình cha gửi một thông điệp đến tiến trình con 1.
* Tiến trình con 1 sẽ nhận thông điệp, thay đổi nó (ví dụ: thêm một chuỗi vào cuối), và gửi đến tiến trình con 2.
* Tiến trình con 2 sẽ nhận thông điệp và in ra màn hình.

### Gợi ý

* Sử dụng nhiều pipe và đảm bảo rằng các tiến trình không bị chặn khi đọc và ghi dữ liệu.

---

## BT3: Đếm số ký tự qua Pipe

### Yêu cầu

* Viết một chương trình sử dụng pipe để đếm số ký tự trong một chuỗi.
* Tạo một pipe và fork một tiến trình con.
* Tiến trình cha sẽ gửi một chuỗi ký tự vào pipe.
* Tiến trình con sẽ đọc chuỗi ký tự từ pipe và đếm số ký tự, sau đó in ra kết quả.

### Gợi ý

* Sử dụng hàm `strlen()` để đếm số ký tự trong chuỗi đã đọc từ pipe.

---

