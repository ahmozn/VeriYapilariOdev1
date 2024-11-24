/**
 * @file         DLList.cpp
 * @description  Doubly Linked List veri yapısının kaynak dosyası. Programda kullanılacak olan
 *               fonksiyonların gövdeleri burada tanımlanmıştır.
 * @course       2. Öğretim A grubu
 * @assignment   2024-2025 Güz, 1. Ödev
 * @date         01.11.2024
 * @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
 */
#include "DLList.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


//Constructor
DLList::DLList() : k_dll_head(nullptr), k_dll_last(nullptr), g_dll_head(nullptr), g_dll_last(nullptr) {}

//listedeki toplam kromozom sayısını döndürür
int DLList::toplamKromozom()
{
    int toplam = 0;
    KromozomNode *temp = k_dll_last;
    if (!temp)
    {
        std::cout << "Kromozom Bulunamadi-toplamKromozom()" << std::endl;
        return -1;
    }
    return (temp->index)+1;
}

//istenen kromozomdaki toplam gen sayısını döndürür
int DLList::toplamGen(int satir)
{
    int toplam = 0;
    KromozomNode *k_temp = kromozomBul(k_dll_head,satir,0,toplamKromozom()-1);
    if (!k_temp)
    {
        std::cout << "Kromozom Bulunamadi-toplamGen()" << std::endl;
        return -1;
    }
    GenNode *g_temp = k_temp->genDLL->g_dll_head;
    while (g_temp)
    {
        toplam++;
        g_temp = g_temp->next;
    }
    g_dll_last=g_temp;
    return toplam;
}

//divide and conquer mantığıyla rekürsif olarak istenen indexteki kromozomu getirir
KromozomNode *DLList::kromozomBul(KromozomNode* head, int satir, int k_ilk, int k_son)
{
    if(k_ilk==k_son){
        return head;
    }

    int k_orta=(k_ilk+k_son)/2;
    KromozomNode* k_node_orta=head;

    for(int i=k_ilk;i<k_orta;i++){
        k_node_orta=k_node_orta->next;
    }

    if(satir<=k_orta){
        return kromozomBul(head, satir, k_ilk, k_orta);
    }else{
        return kromozomBul(k_node_orta->next,satir, k_orta+1,k_son);
    }

    return nullptr; // kromozom bulunamadi
}

//istenen kromozomdaki istenen indexteki geni bulup döndürür
GenNode *DLList::genBul(int satir, int sutun)
{
    KromozomNode *k_temp = kromozomBul(k_dll_head,satir,0,toplamKromozom()-1);
    if (!k_temp)
    {
        std::cout << "Kromozom Bulunamadi-genBul()" << std::endl;
        return nullptr;
    }
    GenNode *g_temp = k_temp->genDLL->g_dll_head;
    if (!g_temp)
    {
        std::cout << "Gen Bulunamadi-genBul()" << std::endl;
        return nullptr;
    }
    while (g_temp && g_temp->index != sutun)
    {
        g_temp = g_temp->next;
    }
    return g_temp;
}

//ilgili kromozomdaki istenen indexteki geni bulup döndürür
GenNode *DLList::genBul(int sutun)
{
    GenNode *g_temp = g_dll_head;
    if (!g_temp)
    {
        std::cout << "Gen Bulunamadi-genBul()" << std::endl;
        return nullptr;
    }
    while (g_temp->index != sutun)
    {
        g_temp = g_temp->next;
    }
    return g_temp;
}

//listeye kromozom ekler
void DLList::kromozomEkle(int index)
{
    KromozomNode *newNode = new KromozomNode(new DLList(), index);
    //liste boşsa ilk eleman olarak atama
    if (!k_dll_head)
    {
        k_dll_head = newNode;
        k_dll_last=newNode;
    }
    //liste boş değilse en sona ekleme
    else
    {
        k_dll_last->next=newNode;
        newNode->prev=k_dll_last;
        k_dll_last=newNode;
    }
}

