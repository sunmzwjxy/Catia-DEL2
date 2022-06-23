//===================================================================
// COPYRIGHT  2020/09/16
//===================================================================
// CMCreateAOSystemCmd.cpp
// Header definition of class CMCreateAOSystemCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/09/16 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef CMCreateAOSystemCmd_H
#define CMCreateAOSystemCmd_H

#include "ProcessPlanningService.h"
#include "CATStateCommand.h"
#include "CATSysBoolean.h"
#include "CATDialogAgent.h"

#include "iostream.h"

#include "CMSystemAODlg.h"
#include "CATPathElementAgent.h"

//CATPLMComponentInterfaces 
#include "CATIPLMNavReference.h"
#include "CATIPLMNavOccurrence.h"
#include "CATIPLMNavRepInstance.h"


//VisualizationInterfaces 
#include "CATPathElement.h"
#include "CATListPtrCATIAdpPLMIdentificator.h"
#include "CATListPtrCATIPLMNavReference.h"

#include "PPRUtity.h"
//-----------------------------------------------------------------------

class CMCreateAOSystemCmd : public CATStateCommand
{
	DeclareResource(CMCreateAOSystemCmd, CATStateCommand)

public:
	// Standard constructors and destructors
	// -------------------------------------
	CMCreateAOSystemCmd();
	virtual ~CMCreateAOSystemCmd();

	//
	// TODO: Add your methods for this class here.
	virtual void     BuildGraph();

	/**
	* Action associated to state transitions.
	*/
	virtual CATBoolean  ActionOne(void * data);

	virtual CATBoolean OKAction(void *data);

	virtual CATBoolean ApplyAction(void *data);

	virtual CATBoolean CancelAction(void *data);

	CATBoolean CheckInputCode(int code);

	CATBoolean CheckAOSelect();

	CATBoolean ElementSelection(void * data);

	void FilterSelectObject();

	HRESULT CreateDELAOSystem();

	CATUnicodeString sApplyAOCode;

	CATBoolean bApplyCreate;

	//

private:
	// Copy constructor and equal operator
	// -----------------------------------
	CMCreateAOSystemCmd(CMCreateAOSystemCmd &);
	CMCreateAOSystemCmd& operator=(CMCreateAOSystemCmd&);

	CATBoolean Init(void *data);

	CMSystemAODlg *_Panel;

	CATDialogAgent *_OKAgent;
	CATDialogAgent *_ApplyAgent;
	CATDialogAgent *_CloseAgent;
	CATDialogAgent *_CancleAgent;

	PPRUtity spPPRUtity;

	CATPathElementAgent *_pSelectAgent;

	CATBaseUnknown        * _pSelectedElement;
	CATIPLMNavOccurrence  * _pSelectedOccurrence;
	CATIPLMNavRepInstance * _pSelectedRepInstance;
	CATIPLMNavReference   * _pSelectedReference;

	CATUnicodeString sInputAOExternalID;

	CATUnicodeString sInputAOName;

	CATUnicodeString sInputEffecivity;

	CATIPLMNavReference * pMIDComponentRef;
	CATIPLMNavInstance * pMIDCompInstance;
	CATIPLMNavOccurrence * pMIDComponentOcc;
	CATIPLMNavReference * pMIDFatherCompRef;

	CATIPLMNavReference * pAOFatherRef;
	CATIPLMNavOccurrence * pAOFatherOcc;

	CATIPLMNavReference * pGWRef;

	CATIPLMNavReference * pAOPreviousRef;
	CATIPLMNavOccurrence * pAOPreviousOcc;

};

//-----------------------------------------------------------------------

#endif

