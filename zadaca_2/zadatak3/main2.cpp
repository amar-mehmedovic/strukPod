#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "MojVektor.hpp"
class Osoba {
   protected:
    std::string _ime;
    std::string _prezime;
    int starosnaDob;

   public:
};
class Automobil {
   protected:
    std::string _model;
    std::string _boja;
    int godinaProizvodnje;
};
class Vozac : protected Osoba, protected Automobil {
   protected:
    int _staz;
    float vrijemeUtrke;

   public:
    Vozac() = default;
    Vozac(std::string& ime, std::string& prezime, int& starost,
	  std::string& model, std::string& boja, int& godiste, int& staz,
	  float& vrijeme) {
	_ime = ime;
	_prezime = prezime;
	starosnaDob = starost;
	_model = model;
	_boja = boja;
	_staz = staz;
	vrijemeUtrke = vrijeme;
	godinaProizvodnje = godiste;
    }
    std::string getName() const { return _ime; }
    std::string getSurname() const { return _prezime; }
    int getAge() const { return starosnaDob; }
    std::string getCarModel() const { return _model; }
    std::string getCarColor() const { return _boja; }
    int getAgeExperience() const { return _staz; }
    int getCarAge() const { return godinaProizvodnje; }

    float inline TimeFinished() const { return vrijemeUtrke; }
};

MojVector<Vozac> inputData(int& br) {
    MojVector<Vozac> ucesnici;
    std::cout << "Unesite podatke o vozacima:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    for (int i = 0; i < br; i++) {
	std::cout << 1 + i << " Vozac " << std::endl;
	std::cout << "Unesite ime vozaca: ";
	std::string ime;
	std::getline(std::cin, ime);
	std::cout << "Unesite prezime vozaca: ";
	std::string prezime;
	std::getline(std::cin, prezime);
	std::cout << "Unesite starosnu dob vozaca: ";
	int starost;
	std::cin >> starost;
	std::cin.ignore();
	std::cout << "Unesite model auta vozaca: ";
	std::string model;
	std::getline(std::cin, model);
	std::cout << "Unesite boju auta vozaca: ";
	std::string boja;
	std::getline(std::cin, boja);
	std::cout << "Unesite godinu proizvodnje auta vozaca: ";
	int godinaProizvodnje;
	std::cin >> godinaProizvodnje;
	std::cin.ignore();
	std::cout << "Unesite staz vozaca: ";
	int staz;
	std::cin >> staz;
	std::cin.ignore();
	std::cout << "Vrijeme za koje je vozac zavrsio utrku: ";
	float vrijeme;
	std::cin >> vrijeme;
	std::cin.ignore();
	Vozac osoba(ime, prezime, starost, model, boja, godinaProizvodnje, staz,
		    vrijeme);
	ucesnici.push_back(osoba);
    }
    return ucesnici;
}
void outputData(MojVector<Vozac>& ucesnici) {
    std::cout << "br" << std::setw(15) << "Name" << std::setw(15) << "Surname"
	      << std::setw(15) << "Age" << std::setw(15) << "Exp."
	      << std::setw(15) << "Model" << std::setw(15) << "Colour"
	      << std::setw(15) << "Year" << std::setw(15) << "Time"
	      << std::endl;
    std::cout << std::string(130, '-') << std::endl;
    for (int i = 0; i < ucesnici.size(); i++) {
	std::cout << i + 1 << std::setw(15) << ucesnici.at(i).getName()
		  << std::setw(16) << ucesnici.at(i).getSurname()
		  << std::setw(15) << ucesnici.at(i).getAge() << std::setw(15)
		  << ucesnici.at(i).getAgeExperience() << std::setw(15)
		  << ucesnici.at(i).getCarModel() << std::setw(15)
		  << ucesnici.at(i).getCarColor() << std::setw(15)
		  << ucesnici.at(i).getCarAge() << std::setw(15)
		  << ucesnici.at(i).TimeFinished() << std::endl;
    }
}
int main(int argc, char* argv[]) {
    int br;
    std::cout << "Unesite broj ucesnika na utrkama:";
    std::cin >> br;
    std::cin.ignore();
    MojVector<Vozac> ucesnici = inputData(br);
    std::sort(ucesnici.begin(), ucesnici.end(),
	      [](const Vozac& vozac1, const Vozac& vozac2) {
		  return vozac1.TimeFinished() < vozac2.TimeFinished();
	      });
    outputData(ucesnici);
}
