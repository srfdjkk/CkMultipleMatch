// CLearnDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CKMultipleDemoMatch.h"
#include "CLearnDlg.h"
#include "afxdialogex.h"
#include "CKMultipleDemoMatchDlg.h"
#include "CModelDlg.h"
extern CKMultipleDemoMatchDlg* pCKMultipleDemoMatchDlg;
// CLearnDlg 对话框

IMPLEMENT_DYNAMIC(CLearnDlg, CDialogEx)

CLearnDlg::CLearnDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEARN_DLG, pParent)
{

}

CLearnDlg::~CLearnDlg()
{
}

void CLearnDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLearnDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLearnDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLearnDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLearnDlg 消息处理程序


void CLearnDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	pCKMultipleDemoMatchDlg->UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_page2.ShowWindow(true);
	pCKMultipleDemoMatchDlg->m_learnDlg.ShowWindow(false);
	pCKMultipleDemoMatchDlg->m_lRoi.SetVisible(true);
	pCKMultipleDemoMatchDlg->m_GdiView.Redraw();
	try
	{
		CShapeModelEx* pNew = new CShapeModelEx;

		//学习模板
		BOOL le = pNew->Learn(pCKMultipleDemoMatchDlg->m_Image, pCKMultipleDemoMatchDlg->m_lRoi);

		if (le)
		{
			pCKMultipleDemoMatchDlg->m_Models.Add(pNew);
		}
		else
		{
			delete pNew;
			return;
		}

		CString text;
		text.Format(_T("Model_%d"), pCKMultipleDemoMatchDlg->m_Models.GetCount());
		pCKMultipleDemoMatchDlg->m_page2.m_ListBox1.AddString(text);

	}
	catch (...)
	{

	}

	CDialogEx::OnOK();
}


void CLearnDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	pCKMultipleDemoMatchDlg->m_page2.ShowWindow(true);
	pCKMultipleDemoMatchDlg->m_learnDlg.ShowWindow(false);
	pCKMultipleDemoMatchDlg->m_lRoi.SetVisible(false);
	CDialogEx::OnCancel();
}
