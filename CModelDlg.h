#if !defined(AFX_MODELDLG_H__99B661FB_505F_4854_8082_AAC597DA1A46__INCLUDED_)
#define AFX_MODELDLG_H__99B661FB_505F_4854_8082_AAC597DA1A46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModelDlg.h : header file
//

/* 形状模板 */
class CShapeModelEx : public CShapeModel
{
public:
	CShapeModelEx();

	~CShapeModelEx();

	bool Copy(const CShapeModelEx& src);

	bool Learn(const CPrImage& image, const IRECT& roi);

	bool Relearn();

	bool Exchange(CFileStore& fs);

	void Release();

public:
	IRECT			m_Roi;
	CPrImage		m_Pat;
	CMask			m_Mask;
};

// CModelDlg 对话框

class CModelDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModelDlg)

public:
	CModelDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CModelDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODEL_DLG };
#endif

	CShapeModelEx	m_Model;
	CGdiView		m_GdiView;
	COverlay		m_Overlay;
	COverlay		m_Results;
	CGdiFrame		m_Frame;
	CGdiRect		m_Roi;
	CGdiContour		m_Contour;
	CMaskImage		m_MskImg;


	DPNT			m_Center;
	CGdiCircle		m_PenCl;
	int				m_penSt;



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedBtnIndic();
	afx_msg void OnBnClickedBtnMask();
	afx_msg void OnBnClickedBtnRecovnr();

	afx_msg LRESULT OnGvMouseDrag(WPARAM wParam, LPARAM lPAram);
	afx_msg LRESULT OnGvMouseMove(WPARAM wParam, LPARAM lPAram);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRelearn();
	CComboBox m_ComboEdge;
	// 金字塔 滑杆
	CSliderCtrl m_SliderCtrl;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedCancel();
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELDLG_H__99B661FB_505F_4854_8082_AAC597DA1A46__INCLUDED_)