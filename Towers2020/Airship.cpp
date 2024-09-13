/**
 * \file Airship.cpp
 *
 * \author Morgan Mundell
 */

#include "pch.h"
#include "Airship.h"

using namespace std;
using namespace Gdiplus;

/// Default image
const std::wstring EmptyImage = L"airship.png";

/// Constant to covert radians to degrees.
const double RtoD = 57.2957795;


/** 
 * Constructor
 * @param item The Towers game 
 */
CAirship::CAirship(CTowersGame* item) : CEntity(item)
{
    // Creates a ship object
    wstring filename = ImagesDirectory + EmptyImage;
    mItemImage = std::unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(filename.c_str()));
    if (mItemImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += EmptyImage;
        AfxMessageBox(msg.c_str());
        return;
    }
}

CAirship::~CAirship()
{
}

/**
 * Draw the rotated ship. Rotation is determined by the member
 * variable mAngle, which is the rotation in radians.
 *
 * @param graphics The graphics context to draw on.
 * @param offsetX An X offset added to the position of the ship.
 * @param offsetY A Y offset added to the position of the ship.
 */
void CAirship::Draw(Gdiplus::Graphics* graphics, int offsetX, int offsetY)
{
    if (mItemImage != nullptr) {
        int wid = mItemImage->GetWidth();
        int hit = mItemImage->GetHeight();

        auto save = graphics->Save(); // Save the image if transforming

        graphics->TranslateTransform((REAL)(GetX() + offsetX),
            (REAL)(GetY() + offsetY));
        graphics->RotateTransform((REAL)(mAngle * RtoD));
        graphics->DrawImage(mItemImage.get(), -wid / 2, -hit / 2, wid, hit);

        graphics->Restore(save); // Reload the image after transforming
    }
}

/** 
 * Handle updates for animation. Overrides the CItem method
 * @param elapsed The time since last update 
 */
void CAirship::Update(double elapsed)
{
    double a = mAngle;
    double sn = sin(a);
    double cs = cos(a);

    double x = GetX() + GetXOffset() / 2 + cs * 10 * elapsed;
    double y = GetY() + GetYOffset() / 2 + sn * 10 * elapsed;

    SetLocation(x, y);
}
