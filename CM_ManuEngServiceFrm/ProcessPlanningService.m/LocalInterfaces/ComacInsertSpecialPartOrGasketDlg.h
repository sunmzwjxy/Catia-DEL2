

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef ComacInsertSpecialPartOrGasketDlg_h
#define ComacInsertSpecialPartOrGasketDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgCombo;
//class CATDlgRadioButton;

// Begin of User Code
enum COMACMBOMPartDlg_ControlID
{
	ID_SelectCreateAssemblyEditor,
	ID_ProcessPartNoEditor,
	ID_ProcessPartNameEditor,		// editor
	ID_PartCodeEditor,				// comb
	ID_ManufactureLineEditor,
	ID_ProcessUnitEditor,
	ID_ProcessPartTypeEditor
	//ID_DesignCodeCopy,			// radio button
	//ID_DesignCodeInput
};
// End of User Code

class  ComacInsertSpecialPartOrGasketDlg : public CATDlgDialog {
	DeclareResource(ComacInsertSpecialPartOrGasketDlg, CATDlgDialog)

public:
	ComacInsertSpecialPartOrGasketDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~ComacInsertSpecialPartOrGasketDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	ComacInsertSpecialPartOrGasketDlg(const ComacInsertSpecialPartOrGasketDlg&);
	ComacInsertSpecialPartOrGasketDlg& operator= (const ComacInsertSpecialPartOrGasketDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgEditor* _Editor1;

	CATDlgLabel* _Label7;			// 新增加的 工艺件类型 对应的type：特制件、垫片
	CATDlgCombo* _Combo4;

	CATDlgLabel* _Label2;
	CATDlgEditor* _Editor2;
	CATDlgLabel* _Label3;
	CATDlgLabel* _Label4;
	CATDlgLabel* _Label5;
	CATDlgCombo* _Combo1;
	CATDlgCombo* _Combo2;
	CATDlgCombo* _Combo3;
	CATDlgLabel* _Label6;
	CATDlgEditor* _Editor3;

	//CATDlgRadioButton* _RadioButton1;
	//CATDlgRadioButton* _RadioButton2;
	// Begin of User Code
public:
	CATDlgEditor* GetEditor(int iCtrlID);
	CATDlgCombo* GetCombo(int iCtrlID);
	//CATDlgRadioButton* GetRadioButton(int iCtrlID);
	// End of User Code

};

#endif
