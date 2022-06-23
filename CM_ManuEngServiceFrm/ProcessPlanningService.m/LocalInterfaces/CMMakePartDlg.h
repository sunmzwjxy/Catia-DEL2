

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMMakePartDlg_h
#define CMMakePartDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgCombo;
class CATDlgRadioButton;

// Begin of User Code
enum COMACMBOMPartDlg_ControlID
{
	ID_SelectProvideEditor,		// 工艺零件号
	ID_ManufacturingNameEditor, // 工艺零组件名称
	ID_DesignCodeEditor,		// 设计基本号
	ID_PartCodeEditor,			// 零件代码
	ID_ManufactureLineEditor,	// 制造路线
	ID_ProcessUnitEditor,		// 使用单位
	ID_DesignCodeCopy,			// radio button
	ID_DesignCodeInput
};
// End of User Code

class  CMMakePartDlg : public CATDlgDialog {
	DeclareResource(CMMakePartDlg, CATDlgDialog)

public:
	CMMakePartDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMMakePartDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMMakePartDlg(const CMMakePartDlg&);
	CMMakePartDlg& operator= (const CMMakePartDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgEditor* _Editor1;
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

	CATDlgRadioButton* _RadioButton1;
	CATDlgRadioButton* _RadioButton2;
	// Begin of User Code
public:
	CATDlgEditor* GetEditor(int iCtrlID);
	CATDlgCombo* GetCombo(int iCtrlID);
	CATDlgRadioButton* GetRadioButton(int iCtrlID);
	// End of User Code

};

#endif
