#include<iostream>
#include<string>

using namespace std;

class ScaraDeBloc
{
private:
	string denumire;
	char* adresa;
	int nrApartamente;
	int* locatari;

public:
	const int idScara;
	static int contor;

	string getDenumire()
	{
		return this->denumire;
	}
	void setDenumire(string denumire)
	{
		this->denumire = denumire;
	}
	const char* getAdresa()
	{
		return this->adresa;
	}
	void setAdresa(const char* adresa)
	{
		if (adresa != nullptr)
		{
			delete[] this->adresa;
		}
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
	}
	int getNrApartamente()
	{
		return this->nrApartamente;
	}
	/*int* getLocatari()
	{
		return this->locatari;
	}*/
	int* getLocatari()
	{
		if (nrApartamente > 0 && locatari != nullptr)
		{
			int* copie = new int[nrApartamente];
			for (int i = 0; i < nrApartamente; i++)
			{
				copie[i] = locatari[i];
			}
			return copie;
		}
		else
		{
			return nullptr;
		}
	}
	int& operator[](int index)
	{
		return this->locatari[index];
	}
	void setLocatari(int nrApartamente, int* locatari)
	{
		this->nrApartamente = nrApartamente;
		this->locatari = new int[nrApartamente];
		for (int i = 0; i < nrApartamente; i++)
		{
			this->locatari[i] = locatari[i];
		}
	}
	ScaraDeBloc() : idScara(contor++)
	{
		this->denumire = "AAA";
		this->adresa = new char[strlen("Dorobanti") + 1];
		strcpy(this->adresa, "Dorobanti");
		this->nrApartamente = 2;
		this->locatari = new int[2];
		this->locatari[0] = 3;
		this->locatari[1] = 2;
	}
	ScaraDeBloc(string denumire, const char* adresa, int nrApartamente, int* locatari) : idScara(contor++)
	{
		this->denumire = denumire;
		this->adresa = new char[strlen(adresa) + 1];
		strcpy(this->adresa, adresa);
		this->nrApartamente = nrApartamente;
		this->locatari = new int[nrApartamente];
		for (int i = 0; i < nrApartamente; i++)
		{
			this->locatari[i] = locatari[i];
		}
	}
	ScaraDeBloc(const ScaraDeBloc& s) : idScara(contor++)
	{
		this->denumire = s.denumire;
		this->adresa = new char[strlen(s.adresa) + 1];
		strcpy(this->adresa, s.adresa);
		this->nrApartamente = s.nrApartamente;
		this->locatari = new int[s.nrApartamente];
		for (int i = 0; i < s.nrApartamente; i++)
		{
			this->locatari[i] = s.locatari[i];
		}
	}
	~ScaraDeBloc()
	{
		if (adresa != nullptr)
		{
			delete[] this->adresa;
		}
		if (locatari != nullptr)
		{
			delete[] this->locatari;
		}
	}
	ScaraDeBloc& operator=(const ScaraDeBloc& s)
	{
		this->denumire = s.denumire;
		if (adresa != nullptr)
		{
			delete[] this->adresa;
		}
		this->adresa = new char[strlen(s.adresa) + 1];
		strcpy(this->adresa, s.adresa);
		if (locatari != nullptr)
		{
			delete[] this->locatari;
		}
		this->nrApartamente = s.nrApartamente;
		this->locatari = new int[s.nrApartamente];
		for (int i = 0; i < s.nrApartamente; i++)
		{
			this->locatari[i] = s.locatari[i];
		}

		return *this;
	}

	friend ostream& operator<<(ostream& out, ScaraDeBloc s);

	virtual void afisare()
	{
		cout << *this;
	}

	int sumaLocatari()
	{
		int suma = 0;
		for (int i = 0; i < nrApartamente; i++)
		{
			suma += this->locatari[i];
		}

		return suma;
	}
};
int ScaraDeBloc::contor = 1;

ostream& operator<<(ostream& out, ScaraDeBloc s)
{
	out << "Denumire: " << s.denumire << endl;
	out << "Adresa: " << s.adresa << endl;
	out << "Nr apartamente: " << s.nrApartamente << endl;
	out << "Locatari: ";
	for (int i = 0; i < s.nrApartamente; i++)
	{
		out << s.locatari[i] << " ";
	}
	out << endl;
	return out;
}

