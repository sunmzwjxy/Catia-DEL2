

// ----------------------------------------
// BEGIN OF IMPLEMENTATION CODE
// ----------------------------------------
#include "CMSystemGWDlg.h"
#include "CATDlgGridConstraints.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgEditor.h"
#include "CATDlgLabel.h"
#include "CATDlgEditor.h"

// Begin of User Code

// End of User Code

CMSystemGWDlg::CMSystemGWDlg(CATDialog* iParent, const CATString& iName)
	:CATDlgDialog(iParent, iName, 0
		| CATDlgWndOK
		| CATDlgWndCANCEL
		| CATDlgGridLayout
	)
{

	_Label1 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Label4 = NULL;
	_Editor4 = NULL;
	_Label5 = NULL;
	_Editor5 = NULL;

	// Begin of User Code

	// End of User Code

}

CMSystemGWDlg::~CMSystemGWDlg()
{

	// Begin of User Code

	// End of User Code
	_Label1 = NULL;
	_Label2 = NULL;
	_Label3 = NULL;
	_Editor1 = NULL;
	_Editor2 = NULL;
	_Editor3 = NULL;
	_Label4 = NULL;
	_Editor4 = NULL;
	_Label5 = NULL;
	_Editor5 = NULL;

}



void CMSystemGWDlg::Build()
{
	int style = 0;

	// Begin of User Code

	// End of User Code
	_Label1 = new CATDlgLabel(this, (const char*)"Label1", 0);
	_Label2 = new CATDlgLabel(this, (const char*)"Label2", 0);
	_Label3 = new CATDlgLabel(this, (const char*)"Label3", 0);
	_Editor1 = new CATDlgEditor(this, (const char*)"Editor1", 0);
	_Editor2 = new CATDlgEditor(this, (const char*)"Editor2", 0);
	_Editor3 = new CATDlgEditor(this, (const char*)"Editor3", 0);
	_Label4 = new CATDlgLabel(this, (const char*)"Label4", 0);
	_Editor4 = new CATDlgEditor(this, (const char*)"Editor4", 0);
	_Label5 = new CATDlgLabel(this, (const char*)"Label5", 0);
	_Editor5 = new CATDlgEditor(this, (const char*)"Editor5", 0);
	_Label1->SetGridConstraints(0, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label2->SetGridConstraints(4, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Label3->SetGridConstraints(2, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor1->SetSensitivity(CATDlgDisable);
	_Editor1->SetGridConstraints(0, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor1->SetVisibleTextWidth(20);
	_Editor2->SetSensitivity(CATDlgDisable);
	_Editor2->SetGridConstraints(2, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor2->SetVisibleTextWidth(20);
	_Editor3->SetGridConstraints(4, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor3->SetVisibleTextWidth(20);
	_Label4->SetGridConstraints(5, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor4->SetGridConstraints(5, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor4->SetVisibleTextWidth(20);
	_Label5->SetGridConstraints(6, 0, 1, 1, 0 | CATGRID_LEFT | CATGRID_TOP);
	_Editor5->SetGridConstraints(6, 1, 1, 1, 0 | CATGRID_LEFT | CATGRID_RIGHT | CATGRID_TOP);
	_Editor5->SetVisibleTextWidth(20);

	// Begin of User Code

	// End of User Code

}


// You can put here the implementation of class methods

// Begin of User Code
CATDlgEditor* CMSystemGWDlg::GetEditor(int iCtrlID)
{
	CATDlgEditor* pEditor = NULL;

	switch (iCtrlID)
	{
	case ID_SelectMIDCompEditor:
		pEditor = _Editor1;
		break;
	case ID_SelectGWFatherEditor:
		pEditor = _Editor2;
		break;
	case ID_InputGWCodeEditor:
		pEditor = _Editor3;
		break;
	case ID_InputGWNameEditor:
		pEditor = _Editor4;
		break;
	case ID_InputEffEditor:
		pEditor = _Editor5;
		break;
	default:
		break;
	}

	return pEditor;
}

CATDlgPushButton* CMSystemGWDlg::GetPushButton(int iCtrlID)
{
	CATDlgPushButton* pPushButton = NULL;

	//switch (iCtrlID)
	//{
	//case ID_SelectMIDCompButton:
	//	pPushButton = _PushButton1;
	//	break;
	//case ID_SelectGWFatherButton:
	//	pPushButton = _PushButton2;
	//	break;
	//default:
	//	break;
	//}

	return pPushButton;
}
// End of User Code


// End of implementation of class methods
