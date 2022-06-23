// System
#include "CATBaseUnknown.h" 
#include "CATUnicodeString.h"
#include "CATBoolean.h"
#include "CATLISTP_Declare.h" 
#include "CATInstantiateComponent.h"
#include "CATLISTP_CATBaseUnknown.h"
#include "CATLISTV_CATBaseUnknown.h"
#include "CATListOfCATString.h"
#include "CATCollec.h"
//#include "ClsOperationOfExcel.h"

// ObjectModelerBase
#include "CATOmbLifeCycleRootsBag.h"
#include "CATOmbObjectInContext.h"
#include "CATIAlias.h"

// CATPLMComponentInterfaces
#include "CATIPLMNavReference.h"
#include "CATPLMCoreType.h"
#include "CATPLMSessionServices.h"
#include "CATListPtrCATIPLMNavEntity.h"
#include "CATIPLMNavEntity.h"
#include "CATIPLMNavInstance.h"
#include "CATIPLMNavOccurrence.h"
#include "CATListPtrCATIPLMNavOccurrence.h"

// ProductStructureInterfaces
#include "CATIPLMProducts.h"
#include "CATIPLMRepInstances.h"
#include "CATIPrdObject.h"
#include "CATIPrdOccurrenceMngt.h"
#include "CATPrdGetOccurrenceMngt.h"

// CATPLMIntegrationAccess
#include "CATAdpPLMExpandSpecification.h"
#include "CATAdpPLMExpandFilter.h"

//PLMWorkspaceInterfaces 
#include "CATPLMPersistentFilterServices.h"
#include "CATWSPCaptureServices.h"

// CATPLMIntegrationUse
#include "CATAdpSaver.h"
#include "CATAdpOpenParameters.h"
#include "CATAdpOpener.h"


//KnowledgeInterfaces 
#include "CATCkeObjectAttrReadServices.h"
#include "CATCkeObjectAttrWriteServices.h"
#include "CATCkeGlobalFunctions.h"
#include "CATICkeObject.h"

//CATPLMIdentificationAccess 
#include "CATListPtrCATIAdpPLMIdentificator.h"
//#include "CATIAInterferenceResult.h"
#include "CATIPLMComponent.h"
#include "CATIAdpType.h"

//VisualizationInterfaces 
#include "CATIBuildPath.h"
#include "CATPathElement.h"

//Mathematics 
#include "CATMathPoint.h"

//PLMDocumentInterfaces 
#include "PLMIDocument.h"
#include "PLMDocumentServices.h"

//PLMDictionaryNavServices 
#include "PLMIDocument.h"
#include "CATCkePLMNavPublicServices.h"

//SystemTS
#include "CATToken.h"

// 引用荣奇现有的库
#include "CUSCAAUtilService.h"
#include "PPRUtity.h"

//CATPLMComponentInterfaces Framework
#include "CATPLMSessionServices.h"

//Compute result product
#include "DELIPPRProcessOutputComputeAuth.h"
#include "DELIPPRProcessOccAuth.h"

// CATPLMIntegrationAccess 
#include "CATAdpVersioningServices.h"
#include  "fengyHelper.h"

// C++ Library
#include <iostream.h>
#include <fstream>
#include <comdef.h>
#include <vector>
using  namespace  std;
#include <direct.h>


CATListPtrCATIPLMNavOccurrence   olistRootOcc;					// 找到的 符合的制造装配体的 RootOcc

 // 日志生成
CATUnicodeString  logFilePath;

#define _RETURN_IF_FAILED_(hr, message) \
	if (FAILED(hr)) \
		{ cout << "=== FAILED ===> " << message << endl; return 1; } else	{	cout << "=== OK ===> " << message << endl; }

#define _RETURN_IF_TRUE_(ret, message) \
	if (ret) \
		{ cout << "=== FAILED ===> " << message << endl; return ret; } else	{	cout << "=== OK ===> " << message << endl; }


void ReleasePtr(CATBaseUnknown * piCBU);

// New Method for creation session from Release R2015x
HRESULT CAAAdpCreateSession(const char *  iRepository,
	const char *  iServer,
	const char *  iLoginTicket,
	CATBoolean iTrace = false);


HRESULT AppendContentToFile(CATUnicodeString strFilePath, CATUnicodeString strContent);




