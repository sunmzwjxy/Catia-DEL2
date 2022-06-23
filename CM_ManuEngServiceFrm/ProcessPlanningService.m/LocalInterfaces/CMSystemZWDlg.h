

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMSystemZWDlg_h
#define CMSystemZWDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgCombo;

// Begin of User Code
class CATDlgPushButton;
enum COMACZWSystemDlg_ControlID
{
	ID_SelectMIDCompButton = 0,
	ID_SelectZWFatherButton = 1,
	ID_SelectZWPreviousButton,
	ID_SelectMIDCompEditor = 10,
	ID_SelectZWFatherEditor = 11,
	ID_InputZWCodeEditor = 12,
	ID_SelectZWPreviousEditor,
	ID_InputZWNameEditor,
	ID_SelectPlaneCode,
	ID_InputEffEditor
};
// End of User Code

class  CMSystemZWDlg : public CATDlgDialog {
	DeclareResource(CMSystemZWDlg, CATDlgDialog)

public:
	CMSystemZWDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMSystemZWDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMSystemZWDlg(const CMSystemZWDlg&);
	CMSystemZWDlg& operator= (const CMSystemZWDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgLabel* _Label2;
	CATDlgLabel* _Label3;
	CATDlgLabel* _Label4;
	CATDlgEditor* _Editor1;
	CATDlgEditor* _Editor2;
	CATDlgEditor* _Editor3;
	CATDlgEditor* _Editor4;
	CATDlgLabel* _Label5;
	CATDlgEditor* _Editor5;
	CATDlgLabel* _Label6;
	CATDlgCombo* _Combo1;
	CATDlgLabel* _Label7;
	CATDlgEditor* _Editor7;

	// Begin of User Code
public:
	CATDlgPushButton* GetPushButton(int iCtrlID);
	CATDlgEditor* GetEditor(int iCtrlID);
	CATDlgCombo* GetCombo(int iCtrlID);
	// End of User Code

};

#endif
