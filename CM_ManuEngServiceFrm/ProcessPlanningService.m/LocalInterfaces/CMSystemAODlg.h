

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMSystemAODlg_h
#define CMSystemAODlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgCombo;
class CATDlgLabel;
class CATDlgCombo;
class CATDlgLabel;
class CATDlgEditor;

// Begin of User Code
class CATDlgPushButton;
enum COMACZWSystemDlg_ControlID
{
	ID_SelectMIDCompButton = 0,
	ID_SelectAOFatherButton,
	ID_SelectAOPreviousButton,
	ID_SelectMIDCompEditor,
	ID_SelectAOFatherEditor,
	ID_InputOperationOrderEditor,
	ID_SelectAOPreviousEditor,
	ID_InputAONameEditor,
	ID_SectionAreaCombo,
	ID_ProfessionWorkCodeCombo,
	ID_AOSequenceCodeEditor,
	ID_InputEffEditor
};
// End of User Code

class  CMSystemAODlg : public CATDlgDialog {
	DeclareResource(CMSystemAODlg, CATDlgDialog)

public:
	CMSystemAODlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMSystemAODlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMSystemAODlg(const CMSystemAODlg&);
	CMSystemAODlg& operator= (const CMSystemAODlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgLabel* _Label2;
	CATDlgEditor* _Editor1;
	CATDlgEditor* _Editor2;
	CATDlgEditor* _Editor3;
	CATDlgLabel* _Label3;
	CATDlgLabel* _Label4;
	CATDlgEditor* _Editor4;
	CATDlgLabel* _Label5;
	CATDlgEditor* _Editor5;
	CATDlgLabel* _Label6;
	CATDlgCombo* _Combo1;
	CATDlgLabel* _Label7;
	CATDlgCombo* _Combo2;
	CATDlgLabel* _Label8;
	CATDlgEditor* _Editor6;
	CATDlgLabel* _Label9;
	CATDlgEditor* _Editor9;

	// Begin of User Code
public:
	CATDlgPushButton* GetPushButton(int iCtrlID);
	CATDlgEditor* GetEditor(int iCtrlID);
	CATDlgCombo* GetCombo(int iCtrlID);
	// End of User Code

};

#endif