//liste sonundaki kromozomu siler, çaprazlama başarısız olduğunda kullanışlıdır
void DLList::sonkromozomSil(){
    KromozomNode* k_temp=k_dll_head;

    // Liste boşsa yapılacak işlem yok
    if (k_temp == nullptr) { 
        std::cout<<"liste bos-sonkromozomSil()"<<std::endl;
        return;
    }

    //Tek düğüm varsa
    if (k_temp->next == nullptr) {
        delete k_temp;
        k_temp = nullptr;
        k_dll_head=nullptr;
        k_dll_last=nullptr;
        std::cout<<"tek dugum vardi, silindi"<<std::endl;
        return;
    }

    //Son düğüme git
    KromozomNode* current = k_dll_last;
    k_dll_last=current->prev;
    k_dll_last->next = nullptr;    // Son düğümü listeden çıkar
    delete current;                // Bellekten serbest bırak
    return;
}

//son kromozoma istenen indexe sahip gen ekler
bool DLList::genEkle(int index, char deger)
{
    KromozomNode *k_temp = k_dll_last;
    if (!k_dll_last)
    {
        std::cout << "Kromozom Bulunamadi-genEkle()" << std::endl;
        return false;
    }

    GenNode *newNode = new GenNode(index, deger);
    //genDLL boş ise ilk eleman olarak atanır
    if (!k_temp->genDLL->g_dll_head)
    {
        k_temp->genDLL->g_dll_head = newNode;
        k_temp->genDLL->g_dll_last=newNode;
    }
    //genDLL içinde eleman varsa en sona ekleme yapar
    else
    {
        GenNode *temp = k_temp->genDLL->g_dll_last;
        temp->next = newNode;
        newNode->prev = temp;
        k_temp->genDLL->g_dll_last=newNode;
    }
    return true;
}

//istenen kromozoma istenen indexe sahip gen ekler
bool DLList::genEkle(int satir, int index, char deger)
{
    KromozomNode *k_temp = kromozomBul(k_dll_head,satir,0,toplamKromozom()-1);
    if (!k_temp)
    {
        std::cout << "Kromozom Bulunamadi-genEkle()" << std::endl;
        return false;
    }

    GenNode *newNode = new GenNode(index, deger);
    //genDLL boş ise ilk eleman olarak atanır
    if (!k_temp->genDLL->g_dll_head)
    {
        k_temp->genDLL->g_dll_head = newNode;
        k_temp->genDLL->g_dll_last=newNode;
    }
    //genDLL içinde eleman varsa en sona ekleme yapar
    else
    {
        GenNode *temp = k_temp->genDLL->g_dll_last;
        temp->next = newNode;
        newNode->prev = temp;
        k_temp->genDLL->g_dll_last=newNode;
    }
    return true;
}

