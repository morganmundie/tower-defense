/**
 * \file DiagTimer.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "DiagTimer.h"

using namespace std;
using namespace Gdiplus;

/** 
 * Constructor
 * @param game The Towers game 
 */
CDiagTimer::CDiagTimer(CTowersGame* game) : CDialogue(game)
{
    SetImage(L"grass1.png");
}

/// Default destructor
CDiagTimer::~CDiagTimer()
{
}

/** 
 * Draws a timer. Overrwitten fucntion.
 * @param graphics The Graphics object 
 */
void CDiagTimer::Draw(Gdiplus::Graphics* graphics)
{
    
}

/** 
 * Sets the current level number
 * @param num The level number 
 */
void CDiagTimer::SetLevelNumber(int num)
{
    mLevelNum = num;
}
