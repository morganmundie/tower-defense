/**
 * \file ScoreCounter.h
 *
 * \author Dimitri Snell
 *
 * A visitors that is tasked with visiting towers to individually count scores.
 * Takes total of scores and passes this information off to the game for processing
 */

#pragma once
#include"TowerBomb.h"
#include"TowerRings.h"
#include"Tower8.h"
#include "TowerAirship.h"
#include "TileRoad.h"

/// A Tower visitor
class CScoreCounter : public CItemVisitor
{
public:
	/** 
	 * Get the current score
	 * @returns score of towers 
	 */
	int GetScore() const { return mScore; }

	


private:

	/// Total score
	int mScore = 0;
};

