#include <memory>
#include "Window.h"

using namespace std;

int main()
{
    std::unique_ptr<Window>  win = make_unique<Window>();
    if(!win->init(800,600,"Hello World Example")){
        return -1;
    }
    win->mainLoop();
    win->cleanUp();
    return 0;
}
