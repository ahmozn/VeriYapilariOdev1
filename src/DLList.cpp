/**
 * @file         DLList.cpp
 * @description  Doubly Linked List veri yapısının kaynak dosyası. Programda kullanılacak olan
 *               fonksiyonların gövdeleri burada tanımlanmıştır.
 * @course       2. Öğretim A grubu
 * @assignment   2024-2025 Güz, 1. Ödev
 * @date         01.11.2024
 * @author       Ahmet Özhan ÖZEN   ozhan.ozen@ogr.sakarya.edu.tr
 */
#include <iostream>
#include "DLList.hpp"

//Constructor
DLList::DLList() : k_dll_head(nullptr), g_dll_head(nullptr) {}

//lsitedeki toplam kromozom sayısını döndürür
int DLList::toplamKromozom()
{
    int toplam = 0;
    KromozomNode *temp = k_dll_head;
    if (!temp)
    {
        std::cout << "Kromozom Bulunamadi-toplamKromozom()" << std::endl;
        return -1;
    }
    while (temp)
    {
        toplam++;
        temp = temp->next;
    }
    return toplam;
}

//istenen kromozomdaki toplam gen sayısını döndürür
int DLList::toplamGen(int satir)
{
    int toplam = 0;
    KromozomNode *k_temp = kromozomBul(satir);
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
    return toplam;
}

//listeyi dolaşarak istenen indexteki kromozomu getirir
KromozomNode *DLList::kromozomBul(int satir)
{
    KromozomNode *temp = k_dll_head;

    while (temp != nullptr)
    {
        if (temp->index == satir)
            return temp; // kromozom bulundu
        temp = temp->next;
    }
    return nullptr; // kromozom bulunamadi
}

//istenen kromozomdaki istenen indexteki geni bulup döndürür
GenNode *DLList::genBul(int satir, int sutun)
{
    KromozomNode *k_temp = kromozomBul(satir);
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
    }
    //liste boş değilse en sona ekleme
    else
    {
        KromozomNode *temp = k_dll_head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

//liste sonundaki kromozomu siler, çaprazlama başarısız olduğunda kullanışlıdır
void DLList::sonkromozomSil(){
    KromozomNode* k_temp=kromozomBul(0);

    // Liste boşsa yapılacak işlem yok
    if (k_temp == nullptr) { 
        std::cout<<"liste bos-sonkromozomSil()"<<std::endl;
        return;
    }

    //Tek düğüm varsa
    if (k_temp->next == nullptr) {
        delete k_temp;
        k_temp = nullptr;
        std::cout<<"tek dugum vardi, silindi"<<std::endl;
        return;
    }

    //Son düğüme git
    KromozomNode* current = k_temp;
    while (current->next!=nullptr) {
        current = current->next;
    }
    current->prev->next = nullptr; // Son düğümü listeden çıkar
    delete current;                // Bellekten serbest bırak
    return;
}

//istenen kromozoma istenen indexe sahip gen ekler
bool DLList::genEkle(int satir, int index, char deger)
{
    KromozomNode *k_temp = kromozomBul(satir);
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
    }
    //genDLL içinde eleman varsa en sona giderek ekleme yapar
    else
    {
        GenNode *temp = k_temp->genDLL->g_dll_head;

        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    return true;
}

//çaprazlama işlemi
bool DLList::caprazla(int satir1, int satir2)
{
    KromozomNode *k1_temp = kromozomBul(satir1);
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
    KromozomNode *k2_temp = kromozomBul(satir2);
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
        for (int j = boyut1 / 2; j < boyut1; j++) 
        {genEkle(toplamKromozom() - 1, ix, k1_temp->genDLL->genBul(j)->data); ix++;} 

        //ikinci kromozomun cift olma durumu
        if (boyut2 % 2 == 0)
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2; i < boyut2; i++)   
            {genEkle(toplamKromozom() - 2, i, k2_temp->genDLL->genBul(i)->data);}
            
            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++) 
            {genEkle(toplamKromozom() - 1, i, k2_temp->genDLL->genBul(i)->data);}
        }
        //ikinci kromozomun tek olma durumu
        else    
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2 + 2; i < boyut2+1; i++)
            {genEkle(toplamKromozom() - 2, i, k2_temp->genDLL->genBul(i)->data);}

            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++)
            {genEkle(toplamKromozom() - 1, i, k2_temp->genDLL->genBul(i)->data);}
        }
        return true;
    }
    //ilk kromozomun tek olma durumu
    else    
    {
        //ilk kromozomun ikinci yarısını 2. yeni kromozoma ekleme 
        int ix = 0;
        for (int j = boyut1 / 2 + 1; j < boyut1; j++)
        {genEkle(toplamKromozom() - 1, ix, k1_temp->genDLL->genBul(j)->data); ix++;}
        
        //ikinci kromozomun cift olma durumu
        if (boyut2 % 2 == 0)
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2; i < boyut2; i++)
            {genEkle(toplamKromozom() - 2, i, k2_temp->genDLL->genBul(i)->data);}

            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++)
            {genEkle(toplamKromozom() - 1, i, k2_temp->genDLL->genBul(i)->data);}
        }
        //ikinci kromozomun tek olma durumu
        else
        {
            //ikinci kromozomun ikinci yarısını 1. yeni kromozoma ekleme
            for (int i = boyut2 / 2 + 1; i < boyut2; i++)
            {genEkle(toplamKromozom() - 2, i, k2_temp->genDLL->genBul(i)->data);}

            //ikinci kromozomun ilk yarısını 2. yeni kromozoma ekleme
            for(int i=0;i<boyut2/2;i++)
            {genEkle(toplamKromozom() - 1, i, k2_temp->genDLL->genBul(i)->data);}
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
    KromozomNode *k_temp = kromozomBul(satir);
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

    std::cout<<"Mutasyon yapilacak gen : "; g_printList(k_temp->index);

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

//ekrana yaz işlemi
void DLList::ekranaYaz()
{
    char ilkGen;
    KromozomNode *k_temp = kromozomBul(0);
    if (!k_temp)
    {
        std::cout << "Kromozom Bulunamadi-ekranaYaz()" << std::endl;
        return;
    }
    
    GenNode*g_temp=k_temp->genDLL->g_dll_head;

    while (k_temp)
    {
        g_temp=k_temp->genDLL->g_dll_head;
        if(!g_temp){
            std::cout << "Gen Listesi Bos-ekranaYaz()" << std::endl;
            return;
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
                std::cout<<g_temp->data<<" ";
                break;
            }
            //bir önceki düğüme geç
            if(g_temp->prev!=nullptr){
                g_temp=g_temp->prev;
            }
        }
        //ilkGen'in kromozomdaki tüm genlerden küçük olma durumu
        if(g_temp->index==0){
            std::cout<<g_temp->data<<" ";
        }
        k_temp = k_temp->next;
    }
    std::cout<<std::endl;
}

//Printer, kromozomu yazdirir
bool DLList::g_printList(int satir)
{
    KromozomNode *k_temp = kromozomBul(satir);
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
    while (g_temp)
    {
        std::cout << g_temp->data << " ";
        g_temp = g_temp->next;
    }
    std::cout << std::endl;
    return true;
}

/*Destructor, kromozomlardaki genlerden başlayarak önce genleri sonra ilgili kromozomu siler, 
* liste bitene kadar tekrar eder
*/
DLList::~DLList(){
    KromozomNode* k_current=kromozomBul(0);
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
            }
        }
        k_nextNode=k_current->next;
        delete k_current; //kromozom serbest birakma
        k_current=k_nextNode;
    }
}
