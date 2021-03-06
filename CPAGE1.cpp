// CPAGE1.cpp: 实现文件
//

#include "stdafx.h"
#include "CKMultipleDemoMatch.h"
#include "CPAGE1.h"
#include "afxdialogex.h"
#include "CKMultipleDemoMatchDlg.h"
// CPAGE1 对话框
extern CKMultipleDemoMatchDlg* pCKMultipleDemoMatchDlg;
IMPLEMENT_DYNAMIC(CPAGE1, CDialogEx)

CPAGE1::CPAGE1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PAGE1, pParent)
{

}

CPAGE1::~CPAGE1()
{

}

void CPAGE1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_IMAGE, m_combox_image);
}


BEGIN_MESSAGE_MAP(CPAGE1, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NULL, &CPAGE1::OnBnClickedBtnNull)
	ON_BN_CLICKED(IDC_BTN_RECT1, &CPAGE1::OnBnClickedBtnRect1)
	ON_BN_CLICKED(IDC_BTN_RECT2, &CPAGE1::OnBnClickedBtnRect2)
	ON_BN_CLICKED(IDC_BTN_LINKPIC, &CPAGE1::OnBnClickedBtnLinkpic)
END_MESSAGE_MAP()


// CPAGE1 消息处理程序


void CPAGE1::PImageParamToCPrImage(CPrImage* Dest, ImageParam*str)
{
	//int m_nWidth;//图片宽
	//int m_nHeight;//图片高
	//int m_nChannel;//图片通道数
	//int m_nSize;//m_pData指向的数据大小（byte）
	//int m_nPtrType;//指针类型0=byte* ;1=HObject*
	//void* m_pData;//图片数据

	Dest->Create(str->m_nWidth, str->m_nHeight, str->m_nChannel);
	Dest->SetBits((BYTE*)str->m_pData, false);
}

/*
清楚ROI绘制
*/
void CPAGE1::OnBnClickedBtnNull()
{
	// TODO: 在此添加控件通知处理程序代码

	pCKMultipleDemoMatchDlg->m_sRectROI.SetVisible(false);
	pCKMultipleDemoMatchDlg->m_sRotBoxROI.SetVisible(false);

	pCKMultipleDemoMatchDlg->m_GdiView.Redraw();
}

/*
绘制不带方向矩阵
*/
void CPAGE1::OnBnClickedBtnRect1()
{
	// TODO: 在此添加控件通知处理程序代码

	if (!pCKMultipleDemoMatchDlg->m_sRectROI.GetVisible())
	{
		pCKMultipleDemoMatchDlg->m_sRectROI.SetVisible(true);

	}
	else {
		pCKMultipleDemoMatchDlg->m_sRectROI.SetVisible(false);

	}
	pCKMultipleDemoMatchDlg->m_GdiView.Redraw();
}

/*
绘制带方向矩阵
*/
void CPAGE1::OnBnClickedBtnRect2()
{
	// TODO: 在此添加控件通知处理程序代码

	if (!pCKMultipleDemoMatchDlg->m_sRotBoxROI.GetVisible())
	{
		pCKMultipleDemoMatchDlg->m_sRotBoxROI.SetVisible(true);

	}
	else
	{
		pCKMultipleDemoMatchDlg->m_sRotBoxROI.SetVisible(false);
	}
	pCKMultipleDemoMatchDlg->m_GdiView.Redraw();
	
}


void CPAGE1::OnBnClickedBtnLinkpic()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR cDocName[MAX_PATH], cNodeName[MAX_PATH], cParamName[MAX_PATH];
	int iNodeID, iIndex, iType;
	int irt = HIDBSelectLink(cDocName, &iNodeID, cNodeName, cParamName, &iType, &iIndex);
	if (iType == NODETYPE_PIMAGE)
	{
		m_iNodeID = iNodeID;
		m_iIndex = iIndex;
		_tcscpy_s(m_cDocName, MAX_PATH, cDocName);
		_tcscpy_s(m_cNodeName, MAX_PATH, cNodeName);
		_tcscpy_s(m_cParamName, MAX_PATH, cParamName);

		PImageParam imagep;
		int n = 1;
		int irt = HIDBGetImagePointer(cDocName, iNodeID, cNodeName, cParamName, &imagep, &n, iIndex);

		//如果取图成功
		if (irt >= 0)
		{
			//转格式
			PImageParamToCPrImage(&m_prImage, imagep);
			//图片显示
			CString strImgInfo;
			strImgInfo.Format(_T("%d*%d,bit=%d"), m_prImage.GetHeight(), m_prImage.GetWidth(), m_prImage.GetFormat()*8);
			pCKMultipleDemoMatchDlg->SetDlgItemText(IDC_EDIT_IMGINFO,strImgInfo);

			pCKMultipleDemoMatchDlg->m_Image.Copy(m_prImage);
			pCKMultipleDemoMatchDlg->m_GdiView.FitSize();
			pCKMultipleDemoMatchDlg->m_GdiView.FitScale();
			m_combox_image.AddString(cNodeName);
			m_combox_image.SelectString(0, cNodeName);


			//保存状态
			pCKMultipleDemoMatchDlg->m_GetMatchParam.str_ImageName = cNodeName;
		}

		HIDBDeleteBuf(imagep);
	}
}
