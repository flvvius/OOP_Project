#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Exceptie {
	string mesajExceptie;

public:
	Exceptie(string mesajExceptie) {
		this->mesajExceptie = mesajExceptie;
	}

	string getMesajExceptie() {
		return mesajExceptie;
	}
};

class Cultura {
	const int idCultura;
	char* tipCultura;
	int suprafataCultivata;
	double productiaMedie;
	float pretPerUnitate;
	bool esteBio;
	double costuriTotale;
	static int numarCulturi;

public:
	Cultura() : idCultura(++numarCulturi) {
		this->tipCultura = new char[strlen("Anonima") + 1];
		strcpy(tipCultura, "Anonima");
		suprafataCultivata = 0;
		productiaMedie = 0.0f;
		pretPerUnitate = 0.0f;
		esteBio = false;
		costuriTotale = 0;
	}

	Cultura(const char* tipCultura, unsigned int suprafataCultivata, double productiaMedie, float pretPerUnitate, bool esteBio, double costuriTotale) : idCultura(++numarCulturi) {
		this->tipCultura = new char[strlen(tipCultura) + 1];
		strcpy(this->tipCultura, tipCultura);
		this->suprafataCultivata = suprafataCultivata;
		this->productiaMedie = productiaMedie;
		this->pretPerUnitate = pretPerUnitate;
		this->esteBio = esteBio;
		this->costuriTotale = costuriTotale;
	}

	~Cultura() {
		if (tipCultura != NULL)
			delete[] tipCultura;
		numarCulturi--;
	}

	Cultura(const Cultura& c) : idCultura(++numarCulturi) {
		if (c.tipCultura != NULL) {
			this->tipCultura = new char[strlen(c.tipCultura) + 1];
			strcpy(this->tipCultura, c.tipCultura);
		}
		this->suprafataCultivata = c.suprafataCultivata;
		this->productiaMedie = c.productiaMedie;
		this->pretPerUnitate = c.pretPerUnitate;
		this->esteBio = esteBio;
		this->costuriTotale = costuriTotale;
	}

	Cultura operator=(const Cultura& c) {
		if (this != &c) {
			if (c.tipCultura != NULL) {
				if (this->tipCultura != NULL)
					delete[] this->tipCultura;
				this->tipCultura = new char[strlen(c.tipCultura) + 1];
				strcpy(this->tipCultura, c.tipCultura);
			}
			this->suprafataCultivata = c.suprafataCultivata;
			this->productiaMedie = c.productiaMedie;
			this->pretPerUnitate = c.pretPerUnitate;
			this->esteBio = esteBio;
			this->costuriTotale = costuriTotale;
		}
		else
			throw Exceptie("\nEroare autoasignare!\n");

		return *this;
	}

	friend ostream& operator<<(ostream& os, Cultura& c);

	friend ofstream& operator<<(ofstream& ofs, Cultura& c) {
		//ofs << c.idCultura;
		ofs << c.tipCultura;
		ofs << endl << c.suprafataCultivata;
		ofs << endl << c.productiaMedie;
		ofs << endl << c.pretPerUnitate;
		ofs << endl << c.esteBio;
		ofs << endl << c.costuriTotale;

		return ofs;
	}

	friend istream& operator>>(istream& os, Cultura& c);

	friend ifstream& operator>>(ifstream& ifs, Cultura& c) {
		if (c.tipCultura != NULL)
			delete[] c.tipCultura;
		c.tipCultura = new char[25];
		//ifs >> c.tipCultura;
		//getchar(); fara pentru fisier
		ifs.getline(c.tipCultura, sizeof(char) * 25);

		ifs >> c.suprafataCultivata;

		ifs >> c.productiaMedie;

		ifs >> c.pretPerUnitate;

		ifs >> c.esteBio;

		ifs >> c.costuriTotale;

		return ifs;
	}

	int getIdCultura() {
		return idCultura;
	}

	char* getTipCultura() {
		return tipCultura;
	}

	void setTipCultura(const char* tipCulturaNou) {
		if (tipCulturaNou != NULL && strlen(tipCulturaNou) >= 2) {
			if (tipCultura != NULL)
				delete[] tipCultura;
			tipCultura = new char[strlen(tipCulturaNou) + 1];
			strcpy(tipCultura, tipCulturaNou);
		}
		else
			throw Exceptie("\nTip cultura invalid!\n");
	}

