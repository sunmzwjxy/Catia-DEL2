

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMMBOMAssemDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgCombo.h"
#include "CATDlgCombo.h"
#include "CATDlgCombo.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgPushButton.h"
#include "CATDlgRadioButton.h"
// Begin of User Code

// End of User Code

CMMBOMAssemDlg::CMMBOMAssemDlg(CATDialog* iParent, const CATString& iName)
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
	_Label5 = NULL;
	_Label6 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Combo1 = NULL;
	_Combo2 = NULL;
	_Combo3 = NULL;
	_Label7 = NULL;
	_Editor4 = NULL;
	_RadioButton1 = NULL;
	_RadioButton2 = NULL;
	// Begin of User Code

	// End of User Code

}

CMMBOMAssemDlg::~CMMBOMAssemDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Label4 = NULL;
	_Label5 = NULL;
	_Label6 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Combo1 = NULL;
	_Combo2 = NULL;
	_Combo3 = NULL;
	_Label7 = NULL;
	_Editor4 = NULL;
	_PushButton1 = NULL;
	_RadioButton1 = NULL;
	_RadioButton2 = NULL;
}



void CMMBOMAssemDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	_Label4 = new CATDlgLabel(this, (const char*)"Label4", 0);
	_Label5 = new CATDlgLabel(this, (const char*)"Label5", 0);
	_Label6 = new CATDlgLabel(this, (const char*)"Label6", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", 0);
	_Combo1 = new CATDlgCombo(this, (const char*)"Combo1", 0 | CATDlgCmbDropDown);
	_Combo2 = new CATDlgCombo(this, (const char*)"Combo2", 0 | CATDlgCmbDropDown);
	_Combo3 = new CATDlgCombo(this, (const char*)"Combo3", 0 | CATDlgCmbDropDown);
	_Label7 = new CATDlgLabel(this, (const char*)"Label7", 0);
	_Editor4 = new CATDlgEditor(this, (const char*)"Editor4", 0);
	//_PushButton1 = new CATDlgPushButton(this, (const char*)"PushButton1", 0);
	_RadioButton1 = new CATDlgRadioButton(this, (const char*)"RadioButton1", 0);
	_RadioButton2 = new CATDlgRadioButton(this, (const char*)"RadioButton2", 0);
	_Label1->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label2->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label3->SetGridConstraints(4, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label4->SetGridConstraints(5, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label5->SetGridConstraints(6, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label6->SetGridConstraints(7, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(1, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);
	_Editor2->SetSensitivity(CATDlgDisable);
	_Editor2->SetGridConstraints(2, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);
	_Editor3->SetGridConstraints(4, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Combo1->SetGridConstraints(5, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo1->SetVisibleTextWidth(20);
	_Combo2->SetGridConstraints(6, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo2->SetVisibleTextWidth(20);
	_Combo3->SetGridConstraints(7, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo3->SetVisibleTextWidth(20);
	_Label7->SetGridConstraints(3, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor4->SetGridConstraints(3, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor4->SetVisibleTextWidth(20);
	//_PushButton1->SetGridConstraints(8, 2, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_RadioButton1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_RadioButton2->SetGridConstraints(0, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMMBOMAssemDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_SelectCADProductEditor:
		pEditor = _Editor1;
		break;
	case ID_SelectMAFatherEditor:
		pEditor = _Editor2;
		break;
	case ID_InputMBOMAssemNameEditor:
		pEditor = _Editor3;
		break;
	case ID_DesignCodeEditor:
		pEditor = _Editor4;
		break;
	default:
		break;
	}

	return pEditor;
}

CATDlgCombo* CMMBOMAssemDlg::GetCombo(int iCtrlID)
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

CATDlgPushButton* CMMBOMAssemDlg::GetPushButton(int iCtrlID)
{
	CATDlgPushButton * pPushButton = NULL;
	switch (iCtrlID)
	{
	case ID_NumberCodePushButton:
		pPushButton = _PushButton1;
		break;
	default:
		break;
	}
	return pPushButton;
}

CATDlgRadioButton* CMMBOMAssemDlg::GetRadioButton(int iCtrlID)
{
	CATDlgRadioButton * pRadioButton = NULL;
	switch (iCtrlID)
	{
	case ID_DesignCodeCopy:
		pRadioButton = _RadioButton1;
		break;
	case ID_DesignCodeInput:
		pRadioButton = _RadioButton2;
		break;
	default:
		break;
	}
	return pRadioButton;
}
// End of User Code


// End of implementation of class methods
