#ifndef OBJECT3D_H
#define OBJECT3D_H

#include<iostream>
#include<vector>
#include<string>
#include<array>
#include"SDL.h"
#include"matrixTransformation.h"
#include"Camera.h"
#include"Projection.h"

class Object3d {
public:
	std::vector<std::array<float,4>> vertices;
	std::vector<std::vector<int>> faces;
	bool movement_flag;
	bool draw_vertices_flag;
	std::string label;
	std::array<std::array<float, 4>, 4> translation_matrix;
	//std::array<std::array<float, 4>, 4> rotation_matrix;
	Camera* cam;
	Projection* proj;
	std::vector<std::array<float, 4>> vvertices;
	

	Object3d(std::vector<std::array<float,4>> &v, std::vector<std::vector<int>>& f,Camera *c,Projection* p) {
		vertices = v;
		faces = f;
		movement_flag = true;
		draw_vertices_flag = false;
		cam = c;
		proj = p;
		label = "";

	}

	void set_matrix() {
		vvertices = matrixTransformation::matrixMultiply_nx4(vertices, cam->camera_matrix);
		vvertices = matrixTransformation::matrixMultiply_nx4(vvertices, proj->projection_matrix);
		matrixTransformation::normalize2dvec(vertices);
		matrixTransformation::normalize2dvec(vvertices);
		// vertices[(vertices > 2) | (vertices < -2)] = 0
		vvertices = matrixTransformation::matrixMultiply_nx4(vvertices, proj->to_screen_matrix);

	}

	void screen_projection(SDL_Renderer * renderer) {
	
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		std::cout << "drawing polygon" << std::endl;
		int sk = faces.size();
		
		for (int j = 0; j < sk; j++) {

			std::vector<int> index = faces[j];
			
			int s = index.size();
			
			for (int i = 0; i < s; i++) {
				if (i != (s - 1)) {
					int x1 = (int)(vvertices[index[i]][0] + 0.5);
					int y1 = (int)(vvertices[index[i]][1] + 0.5);
					int x2 = (int)(vvertices[index[i + 1]][0] + 0.5);
					int y2 = (int)(vvertices[index[i + 1]][1] + 0.5);
					//std::cout << x1 <<" " << y1 <<" " << x2<<" " << y2 << std::endl;
					SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
				
				}
				else {
					int x1 = (int)(vvertices[index[i]][0] + 0.5);
					int y1 = (int)(vvertices[index[i]][1] + 0.5);
					int x2 = (int)(vvertices[index[0]][0] + 0.5);
					int y2 = (int)(vvertices[index[0]][1] + 0.5);
					// std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
					SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
					//SDL_RenderPresent(renderer);
				}

			}
		}
		SDL_RenderPresent(renderer);
		printf("draw called");
		
	}

	void movement() {
		unsigned int ct = SDL_GetTicks();
		float getrm = (float)ct / 10000-(int)(ct/10000);
		if (movement_flag) {
			rotate_y(getrm);
		}

	}

	void draw(SDL_Renderer* renderer) {
		screen_projection(renderer);
		//movement();

	}
	

	void translate(float tx, float ty, float tz) {
		matrixTransformation::get_translation_matrix(translation_matrix, tx, ty, tz);
		vertices = matrixTransformation::matrixMultiply_nx4(vertices, translation_matrix);
	}

	void scale(float s) {
		matrixTransformation::scale(translation_matrix, s);
		vertices = matrixTransformation::matrixMultiply_nx4(vertices, translation_matrix);
	}

	void rotate_x(float angle) {
		matrixTransformation::get_rotation_x(translation_matrix, angle);
		vertices = matrixTransformation::matrixMultiply_nx4(vertices, translation_matrix);
	}

	void rotate_y(float angle) {
		matrixTransformation::get_rotation_y(translation_matrix, angle);
		vertices = matrixTransformation::matrixMultiply_nx4(vertices, translation_matrix);
	}

	void rotate_z(float angle) {
		matrixTransformation::get_rotation_z(translation_matrix, angle);
		vertices = matrixTransformation::matrixMultiply_nx4(vertices, translation_matrix);
	}



};

#endif
