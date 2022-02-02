#include<iostream>
#include<cmath>
#include"getOneGaussianByBoxMueller.h"
#include"BarrierOption.h"
#include <Rcpp.h>

//definition of constructor
BarrierOption::BarrierOption(
	int nInt_,
	double strike_,
	double spot_,
	double barrier_,
	double vol_,
	double r_,
	double expiry_){
		nInt = nInt_;
		strike = strike_;
		spot = spot_;
		barrier = barrier_;
		vol = vol_;
		r = r_;
		expiry = expiry_;
		generatePath();
}

//method definition
void BarrierOption::generatePath(){
	double thisDrift = (r * expiry - 0.5 * vol * vol * expiry) / double(nInt);
	double cumShocks = 0;
	thisPath.clear();
	// this it to guarantee that the path starts at the spot price
	// thisPath.push_back(spot * exp(cumShocks));
	for(int i = 0; i < nInt; i++){
	  thisPath.push_back(spot * exp(cumShocks));
		cumShocks += (thisDrift + vol * sqrt(expiry / double(nInt)) * getOneGaussianByBoxMueller());

	}
}

//method definition
bool BarrierOption::checkIfOverBarrier(){
  //calculate max element in thisPath and see if is >= barrier
  double thisMax = *std::max_element(thisPath.begin(), thisPath.end());
 
  if (thisMax >= barrier) {
    return true;
  }else{
    return false;
    }
}



//method definition
void BarrierOption::printPath(){

	for(int i = 0;  i < nInt; i++){

		std::cout << thisPath[i] << "\n";

	}

}

//method definition
double BarrierOption::getBarrierCallPrice(int nReps){

	double rollingSum = 0.0;
  bool isThisPathActive;

	for(int i = 0; i < nReps; i++){
		generatePath();
		isThisPathActive=checkIfOverBarrier();
		//std::cout << isThisPathActive << "\n";
		if(isThisPathActive){
		    rollingSum += ( (thisPath.back() > strike) ) ? (thisPath.back()-strike) : 0;
		}else{
		    continue;
		  }
		
	}

	return exp(-r*expiry)*rollingSum/double(nReps);

}



