#ifndef CAMERA_H
#define CAMERA_H
#define _USE_MATH_DEFINES

#include<iostream>
#include<vector>
#include<array>
#include<cmath>
#include"SDL.h"
#include"matrixTransformation.h"

class Camera {
public:
	std::array<float, 4> position;
	std::array<float, 4> forward;
	std::array<float, 4> up;
	std::array<float, 4> right;
	float h_fov;
	float v_fov;
	float near_plane;
	float far_plane;
	float moving_speed;
	float rotation_speed;
	std::array<std::array<float, 4>, 4> translation_matrix;
	std::array<std::array<float, 4>, 4> rotation_matrix;
	std::array<std::array<float, 4>, 4> camera_matrix;
	int height;
	int width;

	Camera(int render_Height,int render_Width,std::array<float, 3>pos) {
		position[0] = pos[0];
		position[1] = pos[1];
		position[2] = pos[2];
		position[3] = 1.0f;
		height = render_Height;
		width = render_Width;
		initialize();
	}

	void control(SDL_Keysym& event) {
		
		
			switch (event.sym) {
				std::cout << "event detected" << event.sym<< std::endl;

			case SDLK_a:
				matrixTransformation::scalar_multiply(right, moving_speed);
				matrixTransformation::vec_subtract(position, right);
				std::cout << "event detected a" << std::endl;
				break;
			case SDLK_d:
				matrixTransformation::scalar_multiply(right, moving_speed);
				matrixTransformation::vec_add(position, right);
				std::cout << "event detected d" << std::endl;
				break;
			case SDLK_w:
				matrixTransformation::scalar_multiply(forward, moving_speed);
				matrixTransformation::vec_add(position, forward);
				std::cout << "event detected w " << std::endl;
				break;
			case SDLK_s:
				matrixTransformation::scalar_multiply(forward, moving_speed);
				matrixTransformation::vec_subtract(position, forward);
				std::cout << "event detected s" << std::endl;
				break;
			case SDLK_q:
				matrixTransformation::scalar_multiply(up, moving_speed);
				matrixTransformation::vec_add(position,up);
				std::cout << "event detected q" << std::endl;
				break;
			case SDLK_e:
				matrixTransformation::scalar_multiply(up, moving_speed);
				matrixTransformation::vec_subtract(position,up);
				std::cout << "event detected e" << std::endl;
				break;
			default:
				std::cout << "event detected default" << event.sym << std::endl;
				break;

			}
			if (event.sym == SDLK_LEFT) {
				std::cout << "event detected default left key" << std::endl;
				camera_yaw(-1 * rotation_speed);
			}
			if (event.sym == SDLK_RIGHT) {
				camera_yaw( rotation_speed);
			}
			if (event.sym == SDLK_UP) {
				camera_pitch(-rotation_speed);
			}
			if (event.sym == SDLK_DOWN) {
				camera_pitch(rotation_speed);
			}
		
	}

	void create_translate_matrix() {
		translation_matrix = { {
			{{1,0,0,0}},
			{{0,1,0,0}},
			{{0,0,1,0}},
			{{-position[0],-position[1],-position[2],1}}
		} };
		//matrixTransformation::display(translation_matrix);

	}

	void create_rotation_matrix() {
		rotation_matrix = { {
			{{right[0],up[0],forward[0],0}},
			{{right[1],up[1],forward[1],0}},
			{{right[2],up[2],forward[2],0}},
			{{0,0,0,1}}

		} };
		//matrixTransformation::display(rotation_matrix);
	}

	void create_camera_matrix() {
		matrixTransformation::matrixMultiply_4x4(translation_matrix, rotation_matrix, camera_matrix);
		matrixTransformation::display(camera_matrix);
	}

	void create_all_matrix() {
		create_translate_matrix();
		create_rotation_matrix();
		create_camera_matrix();
	}

	void camera_pitch(float angle) {
		std::array<std::array<float, 4>, 4> rotate_x;
		matrixTransformation::get_rotation_x(rotate_x, angle);
		forward = matrixTransformation::multiply1x4(forward, rotate_x);
		right = matrixTransformation::multiply1x4(right, rotate_x);
		up = matrixTransformation::multiply1x4(up, rotate_x);
	}

	void camera_yaw(float angle) {
		std::array<std::array<float, 4>, 4> rotate_y;
		matrixTransformation::get_rotation_y(rotate_y, angle);
		forward = matrixTransformation::multiply1x4(forward, rotate_y);
		right = matrixTransformation::multiply1x4(right, rotate_y);
		up = matrixTransformation::multiply1x4(up, rotate_y);
	}

protected:
	void initialize() {
		forward = { {0, 0, 1, 1} };
		up = { {0,1,0,1} };
		right = { {1,0,0,1} };
		h_fov =  M_PI/ 3;
		v_fov = h_fov * (float) (height/width);
		near_plane = 0.1f;
		far_plane = 100.0f;
		moving_speed = 0.3f;
		rotation_speed = 0.015f;

	}
	
};







#endif