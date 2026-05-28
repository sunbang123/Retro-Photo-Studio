
// RetroPhotoStudioDlg.h: 헤더 파일
//
#pragma once
#include <atlimage.h>


// CRetroPhotoStudioDlg 대화 상자
class CRetroPhotoStudioDlg : public CDialogEx
{
// 생성입니다.
public:
	CRetroPhotoStudioDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CImage m_image; // 이미지 객체를 멤버 변수로 선언

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RETROPHOTOSTUDIO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	template <typename FilterFunc>
	afx_msg void ProcessPixels(FilterFunc filter);
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnGray();
	afx_msg void OnBnClickedBtnSepia();
};

template <typename FilterFunc>
void CRetroPhotoStudioDlg::ProcessPixels(FilterFunc filter)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 1. 이미지가 로드되어 있는지 확인
	if (m_image.IsNull())
	{
		AfxMessageBox(_T("먼저 이미지를 열어주세요."));
		return;
	}

	// 2. 이미지의 정보 가져오기
	int width, height, pitch, bpp;
	ExtractImageInfo(m_image, width, height, pitch, bpp);

	// 3. 픽셀 데이터의 시작 주소 가져오기
	byte* pBits = (byte*)m_image.GetBits();

	// 24비트(RGB) 또는 32비트(RGBA) 이미지인지 확인
	if (bpp != 24 && bpp != 32)
	{
		AfxMessageBox(_T("지원되지 않는 이미지 형식입니다. 24비트 또는 32비트 이미지를 사용해주세요."));
		return;
	}

	int bytesPerPixel = bpp / 8; // 픽셀당 바이트 수 (3 또는 4)


	// 4. 픽셀 데이터를 순회하면서 그레이스케일로 변환
	for (int y = 0; y < height; ++y)
	{

		// Y축의 각 줄(Row)의 시작 포인터 계산(Pitch 사용 필수)
		byte* pRow = pBits + (y * pitch);

		for (int x = 0; x < width; ++x)
		{
			// 현재 픽셀의 포인터 위치 계산
			byte* pPixel = pRow + (x * bytesPerPixel);

			// Windows 메모리 상에서는 RGB가 아니라 BGR 순서로 저장되어있음
			byte B = pPixel[0];
			byte G = pPixel[1];
			byte R = pPixel[2];

			// 필터 타입에 따라 다른 효과 적용
			filter(pPixel, R, G, B);
		}

		// 5. 화면갱신
		// OnPaint() 함수에서 이미지가 그려질 때, m_image.Draw()가 호출되므로
		// Invalidate()를 호출하여 대화 상자를 다시 그리도록 요청합니다.
		Invalidate();
	}
}