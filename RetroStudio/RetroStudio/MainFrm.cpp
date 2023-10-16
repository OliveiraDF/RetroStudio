
// MainFrm.cpp : implémentation de la classe CMainFrame
//

#include "pch.h"
#include "framework.h"
#include "RetroStudio.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_CONSOLE, &CMainFrame::OnViewConsole)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CONSOLE, &CMainFrame::OnUpdateViewConsole)
END_MESSAGE_MAP()

static UINT INDICATORS[] =
{
	ID_SEPARATOR,           // indicateur de la ligne d'état
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// construction/destruction de CMainFrame

CMainFrame::CMainFrame() noexcept
{
	// TODO: ajoutez ici le code d'une initialisation de membre
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	if (!m_wndMenuBar.Create(this))
	{
		return -1; 
	}

	m_wndMenuBar.SetPaneStyle(m_wndMenuBar.GetPaneStyle() | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS | CBRS_FLYBY);

	CMFCPopupMenu::SetForceMenuFocus(FALSE);

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(theApp.m_bHiColorIcons ? IDR_MAINFRAME_256 : IDR_MAINFRAME))
	{
		return -1;    
	}

	if (!m_wndStatusBar.Create(this))
	{
		return -1;     
	}
	m_wndStatusBar.SetIndicators(INDICATORS, ARRAYSIZE(INDICATORS));

	if (!m_wndLogPane.Create(_T("Console"), this, { 0, 0, 200, 200 }, TRUE, ID_VIEW_CONSOLE,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		return -1;
	}

	retro::core::RegisterLogObserver(&m_wndLogPane);

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndLogPane.EnableDocking(CBRS_ALIGN_BOTTOM | CBRS_ALIGN_TOP);
	EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndMenuBar);
	DockPane(&m_wndToolBar);
	DockPane(&m_wndLogPane);

	// activer le comportement de la fenêtre d'ancrage de style Visual Studio 2005
	CDockingManager::SetDockingMode(DT_SMART);
	// activer le comportement de masquage automatique de la fenêtre d'ancrage de style Visual Studio 2005
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// définir le gestionnaire visuel utilisé pour dessiner tous les éléments d'interface utilisateur
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
	CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
	RetroVisualManager::SetWindowDarkAttribute(this);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWndEx::PreCreateWindow(cs))
	{
		return FALSE;
	}

	return TRUE;
}

// diagnostics de CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG

BOOL CMainFrame::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle, CWnd* pParentWnd, CCreateContext* pContext)
{
	if (!CFrameWndEx::LoadFrame(nIDResource, dwDefaultStyle, pParentWnd, pContext))
	{
		return FALSE;
	}

	return TRUE;
}

void CMainFrame::OnViewConsole()
{
	ShowPane(&m_wndLogPane, !(m_wndLogPane.IsVisible()), FALSE, TRUE);
	RecalcLayout();
}

void CMainFrame::OnUpdateViewConsole(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndLogPane.IsVisible());
}
