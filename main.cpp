#include <iostream>
#include "System.h"

using namespace std;

int main() {
	
	System system(4);
	system.fillTheMatrix();
	
	cout<<"Minimalny czas realizacji tego przedsiewziecia: "<<system.zwrocMinimalnyCzasRealizacjiPrzedsiewziecia(0, 3)<<endl;
	system.wypiszWszystkieZadania();
	
	return 0;
}
