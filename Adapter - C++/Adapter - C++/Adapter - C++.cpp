#include <iostream>
using namespace std;

class Scales {
public:
	virtual float* GetWeight() = 0;
	virtual ~Scales(){}
};

class UkrainScales : public Scales {
private:
	float* current_weight;
public:
	UkrainScales(float* cw) : current_weight(cw){}

	float* GetWeight() override {
		return current_weight;
	}

	~UkrainScales() override {
		delete current_weight;
	}
};

class BritishScale : public Scales {
private:
	float* current_weight;
public:
	BritishScale(float* cw) : current_weight(cw) {}

	float* GetWeight() override {
		return current_weight;
	}

	~BritishScale() override {
		delete current_weight;
	}
};

class AdapterForBritishScales : public Scales {
private:
	BritishScale* britishscales;
	float* cw;
public:
	AdapterForBritishScales(BritishScale* bs) : britishscales(bs){}
	~AdapterForBritishScales() {
		delete britishscales;
		delete cw;
	}

	float* GetWeight() {
		cw = britishscales->GetWeight();
		*cw = *cw * 0.453;
		return cw;
	}
};

int main() {
	float kg = 55.0;
	float lb = 55.0;

	Scales* UkrainSCales = new UkrainScales(&kg);
	Scales* BritishSCales = new AdapterForBritishScales(new BritishScale(&lb));

	cout << *UkrainSCales->GetWeight() << "\n";
	cout << *BritishSCales->GetWeight() << "\n";
}