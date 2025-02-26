// implement the class Etats

#include "etats.h"
#include "automate.h"

#include <iostream>
using namespace std;

void Etat::Affiche() const
{
    cout << name << endl;
}

bool E0::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new E3());
        break;
    case OPENPAR:
        automate.decalage(s, new E2());
        break;
    case EXPR:
        automate.transitionSimple(s, new E1());
        break;
    default:
        return false;
    }
    return true;
}

bool E1::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
        automate.decalage(s, new E4());
        break;
    case MULT:
        automate.decalage(s, new E5());
        break;
    case FIN:
        automate.acceptation();
        break;
    default:
        return false;
    }
    return true;
}

bool E2::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new E3());
        break;
    case OPENPAR:
        automate.decalage(s, new E2());
        break;
    case EXPR:
        automate.transitionSimple(s, new E6());
        break;
    default:
        return false;
    }
    return true;
}

bool E3::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
    {
        Entier *s1 = (Entier *)automate.popSymbole();
        automate.reduction(1, new ExprVal(s1));
        break;
    }
    case MULT:
    {
        Entier *s1 = (Entier *)automate.popSymbole();
        automate.reduction(1, new ExprVal(s1));
        break;
    }
    case CLOSEPAR:
    {
        Entier *s1 = (Entier *)automate.popSymbole();
        automate.reduction(1, new ExprVal(s1));
        break;
    }
    case FIN:
    {
        Entier *s1 = (Entier *)automate.popSymbole();
        automate.reduction(1, new ExprVal(s1));
        break;
    }
    default:
        return false;
    }
    return true;
}

bool E4::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new E3());
        break;
    case OPENPAR:
        automate.decalage(s, new E2());
        break;
    case EXPR:
        automate.transitionSimple(s, new E7());
        break;
    default:
        return false;
    }
    return true;
}

bool E5::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case INT:
        automate.decalage(s, new E3());
        break;
    case OPENPAR:
        automate.decalage(s, new E2());
        break;
    case EXPR:
        automate.transitionSimple(s, new E8());
        break;
    default:
        return false;
    }
    return true;
}

bool E6::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
        automate.decalage(s, new E4());
        break;
    case MULT:
        automate.decalage(s, new E5());
        break;
    case CLOSEPAR:
        automate.decalage(s, new E9());
        break;
    default:
        return false;
    }
    return true;
}

bool E7::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
    {
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        Expression *s2 = (Expression *)automate.popSymbole();
        automate.reduction(3, new ExprPlus(s2, s1));
        break;
    }
    case MULT:
        automate.decalage(s, new E5());
        break;
    case CLOSEPAR:
    {
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        Expression *s2 = (Expression *)automate.popSymbole();
        automate.reduction(3, new ExprPlus(s2, s1));
        break;
    }
    case FIN:
    {
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        Expression *s2 = (Expression *)automate.popSymbole();
        automate.reduction(3, new ExprPlus(s2, s1));
        break;
    }
    default:
        return false;
    }
    return true;
}

bool E8::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
    {
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        Expression *s2 = (Expression *)automate.popSymbole();
        automate.reduction(3, new ExprMult(s2, s1));
        break;
    }
    case MULT:
    {
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        Expression *s2 = (Expression *)automate.popSymbole();
        automate.reduction(3, new ExprMult(s2, s1));
        break;
    }
    case CLOSEPAR:
    {
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        Expression *s2 = (Expression *)automate.popSymbole();
        automate.reduction(3, new ExprMult(s2, s1));
        break;
    }
    case FIN:
    {
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        Expression *s2 = (Expression *)automate.popSymbole();
        automate.reduction(3, new ExprMult(s2, s1));
        break;
    }
    default:
        return false;
    }
    return true;
}

bool E9::transition(Automate &automate, Symbole *s)
{
    switch (*s)
    {
    case PLUS:
    {
        automate.popAndDestroySymbole();
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        automate.reduction(3, new ExprPar(s1));
        break;
    }
    case MULT:
    {
        automate.popAndDestroySymbole();
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        automate.reduction(3, new ExprPar(s1));
        break;
    }
    case CLOSEPAR:
    {
        automate.popAndDestroySymbole();
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        automate.reduction(3, new ExprPar(s1));
        break;
    }
    case FIN:
    {
        automate.popAndDestroySymbole();
        Expression *s1 = (Expression *)automate.popSymbole();
        automate.popAndDestroySymbole();
        automate.reduction(3, new ExprPar(s1));
        break;
    }
    default:
        return false;
    }
    return true;
}
