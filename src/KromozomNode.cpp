/**
* @file         KromozomNode.cpp
* @description  Doubly Linked List içerisinde kullanılacak düğümlerin kaynak dosyası.
* @course       2. Öğretim A grubu
* @assignment   2024-2025 Güz, 1. Ödev
* @date         01.11.2024
* @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
*/
#include "KromozomNode.hpp"
#include "DLList.hpp"

KromozomNode::KromozomNode(DLList* genDll,int index): genDLL(genDll),index(index), next(nullptr), prev(nullptr){}
KromozomNode::~KromozomNode(){}