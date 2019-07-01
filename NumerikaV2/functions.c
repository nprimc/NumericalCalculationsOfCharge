#include "header.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float getArea(float *v1, float *v2, float *v3){ //calculates area of a triangle using Heron's formula
    float a = sqrt((v2[0]-v1[0])*(v2[0]-v1[0])+(v2[1]-v1[1])*(v2[1]-v1[1])+(v2[2]-v1[2])*(v2[2]-v1[2]));
    float b = sqrt((v3[0]-v2[0])*(v3[0]-v2[0])+(v3[1]-v2[1])*(v3[1]-v2[1])+(v3[2]-v2[2])*(v3[2]-v2[2]));
    float c = sqrt((v3[0]-v1[0])*(v3[0]-v1[0])+(v3[1]-v1[1])*(v3[1]-v1[1])+(v3[2]-v1[2])*(v3[2]-v1[2]));
    float s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ###LINKED LIST###
/////////////////////////////////////////////////////////////////////////////////////////////////////////

struct face {
    float vertex1[3];
    float vertex2[3];
    float vertex3[3];
    float area;
    float center[3];
    struct face *next;
};


struct face addNext (struct face *currentFace, int index, float vertices[][3], int faces[][3]){
    struct face *newFace = malloc(sizeof(struct face));
    if (newFace == NULL){
        printf("Memory error!");
        exit(3);
    }
    //member definitions

    newFace->vertex1[0] = vertices[faces[index][0]][0]; //X
    newFace->vertex1[1] = vertices[faces[index][0]][1]; //Y
    newFace->vertex1[2] = vertices[faces[index][0]][2]; //Z of vertex 1

    newFace->vertex2[0] = vertices[faces[index][1]][0];
    newFace->vertex2[1] = vertices[faces[index][1]][1];
    newFace->vertex2[2] = vertices[faces[index][1]][2];

    newFace->vertex3[0] = vertices[faces[index][2]][0];
    newFace->vertex3[1] = vertices[faces[index][2]][1];
    newFace->vertex3[2] = vertices[faces[index][2]][2];

    newFace->area = getArea(newFace->vertex1, newFace->vertex2, newFace->vertex3);


    newFace->next = currentFace->next;
    currentFace->next = newFace;
};

