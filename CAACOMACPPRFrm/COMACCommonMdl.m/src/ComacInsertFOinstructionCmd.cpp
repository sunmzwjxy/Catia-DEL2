//===================================================================
// COPYRIGHT Comac 2021/12/13
//===================================================================
// ComacInsertFOinstructionCmd.cpp
// Header definition of class ComacInsertFOinstructionCmd
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2021/12/13 Creation: Code generated by the 3DS wizard
//===================================================================
#include "fengyHelper.h"
#include "ComacInsertFOinstructionCmd.h"
#include "CATCreateExternalObject.h"
CATCreateClass(ComacInsertFOinstructionCmd);

#include "CATDlgEditor.h"
//#include "CATDlgCombo.h"
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

// VB 实现MainBody 赋值
#include "CATIABody.h"
#include "CATIAPart.h"

#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
using namespace std;

#include "CATLib.h"


//-----------------------------------------------------------------------------
// CMCreateMBOMAssembly : constructor
//-----------------------------------------------------------------------------
ComacInsertFOinstructionCmd::ComacInsertFOinstructionCmd() :
	CATStateCommand("ComacInsertFOinstructionCmd", CATDlgEngOneShot, CATCommandModeShared)
	, _OKAgent(NULL),
	_ApplyAgent(NULL),
	_CloseAgent(NULL)
{
	//
	//TODO: Add the constructor code here

	CATDlgWindow *pWnd = (CATApplicationFrame::GetFrame())->GetMainWindow();
	_Panel = new ComacInsertFOinstructionDlg(pWnd, "Insert FO & instruction");
	_Panel->Build();
	_Panel->SetFather(this);

	pFO_OPStartingRef = NULL;
	pFO_OPStartingOcc = NULL;
	pFO_OPFatherRef = NULL;
	pFO_OPFatherOcc = NULL;
	_strListOPReftitle.RemoveAll();
	_strListOPInsttitle.RemoveAll();
	
	_bConCurrentDesign = FALSE;
}

//-----------------------------------------------------------------------------
// CMCreateMBOMAssembly : destructor
//-----------------------------------------------------------------------------

ComacInsertFOinstructionCmd::~ComacInsertFOinstructionCmd()
{
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

	if (_Panel != NULL)								// 析构时 按钮使能消失！
	{
		_Panel->RequestDelayedDestruction();
		_Panel = NULL;
	}
	_strListOPReftitle.RemoveAll();
	_strListOPInsttitle.RemoveAll();

	_bConCurrentDesign = FALSE;
	pFO_OPStartingRef = NULL;
	pFO_OPStartingOcc = NULL;
	pFO_OPFatherRef = NULL;
	pFO_OPFatherOcc = NULL;

}


