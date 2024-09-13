/**
 * \file Item.cpp
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 * \author Dimitri Snell
 * \author Rohit Vadlamudi
 * \author Brandon Addis
 */

#include "pch.h"
#include<memory>
#include "Item.h"
#include "TowersGame.h"

using namespace std;
using namespace Gdiplus;

/// The directory containing the file images
const std::wstring CItem::ImagesDirectory = L"Images/";

/** 
* Draw this item
* @param graphics The graphics context to draw on 
*/
void CItem::Draw(Gdiplus::Graphics* graphics)
{
    if (mItemImage != nullptr)
    {
        int wid = mItemImage->GetWidth();
        int hit = mItemImage->GetHeight();

        graphics->DrawImage(mItemImage.get(),
            float(GetX() - wid / 2), float(GetY() - hit / 2),
            (float)mItemImage->GetWidth() + 1, (float)mItemImage->GetHeight() + 1);
    }
}

/**  Constructor
 * @param game The game this item is a member of
 */
CItem::CItem(CTowersGame* game) : mTowersGame(game)
{
}

/// Default destructor
CItem::~CItem()
{
}

/**  
 * Test an x,y click location to see if it clicked
 * on some item in the game.
 * @param x X location
 * @param y Y location
 * @returns Pointer to item we clicked on or nullptr if none.
 */
bool CItem::HitTest(double x, double y)
{
    double insideTolerance = 32; // tolerance

    double wid = mItemImage->GetWidth(); //width
    double het = mItemImage->GetHeight(); // height 
    /// will add back later once images are added to code

    // Test to see if x, y are in the image
    if (abs(x - mX) > insideTolerance || abs(y - mY) > insideTolerance)
    {
        // We are outside the image
        return false;
    }
    
    // Test to see if x, y are in the drawn part of the image
    auto format = mItemImage->GetPixelFormat();
    if (format == PixelFormat32bppARGB || format == PixelFormat32bppPARGB)
    {
        double transX = x - GetX() + wid / 2;
        double transY = y - GetY() + het / 2;
        // This image has an alpha map, which implements the 
        // transparency. If so, we should check to see if we
        // clicked on a pixel where alpha is not zero, meaning
        // the pixel shows on the screen.
        Color color;
        mItemImage->GetPixel((int)transX, (int)transY, &color);
        return color.GetAlpha() != 0;
    } 
    else {
        return true;
    }
}

/**
 *  Get any adjacent tile. 
 *  Uses parent function in CTowersGame.
 *
 * @param dx Left/right determination, -1=left, 1=right
 * @param dy Up/Down determination, -1=up, 1=down
 * @returns Adjacent tile or nullptr if none.
 */
std::shared_ptr<CItem> CItem::GetAdjacent(int dx, int dy)
{
	return mTowersGame->GetAdjacent(this, dx, dy);
}

/**
 * Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void CItem::SetImage(const std::wstring & file)
{
    if (!file.empty())
    {
        wstring filename = ImagesDirectory + file;
        mItemImage = unique_ptr<Bitmap>(Bitmap::FromFile(filename.c_str()));
        if (mItemImage->GetLastStatus() != Ok)
        {
            wstring msg(L"Failed to open ");
            msg += filename;
            AfxMessageBox(msg.c_str());
            return;
        }
    }
    else
    {
        mItemImage.release();
    }

    mFile = file;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void CItem::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode>& node)
{
    mItemId = node->GetAttributeValue(L"id", L"");
    mX = (node->GetAttributeIntValue(L"x", 0) * 64) - 16; // Converted to virtual pixels
    mY = (node->GetAttributeIntValue(L"y", 0) * 64) + 32; // Converted to virtual pixels

    // Set the Item's image
    mFile = GetGame()->GetDeclarationAttribute(mItemId, L"image");
    SetImage(mFile);
}

/**
 *  Force the tile to a regular grid by forcing the values to be multiples of 32.
 *
 * This version works correctly for negative coordinates. 
 */
void CItem::QuantizeLocation()
{
    int spacing = CTowersGame::GridSpacing;
    if (mX < 0)
    {
        mX = ((mX + spacing / 2) / spacing) * spacing - spacing;
    }
    else
    {
        mX = ((mX + spacing / 2) / spacing) * spacing;
    }

    if (mY < 0)
    {
        mY = ((mY + spacing / 2) / spacing) * spacing - spacing;
    }
    else
    {
        mY = ((mY + spacing / 2) / spacing) * spacing;
    }
}

/** 
 * Gets a specific attribute from an item value. Upcall to the implementation located in CTowersGame.
 * @returns The value of the attribute at the speicifc item value. Null if none.
 * @param id The itemID as declared in the XML Declarations section
 * @param attribute The attribute that needs to be looked up 
 */
std::wstring CItem::GetDeclarationAttribute(const std::wstring id, const std::wstring& attribute)
{
    return GetGame()->GetDeclarationAttribute(id, attribute);
}

/**
 * Gets the distane between one item and another
 * @param other The other item
 * \return The distance
 */
double CItem::Distance(std::shared_ptr<CItem> other)
{
  double dx = mX - other->mX;
  double dy = mY - other->mY;

  return sqrt(dx * dx + dy * dy);
}