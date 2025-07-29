#include "stdafx.h"
#include "Hoe.h"
#include "Map.h"
#include "Player.h"
Hoe::Hoe(ItemInfo info)
	:InGameItem(info)
{
}

void Hoe::Update(float dt)
{
	InGameItem::Update(dt);

	if (startAnimation) {
		hoeAni.Update(dt);
		SetOrigin({ player->GetLocalBounds().width / 2 + 0.5f , player->GetLocalBounds().height + 5.f });
	}
}

void Hoe::Reset()
{
	InGameItem::Reset();

	ANI_CLIP_MGR.Load(ANIMATION_PATH"hoe/hoeFront.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hoe/hoeBack.csv");

	hoeAni.SetTarget(&itemSp);
	itemSp.setScale({ 0.8f , 0.8f });

	hoeAni.AddEvent("hoefront", 3, [this]() {
		startAnimation = false;
	});
	hoeAni.AddEvent("hoeback", 3, [this]() {
		startAnimation = false;
	});
}

void Hoe::UseItem()
{
	Map* map = player->GetMap();

	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };

	int cellIdx = map->GetCellIndex(holePos, 0);
	int cellData = map->GetCell(cellIdx, 0).idx;
	
	StartAnimation(lookDir);
	player->PlayUseItemAnimation(lookDir);
	startAnimation = true;

	if (cellData == 25) {
		CellData changeCellData = map->GetTextureCell(308, 0);
		map->SetCellData(cellIdx , 0 , &changeCellData);
	}
}

void Hoe::Draw(sf::RenderWindow& window)
{
	if (startAnimation) {
		window.draw(itemSp);
	}
}

void Hoe::StartAnimation(sf::Vector2i lookDir)
{
	if (prevDir == lookDir) return;

	prevDir = lookDir;
	if (lookDir.y == 1) {
		hoeAni.Play(ANIMATION_PATH"hoe/hoeFront.csv");
	}
	if (lookDir.y == -1) {
		hoeAni.Play(ANIMATION_PATH"hoe/hoeBack.csv");
	}
}


