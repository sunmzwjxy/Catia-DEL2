

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef ComacInsertFOinstructionDlg_h
#define ComacInsertFOinstructionDlg_h

#include "COMACCommonMdl.h"
#include "CATDlgDialog.h"
#include "CATDlgCheckButton.h"


class CATDlgLabel;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgEditor;
//class CATDlgCombo;
//class CATDlgRadioButton;
class CATDlgCheckButton;

enum ComacInsertFOinstructionDlg_ControlID
{
	ID_FatherWorkPlanEditor,
	ID_StartingOperationNameEditor,
	ID_OprationCountEditor,
	ID_OprationStepEditor,
	ID_ConcurrentOPChectBtn
};

class  ComacInsertFOinstructionDlg : public CATDlgDialog {
	DeclareResource(ComacInsertFOinstructionDlg, CATDlgDialog)

public:
	ComacInsertFOinstructionDlg(CATDialog * iParent, const CATString& iDialogName);
	virtual ~ComacInsertFOinstructionDlg();

	void Build();
	CATDlgEditor* GetEditor(int iCtrlID);
	CATDlgCheckButton* GetCheckButton(int iCtrlID);

	//
	// TODO: Add your methods for this class here.
	//

	// Copy constructor and equal operator
	// -----------------------------------
	ComacInsertFOinstructionDlg(ComacInsertFOinstructionDlg &);
	ComacInsertFOinstructionDlg& operator=(ComacInsertFOinstructionDlg&);

private:

	CATDlgLabel * _Label1;
	CATDlgEditor* _Editor1;
	CATDlgLabel* _Label2;
	CATDlgEditor* _Editor2;
	CATDlgLabel* _Label3;
	CATDlgEditor* _Editor3;
	CATDlgLabel* _Label4;
	CATDlgEditor* _Editor4;

	CATDlgCheckButton *_CheckButton1;

};

#endif
