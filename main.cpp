#include <iostream>
#include "lexer.h"
#include "automate.h"
#include "symbole.h" // for Expression and derived classes
#include <map>

using namespace std;

int main()
{
   string chaine("5*13+(9+(5+34)*2)");
   cout << "Input: " << chaine << endl;

   // Create the lexer with the input string
   Lexer l(chaine);

   // Create the automate and pass the lexer pointer
   Automate automate(&l);

   // Run the parsing process
   automate.lecture();

   // If the input was accepted, get the result and evaluate it
   if (automate.isAccepted())
   {
      Symbole *resultSymbol = automate.getResult();
      // Cast the final symbol to an Expression
      Expression *expr = dynamic_cast<Expression *>(resultSymbol);
      if (expr)
      {
         // Assuming no variables are used, pass an empty map
         double value = expr->eval(map<string, double>());
         cout << "Calculated value: " << value << endl;
      }
      else
      {
         cout << "Final symbol is not a valid expression." << endl;
      }
   }
   else
   {
      cout << "Input not accepted!" << endl;
   }

   return 0;
}
