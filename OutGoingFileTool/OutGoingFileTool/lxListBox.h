#pragma once


// lxListBox 对话框

#include "FIlestruct.h"
#include <memory>
class lxListBox : public CListCtrl
{

	DECLARE_DYNAMIC(lxListBox)

public:
#define   WM_USER_CHANGE_LIST  (WM_USER + 0x100);
	afx_msg VOID OnDropFiles(HDROP hDropInfo);
	lxListBox(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~lxListBox();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	std::shared_ptr<rjFileInfo> FileInfo;
	DECLARE_MESSAGE_MAP()
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTGOINGFILETOOL_DIALOG };
#endif

protected:

};
