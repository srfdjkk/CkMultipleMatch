// CPAGE3.cpp: 实现文件
//

#include "stdafx.h"
#include "CKMultipleDemoMatch.h"
#include "CPAGE3.h"
#include "afxdialogex.h"


// CPAGE3 对话框

IMPLEMENT_DYNAMIC(CPAGE3, CDialogEx)

CPAGE3::CPAGE3(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_Num(FALSE)
	, m_PosX(FALSE)
	, m_PosY(FALSE)
	, m_Angle(FALSE)
	, m_Scale(FALSE)
{

}

CPAGE3::~CPAGE3()
{
}

void CPAGE3::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST2, m_ListCtrl);
	DDX_Control(pDX, IDC_CHECK1, m_CheckNum);
	DDX_Control(pDX, IDC_CHECK2, m_CheckX);
	DDX_Control(pDX, IDC_CHECK3, m_CheckY);
	DDX_Control(pDX, IDC_CHECK4, m_CheckAngle);
	DDX_Control(pDX, IDC_CHECK5, m_CheckScale);
	DDX_Control(pDX, IDC_COMBO_HORI, m_Combo_Hori);
	DDX_Control(pDX, IDC_COMBO_VERT, m_Combo_Vert);
	DDX_Text(pDX, IDC_EDIT1, m_iNumDown);
	DDX_Text(pDX, IDC_EDIT2, m_iNumUp);
	DDX_Text(pDX, IDC_EDIT3, m_iXDown);
	DDX_Text(pDX, IDC_EDIT4, m_iXUp);
	DDX_Text(pDX, IDC_EDIT5, m_iYDown);
	DDX_Text(pDX, IDC_EDIT6, m_iYUp);
	DDX_Text(pDX, IDC_EDIT7, m_iAngleDown);
	DDX_Text(pDX, IDC_EDIT8, m_iAngleUp);
	DDX_Text(pDX, IDC_EDIT9, m_dScaleDown);
	DDX_Text(pDX, IDC_EDIT10, m_dScaleUp);
	DDX_Check(pDX, IDC_CHECK1, m_Num);
	DDX_Check(pDX, IDC_CHECK2, m_PosX);
	DDX_Check(pDX, IDC_CHECK3, m_PosY);
	DDX_Check(pDX, IDC_CHECK4, m_Angle);
	DDX_Check(pDX, IDC_CHECK5, m_Scale);
}


BEGIN_MESSAGE_MAP(CPAGE3, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK1, &CPAGE3::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CPAGE3::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CPAGE3::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CPAGE3::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CPAGE3::OnBnClickedCheck5)
END_MESSAGE_MAP()


// CPAGE3 消息处理程序


void CPAGE3::OnBnClickedCheck1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_CheckNum.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	}
}


void CPAGE3::OnBnClickedCheck2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_CheckX.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT3)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	}
}


void CPAGE3::OnBnClickedCheck3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_CheckY.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	}
}


void CPAGE3::OnBnClickedCheck4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_CheckAngle.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT7)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT8)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	}
}


void CPAGE3::OnBnClickedCheck5()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_CheckScale.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT9)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);
	}
}


BOOL CPAGE3::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_Combo_Hori.SetCurSel(0);
	m_Combo_Vert.SetCurSel(0);

	GetDlgItem(IDC_EDIT1)->SetWindowTextW(_T("1"));
	GetDlgItem(IDC_EDIT2)->SetWindowTextW(_T("100"));
	GetDlgItem(IDC_EDIT3)->SetWindowTextW(_T("-99999"));
	GetDlgItem(IDC_EDIT4)->SetWindowTextW(_T("99999"));
	GetDlgItem(IDC_EDIT5)->SetWindowTextW(_T("-99999"));
	GetDlgItem(IDC_EDIT6)->SetWindowTextW(_T("99999"));
	GetDlgItem(IDC_EDIT7)->SetWindowTextW(_T("-180"));
	GetDlgItem(IDC_EDIT8)->SetWindowTextW(_T("180"));
	GetDlgItem(IDC_EDIT9)->SetWindowTextW(_T("0.5"));
	GetDlgItem(IDC_EDIT10)->SetWindowTextW(_T("2"));

	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT5)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT6)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT7)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT9)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT10)->EnableWindow(FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
