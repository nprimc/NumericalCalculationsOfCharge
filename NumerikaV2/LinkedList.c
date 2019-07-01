#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct face {
    float vertex1[3];
    float vertex2[3];
    float vertex3[3];
    float area;
    float center[3];
    struct face *next;
};

float getArea(float v1[], float v2[], float v3[]){ //calculates area of a triangle using Heron's formula
    //printf("A: %f %f %f\n", v1[0], v1[1], v1[2]);
    //printf("B: %f %f %f\n", v2[0], v2[1], v2[2]);
    //printf("C: %f %f %f\n", v3[0], v3[1], v3[2]);
    float a = sqrt(pow((v2[0]-v1[0]), 2)+pow((v2[1]-v1[1]), 2)+pow((v2[2]-v1[2]),2));
    float b = sqrt((v3[0]-v2[0])*(v3[0]-v2[0])+(v3[1]-v2[1])*(v3[1]-v2[1])+(v3[2]-v2[2])*(v3[2]-v2[2]));
    float c = sqrt((v3[0]-v1[0])*(v3[0]-v1[0])+(v3[1]-v1[1])*(v3[1]-v1[1])+(v3[2]-v1[2])*(v3[2]-v1[2]));
    float s = (a+b+c)/2;
    return sqrt(s*(s-a)*(s-b)*(s-c));
};

void getCenter(float v1[], float v2[], float v3[], float center[]){
    /*float vectAB[3], vect[3]; //[x, y, z]
    vectAB[0] = v2[0]-v1[0];
    vectAB[1] = v2[1]-v1[1];
    vectAB[2] = v2[2]-v1[2];
    vect[0] = v1[0] - v3[0] + vectAB[0]/2;
    vect[1] = v1[1] - v3[1] + vectAB[1]/2;
    vect[2] = v1[2] - v3[2] + vectAB[2]/2;
    center[0] = v3[0] + vect[0]/3;
    center[1] = v3[1] + vect[1]/3;
    center[2] = v3[2] + vect[2]/3;

    */
    center[0] = (v1[0]+v2[0]+v3[0])/3;
    center[1] = (v1[1]+v2[1]+v3[1])/3;
    center[2] = (v1[2]+v2[2]+v3[2])/3;
};


struct face* addFront(struct face* list, int index,float vertices[][3], int faces[][3]){ //arguments: Pointer to the currently first node of LL, data to be written in new node
    struct face* newFace = malloc(sizeof(struct face));                  //memory allocation
    if (newFace == NULL){
        printf("Memory error");
        exit(3);
    }
    newFace->vertex1[0] = vertices[faces[index][0]-1][0]; //X
    newFace->vertex1[1] = vertices[faces[index][0]-1][1]; //Y
    newFace->vertex1[2] = vertices[faces[index][0]-1][2]; //Z of vertex 1

    newFace->vertex2[0] = vertices[faces[index][1]-1][0];
    newFace->vertex2[1] = vertices[faces[index][1]-1][1];
    newFace->vertex2[2] = vertices[faces[index][1]-1][2];

    newFace->vertex3[0] = vertices[faces[index][2]-1][0];
    newFace->vertex3[1] = vertices[faces[index][2]-1][1];
    newFace->vertex3[2] = vertices[faces[index][2]-1][2];

    newFace->area = getArea(newFace->vertex1, newFace->vertex2, newFace->vertex3);

    float cent[3]= {0};
    getCenter(newFace->vertex1, newFace->vertex2, newFace->vertex3, cent);
    newFace->center[0] = cent[0];
    newFace->center[1] = cent[1];
    newFace->center[2] = cent[2];

    newFace->next = list;       //pointing next of newly added node to the previously first node
    return newFace;             //returning a pointer to new node
};

void addBehind(struct face *current, float A[3], float B[3], float C[3]){
    struct face *newFace = malloc(sizeof(struct face));
        if (newFace == NULL){
        printf("Memory error");
        exit(3);
    }
    newFace->vertex1[0] = A[0];
    newFace->vertex1[1] = A[1];
    newFace->vertex1[2] = A[2];

    newFace->vertex2[0] = B[0];
    newFace->vertex2[1] = B[1];
    newFace->vertex2[2] = B[2];

    newFace->vertex3[0] = C[0];
    newFace->vertex3[1] = C[1];
    newFace->vertex3[2] = C[2];

    newFace->area = getArea(newFace->vertex1, newFace->vertex2, newFace->vertex3);

    float cent[3]= {0};
    getCenter(newFace->vertex1, newFace->vertex2, newFace->vertex3, cent);
    newFace->center[0] = cent[0];
    newFace->center[1] = cent[1];
    newFace->center[2] = cent[2];

    newFace->next = current->next;
    current->next = newFace;
}

