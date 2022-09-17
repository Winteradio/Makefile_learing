#include <Windows.h>
#include <iostream>

LRESULT CALLBACK WndProc(
  HWND hWnd,
  UINT msg,
  WPARAM wParam,
  LPARAM lParam
)
{
  std::cout << msg << std::endl;
  switch( msg )
  {
    case WM_CLOSE:
      std::cout << "Done..." << std::endl;
      PostQuitMessage( 69 );
      /*
      VOID PostQuitMessage(int nExitCode);

      nExitCode
        종료코드
        이 값은 WM_QUIT의 wParam으로 전달되며 잘 사용되지 않으므로 보통0으로 전달한다.
        이 값은 메세지 루프 종료후에 다시 WinMain의 리턴값으로 재사용되며 결국 프로세스의 종료 코드가 되는데,
        프로세스의 종료코드도 사용되는 경우가 드물다.

      스레드 메세지 큐에 WM_QUIT 메세지를 붙이고 즉시 리턴한다.
      WM_QUIT 메세지를 큐에 붙임으로써 시스템에게 이 스레드가 종료될 것이라는 것을 미리 알려준다.
      메세지 루프는 보통 WM_QUIT 메세지를 받으면 종료되도록 되어 있으므로 이 함수를 호출하면 메세지 루프가 종료된다.
      특히 이 함수를 호출하는 스레드가 주 스레드일 경우는 주 스레드의 메세지 루프가 종료됨으로써 프로세스가 종료된다.

      단, 이 함수는 메세지를 큐에 붙인 후 즉시 리턴하므로 호출 즉시 프로세스가 종료되는 것은 아니다.
      즉 PostQuitMessage 호출 후 다른 처리르 계속할 수 있으며 이미 메세지 큐에 들어와 있는 모든 메세지가 처리된 후에
      WM_QUIT 메세지가 읽혀져야 종료된다.
      반면 ExitProcess 함수는 즉시 프로세스를 종료하기 때문에 이 함수 아래에 작성된 코드는 실행되지 않는다.

      통상 이 함수는 메인 윈도우의 WM_DESTORY 메세지 처리 코드에 작성되어 메인 윈도우가 파괴되면 응용 프로그램을 종룧나느 역할을 한다.
      차일드 윈도우가 WM_DESTORY에서 이 메세지를 호출해서는 안된다.
      그래서 DefWindowProc은 WM_DESTORY 메세지를 디폴트 처리할 때 PostQuitMessage를 호출하지 않도록 되어있다.
      */
      break;
  }
  return DefWindowProc( hWnd, msg, wParam, lParam);
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
  wc.lpfnWndProc = DefWindowProc;
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
  /*
  typedef struct tagMSG
  {
    HWND hwnd; // 메세지를 받을 윈도우 핸들
    UINT message; // 어떤 종류의 메세지인가를 나타낸다.
    WPARAM wParam; // 전달된 메세지에 대한 부가적인 정보
    LPARAM lParam; // 전달된 메세지에 대한 부가적인 정보
    DWORD time; // 메세지가 발생한 시간
    POINT pt; // 메세지가 발생했을 때의 마우스 위치
  }MSG;

  매크로 WM_
  WM_QUIT : 프로그램을 끝낼 때 발생하는 메세지
  WM_LBUTTIONDOWN : 마우스의 좌측 버튼을 누를 경우 발생
  WM_CHAR : 키보드로부터 문자가 입력될 때 발생
  WM_PATIN : 화면을 다시 그려야할 필요가 있을 때 발생
  WM_DESTORY : 윈도우가 메모리에서 파괴될 때 발생
  WM_CREATE : 윈도우가 처음 만들어 질 떄 발생
  */
  BOOL gResult;
  while( (gResult = GetMessage( &msg, nullptr, 0, 0 )) > 0 ){
    /*
      GetMessage
      1. LPMSG : MSG 포인터
      2. hWnd : 메세지를 받을 윈도우이며 이 윈도우로 보내지는 메세지를 조사한다.
                이 인수가 NULL이면 이 함수를 호출한 스레드로 전달된 모든 메세지를 조사한다.
      3. wMsgFilterMin : 조사할 메세지의 최소값
      4. wMsgFilterMax : 조사할 메세지의 최대값
        이 두 인수를 사용하면 일정한 범위에 속한 메세지만 조사할 수 있는데
        이를 메세지 필터링이라고 한다.
        예를 들어 키보드 관련 메세지만 조사하고 싶으면
        WM_KEYFIRST, WM_KEYLAST로 범위를 지정할 수 있다.
        두 인수가 모두 0이면 메세지 필터링을 하지 않으며 모든 메세지를 조사한다.

      조사한 메세지가 WM_QUIT 메세지이면 FALSE를 리턴하며 그 외의 메세지이면 TRUE를 리턴한다.
      이 리턴값은 메세지 루프를 탈출하기 위한 용도로 사용되는데
      WM_QUIT 메세지가 전달되었으면 메세지 루프가 종료된다.
      에러 발생시 -1이 리턴된다.

      호출한 스레드에서 메세지를 꺼내 첫번째 인수로 전달된 lpMsg 구조체에 채워준다.
      특정 윈도우(그 child 포함된다)로 보내지는 메세지나 PostThreadMessage 함수에 의해 스레드로 보내진 메세지를 조사할 수 있으며
      특정한 범위에 있는 메시지만 조사할 수 있다.
      이 함수는 다른 스레드나 다른 프로세스의 메세지는 조사하지 못하며 오직 호출 스레드의 메세지만 조사할 수 있다.

      전체 루프는 while문으로 싸여져 있어 GetMessage가 WM_QUIT를 조사할 때까지 반복된다.
      GetMessage는 이 스레드에 속한 모든 윈도우에 대한 모든 메세지를 조사하여 Message 구조체에 채워준다.
      이 메세지는 DispatchMessage 함수에 의해 해당 윈도우의 윈도우 프로시저로 보내진다.

      GetMessage 함수는 스레드 메세지 큐에서 메시지를 읽은 후 이 메세지를 큐에서 제거한다.
      단 예외적으로 WM_PAINT 메세지는 이 메세지가 처리된 후에 메시지 큐에서 제거된다.

      GetMessage 함수는 메세지 큐에 대기중인 메세지가 없을 경우 메세지가 전달될 때까지 무한히 대기한다.
    */
    TranslateMessage( &msg );
    /*
    BOOL TranslateMessage( CONST MSG *lpMsg);
    키보드 입력 메세지를 가공하여 프로그램에서 쉽게 쓸 수 있도록 해준다.
    윈도우즈는 키보드의 어떤 키가 눌러졌다거나 떨어져씅ㄹ 때 키보드 메세지를 발생시키는데
    이 함수는 키보드의 눌림(WM_KEYDOWN)과 떨어짐(WM_KEYUP)이 연속적으로 발생할 때 문자가 입력되었다는 메세지(WM_CHAR)를 만드는 역할을 한다.
    예를 들어 A키를 누른 후 다시 A키를 떼면 A문자가 입력되었다는 메세지를 만들어낸다.
    */
    DispatchMessage( &msg );
    /*
    LONG DispatchMessage( CONST MSG *lpMsg);
    시스템 메세지 큐에서 꺼낸 메세지를 프로그램의 메세지 처리 함수(WndProc)로 전달한다.
    이 함수에 의해 메세지가 프로그램으로 전달되며 프로그램에서는 전달된 메세지를 점검하여 다음 동작을 결정하게 된다.

    메세지 루프에서 하는 일은 메세지를 꺼내고, 필요한 경우 약간 형태를 바꾼 후 응용 프로그램으로 전달하는 것 뿐이다.
    이 과정은 WM_QUIT 메세지가 전달될 떄까지, 즉 프로그램이 종료될 때까지 반복된다.
    결국 메세지 루프가 하는 일이란 메세지 큐에서 메세지를 꺼내 메세지 처리함수로 보내주는 것 뿐이다.

    실제 메세지 처리는 별도의 메세지 처리 함수(WndProc)에서 수행한다. 메세지는 시스템의 변화에 대한 정보이며 MSG라는 구조체에 보관된다.
    */
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

/*
## 공통점
  두 함수는 모두 메세지 큐로부터 메세지를 가져온다.
  두 함수는 동일한 매개변수 4개를 가진다.
  그중에 첫번째 인자로 MSG 구조체를 받는다.
  메세지 큐로부터 얻은 메세지 값을 MSG 구조체에 저장한다.

## Getmessage
  GetMessage()는 메세지 큐에 메세지가 존재한다면 가져와서 MSG 구조체에 그 값을 저장하고 TRUE를 반환한다.
  그런데 만약 읽은 메세지가 WM_QUIT이면 FALSE를 리턴한다.
  WM_QUIT은 메세지 루프를 종료하기 위한 조건으로 사용된다.
  만약 메세지 큐에 메세지가 존재하지 않으면 메세지가 생성될 때까지 무한정 기다린다.
  이는 scanf 또는 cin과 같은 함수 사용 시 사용자가 입력할 때까지 무한정 기다리는 것과 같다.
  때문에 이러한 상황을 생각하여 사용하기 적절한 상황인지 생각해야 한다.

  이러한 메세지들을 가져오면 TranslateMessage()라는 함수를 통해 번역을 하고,
  DispatchMessage()라는 함수를 통해 메세지 처리 함수(WndProc)으로 전달한다.
  WndProc이 최종적으로 해당 메세지를 처리한다. 윈도우의 모든 메세지는 이처럼 3개의 함수를 거친다.

## PeekMessage
  PeekMessage()는 메세지 큐에 메세지가 존재한다면 가져와서 MSG 구조체에 그 값을 저장하고 0이 아닌 값을 반환한다.
  해당 함수는 메세지 큐가 비어있을 때 GetMessage()처럼 무한정 기다리지 않고 바로 0을 리턴한다.
  때문에 PeekMessage() 함수는 무한 대기에 빠지지 않고,
  메세지 큐가 비었다면 다음과 같이 다른 작업을 해줄 수 있다.
  해당 함수도 메세지를 읽어오면 GetMessage와 동일한 메세지가 번역되어 메세지 처리 함수로 보내진다.


*/
