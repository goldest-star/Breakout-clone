#ifndef INPUT_COMPONENT_H
#define INPUT_COMPONENT_H

#include "../include/olcPixelGameEngine.h"

class GameObject;
class World;

class InputComponent {
public:
	virtual ~InputComponent() = default;
	virtual void update(GameObject &obj, const olc::PixelGameEngine &pge, World &world) = 0;
};
#endif /* ifndef INPUT_COMPONENT_H */
