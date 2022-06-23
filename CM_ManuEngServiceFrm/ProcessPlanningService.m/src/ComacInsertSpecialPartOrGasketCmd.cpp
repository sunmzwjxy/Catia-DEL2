//===================================================================
// COPYRIGHT  2020/09/27
//===================================================================
// ComacInsertSpecialPartOrGasketCmd.cpp
// Header definition of class ComacInsertSpecialPartOrGasketCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/09/27 Creation: Code generated by the 3DS wizard
//===================================================================

#include "ComacInsertSpecialPartOrGasketCmd.h"
#include "CATCreateExternalObject.h"
CATCreateClass(ComacInsertSpecialPartOrGasketCmd);

#include "CATDlgEditor.h"
#include "CATDlgCombo.h"
#include "CATApplicationFrame.h"
#include "CUSCAAUtilService.h"
#include "PPRUtity.h"

//from edu CAAPPRProcessItf.edu\CAAFmiProcessOutput.m\src\CAAFmiProcessOutput.cpp

// DELPPRProcessItf Framework
#include "DELPPRProcessAuthAccess.h"
#include "DELIPPRProcessAuth.h"
#include "DELPPRProcessNavAccess.h"
#include "DELIPPRProcessNav.h"
#include "DELIPPRProcessOutputNav.h"
#include "DELIPPRProcessOutputAuth.h"
//#include "CATIPrdOccurrenceMngt.h"
//#include "CATPrdGetOccurrenceMngt.h" 
#include "DELIPPRProcessPrecedencesAuth.h"

//DELPPRProcessItf
#include "DELIPPRProcessOccAuth.h"
//DELPPRSystemItf
#include "DELIPPRSystemOccAuth.h"


// ProductStructureUseItf  Framework
#include "CATIPrdReferenceFactory.h"
#include "CATPrdFactory.h"
#include "CATIPrd3DPartReferenceFactory.h"
// ProductStructureInterfaces Framework
#include "CATIPLMProducts.h"
//ObjectModelerBase Framework
#include "CATOmbLifeCycleRootsBag.h"

// ProductStructureInterfaces Framework
#include "CATIPrdObject.h"
#include "CATIPLMProducts.h"
#include "CATIPrdIterator.h"
#include "CATIPrdOccurrenceMngt.h"
#include "CATPrdGetOccurrenceMngt.h"

// CATMecModUseItf Framework
#include "CATIMmiUseCreateImport.h"         // To copy mechanical feature
#include "CATMmiUseServicesFactory.h"

#include "DataCommonProtocolServices.h"
#include "CATIUseEntity.h"
#include "CATLISTV_CATIMmiMechanicalFeature.h"

// CATMecModLiveUseItf Framework
#include "CATIMmiMechanicalFeature.h"
#include "CATIBodyRequest.h"
#include "CATIPartRequest.h"
#include "CATIMmiViewServices.h"
#include "CATMmiUseServicesFactory.h"
#include "CATIMmiGeometricalSet.h"

//DataCommonProtocolUse Framework
#include "DataCommonProtocolCCPServices.h"


// VB ʵ��MainBody ��ֵ
#include "CATIABody.h"
#include "CATIAPart.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// CMCreateMBOMAssembly : constructor
//-----------------------------------------------------------------------------
ComacInsertSpecialPartOrGasketCmd::ComacInsertSpecialPartOrGasketCmd() :
	CATStateCommand("ComacInsertSpecialPartOrGasketCmd", CATDlgEngOneShot, CATCommandModeShared)
	, _OKAgent(NULL),
	_ApplyAgent(NULL),
	_CloseAgent(NULL)
{
	//
	//TODO: Add the constructor code here
	CATDlgWindow *pWnd = (CATApplicationFrame::GetFrame())->GetMainWindow();
	_Panel = new ComacInsertSpecialPartOrGasketDlg(pWnd, "MBOM ManufacturingPart");
	_Panel->Build();
	_Panel->SetFather(this);

	//pProvidePartRef = NULL;
	//pProvidePartOcc = NULL;

	pMARootRef = NULL;
	pMARootOcc = NULL;
	pMAFatherRef = NULL;
	pMAFatherOcc = NULL;
	//pMAFatherRef = NULL;
	//pMAFatherOcc = NULL;
	//
	_sPartNo = "";
	_sPartName = "";
}

