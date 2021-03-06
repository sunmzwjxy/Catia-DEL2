//===================================================================
// COPYRIGHT DS 2021/11/30
//===================================================================
// CAAUtility.cpp
// Header definition of class CAAUtility
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2021/11/30 Creation: Code generated by the 3DS wizard
//===================================================================

#include "CAAUtility.h"
//CATPLMIntegrationUse 
#include "CATAdpPLMQueryAttributeSet.h"
#include "CATAdpPLMComponentsInfos.h"
#include "CATAdpPLMQueryFilter.h"
#include "CATAdpPLMExtendedQueryServices.h"
#include "CATAdpPLMComponentsInfosIter.h"
#include "CATAdpPLMComponentInfos.h"
#include "CATAdpPLMComponentUniqueKey.h"
#include "CATAdpPLMQueryServices.h"
#include "CATAdpOpenParameters.h"
#include "CATAdpOpener.h"
//CATPLMIntegrationAccess 
#include "CATAdpAttributeSet.h"
#include "CATLISTP_CATAdpQueryResult.h"
#include "CATAdpQueryResult.h"
#include "CATAdpPublicSecurityServices.h"
#include "CATAdpPLMExpandFilter.h"
#include "CATAdpPLMExpandSpecification.h"
#include "CATIAdpPLMErrorReviewer.h"
#include "CATIAdpPLMErrorIterator.h"
#include "CATIAdpPLMError.h"
#include "CATAdpPLMErrorReviewerFactory.h"
#include "CATAdpOpenSaveServices.h"
//PLMDictionaryNavServices 
#include "CATCkePLMNavPublicServices.h"
#include "CATCkePLMNavCustoAccessPublicServices.h"
#include "CATCkePLMNavSpecializationAccessPublicServices.h"
//AfrFoundation 
#include "CATApplicationFrame.h"
#include "CATFrmEditor.h"
//Dialog 
#include "CATDlgWindow.h"
#include "CATDlgNotify.h"
#include "CATCommand.h"
//KnowledgeInterfaces 
#include "CATListValCATICkeParm.h"
#include "CATICkeParm.h"
#include "CATICkeParmFactory.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeObject.h"
#include "CATCkeObjectAttrReadServices.h"
//PLMDocumentInterfaces
#include "PLMDocumentServices.h"
//system
#include "CATGetEnvValue.h"
#include "CATError.h"
#include "CATStdIO.h"
//DELPPRSystemItf 
#include "DELIPPRSystemOccAuth.h"
//CATPLMComponentInterfaces
#include "CATListPtrCATIPLMNavInstance.h"
//DELPPRProcessItf 
#include "DELIPPRProcessOccAuth.h"
//ProductStructureInterfaces 
#include "CATIPrdOccurrenceMngt.h"
#include "CATPrdGetOccurrenceMngt.h"
//CATPLMUIInterfaces 
#include "CATIPLMOpenServices.h"
#include "CATPLMOpenServicesFactory.h"
//PLMSetupDataInterfaces 
#include "PLMISetupDataFinder.h"
#include "PLMSetupDataGlobalFunctions.h"
//CATPLMIdentificationAccess 
#include "CATPLMTypeServices.h"
#include "CATIAdpType.h"
#include "CATAdpComponentData.h"

//C++ Library
#include <fstream>
#include <ShlObj.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <comdef.h> 
#include <commdlg.h>
#include <io.h>  
#include <time.h>
#include <wchar.h>
#include <iostream>
#include <WinInet.h>
#pragma comment(lib,"Wininet.lib")
using namespace std;

#define MaxSize 10240

//-----------------------------------------------------------------------------
// CAAUtility : constructor
//-----------------------------------------------------------------------------
CAAUtility::CAAUtility()
{
//
//TODO: Add the constructor code here
//
}

//-----------------------------------------------------------------------------
// CAAUtility : destructor
//-----------------------------------------------------------------------------

CAAUtility::~CAAUtility()
{
//
// TODO: Place code here.
//
}

CATUnicodeString CAAUtility::GetEnvValue(CATUnicodeString iEnvName)
{
	const char * pPath = iEnvName.ConvertToChar();

	char * t_Value = "";

	CATGetEnvValue(pPath, &t_Value);

	CATUnicodeString sEnvValue = t_Value;

	return sEnvValue;
}

