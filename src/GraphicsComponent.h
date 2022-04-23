#ifndef GRAPHICS_COMPNONENT_H
#define GRAPHICS_COMPNONENT_H

#include <olcPixelGameEngine.h>
class GameObject;

class GraphicsComponent {
public:
	virtual ~GraphicsComponent() = default;
	virtual void update(GameObject &obj, olc::PixelGameEngine &pge) = 0;
};
#endif /* ifndef GRAPHICS_COMPNONENT_H */