//-----------------------------------------------------------------------------
// CMCreateMBOMAssembly : destructor
//-----------------------------------------------------------------------------

ComacInsertSpecialPartOrGasketCmd::~ComacInsertSpecialPartOrGasketCmd()
{
	//
	// TODO: Place code here.
	if (_OKAgent != NULL)
	{
		_OKAgent->RequestDelayedDestruction();
		_OKAgent = NULL;
	}

	if (_ApplyAgent != NULL)
	{
		_ApplyAgent->RequestDelayedDestruction();
		_ApplyAgent = NULL;
	}

	if (_CloseAgent != NULL)
	{
		_CloseAgent->RequestDelayedDestruction();
		_CloseAgent = NULL;
	}

	if (_Panel != NULL)
	{
		_Panel->RequestDelayedDestruction();
		_Panel = NULL;
	}

	//pProvidePartRef = NULL;
	//pProvidePartOcc = NULL;

	pMARootRef = NULL;
	pMARootOcc = NULL;
	pMAFatherRef = NULL;
	pMAFatherOcc = NULL;

	_sPartNo = "";
	_sPartName = "";
	//
}


void ComacInsertSpecialPartOrGasketCmd::BuildGraph()
{
	// TODO: Define the StateChart
	// ---------------------------
		// Define the Ok button agent
	_OKAgent = new CATDialogAgent("OK Agent");
	_OKAgent->AcceptOnNotify(_Panel, _Panel->GetDiaOKNotification());

	// Define the Cancel button agent
	_ApplyAgent = new CATDialogAgent("Apply Agent");
	_ApplyAgent->AcceptOnNotify(_Panel, _Panel->GetDiaAPPLYNotification());   //GetDiaAPPLYNotification    

	// Define the Close button agent
	_CloseAgent = new CATDialogAgent("Close Agent");
	_CloseAgent->AcceptOnNotify(_Panel, _Panel->GetWindCloseNotification());    //GetMDICloseNotification    //GetWindCloseNotification

	_CancleAgent = new CATDialogAgent("Cancle Agent");
	_CancleAgent->AcceptOnNotify(_Panel, _Panel->GetDiaCANCELNotification());
	// Define the selection agent
	_pSelectAgent = new CATPathElementAgent("SelectionAgent");

	// Define the behaviors
	_pSelectAgent->SetBehavior(CATDlgEngWithCSO | CATDlgEngWithPrevaluation | CATDlgEngNewHSOManager);   //CATDlgEngMultiAcquisitionCtrl
	AddCSOClient(_pSelectAgent);

	// Define the states
	CATDialogState * pSelectionState = GetInitialState("ElementSelection");
	pSelectionState->AddDialogAgent(_OKAgent);
	pSelectionState->AddDialogAgent(_CloseAgent);
	pSelectionState->AddDialogAgent(_ApplyAgent);
	pSelectionState->AddDialogAgent(_CancleAgent);
	pSelectionState->AddDialogAgent(_pSelectAgent);

	// Transition from Input state to NULL, when click on OK button
	AddTransition(pSelectionState, NULL, AndCondition(IsOutputSetCondition(_OKAgent), Condition((ConditionMethod)&ComacInsertSpecialPartOrGasketCmd::OKAction)), NULL);

	// Transition from Input state to NULL, when click on Cancel button
	AddTransition(pSelectionState, pSelectionState, IsOutputSetCondition(_ApplyAgent), Action((ActionMethod)&ComacInsertSpecialPartOrGasketCmd::ApplyAction));

	// Transition from Input state to NULL, when click on Close button
	AddTransition(pSelectionState, NULL, IsOutputSetCondition(_CloseAgent), Action((ActionMethod)&ComacInsertSpecialPartOrGasketCmd::CancelAction));

	AddTransition(pSelectionState, NULL, IsOutputSetCondition(_CancleAgent), Action((ActionMethod)&ComacInsertSpecialPartOrGasketCmd::CancelAction));

	AddTransition(pSelectionState, pSelectionState, IsOutputSetCondition(_pSelectAgent), Action((ActionMethod)&ComacInsertSpecialPartOrGasketCmd::ElementSelection, NULL, NULL, (void*)1));


	// ��ʼ��д�� dlg
	CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_ProcessPartTypeEditor), "ComacInsertSpecialPartOrGasketDlg", "ProcessPartType.Range", ",");

	CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_PartCodeEditor), "CMMBOMAssemDlg", "PartCode.Range", ",");
	CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_ManufactureLineEditor), "CMMBOMAssemDlg", "ManufactureLine.Range", ",");
	CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_ProcessUnitEditor), "CMMBOMAssemDlg", "ProcessUnit.Range", ",");

	//// ��������  radio �ȴ�
	//_pRadioBtnCopy = _Panel->GetRadioButton(ID_DesignCodeCopy);
	//AddAnalyseNotificationCB(_pRadioBtnCopy, _pRadioBtnCopy->GetRadBModifyNotification(),
	//	(CATCommandMethod)&ComacInsertSpecialPartOrGasketCmd::ChangeRadioNotifyCopy, NULL);

	//_pRadioBtnCopy->SetState(CATDlgCheck);

	//_pRadioBtnInput = _Panel->GetRadioButton(ID_DesignCodeInput);
	//AddAnalyseNotificationCB(_pRadioBtnInput, _pRadioBtnInput->GetRadBModifyNotification(),
	//	(CATCommandMethod)&ComacInsertSpecialPartOrGasketCmd::ChangeRadioNotifyInput, NULL);


	DRECT rect;
	CATBoolean iAlreadyScaled = false;
	_Panel->GetRectDimensionsEx(&rect, iAlreadyScaled);
	rect.x = 800;
	rect.y = 400;
	_Panel->SetRectDimensionsEx(rect, iAlreadyScaled);
	_Panel->SetVisibility(CATDlgShow);

}