void insertBehind(struct face **list, int index, float vertices[][3], int faces[][3]){ //as we pass the function a pointer to list, the first argument must be the address of list
    struct face* newFace = malloc(sizeof(struct face));
    if (newFace == NULL){
        printf("Memory error");
        exit(3);
    }
    newFace->vertex1[0] = vertices[faces[index][0]-1][0]; //X
    newFace->vertex1[1] = vertices[faces[index][0]-1][1]; //Y
    newFace->vertex1[2] = vertices[faces[index][0]-1][2]; //Z of vertex 1

    newFace->vertex2[0] = vertices[faces[index][1]-1][0];
    newFace->vertex2[1] = vertices[faces[index][1]-1][1];
    newFace->vertex2[2] = vertices[faces[index][1]-1][2];

    newFace->vertex3[0] = vertices[faces[index][2]-1][0];
    newFace->vertex3[1] = vertices[faces[index][2]-1][1];
    newFace->vertex3[2] = vertices[faces[index][2]-1][2];

    newFace->area = getArea(newFace->vertex1, newFace->vertex2, newFace->vertex3);

    float cent[3]= {0};
    getCenter(newFace->vertex1, newFace->vertex2, newFace->vertex3, cent);
    newFace->center[0] = cent[0];
    newFace->center[1] = cent[1];
    newFace->center[2] = cent[2];

    newFace->next = (*list)->next;
    (**list).next = newFace;
};

void printList(struct face *firstFace){
    struct face *p;
    p = firstFace;
    printf("Printing list: \n");
    while (p != NULL){
        printf("A: %f, %f, %f\n", p->vertex1[0], p->vertex1[1], p->vertex1[2]);
        printf("B: %f, %f, %f\n", p->vertex2[0], p->vertex2[1], p->vertex2[2]);
        printf("C: %f, %f, %f\n", p->vertex3[0], p->vertex3[1], p->vertex3[2]);
        printf("sredisce: %f, %f, %f\n", p->center[0], p->center[1], p->center[2]);
        printf("povrsina: %f\n\n\n", p->area);
        p = p->next;
    }
}

float totalArea (struct face *firstFace){
    struct face *p;
    p = firstFace;
    float area = 0;
    while (p != NULL){
        area = area + p->area;
        p = p->next;
    }
    return area;
}

