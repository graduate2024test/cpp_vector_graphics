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

//**********************************************************************
//**********************************************************************
//**********************************************************************
/*
mat4 rotate(float theta, vec3 n) {

	//поворот - формула Родрига

	float q0 = cos(theta / 2.f);
	//вокруг оси Ox d(1,0,0)
	//вокруг оси Oy d(0,1,0)
	//вокруг оси Oz d(0,0,1)
	//n - направляющий вектор произвольной длины отличный от нуля (нормализация - деление на длину - единичный)
	//theta - угол вращения
	
	// q = q0 * e , где q - вектор, e - единичный вектор напраления, q0 - косинус угла поворота
	//вычислени модуля - длины вектра, получение единичного вектора
	float mod_n = sqrt(n.x * n.x + n.y * n.y + n.z * n.z);
	//координаты вектора q в разложении по неподвижным осям
	float q1 = q0 * (n.x / mod_n);//1//координата x
	float q2 = q0 * (n.y / mod_n);//0//координата y
	float q3 = q0 * (n.z / mod_n);//0//координата z

	//компоненты оператора поворота
	float	r11 = 2.f * (q0 * q0 + q1 * q1) - 1,	r12 = 2.f * (q1 * q2 - q0 * q3),		r13 = 2.f * (q1 * q3 + q0 * q2);
	float	r21 = 2.f * (q1 * q2 + q0 * q3),		r22 = 2.f * (q0 * q0 + q2 * q2) - 1,	r23 = 2.f * (q2 * q3 - q0 * q1);
	float	r31 = 2.f * (q1 * q3 - q0 * q2),		r32 = 2.f * (q2 * q3 + q0 * q1),		r33 = 2.f * (q0 * q0 + q3 * q3) - 1;

	//матрица оператора поворота
	mat4(*res) = new mat4(1.f);
	(*res)[0][0] = r11;	(*res)[0][1] = r12;	(*res)[0][2] = r13;
	(*res)[1][0] = r21;	(*res)[1][1] = r22;	(*res)[1][2] = r23;
	(*res)[2][0] = r31;	(*res)[2][1] = r32;	(*res)[2][2] = r33;
		
	return (*res);
}*/

mat4 rotate(float theta, vec3 k) {

	float kx = k.x, ky = k.y, kz = k.z;
	float cosinus = cos(theta), sinus = sin(theta);
	
	mat4 res = mat4(1.0f);
	
	res.row1.x = cosinus + (1 - cosinus)*kx*kx;
	res.row1.y = -sinus * kz + (1 - cosinus)*kx*ky;
	res.row1.z = sinus * ky + (1 - cosinus)*kx*kz;

	res.row2.x = sinus * kz + (1 - cosinus)*ky*kx;
	res.row2.y = cosinus + (1 - cosinus)*ky*ky;
	res.row2.z = -sinus * kx + (1 - cosinus)*ky*kz;

	res.row3.x = -sinus * ky + (1 - cosinus)*kz*kx;
	res.row3.y = sinus * kx + (1 - cosinus)*kz*ky;
	res.row3.z = cosinus + (1 - cosinus)*kz*kz;
	
	return res;
}


mat4 rotateP(float theta, vec3 n, vec3 P) {
	return translate(P.x, P.y, P.z) *
		(rotate(theta, n) * translate(-P.x, -P.y, -P.z));
}





mat4 lookAt(vec3 position, vec3 target, vec3 worldUp) {


	// 1. Position = known
	// 2. Calculate cameraDirection
	vec3 zaxis = norm(position - target);//e3
	// 3. Get positive right axis vector
	vec3 xaxis = norm(cross(norm(worldUp), zaxis));//e1
	// 4. Calculate camera up vector
	vec3 yaxis = cross(zaxis, xaxis);//e2

	// Create translation and rotation matrix
	// In glm we access elements as mat[col][row] due to column-major layout
	mat4 translation = mat4(1.0f); // Identity matrix by default
	translation[0][3] = -position.x; // Third column, first row
	translation[1][3] = -position.y;
	translation[2][3] = -position.z;
	mat4 rotation = mat4(1.0f);
	rotation.row1.x = xaxis.x; // First column, first row
	rotation.row1.y = xaxis.y;
	rotation.row1.z = xaxis.z;
	rotation.row2.x = yaxis.x; // First column, second row
	rotation.row2.y = yaxis.y;
	rotation.row2.z = yaxis.z;
	rotation.row3.x = zaxis.x; // First column, third row
	rotation.row3.y = zaxis.y;
	rotation.row3.z = zaxis.z;

	// Return lookAt matrix as combination of translation and rotation matrix
	return rotation * translation; // Remember to read from right to left (first translation then rotation)
}




//матрица прямоугольной проекции
mat4 ortho(float l, float r, float b, float t, float zn, float zf) {
	return mat4(vec4(2.f / (r - l), 0.f, 0.f, -(r + l) / (r - l)),
				vec4(0.f, 2.f / (t - b), 0.f, -(t + b) / (t - b)),
				vec4(0.f, 0.f, -2.f / (zf - zn), -(zf + zn) / (zf - zn)),//-2 на -2.f заменил
				vec4(0.f, 0.f, 0.f, 1.f));
}

//
//матрицы перспективной проекции
mat4 frustum(float l, float r, float b, float t, float n, float f) {
	return mat4(vec4(2.f*n / (r - l), 0.f, (r + l) / (r - l), 0.f),
				vec4(0.f, 2.f*n / (t - b), (t + b) / (t - b), 0.f),
				vec4(0.f, 0.f, -(f + n) / (f - n), -2.f*f*n / (f - n)),
				vec4(0.f, 0.f, -1.f, 0.f));
}

mat4 perspective(float fovy, float aspect, float n, float f) {
	return mat4(vec4((1.f / tan(fovy / 2.f)) / aspect, 0.f, 0.f, 0.f),
				vec4(0.f, 1.f / tan(fovy / 2.f), 0.f, 0.f),
				vec4(0.f, 0.f, -(f + n) / (f - n), -2.f*f*n / (f - n)),
				vec4(0.f, 0.f, -1.f, 0.f));
}

//преобразование кадрирования
mat3 cadrRL(vec2 Vc, vec2 V, vec2 Wc, vec2 W) {
	return translate(Wc.x, Wc.y) *
		(scale(W.x / V.x, -W.y / V.y) * translate(-Vc.x, -Vc.y));
}



















