

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMChangeMakePartDlg_h
#define CMChangeMakePartDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgLabel;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgEditor;
class CATDlgEditor;

// Begin of User Code
enum COMACCHGMBOMAssemDlg_ControlID
{
	ID_SelectManufacturingPartEditor,
	ID_ManufacturingAssemblyEditor,
	ID_DesignPartEditor
};
// End of User Code

class  CMChangeMakePartDlg : public CATDlgDialog {
	DeclareResource(CMChangeMakePartDlg, CATDlgDialog)

public:
	CMChangeMakePartDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMChangeMakePartDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMChangeMakePartDlg(const CMChangeMakePartDlg&);
	CMChangeMakePartDlg& operator= (const CMChangeMakePartDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgLabel* _Label2;
	CATDlgLabel* _Label3;
	CATDlgEditor* _Editor2;
	CATDlgEditor* _Editor3;
	CATDlgEditor* _Editor1;

	// Begin of User Code
public:
	CATDlgEditor* GetEditor(int iCtrlID);
	// End of User Code

};

#endif