	int getSuprafataCultivata() {
		return suprafataCultivata;
	}

	void setSuprafataCultivata(int suprafataCultivataNoua) {
		if (suprafataCultivataNoua >= 0)
			suprafataCultivata = suprafataCultivataNoua;
		else
			throw Exceptie("\nSuprafata cultivata nu poate fi negativa!\n");
	}

	double getProductiaMedie() {
		return productiaMedie;
	}

	void setProductiaMedie(double productiaMedieNoua) {
		if (productiaMedieNoua >= 0.0f)
			productiaMedie = productiaMedieNoua;
		else
			throw Exceptie("\nProductia medie nu poate fi negativa!\n");
	}

	float getPretPerUnitate() {
		return pretPerUnitate;
	}

	void setPretPerUnitate(float pretPerUnitateNou) {
		if (pretPerUnitateNou >= 0.0f)
			pretPerUnitate = pretPerUnitateNou;
		else
			throw Exceptie("\nPretul per unitate nu poate fi negativ!\n");
	}

	bool getEsteBio() {
		return esteBio;
	}

	void setEsteBio(bool esteBioNou) {
		if (esteBio != esteBioNou)
			esteBio = esteBioNou;
		else
			throw Exceptie("Variabile boolene asemenea!");
	}

	double getCosturiTotale() {
		return costuriTotale;
	}

	void setCosturiTotale(double costuriTotaleNoi) {
		if (costuriTotaleNoi >= 0)
			costuriTotale = costuriTotaleNoi;
		else
			throw Exceptie("\nCosturile totale nu pot fi negative!\n");
	}

	virtual double valoareCultura() {
		return suprafataCultivata * productiaMedie * (pretPerUnitate * 1000);
	}

	virtual double profitCultura() {
		return valoareCultura() - costuriTotale;
	}

	void operator+=(int suprafata) {
		if (suprafata >= 0)
			suprafataCultivata += suprafata;
		else
			throw Exceptie("Nu puteti adauga o suprafata negativa!");
	}

	operator double() {
		return costuriTotale;
	}

	bool operator!() {
		if (suprafataCultivata == 0)
			return true;
		else
			return false;
	}

	bool operator==(Cultura c) {
		if (profitCultura() == c.profitCultura())
			return true;
		else
			return false;
	}

	bool operator!=(Cultura c) {
		if (idCultura != c.idCultura)
			return true;
		return false;
	}
};

int Cultura::numarCulturi = 0;

ostream& operator<<(ostream& os, Cultura& c) {
	os << endl << "ID cultura:                      " << c.idCultura;
	os << endl << "Tip cultura:                     " << c.tipCultura;
	os << endl << "Suprafata cultivata(hectare):    " << c.suprafataCultivata;
	os << endl << "Productia medie la hectar(tone): " << c.productiaMedie;
	os << endl << "Pret per unitate(RON/kilogram):  " << c.pretPerUnitate;
	os << endl << "Ferma este bio:                  " << (c.esteBio == 1 ? "Da" : "Nu");
	os << endl << "Costuri totale:                  " << c.costuriTotale;
	os << endl << "-------------------------------------------------------------------" << endl;

	return os;
}

istream& operator>>(istream& is, Cultura& c) {
	cout << "\nIntroduceti tipul culturii: ";
	if (c.tipCultura != NULL)
		delete[] c.tipCultura;
	c.tipCultura = new char[25];
	//is >> c.tipCultura;
	getchar();
	is.getline(c.tipCultura, sizeof(char) * 25);

	cout << "Introduceti suprafata cultivata(hectare): ";
	is >> c.suprafataCultivata;

	cout << "Introduceti productia medie(tone/hectar): ";
	is >> c.productiaMedie;

	cout << "Introduceti pretul per unitate(RON): ";
	is >> c.pretPerUnitate;

	cout << "Cultura " << c.tipCultura << " este BIO?(1 - DA | 0 - NU): ";
	is >> c.esteBio;

	cout << "Introduceti costurile totale: ";
	is >> c.costuriTotale;

	return is;
}

