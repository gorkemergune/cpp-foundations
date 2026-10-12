// =============================================================================
//  WEEK 03 - LINKED LIST ALISTIRMALARI
//
//  NASIL CALISILIR:
//    1. Asagidaki fonksiyonlarin govdesini doldur (// TODO yazan yerler).
//    2. Derle ve calistir:
//         g++ -std=c++17 01_exercises.cpp -o ex && ./ex
//    3. Cikti sana her alistirma icin  [OK] / [HATA]  yazacak.
//    4. Takilirsan 00_schema.cpp'deki ilgili kalibi ac, bak, kapat, tekrar dene.
//
//  Sirayla git. 1-4 isinma, 5-8 asil is, 9-10 zor.
// =============================================================================

#include "iostream"
#include "string"

struct Node {
    int data;
    Node* next;
};

// -----------------------------------------------------------------------------
//  YARDIMCI FONKSIYONLAR - bunlar hazir, dokunma.
//  Alistirmalari test edebilmek icin gerekli.
// -----------------------------------------------------------------------------

// Diziden liste kurar:  listeYap({10,20,30}, 3) -> head -> [10]->[20]->[30]->NULL
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

void yazdir(Node* head) {
    std::cout << "head -> ";
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        std::cout << "[" << cur->data << "] -> ";
    }
    std::cout << "NULL" << std::endl;
}

void listeyiSil(Node* head) {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Listeyi "10,20,30" seklinde metne cevirir (test karsilastirmasi icin)
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
        std::cout << "[HATA] " << ad
                  << "  | beklenen: " << beklenen
                  << "  | senin: " << bulunan << std::endl;
    }
}

// =============================================================================
//  ALISTIRMA 1 - uzunluk
//  Listedeki node sayisini dondur. Bos liste icin 0.
//
//  SEMA:  head -> [10] -> [20] -> [30] -> NULL      cevap: 3
//
//  IPUCU: gezinme kalibi + bir sayac.
// =============================================================================
int uzunluk(Node* head) {
    // TODO: bir sayac tanimla, listeyi gez, her node'da sayaci arttir.
    return 0;
}

// =============================================================================
//  ALISTIRMA 2 - toplam
//  Tum data degerlerinin toplamini dondur. Bos liste icin 0.
//
//  SEMA:  [10] -> [20] -> [30]      cevap: 60
// =============================================================================
int toplam(Node* head) {
    // TODO
    return 0;
}

// =============================================================================
//  ALISTIRMA 3 - iceriyorMu
//  Listede 'deger' varsa true, yoksa false dondur.
//
//  IPUCU: buldugun anda hemen return true; dongunun bitmesini bekleme.
// =============================================================================
bool iceriyorMu(Node* head, int deger) {
    // TODO
    return false;
}

// =============================================================================
//  ALISTIRMA 4 - enBuyuk
//  En buyuk data degerini dondur. Liste bos ise 0 dondur.
//
//  IPUCU: ilk node'u "simdilik en buyuk" kabul et, sonra 2. node'tan itibaren gez.
//         Dikkat: head == NULL kontrolunu en basta yap.
// =============================================================================
int enBuyuk(Node* head) {
    // TODO
    return 0;
}

// =============================================================================
//  ALISTIRMA 5 - basaEkle
//  Yeni bir node olustur ve listenin BASINA koy. Yeni head'i dondur.
//
//  SEMA:
//    ONCE:   head -> [20] -> [30] -> NULL
//    SONRA:  head -> [10] -> [20] -> [30] -> NULL      (basaEkle(head, 10))
//
//  IPUCU: 3 satir. new Node -> data/next doldur -> head = yeni.
//         Bos listede de otomatik calisir, ayri if'e gerek yok. Neden?
// =============================================================================
Node* basaEkle(Node* head, int deger) {
    // TODO
    return head;
}

// =============================================================================
//  ALISTIRMA 6 - sonaEkle
//  Yeni node'u listenin SONUNA koy. Yeni head'i dondur.
//
//  SEMA:
//    ONCE:   head -> [10] -> [20] -> NULL
//    SONRA:  head -> [10] -> [20] -> [30] -> NULL
//
//  IPUCU: IKI DURUM var:
//     a) head == NULL  -> yeni node'un kendisi head olur
//     b) degilse       -> while (cur->next != NULL) ile sona yuru, cur->next = yeni
// =============================================================================
Node* sonaEkle(Node* head, int deger) {
    // TODO
    return head;
}