CATUnicodeString CAAUtility::GetObjectTypeName(CATIPLMComponent_var spiPLMCompOnObject)
{
	CATIAdpType* pAdpType = NULL;
	spiPLMCompOnObject->GetAdpType(pAdpType);
	if (pAdpType == NULL)
	{
		return "";
	}

	CATIType* pType = NULL;
	CATPLMTypeServices::GetKweTypeFromAdpType(pAdpType, pType);
	pAdpType->Release();
	pAdpType = NULL;

	CATUnicodeString oPLMType = pType->Name();
	if (pType != NULL)
	{
		pType->Release();
		pType = NULL;
	}
	return oPLMType;

}

HRESULT CAAUtility::RetrieveIDofUniquePLMObject(CATListOfCATString &ilistOfAttribute,
												CATListOfCATUnicodeString &ilistOfValues,
												const char* &iStrPLMType,
												CATIAdpPLMIdentificator* &opiIdentOnPLMComp)
{
	// 0. Initialize the Return Value
	HRESULT hr = E_INVALIDARG;

	// 1. Check For Input Arguments
	if ((0 != ilistOfAttribute.Size()) || (0 != ilistOfValues.Size()))  hr = S_OK;
	if (ilistOfAttribute.Size() == ilistOfValues.Size())  hr = S_OK;


	int iListSize = ilistOfAttribute.Size();

	CATAdpPLMQueryAttributeSet iAttributeSetNew;
	CATAdpAttributeSet iAttributeSet;

	// 2. Build the Attribute Set For Query
	int i = 1;
	while ((i <= iListSize) && (SUCCEEDED(hr)))
	{
		// 2.1. Retrieve the Attributes Name and values from the input argument
		CATUnicodeString Name = ilistOfAttribute[i].CastToCharPtr();
		const CATString AttributeINPUT = CATCkePLMNavPublicServices::RetrieveBasicAttributeNameFromPreviousOne(NULL_var, Name).CastToCharPtr();
		CATUnicodeString AttrValue = ilistOfValues[i];
		// 2.2. Add the Attributes To the Set
		hr = iAttributeSetNew.AddStringAttribute(AttributeINPUT, AttrValue);
		// CATAdpAttributeSet is formed for the query by GetElementFromAttributes
		hr = iAttributeSet.AddAttribute(AttributeINPUT, AttrValue);
		i++;
	}

	// 3. Retrieve the Type by using the input String PLM Type
	CATIType_var spCATITypeOnPLMType;
	hr = RetrievePLMType(iStrPLMType, spCATITypeOnPLMType);

	// 4. Retrieve the Element From Database by using the PLM Type and Attribute Set
	CATBoolean bMultipleElementAttrSet = FALSE;
	CATBoolean bUniqueKeyDefOnObject = TRUE;
	CATBoolean bIsUnique = TRUE;
	CATBoolean bUniqueObjectFromKey = TRUE;
	CATBoolean bMultipleElementFromQuery = FALSE;
	CATAdpPLMComponentsInfos oComponentsInfos;

	// 4.1. Create the Filter Consists of PLMType and Attribute Set
	CATAdpPLMQueryFilter iQueryFilter(spCATITypeOnPLMType, iAttributeSetNew);

	// 4.2. Retrieve the Element from Database By using Filter , If Multiple elements are retrieved then Query Fails
	if (SUCCEEDED(hr)) hr = CATAdpPLMExtendedQueryServices::GetElementsFromQueryFilter(iQueryFilter, oComponentsInfos);

	if (SUCCEEDED(hr) && oComponentsInfos.Size() != 0)
	{
		if (oComponentsInfos.Size() != 1)
		{
			cout << "\n\t GetElementsFromQueryFilter Returns Multiple Elements. Please Provide Attribute For Identifying the Unique object from Database. Use PLM_EXTERNAL ID + Version" << endl;
			bMultipleElementAttrSet = TRUE;
		}
		// 4.3. Retrieve the Iterator for Attribute Set
		CATAdpPLMComponentsInfosIter iterator = oComponentsInfos.GetIterator();
		CATIAdpPLMIdentificator *oComponent = NULL;
		CATAdpPLMComponentInfos oInfos;
		CATAdpPLMComponentUniqueKey oUniqueKey;
		// 4.4. Retrieve the Attributes from iterator : Identificator of First PLM Object
		hr = iterator.NextInfos(oComponent, oInfos);

		// 4.5. Retrieve the Unique Key for PLM Object from Identificator
		if (SUCCEEDED(hr) && NULL != oComponent)
			hr = CATAdpPLMQueryServices::GetUniqueKey(oComponent, oUniqueKey);

		if (NULL != oComponent)
		{
			oComponent->Release(); oComponent = NULL;
		}

		if (FAILED(hr)) bUniqueKeyDefOnObject = FALSE;

		// 4.6. Display the Value of Unique Key
		CATUnicodeString oDisplayed;
		if (SUCCEEDED(hr))  hr = oUniqueKey.Display(oDisplayed);
		if (S_OK == hr)	 cout << "\n\t Unique Key is :" << oDisplayed.ConvertToChar() << endl;

		// 4.7. Insure the Unicity of Unique Key
		if (SUCCEEDED(hr))  hr = oUniqueKey.UnicityGuarantee();

		if (S_OK == hr)   cout << "\n\t Unicity Guranteed" << endl;
		else
		{
			cout << "\n\t Unicity of Unique Key is not Guranteed" << endl;
			bIsUnique = FALSE;
		}

		if (TRUE == bIsUnique)
		{
			CATListPtrCATIAdpPLMIdentificator oComponentsIdentifiers;
			// 4.8. Retrieve the Elements from Database by using Unique Key
			if (SUCCEEDED(hr))  hr = CATAdpPLMQueryServices::GetElementsByUniqueKey(oUniqueKey, oComponentsIdentifiers);
			// 4.9. If single element is retrieved return it, if mulitple elements are retrieved then Query Fails.
			if (SUCCEEDED(hr) && oComponentsIdentifiers.Size() != 0)  opiIdentOnPLMComp = oComponentsIdentifiers[1];
			else if (oComponentsIdentifiers.Size() != 1)
			{
				cout << "\n\t GetElementsByUniqueKey Returns Multiple Elements." << endl;
				bUniqueObjectFromKey = FALSE;
			}
		}

		// 4.10. If unique Key is not implemented on the Object then Retrieve the Object By using GetElementFromAttributes
		CATListPtrCATAdpQueryResult opQueryResults;
		if (bUniqueKeyDefOnObject == FALSE || bIsUnique == FALSE)
		{
			cout << "\n\t Unique Key is not Defined on PLM Object or Not Unique Use GetElementFromAttributes" << endl;
			hr = CATAdpPLMQueryServices::GetElementsFromAttributes(spCATITypeOnPLMType, iAttributeSet, opQueryResults);
		}

		// 4.11. If multiple elements areretrieved by above query then Query Fails  Return the identifier for first Object only
		if (SUCCEEDED(hr) && opQueryResults.Size() != 0)
		{
			CATAdpQueryResult *res = opQueryResults[1];
			if (res)
			{
				res->GetIdentifier(opiIdentOnPLMComp);
				delete res;
				res = NULL;
			}

			if (opQueryResults.Size() != 1)
			{
				cout << "\n\t\t GetElementFromAttributes Returns Mulitple Elements. Use Attribute which are unique" << endl;
				bMultipleElementFromQuery = TRUE;
			}
		}
	}

	// 5. Check for the Conditional Variable 
	if (bMultipleElementAttrSet == TRUE || bUniqueObjectFromKey == FALSE || bMultipleElementFromQuery == TRUE)
		hr = E_FAIL;

	return hr;
}

