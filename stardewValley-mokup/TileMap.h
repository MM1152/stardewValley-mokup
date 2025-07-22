#pragma once
#include "GameObject.h"
class TileMap : public GameObject
{

protected:
	sf::VertexArray va;
	std::string spriteSheetid = "graphics/background_sheet.png";
	sf::Texture* texture = nullptr;
	sf::Transform transform;

	sf::Vector2i cellCount; // x에는 가로 갯수 , y에는 세로 갯수
	sf::Vector2f cellSize;

public:
	TileMap(const std::string& name = "");
	~TileMap() override = default;

	void Set(const sf::Vector2i& cellCount , const sf::Vector2f& cellSize);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;
	
	void UpdateTransform();
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

