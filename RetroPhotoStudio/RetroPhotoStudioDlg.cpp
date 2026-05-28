
// RetroPhotoStudioDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "RetroPhotoStudio.h"
#include "RetroPhotoStudioDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRetroPhotoStudioDlg 대화 상자



CRetroPhotoStudioDlg::CRetroPhotoStudioDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RETROPHOTOSTUDIO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRetroPhotoStudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRetroPhotoStudioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CRetroPhotoStudioDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_GRAY, &CRetroPhotoStudioDlg::OnBnClickedBtnGray)
	ON_BN_CLICKED(IDC_BTN_SEPIA, &CRetroPhotoStudioDlg::OnBnClickedBtnSepia)
END_MESSAGE_MAP()


// CRetroPhotoStudioDlg 메시지 처리기

BOOL CRetroPhotoStudioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CRetroPhotoStudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CRetroPhotoStudioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

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
		//CDialogEx::OnPaint();

		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

		// 이미지가 로드되어 있는지 확인
		if (!m_image.IsNull())
		{
			// 2. Picture Control의 '모니터 화면 전체 기준' 실제 좌표를 가져옵니다.
			CRect rect;
			GetDlgItem(IDC_PIC_VIEWER)->GetWindowRect(&rect);

			// 3. 그 좌표를 '현재 다이얼로그 창 기준' 좌표로 변환합니다. (가장 중요한 핵심!)
			ScreenToClient(&rect);

			// 4. 화질 보정 후, 다이얼로그의 해당 위치에 정확히 그림을 그립니다.
			SetStretchBltMode(dc.m_hDC, HALFTONE);
			m_image.Draw(dc.m_hDC, rect);
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CRetroPhotoStudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRetroPhotoStudioDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 1. 파일 탐색기 창 띄우기 (jpg, bmp, png 파일만 보이게 필터링)
	CFileDialog dlg(TRUE, _T("*.jpg;*.bmp;*.png"), NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,\
		_T("Image Files (*.jpg;*.bmp;*.png)|*.jpg;*.bmp;*.png||"), NULL);

	// 사용자가 열기	버튼을 클릭하면
	if (dlg.DoModal() == IDOK)
	{
		// 2. 기존의 메모리 비우기
		if(!m_image.IsNull())
		{
			m_image.Destroy();
		}

		// 3. 선택한 파일 경로 가져오기
		CString filePath = dlg.GetPathName();
		// 4. CImage 객체에 이미지 로드하기
		HRESULT hr = m_image.Load(filePath);

		if (FAILED(hr))
		{
			AfxMessageBox(_T("이미지를 로드하는 데 실패했습니다."));
			return;
		}
		// 5. 이미지가 성공적으로 로드되었음을 사용자에게 알리기
		AfxMessageBox(_T("이미지가 성공적으로 로드되었습니다."));

		Invalidate(); // 이미지가 로드된 후 대화 상자를 다시 그리도록 요청
	}

}

void ExtractImageInfo(CImage& image, int& width, int& height, int& pitch, int& bpp)
{
	width = image.GetWidth();
	height = image.GetHeight();
	pitch = image.GetPitch(); // 한 줄의 바이트 수
	bpp = image.GetBPP(); // 픽셀당 비트 수 Bits Per Pixel (예: 24, 32)
}

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

void CRetroPhotoStudioDlg::OnBnClickedBtnGray()
{
	ProcessPixels([](byte* pPixel, byte R, byte G, byte B) {
		// 그레이스케일 변환 공식: Gray = 0.299 * R + 0.587 * G + 0.114 * B
		byte gray = static_cast<byte>(0.299 * R + 0.587 * G + 0.114 * B);
		pPixel[0] = gray; // B
		pPixel[1] = gray; // G
		pPixel[2] = gray; // R		
	});
}

void CRetroPhotoStudioDlg::OnBnClickedBtnSepia()
{
	// 람다식을 이용해 세피아 공식만 템플릿 함수로 전달
	ProcessPixels([](byte* pPixel, byte R, byte G, byte B) {
		int tr = (int)(0.393 * R + 0.769 * G + 0.189 * B);
		int tg = (int)(0.349 * R + 0.686 * G + 0.168 * B);
		int tb = (int)(0.272 * R + 0.534 * G + 0.131 * B);

		// 지역 변수 R,G,B가 아니라, 실제 이미지 메모리(pPixel)에 덮어쓰기!
		pPixel[2] = (tr > 255) ? 255 : (byte)tr; // R
		pPixel[1] = (tg > 255) ? 255 : (byte)tg; // G
		pPixel[0] = (tb > 255) ? 255 : (byte)tb; // B
	});
}