HRESULT CAAUtility::RetrievePLMType(CATUnicodeString isPLMType, CATIType_var& ospType)
{
	HRESULT hr = E_INVALIDARG;
	CATBoolean bPLMType = FALSE;
	if (isPLMType != "")
	{
		hr = CATCkePLMNavPublicServices::RetrieveKnowledgeType(isPLMType, ospType);
		if (NULL_var == ospType)
		{
			hr = CATCkePLMNavCustoAccessPublicServices::RetrieveCustoType(isPLMType, ospType);
			if (SUCCEEDED(hr) && (NULL_var != ospType))
			{
				bPLMType = TRUE;
				cout << "   Success CATCkePLMNavCustoAccessPublicServices::RetrieveCustoType " << (ospType->Name()).ConvertToChar() << endl;
			}
			else
			{
				hr = CATCkePLMNavSpecializationAccessPublicServices::RetrieveSpecializationType(isPLMType, ospType);
				if (SUCCEEDED(hr) && (NULL_var != ospType))
				{
					bPLMType = TRUE;
					cout << "   Success CATCkePLMNavSpecializationAccessPublicServices::RetrieveSpecializationType " << (ospType->Name()).ConvertToChar() << endl;
				}
			}
		}
		else
		{
			bPLMType = TRUE;
			cout << "   Success CATCkePLMNavPublicAccessServices ::RetrieveKnowledgeType non custo type  " << (ospType->Name()).ConvertToChar() << endl;
		}
	}
	if (bPLMType == FALSE)
	{
		cout << "   RetrieveCustoType AND RetrieveKnowledgeType are Failed, Invalid PLMType : Identify the Correct PLMType in Modeler" << endl;
		return E_FAIL;
	}

	return S_OK;
}

