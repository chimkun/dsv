#include "nodeTextureHolder.h"

nodeTexture::nodeTexture() {
    if (!baseTexture.loadFromFile("src//include//texture//circle-outline.png")) {
        std::cout << "Texture file not found! (circle)\n";
        exit(-1);
    }
    if (!outlineTexture.loadFromFile("src//include//texture//circle-outline.png")) {
        std::cout << "Texture file not found! (circle outline)\n";
        exit(-1);
    }
    
    // std::cerr << "texture size INIT: " << circleTexture.getSize().x << " " << circleTexture.getSize().y << '\n';
    std::string digitFile = "default-";
    for (int i = 0; i < 10; i++) {
        std::string curFile = "src//include//texture//" + digitFile + std::to_string(i) + ".png";
        std::cerr << "file:" << curFile << '\n';
        if (!digitTexture[i].loadFromFile(curFile)) {
            std::cout << "Texture file not found! (digit)\n";
            exit(-1);
        }
    }
}

sf::Texture nodeTexture::getBaseTexture() {
    std::cerr << "return texture " << baseTexture.getSize().x << " " << baseTexture.getSize().y << '\n';
    return baseTexture;
}
sf::Texture nodeTexture::getOutlineTexture() {
    std::cerr << "outline texture " << outlineTexture.getSize().x << " " << outlineTexture.getSize().y << '\n';
    return outlineTexture;
}
sf::Texture nodeTexture::getDigitTexture(int digit) {
    std::cerr << "digit, siz: " << digit << " " << digitTexture[digit].getSize().x << " " << digitTexture[digit].getSize().y << '\n';
    return digitTexture[digit];
}