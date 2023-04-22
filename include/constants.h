#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SFML/Graphics.hpp>

class nodeConstants {
public:
    static int nodeDistance;
    static int firstNodePositionX;
    static int initialInsertNodeY;
    static int firstNodePositionY;
    static int nodePositionSpeedAfterInsert;
    static int insertMoveSpeed;
    static int fadeSpeed;
    static int nodeRadius;
    static int textOpacity;
    static sf::Vector2f firstNodePosition;
    static sf::Vector2f searchTextInfoPosition;
    static sf::Color flashColor;
    static sf::Color baseColor;
    static sf::Color searchFoundColor;
    static float moveDuration;
    static sf::Time flashDuration;
    static void initializeConstants();
};

class arrowConstants {
public:
    static int arrowLengthInit;
    static int arrowHeightInit;
    static sf::Vector2i arrowHeadSize;
    static sf::Vector2i arrowShaftSize;
    static void initializeConstants();
};

class mathConstants {
public:
    static float PI;
    static void initializeConstants();
};

class textConstants {
public:
    static int typeHead;
    static int typeCur;
    static int typeTail;
    static int typeHeadAndTail;
    static int typeHeadAndCur;
    static int typeTailAndCur;
    static int typeTemp;
    static int typeNext;
    static int typeDel;
    static int typeHeadAndTemp;
    static int typeTailAndNext;
    static sf::Time textCursorTickRate;
    static void initializeConstants();
};

class buttonConstants {
public:
    static int moveSpeed;
    static int moveLength;
    static int textBoxDistance;
    static int textCursorDistance;
    static void initializeConstants();
};

#endif