//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean ComacInsertSpecialPartOrGasketCmd::ActionOne(void *data)
{
	// TODO: Define the action associated with the transition
	// ------------------------------------------------------

	return TRUE;
}


CATBoolean ComacInsertSpecialPartOrGasketCmd::ElementSelection(void * data)
{
	CATBoolean returnCode = FALSE;

	int CaseAgent = CATPtrToINT32(data);

	// Check input data
	if (NULL != _pSelectAgent)
	{
		// Intialisation
		returnCode = TRUE;
		_pSelectedElement = NULL;
		// Get the selected Element
		CATPathElement * pPathElement = _pSelectAgent->GetValue();
		//pPathElement = _pSelectAgent->GetValue();
		if (NULL != pPathElement)
		{
			_pSelectedElement = pPathElement->FindElement(IID_CATBaseUnknown);
			//_pSelectedRepInstance = (CATIPLMNavRepInstance*)(pPathElement->FindElement(IID_CATIPLMNavRepInstance));
			_pSelectedOccurrence = (CATIPLMNavOccurrence*)(pPathElement->FindElement(IID_CATIPLMNavOccurrence));
			if (_pSelectedOccurrence) {
				_pSelectedOccurrence->GetRelatedReference(_pSelectedReference);
			}
		}
		_pSelectAgent->InitializeAcquisition();

		if (NULL != _pSelectedElement)
		{
			// Highlight the selected Element
			if (FAILED(CUSCAAUtilService::HighlightElement(_pSelectedOccurrence, _pSelectedRepInstance, _pSelectedElement)))
				returnCode = FALSE;

			FilterSelectObject();
		}
		else  returnCode = FALSE;
	}

	return returnCode;
}

