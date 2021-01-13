#ifndef BAT_H
#define BAT_H

#include "Entity.h"
#include "TileMap.h"
#include <memory>

class Bat : public Entity {
public:
	Bat(TileMap *m);
	void update() override;
	void draw(olc::PixelGameEngine *game) override;
	float width() const;
	float speed() const;
private:
	float width_ = 4.0f;
	float speed_ = 20.0f;
	std::unique_ptr<olc::Sprite> sprBat;
	TileMap *map;
};

#endif /* ifndef BAT_H */
