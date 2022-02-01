#include<vector>

class BarrierOption{
public:

	//constructor
	BarrierOption(
		int nInt_,
		double strike_,
		double spot_,
		double barrier_,
		double vol_,
		double r_,
		double expiry_
		);

	//destructor
	~BarrierOption(){};

	//methods
	void generatePath();
	bool checkIfOverBarrier();
	void printPath();
	double getBarrierCallPrice(int nReps);


	
	//members
	std::vector<double> thisPath;
	int nInt;
	double strike;
	double spot;
	double barrier;
	double vol;
	double r;
	double expiry;

};
