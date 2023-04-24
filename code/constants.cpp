#include "constants.h"

int nodeConstants::nodeDistance;
int nodeConstants::firstNodePositionX;
int nodeConstants::initialInsertNodeY;
int nodeConstants::firstNodePositionY;
int nodeConstants::nodePositionSpeedAfterInsert;
int nodeConstants::insertMoveSpeed;
int nodeConstants::fadeSpeed;
int nodeConstants::nodeRadius;
int nodeConstants::textOpacity;
float nodeConstants::moveDuration;
sf::Time nodeConstants::flashDuration;
sf::Vector2f nodeConstants::firstNodePosition;
sf::Vector2f nodeConstants::searchTextInfoPosition;
sf::Color nodeConstants::flashColor;
sf::Color nodeConstants::baseColor;
sf::Color nodeConstants::searchFoundColor;

void nodeConstants::initializeConstants() {
    nodeDistance = 174;
    firstNodePositionX = 174;
    initialInsertNodeY = 180;
    firstNodePositionY = 180;
    nodePositionSpeedAfterInsert = 10;
    insertMoveSpeed = 6;
    fadeSpeed = 13;
    nodeRadius = 64;
    moveDuration = 1;
    textOpacity = 255;
    flashDuration = sf::seconds(1.0f);
    firstNodePosition.x = firstNodePositionX, firstNodePosition.y = firstNodePositionY;
    searchTextInfoPosition.x = 1400, searchTextInfoPosition.y = 400;
    flashColor = sf::Color(237, 8, 8, 255);
    baseColor = sf::Color::White;
    searchFoundColor = sf::Color(17, 215, 18, 255);
}

int arrowConstants::arrowLengthInit;
int arrowConstants::arrowHeightInit;
sf::Vector2i arrowConstants::arrowHeadSize;
sf::Vector2i arrowConstants::arrowShaftSize;

void arrowConstants::initializeConstants() {
    arrowLengthInit = 52;
    arrowHeightInit = 23;
    arrowHeadSize.x = 19, arrowHeadSize.y = 23;
    arrowShaftSize.x = 97, arrowShaftSize.y = 3;
}

float mathConstants::PI;

void mathConstants::initializeConstants() {
    PI = 3.14159;
}

int textConstants::typeHead;
int textConstants::typeCur;
int textConstants::typeTail;
int textConstants::typeHeadAndTail;
int textConstants::typeHeadAndCur;
int textConstants::typeTailAndCur;
int textConstants::typeTemp;
int textConstants::typeNext;
int textConstants::typeDel;
int textConstants::typeHeadAndTemp;
int textConstants::typeTailAndNext;
sf::Time textConstants::textCursorTickRate;

void textConstants::initializeConstants() {
    typeHead = 1, typeCur = 2, typeTail = 3, typeHeadAndTail = 4, typeHeadAndCur = 5, typeTailAndCur = 6;
    typeTemp = 7, typeNext = 8, typeDel = 9, typeHeadAndTemp = 10, typeTailAndNext = 11;
    textCursorTickRate = sf::milliseconds(530);
}

int buttonConstants::moveSpeed;
int buttonConstants::moveLength;
int buttonConstants::textBoxDistance;
int buttonConstants::textCursorDistance;

void buttonConstants::initializeConstants() {
    moveSpeed = 3;
    moveLength = 30;
    textBoxDistance = 385;
    textCursorDistance = 10;
}

sf::Vector2f codeTextConstants::textPosition;
sf::Vector2f codeTextConstants::blockPosition;
sf::Vector2f codeTextConstants::highlightPosition;
int codeTextConstants::textSize;
int codeTextConstants::baseHeight, codeTextConstants::baseWidth;
int codeTextConstants::highlightHeight, codeTextConstants::highlightWidth;

void codeTextConstants::initializeConstants() {
    textSize = 25;
    textPosition = sf::Vector2f(1200, 480);
    blockPosition = sf::Vector2f(1185, 465);
    highlightPosition = sf::Vector2f(1185, 482);
    baseWidth = 1000, baseHeight = 600;
    highlightWidth = 1000, highlightHeight = 29;
};

int logoConstants::minMoveDistance;
int logoConstants::logoRadius;
int logoConstants::logoMoveSpeed;
int logoConstants::logoFloatSpeed;
int logoConstants::backgroundFadeSpeed;
int logoConstants::backgroundMinOpacity;
sf::Vector2f logoConstants::logoCenter;

void logoConstants::initializeConstants() {
    minMoveDistance = 270;
    logoRadius = 370;
    logoMoveSpeed = 20;
    logoFloatSpeed = 6;
    backgroundFadeSpeed = 5, backgroundMinOpacity = 130;
    logoCenter = sf::Vector2f(1920/2, 1000/2);
}

int menuButtonConstants::maxMoveDistance;
int menuButtonConstants::maxHoverDistance;
int menuButtonConstants::hoverMoveSpeed;
int menuButtonConstants::moveSpeed;
int menuButtonConstants::moveOutSpeed;
int menuButtonConstants::buttonFadeInSpeed;
int menuButtonConstants::buttonFadeOutSpeed;
int menuButtonConstants::hoverFloatBackSpeed;
sf::Vector2f menuButtonConstants::buttonPos3Button[3];
sf::Vector2f menuButtonConstants::buttonPos4Button[4];

void menuButtonConstants::initializeConstants() {
    maxMoveDistance = 180;
    maxHoverDistance = 30;
    hoverMoveSpeed = 6;
    hoverFloatBackSpeed = 3;
    moveSpeed = 12;
    moveOutSpeed = 8;
    buttonFadeInSpeed = 17;
    buttonFadeOutSpeed = 8;
    sf::Vector2f positionButtonGroupOf3 = sf::Vector2f(600, 280);
    for (int i = 0; i < 3; i++) {
        buttonPos3Button[i] = positionButtonGroupOf3;
        buttonPos3Button[i].y += 155 * i;
    }
    buttonPos3Button[1].x += 20;
    sf::Vector2f positionButtonGroupOf4 = sf::Vector2f(600, 250); 
    for (int i = 0; i < 4; i++) {
        buttonPos4Button[i] = positionButtonGroupOf4;
        buttonPos4Button[i].y += 150 * i;
    }
    buttonPos4Button[1].x += 20;
    buttonPos4Button[2].x += 20;
}