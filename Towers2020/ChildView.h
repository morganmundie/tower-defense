/**
* \file ChildView.h
*
* \author Morgan Mundell
* \author Jacob Frank
* \author Brandon Addis
* \author Dimitri Snell
* \author Rohit Vadlamundi
*
*  Class that implements the child window our program draws in.
*
* The window is a child of the main frame, which holds this
* window, the menu bar, and the status bar.
*/


#pragma once
#include "TowersGame.h"

/// CChildView window
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	/**
	 * This function is called to paint the window
	 */
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:

	/**
	 * @brief Adds all CItems necessary for the palette
	*/
	void OnAddAll();

	/// The towers game
	CTowersGame mTowers; 

	/// True until our first draw
	bool mFirstDraw = true;	

	/// True until our first click for the go button
	bool mFirstClick = true; 

	/// Last time we read the timer
	long long mLastTime = 0; 

	/// Rate the timer updates
	double mTimeFreq = 0; 

	/// Any item we are currently dragging
	std::shared_ptr<CItem> mGrabbedItem; 

	/// The max time between frames
	double MaxElapsed = 0.025; 

public:
	
	afx_msg void OnLevelLevel0();

	afx_msg void OnLevelLevel1();

	afx_msg void OnLevelLevel2();
	
	afx_msg void OnLevelLevel3();

	afx_msg void OnFileOpen();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	afx_msg void OnAddTowerRings();

	afx_msg void OnAddTowerBomb();

	afx_msg void OnAddTower8();

	afx_msg void OnAddTowerAirship();

	afx_msg void OnAddGoButton();

	afx_msg void OnAddDiagTimer(int num);
	
	/** Explains TowerRings */
	afx_msg void OnHowtousetowerRingtower();

	/** Explains TowerBomb */
	afx_msg void OnHowtousetowerBombtower();

	/** Explains TowerAirship */
	afx_msg void OnHowtousetowerAirshiptower();

	/** Explains the game */
	afx_msg void OnHowtoHowtoplay32782();

	/** Explains Tower8 */
	afx_msg void OnHowtousetowerTower9();
};

