#pragma once
#include "GameObject.h"
enum class VertexType {
	Palette,
	Draw,
	Grid,
};

class TileMap : public GameObject
{
private:
	bool InArea(sf::Vector2f mousePos);
protected:
	VertexType type;

	sf::VertexArray va;


	std::string spriteSheetId;
	sf::Texture* texture = nullptr;
	sf::Transform transform;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;

	int index = -1;
public:
	std::function<void(sf::Vector2f*)> getIndexFunc;
	std::function<sf::Vector2f* ()> setTextCoorFunc;

	TileMap(VertexType type, const std::string& name = "");
	virtual ~TileMap() = default;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size, const std::string texId);
	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void UpdateTransform();

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
	void drawGrid(const sf::Vector2i& count, const sf::Vector2f& size);

	void SetTexture(sf::Texture* tex) { texture = tex; };
};