void ComacInsertFOinstructionCmd::BuildGraph()
{
	_OKAgent = new CATDialogAgent("OK Agent");
	_OKAgent->AcceptOnNotify(_Panel, _Panel->GetDiaOKNotification());

	// Define the Cancel button agent
	_ApplyAgent = new CATDialogAgent("Apply Agent");
	_ApplyAgent->AcceptOnNotify(_Panel, _Panel->GetDiaAPPLYNotification());   //GetDiaAPPLYNotification     //GetDiaCANCELNotification 

																			  // Define the Close button agent
	_CloseAgent = new CATDialogAgent("Close Agent");
	_CloseAgent->AcceptOnNotify(_Panel, _Panel->GetWindCloseNotification());    //GetMDICloseNotification    //GetWindCloseNotification

	_CancleAgent = new CATDialogAgent("Cancle Agent");
	_CancleAgent->AcceptOnNotify(_Panel, _Panel->GetDiaCANCELNotification());
	// Define the selection agent
	_pSelectAgent = new CATPathElementAgent("SelectionAgent");

	// Define the behaviors
	_pSelectAgent->SetBehavior(CATDlgEngWithCSO | CATDlgEngWithPrevaluation | CATDlgEngNewHSOManager);		 //CATDlgEngMultiAcquisitionCtrl
	AddCSOClient(_pSelectAgent);

	// Define the states
	CATDialogState * pSelectionState = GetInitialState("ElementSelection");
	pSelectionState->AddDialogAgent(_OKAgent);
	pSelectionState->AddDialogAgent(_CloseAgent);
	pSelectionState->AddDialogAgent(_ApplyAgent);
	pSelectionState->AddDialogAgent(_CancleAgent);
	pSelectionState->AddDialogAgent(_pSelectAgent);

	// Transition from Input state to NULL, when click on OK button
	AddTransition(pSelectionState, NULL, AndCondition(IsOutputSetCondition(_OKAgent), Condition((ConditionMethod)&ComacInsertFOinstructionCmd::OKAction)), NULL);
	//AddTransition(pSelectionState, NULL, IsOutputSetCondition(_OKAgent), Action((ActionMethod)&ComacInsertFOinstructionCmd::OKAction));

	// Transition from Input state to NULL, when click on Cancel button
	AddTransition(pSelectionState, pSelectionState, IsOutputSetCondition(_ApplyAgent), Action((ActionMethod)&ComacInsertFOinstructionCmd::ApplyAction));

	// Transition from Input state to NULL, when click on Close button
	AddTransition(pSelectionState, NULL, IsOutputSetCondition(_CloseAgent), Action((ActionMethod)&ComacInsertFOinstructionCmd::CancelAction));

	AddTransition(pSelectionState, NULL, IsOutputSetCondition(_CancleAgent), Action((ActionMethod)&ComacInsertFOinstructionCmd::CancelAction));

	AddTransition(pSelectionState, pSelectionState, IsOutputSetCondition(_pSelectAgent), Action((ActionMethod)&ComacInsertFOinstructionCmd::ElementSelection, NULL, NULL, (void*)1));

	_pCheckBtn = _Panel->GetCheckButton(ID_ConcurrentOPChectBtn);
	AddAnalyseNotificationCB(_pCheckBtn, _pCheckBtn->GetChkBModifyNotification(), (CATCommandMethod)&ComacInsertFOinstructionCmd::ChangeChkBtn, NULL);


	//// 初始化写入 dlg
	//CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_PartCodeEditor), "CMMBOMAssemDlg", "PartCode.Range", ",");
	//CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_ManufactureLineEditor), "CMMBOMAssemDlg", "ManufactureLine.Range", ",");
	//CUSCAAUtilService::ShowComboValue(_Panel->GetCombo(ID_ProcessUnitEditor), "CMMBOMAssemDlg", "ProcessUnit.Range", ",");

	//// 添了两处  radio 等待
	//_pRadioBtnCopy = _Panel->GetRadioButton(ID_DesignCodeCopy);
	//AddAnalyseNotificationCB(_pRadioBtnCopy, _pRadioBtnCopy->GetRadBModifyNotification(),
	//	(CATCommandMethod)&ComacInsertFOinstructionCmd::ChangeRadioNotifyCopy, NULL);

	//_pRadioBtnCopy->SetState(CATDlgCheck);

	//_pRadioBtnInput = _Panel->GetRadioButton(ID_DesignCodeInput);
	//AddAnalyseNotificationCB(_pRadioBtnInput, _pRadioBtnInput->GetRadBModifyNotification(),
	//	(CATCommandMethod)&ComacInsertFOinstructionCmd::ChangeRadioNotifyInput, NULL);

	DRECT rect;
	CATBoolean iAlreadyScaled = false;
	_Panel->GetRectDimensionsEx(&rect, iAlreadyScaled);
	rect.x = 800;
	rect.y = 400;
	_Panel->SetRectDimensionsEx(rect, iAlreadyScaled);

	_Panel->SetVisibility(CATDlgShow);		// 一定要显示！

}

CATBoolean ComacInsertFOinstructionCmd::ChangeChkBtn(void *data)
{
	CATUInt checkState = _pCheckBtn->GetState();
	if (checkState == CATDlgCheck)
	{
		_bConCurrentDesign = TRUE;
		_Panel->GetEditor(ID_OprationStepEditor)->SetText("0");
		_Panel->GetEditor(ID_OprationStepEditor)->SetSensitivity(CATDlgDisable);
	}
	else
	{
		_bConCurrentDesign = FALSE;
		_Panel->GetEditor(ID_OprationStepEditor)->SetText("10");
		_Panel->GetEditor(ID_OprationStepEditor)->SetSensitivity(CATDlgEnable);
	}

	return TRUE;
}


//-------------------------------------------------------------------------
// ActionOne ()
//-------------------------------------------------------------------------
CATBoolean ComacInsertFOinstructionCmd::ActionOne(void *data)
{
	// TODO: Define the action associated with the transition
	// ------------------------------------------------------

	return TRUE;
}

CATBoolean ComacInsertFOinstructionCmd::ElementSelection(void * data)
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

