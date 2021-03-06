// CPAGE2.cpp: 实现文件
//

#include "stdafx.h"
#include "CKMultipleDemoMatch.h"
#include "CPAGE2.h"
#include "afxdialogex.h"
#include "CKMultipleDemoMatchDlg.h"
#include "CModelDlg.h"
extern CKMultipleDemoMatchDlg* pCKMultipleDemoMatchDlg;

// CPAGE2 对话框

IMPLEMENT_DYNAMIC(CPAGE2, CDialogEx)

CPAGE2::CPAGE2(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_MaxCount(0)
	, m_iMinScore(0)
	, m_iMinAngle(0)
	, m_iMaxAngle(0)
	, m_iMinScale(0)
	, m_iMaxScale(0)
	, m_iMaxOverlap(0)
	, m_iSpeed(0)
	, m_iAccuracy(0)
	, m_iPolarity(0)
{

}

CPAGE2::~CPAGE2()
{
}

void CPAGE2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MODEL, m_ListBox1);
	DDX_Text(pDX, IDC_EDIT_MAXCOUNT, m_MaxCount);
	DDX_Text(pDX, IDC_EDIT_MINSCORE, m_iMinScore);
	DDV_MinMaxInt(pDX, m_iMinScore, 1, 100);
	DDX_Text(pDX, IDC_EDIT_MINANGLE, m_iMinAngle);
	DDV_MinMaxInt(pDX, m_iMinAngle, -180, 180);
	DDX_Text(pDX, IDC_EDIT_MAXANGLE, m_iMaxAngle);
	DDV_MinMaxInt(pDX, m_iMaxAngle, -180, 180);
	DDX_Text(pDX, IDC_EDIT_MINSCALE, m_iMinScale);
	DDV_MinMaxInt(pDX, m_iMinScale, 50, 200);
	DDX_Text(pDX, IDC_EDIT_MAXSCALE, m_iMaxScale);
	DDV_MinMaxInt(pDX, m_iMaxScale, 50, 200);
	DDX_Text(pDX, IDC_EDIT_MAXOVERLAP, m_iMaxOverlap);
	DDX_CBIndex(pDX, IDC_COMBO_SPEED, m_iSpeed);
	DDV_MinMaxInt(pDX, m_iSpeed, 0, 10);
	DDX_CBIndex(pDX, IDC_COMBO_ACCURACY, m_iAccuracy);
	DDV_MinMaxInt(pDX, m_iAccuracy, 0, 10);
	DDX_Control(pDX, IDC_COMBO_SPEED, m_CCbox_Speed);
	DDX_Control(pDX, IDC_COMBO_ACCURACY, m_CCbox_Accuracy);
	DDX_Control(pDX, IDC_COMBO_POLARITY, m_CCbox_Polarity);

	DDX_CBIndex(pDX, IDC_COMBO_POLARITY, m_iPolarity);
	DDV_MinMaxInt(pDX, m_iPolarity, 0, 2);
}


BEGIN_MESSAGE_MAP(CPAGE2, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_MODEL_ADD, &CPAGE2::OnBnClickedBtnModelAdd)
	ON_BN_CLICKED(IDC_BTN_MODEL_DEL, &CPAGE2::OnBnClickedBtnModelDel)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CPAGE2::OnBnClickedBtnSave)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CPAGE2::OnBnClickedBtnLoad)
	ON_EN_KILLFOCUS(IDC_EDIT_MAXCOUNT, &CPAGE2::OnEnKillfocusEditMaxcount)
	ON_EN_KILLFOCUS(IDC_EDIT_MINSCORE, &CPAGE2::OnEnKillfocusEditMinscore)
	ON_EN_KILLFOCUS(IDC_EDIT_MINANGLE, &CPAGE2::OnEnKillfocusEditMinangle)
	ON_EN_KILLFOCUS(IDC_EDIT_MAXANGLE, &CPAGE2::OnEnKillfocusEditMaxangle)
	ON_EN_KILLFOCUS(IDC_EDIT_MINSCALE, &CPAGE2::OnEnKillfocusEditMinscale)
	ON_EN_KILLFOCUS(IDC_EDIT_MAXSCALE, &CPAGE2::OnEnKillfocusEditMaxscale)
	ON_EN_KILLFOCUS(IDC_EDIT_MAXOVERLAP, &CPAGE2::OnEnKillfocusEditMaxoverlap)
	ON_CBN_SELCHANGE(IDC_COMBO_SPEED, &CPAGE2::OnCbnSelchangeComboSpeed)
	ON_CBN_SELCHANGE(IDC_COMBO_ACCURACY, &CPAGE2::OnCbnSelchangeComboAccuracy)
	ON_CBN_SELCHANGE(IDC_COMBO_POLARITY, &CPAGE2::OnCbnSelchangeComboPolarity)
	ON_BN_CLICKED(IDC_BTN_EDIT, &CPAGE2::OnBnClickedBtnEdit)
