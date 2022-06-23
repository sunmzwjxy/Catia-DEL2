//===================================================================
// COPYRIGHT  2020/09/22
//===================================================================
// PPRUtity.cpp
// Header definition of class PPRUtity
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/09/22 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef PPRUtity_H
#define PPRUtity_H
#include "CATBaseUnknown.h"

#include <iostream>
using namespace std;

#include "DELIPPRUIServices.h"			// 窗口下搜索maroot

// DELWkiExposeUseItf
#include "DELIWKIAttributeMgt.h"
#include "DELIWKIInstructionAuthoring.h"

// DELPPRSystemItf
#include "CATITypeDictionary.h"
#include "CATGlobalFunctions.h"

#include "DELIPPRSystemAuth.h"
#include "DELPPRSystemAuthAccess.h"
#include "DELIPPRSystemOccAuth.h"
#include "CATListPtrCATIPLMNavInstance.h"
#include "DELIPPRSystemProductFlowAuth.h"

#include "CATListPtrCATIPLMNavInstance.h"
#include "CATOmbLifeCycleRootsBag.h"

//DELPPRAuthFoundationInterfaces 
#include "DELPPRUIServicesAccess.h"
#include "DELIPPRUIServices.h"

//DELPPRProcessItf 
#include "DELPPRProcessNavAccess.h"
#include "DELIPPRProcessNav.h"
#include "DELIPPRProcessAuth.h"
#include "DELPPRProcessAuthAccess.h"

#include "CATCkePLMNavPublicServices.h"
#include "CUSCAAUtilService.h"
#include "CATAdpSaver.h"
#include "DELIPPRSystemAndOperationInstancesAuth.h"
#include "DELIPPRSystemProductFlowAuth.h"
#include "CATAdpSaver.h"

// XMLParser
#include "CATIDOMElement.h"
#include "CATIDOMImplementation.h"
#include "CATIDOMText.h"
#include "CATListOfCATUnicodeString.h"
#include "CATIDOMDocumentType.h"
#include "CATIXMLSAX2Factory.h"
#include "CATIDOMNodeList.h"
#include "CATIDOMNode.h"

#include "CATAdpPublicSecurityServices.h"
//-----------------------------------------------------------------------
static CATUnicodeString TYPE_ManufacturingPart = "ElementaryEndItem";
static CATUnicodeString TYPE_ManufacturingMat = "CreateMaterial";		// type名字？
static CATUnicodeString TYPE_ProvidePart = "Provide";
static CATUnicodeString TYPE_MBOMAssembly = "CreateAssembly";
static CATUnicodeString TYPE_MBOMKit = "CreateKit";
static CATUnicodeString TYPE_MBOMFasten = "CUS_Fasten";
static CATUnicodeString TYPE_System = "DELLmiGeneralSystemReference";
static CATUnicodeString TYPE_GWSystem = "CUS_GWSystemRef";
static CATUnicodeString TYPE_ZWSystem = "CUS_ZWSystemRef";
static CATUnicodeString TYPE_AOSystem = "CUS_HeaderOperation_AO";   //CUS_AO_OperationRef   CUS_AOSystemRef
static CATUnicodeString TYPE_Product = "VPMReference";

static CATUnicodeString TYPE_Workplan = "DELLmiWorkPlanSystemReference";
static CATUnicodeString TYPE_GW_Workplan = "CUS_Workplan_GW";
static CATUnicodeString TYPE_ZW_Workplan = "CUS_Workplan_ZW";


// fengy 2021.12.14
static CATUnicodeString TYPE_FO_OP = "CUS_FO_OP";										// CUS_FO_OP     operation
static CATUnicodeString TYPE_GeneralOperation = "DELLmiGeneralOperationReference";		// GeneralOperation     
static CATUnicodeString TYPE_CUS_FO_Workplan = "CUS_FO";								// CUS_FO        workplan
static CATUnicodeString TYPE_Instruction_Workplan = "DELWkiInstructionReference";		// Instruction



static CATUnicodeString splitNameChar = "-";

static CATUnicodeString splitFastenChar = "@@";


enum PPRUtity_ControlID
{
	ID_WIAlertType = 0,
	ID_WIDataCollectType,
	ID_WISignOffType,
	ID_WIInstructionType
};