void ComacInsertFOinstructionCmd::FilterSelectObject()
{
	CATUnicodeString sSelectObjectType = CUSCAAUtilService::GetObjectKnowledgeType(_pSelectedReference);
	cout << "## sSelectObjectType:" << sSelectObjectType << endl;

	
	//  Test 0 测试打印出 V_TreeOrder
	if ( sSelectObjectType == TYPE_ProvidePart || sSelectObjectType == TYPE_ManufacturingPart)																// OPeration
	{
		pFO_OPStartingOcc = _pSelectedOccurrence;
		pFO_OPStartingRef = _pSelectedReference;
		CATBoolean iAllAtributes = TRUE;

		HRESULT hr = fengyHelper::BrowseReference(pFO_OPStartingRef, 1, iAllAtributes, 0);
		if (FAILED(hr))
		{
			fengyHelper::Notify("BrowseReference  KO!");
			return;
		}
	}

	//// Test 1
	//CATSystemInfo iSystemInfo /*=NULL*/;
	//CATLibStatus sStatus =  CATGetSystemInfo(&iSystemInfo);
	//if (CATLibSuccess == sStatus)
	//{
	//	cout << "iSystemInfo-HostName :" << iSystemInfo.HostName << endl
	//		<< "iSystemInfo-OSName :" << iSystemInfo.OSName << endl
	//		<< "iSystemInfo-OSVersion :" << iSystemInfo.OSVersion << endl
	//		<< "iSystemInfo-MajorVersion :" << iSystemInfo.MajorVersion << endl
	//		<< "iSystemInfo-MinorVersior :" << iSystemInfo.MinorVersion << endl
	//		<< "iSystemInfo-OSType :" << iSystemInfo.OSType << endl;
	//}
	//if (CATLibError == sStatus)
	//{
	//	cout << "CATGetSystemInfo  ERROR! " << iSystemInfo.HostName << endl;
	//}



	if ((sSelectObjectType == TYPE_Workplan) || (sSelectObjectType == TYPE_CUS_FO_Workplan))					// workplan
	{
		pFO_OPFatherOcc = _pSelectedOccurrence;
		pFO_OPFatherRef = _pSelectedReference;
		CATDlgEditor *pEditor = _Panel->GetEditor(ID_FatherWorkPlanEditor);
		pEditor->SetText(CUSCAAUtilService::GetObjectAttrValue(pFO_OPFatherRef, "V_Name"));

		// 互锁
		pFO_OPStartingOcc = NULL ;
		pFO_OPStartingRef = NULL;
		CATDlgEditor *pEditor2 = _Panel->GetEditor(ID_StartingOperationNameEditor);
		pEditor2->SetText("");

		_Panel->GetCheckButton(ID_ConcurrentOPChectBtn)->SetSensitivity(CATDlgDisable);

	}

	if (sSelectObjectType == TYPE_FO_OP)																// OPeration
	{
		pFO_OPStartingOcc = _pSelectedOccurrence;
		pFO_OPStartingRef = _pSelectedReference;
		CATDlgEditor *pEditor2 = _Panel->GetEditor(ID_StartingOperationNameEditor);
		pEditor2->SetText(CUSCAAUtilService::GetObjectAttrValue(pFO_OPStartingRef, "V_Name"));

		// 互锁
		pFO_OPFatherOcc = NULL;
		pFO_OPFatherRef = NULL;
		CATDlgEditor *pEditor = _Panel->GetEditor(ID_FatherWorkPlanEditor);
		pEditor->SetText("");
		_Panel->GetCheckButton(ID_ConcurrentOPChectBtn)->SetSensitivity(CATDlgEnable);

	}

}

CATBoolean ComacInsertFOinstructionCmd::ApplyAction(void *data)
{
	if (_ApplyAgent)
	{
		_ApplyAgent->InitializeAcquisition();
	}
	if (!CheckSelectObject())
	{
		return FALSE;
	}

	//_strListOPReftitle.RemoveAll();
	//_strListOPInsttitle.RemoveAll();
	// 主函数： MBOM 写入
	InsertFOinstruction();

	return FALSE;
}


CATBoolean ComacInsertFOinstructionCmd::OKAction(void *data)
{
	if (_OKAgent)
	{
		_OKAgent->InitializeAcquisition();
	}
	if (!CheckSelectObject())
	{
		return FALSE;
	}
	// 主函数： MBOM 写入
	InsertFOinstruction();

	return TRUE;
}

CATBoolean ComacInsertFOinstructionCmd::CheckSelectObject()
{
	if ( (pFO_OPStartingOcc == NULL) && (pFO_OPFatherOcc == NULL) )
	{
		fengyHelper::Notify("请选择 WorkPlan 或者 Operation 节点！");
		return FALSE;
	}

	return TRUE;
}

CATBoolean ComacInsertFOinstructionCmd::CancelAction(void *data)
{
	if (_Panel != NULL)  _Panel->SetVisibility(CATDlgHide);

	return TRUE;
}


