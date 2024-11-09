/**
* @file         KromozomNode.hpp
* @description  Doubly Linked List içerisinde kullanılacak düğümlerin başlık dosyası. Ana listedeki düğümler
*               olan Kromozom'ları temsil eder.
* @course       2. Öğretim A grubu
* @assignment   2024-2025 Güz, 1. Ödev
* @date         01.11.2024
* @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
*/
#ifndef KROMOZOMNODE_HPP
#define KROMOZOMNODE_HPP

#include "DLList.hpp"

class DLList;

class KromozomNode{
    public:
        int index;          //kromozom indexi
        KromozomNode* next; //sonraki dugume pointer
        KromozomNode* prev; //onceki dugume pointer
        DLList* genDLL;     //genlerin saklanacagi double linked list

        KromozomNode(DLList* genDll,int index); //constructor
        ~KromozomNode();                       //destructor
};

#endif