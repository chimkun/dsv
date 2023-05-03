#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <string>
#include <windows.h>
#include <commdlg.h>
#include <shlobj.h>
#include <iostream>
#include <fstream>
#include <string>
#include <tchar.h>
#include "thread"
#include "constants.h"
#include "LLscreenEvent.h"
#include "DLLscreenEvent.h"
#include "stackScreenEvent.h"
#include "queueScreenEvent.h"
#include "LLscreen.h"
#include "menu.h"

int main()
{   
    
    std::ofstream out("output.txt");
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::streambuf* cerrbuf = std::cerr.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    std::cerr.rdbuf(out.rdbuf());

    // menu DS Type
    // none (0), SLL (1), DLL (2), CLL (3),
    // array (4), dArray (5),
    // stack (6), queue (7)
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
    window.setFramerateLimit(60);
    window.clear(sf::Color::Black);

    initializeConstants();
    std::cerr << "init\n";

    enum screenType {
        menu, SLL, DLL, CLL,
        array, sArray, dArray,
        Stack, Queue
    };

    screenType ScreenType = menu;
    menuScreen myMenuScreen;
    SLLObject mySLLObject;
    std::cerr << "SLL\n";
    DLLObject myDLLObject;
    std::cerr << "DSAJKFL\n";
    StackObject myStackObject;
    QueueObject myQueueObject;
    
    std::cout.flush();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (ScreenType) {
                case menu:
                    myMenuScreen.processAllEvent(window, event);
                    break;
                case SLL:
                    mySLLObject.processAllEvent(window, event);
                    if (mySLLObject.exitSLLScreen()) {
                        ScreenType = menu;
                        mySLLObject.setExitToFalse();
                        myMenuScreen.backToMenu();
                    }
                    break;
                case DLL:
                    myDLLObject.processAllEvent(window, event);
                    if (myDLLObject.exitDLLScreen()) {
                        ScreenType = menu;
                        myDLLObject.setExitToFalse();
                        myMenuScreen.backToMenu();
                    }
                    break;
                case Stack:
                    myStackObject.processAllEvent(window, event);
                    if (myStackObject.exitStackScreen()) {
                        ScreenType = menu;
                        myStackObject.setExitToFalse();
                        myMenuScreen.backToMenu();
                    }
                    break;
                case Queue:
                    myQueueObject.processAllEvent(window, event);
                    if (myQueueObject.exitQueueScreen()) {
                        ScreenType = menu;
                        myQueueObject.setExitToFalse();
                        myMenuScreen.backToMenu();
                    }
            }
        }
        window.clear();
        int dsType = myMenuScreen.getDSType();
        // std::cerr << "dsType: " << dsType << '\n';
        switch (dsType) {
            case 1:
                ScreenType = SLL;
                break;
            case 2:
                ScreenType = DLL;
                break;
            case 7:
                ScreenType = Stack;
                break;
            case 8:
                ScreenType = Queue;
                break;
            default:
                ScreenType = menu;
                break;
        }
        switch (ScreenType) {
            case menu:
                myMenuScreen.drawMenuScreen(window);
                break;
            case SLL:
                mySLLObject.drawLLScreen(window);
                break;
            case DLL:
                myDLLObject.drawLLScreen(window);
                break;
            case Stack:
                myStackObject.drawStackScreen(window);
                break;
            case Queue:
                myQueueObject.drawQueueScreen(window);
        }
        window.display();
    }
    mySLLObject.deleteSLL();

    std::cout.rdbuf(coutbuf);
    std::cerr.rdbuf(cerrbuf);

    // Close the output file
    out.close();
    return 0;
}

// #include <SFML/Graphics.hpp>
// #include <iostream>
// #include <algorithm>
// #include <string>
// #include <windows.h>
// #include <commdlg.h>
// #include <shlobj.h>
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <tchar.h>
// #include "LLscreenEvent.h"
// #include "constants.h"
// #include "general.h"
// #include "LLscreen.h"
// #include "button.h"
// #include "node.h"
// #include "menu.h"
// #include "DLLscreenEvent.h"
// #include "DLLScreen.h"
// #include "arrow.h"
// #include "stackScreenEvent.h"

// int main()
// {   
    
//     std::ofstream out("output.txt");
//     std::streambuf* coutbuf = std::cout.rdbuf();
//     std::streambuf* cerrbuf = std::cerr.rdbuf();
//     std::cout.rdbuf(out.rdbuf());
//     std::cerr.rdbuf(out.rdbuf());

//     // menu DS Type
//     // none (0), SLL (1), DLL (2), CLL (3),
//     // array (4), dArray (5),
//     // stack (6), queue (7)
//     srand(time(NULL));
//     sf::RenderWindow window(sf::VideoMode(1920, 1080), "DS Visualizer");
//     window.setFramerateLimit(60);
//     window.clear(sf::Color::Black);

//     initializeConstants();

//     enum screenType {
//         menu,
//         SLL,
//         DLL,
//         Stack
//     };

//     screenType ScreenType = Stack;
//     StackObject myStackObject;
//     std::cerr << "my pc is fucked\n";

//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             switch (ScreenType) {
//                 case Stack:
//                     myStackObject.processAllEvent(window, event);
//                     break;
//             }
//         }
//         window.clear();
//         switch (ScreenType) {
//             case Stack:
//                 myStackObject.drawStackScreen(window);
//                 break;
//         }
//         window.display();
//     }

//     std::cout.rdbuf(coutbuf);
//     std::cerr.rdbuf(cerrbuf);

//     // Close the output file
//     out.close();
//     return 0;
// }