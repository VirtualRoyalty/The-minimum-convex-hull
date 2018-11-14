#include <conio.h> 
#include <windows.h> 
#include <iostream>
#include "draw.h"
void drawpoint(HDC hdc, int left, int top)//draw a point
{

	Ellipse(hdc, left, 270 - top, left + 10, 270 - top + 10);
}
void drawSHELL(int dot[][2], int *list, int N)//draw a shell via on list of points included in the shell
{
	HWND hWnd = FindWindowA("ConsoleWindowClass", NULL);
	HDC hdc = GetDC(hWnd);
	HPEN p1, p2 = CreatePen(PS_SOLID, 2, RGB(0, 107, 60));
	p1 = (HPEN)SelectObject(hdc, p2);
	MoveToEx(hdc, dot[list[0]][0] + 3, 270 - dot[0][1] + 3, NULL);
	for (auto i = 0; i < N; i++)
	{
		LineTo(hdc, dot[list[i]][0] + 3, 270 - dot[list[i]][1] + 3);
	}
	LineTo(hdc, dot[0][0] + 3, 270 - dot[0][1] + 3);
	ReleaseDC(hWnd, hdc);
}
void drawPOINTS(int dot[][2], const int N)
{
	HWND hWnd = FindWindowA("ConsoleWindowClass", NULL);
	HDC hdc = GetDC(hWnd);
	HPEN p1, p2 = CreatePen(PS_SOLID, 1, RGB(0, 107, 60));
	p1 = (HPEN)SelectObject(hdc, p2);
	for (auto i = 0; i < N; i++)
	{
		drawpoint(hdc, dot[i][0], dot[i][1]);

	}

}
int rotate(int dot[][2], int i, int j, int f)//func to determine the right-position or left-position
{
	return (dot[j][0] - dot[i][0])*(dot[f][1] - dot[j][1]) - (dot[j][1] - dot[i][1])*(dot[f][0] - dot[j][0]);
}

bool checklist(int *list, int N, int num)
{
	for (auto i = 0; i <= N; i++)
	{
		if (list[i] == num)
		{
			return TRUE;
		}
	}
	return FALSE;
}

void buildSHELL(int dot[][2], int N)
{
	int *list = new int[N];
	for (auto i = 0; i < N; i++)
	{
		if (dot[i][0] < dot[0][0])
		{
			int tmp;
			tmp = dot[i][0];
			dot[i][0] = dot[0][0];
			dot[0][0] = tmp;
			tmp = dot[i][1];
			dot[i][1] = dot[0][1];
			dot[0][1] = tmp;
		}

	}
	for (auto i = 1; i < N; i++)
		for (auto j = 1; j < N - i; j++)
		{
			if (dot[j][0] > dot[j + 1][0])
			{
				int tmp;
				tmp = dot[j][0];
				dot[j][0] = dot[j + 1][0];
				dot[j + 1][0] = tmp;
				tmp = dot[j][1];
				dot[j][1] = dot[j + 1][1];
				dot[j + 1][1] = tmp;
			}

		}
	int right;
	list[0] = 0;
	int itr = 0;
	/*for (auto i = 0; i < N ; i++)
	{
		std::cout << " ( " << dot[i][0] << " , " << dot[i][1] << " ) ";
	}*/
	while (1)
	{
		right = 1;
		for (auto i = 2; i < N; i++)
		{
			if (rotate(dot, list[itr], right, i) <= 0)
			{
				if (checklist(list, itr + 1, i) == FALSE)
				{
					right = i;
				}
			}
		}
		if (right == 1)
		{
			break;
		}
		else
		{
			itr++;
			if (itr > N)
			{
				break;
			}
			list[itr] = right;
		}
	}
	std::cout << "list of min SHELL:" << std::endl;
	for (auto i = 0; i < itr + 1; i++)
	{
		std::cout << " ( " << dot[list[i]][0] << " , " << dot[list[i]][1] << " ) " << std::endl;
	}
	drawSHELL(dot, list, itr + 1);
	drawPOINTS(dot, N);
}