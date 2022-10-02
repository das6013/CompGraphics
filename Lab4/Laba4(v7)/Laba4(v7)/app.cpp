// Лабораторная работа 4. Удаление невидимых линий поверхности методом плавающего горизонта.
// Вариант 4. Поворот вокруг осей y, x, рисование отрезками.
// Задача 7 Пик.

#include <cmath>

#include "graphics.h"
#include "surface.h"
#include "app.h"

bool App::running_ = false;





// 9
Surface surface(-pi / 2, pi / 2, -pi / 2, pi / 2, [](float x, float z) { return sin(x + pi / 2) * sin(z + pi / 2); });



void App::Run()
{

}

void App::Draw()
{
	Graphics g;

	// surface - поверхность
	surface.Draw(g);
}

void App::Update()
{
	
		static int32_t a = 0; // angle
		static int32_t i = 1; // increment

		//surface.SetAngles(25, a);

		a += i;

		if (a >= 60 || a <= -60)
		{
			i = -i;
		}

		Draw();
}

void App::Init()
{
	//Camera::LookAt(0, 0, -1);
	Camera::Ortho(Graphics::width / 2, Graphics::height / 2, 1);

	surface.SetAngles(15, 45);

	//Draw();
}
