
// ImageResizeDlg.h : header file
//

#pragma once

#include <memory>


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
  afx_msg void OnBnClickedButtonOpen();
  afx_msg void OnEnKillfocusTargetSizeWL();
  afx_msg void OnEnKillfocusTargetSizeHL();
  afx_msg void OnBnClickedButtonResize();

 private:
  void SaveImage(const std::string& filename, std::shared_ptr<cv::Mat> img);
 private:
  int interpolation_method;
  int src_width;
  int src_height;
  int dst_width;
  int dst_height;
  std::shared_ptr<cv::Mat> img;
 public:
  afx_msg void OnBnClickedRadioNn();
  afx_msg void OnBnClickedRadioBilinear();
  afx_msg void OnBnClickedRadioArea();
  afx_msg void OnBnClickedRadioBicubic();
  afx_msg void OnBnClickedRadioLanczos();
};
