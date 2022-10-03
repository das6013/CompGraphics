// Лабораторная работа 1. Двумерные геометрические преобразования.
// Задача 9. Кувырок

#include "graphics.h"
#include "figure.h"
#include <iostream>
#include "app.h"

bool App::_isRunnig = false;
//Задание фигуры с помощью вершин и граней
Figure rectangle(
	{
	{ 0, 0 },
	{ 0, 69 },
	{ 134, 69 },
	{ 134, 0 },
	}, {
		{ 3, 0 },
		{ 0, 1 },
		{ 1, 2 },
		{ 2, 3 },
	});

void App::Run()
{
	_isRunnig = true;
}

// метод рисующий фигуры
void App::Draw()
{
	Graphics g;

	g.DrawLine(0, 308, Graphics::width - 1, Graphics::height - 1, RGB(255, 255, 255));

	rectangle.Draw(g);
}

void App::Update()
{
	static const int a = 30;

	static uint32_t i = a;

	if (_isRunnig)
	{
		if (i % a == 0)
		{
			rectangle.SetPivot(i / a % 4);
		}

		rectangle.Rotate(90.f / a);

		Draw();

		i++;

		if (i / a == 6)
		{
			_isRunnig = false;
		}
	}
}

void App::Init()
{
	// 1
	rectangle.Rotate(-75);
	rectangle.Translate(0, 307);
	Draw();
}

