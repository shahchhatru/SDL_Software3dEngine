#include<iostream>
#include"SDL.h"
#undef main
#include"Camera.h"
#include"Projection.h"
#include"Object3d.h"
#include"ObjReader.h"
#include"SoftwareRenderer.h"


int main() {
	
	SoftwareRender* soft = new SoftwareRender();
	soft->init();

}