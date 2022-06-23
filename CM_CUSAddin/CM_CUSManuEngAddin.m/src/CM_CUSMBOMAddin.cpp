﻿//===================================================================
// COPYRIGHT  2020/09/16
//===================================================================
// CM_CUSMBOMAddin.cpp
// Header definition of class CM_CUSMBOMAddin
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/09/16 Creation: Code generated by the 3DS wizard
//===================================================================

#include "CM_CUSMBOMAddin.h"

//CATImplementClass(CM_CUSMBOMAddin, DataExtension, CATBaseUnknown, CM_CUSMBOMAddinLT);
CATImplementClass(CM_CUSMBOMAddin, Implementation, CATBaseUnknown, CATNull);


#include "CATIPPRLiveProcessWkbAddin.h"
#include "TIE_CATIPPRLiveProcessWkbAddin.h"
TIE_CATIPPRLiveProcessWkbAddin(CM_CUSMBOMAddin);

#include "TIE_CATIManufacturingSystemDefinitionWorkbenchAddin.h"
//TIE_CATIManufacturingSystemDefinitionWorkbenchAddin(CM_CUSMBOMAddin);

#include "TIE_DELIManufacturingProgramAddin.h"
TIE_DELIManufacturingProgramAddin(CM_CUSMBOMAddin);
//#include "DELIManufacturingProgramAddin.h"
//CATImplementBOA(DELIManufacturingProgramAddin, CM_CUSMBOMAddin)

//#include "TIE_CATIAfrGeneralWksAddin.h"
//TIE_CATIAfrGeneralWksAddin(CM_CUSMBOMAddin);

//-----------------------------------------------------------------------------
// CM_CUSMBOMAddin : constructor
//-----------------------------------------------------------------------------
CM_CUSMBOMAddin::CM_CUSMBOMAddin():CATBaseUnknown()
{
//
//TODO: Add the constructor code here
//
}

//-----------------------------------------------------------------------------
// CM_CUSMBOMAddin : destructor
//-----------------------------------------------------------------------------

CM_CUSMBOMAddin::~CM_CUSMBOMAddin()
{
//
// TODO: Place code here.
//
}

