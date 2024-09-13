/**
* \file ChildView.cpp
*
* \author Morgan Mundell
* \author Jacob Frank
* \author Brandon Addis
* \author Dimitri Snell
* \author Rohit Vadlamundi
*
*/




// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include<cmath>
#include <sstream>
#include <afxwin.h>
#include "framework.h"
#include "Towers2020.h"
#include "TowersGame.h"
#include "ChildView.h"
#include "DoubleBufferDC.h"
#include "TowerRings.h"
#include "TowerBomb.h"
#include "Tower8.h"
#include "GoButton.h"
#include "CanMoveVisitor.h"
#include "DiagVisitor.h"
#include "DiagTimer.h"
#include "TowerAirship.h"
#include <mmsystem.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;
using namespace std;

/// Frame duration in ms (set to 30 for animation)
const int FrameDuration = 30;

/// X Location for every item on the Pallette apart from Diag Timer
const static double XLocation = 1150;

/// X Location for the Diag Timer on the Pallette
const static double XLocationDiagTimer = 1110;

/// Y Location for the Ring Tower on the Pallete
const static double YLocationTowerRings = 80;

/// Y Location for the Bomb Tower on the Pallette
const static double YLocationTowerBomb = 280;

/// Y Location for the Tower 8 on the Pallette
const static double YLocationTower8 = 180;

/// Y Location for the Airship Tower on the Pallette
const static double YLocationTowerAirship = 380;

/// Y Location for the Go Button on the Pallette
const static double YLocationGoButton = 923;

/// Y Location for the Diag Timer on the Pallette
const static double YLocationDiagTimer = 923;


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
	ON_COMMAND(ID_FILE_OPEN32775, &CChildView::OnFileOpen)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADDTOWER_ADDRINGTOWER, &CChildView::OnAddTowerRings)
	ON_COMMAND(ID_ADDTOWER_ADDBOMBTOWER, &CChildView::OnAddTowerBomb)
	ON_COMMAND(ID_ADDTOWER_ADDTOWER8, &CChildView::OnAddTower8)
	
	
	
	ON_COMMAND(ID_HOWTOUSETOWER_RINGTOWER, &CChildView::OnHowtousetowerRingtower)
	ON_COMMAND(ID_HOWTOUSETOWER_BOMBTOWER, &CChildView::OnHowtousetowerBombtower)
	ON_COMMAND(ID_HOWTOUSETOWER_AIRSHIPTOWER, &CChildView::OnHowtousetowerAirshiptower)
	ON_COMMAND(ID_HOWTO_HOWTOPLAY32782, &CChildView::OnHowtoHowtoplay32782)
	ON_COMMAND(ID_HOWTOUSETOWER_TOWER9, &CChildView::OnHowtousetowerTower9)
END_MESSAGE_MAP()

// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC paintDC(this); // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting

	Graphics graphics(dc.m_hDC);    // Create GDI+ graphics context
	graphics.Clear(Color(0, 0, 0));

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		OnLevelLevel1();

		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mLastTime = time.QuadPart;

	//
	// Prevent tunnelling
	//
	while (elapsed > MaxElapsed)
	{
		mTowers.Update(MaxElapsed);

		elapsed -= MaxElapsed;
	}

	// Consume any remaining time
	if (elapsed > 0)
	{
		mTowers.Update(elapsed);
	}

	CRect rect;
	GetClientRect(&rect);
	
	mTowers.OnDraw(&graphics, rect.Width(), rect.Height());

	if (mTowers.GetNewLevelItems())
	{
		// Update the entire object panel

		OnAddAll(); 

		// Arcade like sound
		PlaySound(L"AudioFile/DST-TowerDefenseTheme.wav", NULL, SND_FILENAME | SND_ASYNC);

		mTowers.SetNewLevelItems(false);
	}
}

void CChildView::OnAddAll()
{
	OnAddTower8();
	OnAddTowerBomb();
	OnAddTowerBomb();
	OnAddTowerRings();
	OnAddTowerAirship();
}

/*
Once xml loading is implemented and level 
files are created they will be loaded in these event handlers
*/

/** Load a tilesheet from "level0.xml" 
 */
void CChildView::OnLevelLevel0()
{
	mTowers.Load(L"levels/level0.xml");
}

/** Load a tilesheet from "level1.xml" 
 */
void CChildView::OnLevelLevel1()
{
	mTowers.Load(L"levels/level1.xml");
}

