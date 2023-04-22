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