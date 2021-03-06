// CModelDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "CKMultipleDemoMatch.h"
#include "CModelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CShapeModelEx::CShapeModelEx()
{

}

CShapeModelEx::~CShapeModelEx()
{
	m_Pat.Release();
}

bool CShapeModelEx::Copy(const CShapeModelEx& src)
{
	if (!CShapeModel::Copy(src))
		return false;

	m_Roi = src.m_Roi;
	m_Pat.Copy(src.m_Pat);
	m_Mask.Copy(src.m_Mask);

	return true;
}

bool CShapeModelEx::Learn(const CPrImage& image, const IRECT& roi)
{
	m_Roi = roi;
	m_Pat.Copy(image);
	m_Mask.Copy(image);
	m_Mask.Clear();
	return CShapeModel::Learn(image, roi);
}

bool CShapeModelEx::Relearn()
{
	return CShapeModel::Learn(m_Pat, m_Mask, m_Roi);
}

bool CShapeModelEx::Exchange(CFileStore& fs)
{
	if (!CShapeModel::Exchange(fs) ||
		!m_Pat.Exchange(fs) ||
		!m_Mask.Exchange(fs)) {
		return false;
	}
	if (fs.IsLoading()) {
		fs.Read(&m_Roi, sizeof(IRECT));
	}
	else {
		fs.Write(&m_Roi, sizeof(IRECT));
	}
	return true;
}

void CShapeModelEx::Release()
{
	m_Pat.Release();
	m_Mask.Release();
	CShapeModel::Release();
}

/////////////////////////////////////////////////////////////////////////////
// CModelDlg dialog



// CModelDlg 对话框
IMPLEMENT_DYNAMIC(CModelDlg, CDialogEx)

CModelDlg::CModelDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MODEL_DLG, pParent)
{
	//感兴趣区域设置
	m_Roi.SetPenColor(RGB(255, 0, 0));

	//轮廓设置
	m_Contour.SetPenWidth(2);
	m_Contour.SetPenColor(RGB(0, 255, 0));

	//
	m_penSt = 0;
	m_PenCl.SetPenColor(RGB(255, 255, 0));
	m_PenCl.SetEnable(false);
	m_PenCl.SetVisible(false);
}

CModelDlg::~CModelDlg()
{
}

void CModelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EDGE, m_ComboEdge);
	DDX_Control(pDX, IDC_SLIDER_PYRAMID, m_SliderCtrl);
}


BEGIN_MESSAGE_MAP(CModelDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModelDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_INDIC, &CModelDlg::OnBnClickedBtnIndic)
	ON_BN_CLICKED(IDC_BTN_MASK, &CModelDlg::OnBnClickedBtnMask)
	ON_BN_CLICKED(IDC_BTN_RECOVNR, &CModelDlg::OnBnClickedBtnRecovnr)

	ON_MESSAGE(GV_WM_MOUSEDRAG, OnGvMouseDrag)
	ON_MESSAGE(GV_WM_MOUSEMOVE, OnGvMouseMove)
	ON_BN_CLICKED(IDC_BTN_RELEARN, &CModelDlg::OnBnClickedBtnRelearn)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDCANCEL, &CModelDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CModelDlg 消息处理程序


void CModelDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Model.SetPercentage(GetDlgItemInt(IDC_EDIT_CHARA_NUM));
	m_Model.SetMinLength(GetDlgItemInt(IDC_EDIT_COUNTOUR));
	m_Model.SetEdgeMode(m_ComboEdge.GetCurSel());

	m_Model.SetMaxPyramid(m_SliderCtrl.GetPos());

	CDialog::OnOK();
	CDialogEx::OnOK();
}


void CModelDlg::OnBnClickedBtnIndic()
{
	// TODO: 在此添加控件通知处理程序代码
	m_penSt = 0;
	m_PenCl.SetVisible(false);
	m_Roi.SetVisible(true);
	m_GdiView.Redraw();
}


void CModelDlg::OnBnClickedBtnMask()
{
	// TODO: 在此添加控件通知处理程序代码
	m_penSt = 1;
	m_PenCl.SetVisible(true);
	m_Roi.SetVisible(false);
	m_GdiView.Redraw();
}


void CModelDlg::OnBnClickedBtnRecovnr()
{
	// TODO: 在此添加控件通知处理程序代码
	m_penSt = 2;
	m_PenCl.SetVisible(true);
	m_Roi.SetVisible(false);
	m_GdiView.Redraw();
}


