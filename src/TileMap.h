#ifndef TILE_MAP_H
#define TILE_MAP_H

#include "../include/olcPixelGameEngine.h"
#include <memory>
#include <vector>

class TileMap {
private:
	static constexpr size_t width_ = 24;
	static constexpr size_t height_ = 30;
	std::unique_ptr<olc::Sprite> sprTile;
	std::unique_ptr<olc::Sprite> sprBreakableTile;
public:
	TileMap();
	TileMap(const std::vector<int> &map);
	size_t width() const;
	size_t height() const;
	size_t size() const;
	void loadMap(const std::vector<int> &map);
	void drawMap(olc::PixelGameEngine *game);
//private:
	std::vector<int> blocks;
	olc::vi2d vBlockSize = olc::vi2d(16, 16);
};

#endif /* ifndef TILE_MAP_H */