//   fengy 2021.12.15  InsertFOinstruction
HRESULT ComacInsertFOinstructionCmd::InsertFOinstruction()
{
	HRESULT rc = E_FAIL;
	CATUnicodeString tmpMsg = "";
	//fengyHelper::Notify("框架搭建OK！\nNext:\n 1-Occ明确；\n 2- CrateMbomStructure 逻辑编写！");


	// 获取 数量 ： ID_OprationCountEditor
	CATDlgEditor *pEditorOPCount = _Panel->GetEditor(ID_OprationCountEditor);
	CATUnicodeString  sOPCount = pEditorOPCount->GetText();
	cout << "GetText sOPCount: " << sOPCount << endl;
	if (CATUnicodeString("") == sOPCount)														//空“”。创建 1441418336个！
	{
		fengyHelper::Notify("请填入工序数量！");
		return rc;
	}
	int nOPCount = fengyHelper::Str2Int(sOPCount);					// new add OP count
	cout << " nOPCount: " << nOPCount << endl;


	// 获取 步长 ： ID_OprationStepEditor
	CATDlgEditor *pEditorOPstep = _Panel->GetEditor(ID_OprationStepEditor);
	CATUnicodeString  sOPstep = pEditorOPstep->GetText();
	cout << "GetText sOPstep: " << sOPstep << endl;
	if (CATUnicodeString("") == sOPstep)														//空“”。创建 1441418336个！
	{
		fengyHelper::Notify("请填入工序步长！");
		return rc;
	}
	int nOPstep = fengyHelper::Str2Int(sOPstep);					// new add OP count
	cout << " nOPstep: " << nOPstep << endl;

	//double  dOPNum = pEditorOPNum->GetValue();
	//cout << "GetValue dOPNum: " << dOPNum << endl;				// 0 可能开始就是 不是 SetValue 
	if ( nOPCount < 1 /*|| nOPCount>99*/ )
	{
		tmpMsg = "不允许工序数量超出 1~99,999,999 范围！";
		fengyHelper::Notify(tmpMsg);
		return rc;
	}

	if (nOPstep < 0 /*|| nOPCount>99*/)
	{
		tmpMsg = "不允许工序步长超出 0~99,999,999 范围！";
		fengyHelper::Notify(tmpMsg);
		return rc;
	}

	// 用户选择了哪种模式 ：workplan or OP _ 直接创建指定数量的operation， 并挂载 instruction！
	//CATIPLMNavInstance			 * pNewFO_OPInstance = NULL;						// 放到 子函数内

	CATListOfCATUnicodeString    strExistedOPTitleList;									// 用于提示已经存在的重复的件 ref title
	strExistedOPTitleList.RemoveAll();
	bool						 isToCreateSameOP = false;

	if (pFO_OPFatherOcc) 		// 父子级 workPlan
	{
		int nOPNamePreffixNumber = 10;

		// 新增重复节点是否创建
		for (int i = 1; i <= nOPCount; i++)
		{
			CATUnicodeString sFormatCode;

			sFormatCode.BuildFromNum(nOPNamePreffixNumber + (i - 1) * nOPstep, "%03d");
			cout << " Title sFormatCode: " << sFormatCode << endl;

			bool isExisted = IsOPTitleExisted(sFormatCode, pFO_OPFatherRef);
			if (isExisted)
				strExistedOPTitleList.Append(sFormatCode);
		}
		int sizeExisted = strExistedOPTitleList.Size();
		if (sizeExisted > 0)
		{
			tmpMsg = "以下工序节点已存在:\n";
			for (int i = 1; i <= sizeExisted; i++)
			{
				tmpMsg.Append(strExistedOPTitleList[i]);
				if(i!= sizeExisted)
					tmpMsg.Append(" , ");
			}
			tmpMsg.Append("\n\n============================\n需要重复创建吗？");
			
			cout << tmpMsg << endl;
			fengyHelper::NotifyYesOrNO("info...",tmpMsg, isToCreateSameOP);
			cout << "# NotifyYesOrNO: " << isToCreateSameOP << endl;
			if (!isToCreateSameOP)
			{
				// 释放，防止apply 按钮 重复进入！
				pFO_OPFatherOcc = NULL;
				pFO_OPStartingOcc = NULL;
				return rc;
			}
		}
		
		for (int i = 1; i <= nOPCount; i++)
		{
			CATUnicodeString sFormatCode;

			sFormatCode.BuildFromNum(nOPNamePreffixNumber + (i - 1) * nOPstep, "%03d");
			cout << " Title sFormatCode: " << sFormatCode << endl;

			// suffix
			int nOccur = _strListOPReftitle.NbOccur(sFormatCode);
			cout << "#已存在 " << nOccur << "个 " << sFormatCode << endl;
			// suffix name
			CATUnicodeString strRefsuffix = sFormatCode;
			CATUnicodeString strInstsuffix = strRefsuffix + "." + fengyHelper::IntToStr(nOccur + 1);		// inst title 修改
			CreateOneOPInstruction(pFO_OPFatherOcc,pFO_OPFatherRef, strRefsuffix, strInstsuffix);

		}
		strExistedOPTitleList.RemoveAll();

		// 释放，防止apply 按钮 重复进入！
		pFO_OPFatherOcc = NULL;
		pFO_OPStartingOcc = NULL;

	}

	if (pFO_OPStartingOcc)		// 选择的 OP
	{

		pFO_OPFatherOcc = fengyHelper::GetFartherOcc(pFO_OPStartingOcc);
		pFO_OPFatherOcc->GetRelatedReference(pFO_OPFatherRef);
		cout << " #workplan ref title  : " << CUSCAAUtilService::GetObjectAttrValue(pFO_OPFatherRef, "V_Name") << endl;		// ref title

		// 获取 起始OP name ： ID_StartingOperationNameEditor
		CATDlgEditor *pEditorStartingOprationName = _Panel->GetEditor(ID_StartingOperationNameEditor);
		CATUnicodeString  sStartingOprationName = pEditorStartingOprationName->GetText();
		cout << "GetText sStartingOprationName: " << sStartingOprationName << endl;	

		// 拆分sStartingOprationName			// 090-A
		OpNameSplitInfo infoOpName("010",10,false,-1);
		bool isConformed = ifNameConformToRule(sStartingOprationName, infoOpName);
		if (!isConformed)
		{
			tmpMsg = "所选工序节点命名不规范！当前： " + sStartingOprationName;
			tmpMsg.Append("\n应为：3位数字（eg：010），或 3位数字+连字符+1位大写字母（eg：010-A）");
			fengyHelper::Notify(tmpMsg);
			// 释放，防止apply 按钮 重复进入！
			pFO_OPFatherOcc = NULL;
			pFO_OPStartingOcc = NULL;
			return rc;
		}
		int nOPNamePreffixNumber	= infoOpName.nNamePreffixNumber;
		int nSuffixABC				= infoOpName.nSuffixABC;
		bool bSuffix				= infoOpName.bSuffix;
		// 新增并行工序节点
		if (_bConCurrentDesign)
		{
			cout << "#enter 并行工序创建 " << endl;
			//strExistedOPTitleList.RemoveAll();
			for (int i = 0; i <= nOPCount; i++)
			{
				if (i == 0)						// 修改原先的 点选OP节点
				{
					if (!bSuffix)			// 选中的OP 不带后缀 ,需加上A
					{
						CATIPLMNavInstance* pFO_OPStartingInst = NULL;
						pFO_OPStartingOcc->GetRelatedInstance(pFO_OPStartingInst);
						// 改operation ref title
						CUSCAAUtilService::SetObjectAttrString(pFO_OPStartingRef, "V_Name", infoOpName.sNamePreffixAlpha + "-A");
						// 改operation inst title；						 inst 后缀 不需要遍历！
						CUSCAAUtilService::SetObjectAttrString(pFO_OPStartingInst, "PLM_ExternalID", infoOpName.sNamePreffixAlpha + "-A.1");
					}
				}
				else							// 对新增的 OP 并行工序设计 ，添加后缀
				{
					CATUnicodeString c_string = "";
					if (!bSuffix)			// 选中的OP 不带后缀 ,需加上A
						c_string = fengyHelper::getAsciiCATUnicodeString(i + nAsciiCharA);		// 从B开始
					else
						c_string = fengyHelper::getAsciiCATUnicodeString(i + infoOpName.nSuffixABC);

					CATUnicodeString sOPtitleWithAlpha = infoOpName.sNamePreffixAlpha + "-" + c_string;
					cout << "# 并行工序创建: " << sOPtitleWithAlpha << endl;

					bool isExisted = IsOPTitleExisted(sOPtitleWithAlpha, pFO_OPFatherRef);
					if (isExisted)
						strExistedOPTitleList.Append(sOPtitleWithAlpha);
				}
			}
			// 开始创建
			rc = startCreateAction(strExistedOPTitleList, nOPNamePreffixNumber, bSuffix,nSuffixABC, nOPCount, nOPstep);
			if (FAILED(rc))
			{
				cout << "==== FAILED at ==== >> startCreateAction ! " << endl;
				// 释放，防止apply 按钮 重复进入！
				pFO_OPFatherOcc = NULL;
				pFO_OPStartingOcc = NULL;
				return rc;
			}
			cout << "==== OK ==== >> startCreateAction ! " << endl;
			// 释放，防止apply 按钮 重复进入！
			pFO_OPFatherOcc = NULL;
			pFO_OPStartingOcc = NULL;
			return rc;
		}

		// 新增重复节点是否创建    —— 非并行设计
		//strExistedOPTitleList.RemoveAll();
		for (int i = 1; i <= nOPCount; i++)
		{
			CATUnicodeString sFormatCode;
			sFormatCode.BuildFromNum(nOPNamePreffixNumber + i * nOPstep, "%03d");
			cout << " Title sFormatCode: " << sFormatCode << endl;

			bool isExisted = IsOPTitleExisted(sFormatCode, pFO_OPFatherRef);
			if (isExisted)
				strExistedOPTitleList.Append(sFormatCode);
		}

		// 开始创建
		rc = startCreateAction(strExistedOPTitleList, nOPNamePreffixNumber, bSuffix, nSuffixABC, nOPCount, nOPstep);
		if(FAILED(rc))
		{
			cout << "==== FAILED at ==== >> startCreateAction ! " << endl;
			// 释放，防止apply 按钮 重复进入！
			pFO_OPFatherOcc = NULL;
			pFO_OPStartingOcc = NULL;
			return rc;
		}
		cout << "==== OK ==== >> startCreateAction ! " << endl;
	}

	//pNewFO_OPInstance->Release();
	//pNewFO_OPInstance = NULL ;
	// 释放，防止apply 按钮 重复进入！
	pFO_OPFatherOcc = NULL;
	pFO_OPStartingOcc = NULL;
	strExistedOPTitleList.RemoveAll();
	return rc;
}


