/**
 * \file ConfigureRoad.h
 *
 * \author Jacob Frank
 *
 * Concrete visitor to modify values of Road Tiles
 */

#pragma once
#include "ItemVisitor.h"
#include "TileRoad.h"
#include <string>

 /**
   *  Implements a visitor to configure a road
   */
class CConfigureRoad : public CItemVisitor
{
public:

	/** Gets the road type from the tile which was accepted
	 * @returns A string representing the road type 
	 */
	std::wstring GetRoadType() { return mType; };

	/** Checks if this road is a starting road
	 * @returns True if a starter, false if not 
	 */
	bool IsStartTile() { return mFoundStarter; };

	/** Gets the road tile which was accepted
	 * @returns A road tile 
	 */
	CTileRoad* GetRoad() { return mRoad; };

	/** Gets if this is a road
	 * \return boolean if road 
	 */
	bool IsRoad() { return mIsRoad; }

	/// This function generates a balloon
	void SetStarterRoad() { mRoad->SetStarterRoad(true); }

	void VisitTileRoad(CTileRoad* road) override;

	/** 
	 * Hit tests the tile road for a balloon
	 * @param x The x value of the balloon
	 * @param y The y value of the balloon
	 * @param radius The radius to check 
	 * @param dartTower True if tower shoots darts
	 * @returns Int of ballons hit
	 */
	int HitTestRoad(int x, int y, double radius, bool dartTower) { return mRoad->HitTestAllBalloons(x, y, radius, dartTower); }

private:
	/// Pointer to road
	CTileRoad* mRoad = nullptr;  

	/// Bool if the visitor has visited a road
	bool mIsRoad = false;

	/// Bool if a starter road has been visited
	bool mFoundStarter = false;

	/// Type of road
	std::wstring mType;
};

