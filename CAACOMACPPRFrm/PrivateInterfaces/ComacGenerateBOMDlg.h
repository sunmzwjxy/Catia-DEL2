

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef ComacGenerateBOMDlg_h
#define ComacGenerateBOMDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgEditor;
//class CATDlgCombo;
//class CATDlgRadioButton;

// Begin of User Code
enum COMACMBOMPartDlg_ControlID
{
	ID_SelectCADEditor,
	//ID_ManufacturingNameEditor,
	ID_SelectMAEditor,
	/*ID_PartCodeEditor,
	ID_ManufactureLineEditor,
	ID_ProcessUnitEditor,
	ID_DesignCodeCopy,
	ID_DesignCodeInput*/
};
// End of User Code

class  ComacGenerateBOMDlg : public CATDlgDialog {
	DeclareResource(ComacGenerateBOMDlg, CATDlgDialog)

public:
	ComacGenerateBOMDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~ComacGenerateBOMDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	ComacGenerateBOMDlg(const ComacGenerateBOMDlg&);
	ComacGenerateBOMDlg& operator= (const ComacGenerateBOMDlg&);

private:
	CATDlgLabel * _Label1;
	CATDlgEditor* _Editor1;
	/*CATDlgLabel* _Label2;
	CATDlgEditor* _Editor2;*/
	CATDlgLabel* _Label3;
	/*CATDlgLabel* _Label4;
	CATDlgLabel* _Label5;
	CATDlgCombo* _Combo1;
	CATDlgCombo* _Combo2;
	CATDlgCombo* _Combo3;
	CATDlgLabel* _Label6;*/
	CATDlgEditor* _Editor3;

	/*CATDlgRadioButton* _RadioButton1;
	CATDlgRadioButton* _RadioButton2;*/
	// Begin of User Code
public:
	CATDlgEditor * GetEditor(int iCtrlID);
	/*CATDlgCombo* GetCombo(int iCtrlID);
	CATDlgRadioButton* GetRadioButton(int iCtrlID);*/
	// End of User Code

};

#endif
