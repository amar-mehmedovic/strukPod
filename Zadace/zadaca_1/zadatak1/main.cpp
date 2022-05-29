#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
class radnik {
   private:
    std::string ime;
    std::string prezime;
    std::string brTelefona;
    int godine;
    int staz;
    int plata;

   public:
    template <typename t>
    void writeData(t podatak, int pom) {
	if (pom == 1) {
	    ime = podatak;
	}  // ime
	else if (pom == 2) {
	    prezime = podatak;
	}  // prezime
	else if (pom == 3) {
	    std::stringstream ss;
	    ss << podatak;
	    ss >> godine;
	}  // godine
	else if (pom == 4) {
	    std::stringstream ss;
	    ss << podatak;
	    ss >> staz;

	}  // staz
	else if (pom == 5) {
	    std::stringstream ss;
	    ss << podatak;
	    ss >> plata;

	}  // plata
	else if (pom == 6) {
	    brTelefona = podatak;
	}  // br.telefona
    }

    friend std::ostream& operator<<(std::ofstream& out, const radnik& o) {
	return out << o.ime << "," << o.prezime << "," << o.godine << ","
		   << o.staz << "," << o.plata << "," << o.brTelefona
		   << std::endl;
    }
    int inline getAge() const { return godine; }
    int inline getExperience() const { return staz; }
    std::string inline getName() const { return ime; }
    std::string inline getSurname() const { return prezime; }
    void changeSalary(char znak, int procenat) {
	if (znak == '+') {
	    plata = plata + (procenat / 100);
	} else {
	    plata = plata - (procenat / 100);
	}
    }
};

std::vector<radnik> processData(std::ifstream& input) {
    std::vector<radnik> Radnici;
    if (input.is_open()) {
	std::string linija_teksta;
	while (std::getline(input, linija_teksta)) {  // uzmi liniju teksta
	    std::string str;
	    std::stringstream ss(linija_teksta);
	    radnik osoba;
	    int pom = 1;
	    while (std::getline(
		ss, str, ',')) {  // odvoji liniju teksta u vise stringova
		osoba.writeData(str, pom);  // unesi podatak u objekat
		pom++;
	    }
	    if (osoba.getAge() < 55) {
		if (osoba.getExperience() > 15) {
		    osoba.changeSalary('+',
				       20);  // povecaj platu za osobe sa stazom
					     // preko 15 godina
		}
		Radnici.push_back(
		    osoba);  // uslov da osobe starije od 55 idu u penziju
	    }
	}
    }
    return Radnici;
}
std::vector<radnik> mergeData(std::vector<radnik>& acme,
			      std::vector<radnik>& globex) {
    std::vector<radnik> merged;
    for (int i = 0; i < acme.size(); i++) {
	merged.push_back(acme.at(i));
    }
    for (int i = 0; i < globex.size(); i++) {
	merged.push_back(globex.at(i));
    }
    return merged;
}
void sortData(std::vector<radnik>& corpexRadnici) {
    std::sort(corpexRadnici.begin(), corpexRadnici.end(),
	      [](const radnik& osoba1, const radnik& osoba2) {
		  return osoba1.getAge() < osoba2.getAge();
	      });
    int br;
    for (int i = 0; i < corpexRadnici.size(); i++) {
	if (br <= 15) {
	    corpexRadnici.at(i).changeSalary('+', 10);
	}
    }
    std::sort(corpexRadnici.begin(), corpexRadnici.end(),
	      [](const radnik& osoba1, const radnik& osoba2) {
		  if (osoba1.getName() == osoba2.getName())
		      return osoba1.getSurname() < osoba2.getSurname();
		  else
		      return osoba1.getName() < osoba2.getName();
	      });
}
void outputDataToFile(std::vector<radnik>& corpexRadnici) {
    std::ofstream out{"corp.txt"};
    if (out.is_open()) {
	for (int i = 0; i < corpexRadnici.size(); i++) {
	    out << corpexRadnici.at(i);
	}
    }
}
int main(int argc, char* argv[]) {
    std::ifstream input{"acme.txt"};
    std::vector<radnik> acmeRadnici = processData(input);
    input.close();
    input.open("globex.txt");
    std::vector<radnik> globexRadnici = processData(input);
    std::vector<radnik> corpexRadnici = mergeData(acmeRadnici, globexRadnici);
    sortData(corpexRadnici);
    outputDataToFile(corpexRadnici);
}