HRESULT AppendContentToFile(CATUnicodeString strFilePath, CATUnicodeString strContent)
{
	HRESULT hr = S_OK;

	unsigned int uFile = 0;
	hr = ::CATFOpen(&strFilePath, "ab+", &uFile);		// 指针指向文件 尾部
	if (FAILED(hr))
	{
		cout << "*** Error : Open log file " << strFilePath.ConvertToChar() << " failed" << endl;
		return E_FAIL;
	}

	CATUnicodeString strWrite = strContent + "\n";

	int nWritten = 0;
	::CATFPuts(strWrite, uFile, &nWritten);
	::CATFClose(uFile);

	return S_OK;
}


int main(int iargc, char *iargv[])
{

	//cout<<"fengy's 1st CAA batch!"<<endl;

	HRESULT rc = E_FAIL;
	int ret0 = 0;
	int ret1 = 1;

	// 1. Checks the input arguments
	// =============================
	if (6 != iargc)
	{
		fprintf(stderr, "COMACCAABatchNewVersion: %c <repository> <server> <login_ticket> <PLM_ExternalID> <version>  \n", iargv[0]);
		//fprintf(stderr, "Usage: %c <repository> <server> <login_ticket> <PLM External Id Product> <version> <clearance> <SimuName> <filtername> <LoginPath>  \n", iargv[0]);

		cout << "The quantity of input parameters is wrong..." << endl;
		return ret1;																		// 返回1 表示KO！
	}
	 
	const char * pstrPrefix = "C:/temp/";
	if (_access(pstrPrefix, 0) == -1)	//如果文件夹不存在
		_mkdir(pstrPrefix);				//则创建
										// 先应对obj 链接 bug
	CATUnicodeString str_logTime;
	CATTime logTime = CATTime::GetCurrentLocalTime();
	str_logTime = logTime.ConvertToString("%Y-%m-%d_%H%M%S");			// 月-日 时分秒格式
	logFilePath = "C:\\temp\\log_BatchNewVersion_" + str_logTime + ".txt";
 

	const char* repository = iargv[1];
	const char* server = iargv[2];
	const char* loginTicket = iargv[3];
	CATUnicodeString		strExternal_ID = iargv[4];
	CATUnicodeString		strVersion = iargv[5];

	cout << "repository            " << repository << endl;
	cout << "server                " << server << endl;
	cout << "loginTicket           " << loginTicket << endl;
	cout << "External_ID           " << strExternal_ID << endl;
	cout << "Version			   " << strVersion << endl;

	CATUnicodeString tmpMsg = "BatchNewVersion   1111111111";
	AppendContentToFile(logFilePath, tmpMsg);

	// 2. Creates a PLM session and connects to the input repository
	// =============================================================
	// A session must always be created in a batch environment.
	// Deleting the session at the end of the program is also necessary.
	rc = ::CAAAdpCreateSession(repository, server, loginTicket, false);
	if (FAILED(rc))
	{
		cout << "Login information is wrong ... " << endl;
		return  1;
	}
	tmpMsg = "BatchNewVersion   222222222";
	AppendContentToFile(logFilePath, tmpMsg);

	//   以搜索的方式 进行NewVersion OK
	CATUnicodeString strExt_ID = strExternal_ID;
	CATUnicodeString strRevision = /*strVersion*/ "*";
	//CATUnicodeString strType = TYPE_Product;

	//CATUnicodeString strTitle = "wpl-14182662-00001931" /*"mass-14182662-00003448"*/ /*"prd-14182662-00097964"*/;				// UAT:  mass-14182662-00000145  TYPE_MBOMAssembly -KO 缺权限
	//CATUnicodeString strRevision = "B";

	CATUnicodeString strType = TYPE_CUS_FO_Workplan;
	CATUnicodeString iKey = "PLM_ExternalID";
	//strTitle = strTitle + "*";

	CATListPtrCATIAdpPLMIdentificator olistIdentificator;
	rc = CUSCAAUtilService::GetObjIdentificator(strExt_ID, strRevision, olistIdentificator, strType, iKey);
	int n_Size = olistIdentificator.Size();
	cout<<"#n_Size: "<< n_Size <<endl;
	tmpMsg = "BatchNewVersion   333333333   #n_Size: "+ fengyHelper::IntToStr(n_Size);
	AppendContentToFile(logFilePath, tmpMsg);
	if (n_Size <= 0)
	{
		cout << "==== FAILED  ==== >> GetObjIdentificator ! " << endl;
		return  1;
	}
	else
		cout << "==== OK ==== >> GetObjIdentificator ! " << endl;

	tmpMsg = "BatchNewVersion   444444444444";
	AppendContentToFile(logFilePath, tmpMsg);

	CATIAdpPLMIdentificator * opiIDComp ;		// 最新版本！
	rc =  fengyHelper::GetBigInAllVersions(olistIdentificator[1], opiIDComp);		// 输入的id任意！
	if (FAILED(rc) || (NULL == opiIDComp))
	{
		cout << "==== FAILED  ==== >> GetBigInAllVersions ! " << endl;
		return 1;
	}
	cout << "==== OK ==== >> GetBigInAllVersions ! " << endl;

	//// =========== 读取属性 START ===========

	//CATIPLMNavReference * pCurRef = NULL;
	//rc = fengyHelper::GetRefFromIdentificator(opiIDComp, pCurRef);
	//if (FAILED(rc) || (NULL == pCurRef))
	//{
	//	cout << "==== FAILED  ==== >> GetRefFromIdentificator ! " << endl;
	//	return 1;
	//}
	//cout << "==== OK ==== >> GetRefFromIdentificator ! " << endl;
	//CATUnicodeString str1 = fengyHelper::GetObjectAttrValue(pCurRef, "PLM_ExternalID");
	//CATUnicodeString str2 = fengyHelper::GetObjectAttrValue(pCurRef, "V_Name");
	//CATUnicodeString str3 = fengyHelper::GetObjectAttrValue(pCurRef, "CUS_FORev");
	//tmpMsg = "改前：PLM_ExternalID: "+ str1;
	//tmpMsg.Append("改前：V_Name" + str2);
	//tmpMsg.Append("改前：CUS_FORev" + str3);
	//fengyHelper::SetObjectAttrString(pCurRef, "CUS_FORev", "test!");			// 批处理内部动不了
	//str3 = fengyHelper::GetObjectAttrValue(pCurRef, "CUS_FORev");
	//tmpMsg.Append("改后：CUS_FORev" + str3);
	//AppendContentToFile(logFilePath, tmpMsg);

	//// =========== 读取属性 END ===========

	////CATListOfCATUnicodeString  strRevList;
	////for(int i =1;i<= n_Size;i++)
	////{
	////	opiIDComp = olistIdentificator[i];
	////	CATIPLMNavReference * ptmpRef = NULL;
	////	rc = fengyHelper::GetRefFromIdentificator(opiIDComp, ptmpRef);
	////	if (FAILED(rc) || (NULL == ptmpRef))
	////	{
	////		cout << "==== FAILED  ==== >> GetRefFromIdentificator ! " << endl;
	////		return 1;
	////	}
	////	cout << "==== OK ==== >> GetRefFromIdentificator ! " << endl;
	////	CATUnicodeString strFORev = fengyHelper::GetObjectAttrValue(ptmpRef, "V_version");		// 必定为空！没有处于打开状态！
	////	strRevList.Append(strFORev);
	////}
	////int index = getMaxcharindexInList(strRevList);

	////opiIDComp = olistIdentificator[1];				// 不一定是最新版！
	////opiIDComp->;
	////	fengyHelper::GetObjectAttrValue();

	//  对最新版做更改！
	CATTime TimeVersion = CATTime::GetCurrentLocalTime();
	CATIAdpPLMIdentificator* pNewIdentificatorOnVersionedComp = NULL;
	rc = CATAdpVersioningServices::NewVersion(opiIDComp, TimeVersion, pNewIdentificatorOnVersionedComp);
	if (rc == S_OK)
		cout<<"1111111"<<endl;
		
	if (!pNewIdentificatorOnVersionedComp)
	{
		CATError* pErr = CATError::CATGetLastError(rc);
		if (NULL != pErr)
		{
			CATUnicodeString ErrorMessage = pErr->GetNLSMessage();
			cout << "The error message is: " << ErrorMessage.ConvertToChar() << endl;
			tmpMsg = "FAILED at  NewVersion！！The error message is: ";
			tmpMsg.Append(ErrorMessage.ConvertToChar());

			pErr->Release();
			pErr = NULL;
		}
		AppendContentToFile(logFilePath, tmpMsg);

		fengyHelper::DisplayErrorMessage(rc, "CATAdpVersioningServices::NewVersion");
		return 1;
	}
	else
	{
		cout << "   a New version has been done" << endl;

		tmpMsg = "BatchNewVersion   6666666666		 a New version has been done";
		AppendContentToFile(logFilePath, tmpMsg);

		// 自增 属性：CUS_FORev 
		CATIPLMNavReference * pNewRef = NULL;
		rc = fengyHelper::GetRefFromIdentificator(pNewIdentificatorOnVersionedComp, pNewRef);

		if (FAILED(rc) || (NULL == pNewRef))
		{
			cout << "==== FAILED  ==== >> GetRefFromIdentificator ! " << endl;
			return 1;
		}
		cout << "==== OK ==== >> GetRefFromIdentificator ! " << endl;
		//CATAdpOpenParameters ModRef(CATAdpExpandParameters::Authoring);
		//CATAdpOpenParameters::LoadingMode iLoadMode = ModRef.EditMode;
		//ModRef.SetLoadingMode(iLoadMode);

		//CATOmbLifeCycleRootsBag ioBag;
		//CATAdpOpener AdpOpener(ioBag, ModRef);

		//CATIPLMNavReference* pNewRef = NULL;
		//AdpOpener.CompleteAndOpen(pNewIdentificatorOnVersionedComp, IID_CATIPLMNavReference, (void**)&pNewRef);
		//if (!pNewRef)
		//{
		//	cout << "CompleteAndOpen  ptmpRef FAILED!" << endl;
		//	return 1;
		//}
		//else
		//	cout << "CompleteAndOpen  ptmpRef OK!" << endl;

		CATUnicodeString strFORev = fengyHelper::GetObjectAttrValue(pNewRef, "CUS_FORev");
		strFORev = "007";
		fengyHelper::SetObjectAttrString(pNewRef, "CUS_FORev", strFORev);			// 批处理内部动不了
	}
	tmpMsg = "BatchNewVersion   77777777		 a New version has been done";
	AppendContentToFile(logFilePath, tmpMsg);
	// 13. Disconnect and Delete session
	//==================================
	rc = CATPLMSessionServices::ClosePLMSession();
	if (FAILED(rc))
	{
		cout << "The SESSION is not Closed \n." << endl;
		return ret1;																		// 返回1 表示KO！
	}
	return ret0;																	// 返回1 表示OK！

}


