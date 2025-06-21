# Thread

## BT1. Tạo và Chạy Threads Cơ Bản

### Yêu cầu

* Viết một chương trình sử dụng thư viện `pthread.h` để thực hiện các thao tác sau:
* Tạo hai threads. Mỗi thread sẽ in ra một chuỗi thông báo kèm theo ID của thread (ví dụ: "Thread 1: Hello from thread").
* Sử dụng hàm `pthread_join` để đợi cả hai threads hoàn thành trước khi chương trình kết thúc.

### Gợi ý

* Sử dụng `pthread_create` để tạo threads và `pthread_join` để chờ các threads hoàn thành.
* Khi nào thread kết thúc? Thread kết thúc khi hàm của nó return hoặc gọi `pthread_exit()`.

---

## BT2. Đồng Bộ Hóa Threads với Mutex

### Yêu cầu

* Viết một chương trình sử dụng pthread và mutex để thực hiện các thao tác sau:
* Tạo một biến toàn cục `counter` khởi tạo bằng 0.
* Tạo ba threads, mỗi thread tăng giá trị của `counter` lên 1, 1.000.000 lần.
* Sử dụng mutex để đảm bảo rằng việc tăng counter được thực hiện an toàn.
* In ra giá trị cuối cùng của counter khi tất cả các threads hoàn thành.

### Gợi ý

* Sử dụng `pthread_mutex_lock` và `pthread_mutex_unlock` để khóa và mở khóa mutex khi truy cập vào counter.
* Nếu bỏ mutex, chương trình có thể gặp race condition dẫn tới kết quả sai.

---

## BT3. Sử Dụng Condition Variables

### Yêu cầu

* Viết một chương trình có hai threads: `producer` và `consumer`.
* `Producer`: Tạo ra một số ngẫu nhiên từ 1 đến 10 và lưu vào một biến toàn cục `data`.
* `Consumer`: Đợi producer cung cấp dữ liệu, sau đó đọc và in ra dữ liệu đó.
* Sử dụng `pthread_cond_wait` và `pthread_cond_signal` để đồng bộ hóa giữa producer và consumer.
* Lặp lại quá trình trên 10 lần và in ra tất cả các giá trị do consumer đọc được.

### Gợi ý

* Sử dụng `pthread_cond_wait` để cho consumer đợi đến khi có tín hiệu từ producer rằng dữ liệu đã sẵn sàng.

---

## BT4. Đếm Số Chẵn và Số Lẻ với Threads

### Yêu cầu

* Viết một chương trình thực hiện các bước sau:
* Tạo một mảng ngẫu nhiên chứa 100 số nguyên từ 1 đến 100.
* Tạo hai threads: một thread đếm số chẵn và một thread đếm số lẻ trong mảng.
* Khi hai threads hoàn tất việc đếm, in ra tổng số số chẵn và tổng số số lẻ.
* Sử dụng `pthread_join` để đảm bảo rằng chương trình chỉ kết thúc khi cả hai threads hoàn thành nhiệm vụ.

### Gợi ý

* Mỗi thread xử lý một phần công việc riêng biệt, không cần mutex.

---

## BT5. Chia Sẻ Tài Nguyên Với Read-Write Lock

### Yêu cầu

* Viết một chương trình mô phỏng tình huống có nhiều thread đọc và ghi dữ liệu:
* Tạo một biến `data` chứa một số nguyên.
* Tạo 5 threads đọc và 2 threads ghi:

  * Các thread đọc chỉ đọc `data` mà không thay đổi.
  * Các thread ghi sẽ tăng giá trị của `data` lên 1.
* Sử dụng read-write lock để đảm bảo nhiều threads có thể đọc cùng lúc, nhưng chỉ một thread được ghi tại bất kỳ thời điểm nào.
* In ra giá trị của `data` sau khi tất cả các threads hoàn thành.

### Gợi ý

* Sử dụng `pthread_rwlock_rdlock` và `pthread_rwlock_wrlock` cho đồng bộ đọc-ghi.

---

## BT6. Tính Tổng Mảng với Threads và Mutex

### Yêu cầu

* Viết một chương trình tính tổng một mảng lớn gồm 1 triệu số nguyên.
* Chia mảng thành 4 phần bằng nhau.
* Tạo 4 threads, mỗi thread tính tổng một phần của mảng.
* Sử dụng một biến tổng toàn cục và mutex để tổng hợp kết quả từ tất cả các threads.
* In ra kết quả tổng của mảng sau khi các threads hoàn thành.

### Gợi ý

* Sử dụng `pthread_mutex_lock` để bảo vệ biến tổng khi các threads cộng kết quả của chúng.

---
