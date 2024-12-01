#pragma once
#include"Stack.h"

class Expression
{

public:

    static void Verifier_Exp(const string& exp);
    static double Calculatrice(const string expression);

private:
    static bool Priorite(char op1, char op2);
    static void EvaluerUneOperation(Stack<char>& operators, Stack<double>& operands);

};





void Expression::Verifier_Exp(const string& exp)
{
    Stack<char> stack;

    for (char ch : exp)
    {
        if (ch == '(' || ch == '[' || ch == '{')
        {
            stack.Empiler(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (stack.isEmpty())
            {
                cout << "Erreur : Parenth�se fermante sans correspondance.\n";
                return;
            }

            char top = stack.Depiler();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{'))
            {
                cout << "Erreur : Parenth�se ouvrante et fermante incompatibles.\n";
                return;
            }
        }
    }

    if (!stack.isEmpty())
    {
        cout << "Erreur : Parenth�se ouvrante sans correspondance.\n";
    }
    else
    {
        cout << "L'expression est bien Equilibree.\n";
    }
}



bool Expression::Priorite(char op1, char op2)
{
    // Si op1 a une priorit� sup�rieure ou �gale � op2, on le d�pile
    if ((op1 == '*' || op1 == '/') && (op2 == '+' || op2 == '-'))
    {
        return true;
    }
    if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-'))
    {
        return true;
    }
    return false;
}




void Expression::EvaluerUneOperation(Stack<char>& operators, Stack<double>& operands)
{
    // R�cup�re les deux derniers op�randes et l'op�rateur du sommet des piles
    double val2 = operands.Depiler();
    double val1 = operands.Depiler();
    char op = operators.Depiler();

    // Effectue l'op�ration en fonction de l'op�rateur
    double result;
    switch (op)
    {
    case '+': result = val1 + val2; break;
    case '-': result = val1 - val2; break;
    case '*': result = val1 * val2; break;
    case '/':
        if (val2 == 0)
        {
            throw std::runtime_error("Erreur : Division par z�ro");
        }
        result = val1 / val2;
        break;
    default: throw std::runtime_error("Erreur : Op�rateur inconnu");
    }

    // Empile le r�sultat
    operands.Empiler(result);
}




double Expression::Calculatrice(const string expression)
{
    Stack<char> operators;  // Pile pour les op�rateurs
    Stack<double> operands; // Pile pour les op�randes (nombres)

    int i = 0;
    while (i < expression.length())
    {
        char ch = expression[i];

        // Ignore les espaces
        if (isspace(ch))
        {
            i++;
            continue;
        }

        // Si le caract�re est un chiffre
        if (isdigit(ch))
        {
            double num = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0'); // Construire le nombre
                i++;
            }
            operands.Empiler(num); // Empiler l'op�rande (le nombre)
            //cout << "Empile op�rande : " << num << endl; // Affichage pour le d�bogage
            continue;
        }

        // Si le caract�re est une parenth�se ouvrante
        if (ch == '(')
        {
            operators.Empiler(ch);
            //cout << "Empile parenth�se ouvrante : " << ch << endl; // Affichage pour d�bogage
        }
        // Si le caract�re est une parenth�se fermante
        else if (ch == ')')
        {
            while (!operators.isEmpty() && operators.Top() != '(')
            {
                EvaluerUneOperation(operators, operands); // D�piler et �valuer
            }
            operators.Depiler(); // D�piler la parenth�se ouvrante '('
            //cout << "D�pile parenth�se ouvrante : (" << endl; // Affichage pour d�bogage
        }
        // Si le caract�re est un op�rateur
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            while (!operators.isEmpty() && Priorite(operators.Top(), ch))
            {
                EvaluerUneOperation(operators, operands); // D�piler et �valuer si n�cessaire
            }
            operators.Empiler(ch); // Empiler l'op�rateur
            //cout << "Empile op�rateur : " << ch << endl; // Affichage pour d�bogage
        }
        else
        {
            throw std::runtime_error("Erreur : Caract�re invalide dans l'expression");
        }

        i++; // Passer � l'�l�ment suivant
    }

    // D�piler les op�rateurs restants et �valuer
    while (!operators.isEmpty())
    {
        EvaluerUneOperation(operators, operands);
    }

    // Il devrait rester un seul op�rande dans la pile, qui est le r�sultat
    if (operands.Size() == 1)
    {
        cout << "R�sultat Final =  " << operands.Depiler() << endl;  //affichage du r�sultat final
        return operands.Depiler();
    }
    else
    {
        throw std::runtime_error("Erreur : Expression mal form�e");
    }
}