//   fengy 2021.12.30  IsOPTitleExisted
bool  ComacInsertFOinstructionCmd::IsOPTitleExisted(CATUnicodeString iStrTitle, CATIPLMNavReference * ipFO_OPFatherRef)
{
	bool oIsExisted = false;
	if (CATUnicodeString("") == iStrTitle || ipFO_OPFatherRef == NULL)
	{
		cout << "IsOPTitleExisted ()输入 为空 ！ " << endl;
		return oIsExisted;
	}
	if ( _strListOPReftitle.Size() == 0 || _strListOPInsttitle.Size() == 0)
	{
		HRESULT rc = E_FAIL;
		// 3 - 对一级direct list 内的 ref 、inst rename

		CATPLMCoreType coreType;
		CATListPtrCATIPLMNavEntity childrenList;

		coreType = PLMCoreInstance;
		rc = ipFO_OPFatherRef->ListChildren(childrenList, 1, &coreType);
		if (SUCCEEDED(rc))
		{
			cout << "the size of the instances aggregated under Ref is " << childrenList.Size() << endl;
			if (childrenList.Size() == 0)
				return oIsExisted;

			// ===========================================================================================================
			//   For each Part Instances
			// ===========================================================================================================
			int j = 1;
			int nIsOperation = 0;
			int  nOP = childrenList.Size();
			while (j <= nOP)
			{
				CATIPLMNavEntity* piNavEntity = childrenList[j];
				if (NULL != piNavEntity)
				{
					CATIPLMNavInstance* piNavInst = NULL;
					rc = piNavEntity->QueryInterface(IID_CATIPLMNavInstance, (void **)&piNavInst);
					if (SUCCEEDED(rc))
					{
						CATIPLMNavReference* piNavRef1 = NULL;
						rc = piNavInst->GetReferenceInstanceOf(piNavRef1);	//搜索后的 层级：rootref - inst- ref -rep isnt -repref
						if (SUCCEEDED(rc) && (NULL != piNavRef1))
						{
							// 类型判断 TYPE_FO_OP
							CATUnicodeString sSelectObjectType = CUSCAAUtilService::GetObjectKnowledgeType(piNavRef1);
							cout << "sSelectObjectType:" << sSelectObjectType << endl;
							if (sSelectObjectType == TYPE_FO_OP || sSelectObjectType == TYPE_GeneralOperation)
							{
								nIsOperation++;
								//  获取ref list 内元素遍历 ref title ，如果重名，更改1st ref title
								CATUnicodeString  sformerRefTitle = CUSCAAUtilService::GetObjectAttrValue(piNavRef1, "V_Name");
								_strListOPReftitle.Append(sformerRefTitle);

								//  获取inst list 内元素遍历 inst title ，如果重名，更改1st inst title
								CATUnicodeString  sformerInstTitle = CUSCAAUtilService::GetObjectAttrValue(piNavInst, "PLM_ExternalID");
								_strListOPInsttitle.Append(sformerInstTitle);
							}
							j++;
						}
					}
				}
			}
		}
	}

	int countOccur = _strListOPReftitle.NbOccur(iStrTitle);
	if (countOccur > 0)
		return true;

	return oIsExisted;
}


