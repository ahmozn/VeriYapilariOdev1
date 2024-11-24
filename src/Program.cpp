/**
* @file         Program.cpp
* @description  Verilen Dna.txt dosyasının içeriğini tarar, çift yönlü listelerde saklar. Bu veriler
*               ile Çaprazlama, Mutasyon, Otomatik İşlemler, Ekrana Yazdırma gibi işlemler yapar.
* @course       2. Öğretim A grubu
* @assignment   2024-2025 Güz, 1. Ödev
* @date         01.11.2024
* @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
*/
#include "DLList.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;

int main() {
    DLList* kromozomlar=new DLList();

    int satir=0,satir2=0,sutun=0,secim=0;

    ifstream fileDna("Dna.txt");  //Dna.txt okumak için açıyoruz

    system("CLS");
    
    auto start=chrono::high_resolution_clock::now(); //okuma süresi hesaplayici
    cout<<"Dna.txt okunuyor..."<<endl;

    int i=0;
    char gen;
    bool satirsonu=false;
    kromozomlar->kromozomEkle(satir);
    while(fileDna.get(gen)){
        if(gen=='\n'){
            satirsonu=true;
            i=0;
            satir++;
            kromozomlar->kromozomEkle(satir);
        }
        else if(gen!=' '){
            kromozomlar->genEkle(i,gen);
            i++;
        }
        if(satirsonu){
            satirsonu=false;
        }
    }

    auto end=chrono::high_resolution_clock::now();
    auto duration=chrono::duration_cast<chrono::milliseconds>(end-start);
    cout<<duration.count()<<" ms"<<endl; //okuma işlemi ne kadar sürdü
    fileDna.close();    //Dna.txt kapatıldı

    char komut;
    satir=0;
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

            if(!kromozomlar->caprazla(satir,satir2)){
                cout<<"Caprazlama BASARISIZ!"<<endl;
            }else{
                cout<<"Caprazlama sonucu olusan kromozomlar: "<<endl;
                kromozomlar->g_printList(kromozomlar->toplamKromozom()-2);
                kromozomlar->g_printList(kromozomlar->toplamKromozom()-1);
                cout<<"________________"<<endl;
            }
            break;
        case 2:
            cout<<"Mutasyon secildi"<<endl;
            cout<<"Kromozom ve Gen indexi giriniz(ornek: 0 2): "; cin>>satir>>sutun;
            if(kromozomlar->genMutasyon(satir,sutun)){
                cout<<"Mutasyon gerceklesti   : ";
                kromozomlar->g_printList(satir);
            }else{
                cout<<"Mutasyon BASARISIZ!"<<endl;
            }
            break;
        case 3:
            cout<<"Otomatik Islemler secildi."<<endl;
            kromozomlar->otomatikIslemler();
            cout<<"Otomatik Islemler tamamlandi."<<endl;
            break;
        case 4:
            cout<<"Ekrana Yaz secildi."<<endl;
            kromozomlar->ekranaYaz();
            cout<<endl;
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
    
    //bellegi serbest birak
    cout<<"Bellek serbest birakiliyor..."<<endl;
    cout<<"..."<<endl;
    kromozomlar->~DLList();
    cout<<"Program basarili sekilde sonlandi."<<endl;
    return 0;
}