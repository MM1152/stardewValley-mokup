#pragma once
#include "GameObject.h"

struct CellData;
class InteractionObject : public GameObject
{
private:
	sf::Sprite objectSp;
	sf::RectangleShape rect;
	std::string texId;
	CellData* cellData;
public:
	InteractionObject(const std::string& texId, CellData* cellData , const std::string& name = "");
	~InteractionObject() override = default;

	void SetRotation(float rot) override;
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& o) override;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	virtual void Interaction();

	sf::RectangleShape& GetRectangle() { return rect; };
};

