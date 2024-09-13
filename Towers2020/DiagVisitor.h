/**
 * \file DiagVisitor.h
 *
 * \author Morgan Mundell
 * \author Jacob Frank
 *
 *
 * A visitor that is tasked with visiting dialogue buttons
 *
 */

#pragma once
#include "ItemVisitor.h"

 /// A visitor specifically for dialogue buttons
class CDiagVisitor : public CItemVisitor
{
public:

	/** 
	 * Find if the Go button has been visited
	 * @returns True if found, false if not 
	 */
	bool GetFindGoButton() { return mFoundGoButton;  }

	/** 
	 * Finds a CGoButton object.
	 * @param button The CGoButton object 
	 */
	void VisitDiagGoButton(CGoButton* button) override { mFoundGoButton = true;  }

private:

	/// GoButton pressed indicator
	bool mFoundGoButton = false; 
};