class PPRUtity : public CATBaseUnknown
{
public:
// Standard constructors and destructors
// -------------------------------------
PPRUtity ();
virtual ~PPRUtity ();

//
// TODO: Add your methods for this class here.
HRESULT CreateSubSystemOrOperation(const CATUnicodeString &iTypeName,
	CATIPLMNavReference *&iParentRef,
	CATIPLMNavInstance  *&pNavInstOp);

HRESULT GetOccFromSystemFather(CATIPLMNavOccurrence *ipSystemFatherOcc,
	CATIPLMNavInstance *ipNavInstSubSys, CATIPLMNavOccurrence *&opSubSystemOcc);

HRESULT CreateSubMAAssembly(const CATUnicodeString iTypeName,
	CATIPLMNavOccurrence *iParentOcc, CATIPLMNavReference *iRootRef,
	CATIPLMNavOccurrence *&pNavOccOp);

HRESULT InsertExistSystem(CATBaseUnknown * ipFatherSystem, CATBaseUnknown * ipChildSystem, 
	CATBaseUnknown *& opInstance);

HRESULT InsertExistProcess(CATIPLMNavOccurrence *iParentOcc, CATIPLMNavReference *piNavRefProcess,
	CATIPLMNavReference *iRootRef, CATIPLMNavOccurrence *&pNavOccOp);

CATUnicodeString NextFormatCode(CATUnicodeString iObjectType, CATUnicodeString iExternalID, 
	CATUnicodeString iFormatChar);

HRESULT CopyProductScope(CATIPLMNavReference *ipSourceRef, CATIPLMNavReference *iTargetRef);

HRESULT AssignProduct(CATIPLMNavOccurrence * spMBOMOcc,
	CATIPLMNavOccurrence * spProductOcc);

HRESULT CopyProductAssignment(CATIPLMNavOccurrence * iSourceMIDOcc, CATIPLMNavReference * iCtxProductRootRef,
	CATIPLMNavOccurrence * iTargetMIDOcc);

HRESULT CopyProcessStructureAssignment(CATIPLMNavOccurrence * spSourceProcessOcc,
	CATIPLMNavOccurrence * spTargetProcessOcc, CATIPLMNavReference * spProcessRootRef, CATIPLMNavReference * spProductRootRef);

CATListValCATBaseUnknown_var getCurrentPPREditorRootRef(CATUnicodeString sPPRType);

CATUnicodeString NextRevisionCode(CATUnicodeString iObjectRevision);

CATBoolean CheckNumberChar(CATUnicodeString inputCode, int charNumber);

CATBoolean CheckNum(CATUnicodeString inputCode);

CATBoolean CheckCapitalChar(CATUnicodeString inputCode);

CATBoolean CheckLowercaseChar(CATUnicodeString inputCode);

// fengy 2021.12.15  CreateInsertWorkInstruction
HRESULT CreateInsertWorkInstruction(CATIPLMNavOccurrence_var ihParentOpOcc, int iWkiTypeID = ID_WIInstructionType);

// from edu:	E:\00dev\dev_3DE_2020\1_edu\CAADELWkiExposeUseItf\CAADELWkiExposeUseItf.edu\CAAWKINavAuth.m\src\CAAWKINavAuth.cpp
CATIPLMNavReference_var GetRefFromOcc(CATIPLMNavOccurrence_var &ihNavOcc);

// fengy 2021.12.15  System rootref - rootOcc
HRESULT GetRootOccFromSystemReference(const CATIPLMNavReference_var ispRootSystemRef, CATIPLMNavOccurrence_var & ospRootSysOcc);

// fengy 2021.12.15 获取当前窗口下的 Root节点 enum Type
//PRODUCTProduct PPR root  PROCESSProcess PPR root  SYSTEMSystem PPR root  RESOURCEResource PPR root
HRESULT GetPPRRootRefNodeFromCurrentEditor(int iType, CATIPLMNavReference_var & ospRootRef);

// 解决 BU toRef fengy 2021.11.18
CATIPLMNavReference_var  FromBUToRef(CATBaseUnknown * ipNewProdBU);

void ReleasePtr(CATBaseUnknown * piCBU);
//

private:
// Copy constructor and equal operator
// -----------------------------------
PPRUtity (PPRUtity &);
PPRUtity& operator=(PPRUtity&);

};



//-----------------------------------------------------------------------

#endif