void ComacInsertSpecialPartOrGasketCmd::FilterSelectObject()
{
	CATUnicodeString sSelectObjectType = CUSCAAUtilService::GetObjectKnowledgeType(_pSelectedReference);
	cout<<"sSelectObjectType:"<< sSelectObjectType <<endl;

	if (sSelectObjectType == TYPE_MBOMAssembly) //
	{
		pMAFatherOcc = _pSelectedOccurrence;
		pMAFatherRef = _pSelectedReference;
		CATDlgEditor *pEditor = _Panel->GetEditor(ID_SelectCreateAssemblyEditor);
		pEditor->SetText(CUSCAAUtilService::GetObjectAttrValue(pMAFatherRef, "V_Name"));
	}

}


CATBoolean ComacInsertSpecialPartOrGasketCmd::ApplyAction(void *data)
{
	if (_ApplyAgent)
	{
		_ApplyAgent->InitializeAcquisition();
	}

	if (!CheckSelectObject())
	{
		return FALSE;
	}

	InsertSpOrGasket();

	return FALSE;
}


CATBoolean ComacInsertSpecialPartOrGasketCmd::OKAction(void *data)
{
	if (_OKAgent)
	{
		_OKAgent->InitializeAcquisition();
	}

	if (!CheckSelectObject())
	{
		return FALSE;
	}

	InsertSpOrGasket();

	return TRUE;
}

CATBoolean ComacInsertSpecialPartOrGasketCmd::CancelAction(void *data)
{
	if (_Panel != NULL) 
		_Panel->SetVisibility(CATDlgHide);

	return TRUE;
}

CATBoolean ComacInsertSpecialPartOrGasketCmd::CheckSelectObject()
{
	// ��������editor
	CATDlgEditor *pEditor1 = _Panel->GetEditor(ID_ProcessPartNoEditor);
	_sPartNo = pEditor1->GetText();
	cout << "_sPartNo:" << _sPartNo << endl;

	CATDlgEditor *pEditor2 = _Panel->GetEditor(ID_ProcessPartNameEditor);
	_sPartName = pEditor2->GetText();
	cout << "_sPartName:" << _sPartName << endl;


	CATUnicodeString tmpErrorStr = "";
	if (pMAFatherOcc == NULL)
		tmpErrorStr.Append("��ѡ������װ�������ڵ���Ϊ�����ڵ㣡\n");

	if(_sPartNo.GetLengthInChar() == 0)
		tmpErrorStr.Append("����д�����ռ���ţ�Process Part No.����\n");
	if (_sPartName.GetLengthInChar() == 0)
		tmpErrorStr.Append("����д�����ռ����ƣ�Process Part Name����\n");

	if (tmpErrorStr.GetLengthInChar() > 0)
	{
		cout<< "#Error CheckSelectObject: "<<tmpErrorStr <<endl;
		CUSCAAUtilService::Notify(tmpErrorStr);
		return false;
	}
	else
		cout << "#OK CheckSelectObject:  ����OK��"  << endl;


	// ��ȡroot MA Occ
	pMARootOcc = CUSCAAUtilService::GetRootOcc(pMAFatherOcc);
	if (pMARootOcc != NULL)
	{
		pMARootOcc->GetRelatedReference(pMARootRef);
	}

	return TRUE;

}

