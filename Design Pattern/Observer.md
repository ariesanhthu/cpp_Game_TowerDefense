Thuộc nhóm behavioral

- Cho phép một đối tượng (subject) thông báo cho các đối tượng khác (observers) **khi có sự kiện xảy ra**
- Giúp giảm sự phụ thuộc giữa các phần của mã nguồn.
- **Ví dụ về hệ thống thành tích**:
    - Hệ thống thành tích trong game có thể sử dụng mẫu thiết kế Observer để theo dõi các sự kiện như "rơi khỏi cầu" mà không làm rối mã nguồn của các phần khác như engine vật lý (Physic engine, tính toán các thông số vật lý trong game, như đường cong của đạn, va chạm,...).
- **Cách hoạt động**:
    - Subject giữ danh sách các observers và thông báo cho họ khi có sự kiện.
    - Observer đăng ký với subject để nhận thông báo.
- **Ưu điểm**:
    - Giảm sự phụ thuộc giữa các phần của mã nguồn.
    - Dễ dàng thêm hoặc loại bỏ các observers mà không ảnh hưởng đến subject.
- **Nhược điểm**:
    - Có thể gây ra vấn đề về hiệu suất nếu có quá nhiều observers.
    - Cần quản lý việc đăng ký và hủy đăng ký của observers để tránh lỗi bộ nhớ.
- **Ứng dụng hiện đại**:
    - Ngày nay, các ngôn ngữ lập trình hiện đại thường sử dụng các phương pháp dựa trên hàm hoặc closure để triển khai mẫu thiết kế Observer, thay vì sử dụng các lớp và giao diện truyền thống.

