
/* Các hàm giải phóng bộ nhớ cho các biến con trỏ */
#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }

/*Danh sách ID và Sprite cho các đối tượng*/
#define WIDTH_OBJECT 32									// chiều rộng cho các đối tượng
#define HEIGHT_OBJECT 32								// chiều cao cho các đối tượng

#define ID_BRICK 1										// brick - Tường
#define ID_TILEBOX_NORMAL 2								// tile box normal - hộp bình thường, khi nổ sẽ mất đi
#define IMG_TILEBOX_NORMAL L"tilebox.png"
#define ID_TILEBOX_COIN 3								// tile box coin - hộp gỗ khi nổ sẽ để lại 1 hộp quà - tiền
#define ID_TILEBOX_HEART 4								// tile box heart - hộp gỗ khi nổ sẽ để lại 1 hộp quà - 1 mạng
#define ID_TILEBOX_TIME 5								// tile box time - hộp gỗ khi nổ sẽ để lại 1 hộp quà - thêm thời gian
#define ID_TILEBOX_VELOCITY 6							// tile box velocity - hộp gỗ khi nổ để lại 1 hộp quà - tăng tốc độ
#define ID_TILEBOX_SUPERBOMB 7							// tile box super bomb - hộp gỗ khi nổ để lại 1 hộp quà - super bomb
#define ID_GIFTBOX_COIN 8								// gift box coin - hộp quà - tiền
#define IMG_GIFTBOX_COIN L"giftbox_coin.png"
#define ID_GIFTBOX_HEART 9								// gift box heart - hộp quà - mạng chơi
#define IMG_GIFTBOX_HEART L"giftbox_heart.png"
#define ID_GIFTBOX_TIME 10								// gift box time - hộp quà - thêm thời gian
#define IMG_GIFTBOX_TIME L"giftbox_time.png"
#define ID_GIFTBOX_VELOCITY 11							// gift box velocity - hộp quà - tăng tốc độ di chuyển
#define IMG_GIFTBOX_VELOCITY L"giftbox_velocity.png"
#define ID_GIFTBOX_KEY 12								// gift box key - hộp quà - chìa khóa để mở cửa qua màn
#define IMG_GIFTBOX_KEY L"giftbox_key.png"
#define ID_GIFTBOX_SUPERBOMB 13								// gift box super boom - hộp quà - super bomb
#define IMG_GIFTBOX_SUPERBOMB L"giftbox_superbomb.png"
#define ID_DOOR 14										// door - cửa sang màn chỉ mở khi đủ chìa khóa
#define IMG_DOOR L"giftbox_door.png"
#define ID_GHOST 15

#define ID_BOMB_NORMAL 16								// normal bomb - bom bình thường
#define IMG_BOMB_NORMAL L"normal_bomb.png"
#define ID_BOMB_SUPER 17								// super bomb - bom có sức nổ lớn
#define IMG_BOMB_SUPER L"super_bomb.png"
#define ID_FIREBANG_LEFT 18								// fire bang left - đường nổ của bom bên trái
#define IMG_FIREBANG_LEFT L"firebang_left.png"
#define ID_FIREBANG_RIGHT 19							// fire bang right - đường nổ của bom bên phải
#define IMG_FIREBANG_RIGHT L"firebang_right.png"
#define ID_FIREBANG_TOP 20								// fire bang top - đường nổ của bom bên trên
#define IMG_FIREBANG_TOP L"firebang_top.png"
#define ID_FIREBANG_BOT 21								// fire bang bottom - đường nổ của bom bên dưới
#define IMG_FIREBANG_BOT L"firebang_bot.png"
#define ID_FIREBANG_MIDLR 22							// fire bang mid left-right - đường nổ của bom giữa ngang
#define IMG_FIREBANG_MIDLR L"firebang_midlr.png"
#define ID_FIREBANG_MIDTB 23							// fire bang mid top-down - đường nổ của bom giữa dọc
#define IMG_FIREBANG_MIDTB L"firebang_midtb.png"
#define ID_FIREBANG_CENTER 26							// fire bang center - đường nổ của bom ở trung tâm
#define IMG_FIREBANG_CENTER L"firebang_center.png"
#define BOMB_ANIMATE_RATE 8
#define FIREBANG_ANIMATE_RATE 8

#define WIDTH_SUPER_FIREBANG_LR 64
#define HEIGHT_SUPER_FIREBANG_LR 32
#define WIDTH_SUPER_FIREBANG_TB 32
#define HEIGHT_SUPER_FIREBANG_TB 64

#define FIREBANG_EXIST_TIME 800
#define NORMAL_BOMB_EXIST_TIME 2000
#define SUPER_BOMB_EXIST_TIME 1500