CATIPLMComponent_var CAAUtility::GetComponentFromPLMID(CATIAdpPLMIdentificator* &ipiIdentOnPLMComp,
														CATOmbLifeCycleRootsBag &ioBag,
														CATAdpExpandParameters::ExpandMode iMode)
{
	CATIPLMComponent_var spComponent = NULL_var;

	CATAdpOpenParameters ModRef(iMode);
	CATAdpOpener AdpOpener(ioBag, ModRef);
	if (ipiIdentOnPLMComp != NULL)
	{
		CATIPLMComponent* pCom = NULL;
		AdpOpener.CompleteAndOpen(ipiIdentOnPLMComp, IID_CATIPLMComponent, (VOID**)&pCom);

		spComponent = pCom;
	}
	return spComponent;
}

CATListOfCATUnicodeString CAAUtility::SplitString(CATUnicodeString iTransformString, CATUnicodeString iSplit)
{
	CATListOfCATUnicodeString stringList;
	CATUnicodeString sTemp = iTransformString;
	int splitSize = iSplit.GetLengthInChar();
	int e = 0;
	while (e >= 0)
	{
		e = sTemp.SearchSubString(iSplit, 0);
		if (e == -1)
		{
			stringList.Append(sTemp);
		}
		else
		{
			CATUnicodeString token = sTemp.SubString(0, e);
			stringList.Append(token);
		}
		sTemp = sTemp.SubString(e + splitSize, sTemp.GetLengthInChar() - e - splitSize);
	}
	return stringList;
}

int CAAUtility::MessageBoxShow(CATUnicodeString iMessage, CATUnicodeString iTitle, CATDlgStyle iStyle)
{
	int value = -1;
	CATApplicationFrame *pApplication = CATApplicationFrame::GetFrame();
	if (NULL != pApplication)
	{
		CATDlgWindow * pMainWindow = pApplication->GetMainWindow();
		CATDlgNotify *pNotifyDlg = new CATDlgNotify(pMainWindow, iTitle.ConvertToChar(), iStyle);
		if (NULL != pNotifyDlg)
		{
			value = pNotifyDlg->DisplayBlocked(iMessage, iTitle);
			pNotifyDlg->RequestDelayedDestruction();
		}
	}
	return value;
}

CATUnicodeString CAAUtility::WebService(const CATUnicodeString& iUrl)
{
	HRESULT hr = E_FAIL;
	CATUnicodeString RecvStr;
	char file[MaxSize + 1];
	unsigned long read;
	HINTERNET hOpen, hURL;
	LPCWSTR NameProgram = L"http";
	LPCWSTR Website;
	if (!(hOpen = InternetOpen((LPCTSTR)NameProgram, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0)))
	{
		return "";
	}

	CATUnicodeString WebUrl = iUrl;
	wchar_t* wc = new wchar_t[WebUrl.GetLengthInChar() + 1];
	WebUrl.ConvertToWChar(wc);
	Website = wc;

	hURL = InternetOpenUrl(hOpen, (LPCTSTR)Website, NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE, 0);

	BOOL flag = InternetReadFile(hURL, file, MaxSize, &read);
	InternetReadFile(hURL, file, MaxSize, &read);
	std::string RecvStrS;
	while (read > 0 && read <= MaxSize)
	{
		file[read] = '\0';
		CATUnicodeString UTFStr;
		UTFStr.BuildFromUTF8(file, read + 1);
		RecvStrS += UTFStr.ConvertToChar();
		InternetReadFile(hURL, file, MaxSize, &read);
	}
	if (RecvStrS.length() > 0)
	{
		RecvStr = RecvStrS.c_str();
	}
	InternetCloseHandle(hURL);
	return RecvStr;
}

