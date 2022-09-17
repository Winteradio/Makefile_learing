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
      std::ostringstream oss;
      oss << "(" << pt.x << "," << pt.y << ")";
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
    printf("HEllo\n");
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