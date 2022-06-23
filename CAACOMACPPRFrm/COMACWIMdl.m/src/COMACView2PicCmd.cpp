//===================================================================
// COPYRIGHT DS 2021/12/06
//===================================================================
// COMACView2PicCmd.cpp
// Header definition of class COMACView2PicCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2021/12/06 Creation: Code generated by the 3DS wizard
//===================================================================

#include "COMACView2PicCmd.h"

#include "CATCreateExternalObject.h"
CATCreateClass( COMACView2PicCmd);

//DialogEngine 
#include "CATAcquisitionFilter.h"
//CATPLMComponentInterfaces 
#include "CATIPLMNavOccurrence.h"
#include "CATIPLMNavReference.h"
//VisualizationInterfaces 
#include "CATPathElement.h"
//SGManager 
#include "CATSO.h"
//DELWkiExposeUseItf 
#include "DELIWKIViewAccess.h"
//System
#include "CATInstantiateComponent.h"
#include "CATListOfCATUnicodeString.h"
#include "CATStdIO.h"
//KnowledgeInterfaces 
#include "CATCkeObjectAttrReadServices.h"
#include "CATICkeObject.h"
//PLMDocumentInterfaces 
#include "PLMDocumentServices.h"

#include "CAAUtility.h"
#include <iostream>
//-------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------
COMACView2PicCmd::COMACView2PicCmd() :
CATStateCommand ("COMACView2PicCmd", CATDlgEngOneShot, CATCommandModeShared)
//  Valid states are CATDlgEngOneShot and CATDlgEngRepeat
, _pSelectAgent(NULL)
{
}

//-------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------
COMACView2PicCmd::~COMACView2PicCmd()
{
if (_pSelectAgent != NULL)
_pSelectAgent->RequestDelayedDestruction();
}


//-------------------------------------------------------------------------
// BuildGraph()
//-------------------------------------------------------------------------
void COMACView2PicCmd::BuildGraph()
{
	_pSelectAgent = new CATPathElementAgent("COMACView2PicCmd", NULL);
	_pSelectAgent->SetBehavior(CATDlgEngWithCSO | CATDlgEngWithPrevaluation | CATDlgEngNewHSOManager | CATDlgEngMultiAcquisitionCtrl);
	
	AddCSOClient(_pSelectAgent);

	CATDialogState * pSelectState = GetInitialState("SelectState");
	pSelectState->AddDialogAgent(_pSelectAgent);

	AddTransition(pSelectState, NULL,
		IsOutputSetCondition(_pSelectAgent),
		Action((ActionMethod)& COMACView2PicCmd::ActionOne));
}

//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean COMACView2PicCmd::ActionOne( void *data )
{
	HRESULT hr;
	CATUnicodeString strTemp = CAAUtility::GetEnvValue("CATTemp");

	CATSO* pSO = _pSelectAgent->GetListOfValues();
	if (pSO == NULL)
	{
		return TRUE;
	}
	int Count = pSO->GetSize();
	for (int i = 0; i < Count; ++i)
	{
		CATPathElement* pPath = (CATPathElement*)(*pSO)[i];

		CATIPLMNavOccurrence* piOcc = (CATIPLMNavOccurrence*)(pPath->FindElement(IID_CATIPLMNavOccurrence));
		if (piOcc == NULL)
		{
			continue;
		}
		CATIPLMNavReference* piReference = NULL;
		piOcc->GetRelatedReference(piReference);

		CATIPLMComponent* piObjectComp = NULL;
		piReference->QueryInterface(IID_CATIPLMComponent,(void**)&piObjectComp);

		CATUnicodeString Title = "";
		CATCkeObjectAttrReadServices::GetValueAsString(piObjectComp, "V_Name", Title);
		std::cout << Title << std::endl;

		CATUnicodeString sObjType = CAAUtility::GetObjectTypeName(piObjectComp);
		std::cout << sObjType << std::endl;
		if (sObjType != "CUS_FO_OP" && sObjType.SearchSubString("Operation") == -1)
		{
			continue;
		}
		CATListOfCATUnicodeString listName;
		CATListOfCATUnicodeString listTargetFile;
		DELIWKIViewAccess* pWKIViewAccess = NULL;
		::CATInstantiateComponent("DELWKIViewAccess", IID_DELIWKIViewAccess, (void**)&pWKIViewAccess);
		if (pWKIViewAccess)
		{
			CATIPLMNavOccurrence_var spOcc(piOcc);
			pWKIViewAccess->GetOperationSlidesImages(spOcc, strTemp, listName);
			ReleasePtr(pWKIViewAccess);
		}
		if (listName.Size() != 0)
		{
			int size = listName.Size();
			for (int i = 1; i <= size; ++i)
			{
				CATUnicodeString strNum = "";
				strNum.BuildFromNum(i);
				CATUnicodeString strSourceFile = strTemp + "\\" + listName[i];
				CATUnicodeString strTargetFile = strTemp + "\\" + Title + "-" + strNum + ".png";
				std::cout << strSourceFile << std::endl;
				hr = ::CATFCopy(strSourceFile, strTargetFile,1);
				if (hr == S_OK)
				{
					listTargetFile.Append(strTargetFile);
				}
				else
				{
					listTargetFile.Append(strSourceFile);
				}
			}
		}
		if (listTargetFile.Size() != 0)
		{
			PLMIDocument* piDocument = NULL;
			hr = CAAUtility::RetrieveDocumentByName(piObjectComp,"View", piDocument);
			if (piDocument != NULL)
			{
				CATIPLMComponent* piCompOnDoc = NULL;
				piDocument->QueryInterface(IID_CATIPLMComponent,(void**)&piCompOnDoc);
				CATIAdpPLMIdentificator* piDocumentID = NULL;
				piCompOnDoc->GetAdpID(piDocumentID);
				PLMDocumentServices::DetachDocument(piObjectComp, piDocumentID);

				ReleasePtr(piDocument);
			}
			CATUnicodeString DocumentTitle = "View";
			CAAUtility::AttachDocumentToObject(piObjectComp, listTargetFile, DocumentTitle,piDocument);
		}
	}
	CAAUtility::MessageBoxShow("�ο���ͼת����ͼƬ���","��ʾ");
return TRUE;
}