HRESULT CAAUtility::RetrieveDocumentByName(CATIPLMComponent_var ispPLMCompOnObject, CATUnicodeString iDocumentTitle, PLMIDocument*& opDocument)
{
	HRESULT hr = E_INVALIDARG;
	if (NULL_var != ispPLMCompOnObject)
	{
		CATOmbLifeCycleRootsBag iBag;
		CATListPtrCATIAdpPLMIdentificator DocumentIdentifiers;
		hr = PLMDocumentServices::ListDocuments(ispPLMCompOnObject, DocumentIdentifiers);

		if (SUCCEEDED(hr) && DocumentIdentifiers.Size() != 0)
		{
			for (int i = 1; i <= DocumentIdentifiers.Size(); i++)
			{
				CATIAdpPLMIdentificator* DocumentID = DocumentIdentifiers[i];
				PLMIDocument* Document = NULL;
				hr = PLMDocumentServices::GetDocument(DocumentID, Document);
				if (SUCCEEDED(hr))
				{
					CATIPLMComponent_var spPLMCompOnDoc = CAAUtility::GetComponentFromPLMID(DocumentID, iBag, CATAdpExpandParameters::Authoring);
					CATUnicodeString Title = "";
					CATCkeObjectAttrReadServices::GetValueAsString(spPLMCompOnDoc, "Title", Title);
					if (iDocumentTitle == Title)
					{
						opDocument = Document;
						ReleaseList(DocumentIdentifiers);
						return S_OK;
					}

				}
				ReleasePtr(Document);
			}
			ReleaseList(DocumentIdentifiers);
		}

	}
	return hr;
}

HRESULT CAAUtility::AttachDocumentToObject(CATIPLMComponent_var ispPLMCompOnObject,
											CATListOfCATUnicodeString ilListFilePaths,
											CATUnicodeString& iDocumentTitle,
											PLMIDocument* & opDocument)
{
	HRESULT hr = S_OK;
	if (NULL_var == ispPLMCompOnObject)
	{
		return E_FAIL;
	}

	CATIType_var spCATITypeOnType;
	CATString typeName = "Document";
	CATCkePLMNavPublicServices::RetrieveKnowledgeType(typeName.CastToCharPtr(), spCATITypeOnType);

	CATListValCATICkeParm_var lstCATListValCATICkeParmEmptyList;
	CATICkeParm_var hTmpParm;
	CATICkeParmFactory_var hCkeParamFact = CATCkeGlobalFunctions::GetVolatileFactory();
	if (NULL_var != hCkeParamFact)
	{
		hTmpParm = hCkeParamFact->CreateString("name", "Document");
		lstCATListValCATICkeParmEmptyList.Append(hTmpParm);
		hTmpParm = hCkeParamFact->CreateString("Title", iDocumentTitle);
		lstCATListValCATICkeParmEmptyList.Append(hTmpParm);
		hTmpParm = hCkeParamFact->CreateString("description", iDocumentTitle);
		lstCATListValCATICkeParmEmptyList.Append(hTmpParm);
		hTmpParm = hCkeParamFact->CreateString("Access Type", "Inherited");
		lstCATListValCATICkeParmEmptyList.Append(hTmpParm);
		hTmpParm = hCkeParamFact->CreateString("Language", "English");
		lstCATListValCATICkeParmEmptyList.Append(hTmpParm);
	}

	CATListOfCATUnicodeString lListFileComments;
	for (int i = 1; i <= ilListFilePaths.Size(); ++i)
	{
		lListFileComments.Append("Attach");
	}
	hr = PLMDocumentServices::CreateDocument(spCATITypeOnType,
		lstCATListValCATICkeParmEmptyList,
		ilListFilePaths,
		lListFileComments,
		opDocument);
	
	/*for (int i = 1; i <= ilListFilePaths.Size(); ++i)
	{
		if (opDocument == NULL)
		{
			CATListOfCATUnicodeString lListFiles;
			lListFiles.Append(ilListFilePaths[i]);
			CATListOfCATUnicodeString lListFileComments;
			lListFileComments.Append("Attach");
			hr = PLMDocumentServices::CreateDocument(spCATITypeOnType,
				lstCATListValCATICkeParmEmptyList,
				lListFiles,
				lListFileComments,
				opDocument);

			cout << hr << endl;
		}
		else
		{
			CATUnicodeString FileComment = "Attach";
			hr = opDocument->CreateFile(ilListFilePaths[i], FileComment);
			cout << hr << endl;
		}
	}*/
	
	if (opDocument != NULL)
	{
		cout << "????????????" << endl;
		CATIPLMComponent *piPLMCompOnNewDoc = NULL;
		opDocument->QueryInterface(IID_CATIPLMComponent, (void**)&piPLMCompOnNewDoc);
		CATIAdpPLMIdentificator * piAdpIdOnNewDocument = NULL;
		piPLMCompOnNewDoc->GetAdpID(piAdpIdOnNewDocument);
		hr = PLMDocumentServices::AttachDocument(ispPLMCompOnObject, piAdpIdOnNewDocument);
		if (hr == S_OK)
		{
			cout << "????????????????" << endl;
		}
		else
		{
			cout << "????????????????" << endl;
		}
		piAdpIdOnNewDocument->Release();
		piAdpIdOnNewDocument = NULL;
		piPLMCompOnNewDoc->Release();
		piPLMCompOnNewDoc = NULL;
	}
	else
	{
		cout << "????????????" << endl;
	}

	return hr;
}

