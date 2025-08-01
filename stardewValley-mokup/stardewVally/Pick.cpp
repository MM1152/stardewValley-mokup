#include "stdafx.h"
#include "Pick.h"
#include "Map.h"
#include "Player.h"
#include "InteractionObject.h"

Pick::Pick(ItemInfo info)
	:InGameItem(info)
{
}
void Pick::Update(float dt)
{
	InGameItem::Update(dt);

	if (startAnimation) {
		hoeAni.Update(dt);
		SetPosition(itemSp.getPosition() + plusPos);

		//SetOrigin({ player->GetLocalBounds().width / 2 + 0.5f , player->GetLocalBounds().height + 5.f });
	}
}

void Pick::Reset()
{
	InGameItem::Reset();
	SetOrigin(Origins::BC);

	ANI_CLIP_MGR.Load(ANIMATION_PATH"pick/pickFront.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"pick/pickBack.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"pick/pickLeft.csv");

	hoeAni.SetTarget(&itemSp);
	itemSp.setScale({ 1.f , 1.f });

	hoeAni.AddEvent("pickfront", 3, [this]() {
		startAnimation = false;
		});
	hoeAni.AddEvent("pickback", 3, [this]() {
		startAnimation = false;
		});

	hoeAni.AddEvent("pickleft", 0, [this]() {
		itemSp.setRotation(0);
		});

	hoeAni.AddEvent("pickleft", 1, [this]() {
		if (itemSp.getScale().x > 0) {
			itemSp.setRotation(45);
		}
		else {
			itemSp.setRotation(-45);
		}
		});
	hoeAni.AddEvent("pickleft", 2, [this]() {
		if (itemSp.getScale().x > 0) {
			itemSp.setRotation(75);
		}
		else {
			itemSp.setRotation(-75);
		}
		});
	hoeAni.AddEvent("pickleft", 3, [this]() {
		if (itemSp.getScale().x > 0) {
			itemSp.setRotation(90);
		}
		else {
			itemSp.setRotation(-90);
		}
		startAnimation = false;

		});

}

bool Pick::UseItem()
{
	Map* map = player->GetMap();

	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };

	int cellIdx = map->GetCellIndex(holePos, 2);
	if (cellIdx >= map->GetCellDatas(2).size()) return false;
	auto cellData = map->GetCell(cellIdx, 2);

	StartAnimation(lookDir);
	player->PlayUseItemAnimation(lookDir);
	startAnimation = true;

	if (cellData.idx == 313) {
		CellData changeCellData = map->GetTextureCell(-1, 2);
		cellData.interactionObj->Interaction();
		cellData.interactionObj = nullptr;

		map->SetCellData(cellIdx, 2, &changeCellData);
		return InGameItem::UseItem();
	}

	if (cellData.idx == 34) {
		CellData changeCellData = map->GetTextureCell(-1, 2);
		cellData.interactionObj->Interaction();
		cellData.interactionObj = nullptr;
		
		map->SetCellData(cellIdx, 2, &changeCellData);
		return InGameItem::UseItem();
	}
	return false;
}

void Pick::Draw(sf::RenderWindow& window)
{
	if (startAnimation) {
		window.draw(itemSp);
	}
}

void Pick::StartAnimation(sf::Vector2i lookDir)
{
	itemSp.setRotation(0);

	if (prevDir == lookDir) return;

	prevDir = lookDir;
	if (lookDir.y == 1) {
		hoeAni.Play(ANIMATION_PATH"pick/pickFront.csv");
		itemSp.setScale({ -1.f, 1.f });
		plusPos = { 0 , -8 };
	}
	if (lookDir.y == -1) {
		hoeAni.Play(ANIMATION_PATH"pick/pickBack.csv");
		itemSp.setScale({ -1.f, 1.f });
		plusPos = { 0 , -15 };
	}
	if (lookDir.x == -1) {
		hoeAni.Play(ANIMATION_PATH"pick/pickLeft.csv");
		itemSp.setScale({ -1.f, 1.f });
		plusPos = { -3 , -15 };
	}
	if (lookDir.x == 1) {
		hoeAni.Play(ANIMATION_PATH"pick/pickLeft.csv");
		plusPos = { 5 , -18 };
		itemSp.setScale({ 1.f, 1.f });
	}
}
