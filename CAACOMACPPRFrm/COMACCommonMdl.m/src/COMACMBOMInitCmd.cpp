//===================================================================
// COPYRIGHT DS 2021/11/30
//===================================================================
// COMACMBOMInitCmd.cpp
// Header definition of class COMACMBOMInitCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2021/11/30 Creation: Code generated by the 3DS wizard
//===================================================================
#include "fengyHelper.h"
#include "COMACMBOMInitCmd.h"

#include "CUSCAAUtilService.h"
#include "CATCreateExternalObject.h"
CATCreateClass( COMACMBOMInitCmd);

//CATPLMIntegrationAccess 
#include "CATAdpPublicSecurityServices.h"
//ProductStructureUseItf 
#include "CATIPrdReferenceFactory.h"
#include "CATPrdFactory.h"
#include "CATIPLMProducts.h"
//PLMDictionaryNavServices 
#include "CATCkePLMNavPublicServices.h"
//KnowledgeInterfaces 
#include "CATIType.h"
#include "CATCkeObjectAttrReadServices.h"
#include "CATCkeObjectAttrWriteServices.h"
#include "CATICkeObject.h"
#include "CATITypeDictionary.h"
#include "CATGlobalFunctions.h"
//DELPPRProcessItf 
#include "DELPPRProcessAuthAccess.h"
//DELPPRSystemItf
#include "DELIPPRSystemAuth.h"
#include "DELPPRSystemAuthAccess.h"
//DELPPRResourceItf 
#include "DELIPPRResourceAuth.h"
#include "DELPPRResourceAuthAccess.h"
//DELPPRAuthFoundationInterfaces 
#include "DELIPPRUIServices.h"
#include "DELPPRUIServicesAccess.h"
//CATPLMComponentInterfaces 
#include "CATListPtrCATIPLMNavOccurrence.h"
#include "CATIPLMNavInstance.h"
//AfrFoundation 
#include "CATApplicationFrame.h"
//CATPLMIdentificationAccess 
#include "CATListPtrCATIAdpPLMIdentificator.h"
#include "CATIAdpPLMIdentificator.h"
//ProductStructureAccess
#include "CATPLMPrdCloningServices.h"

#include "CAAUtility.h"

#include "json.h"
#include <iostream>

#include "CATAdpOpenParameters.h"
#include "CATAdpOpener.h"

#include "PPRUtity.h"

#include "CATAdpMaturityServices.h"


