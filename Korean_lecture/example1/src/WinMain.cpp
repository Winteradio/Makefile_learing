#include "WinMain.h"

#define MAX_LOADSTRING 100

// 전역 변수
HINSTANCE hInst;                        // 현재 인스턴스
const auto szTitle = "Example";          // 제목 표시줄 텍스트
const auto szWindowClass = "Example_Class";    // 기본 창 클래스 이름

HWND g_hWnd;

LPDIRECT3D9 g_pD3D = nullptr;
LPDIRECT3DDEVICE9 g_pd3dDevice = nullptr;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다.
ATOM MyRegisterClass( HINSTANCE );
BOOL InitInstance( HINSTANCE, int );
HRESULT InitD3D( HWND );

//
// 함수 : WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//
// 용도 : Window Main 함수
//
int CALLBACK WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
)
{
  MyRegisterClass(hInstance);

  // 어플리케이션 초기화를 수행
  if (!InitInstance(hInstance, nCmdShow))
  {
    return FALSE;
  }

  // TODO : 여기에 코드를 입력
  InitD3D( g_hWnd );

  // 기본 메세지 루프
  MSG msg;
  while (true)
  {
    if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)
      {
        break;
      }

      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }

  }

  return (int) msg.wParam;
}

//
// 함수 : WndProc(HWND, UINT, WPARAM, LPARAM)
//
// 용도 : 주 창의 메세지를 처리
//
// WM_COMMAND     - 애플리케이션 메뉴를 처리
// WM_PAINT     - 주 창을 그림
// WM_DESTORY     - 종료 메세지를 게시하고 반환
LRESULT CALLBACK WndProc(
  HWND hWnd,
  UINT message,
  WPARAM wParam,
  LPARAM lParam
)
{
  switch( message )
  {
  case WM_CLOSE :
    PostQuitMessage( 69 );
    break;

  case WM_KEYDOWN :
    if( wParam == 'F')
    {
      SetWindowText( hWnd, "Recent");
    }
    break;

  case WM_KEYUP :
    if( wParam == 'F')
    {
      SetWindowText( hWnd, "UPUPUP");
    }
    break;

  case WM_CHAR : // text input에 대한 메세지만을 준다.
    {
      static std::string title;
      title.push_back( (char)wParam );
      SetWindowText( hWnd, title.c_str() );
    }
    break;

  case WM_LBUTTONDOWN :
    {
      POINTS pt = MAKEPOINTS( lParam );
      std::ostringstream oss;
      oss << "(" << pt.x << "," << pt.y << ")";
      SetWindowText( hWnd, oss.str().c_str() );
    }
    break;
  }
  return DefWindowProc( hWnd, message, wParam, lParam );
}

//
// 함수 : MyRegisterClass(HINSTANCE)
//
// 용도 : 창 클래스를 등록
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);

  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = nullptr;
  wcex.hCursor = nullptr;
  wcex.hbrBackground = nullptr;
  wcex.lpszMenuName = nullptr;
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = nullptr;

  return RegisterClassEx( &wcex );
}

//
// 함수 : InitInstance(HINSTANCE, int)
//
// 용도 : 인스턴스 핸들을 저장하고 주 창을 만듦
//
// 주석 : 이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고 주 프로그램 창을 만든 다음 표시
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장

  HWND hWnd;
  g_hWnd = hWnd = CreateWindow(
    szWindowClass,
    szTitle,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT,
    0,
    CW_USEDEFAULT,
    0,
    nullptr,
    nullptr,
    hInstance,
    nullptr);

  if (!hWnd)
  {
    return FALSE;
  }

  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);

  return TRUE;
}

//
// 함수 : InitD3D(HWND)
//
// 용도 : Direct3D & Direct3D Device 생성
//
HRESULT InitD3D( HWND hWnd )
{
  if ( NULL == (g_pD3D = Direct3DCreate9( D3D_SDK_VERSION )) )
  {
    return E_FAIL;
  }

  D3DPRESENT_PARAMETERS d3dpp;
  ZeroMemory( &d3dpp, sizeof( D3DPRESENT_PARAMETERS ));
  d3dpp.Windowed = TRUE;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

  if ( FAILED( g_pD3D->CreateDevice(
    D3DADAPTER_DEFAULT,
    D3DDEVTYPE_HAL,
    hWnd,
    D3DCREATE_SOFTWARE_VERTEXPROCESSING,
    &d3dpp,
    &g_pd3dDevice)))
  {
    return E_FAIL;
  }

  return S_OK;
}

