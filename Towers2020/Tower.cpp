/**
 * \file Tower.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "Tower.h"

using namespace std;
using namespace Gdiplus;

/** 
 * Constructor
 * @param game The Towers game 
 */
CTower::CTower(CTowersGame* game) : CItem(game)
{
}

/// Destructor
CTower::~CTower()
{
}