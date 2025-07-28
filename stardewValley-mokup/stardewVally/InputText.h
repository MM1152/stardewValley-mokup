#pragma once
#include "GameObject.h"
class InputText : public GameObject
{
private:
    sf::RectangleShape inputBox;
    sf::Text text;

    std::string fontId;
    std::string texId;

    sf::Vector2f inputBoxInitSize ;

    bool inputAble;
    std::string input;
public:
    InputText(const std::string& fontId  , const std::string& texId= "" , const std::string& name = "");
    ~InputText() override = default;

    // GameObject을(를) 통해 상속됨
    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;

    void SetPosition(const sf::Vector2f& pos) override;
    void SetRotation(float rot) override;
    void SetScale(const sf::Vector2f& s) override;
    void SetOrigin(const sf::Vector2f& o) override;
    void SetOrigin(Origins preset) override;

    void SetTextColor(const sf::Color& color);
    void SetSize(const sf::Vector2f& size);
    void SetString(const std::string text);
    std::string GetString() { return text.getString(); };
};

