

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMMBOMReportDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"

// Begin of User Code

// End of User Code

CMMBOMReportDlg::CMMBOMReportDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_Editor1 = NULL;

	// Begin of User Code

	// End of User Code

}

CMMBOMReportDlg::~CMMBOMReportDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Editor1 = NULL;

}



void CMMBOMReportDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Label1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(0, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMMBOMReportDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_SelectMAEditor:
		pEditor = _Editor1;
		break;
	default:
		break;
	}

	return pEditor;
}
// End of User Code


// End of implementation of class methods
