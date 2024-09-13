/**
 * \file CanMoveVisitor.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "CanMoveVisitor.h"
#include "Tower.h"
#include "Tower8.h"
#include "TowerRings.h"
#include "TowerBomb.h"
#include "Balloon.h"
#include "TowerAirship.h"
#include "ConfigureRoad.h"


/** 
 * Visits a Tower 8 object
 * @param tower8 Tower 8 object to visit 
 */
void CCanMoveVisitor::VisitTower8(CTower8* tower8)
{ 
	mKey = 1;
	mIsTower = true;
	mIsOpen = true;
	mTower = tower8;
}

/**
 * Visits a Tower Bomb object
 * @param bomb Tower Bomb object to visit
 */
void CCanMoveVisitor::VisitTowerBomb(CTowerBomb* bomb)
{
	mKey = 2;
	mIsTower = true;
	mIsOpen = true;
	mTower = bomb;
	mIsBlownUp = bomb->GetBlownUp();
}

/**
 * Visits a Tower Rings object
 * @param ring Tower Rings object to visit
 */
void CCanMoveVisitor::VisitTowerRings(CTowerRings* ring)
{
	mKey = 3;
	mIsTower = true;
	mIsOpen = true;
	mTower = ring;
	mRingAttacking = ring->GetAttacking();
}

/**
 * Visits a Tower Airship object
 * @param airship Tower Airship object to visit
 */
void CCanMoveVisitor::VisitTowerAirship(CTowerAirship* airship)
{
	mKey = 4;
	mIsTower = true;
	mIsOpen = true;
	mTower = airship;
}

/**
 * Visits a Tile Open object
 * @param open Tile Open (grass) object to visit
 */
void CCanMoveVisitor::VisitTileOpen(CTileOpen* open)
{
	mIsOpen = true;
}

/**
 * Visits an Entity-type object
 * @param entity The Entity-type object to visit
 */
void CCanMoveVisitor::VisitEntity(CEntity* entity)
{
	mIsEntity = true;
}

/**
 * Visits an Entity Balloon object
 * @param balloon The Entity Balloon object to visit
 */
void CCanMoveVisitor::VisitBalloon(CBalloon* balloon)
{
	mIsBalloon = true;
}

/**
* Visits an Entity Balloon object
* @param road The Entity Balloon object to visit
*/
void CCanMoveVisitor::VisitTileRoad(CTileRoad* road)
{
	mIsRoad = true;
	mRoad = road;
	if (mRoad != nullptr)
	{
		mFoundStarter = mRoad->IsStartTile();
		mType = mRoad->GetType();
	}
}

/** Changes the tower's placement status (mIsPlaced in CTower) to true (placed) 
 */
void CCanMoveVisitor::PlaceTower()
{
	mTower->SetIsPlaced(true);
}

/** Changes the tower's placement status (mIsPlaced in CTower) to false (lifted) 
 */
void CCanMoveVisitor::LiftTower()
{
	mTower->SetIsPlaced(false);
}

/**
 * Tests if this visitor has visited a road.
 * @returns True if a road has been visited. False if not.
 */
bool CCanMoveVisitor::IsRoad()
{
	if (mIsRoad)
	{
		mIsRoad = false;
		return true;
	}
	return false;
}

/**
 * Gets the road type from the tile which was accepted
 * @returns A string representing the road type 
 */
std::wstring CCanMoveVisitor::GetRoadType()
{
	return mType;
}