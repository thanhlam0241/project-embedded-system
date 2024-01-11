# Báo cáo hệ nhúng - Game PACMAN

- Lớp: Hệ nhúng - 143800
- Thành viên:
  - Nguyễn Thanh Lâm - 20200336
  - Lê Thành Nguyên - 20200447
- Thiết bị: Bộ KIT STM32F429I-DISC1

  - Bộ Kit STM32F429I-DISC1 là một sản phẩm của STMicroelectronics, thuộc dòng STM32 Discovery Kit. Được thiết kế để hỗ trợ nhà phát triển và kỹ sư trong việc phát triển và kiểm thử ứng dụng nhúng sử dụng vi điều khiển STM32F429ZI, nó cung cấp một môi trường phát triển linh hoạt và tiện ích.

  - Bộ Kit này tích hợp nhiều tính năng, bao gồm một màn hình cảm ứng màu TFT LCD với độ phân giải cao, cảm biến gia tốc, cảm biến ánh sáng, loa và microphone, tạo điều kiện thuận lợi cho việc phát triển ứng dụng đa dạng. Ngoài ra, nó cũng có các giao diện giao tiếp như USB, Ethernet, và nhiều cổng GPIO để kết nối với các thiết bị và mô-đun ngoại vi khác.

  - Bộ Kit STM32F429I-DISC1 cũng hỗ trợ sự phát triển và debug thông qua giao diện ST-LINK/V2, giúp nhà phát triển dễ dàng nạp chương trình và theo dõi quá trình thực thi chương trình.

  - Với vi xử lý ARM Cortex-M4, bộ nhớ lớn, và các tính năng tích hợp mạnh mẽ, bộ Kit STM32F429I-DISC1 là một công cụ hiệu quả cho việc phát triển ứng dụng nhúng đòi hỏi hiệu suất cao và tính linh hoạt trong các dự án điện tử.

## Giới thiệu

<!-- %<Khái quát về trò chơi>% -->

**Tổng quan về Trò chơi:**
Pac-Man là một trò chơi điện tử kinh điển được phát triển bởi Namco và xuất hiện lần đầu tiên vào năm 1980. Trò chơi này nhanh chóng trở thành một biểu tượng trong ngành công nghiệp game và đã giữ vững sức hấp dẫn suốt nhiều thập kỷ.

Người chơi trong Pac-Man kiểm soát một nhân vật tròn trắng mắt và miệng mở rộng, được gọi là Pac-Man, điều khiển qua một mê cung đầy ăn điểm và những quả trái cây. Nhiệm vụ chính của người chơi là ăn hết tất cả các điểm trong mê cung mà không bị bắt giữ bởi những hồn ma điều khiển bởi máy tính.

Trong project này, trò chơi có 10 độ khó. Mỗi độ khó tốc độ của người chơi và các hồn ma sẽ tăng tốc. Các hồn ma có tên là Blinky, Pinky, Inky và Clyde, mỗi con có chiến thuật điều động riêng để theo đuổi Pac-Man.

Người chơi có thể ăn những viên bi lớn để tạm thời làm cho hồn ma trở nên yếu đuối, và trong thời gian này, Pac-Man có thể đảo ngược vai trò bằng cách săn đuổi và ăn chúng.

Pac-Man không chỉ ghi điểm thông qua việc ăn điểm mà còn trở thành một biểu tượng văn hóa, xuất hiện trong nhiều tác phẩm nghệ thuật, sản phẩm tiêu dùng và thậm chí là đề tài trong các nghiên cứu về trò chơi điện tử. Đến ngày nay, Pac-Man vẫn được coi là một trong những trò chơi điện tử thành công và lâu bền nhất trong lịch sử.

## Phân công công việc

- ## Nguyễn Thanh Lâm:

  - Kết nối bộ Kit với Keyboard, Toach.
  - Xây dựng màn hình Menu và cấu hình cho map chơi (level, điểm, sự kiện, vật phẩm)

- ## Lê Thành Nguyên:
  - Xây dựng thuật các con Bot hồn ma (cách di chuyển, thuật toán đuổi bắt)
  - Xây dựng nhân vật Pacman (di chuyển, ăn hồn ma)

## Hướng dẫn chơi

