/*
 * IDrawable.h
 *
 *  Created on: Jul 8, 2016
 *      Author: default
 */

#ifndef IDRAWABLE_H_
#define IDRAWABLE_H_

struct SDL_Renderer;

#include <vector>
#include <SDL_rect.h>

#include "SDL2_gfxPrimitives.h"

#ifndef NULL
#define NULL 0
#endif

namespace Contracts {

class IDrawable {
public:
	IDrawable() {};
	virtual ~IDrawable() {};
	virtual void Draw(SDL_Renderer* rend, std::vector<IDrawable*>& others, SDL_Point coursor) = 0;
	virtual void Move(int, int) = 0;
	virtual SDL_Point GetCenter() = 0;
};

} /* namespace Contracts */

#endif /* IDRAWABLE_H_ */