class CulturaIrigata : public Cultura {
	char* tipIrigatie;
	int costuriIrigatie = 0;

public:
	CulturaIrigata() : Cultura() {
		tipIrigatie = new char[strlen("clasica") + 1];
		strcpy(tipIrigatie, "clasica");
		costuriIrigatie = 0;
	}

	CulturaIrigata(const char* tipCultura, unsigned int suprafataCultivata, double productiaMedie, float pretPerUnitate, bool esteBio, double costuriTotale, const char* tipIrigatie, int costuriIrigatie)
		: Cultura(tipCultura, suprafataCultivata, productiaMedie, pretPerUnitate, esteBio, costuriTotale) {

		this->tipIrigatie = new char[strlen(tipIrigatie) + 1];
		strcpy(this->tipIrigatie, tipIrigatie);
		this->costuriIrigatie = costuriIrigatie;
	}

	~CulturaIrigata() {
		if (tipIrigatie != NULL) delete[] tipIrigatie;
	}

	CulturaIrigata(const CulturaIrigata& ci) : Cultura(ci) {
		if (ci.tipIrigatie != NULL) {
			this->tipIrigatie = new char[strlen(ci.tipIrigatie) + 1];
			strcpy(this->tipIrigatie, ci.tipIrigatie);
		}
		this->costuriIrigatie = ci.costuriIrigatie;
	}

	CulturaIrigata operator=(const CulturaIrigata& ci) {
		if (this != &ci) {
			Cultura::operator=(ci);
			if (ci.tipIrigatie != NULL) {
				if (this->tipIrigatie != NULL)
					delete[] this->tipIrigatie;
				this->tipIrigatie = new char[strlen(ci.tipIrigatie) + 1];
				strcpy(this->tipIrigatie, ci.tipIrigatie);
			}
			this->costuriIrigatie = ci.costuriIrigatie;
		}
		else
			throw Exceptie("Eroare autoasignare!");

		return *this;
	}

	friend ostream& operator<<(ostream& os, CulturaIrigata& ci) {
		os << (Cultura&)ci;
		os << "Tip irigatie:                    " << ci.tipIrigatie << endl;
		os << "Costuri irigatie:                " << ci.costuriIrigatie;
		os << endl << "-------------------------------------------------------------------";
		os << endl << "_______________________" << endl;

		return os;
	}

	friend ofstream& operator<<(ofstream& ofs, CulturaIrigata& ci) {
		ofs << (Cultura&)ci;
		ofs << endl << ci.tipIrigatie;
		ofs << endl << ci.costuriIrigatie;

		return ofs;
	}

	friend istream& operator>>(istream& is, CulturaIrigata& ci) {
		is >> (Cultura&)ci;
		if (ci.tipIrigatie != NULL)
			delete[] ci.tipIrigatie;
		ci.tipIrigatie = new char[25];
		cout << "Introduceti tipul de irigatie: ";
		getchar();
		is.getline(ci.tipIrigatie, sizeof(char) * 25);

		cout << "Introduceti costul irigatiei: ";
		is >> ci.costuriIrigatie;

		return is;
	}

	friend ifstream& operator>>(ifstream& ifs, CulturaIrigata& ci) {
		ifs >> (Cultura&)ci;
		//getchar();
		if (ci.tipIrigatie != NULL)
			delete[] ci.tipIrigatie;
		ci.tipIrigatie = new char[25];
		//getchar();
		string junk; getline(ifs, junk);
		ifs.getline(ci.tipIrigatie, sizeof(char) * 25);
		ifs >> ci.costuriIrigatie;

		return ifs;
	}

	double valoareCultura() {
		return getSuprafataCultivata() * getProductiaMedie() * (getPretPerUnitate() * 1000);
	}

	double profitCultura() {
		return valoareCultura() - getCosturiTotale() - costuriIrigatie;
	}

	char* getTipIrigatie() {
		return tipIrigatie;
	}

	void setTipIrigatie(char* tipIrigatieNou) {
		if (tipIrigatieNou != NULL) {
			if (tipIrigatie != NULL)
				delete[] tipIrigatie;
			tipIrigatie = new char[strlen(tipIrigatieNou) + 1];
			strcpy(tipIrigatie, tipIrigatieNou);
		}
		else
			throw Exceptie("Tip irigatie identic!");
	}

