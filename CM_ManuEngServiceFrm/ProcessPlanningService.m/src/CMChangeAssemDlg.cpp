

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMChangeAssemDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgCombo.h"
#include "CATDlgCombo.h"
#include "CATDlgLabel.h"
#include "CATDlgCombo.h"
#include "CATDlgPushButton.h"

// Begin of User Code

// End of User Code

CMChangeAssemDlg::CMChangeAssemDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Editor3 = NULL;
	_Label4 = NULL;
	_Label5 = NULL;
	_Combo1 = NULL;
	_Combo2 = NULL;
	_Label6 = NULL;
	_Combo3 = NULL;
	_Label7 = NULL;
	_Editor4 = NULL;
	// Begin of User Code

	// End of User Code

}

CMChangeAssemDlg::~CMChangeAssemDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Editor3 = NULL;
	_Label4 = NULL;
	_Label5 = NULL;
	_Combo1 = NULL;
	_Combo2 = NULL;
	_Label6 = NULL;
	_Combo3 = NULL;
	_Label7 = NULL;
	_Editor4 = NULL;

}



void CMChangeAssemDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0);
	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	//_Label3->SetVisibility(CATDlgHide);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", 0);
	_Label4 = new CATDlgLabel(this, (const char*)"Label4", 0);
	_Label5 = new CATDlgLabel(this, (const char*)"Label5", 0);
	_Combo1 = new CATDlgCombo(this, (const char*)"Combo1", 0 | CATDlgCmbDropDown);
	_Combo2 = new CATDlgCombo(this, (const char*)"Combo2", 0 | CATDlgCmbDropDown);
	_Label6 = new CATDlgLabel(this, (const char*)"Label6", 0);
	_Combo3 = new CATDlgCombo(this, (const char*)"Combo3", 0 | CATDlgCmbDropDown);
	_Button1 = new CATDlgPushButton(this, (const char*)"Button1", 0);
	_Button2 = new CATDlgPushButton(this, (const char*)"Button2", 0);
	_Label1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(0, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);
	_Button1->SetGridConstraints(0, 2, 8, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Label2->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor2->SetSensitivity(CATDlgDisable);
	_Editor2->SetGridConstraints(1, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);

	_Label3->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor3->SetSensitivity(CATDlgDisable);
	_Editor3->SetGridConstraints(2, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Button2->SetGridConstraints(2, 2, 8, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Label4->SetGridConstraints(3, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label5->SetGridConstraints(4, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Combo1->SetGridConstraints(3, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo1->SetVisibleTextWidth(20);
	_Combo2->SetGridConstraints(4, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo2->SetVisibleTextWidth(20);
	_Label6->SetGridConstraints(5, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Combo3->SetGridConstraints(5, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo3->SetVisibleTextWidth(20);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMChangeAssemDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_ManufacturingNameEditor:
		pEditor = _Editor1;
		break;
	case ID_RevisionEditor:
		pEditor = _Editor2;
		break;
	case ID_FatherManuAssemEditor:
		pEditor = _Editor3;
		break;
	default:
		break;
	}

	return pEditor;
}
CATDlgCombo* CMChangeAssemDlg::GetCombo(int iCtrlID)
{
	CATDlgCombo * pCombo = NULL;
	switch (iCtrlID)
	{
	case ID_PartCodeEditor:
		pCombo = _Combo1;
		break;
	case ID_ManufactureLineEditor:
		pCombo = _Combo2;
		break;
	case ID_ProcessUnitEditor:
		pCombo = _Combo3;
		break;
	default:
		break;
	}
	return pCombo;
}
// End of User Code
CATDlgPushButton* CMChangeAssemDlg::GetPushButton(int iCtrlID)
{
	CATDlgPushButton * pPushButton = NULL;
	switch (iCtrlID)
	{
	case ID_ComponentBtn:
		pPushButton = _Button1;
		break;
	case ID_FatherCompBtn:
		pPushButton = _Button2;
		break;
	default:
		break;
	}
	return pPushButton;
}

// End of implementation of class methods
