#include "Widget.h"

namespace gui {

//Text
    Widget::Text::Text() {
        setCharacterSize(25);
        setOutlineColor(sf::Color::Black);
        setFillColor(sf::Color::White);
        setFont(ResourceHolder::get().fonts.get("arial"));
    }

    bool Widget::Rectangle::isHovered(const sf::RenderWindow &window) const {
        auto pos = sf::Mouse::getPosition(window);
        return getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y));
    }

    bool Widget::Rectangle::isClicked(sf::Event e, const sf::RenderWindow &window) {
        if (isHovered(window)) {
            if (e.type == sf::Event::MouseButtonPressed) {
                return e.mouseButton.button == sf::Mouse::Left;
            }
        }
        return false;
    }

}
