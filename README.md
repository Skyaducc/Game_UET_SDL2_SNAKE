# SNAKE BATTLE
SNAKE BATTLE - Game được code bằng C++ và thư viện đồ họa SDL2

# Cách cài đặt
 ![image](https://github.com/Skyaducc/Game_UET_SDL2_SNAKE/assets/94954914/f5e0e27d-7bab-45b0-a2c9-6b6ada498457)

Chọn download zip , sau khi download về giải nén và mở file snakeBattle.exe để trải nghiệm trò chơi.

Nếu báo thiếu file dll có thể cài thêm trên trang web https://github.com/libsdl-org/SDL_image/releases

# Cách chơi

Khi vào màn hình Menu Game người chơi có các tùy chọn chế độ chơi như sau :

- Bấm vào nút MEDIUM để chỉnh độ khó của Game - tương ứng với tốc độ di chuyển của con rắn (có 3 chế độ EASY , MEDIUM , HARD)

![image](https://github.com/Skyaducc/Game_UET_SDL2_SNAKE/assets/94954914/fe788a49-ce19-40f7-98aa-ad9b3b8837b4)

- Bấm vào màn hình bản đồ Game để chọn các loại bản đồ.
- khi bấm vào có 4 loại bản đồ được hiện ra : FIELD , FOREST , ICE , VOLCANO người chơi sẽ chọn bản đồ mình muốn.

![image](https://github.com/Skyaducc/Game_UET_SDL2_SNAKE/assets/94954914/35c9ab55-9b8b-47ac-984c-b96f12c05561)

- Sau đó có thể chọn Play để chơi hoặc Exit để thoát khỏi Game.

- Luật chơi như sau : Người chơi sẽ điều khiển một con rắn (rắn màu xanh) và cố gắng ăn nhiều đồ ăn (bird) nhất có thể để chiến đấu với con rắn bot (rắn màu tím). Khi một con rắn ăn được đồ ăn nó sẽ dài thêm một đoạn và con rắn còn lại sẽ bị ngắn đi một đoạn.  Người chơi có 3 máu , khi chạm vào các chướng ngại vật sẽ bị trừ đi 1 máu và rắn có thể được điểu khiển ra ngoài viền sang viền đối diện. Người chơi sẽ thua khi hết máu hoặc rắn không còn độ dài nào , ngược lại người chơi thắng khi rắn bot cũng không còn độ dài nào hết.
- Ngoài ra người chơi có thể ăn đồ ăn đặc biệt sẽ được tăng thêm 2 độ dài hoặc thu nhập đủ 5 chữ cái của chữ "BONUS" sẽ được hồi đầy máu và thêm 3 độ dài.
![image](https://github.com/Skyaducc/Game_UET_SDL2_SNAKE/assets/94954914/583391cf-6187-457b-9bba-e434d6978816)

Người chơi có thể điều khiển con rắn bằng các phím `W` , `A` , `S` , `D` hoặc bằng các phím mũi tên tương ứng với 4 hướng di chuyển của rắn.

Bấm nút `space bar` nếu muốn dừng game hoặc chọn các chế độ chơi khác.

# Thuật toán của rắn bot

Rắn bot được di chuyển theo đường đi ngắn nhất từ vị trí đang đứng tới vị trí của đồ ăn bằng thuật toán `BFS`. Mỗi khi đồ ăn được sinh ra , rắn bot sẽ được tính toán trước đường đi và sẽ di chuyển theo đường đi đó thay vì di chuyển bằng hướng như rắn người chơi.

# Nguồn
các kĩ thuật lập trình được tham khảo tại https://lazyfoo.net/index.php và thầy Trần Quốc Long

# Chúc bạn có một trải nghiệm game tuyệt vời!!!
