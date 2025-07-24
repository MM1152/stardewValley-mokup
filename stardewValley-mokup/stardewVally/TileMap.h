#pragma once
#include "GameObject.h"
#include "Map.h"

enum class VertexType {
	Palette,
	Draw,
	Grid,
	Game,
};

class TileMap : public GameObject
{
private:
	bool InArea(sf::Vector2f mousePos);
protected:
	VertexType type;
	std::vector<CellData> cellData;
	sf::VertexArray va;

	Scene* scene;

	std::string spriteSheetId;
	sf::Texture* texture = nullptr;
	sf::Transform transform;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;

	int index = -1;

public:
	std::function<void(sf::Vector2f*)> getIndexFunc;
	std::function<sf::Vector2f*()> setTextCoorFunc;

	TileMap(VertexType type, const std::string& name = "");
	virtual ~TileMap() = default;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size, const std::string texId);
	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void Set(const std::string texId, std::vector<CellData>& cellData);
	
	void SettingCellData(int idx, CellData cellData);
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

	void SetTexture(const std::string tex);
	void SetScene(Scene* scene) { this->scene = scene; };
	sf::VertexArray& GetVaData() { return va; };
	sf::Vector2i GetCellCount() { return cellCount; };
	std::string GetTextureId() { return spriteSheetId; };

	CellData& GetCellData(int idx) { return cellData[idx]; };
	std::vector<CellData>& GetCellDatas() { return cellData; };
	void SetCellData(int idx, CellData& celldata);
	virtual sf::FloatRect GetLocalBounds() const
	{
		return va.getBounds();
	}
};

