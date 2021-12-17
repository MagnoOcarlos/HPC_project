#ifndef SPHERE_H
#define SPHERE_H
using namespace std;

#include<string>
class Sphere{

	private:

		double **sphericalcoord;  //Spherical coordinates from Healpix.
		int *pixelnumber;         //Save the the pixel address of each phi and theta pair
		const double r;           //The distance from Source to Earth.
		double **cartesiancoord;   //Array that save the cartesian coordinates after the change from spherical
//		const string inputfile;
	
	public:
		
		//constructor 
		Sphere(const double);
		
		//Read the file with the pixel data 
		
		void count(string &inputfile,int*, int*);	
		virtual double **readData(string &inputfile);
		double **turnTocartesian(string &inputfile,double**, double);
		double getRadians(double);
		double** getPixel();
			
};

#endif
