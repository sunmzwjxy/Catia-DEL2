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

#include "CMChangeMBOMAssemCmd.h"
#include "CUSCAAUtilService.h"
#include "PPRUtity.h"

#include "CATCreateExternalObject.h"
CATCreateClass(CMChangeMBOMAssemCmd);
//-----------------------------------------------------------------------------
// CMChangeMBOMAssemCmd : constructor
//-----------------------------------------------------------------------------
CMChangeMBOMAssemCmd::CMChangeMBOMAssemCmd():CATStateCommand()
{
//
//TODO: Add the constructor code here
	CATDlgWindow *pWnd = (CATApplicationFrame::GetFrame())->GetMainWindow();
	_Panel = new CMChangeAssemDlg(pWnd, "MBOM 401 Component");
	_Panel->Build();
	_Panel->SetFather(this);

	pMIDComponentRef = NULL;
	pMIDComponentOcc = NULL;
	pReviseMIDOcc = NULL;
	pReviseMIDRef = NULL;
	pMAFatherOcc = NULL;
	pMAFatherRef = NULL;
	pMARootOcc = NULL;
	pMARootRef = NULL;
	pFatherMIDOcc = NULL;
	pFatherMIDRef = NULL;

	_ComponentBtn = NULL;
	_FatherCompBtn = NULL;

	selectFlag = 1;
//
}

//-----------------------------------------------------------------------------
// CMChangeMBOMAssemCmd : destructor
//-----------------------------------------------------------------------------

CMChangeMBOMAssemCmd::~CMChangeMBOMAssemCmd()
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

	pMIDComponentRef = NULL;
	pMIDComponentOcc = NULL;
	pReviseMIDOcc = NULL;
	pReviseMIDRef = NULL;
	pMAFatherOcc = NULL;
	pMAFatherRef = NULL;
	pMARootOcc = NULL;
	pMARootRef = NULL;
	pFatherMIDOcc = NULL;
	pFatherMIDRef = NULL;

	_ComponentBtn = NULL;
	_FatherCompBtn = NULL;
//
}