	int getCosturiIrigatie() {
		return costuriIrigatie;
	}

	void setCosturiIrigatie(int costuriIrigatieNoi) {
		if (costuriIrigatieNoi >= 0)
			costuriIrigatie = costuriIrigatieNoi;
		else
			throw Exceptie("Costurile de irigatie nu pot fi negative!");
	}

	bool operator==(CulturaIrigata ci) {
		if (strcmp(tipIrigatie, ci.tipIrigatie) == 0)
			return true;
		return false;
	}

	bool operator>=(CulturaIrigata ci) {
		if (costuriIrigatie >= ci.costuriIrigatie)
			return true;
		return false;
	}

	operator int() {
		return costuriIrigatie;
	}

	bool operator!() {
		if (costuriIrigatie == 0)
			return true;
		return false;
	}
};

class Ferma {
	string numeFerma;
	int numarCulturi;
	Cultura* c;
	int numarCulturiIrigate;
	CulturaIrigata* ci;
	double capacitateDepozitare;
	unsigned int numarFermieri;
	int* salariiFermieri;

public:
	Ferma() {
		numeFerma = "Ferma anonima";
		numarCulturi = 0;
		c = nullptr;
		numarCulturiIrigate = 0;
		ci = nullptr;
		capacitateDepozitare = 0;
		numarFermieri = 0;
		salariiFermieri = nullptr;
	}

	Ferma(string numeFerma, int numarCulturi, Cultura* c, int numarCulturiIrigate, CulturaIrigata* ci, double capacitateDepozitare, unsigned int numarFermieri, int* salariiFermieri) {
		this->numeFerma = numeFerma;
		this->numarCulturi = numarCulturi;
		if (numarCulturi > 0) {
			this->c = new Cultura[numarCulturi];
			for (int i = 0; i < numarCulturi; i++)
				this->c[i] = c[i];
		}
		this->numarCulturiIrigate = numarCulturiIrigate;
		if (numarCulturiIrigate > 0) {
			this->ci = new CulturaIrigata[numarCulturiIrigate];
			for (int i = 0; i < numarCulturiIrigate; i++)
				this->ci[i] = ci[i];
		}
		this->capacitateDepozitare = capacitateDepozitare;
		this->numarFermieri = numarFermieri;
		if (numarFermieri > 0) {
			this->salariiFermieri = new int[numarFermieri];
			for (int i = 0; i < numarFermieri; i++)
				this->salariiFermieri[i] = salariiFermieri[i];
		}
	}

	~Ferma() {
		if (c != NULL)
			delete[] c;
		if (ci != NULL)
			delete[] ci;
		if (salariiFermieri != NULL)
			delete[] salariiFermieri;
	}

	Ferma(const Ferma& f) {
		this->numeFerma = f.numeFerma;
		this->numarCulturi = f.numarCulturi;
		if (f.c != NULL) {
			this->c = new Cultura[numarCulturi];
			for (int i = 0; i < numarCulturi; i++)
				this->c[i] = f.c[i];
		}
		this->numarCulturiIrigate = f.numarCulturiIrigate;
		if (f.ci != NULL) {
			this->ci = new CulturaIrigata[numarCulturiIrigate];
			for (int i = 0; i < numarCulturiIrigate; i++)
				this->ci[i] = f.ci[i];
		}
		this->capacitateDepozitare = f.capacitateDepozitare;
		this->numarFermieri = f.numarFermieri;
		if (numarFermieri > 0) {
			this->salariiFermieri = new int[numarFermieri];
			for (int i = 0; i < numarFermieri; i++)
				this->salariiFermieri[i] = f.salariiFermieri[i];
		}
	}

