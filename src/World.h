#ifndef WORLD_H
#define WORLD_H

#include "../include/olcPixelGameEngine.h"
#include "GameObject.h"
#include <algorithm>
#include <memory>
#include <vector>

class World {
public:
	using size_type = std::vector<int>::size_type;
	using iterator = std::vector<int>::iterator;
	using const_iterator = std::vector<int>::const_iterator;
	World(olc::PixelGameEngine &gameEngine);
	World(const std::vector<int> &map);
	void update(float fElapsedTime);
	void draw();
	int& operator[](const size_type index);
	size_t width() const { return width_; }
	size_t height() const { return height_; }
	size_t size() const { return tileMap.size(); }
	olc::vi2d blockSize() { return blockSize_; }
	void loadMap(const std::vector<int> &map);
	iterator begin() { return tileMap.begin(); }
	iterator end() { return tileMap.end(); }
	const_iterator cbegin() const { return tileMap.cbegin(); }
	const_iterator cend() const { return tileMap.cend(); }
private:
	static constexpr size_t width_{24};
	static constexpr size_t height_{30};
	olc::vi2d blockSize_{ 16, 16 };
	std::vector<int> tileMap{};
	std::unique_ptr<olc::PixelGameEngine> gameEngine_{nullptr};
	std::unique_ptr<olc::Sprite> sprTile{nullptr};
	std::unique_ptr<olc::Sprite> sprBreakableTile{nullptr};
};

inline
int& World::operator[](const size_type index) { return tileMap[index]; }
#endif /* ifndef WORLD_H */
