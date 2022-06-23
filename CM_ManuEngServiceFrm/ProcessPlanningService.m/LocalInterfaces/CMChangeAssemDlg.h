

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMChangeAssemDlg_h
#define CMChangeAssemDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgCombo;
class CATDlgCombo;
class CATDlgLabel;
class CATDlgCombo;
class CATDlgPushButton;

// Begin of User Code
enum COMACCHGMBOMAssemDlg_ControlID
{
	ID_SelectProvideEditor,
	ID_ManufacturingNameEditor,
	ID_ReviseManuAssemEditor,
	ID_FatherManuAssemEditor,
	ID_ManufacturingTitleEditor,
	ID_PartCodeEditor,
	ID_ManufactureLineEditor,
	ID_ProcessUnitEditor,
	ID_RevisionEditor,
	ID_ComponentBtn,
	ID_FatherCompBtn
};
// End of User Code

class  CMChangeAssemDlg : public CATDlgDialog {
	DeclareResource(CMChangeAssemDlg, CATDlgDialog)

public:
	CMChangeAssemDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMChangeAssemDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMChangeAssemDlg(const CMChangeAssemDlg&);
	CMChangeAssemDlg& operator= (const CMChangeAssemDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgEditor* _Editor1;
	CATDlgEditor* _Editor2;
	CATDlgLabel* _Label2;
	CATDlgLabel* _Label3;
	CATDlgEditor* _Editor3;
	CATDlgLabel* _Label4;
	CATDlgLabel* _Label5;
	CATDlgCombo* _Combo1;
	CATDlgCombo* _Combo2;
	CATDlgLabel* _Label6;
	CATDlgCombo* _Combo3;
	CATDlgLabel* _Label7;
	CATDlgEditor* _Editor4;

	CATDlgPushButton* _Button1;
	CATDlgPushButton* _Button2;

	// Begin of User Code
public:
	CATDlgEditor* GetEditor(int iCtrlID);
	CATDlgCombo* GetCombo(int iCtrlID);
	CATDlgPushButton* GetPushButton(int iCtrlID);
	// End of User Code

};

#endif
