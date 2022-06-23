//===================================================================
// COPYRIGHT  2020/09/27
//===================================================================
// ComacGenerateBOMCmd.cpp
// Header definition of class ComacGenerateBOMCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/09/27 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef ComacGenerateBOMCmd_H
#define ComacGenerateBOMCmd_H

//#include "ProcessPlanningService.h"
#include "CATStateCommand.h"

#include "ComacGenerateBOMDlg.h"
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

// 添加包
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
#include "iostream.h"
//MecModInterfaces Framework
#include "CATIPartRequest.h"

#include "CATIMmiUseBodyContent.h"
#include "CATIAlias.h"      // to retrieve a specific body 

#include "CATLISTV_CATBaseUnknown.h" 

//System Framewrks
#include "CATBoolean.h"
#include "CATUnicodeString.h"
#include "iostream.h"

//-----------------------------------------------------------------------

#define _RETURN_IF_FAILED_(hr, message) \
	if (FAILED(hr)) \
		{ cout << "=== FAILED ===> " << message << endl; return 1; } else	{	cout << "=== OK ===> " << message << endl; }

#define _RETURN_IF_TRUE_(ret, message) \
	if (ret) \
		{ cout << "=== FAILED ===> " << message << endl; return ret; } else	{	cout << "=== OK ===> " << message << endl; }



class ComacGenerateBOMCmd : public CATStateCommand
{
	DeclareResource(ComacGenerateBOMCmd, CATStateCommand)
public:
	// Standard constructors and destructors
	// -------------------------------------
	ComacGenerateBOMCmd();
	virtual ~ComacGenerateBOMCmd();

	//
	// TODO: Add your methods for this class here.
	virtual CATBoolean  ActionOne(void * data);

	virtual CATBoolean OKAction(void *data);

	virtual CATBoolean ApplyAction(void *data);

	virtual CATBoolean CancelAction(void *data);

	CATBoolean ElementSelection(void * data);

	CATBoolean CheckSelectObject();

	void BuildGraph();

	//   fengy 2021.12.9  创建协作BOM 规划 
	HRESULT CrateMbomStructure();

	// fengy 2021.12.10 添加空的product 装配节点
	HRESULT AddOneBlankProduct(CATIPLMNavReference * ipProductFatherRef, CATUnicodeString iStrPartNo, CATUnicodeString iStrInstName, CATBaseUnknown *& opPrdInstanceBU);

	// fengy 2021.12.10 改写 CAAProductStructure.edu\CAAPstBrowsingProductModel.m\src\CAAPstBrowsingProductModel.cpp 
	//  浏览maRef结构，添加到CAD的结构上复现！
	HRESULT BrowseMARef2CADTree(CATIPLMNavOccurrence* ipMAOcc, CATIPLMNavOccurrence * iRootProcessOcc, int iDepth, CATIPLMNavReference * ipProductFatherRef);
	
	//fengy 2021.12.1 根据 ref \ contextFatherOcc 获取Occ 
	CATIPLMNavOccurrence_var GetOccFromRef(CATIPLMNavOccurrence_var ispOccOnFarther, CATIPLMNavReference_var ispRef);


	// ******************** 几个包 *********************
	
	int FindReference(CATOmbLifeCycleRootsBag & iLifeCycleBag,
		const CATAdpAttributeSet & iAttributeSet,
		CATIType * ipModelerType,
		const IID & iIID,
		void ** oppReference);

	void ReleasePtr(CATBaseUnknown * piCBU);

	HRESULT GetOccurrenceFromProcessReference(const CATIPLMNavReference_var & ihNavRef, CATIPLMNavOccurrence_var & ohNavOcc);

	CATUnicodeString GetAliasName(CATBaseUnknown * ipBaseUnknown);


	// 自行添加 module 一直 KO! 没办法 只能添加在函数内部！
	HRESULT CAAMmrGetPartFromProduct(CATIPLMNavInstance_var   spNavInstance, CATIPartRequest_var  & ospPartFromProduct);

	HRESULT CAAMmrGetGeometry(CATIPartRequest_var ispModelPart, const CATUnicodeString iInputName,
		CATBaseUnknown ** oInput);


	// 解决 BU toRef fengy 2021.11.18
	CATIPLMNavReference_var  FromBUToRef(CATBaseUnknown * ipNewProdRef);

	void DeleteFeature(CATBaseUnknown_var spObj);
	void UpdateFeature(CATBaseUnknown_var spObj);


	// ******************** 几个包 *********************
	void FilterSelectObject();

	//CATBoolean ChangeRadioNotifyCopy(void *data);

	//CATBoolean ChangeRadioNotifyInput(void *data);
	//

private:
	// Copy constructor and equal operator
	// -----------------------------------
	ComacGenerateBOMCmd(ComacGenerateBOMCmd &);
	ComacGenerateBOMCmd& operator=(ComacGenerateBOMCmd&);

	ComacGenerateBOMDlg *_Panel;

	CATUnicodeString iManuPartType;
	CATUnicodeString sPartExternalId;

	CATDialogAgent *_OKAgent;
	CATDialogAgent *_ApplyAgent;
	CATDialogAgent *_CancleAgent;
	CATDialogAgent *_CloseAgent;

	CATPathElementAgent *_pSelectAgent;

	//CATDlgRadioButton *_pRadioBtnCopy;
	//CATDlgRadioButton *_pRadioBtnInput;

	CATBaseUnknown        * _pSelectedElement;
	CATIPLMNavOccurrence  * _pSelectedOccurrence;
	CATIPLMNavRepInstance * _pSelectedRepInstance;
	CATIPLMNavReference   * _pSelectedReference;

	//CATIPLMNavReference *pProvidePartRef;
	//CATIPLMNavOccurrence *pProvidePartOcc;

	//CATIPLMNavOccurrence * pNewManuPartOcc;		// create 空的 MA Process Occ

	//CATIPLMNavReference *pMARootRef;
	//CATIPLMNavOccurrence *pMARootOcc;

	CATIPLMNavInstance *pProductInstance;
	CATUnicodeString	 _strMAExternal_ID;


	CATIPLMNavReference *pMASelectedRef;
	CATIPLMNavOccurrence *pMASelectedOcc;

	CATIPLMNavReference *pProductFatherRef;
	CATIPLMNavOccurrence *pProductFatherOcc;


};

//-----------------------------------------------------------------------

#endif
