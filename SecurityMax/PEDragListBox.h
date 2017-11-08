#pragma once
#include <afxwin.h>


// PEDragListBox

class PEDragListBox : public CListBox
{
	DECLARE_DYNAMIC(PEDragListBox)

public:
	PEDragListBox();
	virtual ~PEDragListBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
};


