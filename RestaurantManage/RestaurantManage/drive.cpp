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


}