void CM_CUSMBOMAddin::CreateCommands()
{

	//创建401组件
	CATAfrCommandHeader::CATCreateCommandHeader("CMCreateMBOMAssemHdr", "ProcessPlanningService",
		"CMCreateMBOMAssemCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);   //CATFrmUnavailable

	//创建901零件
	CATAfrCommandHeader::CATCreateCommandHeader("CMCreateMakePartHdr", "ProcessPlanningService",
		"CMCreateMakePartCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);

	//制造零组件报表
	CATAfrCommandHeader::CATCreateCommandHeader("CMCreateMBOMReportHdr", "ProcessPlanningService",
		"CMMBOMReportCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);

	//401组件升版
	CATAfrCommandHeader::CATCreateCommandHeader("CMChangeMBOMAssemHdr", "ProcessPlanningService",
		"CMChangeMBOMAssemCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);   //CATFrmUnavailable

	//紧固件设计
	CATAfrCommandHeader::CATCreateCommandHeader("CMMBOMFastenHdr", "ProcessPlanningService",
		"CMMBOMFastenCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);   //CATFrmUnavailable

	//901零件换号
	CATAfrCommandHeader::CATCreateCommandHeader("CMChangeMakePartHdr", "ProcessPlanningService",
		"CMChangeMakePartCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);

	//WA100 手动computeResult
	CATAfrCommandHeader::CATCreateCommandHeader("ComacComputeReslutingProductHdr", "ProcessPlanningService",
		"ComacComputeReslutingProductCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);


	//// 协作BOM 规划  ComacGenerateBOMCmd 
	//CATAfrCommandHeader::CATCreateCommandHeader("ComacGenerateBOMHdr", "ProcessPlanningService",
	//	"ComacGenerateBOMCmd", (void *)NULL,
	//	"CMMECommandHeader", CATFrmAvailable);

	// 8 特制件、垫片添加		ComacInsertSpecialPartOrGasketCmd
	CATAfrCommandHeader::CATCreateCommandHeader("ComacInsertSpecialPartOrGasketHdr", "ProcessPlanningService",
		"ComacInsertSpecialPartOrGasketCmd", (void *)NULL,
		"CMMECommandHeader", CATFrmAvailable);


}
CATCmdContainer *CM_CUSMBOMAddin::CreateToolbars()
{
	NewAccess(CATCmdContainer, pCMMBOMSection, CMMBOMSection);

	NewAccess(CATCmdContainer, pCMMBOMTlb, CMMBOMTlb);
	SetAccessChild(pCMMBOMSection, pCMMBOMTlb);

	//401组件
	NewAccess(CATCmdStarter, pCMMBOMAssembly, CMMBOMAssembly);
	SetAccessCommand(pCMMBOMAssembly, "CMCreateMBOMAssemHdr");
	SetAccessChild(pCMMBOMTlb, pCMMBOMAssembly);

	//901零件
	NewAccess(CATCmdStarter, pCMMBOMPart, CMMBOMPart);
	SetAccessCommand(pCMMBOMPart, "CMCreateMakePartHdr");
	SetAccessNext(pCMMBOMAssembly, pCMMBOMPart);

	//制造零组件报表
	NewAccess(CATCmdStarter, pCMMBOMReport, CMMBOMReport);
	SetAccessCommand(pCMMBOMReport, "CMCreateMBOMReportHdr");
	SetAccessNext(pCMMBOMPart, pCMMBOMReport);

	//401组件换号
	NewAccess(CATCmdStarter, pCMChangeMBOMAssembly, CMChangeMBOMAssembly);
	SetAccessCommand(pCMChangeMBOMAssembly, "CMChangeMBOMAssemHdr");
	SetAccessNext(pCMMBOMReport, pCMChangeMBOMAssembly);

	//紧固件设计
	NewAccess(CATCmdStarter, pCMMBOMFasten, CMMBOMFasten);
	SetAccessCommand(pCMMBOMFasten, "CMMBOMFastenHdr");
	SetAccessNext(pCMChangeMBOMAssembly, pCMMBOMFasten);

	////901零件
	//NewAccess(CATCmdStarter, pCMChangeMakePart, CMChangeMakePart);
	//SetAccessCommand(pCMChangeMakePart, "CMChangeMakePartHdr");
	//SetAccessNext(pCMChangeMBOMAssembly, pCMChangeMakePart);

	//901零件
	NewAccess(CATCmdStarter, pCMChangeMakePart, CMChangeMakePart);
	SetAccessCommand(pCMChangeMakePart, "CMChangeMakePartHdr");
	SetAccessNext(pCMMBOMFasten, pCMChangeMakePart);

	//WA100 手动批量 computeResult
	NewAccess(CATCmdStarter, pComacComputeReslutingProduct, ComacComputeReslutingProduct);
	SetAccessCommand(pComacComputeReslutingProduct, "ComacComputeReslutingProductHdr");
	SetAccessNext(pCMChangeMakePart, pComacComputeReslutingProduct);

	//// 协作BOM 规划  ComacGenerateBOM
	//NewAccess(CATCmdStarter, pComacGenerateBOM, ComacGenerateBOM);
	//SetAccessCommand(pComacGenerateBOM, "ComacGenerateBOMHdr");
	//SetAccessNext(pComacComputeReslutingProduct, pComacGenerateBOM);

	// 特制件、垫片添加		ComacInsertSpecialPartOrGasketCmd
	NewAccess(CATCmdStarter, pComacInsertSpecialPartOrGasket, ComacInsertSpecialPartOrGasket);
	SetAccessCommand(pComacInsertSpecialPartOrGasket, "ComacInsertSpecialPartOrGasketHdr");
	SetAccessNext(pComacComputeReslutingProduct, pComacInsertSpecialPartOrGasket);

	AddToolbarView(pCMMBOMTlb, -1, UnDock);

	return pCMMBOMSection;
}