BOOL CModelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_Slider1.SetRange(0, m_Model.GetModelCount() - 1);
	//m_Slider1.SetPos(0);

	SetDlgItemInt(IDC_EDIT_CHARA_NUM, m_Model.GetPercentage());   //特征数量
	SetDlgItemInt(IDC_EDIT_COUNTOUR, m_Model.GetMinLength());	//轮廓长度

	m_ComboEdge.SetCurSel(m_Model.GetEdgeMode());		//边缘模式

	m_SliderCtrl.SetPos(0);				//金字塔层数
	m_SliderCtrl.SetRange(0, 5);
	CModelContour templ;

	m_Roi = CGdiRect(m_Model.m_Roi);
	m_Center.x = (m_Roi.left + m_Roi.right)*0.5;
	m_Center.y = (m_Roi.top + m_Roi.bottom)*0.5;

	templ.Create(m_Model, 0,
		m_Center.x, m_Center.y, 0, 1.0);

	m_Contour.Create(templ);
	m_Contour.Offset(0.5, 0.5);

	m_MskImg.Build(m_Model.m_Pat, m_Model.m_Mask, 0);

	CRect rect;
	GetDlgItem(IDC_PIC2)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_GdiView.Create(m_hWnd, rect);
	m_GdiView.SetBackColor(RGB(0, 0, 64));
	m_GdiView.SetDisplayImage(&m_MskImg);
	m_GdiView.SetActiveOverlay(&m_Overlay);
	m_GdiView.SetStaticOverlay(&m_Results);
	m_GdiView.SetMessage(GV_MSG_MOUSEDRAG | GV_MSG_LBUTTONDOWN);
	m_GdiView.FitSize();
	m_GdiView.FitScale();

	m_Overlay.AddItem(&m_Roi);
	m_Results.AddItem(&m_Contour);
	m_Results.AddItem(&m_PenCl);

	m_Roi.SetPenColor(RGB(0, 0, 255));
	m_Roi.SetEnable(false);

	SetDlgItemInt(IDC_EDIT_PEN, 5);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



LRESULT CModelDlg::OnGvMouseDrag(WPARAM wParam, LPARAM lParam)
{
	if (m_GdiView.GetLMouseFun() == GV_LMF_POINT) {
		if (m_penSt > 0) {
			double dx = double(LOWORD(lParam));
			double dy = double(HIWORD(lParam));
			m_GdiView.ViewToImage(dx, dy);
			m_PenCl.center.x = dx;
			m_PenCl.center.y = dy;
			m_PenCl.radius = GetDlgItemInt(IDC_EDIT_PEN);
			if (m_penSt == 1) {
				m_Model.m_Mask.Fill(m_PenCl, 255);
			}
			else {
				m_Model.m_Mask.Fill(m_PenCl, 0);
			}
			m_MskImg.Build(m_Model.m_Pat, m_Model.m_Mask, 0);
			m_GdiView.Redraw();
		}
	}
	return 0L;
}

LRESULT CModelDlg::OnGvMouseMove(WPARAM wParam, LPARAM lParam)
{
	if (m_GdiView.GetLMouseFun() == GV_LMF_POINT) {
		if (m_penSt > 0) {
			double dx = double(LOWORD(lParam));
			double dy = double(HIWORD(lParam));
			m_GdiView.ViewToImage(dx, dy);
			m_PenCl.center.x = dx;
			m_PenCl.center.y = dy;
			m_PenCl.radius = GetDlgItemInt(IDC_EDIT_PEN);
			m_GdiView.Redraw();
		}
	}
	return 0L;
}


void CModelDlg::OnBnClickedBtnRelearn()
{
	// TODO: 在此添加控件通知处理程序代码
	m_Model.SetEdgeMode(m_ComboEdge.GetCurSel());
	m_Model.SetPercentage(GetDlgItemInt(IDC_EDIT_CHARA_NUM));
	m_Model.SetMinLength(GetDlgItemInt(IDC_EDIT_COUNTOUR));

	IRECT rc = m_Roi;

	m_Model.Relearn();

	CModelContour templ;

	m_Center.x = (rc.left + rc.right)*0.5;
	m_Center.y = (rc.top + rc.bottom)*0.5;

	templ.Create(m_Model, 0,
		m_Center.x, m_Center.y, 0, 1.0);

	m_Contour.Create(templ);
	m_Contour.Offset(0.5, 0.5);

	m_GdiView.Redraw();
}


void CModelDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strtemp;
	strtemp.Format(_T("%d"), m_SliderCtrl.GetPos());
	GetDlgItem(IDC_STATIC_PYRAMID_NUM)->SetWindowText(strtemp);
	CModelContour templ;

	int i = m_SliderCtrl.GetPos();
	double scale = double(1 << i);

	templ.Create(m_Model, i,
		m_Center.x, m_Center.y, 0, scale);

	m_Contour.Create(templ);
	m_Contour.Offset(0.5, 0.5);

	m_GdiView.Redraw();


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CModelDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
