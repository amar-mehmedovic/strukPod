
#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
class Vozac {
   public:
    std::string ime_;
    int bodovi_;
    int vrijeme_;
    std::string tim_;
    Vozac(std::string ime, int bodovi, int vrijeme, std::string tim)
	: ime_{ime}, bodovi_{bodovi}, vrijeme_{vrijeme}, tim_{tim} {}
};
class Utrka {
   public:
    std::vector<Vozac> u;

   public:
    Utrka() {}
    Utrka(std::vector<Vozac> v) {
	for (int i = 0; i < v.size(); i++) {
	    u.push_back(v.at(i));
	}
	std::partition(u.begin(), u.end(),
		       [](const Vozac& v1) { return v1.vrijeme_ > 0; });
	std::sort(u.begin(), u.end(), [](const Vozac& v1, const Vozac& v2) {
	    if (v1.vrijeme_ == v2.vrijeme_) {
		return v1.bodovi_ > v2.bodovi_;
	    } else {
		if (v1.vrijeme_ > 0 && v2.vrijeme_ > 0) {
		    return v1.vrijeme_ < v2.vrijeme_;
		}
	    }
	});
    }

    friend std::ostream& operator<<(std::ostream& out, const Utrka& v) {
	for (int i = 0; i < v.u.size(); i++) {
	    out << 1 + i << ". " << v.u.at(i).ime_ << " ";
	    if (v.u.at(i).vrijeme_ == 0) {
		out << "DNF"
		    << " ";
	    } else {
		out << v.u.at(i).vrijeme_ << " ";
	    }
	    out << v.u.at(i).bodovi_ << std::endl;
	}
	return out;
    }

    std::string dnf() {
	std::string pom;
	for (int i = 0; i < u.size(); i++) {
	    if (u.at(i).vrijeme_ == 0) {
		pom = pom + u.at(i).ime_ + ",";
	    }
	}
	pom.erase(pom.end() - 1);
	return "Ispis: " + pom;
    }

    std::string najgoriTim() {
	std::map<std::string, int> mapa;
	for (int i = 0; i < u.size(); i++) {
	    mapa[u.at(i).tim_] += u.at(i).bodovi_;
	}
	int min = mapa.begin()->second;
	std::string tim = mapa.begin()->first;
	auto begin = mapa.begin();
	while (begin != mapa.end()) {
	    if (begin->second < min) {
		min = begin->second;
		tim = begin->first;
	    }
	    begin++;
	}
	return tim + " " + std::to_string(min);
    }
};

int main(int argc, char* argv[]) {
    std::vector<Vozac> vozaci{{"Hamilton", 144, 150, "Mercedes"},
			      {"Ocon", 41, 0, "Alpine"},
			      {"Verstappen", 100, 145, "Red Bull"},
			      {"Alonso", 50, 160, "Alpine"},
			      {"Bottas", 55, 0, "Alfa Romeo"}};
    Utrka australiaGP{vozaci};
    std::cout << australiaGP << std::endl;
    std::cout << australiaGP.dnf() << std::endl;
    std::cout << australiaGP.najgoriTim() << std::endl;
    return 0;
}
