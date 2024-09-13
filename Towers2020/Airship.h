/**
 * \file Airship.h
 *
 * \author Morgan Mundell
 * \author
 *
 *  Class that implements a ship
 */

#pragma once
#include "Entity.h"

 /**
  *  Implements a simple ship with tiles we can manipulate
  */
class CAirship : public CEntity
{
public:

	CAirship(CTowersGame* game);

	/// Default constructor (disabled)
	CAirship() = delete;

	virtual ~CAirship();

	/// Copy Constructor Disabled
	CAirship(const CAirship&) = delete;


	void Draw(Gdiplus::Graphics* graphics, int offsetX, int offsetY);


	virtual void Update(double elapsed) override;

	/** 
	 * Acccepts a CItemVisitor
	 * @param visitor The visitor being accepted 
	 */
	virtual void Accept(CItemVisitor* visitor) override { }

	/**
	 * Method Disabled (no entities are drawn on/in balloon entities)
	 * @param graphics The graphics 
	 */
	virtual void RenderEntities(Gdiplus::Graphics* graphics) {};

	/** 
	 * Sets the angular offset to determine rotation of dart
	 * @param newAngle The new angular offset 
	 */
	void SetAngle(double newAngle) { mAngle = newAngle; }

private:
	/// The image of this ship
	std::unique_ptr<Gdiplus::Bitmap> mItemImage; 

	/// The angle of this dart
	double mAngle = 0; 

};
