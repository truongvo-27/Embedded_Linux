# IPC Signal

## BT1. Bắt Tín hiệu SIGINT

### Yêu cầu

* Viết một chương trình bắt tín hiệu SIGINT (được gửi khi nhấn Ctrl+C) và in ra thông báo khi nhận được tín hiệu này.
* Sử dụng hàm `signal()` để đăng ký một hàm xử lý cho tín hiệu SIGINT.
* Trong hàm xử lý, in ra thông báo "SIGINT received" mỗi khi nhận được tín hiệu.
* Chương trình sẽ tiếp tục chạy cho đến khi nhận được SIGINT lần thứ 3, sau đó kết thúc.

### Gợi ý

* Sử dụng một biến đếm toàn cục để đếm số lần tín hiệu SIGINT được nhận và kiểm tra biến này trong hàm xử lý.

### Câu hỏi

* Nếu bỏ qua tín hiệu SIGINT, chuyện gì sẽ xảy ra khi nhấn Ctrl+C?

---

## BT2. Sử dụng Tín hiệu SIGALRM để Tạo Timer

### Yêu cầu

* Viết chương trình tạo một bộ đếm thời gian bằng cách sử dụng tín hiệu SIGALRM.
* Sử dụng hàm `alarm()` để đặt thời gian kích hoạt SIGALRM mỗi giây.
* Khi nhận tín hiệu SIGALRM, chương trình sẽ tăng biến đếm và in ra dòng "Timer: \<giây> seconds".
* Dừng chương trình sau khi đếm đến 10 giây.

### Gợi ý

* Sử dụng hàm `signal()` để đăng ký xử lý tín hiệu SIGALRM, và đặt `alarm(1)` để bộ đếm lặp lại hàng giây.

### Câu hỏi

* Điều gì xảy ra nếu không gọi lại `alarm(1)` trong hàm xử lý?

---

## BT3. Tạo Giao tiếp giữa Các Process bằng Tín hiệu

### Yêu cầu

* Viết chương trình tạo hai process (cha và con) và sử dụng tín hiệu SIGUSR1 để giao tiếp giữa chúng.

### Cách thực hiện

* Dùng `fork()` để tạo process con từ process cha.
* Process cha sẽ gửi tín hiệu SIGUSR1 cho process con mỗi 2 giây.
* Khi nhận tín hiệu SIGUSR1, process con sẽ in ra thông báo "Received signal from parent".
* Dừng chương trình sau khi đã gửi tín hiệu 5 lần.

### Gợi ý

* Dùng `kill()` để gửi tín hiệu từ process cha đến process con, và sử dụng `signal()` trong process con để bắt tín hiệu SIGUSR1.

### Câu hỏi

* Tại sao chúng ta cần sử dụng `kill()` để gửi tín hiệu trong bài này?

---

## BT4. Viết chương trình bỏ qua tín hiệu SIGTSTP (Ctrl+Z)

### Yêu cầu

* Sử dụng `signal()` hoặc `sigaction()` để bắt và bỏ qua tín hiệu SIGTSTP.
* Khi nhận tín hiệu SIGTSTP, chương trình sẽ không dừng mà tiếp tục chạy và in thông báo "SIGTSTP ignored".

### Gợi ý

* Đảm bảo chương trình sẽ tiếp tục chạy thay vì bị dừng khi nhấn Ctrl+Z.

### Câu hỏi

* Điều gì xảy ra nếu không xử lý tín hiệu SIGTSTP và người dùng nhấn Ctrl+Z?

---

## BT5. Chương trình chờ tín hiệu kết hợp chờ người dùng nhập liệu

### Mục tiêu

* Viết một chương trình có thể nhận tín hiệu đồng thời cho phép người dùng nhập liệu từ bàn phím.

### Hướng dẫn

* Dùng `select()` hoặc `poll()` để cho phép chương trình xử lý tín hiệu mà không làm gián đoạn khi nhận dữ liệu nhập từ bàn phím.
* Khi nhận tín hiệu SIGINT, in ra thông báo “SIGINT received.”
* Nếu nhận tín hiệu SIGTERM, thoát chương trình.

### Gợi ý

* Kết hợp giữa việc bắt tín hiệu và đọc nhập liệu để chương trình linh hoạt hơn.
