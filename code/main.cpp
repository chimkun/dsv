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

    enum screenType {
        menu,
        SLL
    };

    screenType ScreenType = SLL;

    menuScreen myMenuScreen;
    SLLObject mySLLObject;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (ScreenType) {
                case menu:
                    myMenuScreen.processAllEvent(window, event);
                    break;
                case SLL:
                    mySLLObject.processAllEvent(window, event);
                    break;
            }
        }
        window.clear();
        int dsType = myMenuScreen.getDSType();
        //switch (dsType) {
        //    case 1:
        //        ScreenType = SLL;
        //        break;
        //    default:
        //        ScreenType = menu;
        //        break;
        //}
        switch (ScreenType) {
            case menu:
                myMenuScreen.drawMenuScreen(window);
                break;
            case SLL:
                mySLLObject.drawLLScreen(window);
                break;
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


// #include <windows.h>
// #include <commdlg.h>
// #include <shlobj.h>
// #include <iostream>
// #include <fstream>
// #include <string>
// #include <tchar.h>

// // HWND hwnd;
// TCHAR szFileName[MAX_PATH];

// int main() {
//     OPENFILENAME ofn;
//     ZeroMemory(&ofn, sizeof(ofn));
//     ofn.lStructSize = sizeof(ofn);
//     // ofn.hwndOwner = hwnd;
//     ofn.lpstrFilter = _T("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
//     ofn.lpstrFile = szFileName;
//     ofn.nMaxFile = MAX_PATH;
//     ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
//     ofn.lpstrDefExt = _T("txt");

//     if (GetOpenFileName(&ofn) == TRUE) {
//         // User selected a file
//         std::ifstream file(ofn.lpstrFile);
//         std::string line;
//         while (std::getline(file, line)) {
//             std::cout << line << '\n';
//         } 
//     }
//     else {
//         // User cancelled the dialog
//     }

//     return 0;
// }