void ReleasePtr(CATBaseUnknown * piCBU)
{
	if (NULL != piCBU)
	{
		piCBU->Release();
		piCBU = NULL;
	}
}


// New Method for creation session from Release R2015x
HRESULT CAAAdpCreateSession(const char *  iRepository,
	const char *  iServer,
	const char *  iLoginTicket,
	CATBoolean iTrace)

{
	cout << " CAAAdpCreateSession   Begin   " << endl;
	if (TRUE == iTrace)
	{
		cout << "   Repository=" << iRepository << endl;
		cout << "   Server    =" << iServer << endl;
		cout << "   Login Ticket      =" << iLoginTicket << endl;
	}
	HRESULT rc = CATPLMSessionServices::SetPLMSessionParameter("Repository", iRepository);
	if (rc != S_OK)
	{
		cout << "FAILED    Set   Repository " << endl;
		return E_FAIL;
	}
	rc = CATPLMSessionServices::SetPLMSessionParameter("Server", iServer);
	if (rc != S_OK)
	{
		cout << "FAILED    Set   Server " << endl;
		return E_FAIL;
	}
	rc = CATPLMSessionServices::SetPLMSessionParameter("LoginTicket", iLoginTicket);
	if (rc != S_OK)
	{
		cout << "FAILED    Set   LoginTicket " << endl;
		return E_FAIL;
	}
	rc = CATPLMSessionServices::InitPLMSession();
	if (rc != S_OK)
	{
		cout << "FAILED    InitPLMSession " << endl;
		return E_FAIL;
	}

	cout << " CAAAdpCreateSession   End    " << endl;
	return rc;
}


