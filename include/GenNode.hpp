/**
* @file         GenNode.hpp
* @description  Doubly Linked List içerisinde kullanılacak düğümlerin başlık dosyası. En iç düğümler
*               olan Gen'leri temsil eder.
* @course       2. Öğretim A grubu
* @assignment   2024-2025 Güz, 1. Ödev
* @date         01.11.2024
* @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
*/
#ifndef GENNODE_HPP
#define GENNODE_HPP

class GenNode{
    public:
        int index;     //gen indexi
        char data;     //veri
        GenNode* next; //sonraki dugume pointer
        GenNode* prev; //onceki dugume pointer

        GenNode(int index,char deger); //constructor
        ~GenNode();                    //destructor
};

#endif