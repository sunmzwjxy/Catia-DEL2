//===================================================================
// COPYRIGHT  2020/09/27
//===================================================================
// ComacNewVersionCmd.cpp
// Header definition of class ComacNewVersionCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/09/27 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef ComacNewVersionCmd_H
#define ComacNewVersionCmd_H

//#include "ProcessPlanningService.h"
#include "CATStateCommand.h"

#include "ComacNewVersionDlg.h"
#include "CATPathElementAgent.h"

//CATPLMComponentInterfaces 
#include "CATIPLMNavReference.h"
#include "CATIPLMNavOccurrence.h"
#include "CATIPLMNavRepInstance.h"
#include "CATIPLMNavInstance.h"
#include "CATIPLMNavRepInstance.h"
#include "CATIPLMNavReference.h"
#include "CATIPLMNavEntity.h"
#include "CATListPtrCATIPLMNavEntity.h"

// CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationLoadMode.h"

#include "CATSysBoolean.h"
#include "CATDialogAgent.h"

//VisualizationInterfaces 
#include "CATPathElement.h"



#include "iostream.h"
#include "CATListPtrCATIAdpPLMIdentificator.h"
#include "CATListPtrCATIPLMNavReference.h"

// ���Ӱ�
// ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

// KnowledgeInterfaces Framework
#include "CATITypeDictionary.h"
//CATPLMIntegrationAccess
#include "CATAdpAttributeSet.h"

//MecModInterfaces Framework
#include "CATIMmiPrtContainer.h"
#include "CATIMmiMechanicalFeature.h"


//CATPLMIdentificationAccess Framework
#include "CATPLMCoreType.h"

//ObjectSpecsModeler Framework
#include "CATIPartRequest.h"

// CATPLMComponentInterfaces Framework
#include "CATIPLMNavInstance.h"
#include "CATIPLMNavRepInstance.h"
#include "CATIPLMNavReference.h"
#include "CATIPLMNavRepReference.h"
#include "CATIPLMNavEntity.h"
#include "CATListPtrCATIPLMNavEntity.h"

// CAT3DPhysicalRepInterfaces Framework
#include "CATIPsiRepresentationLoadMode.h"

// System Framework
#include "CATBaseUnknown.h"
#include "CATUnicodeString.h"

// others
#include "PPRUtity.h"

//MecModInterfaces Framework
#include "CATIPartRequest.h"

#include "CATIMmiUseBodyContent.h"
#include "CATIAlias.h"      // to retrieve a specific body 

#include "CATLISTV_CATBaseUnknown.h" 

#include "CATString.h"


//System Framewrks
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "iostream.h"


#include "CATDlgCheckButton.h"

#define nAsciiCharA 65
#define nAsciiCharZ 90


//-----------------------------------------------------------------------

#define _RETURN_IF_FAILED_(hr, message) \
	if (FAILED(hr)) \
		{ cout << "=== FAILED ===> " << message << endl; return 1; } else	{	cout << "=== OK ===> " << message << endl; }

#define _RETURN_IF_TRUE_(ret, message) \
	if (ret) \
		{ cout << "=== FAILED ===> " << message << endl; return ret; } else	{	cout << "=== OK ===> " << message << endl; }



class ComacNewVersionCmd : public CATStateCommand
{
	DeclareResource(ComacNewVersionCmd, CATStateCommand)
public:
	// Standard constructors and destructors
	// -------------------------------------
	ComacNewVersionCmd();
	virtual ~ComacNewVersionCmd();
	void BuildGraph();

	//
	// TODO: Add your methods for this class here.
	virtual CATBoolean  ActionOne(void * data);

	virtual CATBoolean OKAction(void *data);

	virtual CATBoolean ApplyAction(void *data);

	virtual CATBoolean CancelAction(void *data);

	CATBoolean ElementSelection(void * data);

	void FilterSelectObject();

	CATBoolean CheckSelectObject();

	//  fengy 	2022.1.14 9:32:57  ����
	void RunNewVersion();


private:
	// Copy constructor and equal operator
	// -----------------------------------
	ComacNewVersionCmd(ComacNewVersionCmd &);
	ComacNewVersionCmd& operator=(ComacNewVersionCmd&);

	PPRUtity spPPRUtity;

	ComacNewVersionDlg * _Panel;

	// agent
	CATDialogAgent *_OKAgent;
	CATDialogAgent *_ApplyAgent;
	CATDialogAgent *_CancleAgent;
	CATDialogAgent *_CloseAgent;

	CATPathElementAgent *_pSelectAgent;
	
	CATBaseUnknown        * _pSelectedElement;
	CATIPLMNavOccurrence  * _pSelectedOccurrence;
	CATIPLMNavRepInstance * _pSelectedRepInstance;
	CATIPLMNavReference   * _pSelectedReference;

	// ========= tmp ======= 
	//CATIPLMNavInstance	  * pProductInstance;
	//CATUnicodeString	    _strMAExternal_ID;

	//CATIPLMNavReference *pMASelectedRef;
	//CATIPLMNavOccurrence *pMASelectedOcc;

	// ========= ComacNewVersionCmd ======= 


	CATIPLMNavReference		*pFO_OPFatherRef;
	CATIPLMNavOccurrence	*pFO_OPFatherOcc;



};

//-----------------------------------------------------------------------

#endif