//çaprazlama işlemi
bool DLList::caprazla(int satir1, int satir2)
{
    KromozomNode *k1_temp = kromozomBul(k_dll_head,satir1,0,toplamKromozom()-1);
    if (!k1_temp)
    {
        std::cout << "Kromozom1 Bulunamadi-caprazla()" << std::endl;
        return false;
    }
    if (!k1_temp->genDLL->g_dll_head)
    {
        std::cout << "Gen Listesi Bos-k1_temp-caprazla()" << std::endl;
        return false;
    }

    KromozomNode *k2_temp = kromozomBul(k_dll_head,satir2,0,toplamKromozom()-1);
    if (!k2_temp)
    {
        std::cout << "Kromozom2 Bulunamadi-caprazla()" << std::endl;
        return false;
    }
    if (!k2_temp->genDLL->g_dll_head)
    {
        std::cout << "Gen Listesi Bos-k2_temp-caprazla()" << std::endl;
        return false;
    }

    //yeni kromozomları kaydedebilmek için iki yeni kromozom ekleniyor
    kromozomEkle(toplamKromozom());
    kromozomEkle(toplamKromozom());

    int boyut1 = toplamGen(satir1);
    int boyut2 = toplamGen(satir2);

    //ilk kromozomun ilk yarısını 1. yeni kromozoma ekleme
    for (int i = 0; i < boyut1 / 2; i++) 
    {genEkle(toplamKromozom() - 2, i, k1_temp->genDLL->genBul(i)->data);} 

    //ilk kromozomun cift olma durumu
    if (boyut1 % 2 == 0)    
    {
        //ilk kromozomun ikinci yarısını 2. yeni kromozoma ekleme 
        int ix = 0;
        int iy = 0;
        for (int j = boyut1 / 2; j < boyut1; j++) 
        {genEkle(toplamKromozom() - 1, ix, k1_temp->genDLL->genBul(j)->data); ix++;} 
        iy=ix;
        //ikinci kromozomun cift olma durumu
        if (boyut2 % 2 == 0)
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2; i < boyut2; i++)   
            {genEkle(toplamKromozom() - 2, ix, k2_temp->genDLL->genBul(i)->data); ix++;}
            
            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++) 
            {genEkle(toplamKromozom() - 1, iy, k2_temp->genDLL->genBul(i)->data); iy++;}
        }
        
        //ikinci kromozomun tek olma durumu
        else    
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2 + 1; i < boyut2; i++)
            {genEkle(toplamKromozom() - 2, ix, k2_temp->genDLL->genBul(i)->data); ix++;}

            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++)
            {genEkle(toplamKromozom() - 1, iy, k2_temp->genDLL->genBul(i)->data); iy++;}
        }
        return true;
    }
    //ilk kromozomun tek olma durumu
    else    
    {
        //ilk kromozomun ikinci yarısını 2. yeni kromozoma ekleme 
        int ix = 0;
        int iy=0;
        for (int j = boyut1 / 2 + 1; j < boyut1; j++)
        {genEkle(toplamKromozom() - 1, ix, k1_temp->genDLL->genBul(j)->data); ix++;}
        iy=ix;
        //ikinci kromozomun cift olma durumu
        if (boyut2 % 2 == 0)
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2; i < boyut2; i++)
            {genEkle(toplamKromozom() - 2, ix, k2_temp->genDLL->genBul(i)->data); ix++;}

            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++)
            {genEkle(toplamKromozom() - 1, iy, k2_temp->genDLL->genBul(i)->data); iy++;}
        }
        //ikinci kromozomun tek olma durumu
        else
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2 + 1; i < boyut2; i++)
            {genEkle(toplamKromozom() - 2, ix, k2_temp->genDLL->genBul(i)->data); ix++;}

            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++)
            {genEkle(toplamKromozom() - 1, iy, k2_temp->genDLL->genBul(i)->data); iy++;}
        }
        return true;
    }
    
    std::cout << "bir hata meydana geldi-caprazla()" << std::endl;

    //caprazlama başarılı olamadığından son işlemleri geri alıyoruz
    sonkromozomSil();
    sonkromozomSil();
    return false;
}

//mutasyon işlemi
bool DLList::genMutasyon(int satir, int sutun)
{
    KromozomNode *k_temp = kromozomBul(k_dll_head,satir,0,toplamKromozom()-1);
    if (!k_temp)
    {
        std::cout << "Kromozom Bulunamadi-genMutasyon()" << std::endl;
        return false;
    }

    GenNode *g_temp = k_temp->genDLL->g_dll_head;
    if (!g_temp)
    {
        std::cout << "Gen Listesi Bos-genMutasyon()" << std::endl;
        return false;
    }

    //ilgili geni bulana dek kromozomun gen listesinde gezer, bulunca geni X yapar
    while (g_temp)
    {
        if (g_temp->index == sutun)
        {
            g_temp->data = 'X';
            return true;
        }
        g_temp = g_temp->next;
    }
    std::cout << "Gen Bulunamadi, index out of bounds-genMutasyon()" << std::endl;
    return false;
}

