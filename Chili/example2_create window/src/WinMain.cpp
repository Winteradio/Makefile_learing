#include <Windows.h>

// WinMain : 윈도우즈 프로그램으 시작점으로 main에 해당
int CALLBACK WinMain(
  HINSTANCE hInstance,
  // 프로그램의 인스턴스 핸들
  HINSTANCE hPrevInstance,
  // 바로 앞에 실행된 현재 프로그램의 인스턴트 핸들
  // 없을 경우 NULL이 되며, Win32에서는 항상 NULL 값을 가짐
  // 현재는 사용이 안되지만, 16비트와의 호환성을 위해 존재
  LPSTR lpCmdLine,
  // 명령행으로 입력된 프로그램 인수
  // 도스의 argv 인수에 해당하며 보통 실행 직후에 파일 경로를 전달
  int nCmdShow
  // 프로그램이 실행될 형태
  // 최소화, 보통, 최대화 등을 전달
)
{
  const auto pClassName = "Example";
  // register window class
  WNDCLASSEX wc = {0};
  // WNDCLASSEX wc; 로도 생성 가능
  // WNDCLASSEX wc = {0}; : 초기화
  wc.cbSize = sizeof( wc );
  // 윈도우 클래스 구조체의 크기를 저장
  wc.style = CS_OWNDC;
  // 윈도우 클래스의 스타일을 지정
  /*
    1. CS_VREDRAW : 윈도우 창의 세로크기 변경시 윈도우를 다시 그림
    2. CS_HREDRAW : 윈도우 창의 가로크기 변경시 윈도우를 다시 그림
    3. CS_DBLCLKS : 마우스 더블클릭 버튼 활성화
    4. CS_OWNDC : 윈도우가 하나의 DC를 독점적으로 사용
    5. CS_CLASSDC : DC를 공유
    6. CS_PARENTDC : 자식윈도우가 부모윈도우의 DC를 사용
    7. CS_NOCLOSE : 닫기 메세지 전달불가
    8. CS_SAVEBITS : 화면영역을 비트맵으로 저장
  */
  wc.lpfnWndProc = DefWindowProc;
  // 윈도우 프로시저의 함수명을 지정
  // DefWindowProc : WndProc에서 처리하지 않은 나머지 메세지에 관한 처리를 해준다.
  // 예를 들어 시스템 메뉴를 더블클릭하면 프로그램이 종료되는데 이런 처리는 별도로 해주지 안항도 DefWindowProc 함수에서 해준다
  wc.cbClsExtra = 0;
  // 윈도우의 여분 메모리량
  wc.cbWndExtra = 0;
  // 윈도우의 여분 메모리량
  wc.hInstance = hInstance;
  // 인스턴스 핸들 전장
  wc.hIcon = nullptr;
  // 아이콘 핸들
  /*
    1. IDI_APPLICATION : 기본 아이콘
  */
  wc.hCursor = nullptr;
  // 커서 핸들
  /*
    1. IDC_ARROW : 화살표
    2. IDC_IBEAM : 캐럿
    3. IDC_WAIT : 모래시계
    4. IDC_CROSS : 십자모양커서
    5. IDC_UPARROW : 수직화살표
    6. IDC_SIZENWSE : 역슬래시 모양 크기 조절
    7. IDC_SIZENESW : 슬래시 모양 크기 조절
    8. IDC_SIZEWE : 수평크기 조절
    9. IDC_SIZENS : 수직크기 조절
    10. IDC_SIZEALL : 4방향 화살표
    11 . IDC_NO : 금지모양
    12. IDC_HAND : 손모양
    13. IDC_APPSTARTING : 화살표 + 모래시계
    14. IDC_HELP : 화살표 + ?
  */
  wc.hbrBackground = nullptr;
  // 기본 배경색상 지정
  /*
    GetStockObject() : 함수를 쓰면 윈도우에서 지정하는 기본윈도우 색을 지정
    WHITE_BRUSH : 하얀색 배경화면
    BLACK_BRUSH : 검은색 배경화면

    함수사용시 (HBRUSH)라고 명시적으로 형변환시켜줘야 함
  */
  wc.lpszMenuName = nullptr;
  // 메뉴 리소스
  wc.lpszClassName = pClassName;
  // 윈도우창 클래스 이름
  wc.hIconSm = nullptr;
  // 16*16 작은 아이콘 핸들
  RegisterClassEx( &wc );
  // create window instance
  HWND hWnd = CreateWindowEx(
    0, // 윈도우 스타일 옵션
    pClassName, // 윈도우 클래스 이름
    "Example", // 윈도우 창 택스트 이름
    WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // Window Style
    200,200, //위치
    640,480, //크기
    nullptr, // Parent Window
    nullptr, // Menu
    hInstance, // Instance handle
    nullptr // Additional application data
  );
  ShowWindow( hWnd, SW_SHOW);
  while( true );
  return 0;
}