//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
COMACMBOMInitCmd::COMACMBOMInitCmd() :
CATStateCommand ("COMACMBOMInitCmd", CATDlgEngOneShot, CATCommandModeShared)
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
, _Dlg(NULL)
{
	_Dlg = new COMACMBOMInitDlg(CATApplicationFrame::GetFrame()->GetMainWindow(),"COMACMBOMInitDlg");
	_Dlg->Build();
	_serverUrl = "";
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
COMACMBOMInitCmd::~COMACMBOMInitCmd()
{
	if (_Dlg != NULL)
		_Dlg->RequestDelayedDestruction();
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void COMACMBOMInitCmd::BuildGraph()
{
	CATString oUserId, oOrganisationId, oProjectId, oRoleId;
	CATAdpPublicSecurityServices::GetSecurityParameters("PLM1", oUserId, oOrganisationId, oProjectId, oRoleId);
	CATUnicodeString strUserID(oUserId.ConvertToChar());
	cout <<"#strUserID: " << strUserID <<endl;

	SecurityContext = "SecurityContext: ctx::" + oRoleId + "." + oOrganisationId + "." + oProjectId;

	InitDlg(strUserID);

	_Dlg->SetVisibility(CATDlgShow);

	AddAnalyseNotificationCB(_Dlg, _Dlg->GetDiaCANCELNotification(), (CATCommandMethod)&COMACMBOMInitCmd::OnCancelAction, NULL);
	AddAnalyseNotificationCB(_Dlg, _Dlg->GetWindCloseNotification(), (CATCommandMethod)&COMACMBOMInitCmd::OnCancelAction, NULL);
	AddAnalyseNotificationCB(_Dlg, _Dlg->GetDiaOKNotification(), (CATCommandMethod)&COMACMBOMInitCmd::OnOKAction, NULL);
}

void COMACMBOMInitCmd::InitDlg(CATUnicodeString strUserID)
{
	_Dlg->SetUserName(strUserID);
	CATUnicodeString ResourceId = "KnowledgeResources|Config_TXT";
	CATUnicodeString strConfigFile = "";
	CAAUtility::RetrieveFileFromResourceTable(ResourceId, strConfigFile);
	std::cout << "�����ļ�·����" << strConfigFile << std::endl;
	if (strConfigFile == "")
	{
		CAAUtility::MessageBoxShow("�޷���ResourceTabale���ҵ������ļ�", "��ʾ");
		RequestDelayedDestruction();
		return;
	}

	CATUnicodeString serverUrl = CAAUtility::GetConfigInfoFromFile(strConfigFile,"ServerUrl");
	std::cout << "�����ַ��" << serverUrl << std::endl;
	_serverUrl = serverUrl;
	CATUnicodeString strURL = serverUrl + "/resources/CUSVPMReference/CUSVPMReferenceWebService/getFOTask?userid=" + strUserID;
	//CAAUtility::MessageBoxShow(strURL, "��ʾ");
	//CATUnicodeString retMsg = CAAUtility::WebService(strURL);
	CATUnicodeString retMsg = CUSCAAUtilService::WebService(SecurityContext, strURL);

	//CAAUtility::MessageBoxShow(retMsg, "��ʾ");

	//retMsg = "{\"data\":[{\"MPRFormNum\":\"MPR_5311W07111G701-901\",\"MPRType\":\"��ͨ\",\"PartNumber\":\"prd-14182662-00097729\",\"PartRevision\":\"A.1\"}],\"message\":\"\",\"status\":\"success\"}";
	//retMsg = "{\"data\":[{\"MPRFormNum\":\"MPR_5311W07111G701-901\",\"MPRType\":\"��ͨ\",\"PartNumber\":\"prd-53783455-00018974\",\"PartRevision\":\"A.1\"}],\"message\":\"\",\"status\":\"success\"}";
	
	Json::Reader reader;
	Json::Value rootData;
	const char* jsonstr = retMsg.ConvertToChar();
	if (reader.parse(jsonstr,rootData))
	{
		CATUnicodeString strStatus = rootData["status"].asString().c_str();
		if (strStatus == "success")
		{
			Json::Value Data = rootData["data"];
			int size = Data.size();
			for (int i = 0; i < size; ++i)
			{
				CATUnicodeString MPRFormNum = Data[i]["MPRFormNum"].asString().c_str();
				MPRFormNum = MPRFormNum.Strip(CATUnicodeString::CATStripModeBoth, ' ');
				CATUnicodeString MPRType = Data[i]["mprType"].asString().c_str();
				MPRType = MPRType.Strip(CATUnicodeString::CATStripModeBoth, ' ');
				CATUnicodeString PartNumber = Data[i]["partNum"].asString().c_str();
				PartNumber = PartNumber.Strip(CATUnicodeString::CATStripModeBoth,' ');
				CATUnicodeString PartRevision = Data[i]["partRev"].asString().c_str();
				PartRevision = PartRevision.Strip(CATUnicodeString::CATStripModeBoth, ' ');
				CATUnicodeString FOName = Data[i]["FOName"].asString().c_str();				
				FOName = FOName.Strip(CATUnicodeString::CATStripModeBoth, ' ');
				CATUnicodeString FORevision = Data[i]["FORevision"].asString().c_str();
				FORevision = FORevision.Strip(CATUnicodeString::CATStripModeBoth, ' ');
				CATUnicodeString MPRId = Data[i]["MPRID"].asString().c_str();
				MPRId = MPRId.Strip(CATUnicodeString::CATStripModeBoth, ' ');
				CATUnicodeString IsRevise = Data[i]["IsRevise"].asString().c_str();
				IsRevise = IsRevise.Strip(CATUnicodeString::CATStripModeBoth, ' ');

				FOTask fo;
				fo.MPRFormNum = MPRFormNum;
				fo.MPRType = MPRType;
				fo.PartNumber = PartNumber;
				fo.PartRevision = PartRevision;
				fo.FOName = FOName;
				fo.FORevision = FORevision;
				fo.MPRId = MPRId;
				fo.IsRevise = IsRevise;

				_FOVect.push_back(fo);
			}
		}
		else
		{
			CATUnicodeString strMessage = rootData["message"].asString().c_str();
			//CAAUtility::MessageBoxShow("��ȡFO����ʧ�ܣ�" + strMessage, "��ʾ");
			CAAUtility::MessageBoxShow("��ȡMPR����ʧ�ܣ�" + strMessage, "��ʾ");
			RequestDelayedDestruction();
			return;
		}
	}
	_Dlg->InitMultiList(_FOVect);
}

void COMACMBOMInitCmd::OnCancelAction()
{
	RequestDelayedDestruction();
}

void COMACMBOMInitCmd::OnOKAction()
{
	int index = _Dlg->GetSelectRow();
	if (index == -1)
	{
		return;
	}

	CATUnicodeString strPrdID = _FOVect[index].PartNumber;
	CATUnicodeString strPrdRevision = _FOVect[index].PartRevision;

	CATUnicodeString strMPRId = _FOVect[index].MPRId;		
	CATUnicodeString strFOName = _FOVect[index].FOName;
	CATUnicodeString strFORevision = _FOVect[index].FORevision;

	cout << "Part Number is: " << strPrdID << endl;

	CATListOfCATString listOfAttribute;
	CATListOfCATUnicodeString listOfValues;
	CATIAdpPLMIdentificator* opiIdentOnPLMComp;
	listOfAttribute.Append("PLM_ExternalID");
	listOfAttribute.Append("revision");
	listOfValues.Append(strPrdID);
	listOfValues.Append(strPrdRevision);
	const char* strPLMType = "VPMReference";
	CAAUtility::RetrieveIDofUniquePLMObject(listOfAttribute, listOfValues, strPLMType, opiIdentOnPLMComp);
	if (opiIdentOnPLMComp == NULL)
	{
		//CAAUtility::MessageBoxShow("ѡ���FO���������MPR���������ݿ��в�����", "��ʾ");
		CAAUtility::MessageBoxShow("ѡ���MPR���������MPR���������ݿ��в�����", "��ʾ");
		return;
	}

	//// ��һ ����
	//CATOmbLifeCycleRootsBag ioBag;
	//CATIPLMComponent_var spPrdComp = CAAUtility::GetComponentFromPLMID(opiIdentOnPLMComp, ioBag);


	// ����  ��������ֱ��д ��id - component
	CATIPLMComponent_var spPrdComp = NULL_var;
	CATAdpOpenParameters ModRef( CATAdpExpandParameters::Authoring);
	CATAdpOpenParameters::LoadingMode iLoadMode = ModRef.EditMode;
	ModRef.SetLoadingMode(iLoadMode); 

	CATOmbLifeCycleRootsBag ioBag;
	CATAdpOpener AdpOpener(ioBag, ModRef);

	CATIPLMNavReference* ptmpRef = NULL;
	AdpOpener.CompleteAndOpen(opiIdentOnPLMComp, IID_CATIPLMNavReference, (void**)&ptmpRef);
	if (!ptmpRef)
		cout << "CompleteAndOpen  ptmpRef KO!" << endl;
	else
		cout << "CompleteAndOpen  ptmpRef OK!" << endl;

	ptmpRef->QueryInterface(IID_CATIPLMComponent, (void**)&spPrdComp);

	spPrdComp = ptmpRef;

	if (spPrdComp == NULL_var)
	{
		CAAUtility::MessageBoxShow("ѡ���MPR���������MPR�����޷���", "��ʾ");
		//CAAUtility::MessageBoxShow("ѡ���FO���������MPR�����޷���", "��ʾ");
		return;
	}

	CATCkeObjectAttrReadServices::GetValueAsString(spPrdComp, "V_Name", _strMPRitle);
	_strMPRitle.ReplaceSubString("M", "");

	//����PPR�ڵ�
	CATUnicodeString strPPRTitle = "PPR" + _strMPRitle;
	CATIPLMProducts_var spPPRPrd = CreatePPRProduct(ioBag, strPPRTitle);
	if (spPPRPrd == NULL_var)
	{
		RequestDelayedDestruction();
		return;
	}

	CATIPLMComponent_var spPPRComp = NULL_var;
	spPPRPrd->QueryInterface(IID_CATIPLMComponent, (void**)&spPPRComp);
	
	CAAUtility::OpenPLMComponent(spPPRComp);		// open editor window

	int NbChildren = 0;
	spPPRPrd->Count(NbChildren);
	if (NbChildren != 0)				// ��FO�����Ӧ��PPR�ṹ�Ѿ�����
	{
		////CAAUtility::MessageBoxShow("��FO�����Ӧ��PPR�ṹ�Ѿ�����", "��ʾ");
		//CAAUtility::MessageBoxShow("��MPR�����Ӧ��PPR�ṹ�Ѿ�����", "��ʾ");
		RequestDelayedDestruction();
		return;
	}

	CATCkeObjectAttrWriteServices::SetValueWithString(spPPRComp, "V_Name", strPPRTitle);

	DELIPPRUIServices_var spPPRUIService = NULL_var;
	::GetPPRUIServices(spPPRUIService);

	//�½�EBOM���ڵ�
	CATUnicodeString strEBOMTitle = "ME" + _strMPRitle;
	CATIPLMProducts_var spEBOMPrd = CreateProduct("VPMReference", strEBOMTitle);
	CATBaseUnknown* pEBOMInstance = NULL;
	spPPRPrd->AddProduct(spEBOMPrd, pEBOMInstance);
	ReleasePtr(pEBOMInstance);
	CATIPLMNavReference_var spRootPrdRef = NULL_var;
	spEBOMPrd->QueryInterface(IID_CATIPLMNavReference, (void**)&spRootPrdRef);
	CATIPLMNavOccurrence_var spRootPrdOcc = NULL_var;
	CAAUtility::GetRootOccurrenceFromRootProductReference(spRootPrdRef, spRootPrdOcc);

	//��EBOM���ڵ��¹ҽ�MPR���ڵ�
	CATIPLMProducts_var pMPRPrd = NULL_var;
	spPrdComp->QueryInterface(IID_CATIPLMProducts,(void**)&pMPRPrd);
	CATBaseUnknown* pMPRInstance = NULL;
	spEBOMPrd->AddProduct(pMPRPrd, pMPRInstance);
	CATIPLMNavInstance_var spMPRInst = pMPRInstance;
	CATIPLMNavOccurrence_var spMPROcc = NULL_var;
	CAAUtility::GetOccurrenceFromProductInstance(spMPRInst, spRootPrdOcc, spRootPrdOcc, spMPROcc);
	ReleasePtr(pMPRInstance);

	//������Դ�ڵ�
	CATUnicodeString strRootResourceTitle = "MR" + _strMPRitle;
	CATIPLMNavReference_var spRootResourceRef = CreateResource("OrganizationalRef", strRootResourceTitle);
	if (spRootResourceRef != NULL_var)
	{
		CATIPLMProducts_var spResourcePrd = NULL_var;
		spRootResourceRef->QueryInterface(IID_CATIPLMProducts,(void**)&spResourcePrd);
		CATBaseUnknown* pRootResourceInst = NULL;
		spPPRPrd->AddProduct(spResourcePrd, pRootResourceInst);
		//�ӽڵ�
		CATUnicodeString strSubResourceTitle = "M" + _strMPRitle;
		CATIPLMNavReference_var spSubResourceRef = CreateSubResource("Organizational", strSubResourceTitle);
		CATIPLMProducts_var spSubResourcePrd = NULL_var;
		spSubResourceRef->QueryInterface(IID_CATIPLMProducts, (void**)&spSubResourcePrd);
		CATBaseUnknown* pSubResourceInst = NULL;
		spResourcePrd->AddProduct(spSubResourcePrd, pSubResourceInst);
	}

	//����MBOM�ڵ�
	CATUnicodeString strMBOMTitle = strEBOMTitle;
	CATIPLMNavReference_var spMBOMRef = CreatePPRProcess("CreateAssembly", strMBOMTitle);
	if (spMBOMRef != NULL_var)
	{
		spPPRUIService->AddPPRRootToCurrentEditor(spMBOMRef);
		//����scope��ϵ
		DELIPPRProcessAuth_var hPPRProcessAuth;
		::GetPPRProcessAuth(hPPRProcessAuth);
		hPPRProcessAuth->CreateScope(spMBOMRef, spRootPrdRef);
		//����MPR�������MBOM�ṹ
		CATIPLMNavOccurrence_var spRootPrcocessOcc = NULL_var;
		CAAUtility::GetRootOccurrenceFromRootProcessReference(spMBOMRef, spRootPrcocessOcc);
		CreateSubMBOMStructure(hPPRProcessAuth, spMBOMRef, spRootPrcocessOcc, spMPROcc);
	}

	//����workplan�ڵ�
	CATUnicodeString strBOPTitle = "MF" + _strMPRitle + _majRevision;
	CATIPLMNavReference_var spBOPRef = CreateWorkPlan("DELLmiWorkPlanSystemReference", strBOPTitle);
	if (spBOPRef != NULL_var)
	{
		spPPRUIService->AddPPRRootToCurrentEditor(spBOPRef);
		////����scope��ϵ
		DELIPPRSystemAuth_var hPPRSystemAuth;
		::GetPPRSystemAuth(hPPRSystemAuth);
		hPPRSystemAuth->CreateScope(spBOPRef, spMBOMRef);

		DELIPPRResourceAuth_var hPPRResourceAuth;
		::GetPPRResourceAuth(hPPRResourceAuth);
		hPPRResourceAuth->CreateScope(spRootResourceRef, spBOPRef);

		////�����ӽڵ�  
		//CATUnicodeString strSubBOPTitle = "FO" + _strMPRitle + _majRevision;
		//CATIType_var spiType = NULL_var;
		//CAAUtility::RetrievePLMType("CUS_FO", spiType);
		//CATIPLMNavInstance* spSubBOPInst = NULL;
		//hPPRSystemAuth->CreateSubSystemOrOperation(spBOPRef, spiType,(void**)&spSubBOPInst);
		//CATIPLMNavReference* spSubBOPRef = NULL;
		//spSubBOPInst->GetReferenceInstanceOf(spSubBOPRef);
		//CATCkeObjectAttrWriteServices::SetValueWithString(spSubBOPRef, "V_Name", strSubBOPTitle);

		// insert ֮ǰ������  FOName FORevision������ fengy
		// ����FO 
		cout << "#ѡ�� FOName: " << strFOName << endl;
		cout << "#ѡ�� FORevision: " << strFORevision << endl;

		CATListOfCATString listOfAttribute2;
		CATListOfCATUnicodeString listOfValues2;
		CATIAdpPLMIdentificator* opiIdentOnPLMComp2;
		listOfAttribute2.Append("PLM_ExternalID");
		//listOfAttribute2.Append("V_Name");
		listOfAttribute2.Append("revision");
		listOfValues2.Append(strFOName);
		listOfValues2.Append(strFORevision);
		const char* strPLMType2 = TYPE_CUS_FO_Workplan;
		CAAUtility::RetrieveIDofUniquePLMObject(listOfAttribute2, listOfValues2, strPLMType2, opiIdentOnPLMComp2);
		if (opiIdentOnPLMComp2 == NULL)
		{
			//CAAUtility::MessageBoxShow("��������FO ��by FOName��FORevision��" + strFOName + " ��" + strFORevision, "��ʾ");
			CAAUtility::MessageBoxShow("��������MPR ��by FOName��FORevision��" + strFOName + " ��" + strFORevision, "��ʾ");
			return;
		}

		CATIPLMNavReference* ptmpRef2 = NULL;
		AdpOpener.CompleteAndOpen(opiIdentOnPLMComp2, IID_CATIPLMNavReference, (void**)&ptmpRef2);
		if (!ptmpRef2)
			cout << "CompleteAndOpen  ptmpRef2 KO!" << endl;
		else
			cout << "CompleteAndOpen  ptmpRef2 OK!" << endl;

		// insert FO
		PPRUtity spPPRUtity;
		CATIPLMNavInstance* spSubBOPInst2 = NULL;
		spPPRUtity.InsertExistSystem(spBOPRef, ptmpRef2, (CATBaseUnknown *&)spSubBOPInst2);
		
		////CATIPLMNavReference* spSubBOPRef2 = NULL;
		////((CATIPLMNavInstance*)spSubBOPInst2 )->GetReferenceInstanceOf(spSubBOPRef2);

		////CATUnicodeString strSubBOPTitle2 = "FO" + _strMPRitle + _majRevision;
		////CATCkeObjectAttrWriteServices::SetValueWithString(spSubBOPRef2, "V_Name", strSubBOPTitle2);

		//CATIType_var spiType2 = NULL_var;
		//CAAUtility::RetrievePLMType(TYPE_FO_OP, spiType2);
		//hPPRSystemAuth->CreateSubSystemOrOperation(spBOPRef, spiType2, (void**)&spSubBOPInst2);

		// ======================================================================================
		// 5- Read the current state and the possible transitions which can be applied on the current state
		// ======================================================================================
		CATUnicodeString CurrentState;
		CATListValCATUnicodeString ListOfPossibleTransitions;
		HRESULT rc = CATAdpMaturityServices::GetStateAndPossibleTransitions(opiIdentOnPLMComp2, CurrentState, ListOfPossibleTransitions);
		if (FAILED(rc))
		{
			fengyHelper::Notify("GetStateAndPossibleTransitions  KO!");
			return;
		}

		//  Output the values retrieved above
		cout << "   The current maturity state of the component is: " << CurrentState.ConvertToChar() << endl;

		int NumberOfPossibleTransitions = ListOfPossibleTransitions.Size();
		cout << "   The transitions possible from the current state are: " << endl;
		for (int i = 1; i <= NumberOfPossibleTransitions; i++)
		{
			CATUnicodeString TransitionName = ListOfPossibleTransitions[i];
			cout << "\t\t" << TransitionName.ConvertToChar() << endl;
		}

		//����������   ptmpRef2  ApplyMaturityTransition opiIdentOnPLMComp2
		CATUnicodeString InputTransitionName = "IN_WORK";
		CATUnicodeString InputTransitionName2 = "ShareWithinProject";

		if ( CurrentState == InputTransitionName2 || CurrentState == InputTransitionName )
			cout << "The current maturity state is Already : " << CurrentState.ConvertToChar() << "not neccssary ApplyMaturityTransition!" << endl;
		else
		{
			//rc = CATAdpMaturityServices::ApplyMaturityTransition(opiIdentOnPLMComp2, InputTransitionName);
			//if (FAILED(rc))
			//	cout << "FAILED at: ApplyMaturityTransition " << InputTransitionName << endl;
			//else
			//	cout << "OK : ApplyMaturityTransition " << InputTransitionName << endl; 

			rc = CATAdpMaturityServices::ApplyMaturityTransition(opiIdentOnPLMComp2, InputTransitionName2);	// apply must use "ShareWithinProject"
			if (FAILED(rc))
				cout << "FAILED at: ApplyMaturityTransition " << InputTransitionName2 << endl;
			else
				cout << "OK : ApplyMaturityTransition " << InputTransitionName2 << endl;
		}
	}

	CATListPtrCATBaseUnknown SaveRoots;
	CATBaseUnknown* piBaseUnk = NULL;
	spPPRComp->QueryInterface(IID_CATBaseUnknown,(void**)&piBaseUnk);
	SaveRoots.Append(piBaseUnk);
	CATUnicodeString strMsg = CAAUtility::PLMSave(&SaveRoots);
	if (strMsg == "Success")
	{
		strMsg = "PPR�����ɹ�";
	}
	CAAUtility::MessageBoxShow(strMsg, "��ʾ");

	//// ����WebService
	//CATUnicodeString strMPRId = _FOVect[index].MPRId;
	//CATUnicodeString strFOName = _FOVect[index].FOName;
	//CATUnicodeString strFORevision = _FOVect[index].FORevision;

	//CATUnicodeString serverUrl = CAAUtility::GetConfigInfoFromFile(strConfigFile, "ServerUrl");
	//std::cout << "�����ַ��" << serverUrl << std::endl;
	CATUnicodeString strURL = _serverUrl + "/resources/CUSVPMReferenceWebService/connectMPRToFO?mprId=" + strMPRId +"&foName="+ strFOName +"&foRevision"+ strFORevision;
	cout << "#����WebService: " << strURL << endl;

	CATUnicodeString retMsg = CUSCAAUtilService::WebService(SecurityContext, strURL);


	RequestDelayedDestruction();
}

CATIPLMProducts_var COMACMBOMInitCmd::CreatePPRProduct(CATOmbLifeCycleRootsBag& ioBag, CATUnicodeString strPPRTitle)
{
	CATIPLMComponent_var spPPRTemplate = NULL_var;
	CATUnicodeString ResourceId = "KnowledgeResources|PPRTemplate";
	CAAUtility::RetrieveObjectFromResourceTable(ResourceId, spPPRTemplate);
	if (spPPRTemplate == NULL_var)
	{
		CAAUtility::MessageBoxShow("�޷���ResourceTabale���ҵ����õ�PPRģ��", "��ʾ");
		return NULL_var;
	}
	CATUnicodeString strPPRTemplateID = "";
	CATCkeObjectAttrReadServices::GetValueAsString(spPPRTemplate, "PLM_ExternalID", strPPRTemplateID);
	CATUnicodeString strPPRTemplateRev = "";
	CATCkeObjectAttrReadServices::GetValueAsString(spPPRTemplate, "revision", strPPRTemplateRev);

	CATUnicodeString iIdCloningString = strPPRTitle + "-";
	/*CATUnicodeString strPrdID = "ppr-53783455-00001268";
	CATUnicodeString strPrdRevision = "A.1";*/

	CATListOfCATString listOfAttribute;
	CATListOfCATUnicodeString listOfValues;
	CATIAdpPLMIdentificator* opiIdentOnPLMComp = NULL;
	listOfAttribute.Append("PLM_ExternalID");
	listOfAttribute.Append("revision");
	listOfValues.Append(iIdCloningString + strPPRTemplateID);
	listOfValues.Append(strPPRTemplateRev);
	const char* strPLMType = "PPRContext";
	CAAUtility::RetrieveIDofUniquePLMObject(listOfAttribute, listOfValues, strPLMType, opiIdentOnPLMComp);
	if (opiIdentOnPLMComp == NULL)
	{
		spPPRTemplate->GetAdpID(opiIdentOnPLMComp);

		CATLISTP(CATIAdpPLMIdentificator) listofIdent;
		CATLISTP(CATIAdpPLMIdentificator) listofNewIdent;
		listofIdent.Append(opiIdentOnPLMComp);

		CATPLMPrdCloningServices::CloneProductStructures(listofIdent, iIdCloningString, listofNewIdent);
		if (listofNewIdent.Size() == 0)
		{
			CAAUtility::MessageBoxShow("PPR���ڵ㴴��ʧ��", "��ʾ");
			return NULL_var;
		}
		opiIdentOnPLMComp = listofNewIdent[1];
	}
	
	CATIPLMComponent_var spPrdComp = CAAUtility::GetComponentFromPLMID(opiIdentOnPLMComp, ioBag);
	
	CATIPLMProducts* pPPR = NULL;
	spPrdComp->QueryInterface(IID_CATIPLMProducts,(void**)&pPPR);
	return pPPR;
}

CATIPLMProducts_var COMACMBOMInitCmd::CreateProduct(CATUnicodeString iStrType, CATUnicodeString iPrdTitle)
{
	CATIPrdReferenceFactory* piPrdFactory = NULL;
	CATPrdFactory::CreatePrdFactory(IID_CATIPrdReferenceFactory,(void**)&piPrdFactory);
	CATIType_var spiType = NULL_var;
	CAAUtility::RetrievePLMType(iStrType, spiType);
	CATListValCATICkeParm_var iPrdAttributesValues;
	CATIPLMProducts* opReference = NULL;
	piPrdFactory->CreatePrdReference(spiType, iPrdAttributesValues, opReference);
	CATIPLMNavReference_var spNewPrdRef = opReference;
	CATCkeObjectAttrWriteServices::SetValueWithString(spNewPrdRef, "V_Name", iPrdTitle);
	return opReference;
}

CATIPLMNavReference_var COMACMBOMInitCmd::CreateResource(CATUnicodeString iStrType, CATUnicodeString iResourceTitle)
{
	CATITypeDictionary_var hTypeDic = CATGlobalFunctions::GetTypeDictionary();
	CATIType_var spiType = NULL_var;
	hTypeDic->FindTypeInPackage(iStrType,"PLMResourceTypePackage", spiType);

	DELIPPRResourceAuth_var hPPRResourceAuth;
	::GetPPRResourceAuth(hPPRResourceAuth);
	CATIPLMNavReference* pNewRef = NULL;
	hPPRResourceAuth->CreateResource(spiType, (void**)&pNewRef);
	CATCkeObjectAttrWriteServices::SetValueWithString(pNewRef, "V_Name", iResourceTitle);
	return pNewRef;
}

CATIPLMNavReference_var COMACMBOMInitCmd::CreateSubResource(CATUnicodeString iStrType, CATUnicodeString iResourceTitle)
{
	DELIPPRResourceAuth_var hPPRResourceAuth;
	::GetPPRResourceAuth(hPPRResourceAuth);
	CATIType_var spiType = NULL_var;
	CAAUtility::RetrievePLMType(iStrType, spiType);
	CATIPLMNavReference* pNewRef = NULL;
	hPPRResourceAuth->CreateResource(spiType, (void**)&pNewRef);
	CATCkeObjectAttrWriteServices::SetValueWithString(pNewRef, "V_Name", iResourceTitle);
	return pNewRef;
}

CATIPLMNavReference_var COMACMBOMInitCmd::CreatePPRProcess(CATUnicodeString iStrType, CATUnicodeString iProcessTitle)
{
	DELIPPRProcessAuth_var hPPRProcessAuth;
	::GetPPRProcessAuth(hPPRProcessAuth);
	CATIType_var spiType = NULL_var;
	CAAUtility::RetrievePLMType(iStrType, spiType);
	CATIPLMNavReference* pNewRef = NULL;
	hPPRProcessAuth->CreateProcess(spiType,(void**)&pNewRef);
	CATCkeObjectAttrWriteServices::SetValueWithString(pNewRef, "V_Name", iProcessTitle);
	return pNewRef;
}

CATIPLMNavReference_var COMACMBOMInitCmd::CreateWorkPlan(CATUnicodeString iStrType, CATUnicodeString iWorkPlanTitle)
{
	DELIPPRSystemAuth_var hPPRSystemAuth;
	::GetPPRSystemAuth(hPPRSystemAuth);
	CATIType_var spiType = NULL_var;
	CAAUtility::RetrievePLMType(iStrType, spiType);
	CATIPLMNavReference* pNewRef = NULL;
	hPPRSystemAuth->CreateSystem(spiType, (void**)&pNewRef);
	CATCkeObjectAttrWriteServices::SetValueWithString(pNewRef, "V_Name", iWorkPlanTitle);
	return pNewRef;
}

void COMACMBOMInitCmd::CreateSubMBOMStructure(DELIPPRProcessAuth_var& hPPRProcessAuth, CATIPLMNavReference_var& ispRootMBOMRef, CATIPLMNavOccurrence_var& spMBOMOcc, CATIPLMNavOccurrence_var& spPrdOcc)
{
	CATIPLMNavReference* pPrdRef = NULL;
	spPrdOcc->GetRelatedReference(pPrdRef);
	CATUnicodeString sPrdTitle = "";
	CATCkeObjectAttrReadServices::GetValueAsString(pPrdRef, "V_Name", sPrdTitle);
	CATUnicodeString sPrdUsage = "";
	CATCkeObjectAttrReadServices::GetValueAsString(pPrdRef, "V_usage", sPrdUsage);
	if (sPrdUsage == "3DPart")
	{
		CATIPLMNavReference_var spSubRef = COMACMBOMInitCmd::CreatePPRProcess("CreateMaterial", sPrdTitle);
		CATIPLMNavOccurrence* piSubOcc = NULL;
		hPPRProcessAuth->InsertPredecessor(spMBOMOcc, spSubRef, ispRootMBOMRef,(void**)&piSubOcc);
		hPPRProcessAuth->AssignProduct(piSubOcc, spPrdOcc);
		if (sPrdTitle == _strMPRitle)
		{
			CATCkeObjectAttrReadServices::GetValueAsString(pPrdRef, "V_version", _majRevision);
		}
	}
	else
	{
		CATIPLMNavReference_var spSubRef = COMACMBOMInitCmd::CreatePPRProcess("CreateAssembly", sPrdTitle);
		CATIPLMNavOccurrence* piSubOcc = NULL;
		hPPRProcessAuth->InsertPredecessor(spMBOMOcc, spSubRef, ispRootMBOMRef, (void**)&piSubOcc);

		CATListPtrCATIPLMNavOccurrence listPrdChildren;
		spPrdOcc->ListChildren(listPrdChildren);
		for (int i = 1; i <= listPrdChildren.Size(); ++i)
		{
			CATIPLMNavOccurrence_var spChildOcc = listPrdChildren[i];
			CATIPLMNavOccurrence_var spSubOcc = piSubOcc;
			CreateSubMBOMStructure(hPPRProcessAuth, ispRootMBOMRef, spSubOcc, spChildOcc);
		}
	}
}