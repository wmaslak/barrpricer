#include<Rcpp.h>
#include<vector>
#include<ctime>
#include<cstdlib>
#include"BarrierOption.h"


using namespace Rcpp;
using std::vector;

//' Get Call price of a European style up-and-in barrier option
//' 
//' @param nInt number of points on single path
//' @param Strike strike price
//' @param Spot spot price at moment of pricing
//' @param Barrier barrier level
//' @param Vol volatility
//' @param Rfr risk free rate
//' @param Expiry time to maturity
//' @param nReps number of paths to simulate
//' @export

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

//' Get simulated paths for plotting purposes
//' 
//' @param nInt number of points on single path
//' @param Strike strike price
//' @param Spot spot price at moment of pricing
//' @param Barrier barrier level
//' @param Vol volatility
//' @param Rfr risk free rate
//' @param Expiry time to maturity
//' @param nReps number of paths to simulate
//' @export

// [[Rcpp::export]]
Rcpp::NumericVector getBarrierPaths(
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
    // Creating an object
    BarrierOption myBarrier(nInt, Strike, Spot,Barrier ,Vol, Rfr, Expiry);
    
    NumericVector paths;
    for(int i = 0; i<nReps; i++){
      myBarrier.generatePath();
      for(int j=0; j<nInt;j++){
          paths.push_back(myBarrier.thisPath[j]);
        }
      }
    
    // Set the number of rows and columns to attribute dim of the vector object.
    paths.attr("dim") = Dimension(nInt, nReps);
    
    // Return the vector to R
    return paths;
  
  
  }
