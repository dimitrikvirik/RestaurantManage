#include "Restaurant.h"
int main() {
	//შეტანა ფაილით
	std::ifstream ifs("restaurant.txt");
	Restaurant rest1;
	ifs >> rest1;
	std::cout << rest1;
	//შეტანა მომხმარებელით
	Restaurant rest2;
	std::cin >> rest2;
	std::cout << rest2;
	//შეტანა კონკრეტული მნიშვნელობები
	Restaurant rest3("Domino Pizza", "Saburtalo 5", 9000, 4000, 500, 70, 1005000, 500000, 10502, 20000);
	Owner ow("Dito", "00013");
	Chef cf1("Jhoniko", "00123", "Georgian");
	Chef cf2("Laniko", "004423", "Spain");
	Waitress wt1("Luka", "00001391", 10);
	Waitress wt2("Mari", "00001377", 20);
	rest3.addEmploye(ow);
	rest3.addEmploye(cf1);
	rest3.addEmploye(cf2);
	rest3.addEmploye(wt1);
	rest3.addEmploye(wt2);
	std::cout << rest3;

}