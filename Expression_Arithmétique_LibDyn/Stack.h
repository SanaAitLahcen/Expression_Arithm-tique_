#pragma once
#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

template<class S>
class Stack
{
private:
    S* pile;
    int sommet;
    int capacity;

public:
    Stack();
    ~Stack();
    bool isEmpty();
    bool isFull();
    void Empiler(S);
    S Depiler();
    char Top();
    int Size() const;
    void resize();
    void afficher() const;
};

template<class S>
Stack<S>::Stack() : sommet(0), capacity(3)
{
    this->pile = new S[capacity];
}



template<class S>
Stack<S>::~Stack()
{
    delete[] pile;
}


template<class S>
bool Stack<S>::isEmpty()
{
    return sommet == 0;  // Retourne vrai si la pile est vide
}

template<class S>
bool Stack<S>::isFull()
{
    return sommet == capacity;  // Retourne vrai si la pile est pleine
}

template<class S>
void Stack<S>::resize()
{
    int k = 0;

    // Créer un tableau temporaire pour copier les anciens éléments
    S* Temp = new S[capacity];

    // Copie les éléments dans Temp
    for (int i = sommet - 1; i >= 0; i--)
    {
        Temp[k++] = pile[i];
    }

    // Redimensionne et crée un nouveau tableau pour pile
    capacity *= 2;
    S* tab = new S[capacity];

    // Re-copie les éléments dans l'ordre correct
    k = 0;
    for (int j = sommet - 1; j >= 0; j--)
    {
        tab[k++] = Temp[j];
    }

    // Nettoyer le tableau temporaire
    delete[] Temp;

    // Mettre à jour pile avec le nouveau tableau
    pile = tab;
}




template<class S>
void Stack<S>::Empiler(S val) {
    if (isFull())
    {
        resize();
    }

    pile[sommet++] = val;
}



template<class S>
S Stack<S>::Depiler()
{
    if (isEmpty())
    {
        throw std::runtime_error("Erreur : La pile est vide (Underflow)");
    }

    S valeur = pile[--sommet];
    return valeur;
}






template<class S>
char Stack<S>::Top()
{
    if (!isEmpty())
        return pile[sommet - 1];
    return '\0'; // Retourne un caractère nul si la pile est vide
}




template<class S>
int Stack<S>::Size() const
{
    return sommet;
}

template<class S>
void Stack<S>::afficher() const
{
    for (int i = sommet - 1; i >= 0; i--)
    {
        std::cout << pile[i] << std::endl;
    }
}


