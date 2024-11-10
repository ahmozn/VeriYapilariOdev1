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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    DLList* kromozomlar=new DLList();

    int satir=0,satir2=0,sutun=0,secim=0;

    ifstream fileDna("Dna.txt");
    string lineDna;

    ifstream fileIslem("Islemler.txt");
    string lineIslem;

    //her bir kromozom ve genin eklendigi kisim
    while(getline(fileDna,lineDna)){
        istringstream lineStreamDna(lineDna);
        kromozomlar->kromozomEkle(satir); //kromozom ekleme
        
        //gen ekleme
        char gen;
        int i=0;
        while(lineStreamDna>>gen){
            kromozomlar->genEkle(satir,i,gen);
            i++; 
        }
        satir++;
    }

    char komut;
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
            //her bir işlemin okunup işlendiği kısım
            while(getline(fileIslem,lineIslem))
            {
                istringstream lineStreamIslem(lineIslem);
                lineStreamIslem>>komut; //yapılacak işlemin kaydı

                //C okununca Caprazlama
                if(komut=='C') {
                    lineStreamIslem>>satir>>satir2;
                    if(!kromozomlar->caprazla(satir,satir2)){
                        cout<<"Caprazlama BASARISIZ!-otomatik"<<endl;
                    }else{
                        cout<<"Caprazlama sonucu olusan kromozomlar: "<<endl;
                        kromozomlar->g_printList(kromozomlar->toplamKromozom()-2);
                        kromozomlar->g_printList(kromozomlar->toplamKromozom()-1);
                        cout<<"________________"<<endl;
                    }
                }
                //M okununca Mutasyon
                else if(komut=='M') {
                    lineStreamIslem>>satir>>sutun;
                    if(kromozomlar->genMutasyon(satir,sutun)){
                        cout<<"Mutasyon gerceklesti   : ";
                        kromozomlar->g_printList(satir);
                    }else{
                        cout<<"Mutasyon BASARISIZ!-otomatik"<<endl;
                    }
                }
                //ikisi de değilse geri bildirim
                else{
                    cout<<"Bilinmeyen komut: "<<komut<<endl;
                }
            }
            cout<<"Otomatik Islemler tamamlandi."<<endl;
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

    //bellegi serbest birak
    cout<<"Bellek serbest birakiliyor..."<<endl;
    cout<<"..."<<endl;
    kromozomlar->~DLList();
    cout<<"Program basarili sekilde sonlandi."<<endl;
    return 0;
}