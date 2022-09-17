#include <Windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(
  HWND hWnd,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam
)
{
  // 간단한 message Map을 만들어서 어떤 키들이 눌러지는지에 대한
  // LOG 파일을 만들어보자
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
  // DefWindowProc로 설정할 시
  // DefWindowProc에서 메세지 전부 처리하기에
  // WndProc를 호출하지 않는다
  // 메세지 처리가 필요할 시,
  // WndProc를 사용하자
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
