/**
 * \file Dart.h
 *
 * \author Rohit Vadlamudi
 * \author
 *
 *  Class that implements a dart
 */

#pragma once
#include "Entity.h"

 /**
  *  Implements a simple dart with tiles we can manipulate
  */
class CDart : public CEntity
{
public:

	CDart(CTowersGame* game);

	/// Default constructor (disabled)
	CDart() = delete;


	virtual ~CDart();

	/// Copy Constructor Disabled
	CDart(const CDart&) = delete;

	void Draw(Gdiplus::Graphics* graphics, int offsetX, int offsetY);

	virtual void Update(double elapsed) override;

	/** Acccepts a CItemVisitor
	 * @param visitor The visitor being accepted 
	 */
	virtual void Accept(CItemVisitor* visitor) override { }

	/** Sets the angular offset to determine rotation of dart
	 * @param newAngle The new angular offset 
	 */
	void SetAngle(double newAngle) { mAngle = newAngle; }

	/** Gets the angular offset which determine rotation of dart
	 * @returns The angular offset 
	 */
	double GetAngle() { return mAngle; }

	/** Method Disabled (no entities are drawn on ship entities)
	 * @param graphics The graphics 
	 */
	virtual void RenderEntities(Gdiplus::Graphics* graphics) {};

private:

	/// The image of this dart
	std::unique_ptr<Gdiplus::Bitmap> mItemImage;

	/// The angle of this dart
	double mAngle = 0;

};

