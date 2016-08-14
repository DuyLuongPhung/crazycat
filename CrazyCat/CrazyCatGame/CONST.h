
/// Lưu các biến const, các hàm const

#define SAFE_RELEASE(x) if( x ) { (x)->Release(); (x) = NULL; }
#define SAFE_DELETE(x) if( x ) { delete(x); (x) = NULL; }
#define SAFE_DELETE_ARRAY(x) if( x ) { delete [] (x); (x) = NULL; }

#define SPEED_X 0.1f
#define GRAVITY_X 0.00002f
#define MAX_VELOCITY_X_WALK 0.12f
#define MAX_VELOCITY_X_RUN 0.30f

#define GRAVITY_Y 0.0006f
#define GROUND_Y -10
#define MAX_VELOCITY_Y 0.6f

#define MAX_JUMP_HEIGHT 100

#define WALK_RIGHT_IMG L"walk_right.png"
#define RUN_RIGHT_IMG L"run_right.png"
#define SLIDE_RIGHT_IMG L"slide_right.png"
#define DEAD_RIGHT_IMG L"dead_right.png"
#define FALL_RIGHT_IMG L"fall_right.png"
#define HURT_RIGHT_IMG L"hurt_right.png"
#define IDLE_RIGHT_IMG L"idle_right.png"
#define JUMP_RIGHT_IMG L"jump_right.png"

#define ANIMATE_RATE 18

#define WALK_IDLE_WIDTH 60
#define WALK_IDLE_HEIGHT 90
#define RUN_JUMP_FALL_WIDTH 61
#define RUN_JUMP_FALL_HEIGHT 91
#define SLIDE_WIDTH 68
#define SLIDE_HEIGHT 72
#define DEAD_HURT_WIDTH 81
#define DEAD_HURT_HEIGHT 91
