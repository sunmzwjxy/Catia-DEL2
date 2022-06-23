

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMMakePartDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgCombo.h"
#include "CATDlgRadioButton.h"
// Begin of User Code

// End of User Code

CMMakePartDlg::CMMakePartDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL				// meiyou CATDlgWndAPPLY
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_Editor1 = NULL;
	_Label2 = NULL;
	_Editor2 = NULL;
	_Label3 = NULL;
	_Label4 = NULL;
	_Label5 = NULL;
	_Combo1 = NULL;
	_Combo2 = NULL;
	_Combo3 = NULL;
	_Label6 = NULL;
	_Editor3 = NULL;
	_RadioButton1 = NULL;
	_RadioButton2 = NULL;
	// Begin of User Code

	// End of User Code

}

CMMakePartDlg::~CMMakePartDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Editor1 = NULL;
	_Label2 = NULL;
	_Editor2 = NULL;
	_Label3 = NULL;
	_Label4 = NULL;
	_Label5 = NULL;
	_Combo1 = NULL;
	_Combo2 = NULL;
	_Combo3 = NULL;
	_Label6 = NULL;
	_Editor3 = NULL;
	_RadioButton1 = NULL;
	_RadioButton2 = NULL;
}



void CMMakePartDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Cod

	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0);
	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	_Label4 = new CATDlgLabel(this, (const char*)"Label4", 0);
	_Label5 = new CATDlgLabel(this, (const char*)"Label5", 0);
	_Combo1 = new CATDlgCombo(this, (const char*)"Combo1", 0 | CATDlgCmbDropDown);
	_Combo2 = new CATDlgCombo(this, (const char*)"Combo2", 0 | CATDlgCmbDropDown);
	_Combo3 = new CATDlgCombo(this, (const char*)"Combo3", 0 | CATDlgCmbDropDown);
	_Label6 = new CATDlgLabel(this, (const char*)"Label6", 0);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", 0);
	_RadioButton1 = new CATDlgRadioButton(this, (const char*)"RadioButton1", 0);
	_RadioButton2 = new CATDlgRadioButton(this, (const char*)"RadioButton2", 0);
	_RadioButton1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_RadioButton2->SetGridConstraints(0, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label1->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(1, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);
	//_Label2->SetVisibility(CATDlgHide);
	_Label2->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	//_Editor2->SetSensitivity(CATDlgDisable);
	//_Editor2->SetVisibility(CATDlgHide);
	_Editor2->SetGridConstraints(2, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);
	_Label6->SetGridConstraints(3, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor3->SetGridConstraints(3, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Label3->SetGridConstraints(4, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label4->SetGridConstraints(5, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label5->SetGridConstraints(6, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Combo1->SetGridConstraints(4, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo1->SetVisibleTextWidth(20);
	_Combo2->SetGridConstraints(5, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo2->SetVisibleTextWidth(20);
	_Combo3->SetGridConstraints(6, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Combo3->SetVisibleTextWidth(20);



	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMMakePartDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_SelectProvideEditor:
		pEditor = _Editor1;
		break;
	case ID_ManufacturingNameEditor:
		pEditor = _Editor2;
		break;
	case ID_DesignCodeEditor:
		pEditor = _Editor3;
		break;
	default:
		break;
	}

	return pEditor;
}
CATDlgRadioButton* CMMakePartDlg::GetRadioButton(int iCtrlID)
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
CATDlgCombo* CMMakePartDlg::GetCombo(int iCtrlID)
{
	CATDlgCombo* pCombo = NULL;

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


// End of implementation of class methods