CATUnicodeString CAAUtility::PLMSave(const CATListPtrCATBaseUnknown* iSaveRoots)
{
	CATUnicodeString retMsg = "Success";
	// Create a PLM Error Reviewer:
	CATIAdpPLMErrorReviewer* piErrorReviewer = NULL;
	HRESULT HRC = CATAdpPLMErrorReviewerFactory::CreateErrorReviewer(piErrorReviewer);
	if (SUCCEEDED(HRC) && piErrorReviewer)
	{
		// Use this PLM Error Reviewer calling service(s) that may fill it with PLMErrors
		HRC = CATAdpOpenSaveServices::Save(iSaveRoots, piErrorReviewer);
		if (FAILED(HRC))
		{
			CATIAdpPLMErrorIterator* piErrorIterator = NULL;
			CATIAdpPLMError* piPLMError = NULL;
			HRC = piErrorReviewer->GetPLMErrorIterator(piErrorIterator);
			if (SUCCEEDED(HRC) && piErrorIterator)
			{
				retMsg = "Fail: ";
				while (SUCCEEDED(piErrorIterator->Next(piPLMError)) && piPLMError)
				{
					// Read error content using CATIAdpPLMError  
					CATError* pError = NULL;
					piPLMError->GetError(&pError);
					retMsg += "<";
					retMsg += pError->GetMsgId();
					retMsg += ">";
					retMsg += pError->GetNLSMessage();
					retMsg += "; ";
					piPLMError->Release();
					piPLMError = NULL;
				}
			}
		}
		// delete the PLM Error Reviewer after use
		piErrorReviewer->Release();
		piErrorReviewer = NULL;
	}
	else
	{
		retMsg = "Fail: CreateErrorReviewer fail";
	}
	return retMsg;
}

HRESULT CAAUtility::GetOccurrenceFromSystemInstance(const CATIPLMNavInstance_var & ihNavInst,
													const CATIPLMNavOccurrence_var & ihFatherOcc,
													const CATIPLMNavOccurrence_var & ihRootOcc,
													CATIPLMNavOccurrence_var & ohNavOcc)
{

	DELIPPRSystemOccAuth_var hSystemOccAuth(getDELIPPRSystemOccAuth());
	if (hSystemOccAuth == NULL_var) return E_FAIL;

	CATIPLMNavInstance * pNavInst = ihNavInst;
	if (NULL == pNavInst) return E_FAIL;

	pNavInst->AddRef();

	CATListPtrCATIPLMNavInstance instancePath;
	hSystemOccAuth->FromOccurrenceToPathOfInstances(ihFatherOcc, instancePath);
	instancePath.Append(pNavInst);

	CATIPLMNavOccurrence* pNavOcc = NULL;
	HRESULT rc = hSystemOccAuth->GetOccurrence(ihRootOcc, instancePath, pNavOcc);
	ohNavOcc = pNavOcc;
	if (NULL != pNavOcc)
	{
		pNavOcc->Release();
		pNavOcc = NULL;
	}
	for (int i = 1; i <= instancePath.Size(); i++)
	{
		CATBaseUnknown * piCBUOnElement = instancePath[i];
		if (NULL != piCBUOnElement)
		{
			piCBUOnElement->Release();
			piCBUOnElement = NULL;
		}
	}

	return rc;
}

HRESULT CAAUtility::GetRootOccurrenceFromRootSystemReference(const CATIPLMNavReference_var & ihNavRef,
															CATIPLMNavOccurrence_var & ohNavOcc)
{
	DELIPPRSystemOccAuth_var hSystemOccAuth(getDELIPPRSystemOccAuth());
	if (hSystemOccAuth == NULL_var) return E_FAIL;

	CATIPLMNavOccurrence* pNavOcc = NULL;
	HRESULT rc = hSystemOccAuth->GetOrCreateRootOccurrence(ihNavRef, pNavOcc);
	ohNavOcc = pNavOcc;
	if (NULL != pNavOcc)
	{
		pNavOcc->Release();
		pNavOcc = NULL;
	}
	return rc;
}

