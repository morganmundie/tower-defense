/**
 * \file TowerRings.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TowerRings.h"

using namespace std;

/// Default image
const wstring EmptyImage = L"tower-rings.png";

/** 
 * Constructor
 * @param item The Towers game 
 */
CTowerRings::CTowerRings(CTowersGame* item) : CTower(item)
{
	mCircleX = this->GetX();
	mCircleY = this->GetY();
	SetImage(EmptyImage);
}

/// Default destructor
CTowerRings::~CTowerRings()
{
}

/**
 * Code for updating the Tower Rings
 * @param elapsed The elapsed time
 */
void CTowerRings::Update(double elapsed)
{

	mElapsed = elapsed;
	if (GetGame()->GetGoButtonPressed()) {
		mTimeTofire -= elapsed;
	}
	if (mTimeTofire <= 0) 
	{
		mCircleX = this->GetX() - mOffset;
		mCircleY = this->GetY() - mOffset;
		mDrawCircle = true;
		mTimeTofire = 5;
		mCircleDiameter = 10;
	}

	// Allow an attack to be initiated
	if (GetIsPlaced() && GetGame()->GetGoButtonPressed())
	{
		Attack();
	}
}

/** Function that controls/initiates the attack sequence of a tower. 
 */
void CTowerRings::Attack()
{
	if (mDrawCircle)
	{
		int collide = GetGame()->CollisionCheck(GetX(), GetY(), mCircleDiameter/2, false);

		if (collide > 0)
		{
			GetGame()->AddToGameScore(3 * collide);
		}
	}
	// Set the new drawing location of the circle up and to the left

	// Adding X sets an object left on screen
	mCircleX = mCircleX - mOffset + cos(3 * 3.141592 / 4) * 10 * mElapsed; 
	// Subtracting Y sets an object upwards on screen
	mCircleY = mCircleY - mOffset - sin(3 * 3.141592 / 4) * 10 * mElapsed; 

	// Increment the radius by 10
	mCircleDiameter = 2 * abs(GetX() - mCircleX);

	// Test if the radius is too large (100px)
	// The first boolean in the if statement saves time by not repeatedly having to test math on downtime
	if (mDrawCircle == true && mCircleDiameter > 200)
	{
		mDrawCircle = false;
	}

	
}

/**
 * Renders the ring of the tower
 * @param graphics The graphics object
 */
void CTowerRings::RenderEntities(Gdiplus::Graphics* graphics)
{
	// Create pen.
	Pen redPen(Color(255, 250, 20, 2));

	redPen.SetWidth(3.0F);

	// 1. The circle must be within an acceptable radius
	// 2. The tower must be placed
	// 3. The game must be started (go button pressed)
	if (mDrawCircle && GetIsPlaced() && GetGame()->GetGoButtonPressed())
	{
		graphics->DrawEllipse(&redPen, mCircleX, mCircleY, mCircleDiameter, mCircleDiameter);
	}
}

/** Draw this item
 * @param graphics The graphics context to draw on 
 */
void CTowerRings::Draw(Gdiplus::Graphics* graphics)
{
	CItem::Draw(graphics);
}