/* Các thông số cho nhân vật - bomber man */
#define BOMBER_VELOCITY_X 0.15f
#define BOMBER_VELOCITY_Y 0.15f
#define BOMBER_BOOT_VELOCITY 2.0f
#define BOMBER_RIGHT_IMG L"bomber_right.png"
#define BOMBER_LEFT_IMG L"bomber_left.png"
#define BOMBER_FRONT_IMG L"bomber_front.png"
#define BOMBER_BEHIND_IMG L"bomber_behind.png"
#define BOMBER_DEAD_IMG L"bomber_dead.png"
#define BOMBER_ANIMATE_RATE 16
#define BOMBER_START_X  70
#define BOMBER_START_Y  1020
#define BOMBER_WIDTH 18
#define BOMBER_HEIGHT 18
#define BOMBER_HEIGHT_HEAD 9
#define BOMBER_HEIGHT_REAL 27
#define BOMBER_BOOT_VELOCITY 1.1f;
#define BOMBER_BOOT_VELOCITY_TIME 0.003f
#define BOMBER_DEAD_TIME 2000
#define BOMBER_ADD_BOMB_TIME 2000

/* Các thông số cho menu */
#define ID_MENU_RESOURCE 30
#define MENU_BG_IMG L"game_menu_bg.png"
#define WIDTH_MENU 320
#define HEIGHT_MENU 416
#define MENU_START_X 140
#define MENU_START_Y 10
#define MENU_START_BUTTON_ID 31
#define MENU_RESUME_BUTTON_ID 32
#define MENU_HELP_BUTTON_ID 33
#define MENU_EXIT_BUTTON_ID 34

#define MENU_START_BUTTON_X 64
#define MENU_RESUME_BUTTON_X 64
#define MENU_HELP_BUTTON_X 64
#define MENU_EXIT_BUTTON_X 64

#define MENU_START_BUTTON_Y 128
#define MENU_RESUME_BUTTON_Y 128
#define MENU_HELP_BUTTON_Y 215
#define MENU_EXIT_BUTTON_Y 302

#define BUTTON_WIDTH 160
#define BUTTON_HEIGHT 64

#define MENU_START_BUTTON_IMG L"button_start.png"
#define MENU_RESUME_BUTTON_IMG L"button_resume.png"
#define MENU_HELP_BUTTON_IMG L"button_help.png"
#define MENU_EXIT_BUTTON_IMG L"button_exit.png"

/* Các thông số cho game bar - thông tin game */
#define DEFAULT_LIVE 3
#define GAMEBAR_FONT_SIZE 8
#define GAMEBAR_WIDTH 58
#define GAMEBAR_HEIGHT 21
#define GAMEBAR_TEXT_X 25
#define GAMEBAR_TEXT_Y 4
#define GAMEBAR_TEXT_WIDTH 26
#define GAMEBAR_TEXT_HEIGHT 6

#define GAMEBAR_HEART_BAR_ID 1
#define GAMEBAR_HEART_BAR_IMG_FILE L"heart_game_bar.png"
#define GAMEBAR_HEART_BAR_X	522
#define GAMEBAR_HEART_BAR_Y 2

#define GAMEBAR_KEY_BAR_ID 2
#define GAMEBAR_KEY_BAR_IMG_FILE L"key_game_bar.png"
#define GAMEBAR_KEY_BAR_X	444
#define GAMEBAR_KEY_BAR_Y 2

#define GAMEBAR_GOLD_BAR_ID 3
#define GAMEBAR_GOLD_BAR_IMG_FILE L"gold_game_bar.png"
#define GAMEBAR_GOLD_BAR_X	366
#define GAMEBAR_GOLD_BAR_Y 2

#define GAMEBAR_TIME_BAR_ID 4
#define GAMEBAR_TIME_BAR_IMG_FILE L"time_game_bar.png"
#define GAMEBAR_TIME_BAR_X	40
#define GAMEBAR_TIME_BAR_Y 2

#define GAMEBAR_SUPERBOMB_BAR_ID 5
#define GAMEBAR_SUPERBOMB_BAR_IMG_FILE L"superbomb_game_bar.png"
#define GAMEBAR_SUPERBOMB_BAR_X	130
#define GAMEBAR_SUPERBOMB_BAR_Y 2

/* Các thông số cho map */
#define MAP_01_TIME_MAP 60000000
#define MAP_01_IMG_FILE L"map1.img"
#define MAP_01_TEXT_FILE L"map1.map"
#define MAP_01_INFO_FILE L"map1.info"
#define MAP_01_NEED_KEYS 5

#define MAP_02_TIME_MAP 1200000000
#define MAP_02_IMG_FILE L"map2.img"
#define MAP_02_TEXT_FILE L"map2.map"
#define MAP_02_INFO_FILE L"map2.info"
#define MAP_02_NEED_KEYS 6

#define MAP_TIME_WAITING 5000
#define MAP_GAME_OVER_IMG L"game_over.png"
#define MAP_START_MAP_IMG L"start_map.png"
