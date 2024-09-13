/**
 * \file FindBalloon.cpp
 *
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "FindBalloon.h"

/** 
 * Find if a road has a balloon in its collection
 */
void CFindBalloon::FindBalloon()
{
	if (mRoad != nullptr) 
	{
		mRoad->AcceptAllBalloons(this);
	}
}

/**
 * A balloon has been found on the road being visited
 * @param road The road being visited 
 */
void CFindBalloon::VisitTileRoad(CTileRoad* road) 
{ 
	CFindBalloon balloon;
	mRoad = road; 
	if (mRoad != nullptr) 
	{
		mRoad->AcceptAllBalloons(&balloon);
		if (balloon.FoundBalloon())
		{
			mFoundBalloon = true;
		}
	}
}

/**
 * A balloon has been found (visited)
 * @param balloon The balloon being visited 
 */
void CFindBalloon::VisitBalloon(CBalloon* balloon) 
{ 
	mFoundBalloon = true; 
}