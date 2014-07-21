
// ImageResizeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageResize.h"
#include "ImageResizeDlg.h"
#include "afxdialogex.h"

#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
 public:
  CAboutDlg();

// Dialog Data
  enum { IDD = IDD_ABOUTBOX };

 protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
 protected:
  DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CImageResizeDlg dialog



CImageResizeDlg::CImageResizeDlg(CWnd* pParent /*=NULL*/)
  : CDialogEx(CImageResizeDlg::IDD, pParent) {
  m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CImageResizeDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CImageResizeDlg, CDialogEx)
  ON_WM_SYSCOMMAND()
  ON_WM_PAINT()
  ON_WM_QUERYDRAGICON()
  ON_BN_CLICKED(IDC_BUTTON_OPEN, &CImageResizeDlg::OnBnClickedButtonOpen)
  ON_EN_KILLFOCUS(IDC_TARGET_SIZE_W_L,
                  &CImageResizeDlg::OnEnKillfocusTargetSizeWL)
  ON_EN_KILLFOCUS(IDC_TARGET_SIZE_H_L,
                  &CImageResizeDlg::OnEnKillfocusTargetSizeHL)
END_MESSAGE_MAP()


// CImageResizeDlg message handlers

BOOL CImageResizeDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();
  // Add "About..." menu item to system menu.
  // IDM_ABOUTBOX must be in the system command range.
  ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
  ASSERT(IDM_ABOUTBOX < 0xF000);
  CMenu* pSysMenu = GetSystemMenu(FALSE);

  if (pSysMenu != NULL) {
    BOOL bNameValid;
    CString strAboutMenu;
    bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
    ASSERT(bNameValid);

    if (!strAboutMenu.IsEmpty()) {
      pSysMenu->AppendMenu(MF_SEPARATOR);
      pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
    }
  }

  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);     // Set big icon
  SetIcon(m_hIcon, FALSE);    // Set small icon
  // TODO: Add extra initialization here
  ((CButton*)GetDlgItem(IDC_RADIO_AREA))->SetCheck(true);
  ((CButton*)GetDlgItem(IDC_TARGET_SIZE_KEEP_ASPECT))->SetCheck(true);
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CImageResizeDlg::OnSysCommand(UINT nID, LPARAM lParam) {
  if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
    CAboutDlg dlgAbout;
    dlgAbout.DoModal();
  } else {
    CDialogEx::OnSysCommand(nID, lParam);
  }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CImageResizeDlg::OnPaint() {
  if (IsIconic()) {
    CPaintDC dc(this); // device context for painting
    SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
    // Center icon in client rectangle
    int cxIcon = GetSystemMetrics(SM_CXICON);
    int cyIcon = GetSystemMetrics(SM_CYICON);
    CRect rect;
    GetClientRect(&rect);
    int x = (rect.Width() - cxIcon + 1) / 2;
    int y = (rect.Height() - cyIcon + 1) / 2;
    // Draw the icon
    dc.DrawIcon(x, y, m_hIcon);
  } else {
    CDialogEx::OnPaint();
  }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CImageResizeDlg::OnQueryDragIcon() {
  return static_cast<HCURSOR>(m_hIcon);
}


void CImageResizeDlg::OnBnClickedButtonOpen() {
  // Open image
  CString FilePathName;
  CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框

  if (dlg.DoModal() == IDOK) {
    FilePathName = dlg.GetPathName();
    GetDlgItem(IMAGE_FILENAME)->SetWindowText(FilePathName);
    CT2CA pszConvertedAnsiString(FilePathName);
    cv::Mat img = cv::imread(std::string(pszConvertedAnsiString),
                             CV_LOAD_IMAGE_UNCHANGED);

    if (!img.empty()) {
      CString int_to_str;
      int_to_str.Format(L"%d", img.rows);
      GetDlgItem(IDC_SOURCE_SIZE_W_L)->SetWindowText(int_to_str);
      GetDlgItem(IDC_TARGET_SIZE_W_L)->SetWindowText(int_to_str);
      int_to_str.Format(L"%d", img.cols);
      GetDlgItem(IDC_SOURCE_SIZE_H_L)->SetWindowText(int_to_str);
      GetDlgItem(IDC_TARGET_SIZE_H_L)->SetWindowText(int_to_str);
      //  cv::namedWindow("Preview",
      //                  CV_WINDOW_AUTOSIZE); //create a window with the name "Preview"
      //  cv::imshow("Preview",
      //             img); //display the image which is stored in the 'img' in the "Preview" window
      //  cv::waitKey(0); //wait infinite time for a keypress
      //  cv::destroyWindow("Preview"); //destroy the window with the name, "Preview"
    }
  }
}

void CImageResizeDlg::OnEnKillfocusTargetSizeWL() {
  CButton* button = (CButton*)GetDlgItem(IDC_TARGET_SIZE_KEEP_ASPECT);

  if (button->GetCheck() == BST_CHECKED) {
    CString string_value;
    GetDlgItem(IDC_SOURCE_SIZE_W_L)->GetWindowText(string_value);
    int src_width = _wtoi(string_value);
    GetDlgItem(IDC_SOURCE_SIZE_H_L)->GetWindowText(string_value);
    int src_height = _wtoi(string_value);
    GetDlgItem(IDC_TARGET_SIZE_W_L)->GetWindowText(string_value);
    int dst_width = _wtoi(string_value);
    int dst_height = (int)round((double)src_height / (double)src_width *
                                (double)dst_width);
    string_value.Format(L"%d", dst_height);
    GetDlgItem(IDC_TARGET_SIZE_H_L)->SetWindowText(string_value);
  }
}


void CImageResizeDlg::OnEnKillfocusTargetSizeHL() {
  CButton* button = (CButton*)GetDlgItem(IDC_TARGET_SIZE_KEEP_ASPECT);

  if (button->GetCheck() == BST_CHECKED) {
    CString string_value;
    GetDlgItem(IDC_SOURCE_SIZE_W_L)->GetWindowText(string_value);
    int src_width = _wtoi(string_value);
    GetDlgItem(IDC_SOURCE_SIZE_H_L)->GetWindowText(string_value);
    int src_height = _wtoi(string_value);
    GetDlgItem(IDC_TARGET_SIZE_H_L)->GetWindowText(string_value);
    int dst_height = _wtoi(string_value);
    int dst_width = (int)round((double)src_width / (double)src_height *
                               (double)dst_height);
    string_value.Format(L"%d", dst_width);
    GetDlgItem(IDC_TARGET_SIZE_W_L)->SetWindowText(string_value);
  }
}