class Bloc
{
public:
	ScaraDeBloc** vector;
	int dim;

	Bloc()
	{
		this->dim = 2;
		this->vector = new ScaraDeBloc * [2];
		this->vector[0] = new ScaraDeBloc();
		this->vector[1] = new ScaraDeBloc();

	}
	Bloc(int dim, ScaraDeBloc** vector)
	{
		this->dim = dim;
		this->vector = new ScaraDeBloc * [dim];
		for (int i = 0; i < dim; i++)
		{
			this->vector[i] = vector[i];
		}
	}

	Bloc(const Bloc& b)
	{
		this->dim = b.dim;
		this->vector = new ScaraDeBloc * [b.dim];
		for (int i = 0; i < b.dim; i++)
		{
			this->vector[i] = b.vector[i];
		}
	}
	Bloc& operator=(const Bloc& b)
	{
		this->dim = b.dim;
		this->vector = new ScaraDeBloc * [b.dim];
		for (int i = 0; i < b.dim; i++)
		{
			this->vector[i] = b.vector[i];
		}

		return *this;
	}
	Bloc& operator+=(ScaraDeBloc& s)
	{
		int dimNou = dim + 1;
		ScaraDeBloc** copieVector = new ScaraDeBloc * [dimNou];
		for (int i = 0; i < dim; i++)
		{
			copieVector[i] = this->vector[i];
		}
		copieVector[dimNou - 1] = &s;

		if (vector != nullptr)
		{
			delete[] vector;
		}
		this->dim = dimNou;
		this->vector = new ScaraDeBloc * [dimNou];
		for (int i = 0; i < dim; i++)
		{
			this->vector[i] = copieVector[i];
		}

		return *this;
	}

	ScaraDeBloc scaraProductiva()
	{
		int max = 0;
		ScaraDeBloc rezultat;

		for (int i = 0; i < dim; i++)
		{
			if (max < this->vector[i]->sumaLocatari())
			{
				max = this->vector[i]->sumaLocatari();
				rezultat = *(this->vector[i]);
			}
		}
		return rezultat;

	}

	ScaraDeBloc scaraNeproductiva()
	{
		int min = 0;
		ScaraDeBloc rezultat;

		for (int i = 0; i < dim; i++)
		{
			if (min > this->vector[i]->sumaLocatari())
			{
				min = this->vector[i]->sumaLocatari();
				rezultat = *(this->vector[i]);
			}
		}
		return rezultat;
	}

	friend ostream& operator<<(ostream& out, Bloc b);
};
ostream& operator<<(ostream& out, Bloc b)
{
	out << "Dimensiune: " << b.dim << endl;
	out << "Vector: " << endl;;
	for (int i = 0; i < b.dim; i++)
	{
		b.vector[i]->afisare();
		// early binding
	}
	out << endl;
	return out;
}
int main()
{
	// constructor implicit
	ScaraDeBloc s1;
	cout << s1 << endl;

	// constructor cu parametri
	int vector[] = { 1, 3, 2, 1, 4 };
	int vector2[] = { 3, 1 };

	ScaraDeBloc s2("BBB", "Dristor", 5, vector);
	cout << s2 << endl;

	// setter
	s2.setLocatari(2, vector2);
	cout << s2 << endl;

	// operator[]
	s2[0] = 2;
	cout << s2 << endl;

	ScaraDeBloc s3("CCC", "Unirii", 5, vector);
	cout << s3 << endl;

	ScaraDeBloc s4("DDD", "Pacii", 2, vector2);
	cout << s4 << endl;

	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;

	// constructor cu parametri
	Bloc b1(2, new ScaraDeBloc * [2]{ &s1, &s2 });
	cout << b1 << endl;

	// constructor implicit
	Bloc b2;
	cout << b2 << endl;

	Bloc b3(1, new ScaraDeBloc * [1]{ &s3 });
	cout << b3 << endl;

	Bloc b4(3, new ScaraDeBloc * [3]{ &s2, &s3, &s4 });
	cout << "     Bloc 4" << endl;
	cout << b4 << endl;

	// operator+=
	b3 += s4;
	cout << "     Bloc 3" << endl;
	cout << b3 << endl;

	ScaraDeBloc s5 = b1.scaraProductiva();
	cout << s5 << endl;

	ScaraDeBloc s6 = b3.scaraNeproductiva();
	cout << s6 << endl;

}