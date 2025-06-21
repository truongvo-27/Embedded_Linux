# IPC Socket

## Viết lại 4 loại socket sau đây để gửi nhận một chuỗi dữ liệu đơn giản:

### 1. IPv4 Stream Socket

* Sử dụng giao thức TCP qua IPv4.
* Server lắng nghe và chấp nhận kết nối từ client.

### 2. IPv4 Datagram Socket

* Sử dụng giao thức UDP qua IPv4.
* Client gửi dữ liệu trực tiếp đến địa chỉ IP và port của server.
* Server nhận dữ liệu và in ra mà không cần thiết lập kết nối như TCP.

### 3. Unix Stream Socket

* Sử dụng giao thức TCP nhưng trong nội bộ hệ điều hành (Unix Domain Socket).
* Client kết nối vào file socket đó và gửi chuỗi dữ liệu.

### 4. Unix Datagram Socket

* Sử dụng giao thức UDP nhưng trong nội bộ hệ điều hành (Unix Domain Socket).
* Client gửi dữ liệu trực tiếp đến file socket của server.

---
