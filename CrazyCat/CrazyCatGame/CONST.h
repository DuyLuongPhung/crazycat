
/// Lưu các biến const, các hàm const

#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }


#define VELOCITY_X 0.15f
#define VELOCITY_Y 0.15f

#define WALK_RIGHT_IMG L"bomber_right.png"
#define WALK_LEFT_IMG L"bomber_left.png"
#define WALK_FRONT_IMG L"bomber_front.png"
#define WALK_BEHIND_IMG L"bomber_behind.png"

#define ANIMATE_RATE 16
#define ANIMATE_RATE_BOMB 8
#define ANIMATE_RATE_FIREBANG 3

#define BOMBER_START_X 70
#define BOMBER_START_Y 635
#define BOMBER_WIDTH 18
#define BOMBER_HEIGHT 18
#define BOMBER_HEIGHT_HEAD 9
#define BOMBER_HEIGHT_REAL 27

#define BRICK_ID 1
#define BOMB_ID 2
#define FIREBANG_ID 3




#define INFO_BAR_HEIGHT 60
#define BOMB_TIME_FIRE 3000
#define BOMB_IMG L"bomb.png"
#define BOMB_WIDTH 32
#define BOMB_HEIGHT 32
#define FIRE_BANG_LEFT L"fire_left.png"
#define FIRE_BANG_CENTER L"fire_center.png"
#define FIRE_BANG_RIGHT L"fire_right.png"
#define FIRE_BANG_TOP L"fire_top.png"
#define FIRE_BANG_BOTTOM L"fire_bottom.png"

#define START_BUTTON_ID 0
#define RESUME_BUTTON_ID 1
#define HELP_BUTTON_ID 2
#define EXIT_BUTTON_ID 3

#define START_BUTTON_X 64
#define RESUME_BUTTON_X 64
#define HELP_BUTTON_X 64
#define EXIT_BUTTON_X 64
#define START_BUTTON_Y 128
#define RESUME_BUTTON_Y 128
#define HELP_BUTTON_Y 215
#define EXIT_BUTTON_Y 302
#define BUTTON_WIDTH 160
#define BUTTON_HEIGHT 64
#define START_BUTTON_IMG L"button_start.png"
#define RESUME_BUTTON_IMG L"button_resume.png"
#define HELP_BUTTON_IMG L"button_help.png"
#define EXIT_BUTTON_IMG L"button_exit.png"

#define DEFAULT_LIVE 3
#define GAMEBAR_FONT_SIZE 8

#define MAP_01_TIME_MAP 600000
#define MAP_01_IMG_FILE L"map1.img"
#define MAP_01_TEXT_FILE L"map1.map"
#define MAP_01_INFO_FILE L"map1.info"

#define BAR_WIDTH 58
#define BAR_HEIGHT 21
#define BAR_TEXT_X 25
#define BAR_TEXT_Y 4
#define BAR_TEXT_WIDTH 26
#define BAR_TEXT_HEIGHT 6

#define HEART_BAR_ID 1
#define HEART_BAR_IMG_FILE L"heart_game_bar.png"
#define HEART_BAR_X	306
#define HEART_BAR_Y 2

#define KEY_BAR_ID 2
#define KEY_BAR_IMG_FILE L"key_game_bar.png"
#define KEY_BAR_X	228
#define KEY_BAR_Y 2

#define GOLD_BAR_ID 3
#define GOLD_BAR_IMG_FILE L"gold_game_bar.png"
#define GOLD_BAR_X	150
#define GOLD_BAR_Y 2


