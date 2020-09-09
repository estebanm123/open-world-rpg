#include "Textbox.h"

#include <iostream>

namespace gui {

TextBox::TextBox(std::string& modString)
:   pModString (&modString)
{
    label.setCharacterSize(15);
    rect.setFillColor({52, 152, 219});
    rect.setSize({256, 64});
}

void TextBox::setLabel(const std::string& str)
{
    label.setString(str);
}

void TextBox::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    handleClick     (e, window);
    handleTextInput (e);
}

void TextBox::render(sf::RenderTarget& renderer)
{
    if (!isActive) {
        rect.setFillColor({52, 152, 219});
    }
    else {
        rect.setFillColor({82, 132, 239});
    }
    renderer.draw(rect);
    renderer.draw(label);
    renderer.draw(text);
}

void TextBox::setPosition(const sf::Vector2f& pos)
{
    position = pos;

    rect.setPosition(position);
    label.setPosition(position.x,
                        position.y + label.getGlobalBounds().height -
                                       rect.getGlobalBounds().height / 2);
    text.setPosition  (position);
    text.move(5, rect.getGlobalBounds().height / 2.5f);
}

sf::Vector2f TextBox::getSize() const
{
    return  {rect.getSize().x,
             rect.getSize().y + label.getGlobalBounds().height};
}

void TextBox::handleClick (sf::Event e, const sf::RenderWindow& window)
{
    auto pos = sf::Mouse::getPosition(window);

    if (rect.getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y)))
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                isActive = true;
            }
        }
    }
    else
    {
        if (e.type == sf::Event::MouseButtonPressed)
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                isActive = false;
            }
        }
    }
}

void TextBox::handleTextInput (sf::Event e)
{
    switch (e.type) {
    case sf::Event::TextEntered:
        if (isActive) {
            //Get the key that was entered
            unsigned char keyCode = e.text.unicode;

            if (isValidCharacter(keyCode)) {
                if (text.getGlobalBounds().width + 30 <= rect.getGlobalBounds().width) {
                    pModString->push_back(keyCode);
                }

            }
            else if (isBackspace(keyCode)) {
                //prevents popping back an empty string
                if (pModString->length() > 0)
                    pModString->pop_back();
            }
            text.setString(*pModString);
        }
        break;

    default:
        break;
    }
}

bool TextBox::isValidCharacter(unsigned char keyCode)
{
    return  keyCode >= 48 && keyCode <= 57  ||  //Numbers
            keyCode >= 65 && keyCode <= 90  ||  //Uppercase
            keyCode >= 97 && keyCode <= 122 ||  //Lowercase
            keyCode == 32;    //Space
}

bool TextBox::isBackspace(unsigned char keycode)
{
    return keycode == 8;
}


}
