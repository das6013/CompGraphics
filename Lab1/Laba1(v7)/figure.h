#pragma once

#include <array>
#include <vector>

#include "graphics.h"
#include "matrix.h"

class Figure
{
public:
	Figure(std::vector<std::array<int32_t, 2>> vertices, std::vector<std::array<uint32_t, 2>> edges);

	void SetPivot(uint32_t vertex);
	void Scaling(float s1,float s2);
	void LessScaling(float s1, float s2);
	void Translate(float x, float y);
	void Rotate(float ang);

	void Draw(Graphics &g);
	void DrawPoint(Graphics& g);
	float GetDistanseX(Figure b)
	{
		return GetCenterX() - b.GetCenterX();
		//return vertices_[pivot_][0] - b.vertices_[b.pivot_][0];
	}

	float GetDistanseY(Figure b) 
	{
		return GetCenterY() - b.GetCenterY();
		//return vertices_[pivot_][1] - b.vertices_[b.pivot_][1];
	}

	float GetCenterX()
	{
		return vertices_[Xmax()][0]+(vertices_[Xmin()][0] - vertices_[Xmax()][0])/2;
	}

	float GetCenterY() 
	{	
		return vertices_[Ymax()][1] + (vertices_[Ymin()][1] - vertices_[Ymax()][1]) / 2;
	}
	int Xmax() {
		int i = 0;
		int nmax = i;
		float max = vertices_[i][0];
		for (i = 1; i < 8; i++) {
			if (max < vertices_[i][0]) {
				max = vertices_[i][0];
				nmax = i;
			}
		}
		return nmax;
	}
	int Xmin() {
		int i = 0;
		int nmin = i;
		float min = vertices_[i][0];
		for (i = 1; i < 8; i++) {
			if (min > vertices_[i][0]) {
				min = vertices_[i][0];
				nmin = i;
			}
		}
		return nmin;
	}
	int Ymin() {
		int i = 0;
		int nmin = i;
		float min = vertices_[i][1];
		for (i = 1; i < 8; i++) {
			if (min > vertices_[i][1]) {
				min = vertices_[i][1];
				nmin = i;
			}
		}
		return nmin;
	}
	int Ymax() {
		int i = 0;
		int nmax = i;
		float max = vertices_[i][1];
		for (i = 1; i < 8; i++) {
			if (max < vertices_[i][1]) {
				max = vertices_[i][1];
				nmax = i;
			}
		}
		return nmax;
	}

private:
	Matrix vertices_;
	std::vector<std::array<uint32_t, 2>> edges_;

	uint32_t pivot_ = 0;
};