// fengy 2021.12.22 ���붯�� Run
void ComacInsertSpecialPartOrGasketCmd::InsertSpOrGasket()
{
	HRESULT rc = E_FAIL;
	CATUnicodeString tmpMsg;

	// 1-  У���ŵ�Ψһ�� _sPartNo 
	CATUnicodeString iKey = "PLM_ExternalID";
	CATUnicodeString strTitle = _sPartNo /*"mass-14182662-00003448"*/ /*"prd-14182662-00097964"*/;
	strTitle = strTitle + "*";

	CATUnicodeString strType = TYPE_ManufacturingMat;									// CreateAssembly

	CATUnicodeString strRevision = "";													// �汾��ʵ�ǣ� A.1
	CATListPtrCATIPLMNavReference opilistIDComp;

	/*rc =*/ CUSCAAUtilService::GetObjReference(strTitle, strRevision, opilistIDComp, strType, iKey);
	//if (FAILED(rc))
	//{
	//	cout << "# ==== FAILED  ==== >>  InsertSpOrGasket - GetObjReference ! " << endl;
	//	CUSCAAUtilService::Notify("��̨����KO��GetObjReference��");
	//	return;
	//}
	//cout << "# ==== OK ==== >>  InsertSpOrGasket - GetObjReference ! " << endl;

	int nIDsExist = opilistIDComp.Size();
	if ( nIDsExist > 0)
	{
		tmpMsg = "��ţ�"+ _sPartNo  +"*����Ψһ�������������ţ�";
		CUSCAAUtilService::Notify(tmpMsg);
		return;
	}
	tmpMsg = "��ţ�" + _sPartNo + "*��Ψһ����ʼ���� ������ Run��";

	cout << tmpMsg << endl;

	// 2- ���붯�� Run
	CATIPLMNavOccurrence *pNewMAMaterialOcc;
	PPRUtity sPPRUtity;
	sPPRUtity.CreateSubMAAssembly(TYPE_ManufacturingMat, pMAFatherOcc, pMARootRef, pNewMAMaterialOcc);
	if (pNewMAMaterialOcc == NULL)
	{
		tmpMsg = "FAILED at ====> CreateSubMAAssembly " + TYPE_ManufacturingMat +"\n";
		cout<< tmpMsg <<endl;
		CUSCAAUtilService::Notify(tmpMsg);
		return ;
	}
	else
	{
		tmpMsg = "OK ====> CreateSubMAAssembly " + TYPE_ManufacturingMat + "\n";
		cout << tmpMsg << endl;
	}

	// 3- д���ԣ�
	CATIPLMNavReference *pNewMAMaterialRef = NULL;
	pNewMAMaterialOcc->GetRelatedReference(pNewMAMaterialRef);
	CATIPLMNavInstance *pNewMAMaterialInst = NULL;
	pNewMAMaterialOcc->GetRelatedInstance(pNewMAMaterialInst);

	// title
	CATUnicodeString sPartType = CUSCAAUtilService::GetSelectComboValue(_Panel->GetCombo(ID_ProcessPartTypeEditor));
	cout << "#sPartType:" << sPartType << endl;

	cout << "# MAMaterial Ref title ǰ:     " << CUSCAAUtilService::GetObjectAttrValue(pNewMAMaterialRef, "V_Name") << endl;
	CUSCAAUtilService::SetObjectAttrString(pNewMAMaterialRef, "V_Name", _sPartName);
	cout << "# MAMaterial Ref title ��:     " << CUSCAAUtilService::GetObjectAttrValue(pNewMAMaterialRef, "V_Name") << endl;
	CUSCAAUtilService::SetObjectAttrString(pNewMAMaterialRef, "PLM_ExternalID", _sPartNo);


	cout << "# MAMaterial inst title ǰ:     " << CUSCAAUtilService::GetObjectAttrValue(pNewMAMaterialInst, "PLM_ExternalID") << endl;
	CUSCAAUtilService::SetObjectAttrString(pNewMAMaterialInst, "PLM_ExternalID", _sPartName + ".1");
	cout << "# MAMaterial inst title ��:     " << CUSCAAUtilService::GetObjectAttrValue(pNewMAMaterialInst, "PLM_ExternalID") << endl;

	// ���� ������롢����·�ߡ�ʹ�õ�λ
	CUSCAAUtilService::SetObjectAttrString(pNewMAMaterialRef, "CUS_PartCode", CUSCAAUtilService::GetSelectComboValue(_Panel->GetCombo(ID_PartCodeEditor)));
	CUSCAAUtilService::SetObjectAttrString(pNewMAMaterialRef, "CUS_ManufactureLine", CUSCAAUtilService::GetSelectComboValue(_Panel->GetCombo(ID_ManufactureLineEditor)/*, "CMMBOMAssemDlg", "ManufactureLineKey.Range", ","*/));
	CUSCAAUtilService::SetObjectAttrString(pNewMAMaterialRef, "CUS_ProcessUnit", CUSCAAUtilService::GetSelectComboValue(_Panel->GetCombo(ID_ProcessUnitEditor)));

	// type ��д�� description
	CUSCAAUtilService::SetObjectAttrString(pNewMAMaterialRef, "V_description", sPartType);


	// 4- ���£�

	return ;
}


