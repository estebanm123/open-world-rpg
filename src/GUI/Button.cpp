#include "Button.h"

#include <iostream>

namespace gui {

Button::Button(ButtonSize s)
{
    button.setOutlineThickness(1);
    button.setOutlineColor(sf::Color::Green);
    button.setFillColor(sf::Color::Black);
    switch (s) {
        case ButtonSize::Wide:
            button.setSize({256, 64});
            break;

        case ButtonSize::Small:
            button.setSize({128, 64});
            break;
    }
}

void Button::setFunction(std::function<void(void)>func)
{
    function = func;
}

void Button::setText (const std::string& str)
{
    text.setString(str);
    updateText();
}

void Button::setTexture (const sf::Texture& tex)
{
    button.setTexture(&tex);
}

void Button::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    switch(e.type) {
        case sf::Event::MouseButtonPressed:
            switch(e.mouseButton.button) {
                case sf::Mouse::Left:
                    if (button.getGlobalBounds().contains((float)pos.x, (float)pos.y)) {
                        function();
                    }

                default:
                    break;
            }

        default:
            break;
    }
}

void Button::render(sf::RenderTarget& renderer)
{
    renderer.draw(button);
    renderer.draw(text);
}

void Button::setPosition(const sf::Vector2f& pos)
{
    position = pos;

    button.setPosition(position);
    text.setPosition  (position);

    updateText();
}

void Button::updateText()
{
    text.setOrigin(text.getGlobalBounds().width  / 2,
                     text.getGlobalBounds().height / 2);

    text.move(button.getGlobalBounds().width  / 2.0f,
                button.getGlobalBounds().height / 2.5f);
}


sf::Vector2f Button::getSize() const
{
    return button.getSize();
}

}