/*
## Main과 WinMain 함수의 비교
  1. main
    -> 도스 프로그램의 시작점
    -> 반드시 소문자

  2. WinMain
    -> 윈도우 프로그램의 시작점
    -> 대소문자를 반드시 구분

  main 함수는 통상 인수 없이 사용되지만,
  main(int argc, char* argv[]) 처럼 인수를 사용

  WinMain 함수는 인수를 반드시 4개를 갖음
    hInstance : 현재 실행되고 있는 프로그램의 인스턴스 핸들
    hPrevInstance : 바로 앞에 실행된 프로그램의 인스턴스 핸들, 통상 NULL
    lpCmdLine : 명령행 인자. main 함수의 argv에 해당
    nCmdShow : 윈도우를 보여주는 형태의 플래그

## 인스턴스 핸들
  메모리에 생성된 클래스의 실체
  예를 들어 내방에 여러가지 물건(객체)들이 있고 이 모든 물건들이 클래스라고 할 수 있다.
  내가 이 물건들을 활용한다면 이 물건들(클래스의 실체)을 메모리에 생성한다고 말할 수 있다.
  내 방에 컴퓨터가 존재하고(클래스가 존재하고) 내가 컴퓨터를 켠다(메모리에 클래스를 생성한다).
  존재하고 있는 그 자체는, 아직 메모리에 생성되지 않는 상태는 아무 의미가 없다.

  즉, 인스턴스 핸들은 프로그램(클래스의 집합) 메모리에 실제로 올라온 것을 의미하며 각 프로그램마다 고유하다.
  핸들은 인스턴스 핸들 외에도 여러가지 핸들이 사용되며, 핸들은 윈도우 프로그램에 있어서 중요한 요소이고 번번하게 사용된다.

  핸들이란 어떤 대상에 붙여진 레이블(Label)과 같은 것으로, 대상을 식별하는데 주로 사용
  핸들을 이용해 특정 대상을 관리
  여러가지 대상이란 내가 조작할 타켓이며 윈도우가 될 수도 있고 컨트롤이 될 수도 있다.

  - 핸들 값은 예외 없이 모두 접두어 h로 시작
  - 핸들은 정수형이며 32비트 값
  - 핸들은 우영체제가 발급하며, 사용자는 할당된 핸들을 쓰기만(임의의 조작을 방지)
  - 같은 종류의 핸들끼리는 절대 중복된 값을 갖지 아니함
  - 핸들은 단순한 구분자이므로 핸들에 어떤 값이 들어가 있는지 알 필요 없음

  - 여기서 말하는 클래스는 일반적인 C++에서의 클래스가 아니다.
  - 윈도우 프로그래멩서 컴퓨터상의 특정 장치들을 사용하기 위한
  - Player에 대한 클래스들을 나타내는 말임
  - ex : windowclass

## Windows 운영체제가 관리하는 구조체(컨텍스트)와 핸들의 개념
  윈도우 운영체제는 관리하는 모든 객체의 정보를 담고 있는 구조체를 리스트로 유지

  그 객체들은 가시적일 수도 그렇지 않을 수도 있음
  객체의 예로는 프로세스, 윈도우, 디바이스 컨텍스트 들...
  이중 윈도우는 가시적이지만, 프로세스와 디바이스 컨텍스트는 그렇지 않음

  핸들은 윈도우 운영체제가 유지하는 개체를 표현하는 구조체와 관련
  가령, 윈도우는 프로세스가 실행될 때마다 프로세르를 관리하기 위해 구조체를 만듦
  그리고 각 프로세스를 구분하기 위해 각각의 구조체에 다른 프로세스의 구조체와 구본되는 유일한 ID를 할당
  이 ID를 핸들(Handle)이라 하며, 여기서는 프로세스 핸들이 됨
  핸들은 의미있는 값일 수도 있고, 단지 구조체가 할당된 메모리의 시작 주소일 수도 있음

## 윈도우 프로그램의 작성 단계
1. WinMain() 작성

2. 윈도우 클래스의 등록
  RegisterClassEx(&wndclass);

3. 윈도우의 생성
  CreateWindow

4. 윈도우를 화면에 나타내기
  ShowWindow

5. 메세지 루프의 작성
  GetMessage / DispatchMessage

6. 윈도우 프로시저의 구현
  WndProc, DefWindowProc
*/
