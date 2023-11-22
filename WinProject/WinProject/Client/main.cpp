// Client.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "Client.h"
#include "pch.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd; // 전역 윈도우 핸들

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// SAL 주석(_In_) : 소스코드 주석언어, 해당 변수의 용도를 적어놓는 것
int APIENTRY wWinMain(_In_ HINSTANCE hInstance /* 실행 된 프로세스의 시작주소. 이때 프로세스를 여러개 실행해도 같은 주소값을 갖는다.
                                                  이 프로그램이 자신만의 가상메모리를 사용하기 떄문. 물론 물리적인 주소는 다르다. */,
    _In_opt_ HINSTANCE hPrevInstance /* 먼저 실행 된 프로세스의 시작주소(option) -> 초창기의 윈도우가 그랬고, 지금은 그렇게 동작하지 않음. */,
    _In_ LPWSTR    lpCmdLine /* 프로그램 시작시 문자열을 입력하면 들어온다. */,
    _In_ int       nCmdShow)
{
    // 메모리 릭(누수) 체크
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // _CrtSetBreakAlloc(); // 문제가 생겼을 때 문제 해당 지점에 중단점을 걸어줌

    // 쓰이지 않는 변수 => 참조되지 않는 변수
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CLIENT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다: 윈도우 창을 생성합니다.
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Core 초기화 진행. 실패하면 실패했다는 메세지 창을 띄우고 종료.
    if (FAILED(CCore::GetInstance()->Init(g_hWnd, POINT{ 1280, 768 }))) {
        MessageBox(nullptr, L"Core 객체 초기화 실패", L"ERROR", MB_OK);

        return FALSE;
    }

    // 단축키 정보 등록
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLIENT));

    MSG msg;

    // 기본 메시지 루프입니다:
    // 
    /* GetMessage
    * 메세지 큐에서 메시지를 확인할 때까지 대기함
    * msg.message = WM_QUIT인 경우, false를 반환함 => 프로그램 종료
    * 이는 모든 작업(창닫기, 함수종료 등)이 마무리되고 반환되는 값 
    * 게임 클라이언트로 제작하기에는 부적합하다.
    */ 

    // SetTimer(g_hWnd, 0, 0, nullptr);
    /*while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }*/
    // 프로그램 종료시 타이머 제거
    // KillTimer(g_hWnd, 0);

    /*
        PeekMessage : 슬쩍보다
        메세지 유무와 관계없이 반환한다. 즉, 메세지큐에 메세지가 있으면 true, 없으면 false를 반환함
    */

    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 받은 메세지가 종료메세지라면 프로그램 종료
            if (msg.message == WM_QUIT) break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            // 메세지가 없는 대부분의 시간의 경우
            // 이곳에서 게임 코드를 수행합니다.

            CCore::GetInstance()->Progress();
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLIENT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLIENT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

#include<vector>
using std::vector;

POINT LmousePos;
POINT RmousePos;

struct OBJinfo {
    POINT g_objPos;
    POINT g_objScale;
};

vector<OBJinfo> objects;
bool LbuttonDown;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT: // 무효화 영역(Invaildate Rect)이 발생한 경우 => 창이 줄였다가 다시 켜지는 경우
        {
            PAINTSTRUCT ps;
            // 윈도우 핸들(hWnd)
            // 윈도우에 무엇인가를 그리려면 항상 선언해야함.
            HDC hdc = BeginPaint(hWnd, &ps); // Device Context(그리기 작업 수행, 필요한 데이터의 집합)를 만들어서 ID 핸들값을 반환
            /*
            // DC의 목적지는 hWnd
            // Dc의 펜은 기본펜(검정)
            // DC의 브러쉬는 기본 브러쉬(White)
            
            // 윈도우 좌표 : pixel 단위
            // hdc, 우측, 하단, 가로크기, 세로세로크기
            // 그리고 브러쉬로 안을 채움.
            // pixel 하나씩 메모리에 RGB 3byte씩 들어있음.
            Rectangle(hdc, 10, 10, 110, 110);

            // SelectObject가 void Type*으로 나오기 때문에, 어떤 오브젝트든 캐스팅하여 받을 수 있다.
            HPEN hPen = CreatePen(PS_DASH, 1, RGB(255, 0, 0));
            HPEN hDefalutPen = (HPEN)SelectObject(hdc, hPen);

            //HBRUSH hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 기본으로 내장되어 있는 오브젝트를 가져올 수 있다.
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
            HBRUSH hDefalutBrush = (HBRUSH)SelectObject(hdc, hBrush);

            if (LbuttonDown) {
                Rectangle(hdc, 
                    LmousePos.x, LmousePos.y,
                    RmousePos.x, RmousePos.y);
            }

            for (int i = 0; i < objects.size(); i++)
            {
                Rectangle(hdc,
                    objects[i].g_objPos.x - objects[i].g_objScale.x / 2, objects[i].g_objPos.y - objects[i].g_objScale.y / 2,
                    objects[i].g_objPos.x + objects[i].g_objScale.x / 2, objects[i].g_objPos.y + objects[i].g_objScale.y / 2);
            }

            // 사용한 펜과 브러쉬를 제거
            (HPEN)SelectObject(hdc, hDefalutPen);
            DeleteObject(hPen);
            

            */
            EndPaint(hWnd, &ps);
        }
        break;
    /* wParam으로 키보드 값, lParam으로 마우스 값을 인식할 수 있음. */
    case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_UP: // 미리 명시된 값을 통해서 인식
                    //g_objPos.y -= 10;
                    break;
                case VK_DOWN:
                    //g_objPos.y += 10;
                    break;
                case VK_LEFT:
                    //g_objPos.x -= 10;
                    break;
                case VK_RIGHT:
                    //g_objPos.x += 10;
                    break;
                //case 'W': // 또는 아스키코드값을 통해서 인식할 수 있다.
                //    break;
                default:
                    break;
            }
            //InvalidateRect(hWnd, nullptr, true);
        }
        break;
    case WM_LBUTTONDOWN:
        // lParam으로 마우스 x, y좌표가 들어온다.
        // 이때, lParam의 상위 2바이트와 하위 2바이트를 나누어서 좌표값을 알아낸다.
        LmousePos.x = LOWORD(lParam);
        LmousePos.y = HIWORD(lParam);
        // 강제로 윈도우 창의 무효화영역으로 지정해준다. 이렇게 하여 WM_PAINT 메세지를 다시 호출한다.
        //InvalidateRect(hWnd, nullptr, true);
        LbuttonDown = true;
        break;
    case WM_MOUSEMOVE:
        RmousePos.x = LOWORD(lParam);
        RmousePos.y = HIWORD(lParam);
        //InvalidateRect(hWnd, nullptr, true);
        break;
    case WM_LBUTTONUP:
        OBJinfo newObj;
        newObj.g_objPos = { (LmousePos.x + RmousePos.x) / 2, (LmousePos.y + RmousePos.y) / 2 };
        newObj.g_objScale = { abs(LmousePos.x - RmousePos.x), abs(LmousePos.y - RmousePos.y) };
        objects.push_back(newObj);
        LbuttonDown = false;
        break;
    // SetTimer로 실행되는 구간
    case WM_TIMER:


        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