void CMChangeMBOMAssemCmd::BuildGraph()
{
	// TODO: Define the StateChart
	// ---------------------------
		// Define the Ok button agent
	_OKAgent = new CATDialogAgent("OK Agent");
	_OKAgent->AcceptOnNotify(_Panel, _Panel->GetDiaOKNotification());

	// Define the Cancel button agent
	_ApplyAgent = new CATDialogAgent("Apply Agent");
	_ApplyAgent->AcceptOnNotify(_Panel, _Panel->GetDiaAPPLYNotification());   //GetDiaAPPLYNotification     //GetDiaCANCELNotification 

	// Define the Close button agent
	_CloseAgent = new CATDialogAgent("Close Agent");
	_CloseAgent->AcceptOnNotify(_Panel, _Panel->GetWindCloseNotification());    //GetWindCloseNotification

	
	_CancleAgent = new CATDialogAgent("Cancle Agent");
	_CancleAgent->AcceptOnNotify(_Panel, _Panel->GetDiaCANCELNotification());

	// Define the selection agent
	_pSelectAgent = new CATPathElementAgent("Selection 401 Component Agent");
	_pSelectAgent->SetBehavior(CATDlgEngWithCSO | CATDlgEngWithPrevaluation | CATDlgEngNewHSOManager);   //CATDlgEngMultiAcquisitionCtrl
	AddCSOClient(_pSelectAgent);

	// Define the selection agent
	_pSelectCompFatherAgent = new CATPathElementAgent("Selection 401 Component Father Agent");
	_pSelectCompFatherAgent->SetBehavior(CATDlgEngWithCSO | CATDlgEngWithPrevaluation | CATDlgEngNewHSOManager);   //CATDlgEngMultiAcquisitionCtrl
	AddCSOClient(_pSelectCompFatherAgent);

	// Define the states
	CATDialogState * pSelectionState = GetInitialState("ElementSelection");
	pSelectionState->AddDialogAgent(_OKAgent);
	pSelectionState->AddDialogAgent(_CloseAgent);
	pSelectionState->AddDialogAgent(_ApplyAgent);
	pSelectionState->AddDialogAgent(_CancleAgent);
	pSelectionState->AddDialogAgent(_pSelectAgent);
	pSelectionState->AddDialogAgent(_pSelectCompFatherAgent);

	// Transition from Input state to NULL, when click on OK button
	AddTransition(pSelectionState, NULL, AndCondition(IsOutputSetCondition(_OKAgent), Condition((ConditionMethod)&CMChangeMBOMAssemCmd::OKAction)), NULL);

	// Transition from Input state to NULL, when click on Cancel button
	AddTransition(pSelectionState, pSelectionState, IsOutputSetCondition(_ApplyAgent), Action((ActionMethod)&CMChangeMBOMAssemCmd::ApplyAction));

	// Transition from Input state to NULL, when click on Close button
	AddTransition(pSelectionState, NULL, IsOutputSetCondition(_CloseAgent), Action((ActionMethod)&CMChangeMBOMAssemCmd::CancelAction));

	AddTransition(pSelectionState, NULL, IsOutputSetCondition(_CancleAgent), Action((ActionMethod)&CMChangeMBOMAssemCmd::CancelAction));

	AddTransition(pSelectionState, pSelectionState, IsOutputSetCondition(_pSelectAgent), Action((ActionMethod)&CMChangeMBOMAssemCmd::ElementSelection, NULL, NULL, (void*)1));

	CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_PartCodeEditor), "CMMBOMAssemDlg", "PartCode.Range", ",");
	CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_ManufactureLineEditor), "CMMBOMAssemDlg", "ManufactureLine.Range", ",");
	CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_ProcessUnitEditor), "CMMBOMAssemDlg", "ProcessUnit.Range", ",");

	_ComponentBtn = _Panel->GetPushButton(ID_ComponentBtn);
	AddAnalyseNotificationCB(_ComponentBtn, _ComponentBtn->GetPushBActivateNotification(),
		(CATCommandMethod)&CMChangeMBOMAssemCmd::SetComponentObject, NULL);

	_FatherCompBtn = _Panel->GetPushButton(ID_FatherCompBtn);
	AddAnalyseNotificationCB(_FatherCompBtn, _FatherCompBtn->GetPushBActivateNotification(),
		(CATCommandMethod)&CMChangeMBOMAssemCmd::SetFatherComponentObject, NULL);


	DRECT rect;
	CATBoolean iAlreadyScaled = false;
	_Panel->GetRectDimensionsEx(&rect, iAlreadyScaled);
	rect.x = 800;
	rect.y = 400;
	_Panel->SetRectDimensionsEx(rect, iAlreadyScaled);

	_Panel->SetVisibility(CATDlgShow);


}

void CMChangeMBOMAssemCmd::SetComponentObject()
{
	cout << "*******************SetComponentObject**************************" << endl;
	selectFlag = 1;    //

}

void CMChangeMBOMAssemCmd::SetFatherComponentObject()
{
	cout << "*******************SetFatherComponentObject**************************" << endl;
	selectFlag = 2; 
}

CATBoolean CMChangeMBOMAssemCmd::ElementSelection(void * data)
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

