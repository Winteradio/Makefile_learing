#include <Windows.h>
#include <iostream>
#include <sstream>

LRESULT CALLBACK WndProc(
  HWND hWnd,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam
)
{
  switch( msg )
  {
  case WM_CLOSE:
    PostQuitMessage( 69 );
    break;
  case WM_KEYDOWN:
    if( wParam == 'F')
    {
      SetWindowText( hWnd, "Recent");
    }
    break;
  case WM_KEYUP:
    if( wParam == 'F')
    {
      SetWindowText( hWnd, "UPUPUP");
    }
    break;
  case WM_CHAR: // text input에 대한 메세지만을 준다.
  {
    static std::string title;
    title.push_back( (char)wParam );
    SetWindowText( hWnd, title.c_str() );
  }
    break;
  case WM_LBUTTONDOWN:
    {
      POINTS pt = MAKEPOINTS( lParam );
      /*
      WM_R or LBUTTON Message위 경우에는
      lParam가 2차원상의 윈도우에서의 마우스의 위치정보를 지니고 있다.
      */
      std::ostringstream oss;
      oss << "(" << pt.x << "," << pt.y << ")";
      /*
      istringstream : string을 입력받아 다른 형식으로 바꿔주는 기능을 한다.
      ostringstream : string을 조립하거나, 특정 수치를 문자열로 변환하기 위해 사용
      stringstream : 가지고 있는 string에서 공백과 \n을 제외한 문자열을 차례대로 빼내는 역할을 수행한다
      str() : string으로 형변환
      c_str() : string을 C style로 변경 >> const char*을 리턴
      */
      SetWindowText( hWnd, oss.str().c_str() );
    }
  }
  return DefWindowProc( hWnd, msg, wParam, lParam );
  // DefWindowProc에서 나머지 메세지들을 처리한다.
}

int CALLBACK WinMain(
  HINSTANCE hInstance,
  HINSTANCE hPrevInstance,
  LPSTR lpCmdLine,
  int nCmdShow
)
{
  const auto pClassName = "Example";
  // register window class
  WNDCLASSEX wc = {0};
  wc.cbSize = sizeof( wc );
  wc.style = CS_OWNDC;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = nullptr;
  wc.hCursor = nullptr;
  wc.hbrBackground = nullptr;
  wc.lpszMenuName = nullptr;
  wc.lpszClassName = pClassName;
  wc.hIconSm = nullptr;
  RegisterClassEx( &wc );

  // create window instance
  HWND hWnd = CreateWindowEx(
    0,
    pClassName,
    "Example",
    WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
    200,200,
    640,480,
    nullptr,
    nullptr,
    hInstance,
    nullptr
  );

  // show window
  ShowWindow( hWnd, SW_SHOW);

  // message pump
  MSG msg;
  BOOL gResult;

  while( (gResult = GetMessage( &msg, nullptr, 0, 0 )) > 0 ){
    TranslateMessage( &msg );
    DispatchMessage( &msg );
  }

  if ( gResult == -1)
  {
    return -1;
  }
  else
  {
    return msg.wParam;
  }
}
