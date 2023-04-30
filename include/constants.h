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

class codeTextConstants {
public:
    static int textSize;
    static sf::Vector2f textPosition;
    static sf::Vector2f blockPosition;
    static sf::Vector2f highlightPosition;
    static int baseWidth, baseHeight;
    static int highlightWidth, highlightHeight;
    static void initializeConstants();
};

class logoConstants {
public:
    static int minMoveDistance;
    static int logoRadius;
    static int logoMoveSpeed;
    static int logoFloatSpeed;
    static int backgroundFadeSpeed, backgroundMinOpacity;
    static sf::Vector2f logoCenter;
    static void initializeConstants();
};

class menuButtonConstants {
public:
    static int maxMoveDistance;
    static int maxHoverDistance;
    static int moveSpeed;
    static int moveOutSpeed;
    static int hoverMoveSpeed;
    static int buttonFadeInSpeed;
    static int buttonFadeOutSpeed;
    static int hoverFloatBackSpeed;
    static sf::Vector2f buttonPos4Button[4];
    static sf::Vector2f buttonPos3Button[3];
    static sf::Vector2f backButtonPosition;
    static void initializeConstants();
};

class stackConstants {
public:
    static sf::Vector2f bottomStack;
    static int yDistance;
    static void initializeConstants();
};

void initializeConstants();

#endif