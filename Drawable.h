/*
 * Drawable.h
 *
 *  Created on: Jul 8, 2016
 *      Author: default
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include "IDrawable.h"
#include "Constants.h"
#include <SDL_rect.h>

namespace Implementations {

using namespace Contracts;

class Drawable : public IDrawable{
public:
	Drawable(SDL_Point size);
	virtual ~Drawable();
	virtual void Draw(SDL_Renderer* rend, std::vector<IDrawable*>& others, SDL_Point coursor);
	virtual void Move(int, int);
	virtual SDL_Point GetCenter();
protected:
	SDL_Point m_center;
	unsigned char m_rad;
	char m_radStep;
	SDL_Point m_velocity;
	//static const int PointDistance = 200;
	//static const int CoursorDistance = 450;
	//static const char MaxRad = 10;
	//static const int MaxVelocity = 2;
	void ChangeSize();
	void RandomPut(SDL_Point size);
};

} /* namespace Implementations */

#endif /* DRAWABLE_H_ */
