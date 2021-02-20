#include "window.h"

extern void initSDL(const std::string &title, int width, int height);
extern void clearSDL();
extern void cleanup();

extern void doInput();

extern void initSpace();

extern void prepareScene();
extern void presentScene();

App app;