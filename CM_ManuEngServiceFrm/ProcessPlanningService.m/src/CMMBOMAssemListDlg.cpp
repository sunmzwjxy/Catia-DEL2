

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMMBOMAssemListDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgSelectorList.h"

// Begin of User Code

// End of User Code

CMMBOMAssemListDlg::CMMBOMAssemListDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_SelectorList1 = NULL;

	// Begin of User Code

	// End of User Code

}

CMMBOMAssemListDlg::~CMMBOMAssemListDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_SelectorList1 = NULL;

}



void CMMBOMAssemListDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_SelectorList1 = new CATDlgSelectorList(this, (const char*)"SelectorList1", 0);
	_Label1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_SelectorList1->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP | CATGRID_BOTTOM);
	_SelectorList1->SetVisibleTextWidth(30);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgSelectorList* CMMBOMAssemListDlg::GetSelectorList(int iCtrlID)
{
	CATDlgSelectorList* pSelectorList = NULL;

	switch (iCtrlID)
	{
	case ID_ComponentNumberList:
		pSelectorList = _SelectorList1;
		break;
	default:
		break;
	}

	return pSelectorList;
}
// End of User Code


// End of implementation of class methods
