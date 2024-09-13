/**
 * \file Tower.h
 *
 * \author Rohit Vadlamudi
 *
 *  Base class for any tower in our game
 */

#pragma once
#include "Item.h"
#include "TowersGame.h"

 /**
  *  Implements a simple tower we can manipulate
  */
class CTower : public CItem
{
public:

	CTower(CTowersGame* game);

	/// Default constructor (disabled)
	CTower() = delete;

	virtual ~CTower();

	/// Copy Constructor Disabled
	CTower(const CTower&) = delete;

	/** 
	 * The attack function for a tower. All towers must be capable of performing some sort of attack.
	 */
	virtual void Attack() = 0;

	/** 
	 * Determines if a tower is placed on a tile (stationary)
	 * @returns If the tower is stationary (true) or not (false) 
	 */
	bool GetIsPlaced() { return mIsPlaced; }

	/** 
	 * Determines if a tower is placed on a tile (stationary)
	 * @param placed If the tower is stationary (true) or not (false) 
	 */
	void SetIsPlaced(bool placed) { mIsPlaced = placed; }

	/**
 	 * Method used to call all entity render functions that a tower may own.
	 * @param graphics The graphics object
	 */
	virtual void RenderEntities(Gdiplus::Graphics* graphics) = 0;
private:
	/** 
	 * Determines if a tower is placed on a tile (stationary). 
	 * Towers on the palette should not be stationary.
	 */
	bool mIsPlaced = false; 

};

