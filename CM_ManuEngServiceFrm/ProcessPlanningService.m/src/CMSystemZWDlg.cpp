

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMSystemZWDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgCombo.h"

// Begin of User Code

// End of User Code

CMSystemZWDlg::CMSystemZWDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Label4 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Editor4 = NULL;
	_Label5 = NULL;
	_Editor5 = NULL;
	_Label6 = NULL;
	_Combo1 = NULL;
	_Label7 = NULL;
	_Editor7 = NULL;

	// Begin of User Code

	// End of User Code

}

CMSystemZWDlg::~CMSystemZWDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Label4 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Editor4 = NULL;
	_Label5 = NULL;
	_Editor5 = NULL;
	_Label6 = NULL;
	_Combo1 = NULL;
	_Label7 = NULL;
	_Editor7 = NULL;
}



void CMSystemZWDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	_Label4 = new CATDlgLabel(this, (const char*)"Label4", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", 0);
	_Editor4 = new CATDlgEditor(this, (const char*)"Editor4", 0);
	_Label5 = new CATDlgLabel(this, (const char*)"Label5", 0);
	_Editor5 = new CATDlgEditor(this, (const char*)"Editor5", 0);
	_Label6 = new CATDlgLabel(this, (const char*)"Label6", 0);
	_Combo1 = new CATDlgCombo(this, (const char*)"Combo1", 0 | CATDlgCmbDropDown);
	_Label7 = new CATDlgLabel(this, (const char*)"Label7", 0);
	_Editor7 = new CATDlgEditor(this, (const char*)"Editor7", 0);
	_Label1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label2->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label3->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(0, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);
	_Editor2->SetSensitivity(CATDlgDisable);
	_Editor2->SetGridConstraints(1, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);
	_Editor3->SetSensitivity(CATDlgDisable);
	_Editor3->SetGridConstraints(2, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Label4->SetGridConstraints(3, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Combo1->SetGridConstraints(3, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo1->SetVisibleTextWidth(20);
	_Label5->SetGridConstraints(4, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor4->SetGridConstraints(4, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor4->SetVisibleTextWidth(20);
	_Label6->SetGridConstraints(5, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor5->SetGridConstraints(5, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor5->SetVisibleTextWidth(20);
	_Label7->SetGridConstraints(6, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor7->SetGridConstraints(6, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor7->SetVisibleTextWidth(20);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMSystemZWDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_SelectMIDCompEditor:
		pEditor = _Editor1;
		break;
	case ID_SelectZWPreviousEditor:
		pEditor = _Editor2;
		break;
	case ID_SelectZWFatherEditor:
		pEditor = _Editor3;
		break;
	case ID_InputZWCodeEditor:
		pEditor = _Editor4;
		break;
	case ID_InputZWNameEditor:
		pEditor = _Editor5;
		break;
	case ID_InputEffEditor:
		pEditor = _Editor7;
		break;
	default:
		break;
	}

	return pEditor;
}

CATDlgCombo* CMSystemZWDlg::GetCombo(int iCtrlID)
{
	CATDlgCombo * pCombo = NULL;
	switch (iCtrlID)
	{
	case ID_SelectPlaneCode:
		pCombo = _Combo1;
		break;
	default:
		break;
	}
	return pCombo;
}

CATDlgPushButton* CMSystemZWDlg::GetPushButton(int iCtrlID)
{
	CATDlgPushButton* pPushButton = NULL;

	//switch (iCtrlID)
	//{
	//case ID_SelectMIDCompButton:
	//	pPushButton = _PushButton1;
	//	break;
	//case ID_SelectZWPreviousButton:
	//	pPushButton = _PushButton2;
	//	break;
	//case ID_SelectZWFatherButton:
	//	pPushButton = _PushButton3;
	//	break;
	//default:
	//	break;
	//}

	return pPushButton;
}
// End of User Code


// End of implementation of class methods
