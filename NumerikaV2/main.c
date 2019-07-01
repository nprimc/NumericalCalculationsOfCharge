#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <math.h>

#define INIT_NUM_VERTICES 100
#define INIT_NUM_FACES 100

#define ITERATIONS 0
#define POTENTIAL 100

#define RED 0
#define GREEN 1
#define BLUE 2

#define OUT_FILE "output.txt"

int main()
{
    char data[80*sizeof(char)]; //string used for reading in input parsing
    char comment[80*sizeof(char)]; //used for printing comments in input parsing
    int numberOfVertices = 0;
    float (*locations)[3] = malloc(sizeof(*locations)*INIT_NUM_VERTICES); //declaring a 2D array for locations of vertices
    int currentLocationsSize = INIT_NUM_VERTICES;

    int (*faces)[3] = malloc(sizeof(*faces)*INIT_NUM_FACES);
    int currentFacesSize = INIT_NUM_FACES;
    int numberOfFaces = 0;


    int *dump;


    FILE *txtfile;  //declaring a pointer (FILE type)

    char promptFile[50];
    printf("Enter file name: ");
    scanf("%s", &promptFile);

    //txtfile = fopen("C:\\Users\\np9659\\Desktop\\naPapir.obj", "r");
    txtfile = fopen(promptFile, "r");

    if (txtfile == NULL){
        printf("Error opening file!");
        exit(1);
    }
    else{
        printf("Opening file... \n");
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    //  ####INPUT PARSING### //
    /////////////////////////////////////////////////////////////////////////////////////////////////////////



    while(fgets(data, 80, txtfile) != NULL){ //reading file, line by line (reads in data until n-1 (79)) bytes are read, or an EOF is reached)
        if (sscanf(data, "# %79[^\n]", &comment)) printf("%s\n\n", comment);

        else if(sscanf(data, "v %f %f %f", &locations[numberOfVertices][0], &locations[numberOfVertices][1], &locations[numberOfVertices][2]) == 3){
            //printf("Input parsing: %f %f %f\n", locations[numberOfVertices][0], locations[numberOfVertices][1], locations[numberOfVertices][2]);
            //REALLOC--if locations gets out of space, reallocate with more space(+free the existing space) #tick
            if (numberOfVertices >= currentLocationsSize-1){

                    //Dynamic allocation of memory, adding space for a defined number of elements
                float (*newLocations)[3] = realloc(locations, sizeof(float)*(currentLocationsSize + INIT_NUM_VERTICES)*3);
                if (newLocations == NULL){
                    printf("Error reallocating memory for vertices!");
                    exit(3);
                }
                currentLocationsSize += INIT_NUM_VERTICES;
                locations = newLocations;
                printf("Locations array reallocated, current size: %d\n", currentLocationsSize);

            }
            numberOfVertices++;
        }
        else{
            if (sscanf(data, "v %f %f %f %f", &locations[numberOfVertices][0], &locations[numberOfVertices][1], &locations[numberOfVertices][2], &dump)){
                printf("Curves not supported, weight value on vertex line (other data is fine): %d", numberOfVertices);
                numberOfVertices++;
            }
            else if(sscanf(data, "f %d %d %d", &faces[numberOfFaces][0], &faces[numberOfFaces][1], &faces[numberOfFaces][2])==3){
                numberOfFaces++;
            }
            else if(sscanf(data, "f %d/%d/%d %d/%d/%d %d/%d/%d", &faces[numberOfFaces][0], &dump, &dump, &faces[numberOfFaces][1], &dump, &dump, &faces[numberOfFaces][2], &dump, &dump)==9){
            numberOfFaces++;
            }
            else if(sscanf(data, "f %d/%d %d/%d %d/%d", &faces[numberOfFaces][0], &dump, &faces[numberOfFaces][1], &dump, &faces[numberOfFaces][2], &dump)==6){
            numberOfFaces++;
            }
            else if(sscanf(data, "f %d//%d %d//%d %d//%d", &faces[numberOfFaces][0], &dump, &faces[numberOfFaces][1], &dump, &faces[numberOfFaces][2], &dump)==6){
            numberOfFaces++;
            }
            else{
                if(sscanf(data, "f %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &dump, &dump, &dump, &dump, &dump, &dump, &dump, &dump, &dump)==12){
                    printf("Four sided elements not supported");
                    exit(2);
                }
                if(sscanf(data, "f %d/%d/ %d/%d/ %d/%d/ %d/%d/", &dump, &dump, &dump, &dump, &dump, &dump)==8){
                    printf("Four sided elements not supported");
                    exit(2);
                }
                if(sscanf(data, "f %d//%d %d//%d %d//%d %d//%d", &dump, &dump, &dump, &dump, &dump, &dump)==8){
                    printf("Four sided elements not supported");
                    exit(2);
                }
            }
            //REALLOC--if faces gets out of space, reallocate with more space(+free the existing space) #tick
            if (numberOfFaces >= currentFacesSize-1){

                    //Dynamic allocation of memory, adding space for a defined number of elements
                float (*newFaces)[3] = realloc(faces, sizeof(int)*(currentFacesSize + INIT_NUM_FACES)*3);
                if (newFaces == NULL){
                    printf("Error reallocating memory for faces!");
                    exit(3);
                }
                currentFacesSize += INIT_NUM_FACES;
                faces = newFaces;
                printf("Faces array reallocated, current size: %d\n", currentFacesSize);

            }
        }

    }
    printf("\nNumber of vertices (int numberOfVertices): %d\n", numberOfVertices);
    printf("\nNumber of faces (int numberOfFaces): %d\n", numberOfFaces);

    fclose(txtfile);

        //printing the structured data
        /*
    for (int i = 0; i<numberOfFaces; i++){
        printf("face No%d: %d %d %d\n",i , faces[i][0], faces[i][1], faces[i][2]);
    }
*/
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ###All of the polygonal data is in arrays###
    /////////////////////////////////////////////////////////////////////////////////////////////////////////


    struct face *firstEl = NULL;

    for (int i = 0; i < numberOfFaces; i++){
        firstEl = addFront(firstEl, i, locations, faces); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    }

    //printList(firstEl); //printing the whole list
    float areaOfObject;
    areaOfObject = totalArea(firstEl);
    printf("Total area: %f\n", areaOfObject);

    printf("Area of whole object is %f, avg = %f, number of faces = %d\n", areaOfObject, areaOfObject/numberOfFaces, numberOfFaces);
    printf("Do you want to resize the faces? (0-No, 1-Yes): ");
    int faceDiv;
    scanf("%d", &faceDiv);
    if (faceDiv){
        float maxS;
        printf("Insert max area: \n");
        scanf("%f", &maxS);
        checkTriangles(firstEl, maxS, &numberOfFaces);
        printf("\n\n New Number of faces= %d, avg = %f\n", numberOfFaces, areaOfObject/numberOfFaces);
        //printList(firstEl);
    }

    float coordinatesAndArea[numberOfFaces][4]; //final array
    listToArray(firstEl, coordinatesAndArea, numberOfFaces);

    // Printing the data for matlab calculations
             //array with correct data structure
/*
    float area, coefitient, distance;
    float xj, yj, zj, xi, yi, zi;

    printf("[");
    for (int j=0; j<numberOfFaces-2; j++){
        printf("[");
        xj = coordinatesAndArea[j][0];
        yj = coordinatesAndArea[j][1];
        zj = coordinatesAndArea[j][2];


        for (int i=0; i<numberOfFaces-2; i++){
            if(i!=j){
                xi = coordinatesAndArea[i][0];
                yi = coordinatesAndArea[i][1];
                zi = coordinatesAndArea[i][2];
                area = coordinatesAndArea[i][3];

                distance  =  sqrt(pow(xi-xj, 2)+pow(yi-yj, 2)+pow(zi-zj, 2));
                coefitient = area/(fourPiEpsilon*distance);
                if(i<numberOfFaces-2) printf("%f, ", coefitient);
                else printf("%f", coefitient);
            }
            else{
                area = coordinatesAndArea[i][3];
                coefitient = 1.5937e10*sqrt(area);
                if(i<numberOfFaces-2) printf("%f, ", coefitient);
                else printf("%f", coefitient);
            }
        }
        printf("]\n");
    }
    printf("]\n");

    for (int xyz = 0; xyz < 3; xyz++){
        printf("[");
        for (int i = 0; i<numberOfFaces-1; i++){
            printf("%f ", coordinatesAndArea[i][xyz]);
        }
        printf("]\n\n");
    }
*/


    ////////////////////////////////////////////////////////
    //
    //      Gauss-Seidl Method
    //
    ////////////////////////////////////////////////////////

    double sigmas[numberOfFaces]; //creating an array for charge surface density

    for (int i = 0; i<numberOfFaces; i++){
        sigmas[i] = 0;
    }

    float xj, yj, zj, xi, yi, zi;
    double factor, dist;
    int iteration;

    for(iteration = 0; iteration < ITERATIONS; iteration++){
        printf("%d\n", iteration);
        for (int j = 0; j<numberOfFaces; j++){
            factor = 0;
            xj = coordinatesAndArea[j][0];
            yj = coordinatesAndArea[j][1];
            zj = coordinatesAndArea[j][2];

            for (int i = 0; i<numberOfFaces; i++){
                if(i != j){
                    xi = coordinatesAndArea[i][0];
                    yi = coordinatesAndArea[i][1];
                    zi = coordinatesAndArea[i][2];

                    dist =  sqrt(pow(xi-xj,2)+pow(yi-yj,2)+pow(zi-zj,2));
                    factor = factor + sigmas[i]*coordinatesAndArea[i][3]/dist;
                }
                else{

                }
            }
            sigmas[j] = (POTENTIAL*fourPiEpsilon - factor)/(2*sqrt(3.1415926535*coordinatesAndArea[j][3])); //izražen iz enaèbe za lastni prispevek
        }
        //printf("%e\n", sigmas[0]);
    }

    double charge = 0;

    printf("Printing sigmas: (%d iterations)\n", ITERATIONS);
    for(int n = 0; n<numberOfFaces; n++){
            printf("sigma no: %d = ", n);
            printf("%.12le\n", sigmas[n]);
            charge += sigmas[n];
    }
    printf("Charge = %e\n\n", charge);



    ////////////////////////////////////////////////////////
    //
    //      RGB colors for visualization
    //
    ////////////////////////////////////////////////////////

    float rgbValues[numberOfFaces][3];

    double maxSigma;
    double minSigma;
    minSigma  = maxSigma = sigmas[0];
    for (int i = 0; i<numberOfFaces; i++){
        if (sigmas[i]>maxSigma) maxSigma = sigmas[i];
        if (sigmas[i]<minSigma) minSigma = sigmas[i];
    }
    //printf("maxSigma = %e, minSigma = %e\n", maxSigma, minSigma);
    //maximum sigma is red, minimum sigma is blue, green is always zero


    for (int i = 0; i<numberOfFaces; i++){
        if(sigmas[i]>0){
            rgbValues[i][RED] = sigmas[i]/maxSigma;
            rgbValues[i][BLUE] = 0;
            rgbValues[i][GREEN] = 0;

            //printf("rgb = %e\n", sigmas[i]/maxSigma);
        }
        if(sigmas[i]<0){
            rgbValues[i][RED] = 0;
            rgbValues[i][BLUE] = sigmas[i]/minSigma;
            rgbValues[i][GREEN] = 0;
        }
    }



    ////////////////////////////////////////////////////////
    //
    //      Writing to a file //matlab plot3d
    //
    ////////////////////////////////////////////////////////


    FILE *outfile;

    outfile = fopen(OUT_FILE, "w");


    float area, coefitient, distance;

    fprintf(outfile, "K = [");
    for (int j=0; j<numberOfFaces; j++){
        fprintf(outfile, "[");
        xj = coordinatesAndArea[j][0];
        yj = coordinatesAndArea[j][1];
        zj = coordinatesAndArea[j][2];


        for (int i=0; i<numberOfFaces; i++){
            if(i!=j){
                xi = coordinatesAndArea[i][0];
                yi = coordinatesAndArea[i][1];
                zi = coordinatesAndArea[i][2];
                area = coordinatesAndArea[i][3];

                distance  =  sqrt(pow(xi-xj, 2)+pow(yi-yj, 2)+pow(zi-zj, 2));
                coefitient = area/(fourPiEpsilon*distance);
                fprintf(outfile, "%e ", coefitient);
            }
            else{
                area = coordinatesAndArea[i][3];
                coefitient = 3.1860041e10*sqrt(area);
                fprintf(outfile, "%e ", coefitient);
            }
        }
        fprintf(outfile, "]\n", coefitient);
    }
    fprintf(outfile, "]\n\n");

    fprintf(outfile, "V = [");
    for (int i = 0; i<numberOfFaces; i++){
        fprintf(outfile, "%d \n", POTENTIAL);
    }
    fprintf(outfile, "]\n\n");

    fprintf(outfile, "sigma = linsolve(K,V)\n\n");



    //Centers of triangles
    for (int xyz = 0; xyz < 3; xyz++){
        if (xyz == 0) fprintf(outfile, "X = [");
        if (xyz == 1) fprintf(outfile, "Y = [");
        if (xyz == 2) fprintf(outfile, "Z = [");
        for (int i = 0; i<numberOfFaces; i++){
            fprintf(outfile, "%f ", coordinatesAndArea[i][xyz]);
        }
        fprintf(outfile, "]\n\n");
    }

    //Sigmas

    fprintf(outfile, "sigmas = [");
    for (int i = 0; i<numberOfFaces; i++){
        fprintf(outfile, "%e\n", sigmas[i]);
    }
    fprintf(outfile, "]\n\n");

    //RGB values

    fprintf(outfile, "RGB = [");
    for (int i = 0; i<numberOfFaces; i++){
        fprintf(outfile, "%e %e %e; ", rgbValues[i][RED], rgbValues[i][GREEN], rgbValues[i][BLUE]);
        /*
        if(i == numberOfFaces-1){
            fprintf(outfile, "%e %e %e", rgbValues[i][RED], rgbValues[i][GREEN], rgbValues[i][BLUE]);
        }
        else{
            fprintf(outfile, "%e %e %e;", rgbValues[i][RED], rgbValues[i][GREEN], rgbValues[i][BLUE]);
        }

        */
    }
    fprintf(outfile, "]\n\n");

    fclose(outfile);


    ////////////////////////////////////////////////////////
    //
    //      Testing of different functions
    //
    ////////////////////////////////////////////////////////
/*
    printList(firstEl);
    printf("Total area = %f\n\n\n", totalArea(firstEl));


    for(int l = 0; l < numberOfVertices; l++) {
        for(int m = 0; m < 3; m++) {
            printf("%f ", locations[l][m]);
        }
        printf("\n");
    }

    for(int l = 0; l < numberOfFaces - 1; l++) {
        for(int m = 0; m < 3; m++) {
            printf("%d ", faces[l][m]);
        }
        printf("\n");
    }



    float a[] = {0,0,0};
    float b[] = {3,2,1};
    float c[] = {7,6,4};

    printf("\n Test delovanja getArea: %f\n", getArea(a, b, c));

    printf("Test delovanja getCenter: \n");
    float sred[3] = {0};
    float aA[] = {3,2,0};
    float bB[] = {1,7,0};
    float cC[] = {12,4,0};
    getCenter(aA,bB,cC,sred);
    printf("%f, %f, %f", sred[0], sred[1], sred[2]);
*/

    return 0;
}
