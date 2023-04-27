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
//         DLL
//     };

//     screenType ScreenType = menu;

//     menuScreen myMenuScreen;
//     SLLObject mySLLObject;
//     while (window.isOpen()) {
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             switch (ScreenType) {
//                 case menu:
//                     myMenuScreen.processAllEvent(window, event);
//                     break;
//                 case SLL:
//                     mySLLObject.processAllEvent(window, event);
//                     break;
//             }
//         }
//         window.clear();
//         int dsType = myMenuScreen.getDSType();
//         switch (dsType) {
//            case 1:
//                ScreenType = SLL;
//                break;
//            default:
//                ScreenType = menu;
//                break;
//         }
//         switch (ScreenType) {
//             case menu:
//                 myMenuScreen.drawMenuScreen(window);
//                 break;
//             case SLL:
//                 mySLLObject.drawLLScreen(window);
//                 break;
//         }
//         window.display();
//     }
//     mySLLObject.deleteSLL();

//     std::cout.rdbuf(coutbuf);
//     std::cerr.rdbuf(cerrbuf);

//     // Close the output file
//     out.close();
//     return 0;
// }

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
#include "LLscreenEvent.h"
#include "constants.h"
#include "general.h"
#include "LLscreen.h"
#include "button.h"
#include "node.h"
#include "menu.h"
#include "DLLScreen.h"

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
    DLL myDLL;
    std::vector <int> input = {2, 3, 4, 5};
    myDLL.build(input);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        myDLL.drawList(window, 255);
        window.display();
    }

    std::cout.rdbuf(coutbuf);
    std::cerr.rdbuf(cerrbuf);

    // Close the output file
    out.close();
    return 0;
}