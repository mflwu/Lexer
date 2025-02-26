// implement automaton class

#include "automate.h"
#include <iostream>
using namespace std;

void Automate::lecture()
{
    cout << "Automate starting lecture..." << endl;
    // Start with the initial state E0
    Etat *e = new E0();
    etats.push_back(e);
    afficherStack();

    // Use the lexer to get the first symbol
    Symbole *s = lexer->Consulter();

    // Loop until we reach the FIN symbol or input is accepted
    while (!accepte)
    {
        cout << "Current Symbol: ";
        s->Affiche();
        cout << endl;
        // Process the transition from the top state
        if (!etats.back()->transition(*this, s))
        {
            cout << "Error: No valid transition for symbol ";
            s->Affiche();
            cout << endl;
            break;
        }
        afficherStack();
        s = lexer->Consulter();
    }

    if (accepte)
        cout << "Input accepted!" << endl;
    else
        cout << "Input not accepted!" << endl;
}

void Automate::transitionSimple(Symbole *s, Etat *e)
{
    cout << "[TransitionSimple] Adding symbol ";
    s->Affiche();
    cout << " and state " << e->getName() << endl;
    symboles.push_back(s);
    etats.push_back(e);
}

void Automate::decalage(Symbole *s, Etat *e)
{
    cout << "[Decalage] Shifting symbol ";
    s->Affiche();
    cout << " and state " << e->getName() << endl;
    symboles.push_back(s);
    etats.push_back(e);
    lexer->Avancer();
}

void Automate::reduction(int n, Symbole *s)
{
    cout << "[Reduction] Reducing by " << n << " symbols, new symbol: ";
    s->Affiche();
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Popping state: " << etats.back()->getName() << endl;
        delete etats.back();
        etats.pop_back();
    }
    etats.back()->transition(*this, s);
}

void Automate::acceptation()
{
    cout << "[Acceptation] The input is accepted!" << endl;
    accepte = true;
}

Symbole *Automate::popSymbole()
{
    cout << "[PopSymbol] Popping symbol: ";
    symboles.back()->Affiche();
    cout << endl;
    Symbole *s = symboles.back();
    symboles.pop_back();
    return s;
}

void Automate::popAndDestroySymbole()
{
    cout << "[PopAndDestroySymbol] Removing symbol: ";
    symboles.back()->Affiche();
    cout << endl;
    delete symboles.back();
    symboles.pop_back();
}