
#include <iostream>
#include"pch.h"

int main() {


    std::cout << "Entrez une expression mathematique : ";
    std::string expression;
    std::getline(std::cin, expression);

    Expression::Verifier_Exp(expression);



    double resultat = Expression::Calculatrice(expression);
    std::cout << "Le resultat de l'expression est : " << resultat << std::endl;


    return 0;
}

