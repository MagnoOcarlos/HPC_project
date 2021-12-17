#ifndef GEOMETRY_H
#define GEOMETRY_H

using namespace std;

#include<string>

#include "Sphere.h"

class Geometry:public Sphere{

	private:
		double **data;
		const bool initenergy;
		double **result;
	public:
		Geometry(double, const bool);

		double anglesBetweenVec(double*,double*);
		void angularDistance();
		void writeResult(double, bool,int);
		double** readSimuData(string &inputfile);
};


#endif
