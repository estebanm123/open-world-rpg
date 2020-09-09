#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Widget.h"

namespace gui
{

class StackMenu : public sf::NonCopyable
{
    public:
        StackMenu(const sf::RenderWindow& window, float baseY);
        StackMenu(const sf::Vector2f& position);

        StackMenu(StackMenu&& other);
        StackMenu& operator =(StackMenu&& other);

        ~StackMenu() = default;

        void addWidget(std::unique_ptr<Widget> w);
        /*
        template<typename T, typename... Args>
        void addWidget(Args&&... args) {
            auto w = std::make_unique<T>(std::forward<Args>(args)...);
            initWidget(*w);
            widgets.push_back(std::move(w));
        }*/

        void setTitle(const std::string& title);

        void handleEvent   (sf::Event e, const sf::RenderWindow& window);
        void render        (sf::RenderTarget& renderer);

    private:
        const sf::RenderWindow& getWindow() const;

        void initWidget(Widget& w);

        const sf::RenderWindow* pWindow;

        std::vector<std::unique_ptr<Widget>> widgets;
        sf::RectangleShape background;

        sf::Vector2f basePosition;
        sf::Vector2f baseSize;

        Widget::Text titleText;
};

}