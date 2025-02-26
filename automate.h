#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "etats.h"
#include "lexer.h"
#include "symbole.h"

using namespace std;

class Automate
{
public:
    Automate(string s) : lexer(new Lexer(s)), accepte(false) {}
    Automate(Lexer *l) : lexer(l), accepte(false) {}
    ~Automate() {}

    void lecture();

    void transitionSimple(Symbole *s, Etat *e);
    void decalage(Symbole *s, Etat *e);
    void reduction(int n, Symbole *s);
    void acceptation();
    Symbole *popSymbole();
    void popAndDestroySymbole();
    void afficherStack()
    {
        cout << "=== Current Automate Stack ===" << endl;
        cout << "Symboles: ";
        for (auto sym : symboles)
        {
            sym->Affiche();
            cout << " ";
        }
        cout << endl;
        cout << "Etats: ";
        for (auto etat : etats)
        {
            cout << etat->getName() << " ";
        }
        cout << endl;
    }

    Symbole *getResult() const
    {
        return symboles.empty() ? nullptr : symboles.back();
    }

    bool isAccepted() const
    {
        return accepte;
    }

protected:
    Lexer *lexer;
    vector<Symbole *> symboles;
    vector<Etat *> etats;
    bool accepte;
};
