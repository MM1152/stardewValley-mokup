#pragma once
#include "GameObject.h"

class Player;

class Gatherable : public GameObject
{
private:
	std::string GtId;
	std::string GtName;
	std::string GtTextureId;
	sf::FloatRect uiTextCoord = { -1,-1,-1,-1 };
	sf::FloatRect textureCoord = { -1,-1,-1,-1 };

	bool interaction = false;


protected:
	sf::Sprite GtSp;
	Player* player;
	sf::RectangleShape bound;


public:

	Gatherable(const std::string& name = "");
	Gatherable() = default;
	~Gatherable() override = default;


	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetGtInfo(Gatherable* gatherable);
	void SetPlayer(Player* player) { this->player = player; };

	virtual void DropItems() {};



	std::string* GetGtIdInfo() { return &GtId; };
	std::string* GetGtNameInfo() { return &GtName; };
	std::string* GetGtTextureIdInfo() { return &GtTextureId; };
	sf::FloatRect* GetGtUiTextCoordInfo() { return &uiTextCoord; };
	sf::FloatRect* GetGtTextureCoordInfo() { return &textureCoord; };
	bool* GetGtInteractionInfo() { return &interaction; };

	virtual sf::FloatRect GetLocalBounds() const
	{
		return GtSp.getLocalBounds();
	}

	virtual sf::FloatRect GetGlobalBounds() const
	{
		return bound.getGlobalBounds();
	}
};