- Khi bắt đầu màn hình của Kit, màn hình chính sẽ hiển thị thanh Menu để người chơi có thể lựa chọn cấu hình cho game như Level, Bot. Người chơi sẽ điều khiển thanh Menu bằng Keyboard được kết nối với Kit hoặc dùng phím cảm ứng(Toach) ở góc trên bên phải màn hình. Sau khi lựa chọn cấu hình, người chơi chọn đến nút Start và bấm phím Enter trên Keyboard (hoặc nút sang bên phải). Lúc này người chơi sẽ được chuyển đến màn hình Game Play.
- Sau khi chuyển đến màn hình Game Play, bản đồ game sẽ hiện ra. Ở dưới màn hình sẽ có dòng chữ thay đổi từ Start đến Go. Khi dòng chữ hiển thị Go, game sẽ bắt đầu. Các con bot sẽ từ từ ra khỏi phòng và tìm kiếm người chơi. Người chơi càng ăn được nhiều thì càng nhiều Bot ra. Có tổng cộng 4 con Bot.
- Sau khi người chơi ăn hết điểm trên map sẽ hiện ra thông báo "You Win" và sẽ chuyển sang Level tiếp theo để chơi sau vài giây.
- Khi người chơi bị bắt bởi Bot, sẽ tiêu tốn 1 mạng sống. Tổng cộng có 3 mạng. Khi hết cả 3 mạng thì sẽ hiện chữ "Game Over" và chuyển đến màn hình Menu

### Đối tượng trong game

![Alt text](image/map.jpg)

- Pacman (Người chơi): Là đối tượng chính trong game, người chơi điều khiển Pacman để ăn các vật phẩm trên Map và lẩn tránh các Hồn ma (Bot).

- Hồn ma (Bot):
  Các đổi tượng sẽ đuổi bắt người chơi.

- Item (Điểm vàng nhỏ): Các điểm vàng, khi ăn sẽ được cộng điểm.

### Cách chơi

1. **Điều khiển:**
   Kết nối Keyboard thông qua cổng USB.
2. **Mục tiêu:**
   Ăn hết toàn bộ vật phẩm trên bản đồ và số mạng không bị về 0.

3. **Cơ chế trò chơi:**

## Các Hàm và Chức Năng của Chúng:

## Thuật Toán Tổng Quát của Trò Chơi:

### 1. **Khởi động**

Khi bật kit, màn hình hiển thị thanh menu. Người chơi dùng bàn phím để chọn level để chơi. Level có giá trị từ 1 đến 10, các giá trị sẽ ảnh hưởng đến tốc độ di chuyển của người chơi và các con bot. Sau khi chọn xong, di chuyển đến nút Start và nhấn Enter.

### 2. **Chuẩn Bị Bản Đồ**:

Sau khi ấn nút Enter từ thanh menu, màn hình menu sẽ bị xóa và hiển thị màn hình chơi. Màn hình gồm có 1 mê cung, trong mê cung có các bức tường và các con bot. Người chơi sẽ dùng các phím mũi tên trên bàn phím để di chuyển nhân vật, mục tiêu là ăn hết các điểm vàng trên màn hình

### 3. **Vòng Lặp Trò Chơi**:

Trong mỗi vòng lặp, các con bot sẽ di chuyển theo chiến lược random (chọn ngẫu nhiên 1 hướng nếu có đường đi). Khi di chuyển, tọa độ x, y của các Bot sẽ được thay đổi tùy theo hướng đi.
Game sẽ nhận diện xem người chơi có bấm phím hay không. Nếu không thì nhân vật sẽ di chuyển theo hướng đi hiện tại đến khi đâm vào tường. Nếu có thay đổi về hướng đi và không bị cản trở bởi tường, nhân vật có thể đổi hướng và di chuyển theo hướng đó (thêm 1 vào tọa độ theo hướng).
Tại mỗi vòng lặp, các Bot và người chơi sẽ kiểm tra hướng đi, từ đó thay đổi trạng thái animation. Đồng thời, người chơi sẽ kiểm tra xem tọa độ x và y có trùng với tọa độ x và y của các con Bot không. Nếu có thì sẽ bị trừ đi 1 sinh mạng và reset trạng thái.
Sau đó game sẽ clear toàn màn hình và update lại các trạng thái của các nhân vật.

### 4. **Kết Thúc Trò Chơi**:

Game sẽ kết thúc khi sinh mệnh người chơi về 0. Màn hình hiển thị Game Over và trở lại Menu

# Video Demo (Demo sau)
