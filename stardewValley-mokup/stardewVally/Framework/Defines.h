#pragma once

#define DEF_DEV
#define INVEN_IMG_PATH "InventoryImg/"
#define ITEM_IMG_PATH "ItemImg/"
#define FONT_PATH "fonts/"
#define MAP_PATH "MapData/"
#define GRAPHICS_PATH "graphics/"
#define ANIMATION_PATH "animation/"
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
	Title,
	Test,
	Home,
	Game,
	Dev1,
	Animator,
	Maptool,
	LoadMapTest,
	ChangeTile,
	AnimationTest,
	Count,
};

enum class Sides
{
	Left,
	Right,
	None,
};