/** Load a tilesheet from "level2.xml" 
 */
void CChildView::OnLevelLevel2()
{
	mTowers.Load(L"levels/level2.xml");
}

/** Load a tilesheet from "level3.xml" 
 */
void CChildView::OnLevelLevel3()
{
	mTowers.Load(L"levels/level3.xml");
}

/** This is called when "Open File" is selected. Allows user to pick a file. 
 */
void CChildView::OnFileOpen()
{
	CFileDialog dlg(true,  // true = Open dialog box
		L".xml",           // Default file extension
		nullptr,            // Default file name (none)
		0,    // Flags
		L"Level Files (*.xml)|*.xml|All Files (*.*)|*.*||");    // Filter
	if (dlg.DoModal() != IDOK)
		return;

	wstring filename = dlg.GetPathName();
	mTowers.Load(filename);
	Invalidate();

}

/**
 * Called when there is a left mouse button press
 * @param nFlags Flags associated with the mouse button press
 * @param point Where the button was pressed
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	double oX = (point.x - mTowers.GetmXOffset()) / mTowers.GetmScale();
	double oY = (point.y - mTowers.GetmYOffset()) / mTowers.GetmScale();
	mGrabbedItem = mTowers.HitTest(oX, oY);

	if (mGrabbedItem != nullptr)
	{
		CDiagVisitor gobuttonvisitor;
		mGrabbedItem->Accept(&gobuttonvisitor);

		if (mTowers.GetLevelLabelStatus())
		{
			mGrabbedItem = nullptr;
		}
		else if (gobuttonvisitor.GetFindGoButton() && !mTowers.GetGoButtonPressed())
		{
			mTowers.PressGoButton(mGrabbedItem);
			mGrabbedItem = nullptr;
		}
		else if (mTowers.GetGoButtonPressed())
		{
			mGrabbedItem = nullptr;
		}
		else
		{
			// Accept a visitor to identify what type of object we have
			CCanMoveVisitor visitor;
			
			mGrabbedItem->Accept(&visitor);

			// Only move if item is tower
			if (visitor.GetIsTower() && visitor.GetIsOpen())
			{
				// Detects if click on panel obj. Hard coded X intercept to represent boundary of panel
				if (oX >= 1024)
				{
					// If the visitor finds that we clicked out of bounds on a tower, it must be
					// a pallete object. We need to replace this palette object with another
					switch (visitor.GetKey())
					{
					case 1: // Key 1 = Tower8
						OnAddTower8();
						break;
					case 2: // Key 2 = TowerBomb
						OnAddTowerBomb();
						break;
					case 3: // Key 3 = TowerRings
						OnAddTowerRings();
						break;
					case 4: // Key 4 = TowerAirship
						OnAddTowerAirship();
						break;
					}
				}

				visitor.LiftTower(); // Lifts the tower to disable attacks
				mTowers.MoveToFront(mGrabbedItem);
				//mTowers.SetDrawMoreItems(true);
			}
			else
			{
				mGrabbedItem = nullptr;
			}

		}

	}
}

/**
 * Called when the left mouse button is released
 * @param nFlags Flags associated with the mouse button release
 * @param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (mGrabbedItem != nullptr)
	{
		double oX = (point.x - mTowers.GetmXOffset()) / mTowers.GetmScale();
		double oY = (point.y - mTowers.GetmYOffset()) / mTowers.GetmScale();

		// The Temporary item representing the object under the cursor (not being dragged)
		std::shared_ptr<CItem> tempItem;
		mGrabbedItem->SetLocation(0, 0);
		tempItem = mTowers.HitTest(oX, oY);

		CCanMoveVisitor visitor, visitorTower; // create new visitor to check if tower

		if (tempItem != nullptr) 
		{
			tempItem->Accept(&visitor);
			mGrabbedItem->Accept(&visitorTower);

			// visitor checks if the place under the dropped location is a tower
			
			if (visitor.GetIsTower())
			{

				// Checks if inside palette. Someone placed a sample turret on another one
				if (oX > 1024)
				{
					// Just delete the dragged tower. Do not replace a palette object
					mTowers.DeleteItem(mGrabbedItem); 
				}
				else
				{
					mTowers.DeleteItem(tempItem); // delete the existing tower
					mGrabbedItem->SetLocation(tempItem->GetX(), tempItem->GetY()); // add the new tower on top of it
					visitorTower.PlaceTower(); // Lifts the tower to enable attacks
				}
				
			}
			else if (visitor.GetIsOpen())
			{
				mGrabbedItem->SetLocation(tempItem->GetX(), tempItem->GetY()); // place the tower on open ground
				visitorTower.PlaceTower(); // Lifts the tower to enable attacks
			}
			else
			{
				mTowers.DeleteItem(mGrabbedItem);
			}
		} 
		else 
		{
			mTowers.DeleteItem(mGrabbedItem);
		}

		// Update the grabbed item
		OnMouseMove(nFlags, point);
	}
}

/**
 * Called when the mouse is moved
 * @param nFlags Flags associated with the mouse movement
 * @param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		double oX = (point.x - mTowers.GetmXOffset()) / mTowers.GetmScale();
		double oY = (point.y - mTowers.GetmYOffset()) / mTowers.GetmScale();
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{

			mGrabbedItem->SetLocation(oX, oY);
		}
		else
		{
			//mGrabbedItem->QuantizeLocation();

			// When the left button is released, we release the
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}

/**
 * Upcall for the OnTimer function in CWnd
 * @param nIDEvent Object passed into CWnd's parent function 
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CWnd::OnTimer(nIDEvent);
}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * @param pDC Device context
 * @returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

/** Adds a new Ring tower to the palette  
 */
