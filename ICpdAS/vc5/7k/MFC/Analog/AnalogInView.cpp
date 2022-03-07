// AnalogInView.cpp : implementation of the CAnalogInView class
//

#include "stdafx.h"
#include "AnalogIn.h"

#include "AnalogInDoc.h"
#include "AnalogInView.h"
#include "AnalogInDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalogInView

IMPLEMENT_DYNCREATE(CAnalogInView, CView)

BEGIN_MESSAGE_MAP(CAnalogInView, CView)
	//{{AFX_MSG_MAP(CAnalogInView)
	ON_COMMAND(ID_ANALOGIN, OnAnalogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalogInView construction/destruction

CAnalogInView::CAnalogInView()
{
	// TODO: add construction code here

}

CAnalogInView::~CAnalogInView()
{
}

BOOL CAnalogInView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAnalogInView drawing

void CAnalogInView::OnDraw(CDC* pDC)
{
	CAnalogInDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAnalogInView diagnostics

#ifdef _DEBUG
void CAnalogInView::AssertValid() const
{
	CView::AssertValid();
}

void CAnalogInView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnalogInDoc* CAnalogInView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnalogInDoc)));
	return (CAnalogInDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnalogInView message handlers

void CAnalogInView::OnAnalogin() 
{
	// TODO: Add your command handler code here
	CAnalogInDlg   dlg;

	dlg.m_nComPort=1;
	dlg.m_strModuleType="7011";
	dlg.m_strChecksum="Disable";
	dlg.m_nModuleAddress=1;
	dlg.m_strBaudrate="9600";
	int   ret=dlg.DoModal();
	
	TRACE("shu DoModal return = %d\n",ret);
	TRACE("shu Baudrate = %s\n",dlg.m_strBaudrate);
	TRACE("shu Checksum = %s\n",dlg.m_strChecksum);
}
