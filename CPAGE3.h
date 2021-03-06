#pragma once


// CPAGE3 对话框

class CPAGE3 : public CDialogEx
{
	DECLARE_DYNAMIC(CPAGE3)

public:
	CPAGE3(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPAGE3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// //显示查找结果
	CListCtrl m_ListCtrl;
	afx_msg void OnBnClickedCheck1();
	CButton m_CheckNum;
	CButton m_CheckX;
	CButton m_CheckY;
	CButton m_CheckAngle;
	CButton m_CheckScale;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	virtual BOOL OnInitDialog();
	CComboBox m_Combo_Hori;
	CComboBox m_Combo_Vert;
	int m_iNumDown;
	int m_iNumUp;
	int m_iXDown;
	int m_iXUp;
	int m_iYDown;
	int m_iYUp;
	int m_iAngleDown;
	int m_iAngleUp;
	double m_dScaleDown;
	double m_dScaleUp;
	BOOL m_Num;
	BOOL m_PosX;
	BOOL m_PosY;
	BOOL m_Angle;
	BOOL m_Scale;
};
