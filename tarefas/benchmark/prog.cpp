#include <chrono>
#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>


int main(int argc , char **argv){

	auto N =std::atoi(argv[1]);
	int R=30;	
		

	int *A,*B, *C,*D;

	A=(int*)malloc(sizeof(int)*N);
	B=(int*)malloc(sizeof(int)*N);
	C=(int*)malloc(sizeof(int)*N);
	D=(int*)malloc(sizeof(int)*N);


	for(int i=0;i<N;++i){
	
		A[i]=0;
		B[i]=1;
		C[i]=2;
		D[i]=3;

	}
	auto start =std::chrono::system_clock::now();

	std::fstream outputfile;

	for(int j=0; j<= R; ++j){

		for(int i=0;i<N; ++i)
			A[i]= B[i] +C[i] *D[i];
	}
	
	auto end = std::chrono::system_clock::now();	
	
	std::chrono::duration<double> elapsed_seconds = end-start;
	auto time =elapsed_seconds.count();
	outputfile.open("plot.dat",std::ios_base::app);
	std::cout <<" "<<time<<"\n";
	auto MFLOPS = R *N * 2. /time*1.e6;

	outputfile<< " "<<N<<"\t"<<MFLOPS<<"\n";
}
