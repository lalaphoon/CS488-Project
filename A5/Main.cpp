#include "A5.hpp"

#include <iostream>
using namespace std;

int main( int argc, char **argv )
{
    if (argc > 1) {
        std::string luaSceneFile(argv[1]);
        std::string title("Assignment 5 - [");
        title += luaSceneFile;
        title += "]";
        
        CS488Window::launch(argc, argv, new A3(luaSceneFile), 1024, 768, title);
        
    } else {
        //cout << "Must supply Lua file as first argument to program.\n";
        //cout << "For example:\n";
        //cout << "./A3 Assets/simpleScene.lua\n";
        //argv = (char**)"Assets/simpleScene.lua";
        std::string title = "Assignment 5 - A Small Town";
        std::string luaSceneFile("ss.lua");
        CS488Window::launch(argc, argv, new A3(luaSceneFile), 1024, 768, title);
        
    }
    
    return 0;
}
