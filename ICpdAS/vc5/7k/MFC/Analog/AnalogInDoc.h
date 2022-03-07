// AnalogInDoc.h : interface of the CAnalogInDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALOGINDOC_H__BA389F9B_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
#define AFX_ANALOGINDOC_H__BA389F9B_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


class CAnalogInDoc : public CDocument
{
protected: // create from serialization only
	CAnalogInDoc();
	DECLARE_DYNCREATE(CAnalogInDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnalogInDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAnalogInDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CAnalogInDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANALOGINDOC_H__BA389F9B_6B2D_11D3_BAE8_0080AD91800F__INCLUDED_)
