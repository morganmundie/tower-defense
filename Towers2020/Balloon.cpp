/**
 * \file Balloon.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include "Balloon.h"

using namespace std;
using namespace Gdiplus;

/// Default image
const wstring EmptyImage = L"red-balloon.png";


/**
 * Constructor. Sets the balloon image.
 * @param item The game we are in 
 */
CBalloon::CBalloon(CTowersGame* item) : CEntity(item)
{
    // Set an image
    wstring filename = ImagesDirectory + EmptyImage;
    mItemImage = std::unique_ptr<Gdiplus::Bitmap>(Gdiplus::Bitmap::FromFile(filename.c_str()));
    Status sh = mItemImage->GetLastStatus();
    if (mItemImage->GetLastStatus() != Ok)
    {
        wstring msg(L"Failed to open ");
        msg += EmptyImage;
        AfxMessageBox(msg.c_str());
        return;
    }

    // Set a random color for the image

    // Random seed
    srand(time(NULL));

    for (size_t i = 0; i < 5; i++) 
    {
        for (size_t u = 0; u < 5; u++)
        {
            if (i == 4 && u == 4 || i == 3 && u == 3)
            {
                mColorMatrix.m[i][u] = 1;
            } 
            else if (i == u)
            {
                mColorMatrix.m[i][u] = (float)rand() / RAND_MAX;
            } 
            else
            {
                mColorMatrix.m[i][u] = 0.0f;
            }
        }
    }

    float primaryColor = (float)rand() / RAND_MAX;

    if (primaryColor < 0.33)
    {
        mColorMatrix.m[0][0] = 1; // Primarily-red balloon.
    }
    else if (primaryColor < 0.66)
    {
        mColorMatrix.m[1][1] = 1; // Primarily-green balloon.
    }
    else
    {
        mColorMatrix.m[2][2] = 1; // Primarily-blue balloon.
    }
}

/**
 * Draw a balloon according to an X and Y offset (to match with a coresponding tile)
 * @param graphics The graphics object
 * @param offsetX The X offset
 * @param offsetY The Y offset
 */
void CBalloon::Draw(Gdiplus::Graphics* graphics, int offsetX, int offsetY)
{
    int wid = mItemImage->GetWidth();
    int hit = mItemImage->GetHeight();

    mImageAttributes.SetColorMatrix(
        &mColorMatrix, 
        ColorMatrixFlagsDefault,
        ColorAdjustTypeBitmap);

    if (mItemImage != nullptr) 
    {
        graphics->DrawImage(
            mItemImage.get(), 
            Rect(GetX() + offsetX, GetY() + offsetY, wid, hit),
            0, 0, wid, hit, UnitPixel, &mImageAttributes);
    }
}

/// Default destructor
CBalloon::~CBalloon()
{
}

/** 
 * Handle updates for animation. Overrides the CItem method
 * @param elapsed The time since last update 
 */
void CBalloon::Update(double elapsed)
{
    mT += 2 * elapsed; // change back to 2.0 pls
}
