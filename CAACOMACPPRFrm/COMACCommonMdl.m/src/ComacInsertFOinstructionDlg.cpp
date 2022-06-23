

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "ComacInsertFOinstructionDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
//#include "CATDlgCombo.h"
//#include "CATDlgRadioButton.h"
// Begin of User Code

// End of User Code

ComacInsertFOinstructionDlg::ComacInsertFOinstructionDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL				// ц╩сп CATDlgWndAPPLY
		| CATDlgGridLayout
		| CATDlgWndAPPLY
	)
{

	_Label1 = NULL;
	_Editor1 = NULL;
	_Label2 = NULL;
	_Editor2 = NULL;
	_Label3 = NULL;
	_Editor3 = NULL;
	_Label4 = NULL;
	_Editor4 = NULL;
	_CheckButton1 = NULL;
}

ComacInsertFOinstructionDlg::~ComacInsertFOinstructionDlg()
{

	_Label1 = NULL;
	_Editor1 = NULL;
	_Label2 = NULL;
	_Editor2 = NULL;
	_Label3 = NULL;
	_Editor3 = NULL;
	_Label4 = NULL;
	_Editor4 = NULL;
	_CheckButton1 = NULL;

}


void ComacInsertFOinstructionDlg::Build()
{
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);

	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0 /* | CATDlgEdtInteger */ /*| CATDlgEdtNumerical*/);

	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", /*CATDlgEdtInteger |*/ CATDlgEdtNumerical);

	_Label4 = new CATDlgLabel(this, (const char*)"Label4", 0);
	_Editor4 = new CATDlgEditor(this, (const char*)"Editor4", /*CATDlgEdtInteger |*/ CATDlgEdtNumerical);

	_CheckButton1 = new CATDlgCheckButton(this, (const char*)"CheckButton1", 0);

	_Label1->SetGridConstraints(1, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	//_Editor1->SetSensitivity(CATDlgEnable);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(1, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);


	_Label2->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	//_Editor2->SetSensitivity(CATDlgEnable);
	_Editor2->SetSensitivity(CATDlgDisable);
	_Editor2->SetGridConstraints(2, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);
	_Editor2->SetText("");
	//_Editor2->SetText("010");


	_Label3->SetGridConstraints(3, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor3->SetSensitivity(CATDlgEnable);
	//_Editor2->SetSensitivity(CATDlgDisable);
	_Editor3->SetGridConstraints(3, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Editor3->SetText("1");


	_Label4->SetGridConstraints(4, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor4->SetSensitivity(CATDlgEnable);
	//_Editor2->SetSensitivity(CATDlgDisable);
	_Editor4->SetGridConstraints(4, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor4->SetVisibleTextWidth(20);
	_Editor4->SetText("10");

	_CheckButton1->SetGridConstraints(5, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_CheckButton1->SetState(CATDlgUncheck);


	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* ComacInsertFOinstructionDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_FatherWorkPlanEditor:
		pEditor = _Editor1;
		break;
	case ID_StartingOperationNameEditor:
		pEditor = _Editor2;
		break;
	case ID_OprationCountEditor:
		pEditor = _Editor3;
		break;
	case ID_OprationStepEditor:
		pEditor = _Editor4;
		break;
	default:
		break;
	}

	return pEditor;
}


CATDlgCheckButton* ComacInsertFOinstructionDlg::GetCheckButton(int iCtrlID)
{
	CATDlgCheckButton* pCheckBtn = NULL;

	switch (iCtrlID)
	{
		case ID_ConcurrentOPChectBtn:
			pCheckBtn = _CheckButton1;
			break;
		default:
			break;
	}

	return pCheckBtn;
}

