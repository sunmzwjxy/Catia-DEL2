

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMChangeMakePartDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"

// Begin of User Code

// End of User Code

CMChangeMakePartDlg::CMChangeMakePartDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Editor1 = NULL;

	// Begin of User Code

	// End of User Code

}

CMChangeMakePartDlg::~CMChangeMakePartDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Editor1 = NULL;

}



void CMChangeMakePartDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Label1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label2->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label3->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor2->SetSensitivity(CATDlgDisable);
	_Editor2->SetGridConstraints(1, 1, 3, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);
	_Editor3->SetSensitivity(CATDlgDisable);
	_Editor3->SetGridConstraints(2, 1, 3, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(0, 1, 3, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMChangeMakePartDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_SelectManufacturingPartEditor:
		pEditor = _Editor1;
		break;
	case ID_ManufacturingAssemblyEditor:
		pEditor = _Editor2;
		break;
	case ID_DesignPartEditor:
		pEditor = _Editor3;
		break;
	default:
		break;
	}

	return pEditor;
}
// End of User Code


// End of implementation of class methods
