

// BEGIN OF HEADER CODE
// ----------------------------------------
    
#ifndef COMACMBOMInitDlg_h
#define COMACMBOMInitDlg_h

#include "CATDlgDialog.h"
class CATDlgFrame;
class CATDlgLabel;
class CATDlgEditor;
class CATDlgFrame;
class CATDlgMultiList;

// Begin of User Code
#include "CATUnicodeString.h"
#include <vector>
class FOTask
{
public:
	CATUnicodeString MPRFormNum;
	CATUnicodeString MPRType;
	CATUnicodeString PartNumber;
	CATUnicodeString PartRevision;
	CATUnicodeString FOName;
	CATUnicodeString FORevision;
	CATUnicodeString MPRId;
	CATUnicodeString IsRevise;
};
// End of User Code

class  COMACMBOMInitDlg : public CATDlgDialog {
DeclareResource(COMACMBOMInitDlg, CATDlgDialog)

public:
	COMACMBOMInitDlg(CATDialog * iParent, const CATString& iDialogName);
	
	virtual ~COMACMBOMInitDlg();
	void Build();

	// Copy ctor and assignment operators are declared but not defined by infra
	COMACMBOMInitDlg(const COMACMBOMInitDlg&);
	COMACMBOMInitDlg& operator= (const COMACMBOMInitDlg&);
	
private:
CATDlgFrame* _Frame1;
CATDlgLabel* _Label1;
CATDlgEditor* _Editor1;
CATDlgFrame* _Frame2;
CATDlgMultiList* _MultiList1;

// Begin of User Code
public:
	void SetUserName(CATUnicodeString iUserName);
	void InitMultiList(std::vector<FOTask> foVect);
	int GetSelectRow();
// End of User Code

};

#endif
