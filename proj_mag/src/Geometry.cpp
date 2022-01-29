#include <iostream>
#include <string>
#include <fstream>
#include <sting.h>
#include <stdlib.h>
#include <math.h>
#include "Geometry.h"
#include "Sphere.h"

using namespace std;



//Start implemantations


	//Constructor
	
	Geometry::Geometry(double radius, const bool E0):initenergy(E0),Sphere(radius){
		const char* n="TXT/dados.txt";
		string name=n;
		data=readSimuData(name);
	}

	
	
	double** Geometry::readSimuData(string &inputfile){
		
			
		double aux;
		FILE *pf;
		int rows, cols,i,j;

		count(inputfile,&rows,&cols);
		double **M=(double **)malloc(rows*sizeof(double*));



	    	for(i=0;i<rows;i++)
		  	*(M+i)=(double *)malloc(cols*sizeof(double));
		
		
		const char * filename=inputfile.c_str();
		pf=fopen(filename,"r");



	    	if(pf==NULL){

			printf("Empty File!\n\n");

			return NULL;
	    	}

		for(i=0;i<rows; i++)
			for(j=0;j<cols;j++){
				
				fscanf(pf, "%lf",&aux);
				*(*(M+i)+j)=aux;
			}



	    	fclose(pf);
	    	return(M);
	} 
	
	double Geometry::anglesBetweenVec(double *u, double *v){

		double inner, strenu,strenv;
		inner= u[0]*v[0]+ u[1]*v[1]+u[2]*v[2];

		strenu= sqrt(u[0]*u[0] + u[1]*u[1] + u[2]*u[2]);
		strenv= sqrt(v[0]*v[2] + v[1]*v[1]+ v[2]*v[2]);
		
		return( acos(inner/(strenu*strenv)));
	}

	void Geometry::angularDistance(){

		int i,j,k,l,rowsp,colsp,rowsd,colsd;
		double *u, *v,**pixel;
		
		const char* n1="TXT/dados.txt";
		const char* n2="TXT/Pixels_carlos.txt";
		string name1=n1;
		string name2=n2;

		count(name1,&rowsd,&colsd);
		count(name2,&rowsp,&colsp);
		
		pixel = getPixel();
		u=(double *)malloc(3*sizeof(double));
		v=(double *)malloc(3*sizeof(double));
		
		#pragma omp parallel private(i,j,l,u,v) shared(pixel,data)
		{
		#pragma omp for collapse(3)		
		for(i=0;i<=0;i+=10){

			for(j=0;j<rowsp;j++)
				for(l=0;l<rowsd;l++){
				
					u[0]=pixel[j][0];
					u[1]=pixel[j][1];
					u[2]=pixel[j][2];

					v[0]=data[l][17];
					v[1]=data[l][18];
					v[2]=data[l][19];
				
					if(anglesBetweenVec(u,v)<=getRadians(i+2.5) && anglesBetweenVec(u,v)>=getRadians(i-2.5)){
						writeResult(data[l][13],true,i);

						v[0]=data[l][5];
						v[1]=data[l][6];
						v[2]=data[l][7];
					

						if(anglesBetweenVec(u,v)<=getRadians(0.15))
							writeResult(data[l][4],false,i);
											
					}

						
				}
						
		}
		}
		free(u);
		free(v);
	}


	void Geometry::writeResult(double E,bool injection, int i){
		
		fstream outputfile;


		if(injection){
			
			string file ="injection_ang"+ to_string(i)+".txt";		
			outputfile.open(file, ios_base::app);
			outputfile << " "<<E<<"\n";

		}

		else{
			string file ="arrive_ang"+ to_string(i)+".txt";		
			outputfile.open(file, ios_base::app);
			outputfile << " "<<E<<"\n";
		}

	}	
	
	
