// AnalogInView.h : interface of the CAnalogInView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALOGINVIEW_H__BA389F9D_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
#define AFX_ANALOGINVIEW_H__BA389F9D_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CAnalogInView : public CView
{
protected: // create from serialization only
	CAnalogInView();
	DECLARE_DYNCREATE(CAnalogInView)

// Attributes
public:
	CAnalogInDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalogInView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnalogInView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnalogInView)
	afx_msg void OnAnalogin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in AnalogInView.cpp
inline CAnalogInDoc* CAnalogInView::GetDocument()
   { return (CAnalogInDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOGINVIEW_H__BA389F9D_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
