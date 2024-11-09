/**
* @file         GenNode.cpp
* @description  Doubly Linked List içerisinde kullanılacak iç düğümlerin kaynak dosyası.
* @course       2. Öğretim A grubu
* @assignment   2024-2025 Güz, 1. Ödev
* @date         01.11.2024
* @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
*/
#include "GenNode.hpp"

GenNode::GenNode(int index, char* deger): index(index), data(deger), next(nullptr), prev(nullptr){}
GenNode::~GenNode(){}