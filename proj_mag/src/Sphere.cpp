#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define pi 3.141592653589793
using namespace std;
#include "Sphere.h"



//Start implemantations 


	//constructor
	
	Sphere::Sphere(const double radius):r(radius){
		int i, j;
		const char* n="TXT/Pixels_carlos.txt"; 
		std::string name =n;
		sphericalcoord=readData(name);
		cartesiancoord=turnTocartesian(name,sphericalcoord,r);


	}


	double Sphere::getRadians( double degrees){
		return( (degrees * pi)/ 180);
	}

	void Sphere::count(string &inputfile,int *rows, int *cols){
		
		std::ifstream fin(inputfile);
	    	int  numItems=0;
		*rows=0;
		*cols=0;

		double val=0;
	    
		while( fin.peek() != '\n' && fin >> val )
	    	{
			++numItems;
	    	}
	    	*cols = numItems;// # of columns found

	    	while( fin >> val )
	    	{	
			++numItems;
	    	}
		*rows = numItems/ *cols;

		fin.close();
	}
	
	double** Sphere::readData(string &inputfile){
		
		double aux;
		FILE *pf;
		int rows, cols,i,j;

		count(inputfile,&rows,&cols);
		double **M=(double **)malloc(rows*sizeof(double*));



	    	for(i=0;i<rows;i++)
		  	*(M+i)=(double *)malloc((cols-1)*sizeof(double));
		
		
		const char * filename=inputfile.c_str();
		pf=fopen(filename,"r");



	    	if(pf==NULL){

			printf("Empty File!\n\n");

			return NULL;
	    	}



	    	for(i=0;i<rows;i++)
		  	for(j=0;j<cols;j+=1){
				
				fscanf(pf,"%lf",&aux);
				*(*(M+i)+j)=aux;
			

		    	}

	    	fclose(pf);
	
			
	    	return(M);
	}



	double** Sphere::turnTocartesian(string &inputfile,double **M, double r){
		
		int i, j;
		int rows, cols;
		count(inputfile,&rows,&cols);

		double **coord=(double **)malloc(rows*sizeof(double*));


	    	for(i=0;i<rows;i++)
		  	*(coord+i)=(double *)malloc(cols*sizeof(double));

		for(i=0;i<rows;i++){

					*(*(coord+i))=r*cos(*(*(M+i)+1))*sin(*(*(M+i)+0));
					*(*(coord+i)+1)=r*sin(*(*(M+i)+1))*sin(*(*(M+i)+1));

					*(*(coord+i)+2)=r*cos(*(*(M+i)+0));	
			
			}
		
		
		return(coord);
	}

	double** Sphere::getPixel(){
			

			return (cartesiancoord);
	}

//end Implemantations