// ��� BU toRef fengy 2021.11.18
CATIPLMNavReference_var  ComacInsertSpecialPartOrGasketCmd::FromBUToRef(CATBaseUnknown * ipNewProdBU)			// BU ת�� ref��ko��
{
	CATIPLMNavReference_var ospNavRef ;

	// ��һ  ò�Ʋ��Ƽ�
	CATIPrdObject_var spPrdObject = ipNewProdBU;
	ReleasePtr(ipNewProdBU);

	if (NULL_var != spPrdObject)
	{
		CATIPLMNavReference* pNavRef = NULL;
		HRESULT rc = spPrdObject->GetReferenceObject((CATBaseUnknown*&)pNavRef,IID_CATIPLMNavReference);
		if (/*SUCCEEDED(rc) && */   NULL != pNavRef)
		{
			cout << "    # FromBUToRef 1111111111" << endl;
			ospNavRef = pNavRef;
			if (NULL_var != ospNavRef)
				cout << "    # FromBUToRef OK��" << endl;
			else
				cout << "    # FromBUToRef KO 3��" << endl;
		}
		else
			cout << "    # FromBUToRef KO1��" << endl;
	}
	else
		cout << "    # FromBUToRef KO2��" << endl;

	//// ����
	//CATIPLMNavOccurrence *pNavOccOnSelObj = NULL;
	//HRESULT rc = ipNewProdBU->QueryInterface(IID_CATIPLMNavOccurrence, (void**)&pNavOccOnSelObj);

	//if (SUCCEEDED(rc))
	//{
	//	CATIPLMNavReference * pRef = NULL;
	//	pNavOccOnSelObj->GetRelatedReference(pRef);
	//	if (NULL != pRef)
	//	{
	//		ospNavRef = pRef;
	//		if (NULL_var != ospNavRef)
	//			cout << " GetRelatedReference OK! " << endl;
	//		else
	//			cout << "    # FromBUToRef KO 3��" << endl;
	//	}
	//	else
	//		cout << "    # FromBUToRef KO 1��" << endl;
	//}
	//else
	//	cout << "    # FromBUToRef KO 2��" << endl;

	return ospNavRef;
}



void ComacInsertSpecialPartOrGasketCmd::DeleteFeature(CATBaseUnknown_var spObj)
{
	CATIUseEntity_var spUseEntity = spObj;
	if (NULL_var != spUseEntity)
	{
		DataCommonProtocolServices::Delete(spUseEntity);
		cout << " DeleteFeature : " << CUSCAAUtilService::GetAliasName(spObj)<< endl;
	}
}

void ComacInsertSpecialPartOrGasketCmd::UpdateFeature(CATBaseUnknown_var spObj)
{
	CATIUseEntity_var spUseEntity = spObj;
	if (NULL_var != spUseEntity)
	{
		DataCommonProtocolServices::Update(spUseEntity);
	}
}

// ******************** ������  Start *********************

void ComacInsertSpecialPartOrGasketCmd::ReleasePtr(CATBaseUnknown * piCBU)
{
	if (NULL != piCBU)
	{
		piCBU->Release();
		piCBU = NULL;
	}
}

