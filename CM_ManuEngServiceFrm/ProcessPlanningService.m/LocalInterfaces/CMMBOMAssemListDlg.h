

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMMBOMAssemListDlg_h
#define CMMBOMAssemListDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgSelectorList;

// Begin of User Code
enum COMACMBOMAssemListDlg_ControlID
{
	ID_ComponentNumberList
};
// End of User Code

class  CMMBOMAssemListDlg : public CATDlgDialog {
	DeclareResource(CMMBOMAssemListDlg, CATDlgDialog)

public:
	CMMBOMAssemListDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMMBOMAssemListDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMMBOMAssemListDlg(const CMMBOMAssemListDlg&);
	CMMBOMAssemListDlg& operator= (const CMMBOMAssemListDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgSelectorList* _SelectorList1;

	// Begin of User Code
public:
	CATDlgSelectorList* GetSelectorList(int iCtrlID);
	// End of User Code

};

#endif
