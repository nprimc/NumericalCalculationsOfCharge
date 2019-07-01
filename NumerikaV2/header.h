#pragma once

const double fourPiEpsilon = 1.112123e-10;

struct face;

float getArea(float *v1, float *v2, float *v3);

struct face* addFront(struct face* list, int index,float vertices[][3], int faces[][3]);

void insertBehind(struct face **list, int index, float vertices[][3], int faces[][3]);

float totalArea (struct face *firstFace);

void listToArray (struct face *firstFace, float data[][4], int numElements);

void getCenter(float v1[], float v2[], float v3[], float center[]);

void print2DArray (float array[][4], int numElements);

void checkTriangles(struct face *firstFace, float maxArea, int *elCounter);
