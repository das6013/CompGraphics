// ������������ ������ 2. ���������� �������� ��������� ������� �����.
// ������ 9. ������.

#include "graphics.h"
#include "camera.h"
#include "wireframe.h"

#include "app.h"

bool App::running_ = false;

Wireframe model({
	{ 6, 0, 0 },

	{ 3, -1.1547005383792515f, 0 },
	{ 3, -0.5773502691896264f, -1},
	{ 3, 0.5773502691896264f, -1},
	{ 3, 1.1547005383792515f, 0 },
	{ 3, 0.5773502691896264f, 1},
	{ 3, -0.5773502691896264f, 1},

	{ -6, -1.1547005383792515f, 0 },
	{ -6, -0.5773502691896264f, -1},
	{ -6, 0.5773502691896264f, -1},
	{ -6, 1.1547005383792515f, 0 },
	{ -6, 0.5773502691896264f, 1},
	{ -6, -0.5773502691896264f, 1},
	}, {
		{ 1, 7 },

		{ 1, 2 },
		{ 2, 3 },
		{ 3, 4 },
		{ 4, 5 },
		{ 5, 6 },
		{ 6, 1 },

		{ 7, 8 },
		{ 8, 9 },
		{ 9, 10 },
		{ 10, 11 },
		{ 11, 12 },
		{ 12, 7 },

		{ 0, 1 },
		{ 0, 2 },
		{ 0, 3 },
		{ 0, 4 },
		{ 0, 5 },
		{ 0, 6 },

		{ 2, 8 },
		{ 3, 9 },
		{ 4, 10 },
		{ 5, 11 },
		{ 6, 12 },
	});

void App::Run()
{
	running_ = true;
}

void App::Draw()
{
	Graphics g;

	// coordinate axes
	Camera::DrawLine(g, 0, 0, 0, 2, 0, 0, RGB(200, 0, 0));
	Camera::DrawLine(g, 0, 0, 0, 0, 2, 0, RGB(0, 200, 0));
	Camera::DrawLine(g, 0, 0, 0, 0, 0, 2, RGB(0, 0, 200));

	// model
	model.Draw(g);
}

void App::Update()
{
	model.Rotate(1, 0, 0);

	Draw();
}

void App::Init()
{
	Camera::LookAt(2, 2, 1);
	Camera::Ortho(Graphics::width / 2, Graphics::height / 2, 50);
	Draw();
}