	Ferma operator=(const Ferma& f) {
		if (this != &f) {
			this->numeFerma = f.numeFerma;
			this->numarCulturi = f.numarCulturi;
			if (f.c != NULL) {
				if (this->c != NULL)
					delete[] this->c;
				this->c = new Cultura[numarCulturi];
				for (int i = 0; i < numarCulturi; i++)
					this->c[i] = f.c[i];
			}
			this->numarCulturiIrigate = f.numarCulturiIrigate;
			if (f.ci != NULL) {
				if (this->ci != NULL)
					delete[] this->ci;
				this->ci = new CulturaIrigata[numarCulturiIrigate];
				for (int i = 0; i < numarCulturiIrigate; i++)
					this->ci[i] = f.ci[i];
			}
			this->capacitateDepozitare = f.capacitateDepozitare;
			this->numarFermieri = f.numarFermieri;
			if (numarFermieri > 0) {
				if (this->salariiFermieri != NULL)
					delete[] this->salariiFermieri;
				this->salariiFermieri = new int[numarFermieri];
				for (int i = 0; i < numarFermieri; i++)
					this->salariiFermieri[i] = f.salariiFermieri[i];
			}
		}
		else
			throw Exceptie("\nEroare autoasignare!\n");

		return *this;
	}

	friend ostream& operator<<(ostream& os, Ferma& f) {
		os << endl << "Nume ferma: " << f.numeFerma;
		os << endl << "Numar culturi fara irigatie: " << f.numarCulturi;
		if (f.numarCulturi > 0) {
			os << endl << "Culturi fara irigatie:\n";
			for (int i = 0; i < f.numarCulturi; i++)
				os << endl << f.c[i];
		}
		os << endl << "Numar culturi cu irigatie: " << f.numarCulturiIrigate << endl;
		if (f.numarCulturiIrigate > 0) {
			os << "Culturi cu irigatie:\n";
			for (int i = 0; i < f.numarCulturiIrigate; i++)
				os << endl << f.ci[i];
		}
		os << endl << "Capacitate de depozitare: " << f.capacitateDepozitare;
		os << endl << "Numar fermieri: " << f.numarFermieri << endl;
		if (f.numarFermieri > 0) {
			os << "Salariile fermierilor:\n";
			for (int i = 0; i < f.numarFermieri; i++)
				os << "Fermierul " << i << " are salariul: " << f.salariiFermieri[i] << endl;
		}

		return os;
	}

	friend ofstream& operator<<(ofstream& ofs, Ferma& f) {
		ofs << f.numeFerma;
		ofs << endl << f.numarCulturi << endl;
		if (f.numarCulturi > 0) {
			for (int i = 0; i < f.numarCulturi; i++) {
				ofs << f.c[i];
				ofs << endl;
			}


		}
		ofs << f.numarCulturiIrigate;
		if (f.numarCulturiIrigate > 0) {
			for (int i = 0; i < f.numarCulturiIrigate; i++)
				ofs << endl << f.ci[i];
		}
		ofs << endl << f.capacitateDepozitare;
		ofs << endl << f.numarFermieri;
		if (f.numarFermieri > 0) {
			for (int i = 0; i < f.numarFermieri; i++)
				ofs << endl << f.salariiFermieri[i];
		}

		return ofs;
	}

	friend istream& operator>>(istream& is, Ferma& f) {
		if (f.salariiFermieri != nullptr) {
			delete[] f.salariiFermieri;
		}
		
		cout << "Introduceti numele fermei: ";
		//getchar();
		is >> f.numeFerma; // !!!!!!!!!!!!!!!!!! nu pot citi cu spatiu

		cout << "Introduceti numarul de culturi fara irigatie: ";
		is >> f.numarCulturi;

		if (f.numarCulturi > 0) {
			if (f.c != NULL)
				delete[] f.c;
			f.c = new Cultura[f.numarCulturi];
			for (int i = 0; i < f.numarCulturi; i++)
				is >> f.c[i];
		}

		cout << "Introduceti numarul de culturi cu irigatie: ";
		is >> f.numarCulturiIrigate;

		if (f.numarCulturiIrigate > 0) {
			if (f.ci != NULL)
				delete[] f.ci;
			f.ci = new CulturaIrigata[f.numarCulturiIrigate];
			for (int i = 0; i < f.numarCulturiIrigate; i++)
				is >> f.ci[i];
		}

		cout << "Introduceti capacitatea de depozitare: ";
		is >> f.capacitateDepozitare;

		cout << "Introduceti numarul de fermieri: ";
		is >> f.numarFermieri;
		f.salariiFermieri = new int[f.numarFermieri];
		if (f.numarFermieri > 0) {
			cout << "Introduceti salariile celor " << f.numarFermieri << " fermieri: ";
			for (int i = 0; i < f.numarFermieri; i++)
				is >> f.salariiFermieri[i];
		}

		return is;
	}