HRESULT CAAUtility::GetOccurrenceFromProcessInstance(const CATIPLMNavInstance_var & ihNavInst,
													const CATIPLMNavOccurrence_var & ihFatherOcc,
													const CATIPLMNavOccurrence_var & ihRootOcc,
													CATIPLMNavOccurrence_var & ohNavOcc)
{
	DELIPPRProcessOccAuth_var hProcessOccAuth(getDELIPPRProcessOccAuth());
	if (hProcessOccAuth == NULL_var) return E_FAIL;

	CATIPLMNavInstance * pNavInst = ihNavInst;
	if (NULL == pNavInst) return E_FAIL;

	pNavInst->AddRef();

	CATListPtrCATIPLMNavInstance instancePath;
	hProcessOccAuth->FromOccurrenceToPathOfInstances(ihFatherOcc, instancePath);
	instancePath.Append(pNavInst);

	CATIPLMNavOccurrence* pNavOcc = NULL;
	HRESULT rc = hProcessOccAuth->GetOccurrence(ihRootOcc, instancePath, pNavOcc);
	ohNavOcc = pNavOcc;
	if (NULL != pNavOcc)
	{
		pNavOcc->Release();
		pNavOcc = NULL;
	}
	for (int i = 1; i <= instancePath.Size(); i++)
	{
		CATBaseUnknown * piCBUOnElement = instancePath[i];
		if (NULL != piCBUOnElement)
		{
			piCBUOnElement->Release();
			piCBUOnElement = NULL;
		}
	}
	return rc;
}

HRESULT CAAUtility::GetRootOccurrenceFromRootProcessReference(const CATIPLMNavReference_var & ihNavRef,
															CATIPLMNavOccurrence_var & ohNavOcc)
{
	DELIPPRProcessOccAuth_var hProcessOccAuth(getDELIPPRProcessOccAuth());
	if (hProcessOccAuth == NULL_var) return E_FAIL;

	CATIPLMNavOccurrence* pNavOcc = NULL;
	HRESULT rc = hProcessOccAuth->GetOrCreateRootOccurrence(ihNavRef, pNavOcc);
	ohNavOcc = pNavOcc;
	if (NULL != pNavOcc)
	{
		pNavOcc->Release();
		pNavOcc = NULL;
	}
	return rc;
}

HRESULT CAAUtility::GetOccurrenceFromProductInstance(const CATIPLMNavInstance_var & ihNavInst,
													const CATIPLMNavOccurrence_var & ihFatherOcc,
													const CATIPLMNavOccurrence_var & ihRootOcc,
													CATIPLMNavOccurrence_var & ohNavOcc)
{
	CATIPrdOccurrenceMngt * pOccMngt = NULL;
	CATPrdGetOccurrenceMngt(pOccMngt);
	CATIPrdOccurrenceMngt_var hOccMngt = pOccMngt;
	if (hOccMngt == NULL_var) return E_FAIL;

	CATIPLMNavInstance * pNavInst = ihNavInst;
	if (NULL == pNavInst) return E_FAIL;

	pNavInst->AddRef();

	CATListPtrCATIPLMNavInstance instancePath;
	hOccMngt->FromOccurrenceToPathOfInstances(ihFatherOcc, instancePath);
	instancePath.Append(pNavInst);

	HRESULT rc = hOccMngt->GetOccurrence(ihRootOcc, instancePath, ohNavOcc);
	for (int i = 1; i <= instancePath.Size(); i++)
	{
		CATBaseUnknown * piCBUOnElement = instancePath[i];
		if (NULL != piCBUOnElement)
		{
			piCBUOnElement->Release();
			piCBUOnElement = NULL;
		}
	}
	return rc;
}

HRESULT CAAUtility::GetRootOccurrenceFromRootProductReference(const CATIPLMNavReference_var & ihNavRef,
															CATIPLMNavOccurrence_var & ohNavOcc)
{
	CATIPrdOccurrenceMngt * pOccMngt = NULL;
	CATPrdGetOccurrenceMngt(pOccMngt);
	CATIPrdOccurrenceMngt_var hOccMngt = pOccMngt;
	if (hOccMngt == NULL_var) return E_FAIL;

	HRESULT rc = hOccMngt->GetOrCreateRootOccurrence(ihNavRef, ohNavOcc);
	return rc;
}

HRESULT CAAUtility::OpenPLMComponent(CATIPLMComponent_var spComp)
{
	if (spComp == NULL_var)
	{
		cout << "????????????" << endl;
		return E_FAIL;
	}
	CATIPLMOpenServices* piPLMOpenService = NULL;
	CATPLMOpenServicesFactory::GetPLMOpenServices(piPLMOpenService);
	if (piPLMOpenService == NULL)
	{
		cout << "??????????????????????????" << endl;
		return E_FAIL;
	}

	CATFrmEditor* pNewEditor = NULL;
	piPLMOpenService->PLMOpen(spComp, pNewEditor);
	if (pNewEditor == NULL)
	{
		cout << "????????????" << endl;
		return E_FAIL;
	}
	
	return S_OK;
}