void CMChangeMBOMAssemCmd::FilterSelectObject()
{
	CATUnicodeString sSelectObjectType = CUSCAAUtilService::GetObjectKnowledgeType(_pSelectedReference);

	if (sSelectObjectType == TYPE_MBOMAssembly)
	{
		CATUnicodeString sExternalName = CUSCAAUtilService::GetObjectAttrValue(_pSelectedReference, "PLM_ExternalID");
		CATUnicodeString sType = CUSCAAUtilService::GetObjectAttrValue(_pSelectedReference, "CUS_MBOMType");
		if (sType == "401Component" && selectFlag == 1){
			CATUnicodeString sLastVersion = CUSCAAUtilService::GetObjectAttrValue(_pSelectedReference, "V_isLastVersion");
			if (sLastVersion.Compare("true") == 0) {
				CATUnicodeString Title = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.Title");
				CATUnicodeString msg = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.notLastVersion");
				CUSCAAUtilService::ErrorMessage(Title, msg);
				return;
			}
			pMIDComponentOcc = _pSelectedOccurrence;
			pMIDComponentRef = _pSelectedReference;
			CATDlgEditor *pMIDEditor = _Panel->GetEditor(ID_ManufacturingNameEditor);
			pMIDEditor->SetText(sExternalName);

			CATDlgEditor *pMIDRevisionEditor = _Panel->GetEditor(ID_RevisionEditor);
			pMIDRevisionEditor->SetText(CUSCAAUtilService::GetObjectAttrValue(_pSelectedReference, "revision"));
		}
		else if(selectFlag == 2){
			pFatherMIDOcc = _pSelectedOccurrence;
			pFatherMIDRef = _pSelectedReference;
			CATDlgEditor *pFatherMIDEditor = _Panel->GetEditor(ID_FatherManuAssemEditor);
			pFatherMIDEditor->SetText(sExternalName);
		}

	}
}
CATBoolean CMChangeMBOMAssemCmd::ApplyAction(void *data)
{
	if (_ApplyAgent)
	{
		_ApplyAgent->InitializeAcquisition();
	}

	if (!CheckSelectObject())
	{
		return FALSE;
	}

	ChangeMBOMAssembly();

	return FALSE;
}


CATBoolean CMChangeMBOMAssemCmd::OKAction(void *data)
{
	if (_OKAgent)
	{
		_OKAgent->InitializeAcquisition();
	}

	if (!CheckSelectObject())
	{
		return FALSE;
	}

	ChangeMBOMAssembly();

	return TRUE;
}

CATBoolean CMChangeMBOMAssemCmd::CancelAction(void *data)
{
	if (_Panel != NULL)  _Panel->SetVisibility(CATDlgHide);

	return TRUE;
}