	friend ifstream& operator>>(ifstream& ifs, Ferma& f) {
		//getchar();
		ifs >> f.numeFerma; // !!!!!!!!!!!!!!!!!! nu pot citi cu spatiu
		ifs >> f.numarCulturi;

		if (f.numarCulturi > 0) {
			if (f.c != NULL)
				delete[] f.c;
			f.c = new Cultura[f.numarCulturi];
			for (int i = 0; i < f.numarCulturi; i++) {
				string junk; getline(ifs, junk);
				ifs >> f.c[i];
			}

		}

		ifs >> f.numarCulturiIrigate;

		if (f.numarCulturiIrigate > 0) {
			if (f.ci != NULL)
				delete[] f.ci;
			f.ci = new CulturaIrigata[f.numarCulturiIrigate];
			for (int i = 0; i < f.numarCulturiIrigate; i++)
				ifs >> f.ci[i];
		}

		ifs >> f.capacitateDepozitare;

		ifs >> f.numarFermieri;

		if (f.numarFermieri > 0) {
			for (int i = 0; i < f.numarFermieri; i++)
				ifs >> f.salariiFermieri[i];
		}

		return ifs;
	}

	string getNumeFerma() {
		return numeFerma;
	}

	void setNumeFerma(string numeFermaNou) {
		if (numeFermaNou.size() > 2)
			numeFerma = numeFermaNou;
		else
			throw Exceptie("Numele fermei este prea scurt!");
	}

	int getNumarCulturi() {
		return numarCulturi;
	}

	/*void setNumarCulturi(int numarCulturiNou) {
		if (numarCulturiNou >= 0)
			numarCulturi = numarCulturiNou;
		else
			throw Exceptie("Numarul de culturi nu poate fi negativ!");
	}*/

	int getNumarCulturiIrigate() {
		return numarCulturiIrigate;
	}

	/*void setNumarCulturiIrigate(int numarCulturiIrigateNou) {
		if (numarCulturiIrigateNou >= 0)
			numarCulturiIrigate = numarCulturiIrigateNou;
		else
			throw Exceptie("Numarul de culturi irigate nu poate fi negativ!");
	}*/

	double getCapacitateDepozitare() {
		return capacitateDepozitare;
	}

	void setCapacitateDepozitare(double capacitateDepozitareNoua) {
		if (capacitateDepozitareNoua >= 0)
			capacitateDepozitare = capacitateDepozitareNoua;
		else
			throw Exceptie("Capacitatea de depozitare nu poate fi negativa!");
	}

	int getNumarFermieri() {
		return numarFermieri;
	}

	/*void setNumarFermieri(int numarFermieriNou) {
		if (numarFermieriNou >= 0)
			numarFermieri = numarFermieriNou;
		else
			throw Exceptie("Numarul de fermieri nu poate fi negativ!");
	}*/

	Cultura* getCultura() {
		return c;
	}

	CulturaIrigata* getCulturaIrigata() {
		return ci;
	}

	Cultura operator[](int index) {
		if (index >= 0 && index < numarCulturi)
			return c[index];
		else
			throw Exceptie("Index in afara intervalului!");
	}

	Ferma operator++() {
		Cultura c1;
		adaugareCulturaNeirigata(c1);
		return *this;
	}

	Ferma operator++(int) {
		Ferma aux = *this;
		Cultura c1;
		adaugareCulturaNeirigata(c1);
		return aux;
	}

	Ferma operator--() {
		if (numarCulturi > 0) {
			stergereCulturaNeirigata(numarCulturi - 1);
			return *this;
		}
		else
			throw Exceptie("Nu exista culturi neirigate!");
	}

	Ferma operator--(int) {
		if (numarCulturi > 0) {
			Ferma aux = *this;
			stergereCulturaNeirigata(numarCulturi - 1);
			return aux;
		}
		else
			throw Exceptie("Nu exista culturi neirigate!");

	}

