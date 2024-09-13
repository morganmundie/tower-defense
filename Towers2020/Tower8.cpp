/**
 * \file Tower8.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "Tower8.h"
#include <math.h>
using namespace std;
using namespace Gdiplus;

/// Default image
const wstring EmptyImage = L"tower8.png";

/** 
 * Constructor
 * @param item The Towers game 
 */
CTower8::CTower8(CTowersGame* item) : CTower(item)
{
	SetImage(EmptyImage);
}

/// Default Destructor
CTower8::~CTower8()
{
}

/** 
 * Generates all 8 darts in predetermined positions around the tower. 
 */
void CTower8::GenerateAllDarts()
{
	GenerateDart(10, 0, 0); // Generate Eastbound dart

	GenerateDart(10, 10, 1); // Generate SouthEastbound dart

	GenerateDart(0, 10, 2); // Generate Southbound dart

	GenerateDart(-10, 10, 3); // Generate SouthWestbound dart

	GenerateDart(-10, 0, 4); // Generate Westbound dart

	GenerateDart(-10, -10, 5); // Generate NorthWestbound dart

	GenerateDart(0, -10, 6); // Generate Northbound dart

	GenerateDart(10, -10, 7); // Generate NorthEastbound dart
}

/** 
 * Generates a Dart entity at the request of the tower. 
 * @param offsetX The X offset relative to the tower.
 * @param offsetY The Y offset relative to the tower.
 * @param sector The clockwise rotation in radians (PI/4) around the tower 
 */
void CTower8::GenerateDart(double offsetX, double offsetY, double sector)
{
	auto dart = make_shared<CDart>(GetGame());
	dart->setXOffset(offsetX);
	dart->setYOffset(offsetY);
	dart->SetLocation(GetX() + dart->GetXOffset(), GetY() + dart->GetYOffset());
	dart->SetAngle(sector * 3.141592 / 4);
	mDarts.push_back(dart);
}

/** Function that controls/initiates the attack sequence of a tower. 
 */
void CTower8::Attack()
{
	GenerateAllDarts();
}

/**
 * Code for updating the Tower 8
 * @param elapsed The elapsed time
 */
void CTower8::Update(double elapsed)
{
	if (GetGame()->GetGoButtonPressed()) {
		mTimeTofire -= elapsed;
	}
	if (mTimeTofire < 0) 
	{
		mTimeTofire = 5;

		// Allow an attack to be initiated
		if (GetIsPlaced() && GetGame()->GetGoButtonPressed())
		{
			Attack();
		}
	}
	for (auto dart : mDarts) 
	{
		dart->Update(elapsed);
	}

	if (mDarts.size() > 0) 
	{
		auto dart = mDarts[0];

		double dartRadius = sqrt(pow((double)dart->GetX() - (double)GetX(), 2) + pow((double)dart->GetY() - (double)GetY(), 2));

		if (dartRadius >= 100) 
		{
			mDarts.clear();
		}

		int collide = GetGame()->CollisionCheck(GetX(), GetY(), dartRadius, true);

		if (collide > 0)
		{
			GetGame()->AddToGameScore(10 * collide);
		}
	}
}

/** 
 * Draw this item
 * @param graphics The graphics context to draw on 
 */
void CTower8::Draw(Gdiplus::Graphics* graphics)
{
	CItem::Draw(graphics);

}

/**
 * Method used to call all dart render functions.
 * @param graphics The graphics object
 */
void CTower8::RenderEntities(Gdiplus::Graphics* graphics)
{
	for (auto dart : mDarts)
	{
		dart->Draw(graphics, dart->GetXOffset(), dart->GetYOffset());
	}
}




