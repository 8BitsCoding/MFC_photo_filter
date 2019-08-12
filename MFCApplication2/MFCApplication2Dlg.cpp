
// MFCApplication2Dlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2Dlg 대화 상자



CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_GRAY_BTN, &CMFCApplication2Dlg::OnBnClickedGrayBtn)
	ON_BN_CLICKED(IDC_FILTER1_BTN2, &CMFCApplication2Dlg::OnBnClickedFilter1Btn2)
	ON_BN_CLICKED(IDC_FILTER2_BTN3, &CMFCApplication2Dlg::OnBnClickedFilter2Btn3)
	ON_BN_CLICKED(IDC_FILTER3_BTN4, &CMFCApplication2Dlg::OnBnClickedFilter3Btn4)
	ON_BN_CLICKED(IDC_RESTORE_BTN, &CMFCApplication2Dlg::OnBnClickedRestoreBtn)
	ON_BN_CLICKED(IDC_COMMIT_BTN, &CMFCApplication2Dlg::OnBnClickedCommitBtn)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BLURE_BTN, &CMFCApplication2Dlg::OnBnClickedBlureBtn)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 메시지 처리기

BOOL CMFCApplication2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_image.Load(L"me.JPG");
	GetObject((HBITMAP)m_image, sizeof(BITMAP), &m_bmp_info);
	mp_image_pattern = (unsigned char *)m_image.GetBits();
	mp_image_pattern += m_bmp_info.bmWidthBytes - 1;

	m_commit_image.Create(m_bmp_info.bmWidth, m_bmp_info.bmHeight, 24);
	mp_commit_pattern = (unsigned char *)m_commit_image.GetBits();
	mp_commit_pattern += m_bmp_info.bmWidthBytes - 1;

	int image_size = m_bmp_info.bmWidth * m_bmp_info.bmHeight * 3;
	memcpy(mp_commit_pattern - image_size + 3, mp_image_pattern - image_size + 3, image_size );

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication2Dlg::OnPaint()
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	if (IsIconic())
	{
		

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		dc.SetStretchBltMode(COLORONCOLOR);		// 그림의 사이즈를 줄일 경우 색 깨짐 방지
		m_image.Draw(dc, 0, 0, m_bmp_info.bmWidth/*/4*/,m_bmp_info.bmHeight/*/4*/);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication2Dlg::OnBnClickedGrayBtn()
{
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	unsigned char * p = mp_image_pattern;
	int temp;
	for (int i = 0; i < dot_count; i++) {
		/*
		*p-- = 0;		// Red
		*p-- = 0;		// Green
		p--;			// Blue 그대로
		*/
		temp = (*p + *(p - 1) + *(p - 2))/3;
		*p-- = temp;
		*p-- = temp;
		*p-- = temp;
	}

	Invalidate(FALSE);
}

_inline void IncFixColor(unsigned char * ap_color, int a_value)
{
	int temp = *ap_color + a_value;
	if (temp > 255) *ap_color = 255;
	else *ap_color = temp;
}

void CMFCApplication2Dlg::OnBnClickedFilter1Btn2()
{
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	unsigned char * p = mp_image_pattern;
	for (int i = 0; i < dot_count; i++) {
		IncFixColor(p--, 30);
		IncFixColor(p--, 30);
		IncFixColor(p--, 30);
	}

	Invalidate(FALSE);
}

_inline void IncFix2Color(unsigned char * ap_color, float a_rate)
{
	int index;
	if (*ap_color > *(ap_color - 1)) {
		if (*ap_color > *(ap_color - 2))	index = 0;	// R
		else index = 2;		// B
	}
	else {
		if (*(ap_color - 1) > *(ap_color - 2))	index = 1;	// G
		else index = 2;	// B
	}
	if (*(ap_color - index) * a_rate > 255) {	// 가장 큰 색상 * 비율
		a_rate = 255.0f / *(ap_color - index);
	}
	*ap_color-- = (int)(*ap_color * a_rate);
	*ap_color-- = (int)(*ap_color * a_rate);
	*ap_color-- = (int)(*ap_color * a_rate);
}

void CMFCApplication2Dlg::OnBnClickedFilter2Btn3()
{
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight;
	unsigned char * p = mp_image_pattern;
	for (int i = 0; i < dot_count; i++) {
		IncFix2Color(p, 1.2f);		// 20% 정도 밝게 해달라
		p -= 3;
	}

	Invalidate(FALSE);
}


void CMFCApplication2Dlg::OnBnClickedFilter3Btn4()
{
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight, temp;
	unsigned char * p = mp_image_pattern;
	for (int i = 0; i < dot_count; i++) {
		temp = (*p + *(p - 1) + *(p - 2));
		IncFix2Color(p, 1.0f + ((768 - temp)*2)/6000);
		p -= 3;
	}

	Invalidate(FALSE);
}


void CMFCApplication2Dlg::OnBnClickedRestoreBtn()
{
	int image_size = m_bmp_info.bmWidth * m_bmp_info.bmHeight * 3;
	memcpy(mp_image_pattern - image_size + 3,  mp_commit_pattern - image_size + 3, image_size);

	Invalidate(FALSE);
}


void CMFCApplication2Dlg::OnBnClickedCommitBtn()
{
	int image_size = m_bmp_info.bmWidth * m_bmp_info.bmHeight * 3;
	memcpy(mp_commit_pattern - image_size + 3,  mp_image_pattern - image_size + 3, image_size);

	Invalidate(FALSE);
}


void CMFCApplication2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (point.x < 50) {
		point.x = 50;
	}
	else if (point.x + 50 >= m_bmp_info.bmWidth/*/4*/) {
		point.x = m_bmp_info.bmWidth /*/4*/ - 51;
	}

	if (point.y < 50) {
		point.y = 50;
	}
	else if (point.y + 50 >= m_bmp_info.bmHeight/*/4*/) {
		point.y = m_bmp_info.bmHeight /*/4*/ - 51;
	}

	int pos = -(point.y /*/4*/)*m_bmp_info.bmWidth * 3 - (m_bmp_info.bmWidth - (point.x/*/4*/)) * 3;
	unsigned char * p = mp_image_pattern + pos;	// 원의 중심점
	unsigned char * p_commit = mp_commit_pattern + pos;

	if(*p == *p_commit)		IncFix2Color(p, 1.2f);

	double radian,x ,y;
	for (int degree = 0; degree < 360; degree++) {
		radian = degree * 3.141592 / 180.0;
		x = sin(radian);
		y = cos(radian);
		for (int radius = 1; radius < 50; radius++) {
			int pos = -(point.y /*/4*/-(int)(y*radius))*m_bmp_info.bmWidth * 3 - 
				(m_bmp_info.bmWidth - (point.x/*/4*/)-(int)(x*radius)) * 3;
			p = mp_image_pattern + pos;
			p_commit = mp_commit_pattern + pos;
			if (*p == *p_commit) IncFix2Color(p, 1.2f);
		}
	}

	Invalidate(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication2Dlg::OnBnClickedBlureBtn()
{
	int dot_count = m_bmp_info.bmWidth * m_bmp_info.bmHeight, temp;
	unsigned char *p, *p_temp;
	unsigned int avr_r, avr_g, avr_b;

	for (int y = 1; y < m_bmp_info.bmHeight - 2; y++) {
		p = mp_image_pattern - y * m_bmp_info.bmWidth * 3;
		for (int x = 1; x < m_bmp_info.bmWidth - 2; x++) {
			p_temp = p + m_bmp_info.bmWidth * 3 + 3;
			avr_r = *p_temp + *(p_temp - 3) + *(p_temp-6);
			avr_g = *(p_temp-1) + *(p_temp - 4) + *(p_temp - 7);
			avr_b = *(p_temp-2) + *(p_temp - 5) + *(p_temp - 8);

			p_temp = p + 3;
			avr_r += *p_temp + *(p_temp - 3) + *(p_temp - 6);
			avr_g += *(p_temp - 1) + *(p_temp - 4) + *(p_temp - 7);
			avr_b += *(p_temp - 2) + *(p_temp - 5) + *(p_temp - 8);

			p_temp = p - m_bmp_info.bmWidth * 3 + 3;
			avr_r += *p_temp + *(p_temp - 3) + *(p_temp - 6);
			avr_g += *(p_temp - 1) + *(p_temp - 4) + *(p_temp - 7);
			avr_b += *(p_temp - 2) + *(p_temp - 5) + *(p_temp - 8);

			*p = avr_r / 9;
			*(p - 1) = avr_g / 9;
			*(p - 2) = avr_b / 9;

			p -= 3;
		}
	}

	Invalidate(FALSE);
}
