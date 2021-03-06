#pragma once


// CPAGE1 对话框

enum EBUTTONTYPE
{
	BTN_NULL = 0,
	BTN_RECT1,   //不带方向矩阵
	BTN_RECT2  //旋转矩阵
};

class CPAGE1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPAGE1)

public:
	CPAGE1(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPAGE1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	//输入数据信息
	TCHAR m_cDocName[MAX_PATH], m_cNodeName[MAX_PATH], m_cParamName[MAX_PATH];
	int m_iNodeID, m_iIndex;
	// 图片下拉列表
	CComboBox m_combox_image;
	CPrImage m_prImage;
	void CPAGE1::PImageParamToCPrImage(CPrImage* Dest, ImageParam*str);
	afx_msg void OnBnClickedBtnNull();
	afx_msg void OnBnClickedBtnRect1();
	afx_msg void OnBnClickedBtnRect2();
	afx_msg void OnBnClickedBtnLinkpic();

};
