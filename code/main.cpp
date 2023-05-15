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
#include "CLLScreenEvent.h"
#include "arrayScreenEvent.h"
#include "dArrayScreenEvent.h"
#include "stackScreenEvent.h"
#include "queueScreenEvent.h"
#include "aboutScreen.h"
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
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "dsv!");

    sf::Image icon;
    if (!icon.loadFromFile("src//include//texture//icon.png")) {
        std::cout << "icon not found!\n";
        exit(-1);
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    window.setFramerateLimit(60);
    window.clear(sf::Color::Black);

    initializeConstants();
    // std::cerr << "init\n";

    enum screenType {
        menu, SLL, DLL, CLL,
        sArray, dArray,
        Stack, Queue,
        about
    };

    screenType ScreenType = menu;
    menuScreen myMenuScreen;
    aboutScreen myAboutScreen;
    SLLObject mySLLObject;
    DLLObject myDLLObject;
    CLLObject myCLLObject;
    SArrayObject myStaticArrayObject;
    DArrayObject myDynamicArrayObject;
    StackObject myStackObject;
    QueueObject myQueueObject;
    
    std::cout.flush();
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
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
                case CLL:
                    myCLLObject.processAllEvent(window, event);
                    if (myCLLObject.exitCLLScreen()) {
                        ScreenType = menu;
                        myCLLObject.setExitToFalse();
                        myMenuScreen.backToMenu();
                    }
                    break;
                case sArray:
                    myStaticArrayObject.processAllEvent(window, event);
                    if (myStaticArrayObject.exitSArrayScreen()) {
                        ScreenType = menu;
                        myStaticArrayObject.setExitToFalse();
                        myMenuScreen.backToMenu();
                    }
                    break;
                case dArray:
                    myDynamicArrayObject.processAllEvent(window, event);
                    if (myDynamicArrayObject.exitDArrayScreen()) {
                        ScreenType = menu;
                        myDynamicArrayObject.setExitToFalse();
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
                    break;
                case about:
                    if (myAboutScreen.backButtonIsClick(window)) {
                        ScreenType = menu;
                        myMenuScreen.backToMenu();
                    }
                    break;
            }
        }
        window.clear();
        int dsType = myMenuScreen.getDSType();
        switch (dsType) {
            case 1:
                ScreenType = SLL;
                break;
            case 2:
                ScreenType = DLL;
                break;
            case 3:
                ScreenType = CLL;
                break;
            case 4:
                ScreenType = sArray;
                break;
            case 5:
                ScreenType = dArray;
                break;
            case 6:
                ScreenType = Stack;
                break;
            case 7:
                ScreenType = Queue;
                break;
            case 8:
                ScreenType = about;
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
            case CLL:
                myCLLObject.drawCLLScreen(window);
                break;
            case sArray:
                myStaticArrayObject.drawSArrayScreen(window);
                break;
            case dArray:
                myDynamicArrayObject.drawDArrayScreen(window);
                break;
            case Stack:
                myStackObject.drawStackScreen(window);
                break;
            case Queue:
                myQueueObject.drawQueueScreen(window);
                break;
            case about:
                myAboutScreen.drawAboutScreen(window);
                break;
        }
        window.display();
    }
    mySLLObject.deleteSLL();
    myDLLObject.deleteDLL();
    myCLLObject.deleteCLL();

    std::cout.rdbuf(coutbuf);
    std::cerr.rdbuf(cerrbuf);

    // Close the output file
    out.close();
    return 0;
}