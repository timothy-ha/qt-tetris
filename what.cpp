#include <iostream>
using namespace std;

int main() {
	int reqLines = 0;
	int reqTotalLines = 0;
	
	for (int i = 0; i < 12; i++) {
		if (i % 10 == 0) reqLines += 1;

		reqTotalLines += reqLines += 2;
		cout << reqTotalLines << ", ";
	}

	return 0;
}