// =============================================================================
//  ALISTIRMA 7 - kthEleman
//  k. indeksteki (0'dan baslayarak) node'un data'sini dondur.
//  k gecersizse (negatif veya liste kisa) -1 dondur.
//
//  SEMA:  head -> [10] -> [20] -> [30] -> NULL
//         indeks:   0       1       2
//         kthEleman(head, 1) -> 20
//         kthEleman(head, 5) -> -1
//
//  IPUCU: k adim ilerle ama her adimda cur != NULL mi diye bak.
// =============================================================================
int kthEleman(Node* head, int k) {
    // TODO
    return -1;
}

// =============================================================================
//  ALISTIRMA 8 - sil
//  'deger'e sahip ILK node'u listeden cikar ve bellekten sil.
//  Yeni head'i dondur. Deger yoksa listeyi oldugu gibi dondur.
//
//  SEMA (ortadaki):
//              prev      cur
//    head -> [10] ->   [20] -> [30] -> NULL
//    prev->next = cur->next;   delete cur;
//    head -> [10] -> [30] -> NULL
//
//  SEMA (ilk node):   head = cur->next;  delete cur;
//
//  IPUCU: prev + cur ikilisini kullan. Dongu bittikten sonra 3 ihtimali ayir:
//         cur == NULL (yok) / prev == NULL (ilk) / digeri (orta-son).
// =============================================================================
Node* sil(Node* head, int deger) {
    // TODO
    return head;
}

// =============================================================================
//  ALISTIRMA 9 - tersCevir  (ZOR)
//  Listeyi tersine cevir. YENI node olusturmak YASAK; sadece next oklarini cevir.
//
//  SEMA:
//    ONCE:   head -> [10] -> [20] -> [30] -> NULL
//    SONRA:  head -> [30] -> [20] -> [10] -> NULL
//
//  IPUCU: uc pointer: prev(NULL), cur(head), next.
//         Dongude sirayla: next'i yedekle, cur->next = prev, prev=cur, cur=next.
//         Dongu bitince yeni head = prev.
// =============================================================================
Node* tersCevir(Node* head) {
    // TODO
    return head;
}

// =============================================================================
//  ALISTIRMA 10 - sirayaEkle  (ZOR)
//  Liste KUCUKTEN BUYUGE sirali. Yeni degeri sirayi bozmayacak yere ekle.
//
//  SEMA:  head -> [10] -> [30] -> [50] -> NULL,  sirayaEkle(head, 40)
//         head -> [10] -> [30] -> [40] -> [50] -> NULL
//
//  IPUCU: prev+cur ile "cur->data < deger" oldugu surece ilerle.
//         Durdugunda yeni node prev ile cur ARASINA girer.
//         prev == NULL ise basa ekleme durumudur.
// =============================================================================
Node* sirayaEkle(Node* head, int deger) {
    // TODO
    return head;
}

// =============================================================================
//  TESTLER - dokunmana gerek yok, sadece calistir.
// =============================================================================