// fengy 2022.1.4 找到后续的节点-A不重复的节点！
CATUnicodeString ComacInsertFOinstructionCmd::findDifferTitle(CATUnicodeString isFormatCode, CATListOfCATUnicodeString iTitlList)
{
	CATUnicodeString osFormatCode = "";

	if (iTitlList.Size() == 0 || CATUnicodeString("")== isFormatCode )
	{
		fengyHelper::Notify("当前结构树下没有OP节点！or input 为空！");
		return osFormatCode;
	}

	if (iTitlList.NbOccur(isFormatCode) > 0)
	{
		// 	16. 将Ascii 码大写字母转换！
		for (int i = nAsciiCharA; i <= nAsciiCharZ; i++)
		{
			CATUnicodeString c_string = fengyHelper::getAsciiCATUnicodeString(i);

			CATUnicodeString tmpStr = isFormatCode + "-" + c_string;
			cout<<"#findDifferTitle pingjie Alpha Beta: "<< tmpStr <<endl;
			if (iTitlList.NbOccur(tmpStr)== 0 )
			{
				osFormatCode = tmpStr;
				return osFormatCode;
			}
		}
	}

	return osFormatCode;
}

// fengy 2022.1.5 create one op  intruction
// ipFO_OPFatherRef  : 父级 workplan
void ComacInsertFOinstructionCmd::CreateOneOPInstruction(CATIPLMNavOccurrence *ipFO_OPFatherOcc, CATIPLMNavReference* ipFO_OPFatherRef,CATUnicodeString istrRefsuffix, CATUnicodeString istrInstsuffix)
{
	if (NULL == ipFO_OPFatherOcc || NULL == ipFO_OPFatherRef)
	{
		fengyHelper::Notify("CreateOneOPInstruction 输入为空！");
		return;
	}
	// 2- 在父子级下新建 operation 
	CATIPLMNavInstance *pNewFO_OPInstance = NULL;
	HRESULT rc = spPPRUtity.CreateSubSystemOrOperation(TYPE_FO_OP, ipFO_OPFatherRef, pNewFO_OPInstance);

	if (FAILED(rc) || (pNewFO_OPInstance == NULL))
	{
		cout << "==== FAILED  ==== >>create operation under the system workplan 节点! " << endl;
		return ;
	}
	cout << "==== OK ==== >> create operation under the system workplan 节点! " << endl;

	// 3- 在operation 创建 isntruction

	// 未封装
	CATIPLMNavReference * spNewFO_OPRef = NULL;
	rc = pNewFO_OPInstance->GetReferenceInstanceOf(spNewFO_OPRef);
	if (FAILED(rc) || (spNewFO_OPRef == NULL))
	{
		cout << "Failed to Get new FO_OP operation system Reference" << endl;
		return ;
	}

	// 改operation ref title
	cout << " #operation ref title 前: " << CUSCAAUtilService::GetObjectAttrValue(spNewFO_OPRef, "V_Name") << endl;		// ref title
	CUSCAAUtilService::SetObjectAttrString(spNewFO_OPRef, "V_Name", istrRefsuffix);
	cout << "#operation ref title 后:" << CUSCAAUtilService::GetObjectAttrValue(spNewFO_OPRef, "V_Name") << endl;

	// 改operation inst title；						 inst 后缀 不需要遍历！
	cout << " #operation ins title 前: " << CUSCAAUtilService::GetObjectAttrValue(pNewFO_OPInstance, "PLM_ExternalID") << endl;		// ins title
	CUSCAAUtilService::SetObjectAttrString(pNewFO_OPInstance, "PLM_ExternalID", istrInstsuffix);
	cout << "#operation ins title 后:" << CUSCAAUtilService::GetObjectAttrValue(pNewFO_OPInstance, "PLM_ExternalID") << endl;


	//// 3- 以 spNewFO_OPInstance 为父级 创建 instruction
	//// get 当前的 OP Occ
	//int typeofRoot = 3;						// DELIPPRUIServices::PPRRootType iRootType = 3
	//CATIPLMNavReference_var spRootSysRef = NULL_var;
	//CATIPLMNavOccurrence_var spRootSysOcc;
	//CATIPLMNavOccurrence_var spCurrentSysOcc;
	//CATIPLMNavOccurrence * pCurrentSysOcc;
	//rc = spPPRUtity.GetPPRRootRefNodeFromCurrentEditor(typeofRoot, spRootSysRef);		// 应该 等于 pFO_OPFatherRef，此处的点选（pFO_OPFatherRef）不一定是root！
	//if (FAILED(rc) || (spRootSysRef == NULL_var))
	//{
	//	cout << "==== FAILED  ==== >> spPPRUtity.GetPPRRootRefNodeFromCurrentEditor ! " << endl;
	//	return ;
	//}
	//cout << "==== OK ==== >>spPPRUtity.GetPPRRootRefNodeFromCurrentEditor ! " << endl;

	//rc = spPPRUtity.GetRootOccFromSystemReference(spRootSysRef, spRootSysOcc);
	//if (FAILED(rc) || (spRootSysOcc == NULL_var))
	//{
	//	cout << "==== FAILED  ==== >> spPPRUtity.GetRootOccFromSystemReference ! " << endl;
	//	return ;

	//}
	//cout << "==== OK ==== >>spPPRUtity.GetRootOccFromSystemReference ! " << endl;

	// ipFO_OPFatherRef 对应的Occ
	// 从父级 获取 当前inst 指定的Occ
	CATIPLMNavOccurrence_var spCurrentSysOcc;
	CATIPLMNavOccurrence * pCurrentSysOcc;
	rc = spPPRUtity.GetOccFromSystemFather(ipFO_OPFatherOcc, pNewFO_OPInstance, pCurrentSysOcc);
	if (FAILED(rc) || (pCurrentSysOcc == NULL))
	{
		cout << "==== FAILED  ==== >> spPPRUtity.GetOccFromSystemFather ! " << endl;
		return ;
	}
	cout << "==== OK ==== >>spPPRUtity.GetOccFromSystemFather ! " << endl;

	spCurrentSysOcc = pCurrentSysOcc;
	_RELEASE_PTR_(pCurrentSysOcc);

	rc = spPPRUtity.CreateInsertWorkInstruction(spCurrentSysOcc, ID_WIInstructionType);
	if (FAILED(rc))
	{
		cout << "==== FAILED  ==== >> spPPRUtity.CreateInsertWorkInstruction ! " << endl;
		return ;
	}
	cout << "==== OK ==== >>spPPRUtity.CreateInsertWorkInstruction ! " << endl;

	pNewFO_OPInstance->Release();
	pNewFO_OPInstance = NULL;

	return;
}

