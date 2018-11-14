
#pragma once
#include <conio.h> 
#include <windows.h> 
#include <iostream>

void drawpoint(HDC hdc, int left, int top);

void drawSHELL(int dot[][2], int *list, int N);

void drawPOINTS(int dot[][2], const int N);

int rotate(int dot[][2], int i, int j, int f);

bool checklist(int *list, int N, int num);

void buildSHELL(int dot[][2], int N);
