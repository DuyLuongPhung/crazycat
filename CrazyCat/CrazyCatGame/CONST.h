
/// Lưu các biến const, các hàm const

#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }


#define VELOCITY_X 0.11f
#define VELOCITY_Y 0.11f

#define WALK_RIGHT_IMG L"bomber_right.png"
#define WALK_LEFT_IMG L"bomber_left.png"
#define WALK_FRONT_IMG L"bomber_front.png"
#define WALK_BEHIND_IMG L"bomber_behind.png"

#define ANIMATE_RATE 18

#define BOMBER_WIDTH 18
#define BOMBER_HEIGHT 18
#define BOMBER_HEIGHT_HEAD 9
#define BOMBER_HEIGHT_REAL 27


#define BRICK_ID 1

# define INFO_BAR_HEIGHT 60