//fengy 2022.1.6 op name 是否符合规则
bool ComacInsertFOinstructionCmd::ifNameConformToRule(CATUnicodeString isStartingOprationName, OpNameSplitInfo &onfoOpName)
{
	bool isConformed = false;

	int nNamePreffixNumber = -1;				// op 数字部分！
	bool bAlphaBelta = false;					// 090-A 是否带后缀！
	int  asciiNum = -1;							// 表示不带 字母后缀!
	CATUnicodeString tmpMsg;

	CATListOfCATUnicodeString strOpTitleList;
	fengyHelper::SplitString(isStartingOprationName, "-", strOpTitleList);
	int size1 = strOpTitleList.Size();		// op title  分割
	if (size1 > 2 || size1 == 0)
		return isConformed;
	if (size1 == 1)							// 不带字母后缀
	{
		if (isStartingOprationName.GetLengthInChar() != 3)
			return isConformed;

		nNamePreffixNumber = fengyHelper::Str2Int(isStartingOprationName);
		cout << " nNamePreffixNumber: " << nNamePreffixNumber << endl;
		if (nNamePreffixNumber < 0)
		{
			tmpMsg = "所选工序节点 Str2Int KO!" + isStartingOprationName;
			fengyHelper::Notify(tmpMsg);
			return isConformed;
		}
		// 赋值
		onfoOpName.sNamePreffixAlpha   = isStartingOprationName;
		onfoOpName.nNamePreffixNumber  = nNamePreffixNumber;
		onfoOpName.bSuffix			   = false;
		onfoOpName.nSuffixABC		   = asciiNum;
		return true;

	}
	if (size1 == 2)
	{
		if (strOpTitleList[1].GetLengthInChar() != 3)
			return isConformed;

		nNamePreffixNumber = fengyHelper::Str2Int(strOpTitleList[1]);
		cout << " nNamePreffixNumber: " << nNamePreffixNumber << endl;
		if (nNamePreffixNumber < 0)
		{
			tmpMsg = "所选工序节点 Str2Int KO!" + isStartingOprationName;
			fengyHelper::Notify(tmpMsg);
			return isConformed;
		}

		// 字母转换！
		CATUnicodeString strABC = strOpTitleList[2];
		asciiNum = fengyHelper::getAsciiNum(strABC);

		// 预检
		if (asciiNum>= nAsciiCharA && asciiNum <= nAsciiCharZ)
		{
			// 赋值
			onfoOpName.sNamePreffixAlpha		= strOpTitleList[1];
			onfoOpName.nNamePreffixNumber		= nNamePreffixNumber;
			onfoOpName.bSuffix					= true;
			onfoOpName.nSuffixABC				= asciiNum;
			return true;
		}
		else
			return isConformed;
	}

	return isConformed;
}

