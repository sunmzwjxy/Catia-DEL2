

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef ComacReNameOperationsDlg_h
#define ComacReNameOperationsDlg_h

#include "COMACCommonMdl.h"
#include "CATDlgDialog.h"
#include "CATDlgCheckButton.h"
#include "CATDlgFrame.h"



class CATDlgLabel;
class CATDlgFrame;
class CATDlgEditor; 
//class CATDlgLabel;
//class CATDlgEditor;
//class CATDlgCombo;
//class CATDlgRadioButton;
//class CATDlgCheckButton;

enum ComacReNameOperationsDlg_ControlID
{
	ID_FatherWorkPlanEditor/*,
	ID_StartingOperationNameEditor,
	ID_OprationCountEditor,
	ID_OprationStepEditor,
	ID_ConcurrentOPChectBtn*/
};

class  ComacReNameOperationsDlg : public CATDlgDialog {
	DeclareResource(ComacReNameOperationsDlg, CATDlgDialog)

public:
	ComacReNameOperationsDlg(CATDialog * iParent, const CATString& iDialogName);
	virtual ~ComacReNameOperationsDlg();

	void Build();
	CATDlgEditor* GetEditor(int iCtrlID);

	//
	// TODO: Add your methods for this class here.
	//

	// Copy constructor and equal operator
	// -----------------------------------
	ComacReNameOperationsDlg(ComacReNameOperationsDlg &);
	ComacReNameOperationsDlg& operator=(ComacReNameOperationsDlg&);

private:

	CATDlgLabel * _Label1;
	CATDlgEditor* _Editor1;
	CATDlgFrame * _Frame001;
	CATDlgLabel * _Label2;

};

#endif
