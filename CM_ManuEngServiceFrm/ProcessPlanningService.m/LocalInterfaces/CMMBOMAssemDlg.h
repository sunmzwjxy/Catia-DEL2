

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMMBOMAssemDlg_h
#define CMMBOMAssemDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgCombo;
class CATDlgCombo;
class CATDlgCombo;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgPushButton;
class CATDlgRadioButton;

// Begin of User Code
enum COMACMBOMAssemDlg_ControlID
{
	ID_SelectCADProductEditor,
	ID_SelectMAFatherEditor,
	ID_InputMBOMAssemNameEditor,
	ID_DesignCodeEditor,
	ID_PartCodeEditor,
	ID_ManufactureLineEditor,
	ID_ProcessUnitEditor,
	ID_NumberCodePushButton,
	ID_DesignCodeInput,
	ID_DesignCodeCopy
};
// End of User Code

class  CMMBOMAssemDlg : public CATDlgDialog {
	DeclareResource(CMMBOMAssemDlg, CATDlgDialog)

public:
	CMMBOMAssemDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMMBOMAssemDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMMBOMAssemDlg(const CMMBOMAssemDlg&);
	CMMBOMAssemDlg& operator= (const CMMBOMAssemDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgLabel* _Label2;
	CATDlgLabel* _Label3;
	CATDlgLabel* _Label4;
	CATDlgLabel* _Label5;
	CATDlgLabel* _Label6;
	CATDlgEditor* _Editor1;
	CATDlgEditor* _Editor2;
	CATDlgEditor* _Editor3;
	CATDlgCombo* _Combo1;
	CATDlgCombo* _Combo2;
	CATDlgCombo* _Combo3;
	CATDlgLabel* _Label7;
	CATDlgEditor* _Editor4;
	CATDlgPushButton* _PushButton1;
	CATDlgRadioButton* _RadioButton1;
	CATDlgRadioButton* _RadioButton2;

	// Begin of User Code
public:
	CATDlgEditor* GetEditor(int iCtrlID);
	CATDlgCombo* GetCombo(int iCtrlID);
	CATDlgPushButton* GetPushButton(int iCtrlID);
	CATDlgRadioButton* GetRadioButton(int iCtrlID);
	// End of User Code

};

#endif