//otomatik işlemler
void DLList::otomatikIslemler(){
    std::ifstream fileIslem("Islemler.txt"); //Islemler.txt dosyası okunmak için açıldı
    std::string lineIslem;  //komut ve parametreleri okumak için

    char komut;
    int satir1;
    int satir2;
    int sutun;
    //her bir işlemin okunup işlendiği kısım
    while(getline(fileIslem,lineIslem))
    {
        std::istringstream lineStreamIslem(lineIslem);
        lineStreamIslem>>komut; //yapılacak işlemin kaydı

        //C okununca Caprazlama
        if(komut=='C') {
            lineStreamIslem>>satir1>>satir2;
            if(!caprazla(satir1,satir2)) std::cout<<"Caprazlama BASARISIZ!-otomatik"<<std::endl;
        }
        //M okununca Mutasyon
        else if(komut=='M') {
            lineStreamIslem>>satir1>>sutun;
            if(!genMutasyon(satir1,sutun)) std::cout<<"Mutasyon BASARISIZ!-otomatik"<<std::endl;
        }
        //ikisi de değilse geri bildirim
        else{
            std::cout<<"Bilinmeyen komut: "<<komut<<std::endl;
        }
    }
    fileIslem.close();
}

//ekrana yaz işlemi
void DLList::ekranaYaz()
{
    char ilkGen;
    KromozomNode *k_temp = k_dll_head;
    if (!k_temp)
    {
        std::cout << "Kromozom Bulunamadi-ekranaYaz()" << std::endl;
        return;
    }
    
    GenNode*g_temp=k_temp->genDLL->g_dll_head;
    std::string output="";
    while (k_temp)
    {
        g_temp=k_temp->genDLL->g_dll_head;
        
        //gen listesi boş ise sonraki kromozoma geçilir
        if(!g_temp){
            k_temp=k_temp->next;
            continue;
        }
        //kromozomdaki genlerin en sonuna gider
        while(g_temp->next!=nullptr){
            g_temp=g_temp->next;
        }

        ilkGen=k_temp->genDLL->g_dll_head->data; //kromozomdaki ilk geni saklar

        //sondan geriye karşılaştırma
        for(int i=g_temp->index;i>=0;i--)
        {
            //ascii değeri ilkGen'den küçükse yazdır ve döngüden çık
            if(g_temp->data<ilkGen){
                output+=g_temp->data;
                output+=" ";
                break;
            }
            //bir önceki düğüme geç
            if(g_temp->prev!=nullptr){
                g_temp=g_temp->prev;
            }
        }
        //ilkGen'in kromozomdaki tüm genlerden küçük olma durumu
        if(g_temp->index==0||g_temp->prev==nullptr){
            output+=g_temp->data;
            output+=" ";
        }
        k_temp = k_temp->next;
    }
    std::cout<<output<<std::endl;
}

//Printer, kromozomu yazdirir
bool DLList::g_printList(int satir)
{
    std::string output="";
    KromozomNode *k_temp = kromozomBul(k_dll_head,satir,0,toplamKromozom()-1);
    if (!k_temp)
    {
        std::cout << "Kromozom Bulunamadi-g_printList()" << std::endl;
        return false;
    }
    GenNode *g_temp = k_temp->genDLL->g_dll_head;
    if (!g_temp)
    {
        std::cout << "Gen Bulunamadi-g_printList()" << std::endl;
        return false;
    }
    std::cout<<"K:"<<k_temp->index<<"| ";
    while (g_temp)
    {
        output+=g_temp->data;
        output+=" ";
        g_temp = g_temp->next;
    }
    std::cout <<output<< std::endl;
    return true;
}

/*Destructor, kromozomlardaki genlerden başlayarak önce genleri sonra ilgili kromozomu siler, 
* liste bitene kadar tekrar eder
*/
DLList::~DLList(){
    KromozomNode* k_current=k_dll_head;
    KromozomNode* k_nextNode;
    while(k_current){
        if (k_current->genDLL && k_current->genDLL->g_dll_head)
        {
            GenNode* g_current=k_current->genDLL->g_dll_head;
            GenNode* g_nextNode;
            while (g_current)
            {
                g_nextNode=g_current->next;
                delete g_current; //gen serbest birakma
                g_current=g_nextNode;
                k_current->genDLL->g_dll_head=g_current;
            }
        }
        k_nextNode=k_current->next;
        delete k_current; //kromozom serbest birakma
        k_current=k_nextNode;
        k_dll_head=k_current;
    }
    std::cout<<"Liste basariyla silindi.\n"<<std::endl;
}
