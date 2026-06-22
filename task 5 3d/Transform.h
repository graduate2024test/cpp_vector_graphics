#pragma once

#include "Matrix.h"
#include <math.h>

mat3 translate(float Tx, float Ty) {

	mat3 *res = new mat3(1.f);
	(*res)[0][2] = Tx;
	(*res)[1][2] = Ty;
	return *res;
}

mat3 scale(float Sx, float Sy) {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = Sx;
	(*res)[1][1] = Sy;
	return *res;
}

mat3 scale(float S) {

	return scale(S, S);
}

mat3 rotate(float theta) {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = (*res)[1][1] = (float)cos(theta);
	(*res)[0][1] = (float)sin(theta);
	(*res)[1][0] = -(*res)[0][1];
	return *res;
}

mat3 mirrorY() {

	const float PI = acos(-1.0);

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = -(float)sin(PI / 2.f);
	(*res)[1][1] = (float)sin(PI / 2.f);
	(*res)[0][1] = (float)cos(PI / 2.f);
	(*res)[1][0] = (float)cos(PI / 2.f);
	return *res;
}

mat3 mirrorX() {

	const float PI = acos(-1.0);

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = (float)sin(PI / 2.f);
	(*res)[1][1] = -(float)sin(PI / 2.f);
	(*res)[0][1] = (float)cos(PI / 2.f);
	(*res)[1][0] = (float)cos(PI / 2.f);
	return *res;
}

mat3 scaleH() {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = 1.1f;
	(*res)[1][1] = 1.1f;
	(*res)[0][1] = 0.f;
	(*res)[1][0] = 0.f;
	return *res;
}

mat3 scaleL() {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = 0.9f;
	(*res)[1][1] = 0.9f;
	(*res)[0][1] = 0.f;
	(*res)[1][0] = 0.f;
	return *res;
}

mat3 scaleXH() {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = 1.1f;
	(*res)[1][1] = 1.f;
	(*res)[0][1] = 0.f;
	(*res)[1][0] = 0.f;
	return *res;
}

mat3 scaleXL() {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = 0.9f;
	(*res)[1][1] = 1.f;
	(*res)[0][1] = 0.f;
	(*res)[1][0] = 0.f;
	return *res;
}

mat3 scaleYH() {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = 1.f;
	(*res)[1][1] = 1.1f;
	(*res)[0][1] = 0.f;
	(*res)[1][0] = 0.f;
	return *res;
}

mat3 scaleYL() {

	mat3 *res = new mat3(1.f);
	(*res)[0][0] = 1.f;
	(*res)[1][1] = 0.9f;
	(*res)[0][1] = 0.f;
	(*res)[1][0] = 0.f;
	return *res;
}

mat4 translate(float Tx, float Ty, float Tz) {
	mat4 *res = new mat4(1.f);
	(*res)[0][3] = Tx;
	(*res)[1][3] = Ty;
	(*res)[2][3] = Tz;
	return *res;
}

mat4 scale(float Sx, float Sy, float Sz) {
	mat4(*res) = new mat4(1.f);
	(*res)[0][0] = Sx;
	(*res)[1][1] = Sy;
	(*res)[2][2] = Sz;
	return *res;
}