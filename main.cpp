#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class IBilet {
public:
    virtual int calculeazaDurata() const = 0;
    virtual double calculeazaCost() const = 0;
    virtual string getTip() const = 0;
    virtual string getNumar() const = 0;
    virtual ~IBilet() {}
};

class Bilet : public IBilet {
protected:
    string numar;
    string oraStart;
    string oraSfarsit;
public:
    Bilet(string numar, string oraStart, string oraSfarsit) {
        this->numar = numar;
        this->oraStart = oraStart;
        this->oraSfarsit = oraSfarsit;
    }

    int calculeazaDurata() const override {
        int hStart, mStart, hSfarsit, mSfarsit;
        char sep;
        stringstream ss1(oraStart);
        ss1 >> hStart >> sep >> mStart;
        stringstream ss2(oraSfarsit);
        ss2 >> hSfarsit >> sep >> mSfarsit;
        return (hSfarsit * 60 + mSfarsit) - (hStart * 60 + mStart);
    }

    virtual double calculeazaCost() const = 0;
    virtual string getTip() const = 0;

    string getNumar() const override {
        return numar;
    }

    virtual ~Bilet() {}
};

class BiletStandard : public Bilet {
private:
    double costPeOra = 2.0;
public:
    BiletStandard(string numar, string oraStart, string oraSfarsit)
        : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() const override {
    int durata = calculeazaDurata();
    int ore = (durata + 59) / 60; 
    return ore * costPeOra;
    }

    string getTip() const override { 
        return "Bilet Standard"; 
    }
};

class Abonament : public Bilet {
private:
    double costAbonament = 50.0;
public:
    Abonament(string numar, string oraStart, string oraSfarsit)
        : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() const override { 
        return costAbonament; 
    }

    string getTip() const override { 
        return "Abonament"; 
    }
};

class BiletReducere : public Bilet {
private:
    double costPeOra = 1.0;
public:
    BiletReducere(string numar, string oraStart, string oraSfarsit)
        : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() const override {
        return (calculeazaDurata() / 60.0) * costPeOra;
    }

    string getTip() const override { 
        return "Bilet Reducere"; 
    }
};

class BiletTuristic : public Bilet {
private:
    double costPeZi = 10.0;
public:
    BiletTuristic(string numar, string oraStart, string oraSfarsit)
        : Bilet(numar, oraStart, oraSfarsit) {}

    double calculeazaCost() const override { 
        return costPeZi; 
    }

    string getTip() const override { 
        return "Bilet Turistic"; 
    }
};

int main() {
    vector<IBilet*> bilete;
    string tip, numar, oraStart, oraSfarsit;

    ifstream fisier("bilete.txt");
    if (!fisier.is_open()) {
        cout << "Eroare: nu s-a putut deschide fisierul bilete.txt";
        return 0;
    }

    while (fisier >> tip >> numar >> oraStart >> oraSfarsit) {
        if (tip == "BiletStandard")
            bilete.push_back(new BiletStandard(numar, oraStart, oraSfarsit));
        else if (tip == "Abonament")
            bilete.push_back(new Abonament(numar, oraStart, oraSfarsit));
        else if (tip == "BiletReducere")
            bilete.push_back(new BiletReducere(numar, oraStart, oraSfarsit));
        else if (tip == "BiletTuristic")
            bilete.push_back(new BiletTuristic(numar, oraStart, oraSfarsit));
    }
    fisier.close();

    for (int i = 0; i < bilete.size(); i++) {
        cout << "Tip: " << bilete[i]->getTip() << endl;
        cout << "Numar: " << bilete[i]->getNumar() << endl;
        cout << "Durata: " << bilete[i]->calculeazaDurata() << " minute" << endl;
        cout << "Cost: " << bilete[i]->calculeazaCost() << " lei" << endl;
        cout << endl;
    }

    for (int i = 0; i < bilete.size(); i++)
        delete bilete[i];

    return 0;
}