	bool operator!() {
		if (numarCulturi == 0 && numarCulturiIrigate == 0)
			return true;
		return false;
	}

	void adaugareCulturaNeirigata(Cultura cn) {
		if (numarCulturi > 0) {
			Cultura* aux = new Cultura[numarCulturi];
			for (int i = 0; i < numarCulturi; i++)
				aux[i] = c[i];
			delete[] c;
			numarCulturi++;
			c = new Cultura[numarCulturi];
			for (int i = 0; i < numarCulturi - 1; i++)
				c[i] = aux[i];
			c[numarCulturi - 1] = cn;
			delete[] aux;
		}
		else {
			numarCulturi++;
			if (c != NULL)
				delete[] c;
			c = new Cultura[numarCulturi];
			c[numarCulturi - 1] = cn;
		}
	}

	void stergereCulturaNeirigata(int index) {
		if (index >= 0 && index < numarCulturi) {
			int k = 0;
			Cultura* aux = new Cultura[numarCulturi - 1];
			for (int i = 0; i < numarCulturi; i++)
				if (i != index) {
					aux[k] = c[i];
					k++;
				}
			delete[] c;
			numarCulturi--;
			c = new Cultura[numarCulturi];
			for (int i = 0; i < numarCulturi; i++)
				c[i] = aux[i];
			delete[] aux;
		}
	}

	void adaugareCulturaIrigata(CulturaIrigata cIr) {
		if (numarCulturiIrigate > 0) {
			CulturaIrigata* aux = new CulturaIrigata[numarCulturiIrigate];
			for (int i = 0; i < numarCulturiIrigate; i++)
				aux[i] = ci[i];
			delete[] ci;
			numarCulturiIrigate++;
			ci = new CulturaIrigata[numarCulturiIrigate];
			for (int i = 0; i < numarCulturiIrigate - 1; i++)
				ci[i] = aux[i];
			ci[numarCulturiIrigate - 1] = cIr;
			delete[] aux;
		}
		else
		{
			numarCulturiIrigate++;
			if (ci != NULL)
				delete[] ci;
			ci = new CulturaIrigata[numarCulturiIrigate];
			ci[numarCulturiIrigate - 1] = cIr;
		}
	}

	void stergereCulturaIrigata(int index) {
		if (index >= 0 && index < numarCulturiIrigate) {
			int k = 0;
			CulturaIrigata* aux = new CulturaIrigata[numarCulturiIrigate - 1];
			for (int i = 0; i < numarCulturiIrigate; i++)
				if (i != index) {
					aux[k] = ci[i];
					k++;
				}
			delete[] ci;
			numarCulturiIrigate--;
			ci = new CulturaIrigata[numarCulturiIrigate];
			for (int i = 0; i < numarCulturiIrigate; i++)
				ci[i] = aux[i];
			delete[] aux;
		}
	}

	double valoareFerma() {
		double valoare = 0;
		for (int i = 0; i < numarCulturi; i++)
			valoare += c[i].valoareCultura();
		for (int i = 0; i < numarCulturiIrigate; i++)
			valoare += ci[i].valoareCultura();

		return valoare;
	}

	double* valoareFiecareCultura() {
		int nr = numarCulturi + numarCulturiIrigate;
		double* valoare = new double[nr];
		int k = 0;
		for (int i = 0; i < numarCulturi; i++) {
			valoare[k] = c[i].valoareCultura();
			k++;
		}
		for (int i = 0; i < numarCulturiIrigate; i++) {
			valoare[k] = ci[i].valoareCultura();
			k++;
		}
		return valoare;
	}

	int ceaMaiMareValoare() {
		int id = -1;
		double valoare = -1;
		for (int i = 0; i < numarCulturi; i++)
			if (c[i].valoareCultura() > valoare) {
				valoare = c[i].valoareCultura();
				id = c[i].getIdCultura();
			}
		return id;
	}
};

