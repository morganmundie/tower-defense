/**
 * \file ConfigureRoad.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "ConfigureRoad.h"

/** Visits the road tile which was accepted
 * @param road A road tile 
 */
void CConfigureRoad::VisitTileRoad(CTileRoad* road)
{
	mRoad = road;
	mIsRoad = true;
	if (mRoad != nullptr)
	{
		mFoundStarter = mRoad->IsStartTile();
		mType = mRoad->GetType();
	}
}