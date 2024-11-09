/**
* @file         Program.cpp
* @description  Verilen Dna.txt dosyasının içeriğini tarar, çift yönlü listelerde saklar. Bu veriler
*               ile Çaprazlama, Mutasyon, Otomatik İşlemler, Ekrana Yazdrıma gibi işlemler yapar.
* @course       2. Öğretim A grubu
* @assignment   2024-2025 Güz, 1. Ödev
* @date         01.11.2024
* @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
*/
#include "DLList.hpp"
#include "fields.h"
#include <iostream>
//#include <fstream>
//#include <string>
//#include <stdio.h>
//#include <stdlib.h>
//#include <windows.h>

// FIELDS YASAK, CHAR OLARAK TUTMAK COK DAHA MANTIKLI CHATGPTDE YOLLAR MEVCUT

using namespace std;

int main() {
    DLList* kromozomlar=new DLList();

    int satir=0,satir2=0,sutun=0,secim=0;

    //dosya okuma icin
    IS isDna;
    isDna=new_inputstruct("Dna.txt");
    IS isOto;
    isOto=new_inputstruct("Islemler.txt");


    //okunacak Dna.txt dosyasinin acilirken hata kontrolu
    if(isDna==NULL)
    {perror("Dna.txt"); exit(1);}
    
    //okunacak Islemler.txt dosyasinin acilirken hata kontrolu
    if(isOto==NULL)
    {perror("Islemler.txt"); exit(1);}


    //her bir kromozom ve genin eklendigi kisim
    while(get_line(isDna)>=0){
        kromozomlar->kromozomEkle(satir); //kromozom ekleme
        //gen ekleme
        for(int i=0;i<isDna->NF;i++){
            kromozomlar->genEkle(satir,i,isDna->fields[i]); 
        }
        satir++;
    }

    char* komut;
    satir=0;
    system("CLS");
    do
    {
        cout<<"1- Caprazlama"<<endl;
        cout<<"2- Mutasyon"<<endl;
        cout<<"3- Otomatik Islemler"<<endl;
        cout<<"4- Ekrana Yaz"<<endl;
        cout<<"5- Cikis"<<endl;
        cin>>secim;
        switch (secim)
        {
        case 1:
            cout<<"Caprazlama secildi"<<endl;
            cout<<"Caprazlanmasi icin iki kromozom seciniz(ornek: 1 5): "; cin>>satir>>satir2;
            kromozomlar->kromozomEkle(kromozomlar->toplamKromozom());
            kromozomlar->kromozomEkle(kromozomlar->toplamKromozom());
            if(!kromozomlar->caprazla(satir,satir2)){
                kromozomlar->sonkromozomSil();
                kromozomlar->sonkromozomSil();
            }
            break;
        case 2:
            cout<<"Mutasyon secildi"<<endl;
            cout<<"Kromozom ve Gen indexi giriniz(ornek: 0 2): "; cin>>satir>>sutun;
            //kromozomlar->genMutasyon(satir,sutun);
            if(kromozomlar->genMutasyon(satir,sutun)){
                kromozomlar->g_printList(satir);
            }else{
                cout<<"Mutasyon BASARISIZ!"<<endl;
            }
            break;
        case 3:
            cout<<"Otomatik Islemler secildi."<<endl;
            //her bir işlemin okunup işlendiği kısım
            while(get_line(isOto)>=0)
            {
                komut=isOto->fields[0]; //yapılacak işlemin kaydı

                //C okununca Caprazlama
                if(strcmp(komut,"C")==0) {
                    satir=atoi(isOto->fields[1]);
                    satir2=atoi(isOto->fields[2]);
                    kromozomlar->kromozomEkle(kromozomlar->toplamKromozom());
                    kromozomlar->kromozomEkle(kromozomlar->toplamKromozom());
                    if(!kromozomlar->caprazla(satir,satir2)){
                        kromozomlar->sonkromozomSil();
                        kromozomlar->sonkromozomSil();
                    }
                }
                //M okununca Mutasyon
                if(strcmp(komut,"M")==0) {
                    satir=atoi(isOto->fields[1]);
                    sutun=atoi(isOto->fields[2]);
                    if(kromozomlar->genMutasyon(satir,sutun)){
                        kromozomlar->g_printList(satir);
                    }else{
                        cout<<"Mutasyon BASARISIZ!"<<endl;
                    }
                }
            }
            break;
        case 4:
            cout<<"Ekrana Yaz secildi."<<endl;
            kromozomlar->ekranaYaz();
            break;
        case 5:
            cout<<"Cikis secildi."<<endl;
            break; 
        default:
            cout<<"Hatali Secim Yaptiniz"<<endl;
            cin.ignore();
            cin.get();
            break;
        }
    } while (secim!=5);

    cout<<"\nToplam Kromozom: "<<kromozomlar->toplamKromozom()<<endl;
    for(int j=0; j<kromozomlar->toplamKromozom();j++){
        cout<<"Kromozom: "<<kromozomlar->kromozomBul(j)->index<<", Toplam Gen: "<<kromozomlar->toplamGen(j)<<"| ";
        kromozomlar->g_printList(j);
    }

    //bellegi serbest birak
    cout<<"Bellek serbest birakiliyor..."<<endl;
    cout<<"..."<<endl;
    kromozomlar->~DLList();
    jettison_inputstruct(isDna);
    cout<<"Program basarili sekilde sonlandi."<<endl;
    return 0;
}