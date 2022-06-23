

// BEGIN OF HEADER CODE
// ----------------------------------------

#ifndef CMMBOMReportDlg_h
#define CMMBOMReportDlg_h

#include "CATDlgDialog.h"
class CATDlgLabel;
class CATDlgEditor;

// Begin of User Code
enum COMACMBOMReportDlg_ControlID
{
	ID_SelectMAEditor,
	ID_ManufacturingNameEditor
};
// End of User Code

class  CMMBOMReportDlg : public CATDlgDialog {
	DeclareResource(CMMBOMReportDlg, CATDlgDialog)

public:
	CMMBOMReportDlg(CATDialog * iParent, const CATString& iDialogName);

	virtual ~CMMBOMReportDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	CMMBOMReportDlg(const CMMBOMReportDlg&);
	CMMBOMReportDlg& operator= (const CMMBOMReportDlg&);

private:
	CATDlgLabel* _Label1;
	CATDlgEditor* _Editor1;

	// Begin of User Code
public:
	CATDlgEditor* GetEditor(int iCtrlID);
	// End of User Code

};

#endif
