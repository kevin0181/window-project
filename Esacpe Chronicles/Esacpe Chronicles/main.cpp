#include <Windows.h>
#include <string>
#include <atlimage.h>
#include <vector>

// ------------------

#include "Stage.h"
#include "StageManager.h"
#include "Monster.h"
#include "Slime.h"
#include "Zombie1.h"
#include "Zombie2.h"
#include "Zombie3.h"
#include "Block.h"
#include "Player.h"

#define BLOCK_SIZE 70

using namespace std;

HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Escape Chronicles";
LPCTSTR lpszWindowName = L"Escape Chronicles";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_QUESTION);
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_QUESTION);
	RegisterClassEx(&WndClass);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_POPUP | WS_VISIBLE,
		0, 0, screenWidth, screenHeight, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return static_cast<int>(Message.wParam);
}

Slime slime;
Zombie1 zombie1;
Zombie2 zombie2;
Zombie3 zombie3;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	static RECT rect; // 화면 전체 크기

	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBITMAP hBitmap;
	HBITMAP hOldBitmap;

	static StageManager stageManager;
	static Player player;

    switch (uMsg) {
    case WM_CREATE:
    {
		GetClientRect(hWnd, &rect);
        stageManager.setBackground_img(stageManager.intro_img_path[0]);
		stageManager.game_rect = rect;
		stageManager.game_rect.right *= 3;
     
        slime.insert();
        zombie1.insert();
        zombie2.insert();
        zombie3.insert();
        SetTimer(hWnd, 1, 1, FALSE);
        break;
    }
    case WM_SIZE:
        break;
    case WM_KEYDOWN:

		if (stageManager.getCurrent_stage() == STAGE::INTRO)
			stageManager.setKeyDown(wParam);

		if (stageManager.getCurrent_stage() == STAGE::STAGE_1 || stageManager.getCurrent_stage() == STAGE::STAGE_2 ||
			stageManager.getCurrent_stage() == STAGE::STAGE_3)
			player.setKeyDown(wParam);

		break;
	case WM_KEYUP:
		player.setKeyUp(wParam);
		break;
	case WM_PAINT: {
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC);
		GetClientRect(hWnd, &rect);
		hBitmap = CreateCompatibleBitmap(hDC, rect.right, rect.bottom);
		hOldBitmap = static_cast<HBITMAP>(SelectObject(mDC, hBitmap));

		FillRect(mDC, &rect, static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));

		/*
		intro
		 스토리 이미지
		*/
		if (STAGE::INTRO == stageManager.getCurrent_stage()) {
			stageManager.DrawBackground_img(mDC, rect, 1);
		}

		/*
		stage 1
			플레이어, 슬라임, 파란색 벽돌
		*/
		if (STAGE::STAGE_1 == stageManager.getCurrent_stage()) {
			stageManager.DrawBackground_img(mDC, rect, 4);
			slime.print(mDC);
			player.print(mDC);
		}

		// ------------------------------------------------
		//zombie1.print(mDC);
		zombie2.print(mDC);
		zombie3.print(mDC);

		BitBlt(hDC, 0, 0, rect.right, rect.bottom, mDC, 0, 0, SRCCOPY);

		SelectObject(mDC, hOldBitmap);
		DeleteObject(hBitmap);
		DeleteDC(mDC);
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_TIMER:
		if (wParam == 1) {

			switch (stageManager.getCurrent_stage())
			{
			case STAGE::STAGE_1:
			{
				
				
				slime.move(stageManager,rect);//_left
				
				//zombie1.move(stageManager,rect);
				zombie2.move(stageManager, rect);
				zombie3.move(stageManager, rect);

				//player
				player.TIMER(stageManager);
				break;
			}
			default:
				break;
			}
		}
		InvalidateRect(hWnd, NULL, false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}