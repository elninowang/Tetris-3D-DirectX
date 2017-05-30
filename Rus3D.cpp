// Rus3D.cpp : ����Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "Rus3D.h"
#include "Define.h"
#include "ddraw.h"
#include "var.h"
#include "Boxes.h"
#include "Show.h"
#include "Platform.h"
#include "Draw.h"
#include "DirectX.h"
#define MAX_LOADSTRING 100

// ȫ�ֱ�����
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ��������
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_RUS3D, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ����
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_RUS3D);

	// ����Ϣѭ����
	while (GetMessage(&msg, NULL, 0, 0)) 
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
//  ������MyRegisterClass()
//
//  Ŀ�ģ�ע�ᴰ���ࡣ
//
//  ע�ͣ�
//
//    ����ϣ��������ӵ� Windows 95 ��
//    ��RegisterClassEx������֮ǰ�˴����� Win32 ϵͳ����ʱ��
//    ����Ҫ�˺��������÷������ô˺���
//    ʮ����Ҫ������Ӧ�ó���Ϳ��Ի�ù�����
//   ����ʽ��ȷ�ġ�Сͼ�ꡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_RUS3D);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= (LPCTSTR)IDC_RUS3D;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}

//
//   ������InitInstance(HANDLE, int)
//
//   Ŀ�ģ�����ʵ�����������������
//
//   ע�ͣ�
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ������WndProc(HWND, unsigned, WORD, LONG)
//
//  Ŀ�ģ����������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_CREATE:
		if( !InitDirectX(hWnd ) )
		{
			MessageBox(hWnd, TEXT("DirectX�ӿ�ʧ��"), TEXT("ERROR"), NULL);
			CleanUp();
			SendMessage( hWnd, WM_DESTROY, 0, 0 );
		}
		Init();
		iTime = 0;
		SetTimer(hWnd,1,TIME,NULL);
		isRun = true;
		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// �����˵�ѡ��
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �ڴ���������ͼ����...
		DrawDirectX();
		EndPaint(hWnd, &ps);
		break;
	case WM_SIZE:
		DrawDirectX();
		break;
	case WM_KEYDOWN:
		if( isRun == false )
		{
			switch( LOWORD(wParam) )
			{
			case VK_UP:
				yMe-=5;
				DrawDirectX();
				break;
			case VK_DOWN:
				yMe+=5;
				DrawDirectX();
				break;
			case VK_LEFT:
				xMe-=5;
				DrawDirectX();
				break;
			case VK_RIGHT:
				xMe+=5;
				DrawDirectX();
				break;
			case VK_TAB:
				zMe--;
				DrawDirectX();
				break;
			case VK_SPACE:
				zMe++;
				if( zMe >=-1 )
					zMe=-1;
				DrawDirectX();
				break;
			case VK_RETURN:
				iTime = 0;
				iRealTime = iTempTime;
				isRun = true;
				DrawDirectX();
				break;
			case VK_ESCAPE:
				SendMessage(hWnd, WM_DESTROY, 0, 0 );
				break;
			}
		}
		else
		{
			switch( LOWORD(wParam) )
			{
			case VK_UP:
				if( CheckUp() )
				{
					yNow--;
					DrawDirectX();
				}
				break;
			case VK_DOWN:
				if( CheckDown() )
				{
					yNow++;
					DrawDirectX();
				}
				break;
			case VK_LEFT:
				if( CheckLeft() )
				{
					xNow--;
					DrawDirectX();
				}
				break;
			case VK_RIGHT:
				if( CheckRight() )
				{
					xNow++;
					DrawDirectX();
				}
				break;
			case 'A':
				if( CheckTurn(0,offX,offY,offZ) )
				{
					swap( inT, inH);
					xNow+=offX;
					yNow+=offY;
					DrawDirectX();
				}
				break;
			case 'Z':
				if( CheckTurn(1,offX,offY,offZ) )
				{
					swap( inH, inT);
					xNow+=offX;
					yNow+=offY;
					DrawDirectX();
				}
				break;
			case 'S':
				if( CheckTurn(2,offX,offY,offZ) )
				{
					swap( inT, inV);
					xNow+=offX;
					yNow+=offY;
					zNow+=offZ;
					DrawDirectX();
				}
				break;
			case 'X':
				if( CheckTurn(3,offX,offY,offZ) )
				{
					swap( inV, inT);
					xNow+=offX;
					yNow+=offY;
					zNow+=offZ;
					DrawDirectX();
				}
			case 'D':
				if( CheckTurn(4,offX,offY,offZ) )
				{
					swap( inH, inV);
					xNow+=offX;
					yNow+=offY;
					zNow+=offZ;
					DrawDirectX();
				}
				break;
			case 'C':
				if( CheckTurn(5,offX,offY,offZ) )
				{
					swap( inV, inH);
					xNow+=offX;
					yNow+=offY;
					zNow+=offZ;
					DrawDirectX();
				}
				break;
			case VK_SPACE:
			case VK_TAB:
				iTime = 0;
				iRealTime = iFastTime;
				break;
			case VK_RETURN:
				iTime = 0;
				iRealTime = iTempTime;
				isRun = false;
				DrawDirectX();
				break;
			case VK_ESCAPE:
				SendMessage(hWnd, WM_DESTROY, 0, 0 );
				break;
			}
		}
		break;
	case WM_KEYUP:
		if( isRun )
		{
			if( LOWORD(wParam) == VK_SPACE ||  LOWORD(wParam) == VK_TAB )
			{
				iTime = 0;
				iRealTime = iTempTime;
			}
		}
		break;
	case WM_TIMER:
		if( isRun == true )
		{
			iTime++;
			if( iTime == iRealTime )
			{
				if( CheckInto() )
				{
					zNow++;
					DrawDirectX();
				}
				else
				{
					WriteNow();
					MakeDown();	
					DrawDirectX();
					iNum = _iNum;
					inV = _inV;
					inH = 2;
					inT = 1;
					_iNum = GetRand( BOXES );
					_inV = 3;	
					xNow=LCX/2;
					yNow=LCY/2;
					zNow=0;
					if( !CheckNow() )
					{
						isRun = false;
						Restart();
					}
					if( isRun )
						DrawDirectX();	
				}
				iTime=0;
			}
		}
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		CleanUp();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
