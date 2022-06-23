//===================================================================
// COPYRIGHT  2020/10/20
//===================================================================
// CMChangeMBOMAssemCmd.cpp
// Header definition of class CMChangeMBOMAssemCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/10/20 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef CMChangeMBOMAssemCmd_H
#define CMChangeMBOMAssemCmd_H

#include "CMChangeAssemDlg.h"

#include "CATStateCommand.h"

#include "ProcessPlanningService.h"

#include "CATPathElementAgent.h"

#include "CATDlgPushButton.h"

//CATPLMComponentInterfaces 
#include "CATIPLMNavReference.h"
#include "CATIPLMNavOccurrence.h"
#include "CATIPLMNavRepInstance.h"
#include "CATIPLMNavInstance.h"
#include "CATSysBoolean.h"
#include "CATDialogAgent.h"

//VisualizationInterfaces 
#include "CATPathElement.h"

//DELPPRProcessItf 
#include "DELPPRProcessNavAccess.h"
#include "DELIPPRProcessNav.h"
#include "DELIPPRProcessAuth.h"
#include "DELPPRProcessAuthAccess.h"

#include "iostream.h"

#include "CATStateCommand.h"

#include "CATPathElementAgent.h"
#include "CATIPLMNavOccurrence.h"
#include "CATIPLMNavRepInstance.h"
#include "CATIPLMNavReference.h"
#include "CATListPtrCATIAdpPLMIdentificator.h"
#include "CATListPtrCATIPLMNavReference.h"
//-----------------------------------------------------------------------

class CMChangeMBOMAssemCmd: public CATStateCommand
{
	DeclareResource(CMChangeMBOMAssemCmd, CATStateCommand)
public:
// Standard constructors and destructors
// -------------------------------------
CMChangeMBOMAssemCmd ();
virtual ~CMChangeMBOMAssemCmd ();

//
// TODO: Add your methods for this class here.
virtual void     BuildGraph();

CATBoolean ElementSelection(void * data);

void FilterSelectObject();

virtual CATBoolean OKAction(void *data);

virtual CATBoolean ApplyAction(void *data);

virtual CATBoolean CancelAction(void *data);

void SetComponentObject();

void SetFatherComponentObject();

CATBoolean CheckSelectObject();

HRESULT ChangeMBOMAssembly();
//

private:
// Copy constructor and equal operator
// -----------------------------------
CMChangeMBOMAssemCmd (CMChangeMBOMAssemCmd &);
CMChangeMBOMAssemCmd& operator=(CMChangeMBOMAssemCmd&);

int selectFlag = 0;

CMChangeAssemDlg *_Panel;

CATDialogAgent *_OKAgent;
CATDialogAgent *_ApplyAgent;
CATDialogAgent *_CancleAgent;
CATDialogAgent *_CloseAgent;

CATDlgPushButton *_ComponentBtn;
CATDlgPushButton *_FatherCompBtn;

CATPathElementAgent *_pSelectAgent;

CATPathElementAgent *_pSelectCompFatherAgent;

CATBaseUnknown        * _pSelectedElement;
CATIPLMNavOccurrence  * _pSelectedOccurrence;
CATIPLMNavRepInstance * _pSelectedRepInstance;
CATIPLMNavReference   * _pSelectedReference;
CATDialogTransition * _pDialogTransition;

CATIPLMNavOccurrence * pMIDComponentOcc;
CATIPLMNavReference * pMIDComponentRef;

CATIPLMNavOccurrence * pReviseMIDOcc;
CATIPLMNavReference * pReviseMIDRef;

CATIPLMNavOccurrence * pFatherMIDOcc;
CATIPLMNavReference * pFatherMIDRef;

CATIPLMNavOccurrence * pMAFatherOcc;
CATIPLMNavReference * pMAFatherRef;

CATIPLMNavOccurrence * pMARootOcc;
CATIPLMNavReference * pMARootRef;

};

//-----------------------------------------------------------------------

#endif