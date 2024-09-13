/**
 * \file TowerBomb.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TowerBomb.h"

using namespace std;

/// Default image
const wstring EmptyImage = L"tower-bomb.png";

using namespace Gdiplus;

/** 
 * Constructor
 * @param item The Towers game 
 */
CTowerBomb::CTowerBomb(CTowersGame* item) : CTower(item)
{
	mCircleX = this->GetX();
	mCircleY = this->GetY();
	SetImage(EmptyImage);
	CBombCounter visitor;
	auto TowersGame = GetGame();
	TowersGame->Accept(&visitor);
	int numOfBombs = visitor.GetNumberOfBombs();
	//adds 3 seconds to explosion time for each bomb in the game
	mTimeToExplode = mTimeToExplode + (3 * numOfBombs);
}

/// Default destructor
CTowerBomb::~CTowerBomb()
{
}

/**
 * Code for updating the Tower Bomb
 * @param elapsed The elapsed time
 */
void CTowerBomb::Update(double elapsed)
{
	
	// Allow an attack to be initiated
	if (GetGame()->GetGoButtonPressed())
	{
		mTimeToExplode -= elapsed;
		if (mTimeToExplode <= 0)
		{

			mCircleX = this->GetX() - mOffset;
			mCircleY = this->GetY() - mOffset;
			mDrawCircle = true;
			mExplosionDuration -= elapsed;
			if (GetIsPlaced() && !mBlownUp)
			{
				Attack();
			}
		}
	}
}

/** 
 * Function that controls/initiates the attack sequence of a tower.
 */
void CTowerBomb::Attack()
{
	// Set the new drawing location of the circle up and to the left

	mCircleX -= 100; // Adding X sets an object left on screen
	mCircleY -= 100; // Subtracting Y sets an object upwards on screen

	// set the radius
	mBombDiameter = 200;
	mShow = true;
	// Test if the radius is too large (200px)
	if (mDrawCircle == true &&
		(mExplosionDuration <=0))
	{
		mDrawCircle = false;
		mBlownUp = true;
	}

	int collide = GetGame()->CollisionCheck(GetX(), GetY(), mBombDiameter/2, false);

	if (collide > 0)
	{
		GetGame()->AddToGameScore(2 * collide);
	}

}

/** 
 * Draw this item
 * @param graphics The graphics context to draw on 
 */
void CTowerBomb::Draw(Gdiplus::Graphics* graphics)
{
	if (mBlownUp)
	{
		return;
	}
	CItem::Draw(graphics);

}

/**
 * Method Disabled (no entities are drawn on/in bomb entities)
 * @param graphics The graphics 
 */
void CTowerBomb::RenderEntities(Gdiplus::Graphics* graphics)
{
	if (!mBlownUp) 
	{
		// Create pen.
		SolidBrush redPen(Color(128, 0, 0));
		SolidBrush middlePen(Color(140, 20, 0));
		SolidBrush innerPen(Color(140, 60, 20));

		// 1. The circle must be within an acceptable radius
		// 2. The tower must be placed
		// 3. The game must be started (go button pressed)
		if (mDrawCircle && GetIsPlaced() && GetGame()->GetGoButtonPressed() && mShow)
		{
			graphics->FillEllipse(&redPen, mCircleX, mCircleY, mBombDiameter, mBombDiameter);
			graphics->FillEllipse(&middlePen, (mCircleX-GetX())*2/3 + GetX(), (mCircleY-GetY())*2/3 + GetY(), mBombDiameter*2/3, mBombDiameter*2/3);
			graphics->FillEllipse(&innerPen, (mCircleX - GetX()) / 3 + GetX(), (mCircleY - GetY()) / 3 + GetY(), mBombDiameter / 3, mBombDiameter / 3);
		}
	}
	
}
