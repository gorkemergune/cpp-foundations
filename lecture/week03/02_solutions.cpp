// =============================================================================
//  WEEK 03 - ALISTIRMA COZUMLERI
//  Once kendin dene (01_exercises.cpp), tikandiginda sadece o alistirmaya bak.
//  Derle:  g++ -std=c++17 02_solutions.cpp -o sol && ./sol
// =============================================================================

#include "iostream"
#include "string"

struct Node {
    int data;
    Node* next;
};

// ---------------- yardimcilar (01_exercises.cpp ile ayni) --------------------

Node* listeYap(const int dizi[], int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; ++i) {
        Node* yeni = new Node();
        yeni->data = dizi[i];
        yeni->next = NULL;
        if (head == NULL) {
            head = yeni;
            tail = yeni;
        } else {
            tail->next = yeni;
            tail = yeni;
        }
    }
    return head;
}

void listeyiSil(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

std::string listeMetni(Node* head) {
    std::string s = "";
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        if (s != "") { s += ","; }
        s += std::to_string(cur->data);
    }
    return s;
}

int basariliSayisi = 0;
int toplamTest = 0;

void kontrol(const std::string& ad, const std::string& beklenen, const std::string& bulunan) {
    toplamTest++;
    if (beklenen == bulunan) {
        basariliSayisi++;
        std::cout << "[OK]   " << ad << std::endl;
    } else {
        std::cout << "[HATA] " << ad << "  | beklenen: " << beklenen
                  << "  | bulunan: " << bulunan << std::endl;
    }
}

// =============================================================================
//  1) uzunluk
// =============================================================================
int uzunluk(Node* head) {
    int sayac = 0;
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        sayac++;
    }
    return sayac;
}
// head == NULL ise dongu hic girmez, 0 doner. Ayri if gerekmedi.

// =============================================================================
//  2) toplam
// =============================================================================
int toplam(Node* head) {
    int t = 0;
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        t += cur->data;
    }
    return t;
}

// =============================================================================
//  3) iceriyorMu
// =============================================================================
bool iceriyorMu(Node* head, int deger) {
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        if (cur->data == deger) {
            return true;      // bulunca hemen cik, gereksiz gezme
        }
    }
    return false;             // dongu bitti, demek ki yok
}

// =============================================================================
//  4) enBuyuk
// =============================================================================
int enBuyuk(Node* head) {
    if (head == NULL) {       // bos liste: head->data yazarsak program coker
        return 0;
    }

    int en = head->data;                     // ilk elemani referans al
    for (Node* cur = head->next; cur != NULL; cur = cur->next) {
        if (cur->data > en) {
            en = cur->data;
        }
    }
    return en;
}
// NOT: "int en = 0;" ile baslamak hatali olur - tum degerler negatifse yanlis sonuc.

// =============================================================================
//  5) basaEkle
// =============================================================================
Node* basaEkle(Node* head, int deger) {
    Node* yeni = new Node();
    yeni->data = deger;
    yeni->next = head;        // eski basi gosterir (head NULL ise de dogru!)
    return yeni;              // yeni bas
}
// Bos listede neden ayri if yok? head == NULL ise yeni->next = NULL olur,
// yani tek elemanli dogru liste cikar. Kalip kendiliginden halleder.

// =============================================================================
//  6) sonaEkle
// =============================================================================
Node* sonaEkle(Node* head, int deger) {
    Node* yeni = new Node();
    yeni->data = deger;
    yeni->next = NULL;        // son node oldugu icin NULL

    if (head == NULL) {       // DURUM A: liste bos
        return yeni;
    }

    Node* cur = head;         // DURUM B: son node'u bul
    while (cur->next != NULL) {   // dikkat: cur != NULL DEGIL
        cur = cur->next;
    }
    cur->next = yeni;
    return head;
}

// =============================================================================
//  7) kthEleman
// =============================================================================
int kthEleman(Node* head, int k) {
    if (k < 0) {
        return -1;
    }

    Node* cur = head;
    int i = 0;
    while (cur != NULL && i < k) {   // k adim ilerle, ama listeden tasmadan
        cur = cur->next;
        i++;
    }

    if (cur == NULL) {               // liste k'dan kisaymis
        return -1;
    }
    return cur->data;
}

// =============================================================================
//  8) sil  -  prev + cur kalibi
// =============================================================================
Node* sil(Node* head, int deger) {
    Node* prev = NULL;
    Node* cur  = head;

    // hedefi ara, prev'i surekli bir geride tut
    while (cur != NULL && cur->data != deger) {
        prev = cur;
        cur  = cur->next;
    }

    if (cur == NULL) {         // 1) hic bulunamadi (bos liste de buraya duser)
        return head;
    }

    if (prev == NULL) {        // 2) silinecek olan ilk node -> head kayar
        head = cur->next;
    } else {                   // 3) orta veya son -> koprusu kur
        prev->next = cur->next;
    }

    cur->next = NULL;          // kopardigimiz node'un okunu temizle
    delete cur;                // bellegi geri ver
    return head;
}

// =============================================================================
//  9) tersCevir  -  uc pointer
// =============================================================================
Node* tersCevir(Node* head) {
    Node* prev = NULL;
    Node* cur  = head;

    while (cur != NULL) {
        Node* next = cur->next;   // 1) yedekle, yoksa zincirin gerisi kaybolur
        cur->next  = prev;        // 2) oku geriye cevir
        prev = cur;               // 3) prev'i kaydir
        cur  = next;              // 4) cur'u kaydir
    }

    return prev;                  // dongu bitince prev = eski son node = yeni head
}
//  Adim adim [10,20,30]:
//    baslangic: prev=NULL  cur=[10]
//    1. tur:    [10]->NULL              prev=[10]  cur=[20]
//    2. tur:    [20]->[10]->NULL        prev=[20]  cur=[30]
//    3. tur:    [30]->[20]->[10]->NULL  prev=[30]  cur=NULL  -> dur

