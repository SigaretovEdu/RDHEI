#include <iostream>
#include <vector>
#include <cmath>
#include <string>


int main() {

	for(int i = 0; i < 255; ++i) {

		// old formula
		int num = 0;
		for(int j = 0; j < 8; ++j) {
			num += (static_cast<int>(std::ceil(i / (std::pow(2, j)))) % 2) << j;
		}
		std::cout<<num<<'\t';


		// new formula
		if(i != 0)
			std::cout<<(255 ^ (i - 1))<<'\n';
		else
			std::cout<<0<<'\n';
	}

	return 0;
}
