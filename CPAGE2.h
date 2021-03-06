#pragma once
#include "CPAGE1.h"

// CPAGE2 对话框

class CPAGE2 : public CDialogEx
{
	DECLARE_DYNAMIC(CPAGE2)

public:
	CPAGE2(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPAGE2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PAGE2};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnModelAdd();
	afx_msg void OnBnClickedBtnModelDel();
	// //模板列表
	CListBox m_ListBox1;
	afx_msg void OnBnClickedBtnSave();
	afx_msg void OnBnClickedBtnLoad();
	// 最大搜索数量
	int m_MaxCount;
	// 最小分数
	int m_iMinScore;
	// 最小角度
	int m_iMinAngle;
	// 最大角度
	int m_iMaxAngle;
	// 最小比例
	int m_iMinScale;
	int m_iMaxScale;
	// 最大重叠数量
	int m_iMaxOverlap;
	// 搜索速度
	int m_iSpeed;
	// 定位精度
	int m_iAccuracy;
	CComboBox m_CCbox_Speed;
	CComboBox m_CCbox_Accuracy;
	CComboBox m_CCbox_Polarity;
	// 匹配极性

	// 匹配极性 0正常 1反转 2任意
	int m_iPolarity;
	afx_msg void OnEnKillfocusEditMaxcount();
	afx_msg void OnEnKillfocusEditMinscore();
	afx_msg void OnEnKillfocusEditMinangle();
	afx_msg void OnEnKillfocusEditMaxangle();
	afx_msg void OnEnKillfocusEditMinscale();
	afx_msg void OnEnKillfocusEditMaxscale();
	afx_msg void OnEnKillfocusEditMaxoverlap();
	afx_msg void OnCbnSelchangeComboSpeed();
	afx_msg void OnCbnSelchangeComboAccuracy();
	afx_msg void OnCbnSelchangeComboPolarity();
	afx_msg void OnBnClickedBtnEdit();
};
