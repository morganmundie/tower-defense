/**
 * \file BombCounter.h
 *
 * \author
 *
 * A visitor that visits bomb towers and counts them
 *
 */

#pragma once
#include"TowerBomb.h"

/// BombCounter is able to visit all items
class CBombCounter: public CItemVisitor
{
public:
	/** 
	 * Returns the number of bomb towers found
	 * @returns The number of bombs recorded. 
	 */
	int GetNumberOfBombs() const{ return mNumberOfBombs; }

	/**
	 * Returns the number of bomb towers found
	 * @param bomb The bomb being visited 
	 */
	void CBombCounter::VisitTowerBomb(CTowerBomb* bomb)
	{
		mNumberOfBombs++;
	}
private:
	/// The number of bombs visited
	int mNumberOfBombs = 0; 
};

