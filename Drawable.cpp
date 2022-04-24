/*
 * Drawable.cpp
 *
 *  Created on: Jul 8, 2016
 *      Author: default
 */

#include "Drawable.h"
#include <cstdlib>

namespace Implementations {

Drawable::Drawable(SDL_Point size) {
	RandomPut(size);
	m_rad = 1;
	m_radStep = 1;
}

Drawable::~Drawable() {
	// TODO Auto-generated destructor stub
}

void Drawable::Draw(SDL_Renderer* rend, std::vector<IDrawable*>& others, SDL_Point coursor) {
	filledCircleRGBA(rend, m_center.x, m_center.y, m_rad, 255, 255, 255, 255);
	for(IDrawable* ball : others)
	{
		float distance = sqrt(pow(m_center.x - ball->GetCenter().x, 2) + pow(m_center.y - ball->GetCenter().y, 2));
		if(ball != this && distance <= PointDistance)
		{
			int alpha = (255 - (255 * (distance / PointDistance))) / 2;
			lineRGBA(rend, m_center.x, m_center.y, ball->GetCenter().x, ball->GetCenter().y, 255, 255, 255, alpha);
		}
	}

	float distanceToCoursor = sqrt(pow(m_center.x - coursor.x, 2) + pow(m_center.y - coursor.y, 2));
	if(distanceToCoursor <= CoursorDistance)
	{
		int alpha = (255 - (255 * (distanceToCoursor / CoursorDistance)));
		lineRGBA(rend, m_center.x, m_center.y, coursor.x, coursor.y, Cursor_lineR, Cursor_lineG, Cursor_lineB, alpha);
	}

	if(CHANGE_SIZE_OF_DOTS)
	ChangeSize();
}

void Drawable::Move(int width, int height) {
	m_center.x += m_velocity.x;
	m_center.y += m_velocity.y;

	if(m_center.x >= width || m_center.x < 0 || m_center.y >= height || m_center.y < 0)
	{
		RandomPut({ width, height });
	}
}

SDL_Point Drawable::GetCenter() {
	return m_center;
}

void Drawable::ChangeSize() {

	if(m_rad == MaxRad)
	{
		m_radStep = -1;
	}
	else if(m_rad == 0)
	{
		m_radStep = 1;
	}

	m_rad += m_radStep;
}

void Drawable::RandomPut(SDL_Point size) {

	m_center = {
		rand() % size.x,
		rand() % size.y
	};

	m_velocity = {
		(rand() % MaxVelocity + 1) * (rand() % 2 == 0 ? 1 : -1 ),
		(rand() % MaxVelocity + 1) * (rand() % 2 == 0 ? 1 : -1 )
	};
}

} /* namespace Implementations */