int main() {

	/*ofstream fisOut("fisier.txt", ios::out);
	fisOut << c;
	fisOut.close();*/

	/*ifstream fisIn("fisier.txt", ios::in);
	fisIn >> c1;
	fisIn.close();
	cout << c1;*/

	/*ofstream fisOut("fisier1.txt", ios::out);
	fisOut << ci;
	fisOut.close();*/

	/*ifstream fisIn("fisier1.txt", ios::in);
	fisIn >> ci;
	fisIn.close();
	cout << ci;*/

	/*ofstream fisOut("fisier2.txt", ios::out);
	fisOut << f;
	fisOut.close();*/

	/*ifstream fisIn("fisier2.txt", ios::in);
	fisIn >> f;
	fisIn.close();
	cout << f;*/

	Cultura c;
	CulturaIrigata ci;
	Ferma f;
	int k = -1, index;
	double valoare = 0.0f;
	cin >> f;
	while (k != 0)
	{
		cout << "\nAlegeti una din optiunile urmatoare:\n";
		cout << "0 - Iesire\n";
		cout << "1 - Adaugare cultura neirigata\n";
		cout << "2 - Adaugare cultura irigata\n";
		cout << "3 - Stergere cultura neirigata\n";
		cout << "4 - Stergere cultura irigata\n";
		cout << "5 - Determinarea valorii fiecarei culturi\n";
		cout << "6 - Determinarea valorii realizate de ferma\n";
		cout << "7 - Determinarea culturii care genereaza cea mai mare valoare\n";
		cin >> k;
		switch (k)
		{
		case 1:
			cin >> c;
			f.adaugareCulturaNeirigata(c);
			cout << "\nCultura a fost adaugata!\n";
			break;
		case 2:
			cin >> ci;
			f.adaugareCulturaIrigata(ci);
			cout << "\nCultura a fost adaugata!\n";
			break;
		case 3:
			cout << "Introduceti index: ";
			cin >> index;
			f.stergereCulturaNeirigata(index);
			cout << "\nCultura a fost stearsa!\n";
			break;
		case 4:
			cout << "Introduceti index: ";
			cin >> index;
			f.stergereCulturaIrigata(index);
			cout << "\nCultura a fost stearsa!\n";
			break;
		case 5:
			if (f.getNumarCulturi() > 0 || f.getNumarCulturiIrigate() > 0) {
				for (int i = 0; i < f.getNumarCulturi(); i++)
					cout << "Cultura neirigata " << i + 1 << " are valoarea: " << f.getCultura()[i].valoareCultura() << endl;
				for (int i = 0; i < f.getNumarCulturiIrigate(); i++)
					cout << "Cultura irigata " << i + 1 << " are valoarea: " << f.getCulturaIrigata()[i].valoareCultura() << endl;
			}
			else
				cout << "Nu exista nicio cultura adaugata!\n";
			break;
		case 6:
			valoare = 0;
			for (int i = 0; i < f.getNumarCulturi(); i++)
				valoare += f.getCultura()[i].valoareCultura();
			for (int i = 0; i < f.getNumarCulturiIrigate(); i++)
				valoare += f.getCulturaIrigata()[i].valoareCultura();
			cout << "Ferma dvs are o valoare totala de: " << valoare << endl;
			break;
		case 7:
			if (f.getNumarCulturi() > 0 || f.getNumarCulturiIrigate() > 0) {
				cout << "Cultura cu cea mai mare valoare este:\n";
				for (int i = 0; i < f.getNumarCulturi(); i++)
					if (f.getCultura()[i].getIdCultura() == f.ceaMaiMareValoare())
						cout << f.getCultura()[i];
				for (int i = 0; i < f.getNumarCulturiIrigate(); i++)
					if (f.getCulturaIrigata()[i].getIdCultura() == f.ceaMaiMareValoare())
						cout << f.getCultura()[i];
			}
			else
				cout << "Nu exista nicio cultura adaugata!\n";

			break;
		default:
			k = 0;
			break;
		}
	}

	cout << f;

	return 0;
}

//Aplicatie pentru gestiunea culturilor dintr - o ferma agricola.Pentru fiecare cultura se vor stoca date referitoare 
//la tipul de cultura, suprafata cultivata, productia medie la ha, pretul pe unitate etc.Se vor implementa opratii de 
//adaugare / actualizare culturi in cadrul fermei, determinarea valorii fiecarei culturi, valoarea realizata de ferma si 
//cultura care genereaza cea mai mare valoare.