void checkTriangles(struct face *firstFace, float maxArea, int *elCounter){
    struct face *p;
    p = firstFace;
    while (p != NULL){
        triangleResized:
        //printf("%f\n", p->area);
        if ((p->area) > maxArea){ //if the current face is bigger than expected, find the longest edge and divide it in two, create two faces
            float str12, str23, str31;
            //str12, str23 and str31 are edge lengths
            str12 = sqrt(pow((p->vertex1[0])-(p->vertex2[0]), 2)+pow((p->vertex1[1])-(p->vertex2[1]), 2)+pow((p->vertex1[2])-(p->vertex2[2]), 2));
            str23 = sqrt(pow((p->vertex2[0])-(p->vertex3[0]), 2)+pow((p->vertex2[1])-(p->vertex3[1]), 2)+pow((p->vertex2[2])-(p->vertex3[2]), 2));
            str31 = sqrt(pow((p->vertex1[0])-(p->vertex3[0]), 2)+pow((p->vertex1[1])-(p->vertex3[1]), 2)+pow((p->vertex1[2])-(p->vertex3[2]), 2));
            //printf("a = %f, b = %f, c = %f\n", str12, str23, str31);
            if(str12>=str23 && str12>=str31){ //str12 is the longest, get center and then change current face and addBehind another
                //Getting center, str12 is the edge between vertex1 and vertex2
                float center[3];
                float vect12[3]; //edge as a vector, from vertex1 to vertex2
                vect12[0] = (p->vertex2[0])-(p->vertex1[0]); //x
                vect12[1] = (p->vertex2[1])-(p->vertex1[1]);
                vect12[2] = (p->vertex2[2])-(p->vertex1[2]);

                center[0] = (p->vertex1[0]) + vect12[0]/2;
                center[1] = (p->vertex1[1]) + vect12[1]/2;
                center[2] = (p->vertex1[2]) + vect12[2]/2;

                //printf("1 Cx = %f, Cy = %f, Cz = %f\n", center[0], center[1], center[2]);

                //we need to add another face, just behind the current one
                addBehind(p, center, p->vertex2, p->vertex3);
                (*elCounter)++;

                //vertecis of the new triangle are: vertex1, vertex3 and center (we have to change vertex2)
                (p->vertex2[0]) = center[0];
                (p->vertex2[1]) = center[1];
                (p->vertex2[2]) = center[2];
                p->area = getArea(p->vertex1, p->vertex2, p->vertex3);
                getCenter(p->vertex1, p->vertex2, p->vertex3,p->center);
                goto triangleResized;
            }
            if(str23>=str12 && str23>=str31){
                //Getting center, str23 is the edge between vertex2 and vertex3
                float center[3];
                float vect23[3]; //edge as a vector, from vertex2 to vertex3
                vect23[0] = (p->vertex3[0])-(p->vertex2[0]); //x
                vect23[1] = (p->vertex3[1])-(p->vertex2[1]);
                vect23[2] = (p->vertex3[2])-(p->vertex2[2]);

                center[0] = (p->vertex2[0]) + vect23[0]/2;
                center[1] = (p->vertex2[1]) + vect23[1]/2;
                center[2] = (p->vertex2[2]) + vect23[2]/2;

                //printf("2 Cx = %f, Cy = %f, Cz = %f\n", center[0], center[1], center[2]);

                //we need to add another face, just behind the current one
                addBehind(p, center, p->vertex3, p->vertex1);
                (*elCounter)++;

                //vertecis of the new triangle are: vertex1, vertex2 and center (we have to change vertex3)
                (p->vertex3[0]) = center[0];
                (p->vertex3[1]) = center[1];
                (p->vertex3[2]) = center[2];
                p->area = getArea(p->vertex1, p->vertex2, p->vertex3);
                getCenter(p->vertex1, p->vertex2, p->vertex3, p->center);
                goto triangleResized;
            }
            if(str31>=str23 && str31>=str12){
                //Getting center, str31 is the edge between vertex3 and vertex1
                float center[3];
                float vect31[3]; //edge as a vector, from vertex3 to vertex1
                vect31[0] = (p->vertex1[0])-(p->vertex3[0]); //x
                vect31[1] = (p->vertex1[1])-(p->vertex3[1]);
                vect31[2] = (p->vertex1[2])-(p->vertex3[2]);

                center[0] = (p->vertex3[0]) + vect31[0]/2;
                center[1] = (p->vertex3[1]) + vect31[1]/2;
                center[2] = (p->vertex3[2]) + vect31[2]/2;

                //printf("3 Cx = %f, Cy = %f, Cz = %f\n", center[0], center[1], center[2]);

                //we need to add another face, just behind the current one
                addBehind(p, center, p->vertex1, p->vertex2);
                (*elCounter)++;

                //vertecis of the new triangle are: vertex2, vertex3 and center (we have to change vertex1)
                (p->vertex1[0]) = center[0];
                (p->vertex1[1]) = center[1];
                (p->vertex1[2]) = center[2];
                p->area = getArea(p->vertex1, p->vertex2, p->vertex3);
                getCenter(p->vertex1, p->vertex2, p->vertex3, p->center);
                goto triangleResized;

            }

        }
        p = p->next;
    }


}

void print2DArray (float array[][4], int numElements){
    for(int i=0; i<numElements; i++){
        printf("Center at coordinates: %f, %f, %f\n", array[i][0], array[i][1], array[i][2]);
        printf("Area: %f\n", array[i][3]);
    }
    printf("End of array, number of elements: %d\n\n", numElements);
}

void listToArray (struct face *firstFace, float data[][4], int numElements){ //pointer to the first face element in a list, a prepared array (for data)
                                                                            //number of face elements in a list
    //////////////////////////////////////////////
    // DATA STRUCTURE:
    //      data = [[X0center, Y0center, Z0center, area0],[X1center, Y1center, Z1center, area],[X2center, Y2center, Z2center, area]...]
    //
    //      centers of faces are used for acquiring the required informations about distances among face elements
    //      area is used to get the surface density
    //////////////////////////////////////////////

    struct face *p;
    p = firstFace;
    for (int i = 0; i<numElements; i++){

        data[i][0] = p->center[0];
        data[i][1] = p->center[1];
        data[i][2] = p->center[2];
        data[i][3] = p->area;
        printf("area: %f\n", p->area);
        if(p->next == NULL){
            printf("Warning! Number of elements\n");
            break;
        }
        p = p->next;
    }
}





