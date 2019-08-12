
// MFCApplication2Dlg.h: 헤더 파일
//

#pragma once


// CMFCApplication2Dlg 대화 상자
class CMFCApplication2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CImage m_image, m_commit_image;
	BITMAP m_bmp_info;
	unsigned char * mp_image_pattern, *mp_commit_pattern;
public:
	afx_msg void OnBnClickedGrayBtn();
	afx_msg void OnBnClickedFilter1Btn2();
	afx_msg void OnBnClickedFilter2Btn3();
	afx_msg void OnBnClickedFilter3Btn4();
	afx_msg void OnBnClickedRestoreBtn();
	afx_msg void OnBnClickedCommitBtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBlureBtn();
};