int ComacInsertSpecialPartOrGasketCmd::FindReference( CATOmbLifeCycleRootsBag & iLifeCycleBag,
										const CATAdpAttributeSet & iAttributeSet,
										CATIType * ipModelerType,
										const IID & iIID,
										void ** oppReference)
{
	HRESULT hr = E_FAIL;

	CATLISTP(CATAdpQueryResult) QueryResults;
	hr = CATAdpPLMQueryServices::GetElementsFromAttributes(ipModelerType, iAttributeSet, QueryResults);

	if (FAILED(hr)) return 1;

	// If several object match with this query we open only the first one.
	int NbResult = QueryResults.Size();
	if (1 <= NbResult)
	{
		CATAdpQueryResult * pQueryResult = QueryResults[1];
		if (NULL != pQueryResult)
		{
			CATIAdpPLMIdentificator * piPLMId = NULL;
			hr = pQueryResult->GetIdentifier(piPLMId);

			if (SUCCEEDED(hr) && NULL != piPLMId)
			{
				CATAdpOpener opener(iLifeCycleBag);			// �˴�Ϊ��ָ������ lifebag��
				hr = opener.CompleteAndOpen(piPLMId, iIID, oppReference);
			}
			if (NULL != piPLMId)
			{
				piPLMId->Release();
				piPLMId = NULL;
			}
		}
		for (int ind = 1; ind <= NbResult; ++ind)		// ע��ÿ�����ͷţ� ���������й¶ 
		{
			CATAdpQueryResult * pQueryResult = QueryResults[ind];
			if (NULL != pQueryResult)
			{
				delete pQueryResult;
				pQueryResult = NULL;
			}
		}
	}
	else return 1;

	if (FAILED(hr)) return 1;

	return 0;
}

// from Process ref to Occ
HRESULT ComacInsertSpecialPartOrGasketCmd::GetOccurrenceFromProcessReference(
	const CATIPLMNavReference_var & ihNavRef,
	CATIPLMNavOccurrence_var & ohNavOcc)
{
	DELIPPRProcessOccAuth* pProcessAuthService = getDELIPPRProcessOccAuth();
	DELIPPRProcessOccAuth_var hProcessOccAuth(pProcessAuthService);
	ReleasePtr(pProcessAuthService);
	if (hProcessOccAuth == NULL_var) return E_FAIL;

	CATIPLMNavOccurrence * pNavOcc = NULL;
	HRESULT rc = hProcessOccAuth->GetOrCreateRootOccurrence(ihNavRef, pNavOcc);
	ohNavOcc = pNavOcc;
	ReleasePtr(pNavOcc);
	return rc;
}


HRESULT ComacInsertSpecialPartOrGasketCmd::CAAMmrGetPartFromProduct(CATIPLMNavInstance_var   spNavInstance, CATIPartRequest_var  & ospPartFromProduct)

{
	HRESULT rc = E_FAIL;

	if (NULL_var == spNavInstance) return E_FAIL;

	// Retrieve the reference of the current instance
	CATIPLMNavReference *pReferenceOfInstance = NULL;
	rc = spNavInstance->GetReferenceInstanceOf(pReferenceOfInstance);

	// Retrieve the first inst rep ref
	//	inst - ref - repInst(s) - RepRef - PrtCont - CATIMmiMechanicalFeature(prtPart)
	CATIPLMNavRepInstance * pNavRepInst = NULL;
	if (NULL != pReferenceOfInstance)
	{
		CATListPtrCATIPLMNavEntity ListNavEntity = NULL;
		CATPLMCoreType TypeRepInstance = PLMCoreRepInstance;
		pReferenceOfInstance->ListChildren(ListNavEntity, 1, &TypeRepInstance);

		if (ListNavEntity.Size() >= 1)
		{
			CATIPLMNavEntity *pCurrent = ListNavEntity[1];
			rc = pCurrent->QueryInterface(IID_CATIPLMNavRepInstance, (void**)& pNavRepInst);	// RepInst
		}
		for (int i = 1; i <= ListNavEntity.Size(); i++)
		{
			CATIPLMNavEntity *pCurrent = ListNavEntity[1];
			if (NULL != pCurrent)
			{
				pCurrent->Release(); pCurrent = NULL;
			}
		}
		pReferenceOfInstance->Release(); pReferenceOfInstance = NULL;
	}

	// Retrieve the reference of the first inst rep ref
	CATIPLMNavRepReference *pNavRepRef = NULL;
	if (NULL != pNavRepInst)
	{
		rc = pNavRepInst->GetRepReferenceInstanceOf(pNavRepRef);
		pNavRepInst->Release(); pNavRepInst = NULL;
	}

	// change the loading mode
	if (NULL != pNavRepRef)
	{
		CATIPsiRepresentationLoadMode *piRepLoadMode = NULL;
		rc = pNavRepRef->QueryInterface(IID_CATIPsiRepresentationLoadMode, (void **)&piRepLoadMode);

		if (SUCCEEDED(rc) && NULL != piRepLoadMode)
		{
			rc = piRepLoadMode->ChangeLoadingMode(CATIPsiRepresentationLoadMode::EditMode);
			piRepLoadMode->Release();
			piRepLoadMode = NULL;
		}
	}

	//Retrieve the applicative container
	CATIMmiPrtContainer * pContainer = NULL;
	if (SUCCEEDED(rc) && (NULL != pNavRepRef))
	{
		rc = pNavRepRef->RetrieveApplicativeContainer("CATPrtCont", IID_CATIMmiPrtContainer, (void **)&pContainer);
	}

	if (SUCCEEDED(rc) && (NULL != pContainer))
	{
		CATIMmiMechanicalFeature_var spMechFeatOnPart;
		rc = pContainer->GetMechanicalPart(spMechFeatOnPart);

		if (SUCCEEDED(rc) && (NULL_var != spMechFeatOnPart))
			ospPartFromProduct = spMechFeatOnPart;
	}

	if (NULL != pContainer)
	{
		pContainer->Release();  pContainer = NULL;
	}

	if (NULL != pNavRepRef)
	{
		pNavRepRef->Release(); pNavRepRef = NULL;
	}


	if (NULL_var == ospPartFromProduct)
		return E_FAIL;
	else return S_OK;

}

