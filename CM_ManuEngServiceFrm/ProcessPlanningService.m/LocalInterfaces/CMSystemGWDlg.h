

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMSystemGWDlg_h
#define CMSystemGWDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgEditor;

// Begin of User Code
class CATDlgPushButton;
enum COMACGWSystemDlg_ControlID
{
	ID_SelectMIDCompButton = 0,
	ID_SelectGWFatherButton = 1,
	ID_SelectMIDCompEditor = 10,
	ID_SelectGWFatherEditor = 11,
	ID_InputGWCodeEditor = 12,
	ID_InputGWNameEditor = 13,
	ID_InputEffEditor
};
// End of User Code

class  CMSystemGWDlg : public CATDlgDialog {
	DeclareResource(CMSystemGWDlg, CATDlgDialog)

public:
	CMSystemGWDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMSystemGWDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMSystemGWDlg(const CMSystemGWDlg&);
	CMSystemGWDlg& operator= (const CMSystemGWDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgLabel* _Label2;
	CATDlgLabel* _Label3;
	CATDlgEditor* _Editor1;
	CATDlgEditor* _Editor2;
	CATDlgEditor* _Editor3;
	CATDlgLabel* _Label4;
	CATDlgEditor* _Editor4;
	CATDlgLabel* _Label5;
	CATDlgEditor* _Editor5;

	// Begin of User Code
public:
	CATDlgPushButton* GetPushButton(int iCtrlID);
	CATDlgEditor* GetEditor(int iCtrlID);
	// End of User Code

};

#endif
