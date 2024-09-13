/**
 * \file GoButton.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "GoButton.h"

using namespace std;

/// Default image
const wstring EmptyImage = L"button-go.png";

/** 
 * Constructor
 * @param item The game 
 */
CGoButton::CGoButton(CTowersGame* item) : CDialogue(item)
{
	SetImage(EmptyImage);
}

/// Default destructor
CGoButton::~CGoButton()
{
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location
 * @param y Y location
 * @returns Pointer to item we clicked on or nullptr if none.
 */
bool CGoButton::HitTest(double x, double y)
{
	double wid = this->GetWidth();
	double hit = this->GetHeight();

	// Make x and y relative to the top-left corner of the bitmap image
	// Subtracting the center makes x, y relative to the center of the image.
	// Adding half the size makes x, y relative to the top corner of the image
	double testX = x - GetX() + wid / 2;
	double testY = y - GetY() + hit / 2;

	// Test to see if x, y are in the image
	if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
	{
		// We are outside the image
		return false;
	}
	else
	{
		return true;
	}
}