HRESULT ComacInsertSpecialPartOrGasketCmd::CAAMmrGetGeometry(CATIPartRequest_var ispModelPart, const CATUnicodeString iInputName,
	CATBaseUnknown ** oInput)
{
	HRESULT rc = E_FAIL;
	CATBoolean found = FALSE;

	if ((NULL != oInput) && (NULL_var != ispModelPart))
	{
		*oInput = NULL;

		// Retrieves all root bodies , all GS and all root OGS ( it does not retrieve ALL bodies below the Part)
		CATListValCATBaseUnknown_var pListBodies;
		rc = ispModelPart->GetAllBodies("", pListBodies);
		if (SUCCEEDED(rc))
		{
			int iBodies = 1;
			int nbbodies = pListBodies.Size();

			while ((FALSE == found) && (iBodies <= nbbodies))
			{
				CATIAlias_var spAliasBody = pListBodies[iBodies];
				if (NULL_var != spAliasBody)
				{
					CATUnicodeString currentbodyname = spAliasBody->GetAlias();

					if (iInputName == currentbodyname)
					{
						// We have found a body
						found = TRUE;
						rc = spAliasBody->QueryInterface(IID_CATBaseUnknown, (void**)&(*oInput));
					}
					else
					{
						// Research in the body
						CATIMmiUseBodyContent_var spUseBodyContentOnBody = spAliasBody;
						if (spUseBodyContentOnBody != NULL_var)
						{
							// Retrieve all geometrical element in the body 
							CATListValCATBaseUnknown_var ListFeatureInsideCurrentBody;
							spUseBodyContentOnBody->GetMechanicalFeatures(ListFeatureInsideCurrentBody);
							int nbchild = ListFeatureInsideCurrentBody.Size();

							int iChild = 1;
							while ((FALSE == found) && (iChild <= nbchild))
							{
								CATIAlias_var spChild = ListFeatureInsideCurrentBody[iChild];
								if (NULL_var != spChild)
								{
									CATUnicodeString currentchildname = spChild->GetAlias();

									if (iInputName == currentchildname)
									{
										// we have found a child of a body
										found = TRUE;
										rc = spChild->QueryInterface(IID_CATBaseUnknown, (void**)&(*oInput));
									}
								}
								iChild++;
							}
						}
					}
				}
				iBodies++;
			}
		}

	}

	if (TRUE == found)
	{
		rc = S_OK;
	}
	else rc = E_FAIL;

	return rc;
}


// ******************** ������  End *********************

