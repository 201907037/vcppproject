// 201907037project.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "201907037project.h"
#include <stdlib.h>
#include <time.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY201907037PROJECT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY201907037PROJECT));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY201907037PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY201907037PROJECT);
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

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1300, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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

// 1. 그라운드 2. 시작버튼 3. 정지버튼 4.계속 버튼 5. 마우스 커서 6.배 7.생선 8.낚싯대 8.미끼 9.치유
RECT g_ground, g_start, g_stop, g_resume,g_m, g_ship,g_rob,g_bait;
//1.물고기 객체 배열 2.쓰레기 객체 배열
RECT fish[6],trash[4],g_hp[3];
//1. 물고기 제어 핸들 2.쓰레기 제어 핸들 3.낚싯대,미끼 제어 핸들
HANDLE hfish[6],htrash[4],hrob;
//마우스 커서 x,y좌표
int g_mx, g_my;
//1. 실행 여부를 확인하는 플래그, 2. 배의 동작 여부를 확인하는 플래그
//3.낚싯대 실행여부 4.물고기 객체 visibility상태 5. 쓰레기 객체 visibility상태 6.미끼 상태 7.체력바 8.점수
int sflag, ship_flag, rob_flag, v_flagf[6], v_flagt[4], bait_flag, hp, score;
//1.물고기 배열 인덱스 번호 2.쓰레기 배열 인덱스 번호
int indexf,indext;