CATBoolean CMChangeMBOMAssemCmd::CheckSelectObject()
{
	if (pMIDComponentRef == NULL)
	{
		CATUnicodeString Title = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.Title");
		CATUnicodeString msg = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.midSelectNull");
		CUSCAAUtilService::ErrorMessage(Title, msg);
		return FALSE;
	}

	if (pFatherMIDOcc == NULL)
	{
		pMIDComponentOcc->GetFather(pFatherMIDOcc);
		if (pFatherMIDOcc != NULL)
		{
			pFatherMIDOcc->GetRelatedReference(pFatherMIDRef);
		}
	}


	pMARootOcc = CUSCAAUtilService::GetRootOcc(pMIDComponentOcc);
	if (pMARootOcc != NULL)
	{
		pMARootOcc->GetRelatedReference(pMARootRef);
	}

	return TRUE;

}
HRESULT CMChangeMBOMAssemCmd::ChangeMBOMAssembly()
{
	HRESULT rc = E_FAIL;

	PPRUtity sPPRUtity;
	sPPRUtity.CreateSubMAAssembly(TYPE_MBOMAssembly, pFatherMIDOcc, pMARootRef, pReviseMIDOcc);
	if (pReviseMIDOcc == NULL)
	{
		CATUnicodeString Title = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.Title");
		CATUnicodeString msg = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.MIDCoponentRevisieFailed");
		CUSCAAUtilService::ErrorMessage(Title, msg);
		return rc;
	}
	pReviseMIDOcc->GetRelatedReference(pReviseMIDRef);

	CATListValCATBaseUnknown_var olistRootRef = sPPRUtity.getCurrentPPREditorRootRef("PRODUCT");
	CATIPLMNavReference_var ospProductRef = NULL_var;
	if (olistRootRef.Size() >= 1) {

		CATIPLMNavInstance_var ospProductInstance = NULL_var;
		olistRootRef[1]->QueryInterface(IID_CATIPLMNavInstance, (void **)&ospProductInstance);
		if (ospProductInstance != NULL_var) {
			ospProductInstance->GetReferenceInstanceOf((CATIPLMNavReference *&)ospProductRef);
			cout << "**************Current Product Instance Reference is *************" << CUSCAAUtilService::GetObjectAttrValue(ospProductRef, "PLM_ExternalID") << endl;
		}
	}
	

	CATListPtrCATIPLMNavOccurrence olistMIDComponentChildOcc;
	pMIDComponentOcc->ListChildren(olistMIDComponentChildOcc);
	int nChild = olistMIDComponentChildOcc.Size();
	CATIPLMNavOccurrence * spNewCompOcc = NULL;
	for (int i = 1; i <= nChild; i++) {
		CATIPLMNavReference * oMIDComponentChildRef = NULL;
		olistMIDComponentChildOcc[i]->GetRelatedReference(oMIDComponentChildRef);
		CATUnicodeString sChildType = CUSCAAUtilService::GetObjectKnowledgeType(oMIDComponentChildRef);
		sPPRUtity.InsertExistProcess(pReviseMIDOcc, oMIDComponentChildRef, pMARootRef, spNewCompOcc);
		if (sChildType == TYPE_MBOMAssembly || sChildType == TYPE_MBOMKit)
		{
			//对于401组件单独处理
		}
		else
		{
			sPPRUtity.CopyProductAssignment(olistMIDComponentChildOcc[i], ospProductRef, spNewCompOcc);
		}
	}


	CATUnicodeString sManuAssemblyName = CUSCAAUtilService::GetObjectAttrValue(pMIDComponentRef, "PLM_ExternalID");
	CATUnicodeString sManuAssemblyRevision = CUSCAAUtilService::GetObjectAttrValue(pMIDComponentRef, "revision");

	//CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "PLM_ExternalID", sManuAssemblyName);
	//CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "name", sManuAssemblyName);
	CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "CUS_ProcessPartCode", sManuAssemblyName);

	CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "CUS_ProcessPartName", CUSCAAUtilService::GetObjectAttrValue(pMIDComponentRef, "CUS_ProcessPartName"));
	CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "V_Name", CUSCAAUtilService::GetObjectAttrValue(pMIDComponentRef, "V_Name"));

	CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "CUS_PartCode", CUSCAAUtilService::GetSelectComboValue(_Panel->GetCombo(ID_PartCodeEditor)));
	CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "CUS_ManufactureLine", CUSCAAUtilService::GetSelectComboValue(_Panel->GetCombo(ID_ManufactureLineEditor)));
	CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "CUS_ProcessUnit", CUSCAAUtilService::GetSelectComboValue(_Panel->GetCombo(ID_ProcessUnitEditor)));

	CUSCAAUtilService::SetObjectAttrString(pReviseMIDRef, "CUS_MBOMType", "401Component");

	CATAdpSaver saver;
	CATListPtrCATBaseUnknown listRootRef;
	listRootRef.Append(pFatherMIDRef);
	rc = saver.Save(&listRootRef);
	if (rc != S_OK)
	{
		CATUnicodeString Title = CATMsgCatalog::BuildMessage((CATString)"CMMakePartDlg", (CATString)"msg.Title");
		CATUnicodeString msg = CATMsgCatalog::BuildMessage((CATString)"CMMakePartDlg", (CATString)"msg.SaveFailed");
		CUSCAAUtilService::ErrorMessage(Title, msg);
		return rc;
	}

	
	sPPRUtity.CopyProductScope(pMIDComponentRef, pReviseMIDRef);

	CATUnicodeString iServicePath = "/resource/CUSDELMIARestService/CUSDELMIAMBOMRestService/reviseFromExistingObject";

	//CATUnicodeString sServerUrl = CATMsgCatalog::BuildMessage((CATString)"CMMBOMReportDlg", (CATString)"ServerUrl");

	CATUnicodeString sServerUrl = CUSCAAUtilService::GetServerURL();
	if (sServerUrl.IsNull())
	{
		CATUnicodeString Title = CATMsgCatalog::BuildMessage((CATString)"CMMBOMReportDlg", (CATString)"msg.Title");
		CATUnicodeString msg = CATMsgCatalog::BuildMessage((CATString)"CMMBOMReportDlg", (CATString)"msg.failedGetURL");
		CUSCAAUtilService::ErrorMessage(Title, msg);
		return rc;
	}
	CATUnicodeString iWebSite = sServerUrl + iServicePath;

	CATString oUserId, oOrganisationId, oProjectId, oRoleId;
	CATAdpPublicSecurityServices::GetSecurityParameters("", oUserId, oOrganisationId, oProjectId, oRoleId);

	CATUnicodeString SecurityContext = "SecurityContext: ctx::" + oRoleId + "." + oOrganisationId + "." + oProjectId;

	CATUnicodeString sChangeRevision = sPPRUtity.NextRevisionCode(sManuAssemblyRevision);
	CATUnicodeString iReviseData = TYPE_MBOMAssembly + "@@" + sManuAssemblyName + "@@" + sManuAssemblyRevision + "@@" + sChangeRevision;

	CATUnicodeString sNewAssemName = CUSCAAUtilService::GetObjectAttrValue(pReviseMIDRef, "PLM_ExternalID");
	CATUnicodeString sNewAssemRevision = CUSCAAUtilService::GetObjectAttrValue(pReviseMIDRef, "revision");
	CATUnicodeString iNewData = TYPE_MBOMAssembly + "@@" + sNewAssemName + "@@" + sNewAssemRevision;

	CATUnicodeString iWebUrl = iWebSite + "?reviseObject=" + iReviseData + "&newObject=" + iNewData;
	cout << "**********************Webservice URL is **********" << iWebUrl << endl;
	CATUnicodeString returnString = CUSCAAUtilService::WebService(SecurityContext, iWebUrl);
	
	if (returnString.Compare("OK") == 0) {
		CATUnicodeString Title = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.Title");
		CATUnicodeString msg = CATMsgCatalog::BuildMessage((CATString)"CMChangeAssemDlg", (CATString)"msg.failedReviseObject");
		CUSCAAUtilService::ErrorMessage(Title, msg);
		return rc;
	}

	//CATListPtrCATIAdpPLMIdentificator olistIdentificator;
	//rc = CUSCAAUtilService::GetObjIdentificator(sManuAssemblyName, sChangeRevision, olistIdentificator, TYPE_MBOMAssembly);
	//int n_Size = olistIdentificator.Size();
	//if (n_Size <= 0) {
	//	return rc;
	//}

	//CATIAdpPLMIdentificator * spNewMAIdent = olistIdentificator[1];
	//CATOmbLifeCycleRootsBag Bag;
	//CATAdpOpenParameters params(CATAdpExpandParameters::Authoring);
	//CATAdpOpenParameters::LoadingMode iLoadMode = params.EditMode;
	//params.SetLoadingMode(iLoadMode);
	//CATAdpOpener opener(Bag, params);
	//

	//CATIPLMNavReference *spNewMACompRef = NULL;//oplistRefComp[1];

	//rc = opener.CompleteAndOpen(spNewMAIdent,IID_CATIPLMNavReference,(void**)&spNewMACompRef);


	//CATIPLMNavOccurrence * spNewMACompOcc = NULL;
	//rc = sPPRUtity.InsertExistProcess(pMAFatherOcc, spNewMACompRef, pMARootRef, spNewMACompOcc);

	//CUSCAAUtilService::CopyDictionariesModel(pMAFatherRef, spNewMACompRef);


	CUSCAAUtilService::CAACallOOTBCmd("PLMGlobalRefresh");

	return rc;
}


