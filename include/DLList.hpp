/**
* @file         DLList.hpp
* @description  Doubly Linked List veri yapısının başlık dosyası 
* @course       2. Öğretim A grubu
* @assignment   2024-2025 Güz, 1. Ödev
* @date         01.11.2024
* @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
*/
#ifndef DLList_HPP
#define DLList_HPP

#include "GenNode.hpp"
#include "KromozomNode.hpp"

class KromozomNode;
class GenNode;

class DLList{
    private: 
        KromozomNode* k_dll_head;
        GenNode* g_dll_head;
    public:
        DLList();   //constructor

        KromozomNode* kromozomBul(int satir);               //kromozom bulma
        GenNode* genBul(int satir, int sutun);              //istenen kromozomdaki geni bulma
        GenNode* genBul(int sutun);                         //ilgili kromozomdaki geni bulma
        int toplamKromozom();                               //toplam kromozom sayısı
        int toplamGen(int index_k);                         //istenen kromozomdaki toplam gen sayısı
        void kromozomEkle(int index_k);                     //kromozom ekleme
        void sonkromozomSil();                              //son kromozom sil
        bool genEkle(int satir, int index_g, char deger);   //gen ekleme 
        bool g_printList(int satir);                        //listeyi yazdirma

        //dökümanda belirtilen fonksiyonlar
        bool caprazla(int satir1, int satir2);              //caprazlama
        bool genMutasyon(int satir, int sutun);             //mutasyona ugratma
        void ekranaYaz();                                   //ekrana yazdirma

        ~DLList();
};

#endif