DWORD WINAPI fish1(LPVOID param) {
     RECT s;
    HWND hWnd = (HWND)param;
    //srand(time(NULL));
   int n,a,v;
    a = indexf;
   n = rand() % 2+1;
   v = rand() % 10 + 5;
    while (true) {
       if (n == 1) {

            while (fish[a].right <= g_ground.right - 10) {

                fish[a].left += v;
                fish[a].right += v;
                InvalidateRect(hWnd, NULL, true);
              
                Sleep(100);
            }

            while (fish[a].left >= g_ground.left + 10)
            {
                fish[a].left -= v;
                fish[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
               
                Sleep(100);
            }
       }
       else
        {

            while (fish[a].left >= g_ground.left + 10)
            {

                fish[a].left -= v;
                fish[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
                
                Sleep(100);
            }
        
        while (fish[a].right <= g_ground.right - 10) {
            fish[a].left += v;
            fish[a].right += v;
            InvalidateRect(hWnd, NULL, true);

           
            Sleep(100);
        }
       }
    } 
    return 0;
}
DWORD WINAPI trashT(LPVOID param) {
    HWND hWnd = (HWND)param;
    //srand(time(NULL));
    int n, a, v;
    a = indext;
    n = rand() % 2 + 1;
    v = rand() % 10 + 5;
    while (true) {
        if (n == 1) {

            while (trash[a].right <= g_ground.right - 10) {

                trash[a].left += v;
                trash[a].right += v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }

            while (trash[a].left >= g_ground.left + 10)
            {
                trash[a].left -= v;
                trash[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }
        }
        else
        {

            while (trash[a].left >= g_ground.left + 10)
            {

                trash[a].left -= v;
                trash[a].right -= v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }

            while (trash[a].right <= g_ground.right - 10) {
                trash[a].left += v;
                trash[a].right += v;
                InvalidateRect(hWnd, NULL, true);
                Sleep(100);
            }
        }
    }
    return 0;
}
DWORD WINAPI fisher(LPVOID param) {
    rob_flag = 1;
    RECT s;
    HWND hWnd = (HWND)param;
    while (g_rob.bottom < g_ground.bottom) {

        g_rob.bottom += 10;
        g_bait.top += 10;
        g_bait.bottom += 10;
        InvalidateRect(hWnd, NULL, true);
        Sleep(10);
        if (bait_flag == 0) {
            for (int i = 0; i < 6; i++) {
                if (true == IntersectRect(&s, &g_bait, &fish[i])) {
                    if (v_flagf[i] == 1) {
                        break;
                    }
                    v_flagf[i] = 1;
                    bait_flag = 1;
                    score++;
                    break;
                }
            }
            for (int i = 0; i < 4; i++) {
                if (true == IntersectRect(&s, &g_bait, &trash[i])) {
                    if (v_flagt[i] == 1) {
                        break;
                    }
                    v_flagt[i] = 1;
                    bait_flag = 1;
                    if (hp == 0) {
                        break;
                    }
                    else
                    {
                        hp--;
                        if (hp == 0) {
                            
                            for (int i = 0; i < 6; i++) {
                                SuspendThread(hfish[i]);
                                if (i < 5) {
                                    SuspendThread(htrash[i]);
                                }
                            }
                            ship_flag = 0;
                            score = 0;
                            MessageBox(hWnd, L"실패", L"알림", MB_OK);
                           
                        }
                    }
                   
                    break;
                }
            }
            
            
        }
        if (bait_flag == 1) {
            while (g_rob.bottom > 120) {
                g_rob.bottom -= 10;
                g_bait.top -= 10;
                g_bait.bottom -= 10;
                InvalidateRect(hWnd, NULL, true);
                Sleep(10);
            }
            bait_flag = 0;
            break;
        }



    }
    
    while (g_rob.bottom > 120) {
        g_rob.bottom -= 10;
        g_bait.top -= 10;
        g_bait.bottom -= 10;
        InvalidateRect(hWnd, NULL, true);
        Sleep(10);
    }
      
    rob_flag = 0;
    return 0;
}


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
    case WM_LBUTTONDOWN:
    {  
        RECT s;
        
        g_mx = LOWORD(lParam);
        g_my = HIWORD(lParam);
        
        g_m.left = g_mx;
        g_m.top = g_my;
        g_m.right = g_mx + 1;
        g_m.bottom = g_my + 1;
        
        if (true == IntersectRect(&s, &g_start, &g_m)) {
            if(0==sflag){
            //MessageBox(hWnd, L"start", L"notice", MB_OK);
                for(int i=0;i<6;i++){
                    hfish[i] = CreateThread(NULL, 0, fish1, hWnd, 0, NULL);
                    indexf = i;
                    Sleep(1);
                }
                for (int i = 0; i < 4; i++) {
                    htrash[i] = CreateThread(NULL, 0, trashT, hWnd, 0, NULL);
                    indext = i;
                    Sleep(1);
                }
               
                
               
            sflag = 1;
            ship_flag = 1;
            }
            else {
                MessageBox(hWnd, L"이미 실행 중 입니다.", L"Notice", MB_OK);
            }
        }

        if (true == IntersectRect(&s, &g_stop, &g_m)) {
            //MessageBox(hWnd, L"stop", L"notice", MB_OK);
            for (int i = 0; i < 6; i++) {
            SuspendThread(hfish[i]);
            if (i < 5) {
                SuspendThread(htrash[i]);
            }
            }
            ship_flag = 0;
            
        }

        if (true == IntersectRect(&s, &g_resume, &g_m)) {
            //MessageBox(hWnd, L"재개", L"notice", MB_OK);
            if (hp == 0) {
                MessageBox(hWnd, L"재도전", L"알림", MB_OK);
                hp = 3;
                InvalidateRect(hWnd, NULL, true);
            }
            for (int i = 0; i < 6; i++) {
                ResumeThread(hfish[i]);
                if (i < 5) {
                    ResumeThread(htrash[i]);
                }
                
            }
            ship_flag = 1;
        }
        
    }
        break;
    case WM_TIMER:
    {  if (ship_flag==1) {
       
            for (int i = 0; i < 6; i++) {
                v_flagf[i] = 0;
                fish[i].left = 10 + (rand() % 850);
                fish[i].top = 150 + (rand() % 500);
                fish[i].right = fish[i].left + 50;
                fish[i].bottom = fish[i].top + 50;
                InvalidateRect(hWnd, NULL, true);

            }
            for (int i = 0; i < 4; i++) {
                v_flagt[i] = 0;
                trash[i].left = 10 + (rand() % 850);
                trash[i].top = 150 + (rand() % 500);
                trash[i].right = trash[i].left + 50;
                trash[i].bottom = trash[i].top + 50;
                InvalidateRect(hWnd, NULL, true);
            }
        }
   
        
        
    }
        break;
    case WM_CREATE:
    {
        hp = 3;
        SetTimer(hWnd, 1, 5000, NULL);
       
        srand(time(NULL));

        g_hp[2].left = 810;
        g_hp[2].top = 12;
        g_hp[2].right = 830;
        g_hp[2].bottom = 32;

        g_hp[1].left = 850;
        g_hp[1].top = 12;
        g_hp[1].right = 870;
        g_hp[1].bottom = 32;

        g_hp[0].left = 890;
        g_hp[0].top = 12;
        g_hp[0].right = 910;
        g_hp[0].bottom = 32;
        
        g_ship.left = 430;
        g_ship.top = 50;
        g_ship.right = 530;
        g_ship.bottom = 100;

        g_rob.left = 480;
        g_rob.top = 100;
        g_rob.right = 485;
        g_rob.bottom = 120;

        g_bait.left = 480;
        g_bait.top = 120;
        g_bait.right = 485;
        g_bait.bottom = 125;

        for (int i = 0; i < 4; i++) {
            trash[i].left = 10 + (rand() % 850);
            trash[i].top = 150 + (rand() % 500);
            trash[i].right = trash[i].left + 50;
            trash[i].bottom = trash[i].top + 50;
        }

        for (int i = 0; i < 6; i++) {
            fish[i].left = 10 + (rand() % 850);
            fish[i].top = 150 + (rand() % 500);
            fish[i].right = fish[i].left + 50;
            fish[i].bottom =fish[i].top + 50;
        }

        g_resume.left = 1150;
        g_resume.top = 230;
        g_resume.right = 1250;
        g_resume.bottom = 330;

        g_stop.left = 1040;
        g_stop.top = 230;
        g_stop.right = 1140;
        g_stop.bottom = 330;

        g_start.left = 930;
        g_start.top = 230;
        g_start.right = 1030;
        g_start.bottom = 330;

        g_ground.left = 10;
        g_ground.top = 10;
        g_ground.right = 910;
        g_ground.bottom = 710;        
    }
        break;
    case WM_KEYDOWN: 
    {   if(1==ship_flag){
        switch (wParam) {
        case VK_RIGHT:
        {
            if (g_ship.right >= g_ground.right) {
                break;
            }
            else {
                g_ship.left += 10;
                g_ship.right += 10;
                g_rob.left += 10;
                g_rob.right += 10;
                g_bait.left += 10;
                g_bait.right += 10;
                InvalidateRect(hWnd, NULL, true);
            }
        }
        break;
        case VK_LEFT:
        {
            if (g_ship.left <= g_ground.left) {
                
                break;
            }
            else {
                g_ship.left -= 10;
                g_ship.right -= 10;
                g_rob.left -= 10;
                g_rob.right -= 10;
                g_bait.left -= 10;
                g_bait.right -= 10;
                InvalidateRect(hWnd, NULL, true);
            }
        }
           break;
        case VK_DOWN:
        {   
           // CreateThread(NULL, 0, regen, hWnd, 0, NULL);
            if(rob_flag==0){
            hrob = CreateThread(NULL, 0, fisher, hWnd, 0, NULL);
            }
            else {
                
                break;
            }
        }
            break;
           }
    }
    else {
        break;
    }

    }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
           
            HDC hdc = BeginPaint(hWnd, &ps);
            HFONT ssf, osf;
            HBRUSH mb, osb;
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            Rectangle(hdc, g_ground.left, g_ground.top, g_ground.right, g_ground.bottom);
            MoveToEx(hdc, 10, 100, NULL);
            LineTo(hdc, 910, 100);
            Rectangle(hdc, g_start.left, g_start.top, g_start.right, g_start.bottom);
            Rectangle(hdc, g_stop.left, g_stop.top, g_stop.right, g_stop.bottom);
            Rectangle(hdc, g_resume.left, g_resume.top, g_resume.right, g_resume.bottom);
            Rectangle(hdc, g_rob.left, g_rob.top, g_rob.right, g_rob.bottom);
            Rectangle(hdc, g_bait.left, g_bait.top, g_bait.right, g_bait.bottom);

            mb = CreateSolidBrush(RGB(255, 0, 0));
            osb = (HBRUSH)SelectObject(hdc, mb);
            for (int i = 0; i < hp; i++) {
                Rectangle(hdc, g_hp[i].left, g_hp[i].top, g_hp[i].right, g_hp[i].bottom);
            }
            SelectObject(hdc, osb);
            DeleteObject(mb);

            mb = CreateSolidBrush(RGB(125, 125, 125));
            osb = (HBRUSH)SelectObject(hdc, mb);
            Rectangle(hdc, g_ship.left, g_ship.top, g_ship.right, g_ship.bottom);
            SelectObject(hdc, osb);
            DeleteObject(mb);


            mb = CreateSolidBrush(RGB(0, 0, 255));
            osb = (HBRUSH)SelectObject(hdc, mb);
           
            for(int i =0;i<6;i++){
                if (v_flagf[i] == 0){
                        Rectangle(hdc, fish[i].left, fish[i].top, fish[i].right, fish[i].bottom);
                }
               
            }
            SelectObject(hdc, osb);
            DeleteObject(mb);


            mb = CreateSolidBrush(RGB(0, 0, 0));
            osb = (HBRUSH)SelectObject(hdc, mb);
            for (int i = 0; i < 4; i++) {
                if(v_flagt[i]==0){
                Ellipse(hdc, trash[i].left, trash[i].top, trash[i].right, trash[i].bottom);
                }
                
            }
            SelectObject(hdc, osb);
            DeleteObject(mb);

            WCHAR scorestr[1024];
            wsprintfW(scorestr, L"점수 : %d", score);

            ssf = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, ANSI_CHARSET, 0, 0, 0, 0, NULL);
            osf = (HFONT)SelectObject(hdc, ssf);
            TextOut(hdc, 920, 15, scorestr, lstrlen(scorestr));
            TextOut(hdc, 945, 270, L"START", 5);
            TextOut(hdc, 1060, 270, L"STOP", 4);
            TextOut(hdc, 1160, 270, L"RESUME", 6);
            SelectObject(hdc, osf);
            DeleteObject(ssf);


            EndPaint(hWnd, &ps);
        }
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
