

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMSystemAODlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgCombo.h"
#include "CATDlgLabel.h"
#include "CATDlgCombo.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"

// Begin of User Code

// End of User Code

CMSystemAODlg::CMSystemAODlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_Label2 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Label3 = NULL;
	_Label4 = NULL;
	_Editor4 = NULL;
	_Label5 = NULL;
	_Editor5 = NULL;
	_Label6 = NULL;
	_Combo1 = NULL;
	_Label7 = NULL;
	_Combo2 = NULL;
	_Label8 = NULL;
	_Editor6 = NULL;
	_Label9 = NULL;
	_Editor9 = NULL;

	// Begin of User Code

	// End of User Code

}

CMSystemAODlg::~CMSystemAODlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Label2 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Label3 = NULL;
	_Label4 = NULL;
	_Editor4 = NULL;
	_Label5 = NULL;
	_Editor5 = NULL;
	_Label6 = NULL;
	_Combo1 = NULL;
	_Label7 = NULL;
	_Combo2 = NULL;
	_Label8 = NULL;
	_Editor6 = NULL;
	_Label9 = NULL;
	_Editor9 = NULL;
}



void CMSystemAODlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", 0);
	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	_Label4 = new CATDlgLabel(this, (const char*)"Label4", 0);
	_Editor4 = new CATDlgEditor(this, (const char*)"Editor4", 0);
	_Label5 = new CATDlgLabel(this, (const char*)"Label5", 0);
	_Editor5 = new CATDlgEditor(this, (const char*)"Editor5", 0);
	_Label6 = new CATDlgLabel(this, (const char*)"Label6", 0);
	_Combo1 = new CATDlgCombo(this, (const char*)"Combo1", 0 | CATDlgCmbDropDown);
	_Label7 = new CATDlgLabel(this, (const char*)"Label7", 0);
	_Combo2 = new CATDlgCombo(this, (const char*)"Combo2", 0 | CATDlgCmbDropDown);
	_Label8 = new CATDlgLabel(this, (const char*)"Label8", 0);
	_Editor6 = new CATDlgEditor(this, (const char*)"Editor6", 0);
	_Label9 = new CATDlgLabel(this, (const char*)"Label9", 0);
	_Editor9 = new CATDlgEditor(this, (const char*)"Editor9", 0);
	_Label1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label2->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(0, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);
	_Editor2->SetSensitivity(CATDlgDisable);
	_Editor2->SetGridConstraints(1, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);
	_Editor3->SetSensitivity(CATDlgDisable);
	_Editor3->SetGridConstraints(2, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Label3->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label4->SetGridConstraints(6, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor4->SetGridConstraints(6, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor4->SetVisibleTextWidth(20);
	_Label5->SetGridConstraints(7, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor5->SetGridConstraints(7, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor5->SetVisibleTextWidth(20);
	_Label6->SetGridConstraints(3, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Combo1->SetGridConstraints(3, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo1->SetVisibleTextWidth(20);
	_Label7->SetGridConstraints(4, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Combo2->SetGridConstraints(4, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo2->SetVisibleTextWidth(20);
	_Label8->SetGridConstraints(5, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor6->SetGridConstraints(5, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor6->SetVisibleTextWidth(20);
	_Label9->SetGridConstraints(8, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor9->SetGridConstraints(8, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor9->SetVisibleTextWidth(20);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMSystemAODlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_SelectMIDCompEditor:
		pEditor = _Editor1;
		break;
	case ID_SelectAOPreviousEditor:
		pEditor = _Editor2;
		break;
	case ID_SelectAOFatherEditor:
		pEditor = _Editor3;
		break;
	case ID_InputOperationOrderEditor:
		pEditor = _Editor4;
		break;
	case ID_InputAONameEditor:
		pEditor = _Editor5;
		break;
	case ID_AOSequenceCodeEditor:
		pEditor = _Editor6;
		break;
	case ID_InputEffEditor:
		pEditor = _Editor9;
		break;
	default:
		break;
	}

	return pEditor;
}

CATDlgCombo* CMSystemAODlg::GetCombo(int iCtrlID)
{
	CATDlgCombo * pCombo = NULL;
	switch (iCtrlID)
	{
	case ID_SectionAreaCombo:
		pCombo = _Combo1;
		break;
	case ID_ProfessionWorkCodeCombo:
		pCombo = _Combo2;
		break;
	default:
		break;
	}
	return pCombo;
}

CATDlgPushButton* CMSystemAODlg::GetPushButton(int iCtrlID)
{
	CATDlgPushButton* pPushButton = NULL;

	//switch (iCtrlID)
	//{
	//case ID_SelectMIDCompButton:
	//	pPushButton = _PushButton1;
	//	break;
	//case ID_SelectAOPreviousButton:
	//	pPushButton = _PushButton2;
	//	break;
	//case ID_SelectAOFatherButton:
	//	pPushButton = _PushButton3;
	//	break;
	//default:
	//	break;
	//}

	return pPushButton;
}
// End of User Code


// End of implementation of class methods
