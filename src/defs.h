/*
Universal definitions. You can think of it as somewhat of a configuration file.
Not sure if preprocessors are standard. We might want to convert these to
actual constant global variables.
*/

#define PI 3.14159265

#define SCREEN_WIDTH	720
#define SCREEN_HEIGHT	720

#define MAX_KEYBOARD_KEYS   350

#define WEDGE_X                 100     // Wedge spawnpoint x
#define WEDGE_Y                 100     // Wedge spawnpoint y
#define WEDGE_W                 38      // Image dimension
#define WEDGE_H                 50      // Image dimension
#define WEDGE_ANGLE             0

#define NEEDLE_X            620     // Needle spawnpoint x
#define NEEDLE_Y            620     // Needle spawnpoint y
#define NEEDLE_W            60      // Image dimension
#define NEEDLE_H            25      // Image dimension
#define NEEDLE_ANGLE        180

#define SUN_X   350
#define SUN_Y   350
#define SUN_W   10
#define SUN_H   10

#define BULLET_SPEED    2
#define RELOAD_SPEED    50     // Lower is faster shooting; Higher is slower shooting

#define THRUSTFORCE     0.001
#define TURNSPEED       1

#define SIDE_WEDGE      0    // set different teams for collision detection
#define SIDE_NEEDLE     1
#define SIDE_SUN        2