int main() {
    int d3[] = {10, 20, 30};
    int bos[] = {0};

    // --- 1. uzunluk ---
    {
        Node* a = listeYap(d3, 3);
        kontrol("1) uzunluk([10,20,30])", "3", std::to_string(uzunluk(a)));
        kontrol("1) uzunluk(bos)",        "0", std::to_string(uzunluk(NULL)));
        listeyiSil(a);
    }

    // --- 2. toplam ---
    {
        Node* a = listeYap(d3, 3);
        kontrol("2) toplam([10,20,30])", "60", std::to_string(toplam(a)));
        kontrol("2) toplam(bos)",         "0", std::to_string(toplam(NULL)));
        listeyiSil(a);
    }

    // --- 3. iceriyorMu ---
    {
        Node* a = listeYap(d3, 3);
        kontrol("3) iceriyorMu(20)", "1", std::to_string(iceriyorMu(a, 20)));
        kontrol("3) iceriyorMu(99)", "0", std::to_string(iceriyorMu(a, 99)));
        kontrol("3) iceriyorMu(bos liste)", "0", std::to_string(iceriyorMu(NULL, 1)));
        listeyiSil(a);
    }

    // --- 4. enBuyuk ---
    {
        int d[] = {7, 42, 13, 5};
        Node* a = listeYap(d, 4);
        kontrol("4) enBuyuk([7,42,13,5])", "42", std::to_string(enBuyuk(a)));
        kontrol("4) enBuyuk(bos)",          "0", std::to_string(enBuyuk(NULL)));
        listeyiSil(a);
    }

    // --- 5. basaEkle ---
    {
        Node* a = listeYap(d3, 3);
        a = basaEkle(a, 5);
        kontrol("5) basaEkle(5)", "5,10,20,30", listeMetni(a));
        listeyiSil(a);

        Node* b = basaEkle(NULL, 1);
        kontrol("5) basaEkle bos listeye", "1", listeMetni(b));
        listeyiSil(b);
    }

    // --- 6. sonaEkle ---
    {
        Node* a = listeYap(d3, 3);
        a = sonaEkle(a, 40);
        kontrol("6) sonaEkle(40)", "10,20,30,40", listeMetni(a));
        listeyiSil(a);

        Node* b = sonaEkle(NULL, 1);
        kontrol("6) sonaEkle bos listeye", "1", listeMetni(b));
        listeyiSil(b);
    }

    // --- 7. kthEleman ---
    {
        Node* a = listeYap(d3, 3);
        kontrol("7) kthEleman(0)", "10", std::to_string(kthEleman(a, 0)));
        kontrol("7) kthEleman(2)", "30", std::to_string(kthEleman(a, 2)));
        kontrol("7) kthEleman(5)", "-1", std::to_string(kthEleman(a, 5)));
        listeyiSil(a);
    }

    // --- 8. sil ---
    {
        Node* a = listeYap(d3, 3);
        a = sil(a, 20);
        kontrol("8) sil(20) ortadan", "10,30", listeMetni(a));
        listeyiSil(a);

        Node* b = listeYap(d3, 3);
        b = sil(b, 10);
        kontrol("8) sil(10) bastan", "20,30", listeMetni(b));
        listeyiSil(b);

        Node* c = listeYap(d3, 3);
        c = sil(c, 30);
        kontrol("8) sil(30) sondan", "10,20", listeMetni(c));
        listeyiSil(c);

        Node* e = listeYap(d3, 3);
        e = sil(e, 99);
        kontrol("8) sil(99) olmayan deger", "10,20,30", listeMetni(e));
        listeyiSil(e);

        Node* f = sil(NULL, 5);
        kontrol("8) sil(bos liste)", "", listeMetni(f));
    }

    // --- 9. tersCevir ---
    {
        Node* a = listeYap(d3, 3);
        a = tersCevir(a);
        kontrol("9) tersCevir([10,20,30])", "30,20,10", listeMetni(a));
        listeyiSil(a);

        Node* b = listeYap(bos, 1);
        b = tersCevir(b);
        kontrol("9) tersCevir(tek elemanli)", "0", listeMetni(b));
        listeyiSil(b);

        Node* c = tersCevir(NULL);
        kontrol("9) tersCevir(bos)", "", listeMetni(c));
    }

    // --- 10. sirayaEkle ---
    {
        int s[] = {10, 30, 50};
        Node* a = listeYap(s, 3);
        a = sirayaEkle(a, 40);
        kontrol("10) sirayaEkle(40) ortaya", "10,30,40,50", listeMetni(a));
        a = sirayaEkle(a, 5);
        kontrol("10) sirayaEkle(5) basa",    "5,10,30,40,50", listeMetni(a));
        a = sirayaEkle(a, 99);
        kontrol("10) sirayaEkle(99) sona",   "5,10,30,40,50,99", listeMetni(a));
        listeyiSil(a);

        Node* b = sirayaEkle(NULL, 7);
        kontrol("10) sirayaEkle bos listeye", "7", listeMetni(b));
        listeyiSil(b);
    }

    std::cout << std::endl;
    std::cout << "SONUC: " << basariliSayisi << " / " << toplamTest << std::endl;
    return 0;
}