// fengy 2022.1.7 整合复用 for 是否重复创建 op 、 instruction
HRESULT ComacInsertFOinstructionCmd::startCreateAction(CATListOfCATUnicodeString istrExistedOPTitleList,
														int inOPNamePreffixNumber,
														bool ibSuffix,
														int inSuffixABC,
														int inOPCount,
														int inOPstep)
{
	HRESULT rc = E_FAIL;
	bool    isToCreateSameOP = false;

	int sizeExisted = istrExistedOPTitleList.Size();
	//CATUnicodeString tmpMsg = "";
	if (sizeExisted > 0)
	{
		CATUnicodeString tmpMsg = "以下工序节点已存在:\n";
		for (int i = 1; i <= sizeExisted; i++)
		{
			tmpMsg.Append(istrExistedOPTitleList[i]);
			if (i != sizeExisted)
				tmpMsg.Append(" , ");
		}
		tmpMsg.Append("\n\n============================\n需要重复创建吗？");

		cout << tmpMsg << endl;
		fengyHelper::NotifyYesOrNO("info...", tmpMsg, isToCreateSameOP);
		cout << "# NotifyYesOrNO: " << isToCreateSameOP << endl;
		if (!isToCreateSameOP)
			//continue;								// 当前重复的节点不创建
			return S_OK;							// 全部不创建
	}


	// 全部创建
	if (_bConCurrentDesign)
	{
		// 一：并行设计
		for (int i = 1; i <= inOPCount; i++)
		{
			CATUnicodeString sNamePreffixAlpha;
			sNamePreffixAlpha.BuildFromNum(inOPNamePreffixNumber /*+ i * inOPstep*/, "%03d");
			cout << " Title sNamePreffixAlpha: " << sNamePreffixAlpha << endl; 
				
			CATUnicodeString c_string = "";
			if (!ibSuffix)			// 选中的OP 不带后缀 ,需加上A
				c_string = fengyHelper::getAsciiCATUnicodeString(i + nAsciiCharA);		// 从B开始
			else
				c_string = fengyHelper::getAsciiCATUnicodeString(i + inSuffixABC);

			CATUnicodeString sOPtitleWithAlpha = sNamePreffixAlpha + "-" + c_string;
			cout << "# 并行工序创建: " << sOPtitleWithAlpha << endl;

			// 判断重复的节点创建？
			int nOccur = _strListOPReftitle.NbOccur(sOPtitleWithAlpha);
			cout << "#已存在 " << nOccur << "个 " << sOPtitleWithAlpha << endl;
			// suffix name
			CATUnicodeString strRefsuffix = sOPtitleWithAlpha;
			CATUnicodeString strInstsuffix = strRefsuffix + "." + fengyHelper::IntToStr(nOccur + 1);		// inst title 修改
			CreateOneOPInstruction(pFO_OPFatherOcc, pFO_OPFatherRef, strRefsuffix, strInstsuffix);

		}
	}
	else
	{
		// 二：非并行设计
		for (int i = 1; i <= inOPCount; i++)
		{
			CATUnicodeString sFormatCode;
			sFormatCode.BuildFromNum(inOPNamePreffixNumber + i * inOPstep, "%03d");
			cout << " Title sFormatCode: " << sFormatCode << endl;

			// 判断重复的节点创建？
			int nOccur = _strListOPReftitle.NbOccur(sFormatCode);
			cout << "#已存在 " << nOccur << "个 " << sFormatCode << endl;
			//if (nOccur > 0)
			//	if (!isToCreateSameOP)
			//		//continue;						// 当前重复的节点不创建
			//		break;							// 全部不创建

			// suffix name
			CATUnicodeString strRefsuffix = sFormatCode;
			CATUnicodeString strInstsuffix = strRefsuffix + "." + fengyHelper::IntToStr(nOccur + 1);		// inst title 修改
			CreateOneOPInstruction(pFO_OPFatherOcc, pFO_OPFatherRef, strRefsuffix, strInstsuffix);

		}
	}
		
	istrExistedOPTitleList.RemoveAll();

	return S_OK;
}