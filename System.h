#ifndef SYSTEM_H
#define SYSTEM_H

class System {
	
	private:
		int **system;
		int size;
	
	public:
		System(int);
		~System();
		
		void wypisz();
		void zeroSystem(int**);
		void fillTheMatrix();
		int zwrocMinimalnyCzasRealizacjiPrzedsiewziecia(int, int);
		int maxWWierszu(int);
		int zwrocLiczbeNieMaksowaTylkoKoncowa(int, int);
		bool sprawdzCzyWRzedzieJestKoncowaLiczba(int, int);
		int zwrocNajpozniejszyMomentRozpoczeciaRealizacji(int, int);
		int zwrocNajwczesniejszyMomentRozpoczeciaRealizacji(int, int);
		int zwrocWageLuku(int, int);
		void wypiszWszystkieZadania();
};

#endif
