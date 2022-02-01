#include<Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"BarrierOption.h"


using namespace Rcpp;
using std::vector;

// [[Rcpp::export]]
double getBarrierCallPrice(
  int nInt,
  double Strike,
  double Spot,
  double Barrier,
  double Vol,
  double Rfr,
  double Expiry,
  int nReps = 1000){

	// set the seed
	srand( time(NULL) );

	// create a new instance of a class
BarrierOption myBarrier(nInt, Strike, Spot,Barrier ,Vol, Rfr, Expiry);

	// call the method to get option price
	double price = myBarrier.getBarrierCallPrice(nReps);
	
	// return option price  
	return price;
}
