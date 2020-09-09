#include "StackMenu.h"

#include "../ResourceManagers/ResourceHolder.h"

constexpr float BASE_Y = 95.0f;

namespace gui
{

StackMenu::StackMenu(const sf::RenderWindow& window, float baseY)
:   basePosition  ((float)window.getSize().x / 2.0f, baseY)
,   baseSize      (300, 20)
{
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::Green);
    background.setFillColor({100, 100, 100, 230});
    background.setSize(baseSize);
    background.setPosition(basePosition.x - baseSize.x / 2, baseY - 30);

    titleText.setPosition(0, baseY - 35);
    titleText.setOutlineColor(sf::Color::Black);
    titleText.setOutlineThickness(1);
    titleText.setCharacterSize(30);
}

StackMenu::StackMenu(const sf::Vector2f& position)
:   basePosition  (position)
,   baseSize      (300, 20)
{
    background.setFillColor({100, 100, 100, 128});
    background.setSize(baseSize);
    background.setPosition(position);
}

StackMenu::StackMenu(StackMenu&& other)
:   widgets       (std::move(other.widgets))
,   background    (std::move(other.background))
,   basePosition  (other.basePosition)
,   baseSize      (other.baseSize)
{
}

StackMenu& StackMenu::operator=(StackMenu&& other)
{
    widgets       =   std::move(other.widgets);
    background    =   std::move(other.background);
    basePosition  =   other.basePosition;
    baseSize      =   other.baseSize;

    return *this;
}

void StackMenu::addWidget(std::unique_ptr<Widget> w)
{
    initWidget(*w);
    widgets.push_back(std::move(w));
}

void StackMenu::initWidget(Widget& widget)
{
    widget.setPosition({basePosition.x - widget.getSize().x / 2,
                       basePosition.y});


    basePosition.y    += widget.getSize().y + 25;
    baseSize.y        += widget.getSize().y + 25;
    background.setSize(baseSize);
}

void StackMenu::setTitle(const std::string & title)
{
    titleText.setString(title);
    titleText.setPosition(getWindow().getSize().x - titleText.getGlobalBounds().width / 2,
        titleText.getPosition().y);
}

void StackMenu::handleEvent(sf::Event e, const sf::RenderWindow& window)
{
    for (auto& widget : widgets) {
        widget->handleEvent(e, window);
    }
}

void StackMenu::render(sf::RenderTarget& renderer)
{
    renderer.draw(background);
    renderer.draw(titleText);
    for (auto& widget : widgets) {
        widget->render(renderer);
    }
}

const sf::RenderWindow& StackMenu::getWindow() const
{
    return *pWindow;
}

}
