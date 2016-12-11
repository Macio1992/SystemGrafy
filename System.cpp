#include "System.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

System::System(int x){
	
	size = x;
		
	system = new int*[size];
	for(int i = 0; i < size; i++)
		system[i] = new int[size];
		
	zeroSystem(system);
	
}

System::~System(){
	
	for (int i = 0; i < size ; i++)
		delete [] system[i];
	delete [] system;
	
}

void System::wypisz(){
	
	cout<<"  0 1 2 3 4 5"<<endl<<endl;
	for(int i = 0; i < size; i++){
		cout<<i<<" ";
		for(int j = 0; j < size; j++){
			cout << system[i][j]<<" ";
		}
		cout <<"\n";
	}
	cout <<"\n";
	
}

void System::zeroSystem(int **tab){
	
	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			tab[i][j] = 0;
	
}

void System::fillTheMatrix(){
	ifstream ifile;
	ifile.open("data.txt");
	
	if(!ifile){
		cout<<"Blad podczas otwierania pliku"<<endl;
	}
	
	int a, b, c;
	string line;
	while(getline(ifile, line)){
		stringstream ss;
		ss << line;
		ss >> a >> b >> c;
		system[a][b] = c;
	}
	ifile.close();
}

int System::maxWWierszu(int wiersz){
	
	int max = system[wiersz][0], pozycja = 0;
	for(int i = 0; i < size; i++)
		if(system[wiersz][i] != 0 && system[wiersz][i] > max){
			max = system[wiersz][i];
			pozycja = i;
		}
			
	
	return pozycja;
}

bool System::sprawdzCzyWRzedzieJestKoncowaLiczba(int koniec, int wiersz) {
	bool check = false;
	for(int i = 0; i < size; i++)
		//jesli mamy 
		if(system[wiersz][i] != 0 && i == koniec && maxWWierszu(wiersz) > koniec){
			check = true;
		}
			
	return check;
}

int System::zwrocLiczbeNieMaksowaTylkoKoncowa(int koniec, int wiersz){
	//sprawdza czy w rzêdzie jest liczba oprocz maksa ktora jest koncowa.
	int found = 0;
	for(int i = 0; i < size; i++)
		if(system[wiersz][i] != 0 && i == koniec)
			found = system[wiersz][i];
			
	return found;
}

int System::zwrocMinimalnyCzasRealizacjiPrzedsiewziecia(int poczatek, int koniec) {
	
	int x = 0, min = 0;
	int i = poczatek;
	
	//przeskakujemy z maxa w wierszu do odpowiadaj¹cego mu wiersza
	do{
		min += system[i][maxWWierszu(i)];
		i = maxWWierszu(i);
		//jeœli chce sprawdzic droge np do 4go zadania. to on wczesniej wybieral maksa. Tu maks prowadzi do 5go
		//zadania i sie zapetla. Jesli chcemy do konkretnego zadania to sprawdzamy czy waga zadania do ktorego 
		//chcemy isc jest koncowa. jesli jest to ignorujemy maksymalna tylko do min dodajemy wage i konczymy
		if(sprawdzCzyWRzedzieJestKoncowaLiczba(koniec, i)){
			min += zwrocLiczbeNieMaksowaTylkoKoncowa(koniec, i);
			i = koniec;
		}
		if(koniec == 0 || poczatek == koniec){
			min = 0;
			i = koniec;
		}
	} while(i != koniec);
	
	return min;
}

int System::zwrocNajpozniejszyMomentRozpoczeciaRealizacji(int poczatek, int koniec){
	//cout<<"test: "<<zwrocMinimalnyCzasRealizacjiPrzedsiewziecia(koniec, size-1)<<endl;
	return 
		zwrocMinimalnyCzasRealizacjiPrzedsiewziecia(0, size-1) - zwrocMinimalnyCzasRealizacjiPrzedsiewziecia(koniec, size-1) - zwrocWageLuku(poczatek, koniec);
}

int System::zwrocNajwczesniejszyMomentRozpoczeciaRealizacji(int poczatek, int koniec){
	return zwrocMinimalnyCzasRealizacjiPrzedsiewziecia(0, poczatek);
}

int System::zwrocWageLuku(int a, int b){
	return system[a][b];
}

void System::wypiszWszystkieZadania(){

	for(int i = 0; i < size; i++)
		for(int j = 0; j < size; j++)
			if(system[i][j] != 0){
				cout<<"Najwczesniejszy moment luku ("<<i<<", "<<j<<") : \t"<<zwrocNajwczesniejszyMomentRozpoczeciaRealizacji(i,j)<<endl;
				cout<<"Najpozniejszy moment luku ("<<i<<", "<<j<<") : \t"<<zwrocNajpozniejszyMomentRozpoczeciaRealizacji(i,j)<<endl;
			}
}
