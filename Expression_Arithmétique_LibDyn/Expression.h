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
                cout << "Erreur : Parenthèse fermante sans correspondance.\n";
                return;
            }

            char top = stack.Depiler();
            if ((ch == ')' && top != '(') ||
                (ch == ']' && top != '[') ||
                (ch == '}' && top != '{'))
            {
                cout << "Erreur : Parenthèse ouvrante et fermante incompatibles.\n";
                return;
            }
        }
    }

    if (!stack.isEmpty())
    {
        cout << "Erreur : Parenthèse ouvrante sans correspondance.\n";
    }
    else
    {
        cout << "L'expression est bien Equilibree.\n";
    }
}



bool Expression::Priorite(char op1, char op2)
{
    // Si op1 a une priorité supérieure ou égale à op2, on le dépile
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
    // Récupère les deux derniers opérandes et l'opérateur du sommet des piles
    double val2 = operands.Depiler();
    double val1 = operands.Depiler();
    char op = operators.Depiler();

    // Effectue l'opération en fonction de l'opérateur
    double result;
    switch (op)
    {
    case '+': result = val1 + val2; break;
    case '-': result = val1 - val2; break;
    case '*': result = val1 * val2; break;
    case '/':
        if (val2 == 0)
        {
            throw std::runtime_error("Erreur : Division par zéro");
        }
        result = val1 / val2;
        break;
    default: throw std::runtime_error("Erreur : Opérateur inconnu");
    }

    // Empile le résultat
    operands.Empiler(result);
}




double Expression::Calculatrice(const string expression)
{
    Stack<char> operators;  // Pile pour les opérateurs
    Stack<double> operands; // Pile pour les opérandes (nombres)

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

        // Si le caractère est un chiffre
        if (isdigit(ch))
        {
            double num = 0;
            while (i < expression.length() && isdigit(expression[i]))
            {
                num = num * 10 + (expression[i] - '0'); // Construire le nombre
                i++;
            }
            operands.Empiler(num); // Empiler l'opérande (le nombre)
            //cout << "Empile opérande : " << num << endl; // Affichage pour le débogage
            continue;
        }

        // Si le caractère est une parenthèse ouvrante
        if (ch == '(')
        {
            operators.Empiler(ch);
            //cout << "Empile parenthèse ouvrante : " << ch << endl; // Affichage pour débogage
        }
        // Si le caractère est une parenthèse fermante
        else if (ch == ')')
        {
            while (!operators.isEmpty() && operators.Top() != '(')
            {
                EvaluerUneOperation(operators, operands); // Dépiler et évaluer
            }
            operators.Depiler(); // Dépiler la parenthèse ouvrante '('
            //cout << "Dépile parenthèse ouvrante : (" << endl; // Affichage pour débogage
        }
        // Si le caractère est un opérateur
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            while (!operators.isEmpty() && Priorite(operators.Top(), ch))
            {
                EvaluerUneOperation(operators, operands); // Dépiler et évaluer si nécessaire
            }
            operators.Empiler(ch); // Empiler l'opérateur
            //cout << "Empile opérateur : " << ch << endl; // Affichage pour débogage
        }
        else
        {
            throw std::runtime_error("Erreur : Caractère invalide dans l'expression");
        }

        i++; // Passer à l'élément suivant
    }

    // Dépiler les opérateurs restants et évaluer
    while (!operators.isEmpty())
    {
        EvaluerUneOperation(operators, operands);
    }

    // Il devrait rester un seul opérande dans la pile, qui est le résultat
    if (operands.Size() == 1)
    {
        cout << "Résultat Final =  " << operands.Depiler() << endl;  //affichage du résultat final
        return operands.Depiler();
    }
    else
    {
        throw std::runtime_error("Erreur : Expression mal formée");
    }
}



