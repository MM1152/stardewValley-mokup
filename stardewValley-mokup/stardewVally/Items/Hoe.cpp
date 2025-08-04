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
		SetPosition(itemSp.getPosition() + plusPos);

		//SetOrigin({ player->GetLocalBounds().width / 2 + 0.5f , player->GetLocalBounds().height + 5.f });
	}
}

void Hoe::Init()
{
	InGameItem::Init();
	SOUND_MGR.Load(SoundType::HOE, "sound/hoe.mp3");
}

void Hoe::Reset()
{
	InGameItem::Reset();
	SetOrigin(Origins::BC);
	
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hoe/hoeFront.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hoe/hoeBack.csv");
	ANI_CLIP_MGR.Load(ANIMATION_PATH"hoe/hoeLeft.csv");

	hoeAni.SetTarget(&itemSp);
	itemSp.setScale({ 1.f , 1.f });

	hoeAni.AddEvent("hoefront", 3, [this]() {
		startAnimation = false;
	});
	hoeAni.AddEvent("hoeback", 3, [this]() {
		startAnimation = false;
	});

	hoeAni.AddEvent("hoeleft", 0, [this]() {
		itemSp.setRotation(0);
	});

	hoeAni.AddEvent("hoeleft", 1, [this]() {
		if (itemSp.getScale().x > 0) {
			itemSp.setRotation(45);
		}
		else {
			itemSp.setRotation(-45);
		}
	});
	hoeAni.AddEvent("hoeleft", 2, [this]() {
		if (itemSp.getScale().x > 0) {
			itemSp.setRotation(75);
		}
		else {
			itemSp.setRotation(-75);
		}
	});
	hoeAni.AddEvent("hoeleft", 3, [this]() {
		if (itemSp.getScale().x > 0) {
			itemSp.setRotation(90);
		}
		else {
			itemSp.setRotation(-90);
		}
		startAnimation = false;
		
	});

}

bool Hoe::UseItem()
{
	Map* map = player->GetMap();

	sf::Vector2i lookDir = player->GetLookDir();
	sf::Vector2f holePos = { player->GetPosition().x + (lookDir.x * 16.f) , player->GetPosition().y + (lookDir.y * 16.f) };

	int cellIdx = map->GetCellIndex(holePos, 0);
	if (cellIdx >= map->GetCellDatas(0).size()) return false;
	auto cellData = map->SequentialGetCell(cellIdx);
	
	StartAnimation(lookDir);
	player->PlayUseItemAnimation(lookDir);
	startAnimation = true;

	if (cellData.layer == 0 && cellData.idx == 25) {
		SOUND_MGR.Play(SoundType::HOE);
		CellData changeCellData = map->GetTextureCell(308, 0);
		map->SetCellData(cellIdx , 0 , &changeCellData);
		return InGameItem::UseItem();
	}
	return false;
}

void Hoe::Draw(sf::RenderWindow& window)
{
	if (startAnimation) {
		window.draw(itemSp);
	}
}

void Hoe::StartAnimation(sf::Vector2i lookDir)
{
	itemSp.setRotation(0);

	if (prevDir == lookDir) return;

	prevDir = lookDir;
	if (lookDir.y == 1) {
		hoeAni.Play(ANIMATION_PATH"hoe/hoeFront.csv");
		itemSp.setScale({ -1.f, 1.f });
		plusPos = {0 , -8 };
	}
	if (lookDir.y == -1) {
		hoeAni.Play(ANIMATION_PATH"hoe/hoeBack.csv");
		itemSp.setScale({ -1.f, 1.f });
		plusPos = { 0 , -15 };
	}
	if (lookDir.x == -1) {
		hoeAni.Play(ANIMATION_PATH"hoe/hoeLeft.csv");
		itemSp.setScale({ -1.f, 1.f });
		plusPos = { -3 , -15 };
	}
	if (lookDir.x == 1) {
		hoeAni.Play(ANIMATION_PATH"hoe/hoeLeft.csv");
		plusPos = { 5 , -18 };
		itemSp.setScale({ 1.f, 1.f });
	}
}


