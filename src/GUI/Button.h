#pragma once

#include <functional>

#include "Widget.h"

namespace gui
{
    enum class ButtonSize
    {
        Small,
        Wide,
    };

    class Button : public gui::Widget
    {
        public:
            Button(ButtonSize s = ButtonSize::Wide);

            void setFunction(std::function<void(void)> func);
            void setText    (const std::string& str);
            void setTexture (const sf::Texture& tex);

            void handleEvent    (sf::Event e, const sf::RenderWindow& window) override;
            void render         (sf::RenderTarget& renderer) override;
            void setPosition    (const sf::Vector2f& pos)   override;
            sf::Vector2f getSize() const    override;

        private:
            void updateText();

            sf::Vector2f    position;

            Rectangle   button;
            Text        text;
            std::function<void(void)> function = [](){};

    };

    inline std::unique_ptr<Button> makeButton() { return std::make_unique<Button>(); }
}