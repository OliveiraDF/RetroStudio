
// MainView.h : interface de la classe CMainView
//

#pragma once


class CMainView : public CView
{
protected: // création à partir de la sérialisation uniquement
	CMainView() noexcept;
	DECLARE_DYNCREATE(CMainView)

// Attributs
public:
	CMainDocument* GetDocument() const;

// Opérations
public:

// Substitutions
public:
	virtual void OnDraw(CDC* pDC);  // substitué pour dessiner cette vue
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implémentation
public:
	virtual ~CMainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Fonctions générées de la table des messages
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // version Debug dans MainView.cpp
inline CMainDocument* CMainView::GetDocument() const
   { return reinterpret_cast<CMainDocument*>(m_pDocument); }
#endif

