// AnalogInDoc.cpp : implementation of the CAnalogInDoc class
//

#include "stdafx.h"
#include "AnalogIn.h"

#include "AnalogInDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnalogInDoc

IMPLEMENT_DYNCREATE(CAnalogInDoc, CDocument)

BEGIN_MESSAGE_MAP(CAnalogInDoc, CDocument)
	//{{AFX_MSG_MAP(CAnalogInDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnalogInDoc construction/destruction

CAnalogInDoc::CAnalogInDoc()
{
	// TODO: add one-time construction code here

}

CAnalogInDoc::~CAnalogInDoc()
{
}

BOOL CAnalogInDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAnalogInDoc serialization

void CAnalogInDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CAnalogInDoc diagnostics

#ifdef _DEBUG
void CAnalogInDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAnalogInDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnalogInDoc commands
