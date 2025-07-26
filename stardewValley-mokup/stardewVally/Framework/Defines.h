#pragma once

#define DEF_DEV
#define INVEN_IMG_PATH "InventoryImg/"
#define ITEM_IMG_PATH "ItemImg/"
#define FONT_PATH "Font/"
#define MAP_PATH "MapData/"
#define GRAPHICS_PATH "graphics/"
enum class SortingLayers
{
	Background,
	Foreground,
	Default,
	UI,
};

enum class Origins
{
	TL, TC, TR,	// 0 1 2
	ML, MC, MR,	// 3 4 5
	BL, BC, BR, // 6 7 8
	Custom
};

enum class SceneIds
{
	None = -1,
	Test,
	Game,
	Dev1,
	Animator,
	Maptool,
	LoadMapTest,
	ChangeTile,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};