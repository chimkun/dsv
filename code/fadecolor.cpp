#include "fadecolor.h"

sf::Color getFadeColor(sf::Color startColor, sf::Color endColor, sf::Clock flashTimer) {
    sf::Time elapsedTime = flashTimer.getElapsedTime();
    float completionPercentage = elapsedTime.asSeconds() / nodeConstants::flashDuration.asSeconds();
    completionPercentage = std::min(completionPercentage, 1.0f);
    sf::Color curColor = sf::Color(startColor.r + (endColor.r - startColor.r) * completionPercentage,
                                   startColor.g + (endColor.g - startColor.g) * completionPercentage,
                                   startColor.b + (endColor.b - startColor.b) * completionPercentage);
    return curColor;
}