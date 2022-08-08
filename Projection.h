#ifndef PROJECTION_H
#define PROJECTION_H
#include<iostream>
#include<vector>
#include<array>
#include<cmath>
#include "Camera.h";
class Projection {
public:
	 float NEAR;
	 float FAR;
	 float RIGHT;
	 float LEFT;
	 float TOP;
	float BOTTOM;
	float m00;
	float m11;
	float m22;
	float m32;
	float HH;
	float HW;
	std::array<std::array<float, 4>, 4> projection_matrix;
	std::array<std::array<float, 4>, 4> to_screen_matrix;

	Projection(float half_width, float half_height, float nearplane,float farplane,float h_fov,float v_fov) {
		NEAR = nearplane;
		FAR = farplane;
		RIGHT = tan(h_fov / 2);
		LEFT = -RIGHT;
		TOP = tan(v_fov / 2);
		BOTTOM = -TOP;
		m00 = 2 / (RIGHT - LEFT);
		m11 = 2 / (TOP - BOTTOM);
		m22 = (FAR + NEAR) / (FAR - NEAR);
		m32 = -2 * NEAR * FAR / (FAR - NEAR);
		projection_matrix = { {
			{{m00, 0, 0, 0}},
			{{0, m11, 0, 0}},
			{{0, 0, m22, 1}},
			{{0, 0, m32, 0}},
		} };

		HW = half_width;
		HH = half_height;
		
		to_screen_matrix = { {
			{{HW, 0, 0, 0}},
			{{0, -HH, 0, 0}},
			{{0, 0, 1, 0}},
			{{HW, HH, 0, 1}},
} };

	}



	Projection(float half_width, float half_height, Camera* camptr) {
		NEAR = camptr->near_plane;
		FAR = camptr->far_plane;
		RIGHT = tan(camptr->h_fov / 2);
		LEFT = -RIGHT;
		TOP = tan(camptr->v_fov / 2);
		BOTTOM = -TOP;
		m00 = 2 / (RIGHT - LEFT);
		m11 = 2 / (TOP - BOTTOM);
		m22 = (FAR + NEAR) / (FAR - NEAR);
		m32 = -2 * NEAR * FAR / (FAR - NEAR);
		projection_matrix = { {
			{{m00, 0, 0, 0}},
			{{0, m11, 0, 0}},
			{{0, 0, m22, 1}},
			{{0, 0, m32, 0}},
		} };

		HW = half_width;
		HH = half_height;

		to_screen_matrix = { {
			{{HW, 0, 0, 0}},
			{{0, -HH, 0, 0}},
			{{0, 0, 1, 0}},
			{{HW, HH, 0, 1}},
} };
	
	}


};

#endif