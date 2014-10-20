#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Include all the windows headers.
#include <windowsx.h> // Include useful macros.
#include<string>
#include<vector>
#include <algorithm>
#include"Cards.h"
using namespace std;

#define WINDOW_CLASS_NAME L"WINCLASS1"

LRESULT CALLBACK WindowProc(HWND _hwnd,
							UINT _msg,
							WPARAM _wparam,
							LPARAM _lparam)
{
	// This is the main message handler of the system.
	PAINTSTRUCT ps; // Used in WM_PAINT.
	HDC hdc; // Handle to a device context.
	CCards testCard;
	RECT rec;
	wchar_t buffer[255];
	

	testCard.SetSuit(clubs);
	testCard.GetSuit();
	testCard.FlipCard();
	testCard.FlipCard();
	vector<CCards> deck,revealpile,heartpile,diamondpile,spadepile,clubpile;
	vector<vector<CCards>> playingspace[7];
	int cardDraw = 1;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			
			CCards* tempCard = new CCards;
			tempCard->SetSuit((m_eCardSuits)i);
			tempCard->SetValue(j);
			deck.push_back(*tempCard);
		}
	}

	//SHUFFLE
	random_shuffle(deck.begin(),deck.end());

	for (int i = 0; i< 7; i++)
	{
		vector<CCards> temp;
		playingspace[i];
		for (int j = 0; j<1+i;j++)
		{
			temp.push_back(deck.back());
			deck.pop_back();
		}
		playingspace[i].push_back(temp);
		playingspace[i].back().back().FlipCard();
	}

	// What is the message?
	switch (_msg)
	{
		case WM_CREATE:
		{
			// Do initialization stuff here.
			// Return Success.
			
			return (0);
		}
		break;
		case WM_PAINT:
		{
			// Simply validate the window.
			hdc = BeginPaint(_hwnd, &ps);
			// You would do all your painting here...
			//DrawText(hdc, itostr(testCard.GetSuit()),strlen("Text Out String"), &rec, DT_TOP|DT_LEFT);
			//swprintf_s(buffer, _countof(buffer), L"Blah blah blah %ld", testCard.GetSuit(););
			DrawText(hdc, buffer, -1, &rec, DT_CENTER | DT_WORDBREAK);

			EndPaint(_hwnd, &ps);
			// Return Success.
			return (0);
		}
		break;
		case WM_LBUTTONDOWN:
		{
			if (!deck.empty())
			{
				for(int i = 0; i<cardDraw; i++)
				{
					revealpile.push_back(deck.back());
					revealpile.back().FlipCard();
					deck.pop_back();
					
				}
			}
			else
			{
				for(int i = 0; i<revealpile.size();i++)
				{
					deck.push_back(revealpile.back());
					deck.back().FlipCard();
					revealpile.pop_back();
				}
			}
		}
		break;
		case WM_DESTROY:
		{
			// Kill the application, this sends a WM_QUIT message.
			PostQuitMessage(0);
			// Return success.
			return (0);
		}
		break;
		default:break;
	} // End switch.

	// Process any messages that we did not take care of...
	return (DefWindowProc(_hwnd, _msg, _wparam, _lparam));
}


int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	WNDCLASSEX winclass; // This will hold the class we create.
	HWND hwnd; // Generic window handle.
	MSG msg; // Generic message.

	// First fill in the window class structure.
	winclass.cbSize = sizeof(WNDCLASSEX);
	winclass.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc = WindowProc;
	winclass.cbClsExtra = 0;
	winclass.cbWndExtra = 0;
	winclass.hInstance = _hInstance;
	winclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground = CreateSolidBrush(RGB(0,128,0));
	//static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	winclass.lpszMenuName = NULL;
	winclass.lpszClassName = WINDOW_CLASS_NAME;
	winclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	// register the window class
	if (!RegisterClassEx(&winclass))
	{
		return (0);
	}

	hwnd = CreateWindowEx(NULL, // Extended style.
	WINDOW_CLASS_NAME, // Class.
	L"Solitaire", // Title.
	WS_OVERLAPPEDWINDOW | WS_VISIBLE,
	0, 0, // Initial x,y.
	800, 600, // Initial width, height.
	NULL, // Handle to parent.
	NULL, // Handle to menu.
	_hInstance, // Instance of this application.
	NULL); // Extra creation parameters.

	// Check the window was created successfully.
	if (!hwnd)
	{
		return (0);
	}

	// Enter main event loop.
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// Translate any accelerator keys...
		TranslateMessage(&msg);
		// Send the message to the window proc.
		DispatchMessage(&msg);
	}

	// Return to Windows like this...
	return (static_cast<int>(msg.wParam));
}