/**
 * \file Balloon.h
 *
 * \author Rohit Vadlamudi
 * \author
 *
 *  Class that implements a balloon
 */

#pragma once
#include "Entity.h"

 /**
  *  Implements a simple balloon with tiles we can manipulate
  */
class CBalloon : public CEntity
{
public:

	CBalloon(CTowersGame* game);

	/// Default constructor (disabled)
	CBalloon() = delete;

	virtual ~CBalloon();

	/// Copy Constructor Disabled
	CBalloon(const CBalloon&) = delete;

	/** 
	 * Accept a visitor
     * @param visitor The visitor we accept 
	 */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitBalloon(this); }

	/** 
	 * Used for getting the scalar T
	 * \return A double scalar 
	 */
	double GetT() const { return mT; }

	/** 
	 * Used for setting the scalar T
	 * @param t A double scalar 
	 */
	void SetT(double t) { mT = t; }

	/** Used to indicate if balloon is reverse
	 * \return mReverse
	 */
	bool IsReverse() { return mReverse; }

	/// Indicate the balloon is going forwards
	void Forwards() { mReverse = false; }

	/// Indicate the balloon is going backwards
	void Backwards() { mReverse = true; }

	/**
	 * Indicates if the balloon is popped.
	 * @returns If the balloon has been popped by a tower
	 */
	bool IsBeingDeleted() { return mIsPopped;  }

	/**
	* Set the pop status of the balloon. Does not delete the balloon.
	* @param popped True if the balloon is already popped (queued for deletion)
	*/
	void SetIsDeleted(bool popped) { mIsPopped = popped;  }

	/**
	 * Sets when the balloon has been transferred / processed
	 * @param hasTransferred True if not processed, false if the balloon has been.
	 */
	void SetHasTransferred(bool hasTransferred) { mHasTransferred = hasTransferred; }

	/**
	 * Indicates if the balloon has been transferred / processed
	 * @returns True if not processed, false if the balloon has been.
	 */
	bool HasTransferred() { return mHasTransferred; }

	/**
	 * Sets when the balloon has been hit
	 * @param rendering False if balloon has been hit
	 */
	void SetRendering(bool rendering) { mRendered = rendering; }

	/**
	 * Indicates if the balloon should be rendered
	 * @returns True if balloon should be rendered
	 */
	bool GetRendering() { return mRendered; }

	virtual void Update(double elapsed) override;
	
	void Draw(Gdiplus::Graphics* graphics, int offsetX, int offsetY);

	/**
	 * Method Disabled (no entities are drawn on/in balloon entities)
	 * @param graphics The graphics 
	 */
	virtual void RenderEntities(Gdiplus::Graphics* graphics) {};

private:

	/// Image of Item
	std::shared_ptr<Gdiplus::Bitmap> mItemImage;

	/// The scalar T used for keeping track of the position of a balloon on a road tile
	double mT = 0.00;

	/// Indicates if the balloon has moved from one tile to another
	bool mHasTransferred = false;

	/// True if a balloon must path in the opposite direction. Ex: WN on a Northwest tile
	bool mReverse = false;

	/// The file for this item
	std::wstring mFile;

	/// Is the Ballon popped or not
	bool mIsPopped = false;  

	/// Used for color transformation of defualt balloon image
	Gdiplus::ColorMatrix mColorMatrix;

	/// Used for setting the colors of different balloon images
	Gdiplus::ImageAttributes mImageAttributes;

	/// Used to determine if a balloon should render
	bool mRendered = true;

};

