# POSIX Message Queue

## Mục Tiêu

Thực hành sử dụng **POSIX message queue** để giao tiếp giữa các tiến trình trong hệ điều hành Linux.

---

## Bài Tập 1: Gửi và Nhận Tin Nhắn Đơn Giản

### 📌 Yêu cầu:
- Viết một chương trình sử dụng POSIX message queue để gửi và nhận một tin nhắn đơn giản.

### 🔧 Hướng dẫn thực hiện:
1. Tạo message queue bằng hàm `mq_open()`.
2. Tiến trình **cha** gửi một chuỗi ký tự vào queue.
3. Tiến trình **con** nhận tin nhắn từ queue và in nội dung ra màn hình.

### 💡 Gợi ý:
- Định nghĩa tin nhắn bằng `mq_msg`.
- Sử dụng `mq_send()` để gửi và `mq_receive()` để nhận tin nhắn.
- Đừng quên gọi `mq_close()` và `mq_unlink()` để đóng và xóa message queue sau khi sử dụng.

---

## Bài Tập 2: Đếm Số Ký Tự Qua POSIX Message Queue

### 📌 Yêu cầu:
- Mở rộng bài 1 để tiến trình con đếm số ký tự trong chuỗi nhận được.

### 🔧 Hướng dẫn thực hiện:
1. Tiến trình **cha** gửi một chuỗi ký tự vào queue 1.
2. Tiến trình **con** nhận chuỗi từ queue 1, đếm số ký tự bằng `strlen()`, và gửi kết quả qua queue 2.
3. Tiến trình **cha** nhận kết quả từ queue 2 và in ra số ký tự đã đếm.

### 💡 Gợi ý:
- Cần tạo **hai message queue**:
  - Một để gửi chuỗi ký tự.
  - Một để gửi kết quả đếm.
- Sử dụng `strlen()` để đếm số ký tự.
- Sử dụng các hàm `mq_send()` và `mq_receive()` như ở Bài 1.

---

## Bài Tập 3: Giao Tiếp Giữa Nhiều Tiến Trình

### 📌 Yêu cầu:
- Viết chương trình sử dụng POSIX message queue để giao tiếp giữa **ba tiến trình**.

### 🔧 Hướng dẫn thực hiện:
1. Tạo một message queue chung để các tiến trình giao tiếp.
2. Tiến trình **cha** gửi một chuỗi ký tự vào queue.
3. Tiến trình **con 1** nhận chuỗi, **chuyển thành chữ in hoa**, và gửi lại vào queue.
4. Tiến trình **con 2** nhận chuỗi đã chuyển đổi và in ra màn hình.

### 💡 Gợi ý:
- Sử dụng `mq_send()` và `mq_receive()` để trao đổi dữ liệu.
- Đảm bảo các tiến trình không bị block khi đọc/ghi (có thể dùng `O_NONBLOCK` nếu cần).
- Dọn dẹp queue bằng `mq_close()` và `mq_unlink()` sau khi kết thúc.

---