// =============================================================================
//  10) sirayaEkle
// =============================================================================
Node* sirayaEkle(Node* head, int deger) {
    Node* yeni = new Node();
    yeni->data = deger;
    yeni->next = NULL;

    Node* prev = NULL;
    Node* cur  = head;

    // dogru yeri bul: kendisinden kucuk olanlari gec
    while (cur != NULL && cur->data < deger) {
        prev = cur;
        cur  = cur->next;
    }

    // artik yeni node, prev ile cur ARASINA girecek
    if (prev == NULL) {        // basa ekleme (bos liste de dahil)
        yeni->next = head;
        return yeni;
    }

    yeni->next = cur;          // cur NULL ise sona eklenmis olur, ayri if gerekmez
    prev->next = yeni;
    return head;
}

// =============================================================================
//  TESTLER
// =============================================================================

int main() {
    int d3[] = {10, 20, 30};

    {
        Node* a = listeYap(d3, 3);
        kontrol("1) uzunluk", "3", std::to_string(uzunluk(a)));
        kontrol("2) toplam",  "60", std::to_string(toplam(a)));
        kontrol("3) iceriyorMu(20)", "1", std::to_string(iceriyorMu(a, 20)));
        kontrol("3) iceriyorMu(99)", "0", std::to_string(iceriyorMu(a, 99)));
        listeyiSil(a);
    }
    {
        int d[] = {7, 42, 13, 5};
        Node* a = listeYap(d, 4);
        kontrol("4) enBuyuk", "42", std::to_string(enBuyuk(a)));
        kontrol("4) enBuyuk(bos)", "0", std::to_string(enBuyuk(NULL)));
        listeyiSil(a);
    }
    {
        Node* a = listeYap(d3, 3);
        a = basaEkle(a, 5);
        kontrol("5) basaEkle", "5,10,20,30", listeMetni(a));
        listeyiSil(a);
        Node* b = basaEkle(NULL, 1);
        kontrol("5) basaEkle(bos)", "1", listeMetni(b));
        listeyiSil(b);
    }
    {
        Node* a = listeYap(d3, 3);
        a = sonaEkle(a, 40);
        kontrol("6) sonaEkle", "10,20,30,40", listeMetni(a));
        listeyiSil(a);
        Node* b = sonaEkle(NULL, 1);
        kontrol("6) sonaEkle(bos)", "1", listeMetni(b));
        listeyiSil(b);
    }
    {
        Node* a = listeYap(d3, 3);
        kontrol("7) kthEleman(0)", "10", std::to_string(kthEleman(a, 0)));
        kontrol("7) kthEleman(2)", "30", std::to_string(kthEleman(a, 2)));
        kontrol("7) kthEleman(5)", "-1", std::to_string(kthEleman(a, 5)));
        listeyiSil(a);
    }
    {
        Node* a = listeYap(d3, 3); a = sil(a, 20);
        kontrol("8) sil orta", "10,30", listeMetni(a)); listeyiSil(a);
        Node* b = listeYap(d3, 3); b = sil(b, 10);
        kontrol("8) sil bas", "20,30", listeMetni(b)); listeyiSil(b);
        Node* c = listeYap(d3, 3); c = sil(c, 30);
        kontrol("8) sil son", "10,20", listeMetni(c)); listeyiSil(c);
        Node* e = listeYap(d3, 3); e = sil(e, 99);
        kontrol("8) sil yok", "10,20,30", listeMetni(e)); listeyiSil(e);
        kontrol("8) sil(bos)", "", listeMetni(sil(NULL, 5)));
    }
    {
        Node* a = listeYap(d3, 3);
        a = tersCevir(a);
        kontrol("9) tersCevir", "30,20,10", listeMetni(a));
        listeyiSil(a);
        kontrol("9) tersCevir(bos)", "", listeMetni(tersCevir(NULL)));
    }
    {
        int s[] = {10, 30, 50};
        Node* a = listeYap(s, 3);
        a = sirayaEkle(a, 40);
        kontrol("10) sirayaEkle orta", "10,30,40,50", listeMetni(a));
        a = sirayaEkle(a, 5);
        kontrol("10) sirayaEkle bas", "5,10,30,40,50", listeMetni(a));
        a = sirayaEkle(a, 99);
        kontrol("10) sirayaEkle son", "5,10,30,40,50,99", listeMetni(a));
        listeyiSil(a);
        Node* b = sirayaEkle(NULL, 7);
        kontrol("10) sirayaEkle(bos)", "7", listeMetni(b));
        listeyiSil(b);
    }

    std::cout << std::endl << "SONUC: " << basariliSayisi << " / " << toplamTest << std::endl;
    return 0;
}

// =============================================================================
//  SIK YAPILAN 5 HATA
// =============================================================================
//  1) cur = cur->next unutulur            -> sonsuz dongu
//  2) while (cur != NULL) ile son node     -> cur->next = yeni yazilamaz, cokme
//     aranir (dogrusu: cur->next != NULL)
//  3) delete edilen node'un next'i okunur  -> once ilerle, sonra delete
//  4) head degisti ama return edilmedi     -> cagiran taraf eski head'i tutar
//  5) head == NULL kontrolu atlanir        -> head->data ile segfault
// =============================================================================
