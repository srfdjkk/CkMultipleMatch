#pragma once


// CPAGE4 对话框

class CPAGE4 : public CDialogEx
{
	DECLARE_DYNAMIC(CPAGE4)

public:
	CPAGE4(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPAGE4();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
