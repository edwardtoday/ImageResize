
// ImageResizeDlg.h : header file
//

#pragma once


// CImageResizeDlg dialog
class CImageResizeDlg : public CDialogEx {
// Construction
 public:
  CImageResizeDlg(CWnd* pParent = NULL);  // standard constructor

// Dialog Data
  enum { IDD = IDD_IMAGERESIZE_DIALOG };

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support


// Implementation
 protected:
  HICON m_hIcon;

  // Generated message map functions
  virtual BOOL OnInitDialog();
  afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
  afx_msg void OnPaint();
  afx_msg HCURSOR OnQueryDragIcon();
  DECLARE_MESSAGE_MAP()
 public:
  afx_msg void OnBnClickedButton1();
  afx_msg void OnBnClickedButtonOpen();
  afx_msg void OnEnKillfocusTargetSizeWL();
  afx_msg void OnEnKillfocusTargetSizeHL();
};
