#include "symbole.h"
#include <iostream>

void Symbole::Affiche()
{
   cout << Etiquettes[ident];
}

void Entier::Affiche()
{
   Symbole::Affiche();
   cout << "(" << valeur << ")";
}

double ExprPlus::eval(const map<string, double> &valeurs)
{
   return exp1->eval(valeurs) + exp2->eval(valeurs);
}

double ExprMult::eval(const map<string, double> &valeurs)
{
   return exp1->eval(valeurs) * exp2->eval(valeurs);
}

double ExprPar::eval(const map<string, double> &valeurs)
{
   return exp->eval(valeurs);
}

double ExprVal::eval(const map<string, double> &valeurs)
{
   return entier->getValeur();
}
