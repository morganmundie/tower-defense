/**
 * \file Entity.h
 *
 * \author Jacob Frank
 * 
 * Class that describes entities, a.k.a. short lived items.
 * A type of CItem that specifically expects to be deleted in
 * a short amount of time.
 */

#pragma once
#include "Item.h"

 /**
  *  Implements a simple entity with tiles we can manipulate
  */
class CEntity : public CItem
{
protected:

	CEntity(CTowersGame* game);

public:

	/// Default constructor (disabled)
	CEntity() = delete;

	virtual ~CEntity();

	/// Copy Constructor Disabled
	CEntity(const CEntity&) = delete;

	void SetSpeed(double minX, double maxX);

	/** 
	 * Sets the X offset to determine location of the object
	 * @param newOffsetX The new X offset 
	 */
	void setXOffset(double newOffsetX) { mXOffset = newOffsetX; }

	/** 
	 *  Sets the Y offset to determine location of the object
	 * @param newOffsetY The new Y offset 
	 */
	void setYOffset(double newOffsetY) { mYOffset = newOffsetY; }

	/** Gets the X offset which determines location of the object
	 * @returns The X offset 
	 */
	double GetXOffset() { return mXOffset; }

	/** Gets the Y offset which determines location of the object
	 * @returns The Y offset 
	 */
	double GetYOffset() { return mYOffset; }

	/** Accepts the visitor
	 * @param visitor The visitor
	 */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitEntity(this); }

private:
	/// Entity speed in the X direction
	double mSpeedX = 0.0;

	/// The X offset of this object
	double mXOffset = 0; 

	/// The Y offset of this object
	double mYOffset = 0;

	/// Entity X location
	int mX = GetX();

	/// Entity Y location
	int mY = GetY();
};

