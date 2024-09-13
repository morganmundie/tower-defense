/**
 * \file TowerAirship.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "TowerAirship.h"
#include <math.h>
using namespace std;
using namespace Gdiplus;

/// Default image
const wstring EmptyImage = L"tower-airship.png";

/** 
 * Constructor
 * @param item The Towers game 
 */
CTowerAirship::CTowerAirship(CTowersGame* item) : CTower(item)
{
	SetImage(EmptyImage);
}

/// Destructor
CTowerAirship::~CTowerAirship()
{
}

/** Generates the airship. 
 */
void CTowerAirship::GenerateAirship()
{
	double offsetX = -10, offsetY = 0, sector = 0;
	mAirship = make_shared<CAirship>(GetGame());
	mAirship->setXOffset(offsetX);
	mAirship->setYOffset(offsetY);
	mAirship->SetLocation(GetX() + mAirship->GetXOffset(), GetY() + mAirship->GetYOffset());
	mAirship->SetAngle(sector * 3.141592 / 4);
}

/** 
 * Generates a Dart entity at the request of the tower. 
 * @param offsetX The X offset relative to the tower.
 * @param offsetY The Y offset relative to the tower.
 * @param sector The clockwise rotation in radians (PI/4) around the tower 
 */
void CTowerAirship::GenerateDart(double offsetX, double offsetY, double sector)
{
	auto dart = make_shared<CDart>(GetGame());
	dart->setXOffset(offsetX);
	dart->setYOffset(offsetY);
	dart->SetLocation(GetX() + dart->GetXOffset() - 170, GetY() + dart->GetYOffset());
	dart->SetAngle(sector * 3.141592 / 4);
	mDarts.push_back(dart);
}

/** 
 * Generates all 8 darts in predetermined positions around the tower. 
 */
void CTowerAirship::GenerateAllDarts()
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

/** Controls/initiates the attack sequence of a tower. 
 */
void CTowerAirship::Attack()
{
	GenerateAirship();
	mAirshipDraw = true;
}

/**
 * Code for updating the Tower Airship
 * @param elapsed The elapsed time
 */
void CTowerAirship::Update(double elapsed)
{
	if (GetGame()->GetGoButtonPressed()) {
		mTimeTofire -= elapsed;
	}
	if (mTimeTofire < 0)
	{
		mTimeTofire = 10;

		// Allow an attack to be initiated
		if (GetIsPlaced() && GetGame()->GetGoButtonPressed())
		{
			Attack();
		}
	}

	if (mAirship != nullptr)
	{
		mAirship->Update(elapsed);
		for (auto dart : mDarts)
		{
			dart->Update(elapsed);
		}
	}
	

	if (mAirship != nullptr)
	{
		auto airshipDistance = sqrt(pow((double)mAirship->GetX() - (double)GetX(), 2) + pow((double)mAirship->GetY() - (double)GetY(), 2));
		if (airshipDistance >= 250)
		{
			mAirshipDraw = false;
			
		}

		if (airshipDistance >= 150 && !mDrawDarts && airshipDistance <= 190)
		{
			mDrawDarts = true;
			GenerateAllDarts();
		}

		if (mDarts.size() > 0)
		{
			//auto dart = mDarts[0];
			int collide = GetGame()->CollisionCheck(GetX() - 170, GetY(), abs(airshipDistance) - 150, true);
			if (collide > 0)
			{
				GetGame()->AddToGameScore(10 * collide);
			}
			if (!mAirshipDraw)
			{
				mDarts.clear();

				mDrawDarts= false;
			}
		}

		else if (mAirship->GetX() < GridSpacing * -1 )
		{
			mAirshipDraw = false;
		}
		
	}
}

/** 
 * Draw this item
 * @param graphics The graphics context to draw on 
 */
void CTowerAirship::Draw(Gdiplus::Graphics* graphics)
{
	CItem::Draw(graphics);

}

/**
 * Method used to call all dart render functions
 * @param graphics The graphics object
 */
void CTowerAirship::RenderEntities(Gdiplus::Graphics* graphics)
{
	if (mAirship != nullptr && mAirshipDraw)
	{
		mAirship->Draw(graphics, mAirship->GetXOffset(), mAirship->GetYOffset());

	}

	if (mDrawDarts) 
	{
		for (auto dart : mDarts)
		{
			dart->Draw(graphics, dart->GetXOffset(), dart->GetYOffset());
		}
	}
	
}