HRESULT CAAUtility::RetrieveObjectFromResourceTable(CATUnicodeString& iResourceId, CATIPLMComponent_var& ospPLMComp)
{
	HRESULT hr;
	// ===========================================================================================================
	// 1- Retrieves  SetupData Finder
	// ===========================================================================================================
	CATUnicodeString SetupDataFinderID = "MyFinder";
	PLMISetupDataFinder_var setupDataFinder = PLMSetupDataGlobalFunctions::GetPLMSetupDataFinder(SetupDataFinderID);
	if (NULL_var == setupDataFinder)
	{
		return E_FAIL;
	}

	// ===========================================================================================================
	// 2.1- Retrieves the Resource ------Object
	// ===========================================================================================================

	CATBaseUnknown_var spCatalogAsCBU;
	hr = setupDataFinder->FindPointedResource(iResourceId, NULL_var, spCatalogAsCBU);

	if (spCatalogAsCBU != NULL_var)
	{
		ospPLMComp = spCatalogAsCBU;
		if (NULL_var == ospPLMComp) return E_FAIL;
	}
	// ===========================================================================================================
	// 3- Removes the SetupData Finder
	// ===========================================================================================================
	hr = PLMSetupDataGlobalFunctions::RemovePLMSetupDataFinder(SetupDataFinderID);

	return hr;
}

HRESULT CAAUtility::RetrieveFileFromResourceTable(CATUnicodeString& iResourceId, CATUnicodeString& oFilePath)
{
	HRESULT hr;
	// ===========================================================================================================
	// 1- Retrieves  SetupData Finder
	// ===========================================================================================================
	CATUnicodeString SetupDataFinderID = "MyFinder";
	PLMISetupDataFinder_var setupDataFinder = PLMSetupDataGlobalFunctions::GetPLMSetupDataFinder(SetupDataFinderID);
	if (NULL_var == setupDataFinder)
	{
		return E_FAIL;
	}

	// ===========================================================================================================
	// 2.1- Retrieves the Resource ------XML
	// ===========================================================================================================
	CATUnicodeString oXMLDocument = "";
	hr = setupDataFinder->FindDocument(iResourceId, NULL_var, oXMLDocument);
	if ((E_FAIL == hr) || (oXMLDocument == ""))
	{
		return E_FAIL;
	}
	oFilePath = oXMLDocument;
	// ===========================================================================================================
	// 3- Removes the SetupData Finder
	// ===========================================================================================================
	hr = PLMSetupDataGlobalFunctions::RemovePLMSetupDataFinder(SetupDataFinderID);

	return hr;
}

CATUnicodeString CAAUtility::GetConfigInfoFromFile(CATUnicodeString iFilePath, CATUnicodeString iConfigName)
{
	CATUnicodeString strConfigValue = "";
	HRESULT hr;
	unsigned int FileDesc = 0;
	hr = CATFOpen(iFilePath,"r",&FileDesc);
	char line[1000];
	while (SUCCEEDED(hr) && CATFEof(FileDesc) != S_OK)
	{
		hr = CATFGets(line,1000, FileDesc);
		if (SUCCEEDED(hr))
		{
			int nLen = ::MultiByteToWideChar(CP_UTF8,0,line,-1,NULL,0);
			wchar_t *pWstr = new wchar_t[nLen + 1];
			::MultiByteToWideChar(CP_UTF8,0,line,-1,pWstr,nLen);
			CATUnicodeString strLine = "";
			strLine.BuildFromWChar(pWstr);
			strLine = strLine.Strip(CATUnicodeString::CATStripModeTrailing,'\n');
			int e = strLine.SearchSubString("=",0);
			CATUnicodeString strConfigName = strLine.SubString(0,e);
			strConfigName = strConfigName.Strip(CATUnicodeString::CATStripModeBoth);
			int bo = std::strcmp(strConfigName.ConvertToChar(), iConfigName.ConvertToChar());
			if (bo == 0)
			{
				CATUnicodeString str = strLine.SubString(e + 1, strLine.GetLengthInChar() - e - 1);
				strConfigValue = str.Strip(CATUnicodeString::CATStripModeBoth);
				break;
			}
		}
	}
	CATFClose(FileDesc);
	return strConfigValue;
}
