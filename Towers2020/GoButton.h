/**
 * \file GoButton.h
 *	
 *	\author Jacob Frank
 * 
 * This class contains the go button
 */

#pragma once
#include "Dialogue.h"

/// GoButton represents the green play button
class CGoButton : public CDialogue
{
public:

	CGoButton(CTowersGame* game);

	/// Default constructor (disabled)
	CGoButton() = delete;

	///  Copy constructor (disabled)
	CGoButton(const CGoButton&) = delete;

	~CGoButton();

	/** 
	 * Accept a visitor
	 * @param visitor The visitor we accept 
	 */
	virtual void Accept(CItemVisitor* visitor) override { visitor->VisitDiagGoButton(this); }

	/** 
	 * Method Disabled (no entities are drawn on ship entities)
	 * @param graphics The graphics 
	 */
	virtual void RenderEntities(Gdiplus::Graphics* graphics) {};

	virtual bool HitTest(double x, double y) override;
};
