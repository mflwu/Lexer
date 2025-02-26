#pragma once

#include <string>
#include <map>
using namespace std;

enum Identificateurs
{
   OPENPAR,
   CLOSEPAR,
   PLUS,
   MULT,
   INT,
   FIN,
   EXPR,
   ERREUR
};

const string Etiquettes[] = {"OPENPAR", "CLOSEPAR", "PLUS", "MULT", "INT", "FIN", "EXPR", "ERREUR"};

class Symbole
{
public:
   Symbole(int i) : ident(i) {}
   virtual ~Symbole() {}
   operator int() const { return ident; }
   virtual void Affiche();

protected:
   int ident;
};

class Entier : public Symbole
{
public:
   Entier(int v) : Symbole(INT), valeur(v) {}
   ~Entier() {}
   virtual void Affiche();
   int getValeur() { return valeur; }

protected:
   int valeur;
};

class Expression : public Symbole
{
public:
   Expression() : Symbole(EXPR) {}
   ~Expression() {}
   virtual double eval(const map<string, double> &valeurs) = 0;
};

class ExprPlus : public Expression
{
public:
   ExprPlus(Expression *e1, Expression *e2) : Expression(), exp1(e1), exp2(e2) {}
   ~ExprPlus() {}
   virtual double eval(const map<string, double> &valeurs);

protected:
   Expression *exp1;
   Expression *exp2;
};

class ExprMult : public Expression
{
public:
   ExprMult(Expression *e1, Expression *e2) : Expression(), exp1(e1), exp2(e2) {}
   ~ExprMult() {}
   virtual double eval(const map<string, double> &valeurs);

protected:
   Expression *exp1;
   Expression *exp2;
};

class ExprVal : public Expression
{
public:
   ExprVal(Entier *e) : Expression(), entier(e) {}
   ~ExprVal() {}
   virtual double eval(const map<string, double> &valeurs);

protected:
   Entier *entier;
};

class ExprPar : public Expression
{
public:
   ExprPar(Expression *e) : Expression(), exp(e) {}
   ~ExprPar() {}
   virtual double eval(const map<string, double> &valeurs);

protected:
   Expression *exp;
};