void CChildView::OnAddTowerRings()
{
	auto ring = make_shared<CTowerRings>(&mTowers);
	ring->SetLocation(XLocation, YLocationTowerRings);
	mTowers.Add(ring);
	Invalidate();
}

/** Adds a new Bomb tower to the palette 
 */
void CChildView::OnAddTowerBomb()
{
	auto bomb = make_shared<CTowerBomb>(&mTowers);
	bomb->SetLocation(XLocation, YLocationTowerBomb);
	mTowers.Add(bomb);
	Invalidate();
}

/** Adds a new 8 tower to the palette 
 */
void CChildView::OnAddTower8()
{
	auto tower8 = make_shared<CTower8>(&mTowers);
	tower8->SetLocation(XLocation, YLocationTower8);
	mTowers.Add(tower8);
	Invalidate();
}

/** Adds a new Airship Tower to the palette 
 */
void CChildView::OnAddTowerAirship()
{
	auto airship = make_shared<CTowerAirship>(&mTowers);
	airship->SetLocation(XLocation, YLocationTowerAirship);
	mTowers.Add(airship);
	Invalidate();
}

/** Adds a new Go Button dialogue to the palette 
 */
void CChildView::OnAddGoButton()
{
	auto button = make_shared<CGoButton>(&mTowers);
	button->SetLocation(XLocation, YLocationGoButton);
	mTowers.Add(button);
	Invalidate();
}

/** Adds a new Timer dialogue to the palette
 * @param num The level number
 */
void CChildView::OnAddDiagTimer(int num)
{
	auto button = make_shared<CDiagTimer>(&mTowers);
	button->SetLocation(XLocationDiagTimer, YLocationDiagTimer);
	mTowers.Add(button);
	button->SetLevelNumber(num);
	Invalidate();
}

void CChildView::OnHowtousetowerRingtower()
{
	MessageBox(L"Ring Tower is the red tower in the pallette.\n" L"It creates a ring that fires every 5 seconds.", L"Ring Tower", MB_ICONINFORMATION);
}


void CChildView::OnHowtousetowerBombtower()
{
	MessageBox(L"Bomb Tower is the red bomb in the pallette.\n" L"A bomb will explode after 3 seconds.", L"Bomb Tower", MB_ICONINFORMATION);
}


void CChildView::OnHowtousetowerAirshiptower()
{
	MessageBox(L"Airship Tower is the blue tower in the pallette.\n" L"It creates sends out an airship every ten seconds.\n"
		L"Airships will shoot 8 darts after traveling.", L"Airship Tower", MB_ICONINFORMATION);
}


void CChildView::OnHowtoHowtoplay32782()
{
	MessageBox(L"Drag towers from the pallete to the game.\n" L"These towers will destroy balloons in unique ways.\n"
		L"Hit the go button to run a level.", L"How To Play", MB_ICONINFORMATION);
}


void CChildView::OnHowtousetowerTower9()
{
	MessageBox(L"Tower8 is the green tower in the pallette.\n" L"It creates 8 darts that shoot every 5 seconds.", L"Tower8", MB_ICONINFORMATION);
}