END_MESSAGE_MAP()


// CPAGE2 消息处理程序


void CPAGE2::OnBnClickedBtnModelAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_lRoi.SetVisible(true);
	pCKMultipleDemoMatchDlg->m_GdiView.Redraw();
	//显示学习模板对话框
	pCKMultipleDemoMatchDlg->m_page2.ShowWindow(false);
	pCKMultipleDemoMatchDlg->m_learnDlg.ShowWindow(true);


}

/***********************************************************
*FunctionName:	OnBnClickedBtnModelDel()
*Description:	删除模板列表中的模板号
*parameter  :	无
*return		:	无
************************************************************/
void CPAGE2::OnBnClickedBtnModelDel()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_ListBox1.GetCurSel();
	if (index >= 0)
	{
		m_ListBox1.DeleteString(index);
		delete pCKMultipleDemoMatchDlg->m_Models.RemoveAt(index);
	}
}

/***********************************************************
*FunctionName:	OnBnClickedBtnSave()
*Description:	保存模板
*parameter  :	无
*return		:	无
************************************************************/
void CPAGE2::OnBnClickedBtnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fd(FALSE, __T(""), NULL,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("模板文件(*.mods)|*.mods||"));
	fd.m_ofn.lpstrTitle = _T("保存模板");
	if (fd.DoModal() == IDOK)
	{
		CFileStore fs;
		USES_CONVERSION;
		if (fs.Open(W2A(fd.GetPathName()), CFileStore::save))
		{
			int nCount = pCKMultipleDemoMatchDlg->m_Models.GetCount();

			fs.Write(&nCount, sizeof(int));

			for (int i = 0; i < nCount; i++)
			{
				((CShapeModelEx*)pCKMultipleDemoMatchDlg->m_Models[i])->Exchange(fs);
			}

			fs.Close();
		}
	}
}

/***********************************************************
*FunctionName:	OnBnClickedBtnLoad()
*Description:	装载模板
*parameter  :	无
*return		:	无
************************************************************/
void CPAGE2::OnBnClickedBtnLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fd(TRUE, _T(""), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("模板文件(*.mods)|*.mods||"));
	fd.m_ofn.lpstrTitle = _T("装载模板");
	if (fd.DoModal() == IDOK)
	{
		CFileStore fs;
		USES_CONVERSION;
		if (fs.Open(W2A(fd.GetPathName()), CFileStore::load))
		{
			int nCount = 0;

			fs.Read(&nCount, sizeof(int));

			for (int i = 0; i < pCKMultipleDemoMatchDlg->m_Models.GetCount(); i++)
			{
				delete pCKMultipleDemoMatchDlg->m_Models[i];
			}
			pCKMultipleDemoMatchDlg->m_Models.RemoveAll();
			m_ListBox1.ResetContent();

			CString text;
			for (int i = 0; i < nCount; i++)
			{
				CShapeModelEx* pNew = new CShapeModelEx;

				pNew->Exchange(fs);
				pCKMultipleDemoMatchDlg->m_Models.Add(pNew);

				text.Format(_T("Model_%d"), i + 1);
				m_ListBox1.AddString(text);
			}

			fs.Close();
		}
	}
}


void CPAGE2::OnEnKillfocusEditMaxcount()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMaxCount = m_MaxCount;
}


void CPAGE2::OnEnKillfocusEditMinscore()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMinScore = m_iMinScore;
}


void CPAGE2::OnEnKillfocusEditMinangle()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMinAngle = m_iMinAngle;
}


void CPAGE2::OnEnKillfocusEditMaxangle()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMaxAngle = m_iMaxAngle;
}


void CPAGE2::OnEnKillfocusEditMinscale()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMinAngle = m_iMinAngle;
}


void CPAGE2::OnEnKillfocusEditMaxscale()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMaxScale = m_iMaxScale;
}


void CPAGE2::OnEnKillfocusEditMaxoverlap()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMaxOverlap = m_iMaxOverlap;
}


void CPAGE2::OnCbnSelchangeComboSpeed()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iMaxSpeed = m_CCbox_Speed.GetCurSel();
}



void CPAGE2::OnCbnSelchangeComboAccuracy()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iAccuracy = m_CCbox_Accuracy.GetCurSel();
}



void CPAGE2::OnCbnSelchangeComboPolarity()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	pCKMultipleDemoMatchDlg->m_GetMatchParam.iPolarity= m_CCbox_Polarity.GetCurSel();
}


void CPAGE2::OnBnClickedBtnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	int i = m_ListBox1.GetCurSel();
	if (i >= 0)
	{
		CModelDlg dlg;
		dlg.m_Model.Copy(*((CShapeModelEx*)pCKMultipleDemoMatchDlg->m_Models[i]));
		if (dlg.DoModal() == IDOK)
		{
			pCKMultipleDemoMatchDlg->m_Models[i]->Copy(dlg.m_Model);
		}
	}
}
