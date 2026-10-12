// =============================================================================
//  WEEK 03 - LINKED LIST SEMALARI
//  Her islem icin: once SEMA (cizim), sonra KALIP (kod).
//  Derle:  g++ -std=c++17 00_schema.cpp -o schema && ./schema
// =============================================================================

#include "iostream"

// -----------------------------------------------------------------------------
//  0) NODE NEDIR?
// -----------------------------------------------------------------------------
//  Bir node = 1 veri + 1 adres.
//
//        +------+------+
//        | data | next |        next = bir sonraki node'un ADRESI
//        +------+------+
//
//  Liste = birbirini isaret eden node'lar zinciri. Son node'un next'i NULL.
//
//    head
//     |
//     v
//   +----+---+    +----+---+    +----+----+
//   | 10 | *-|--> | 20 | *-|--> | 30 | /  |   ( / = NULL )
//   +----+---+    +----+---+    +----+----+
//
//  ONEMLI: "head" bir node DEGIL, sadece ilk node'u gosteren bir pointer.
// -----------------------------------------------------------------------------

struct Node {
    int data;
    Node* next;
};

// -----------------------------------------------------------------------------
//  1) BOS LISTE
// -----------------------------------------------------------------------------
//    head --> NULL          Bos liste demek: head == NULL
//
//  KALIP:
//      Node* head = NULL;
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
//  2) YENI NODE URETME (her zaman 3 adim)
// -----------------------------------------------------------------------------
//      Node* n = new Node();   // 1) yer ac
//      n->data = 42;           // 2) veriyi koy
//      n->next = NULL;         // 3) next'i MUTLAKA doldur  <-- en sik yapilan hata
//
//  Not: n.data DEGIL, n->data. Cunku n bir pointer.
//       (*n).data ile n->data ayni seydir; "->" kisayoldur.
// -----------------------------------------------------------------------------

Node* yeniNode(int deger) {
    Node* n = new Node();
    n->data = deger;
    n->next = NULL;
    return n;
}

// -----------------------------------------------------------------------------
//  3) BASA EKLEME  (push_front)  -  O(1), en kolayi
// -----------------------------------------------------------------------------
//  ONCE:    head --> [20|*] --> [30|/]
//
//  1) yeni node:              [10| ? ]
//  2) n->next = head;         [10| *] --> [20|*] --> [30|/]
//  3) head = n;      head --> [10| *] --> [20|*] --> [30|/]
//
//  SONRA:   head --> [10|*] --> [20|*] --> [30|/]
//
//  SIRA ONEMLI: once n->next, sonra head. Ters yaparsan listeyi kaybedersin.
// -----------------------------------------------------------------------------

Node* basaEkle(Node* head, int deger) {
    Node* n = yeniNode(deger);
    n->next = head;   // yeni node eski basi gosterir
    head = n;         // yeni bas = n
    return head;      // DEGISEN head'i geri vermeyi unutma
}

// -----------------------------------------------------------------------------
//  4) SONA EKLEME  (push_back)
// -----------------------------------------------------------------------------
//  Iki durum var, ikisini de yazmak zorundasin:
//
//  DURUM A: liste bos          head --> NULL
//           head = n;          head --> [40|/]
//
//  DURUM B: liste dolu
//           sona kadar yuru:
//                                      cur
//           head --> [10|*] --> [20|*] --> [30|/]        <-- cur->next == NULL
//           cur->next = n;
//           head --> [10|*] --> [20|*] --> [30|*] --> [40|/]
//
//  SON NODE'U BULMA KALIBI:  (dikkat: cur != NULL degil, cur->next != NULL)
//      Node* cur = head;
//      while (cur->next != NULL) { cur = cur->next; }
// -----------------------------------------------------------------------------

Node* sonaEkle(Node* head, int deger) {
    Node* n = yeniNode(deger);

    if (head == NULL) {       // DURUM A
        return n;
    }

    Node* cur = head;         // DURUM B
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = n;
    return head;              // head degismedi ama yine de donduruyoruz
}

// -----------------------------------------------------------------------------
//  5) GEZINME (traverse)  -  TUM listeyi dolasmanin kalibi
// -----------------------------------------------------------------------------
//    cur       cur       cur       cur
//     |         |         |         |
//     v         v         v         v
//   [10|*]-->[20|*]-->[30|/]       NULL   <-- dongu burada biter
//
//  KALIP 1 (while):
//      Node* cur = head;
//      while (cur != NULL) {
//          ... cur->data ...
//          cur = cur->next;      // <-- bunu unutursan SONSUZ DONGU
//      }
//
//  KALIP 2 (for) - ayni sey, daha kisa:
//      for (Node* cur = head; cur != NULL; cur = cur->next) { ... }
//
//  KURAL: head'i ASLA dongude ilerletme (head = head->next). Listeyi kaybedersin.
//         Her zaman bir kopya pointer (cur) kullan.
// -----------------------------------------------------------------------------

void yazdir(Node* head) {
    std::cout << "head -> ";
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        std::cout << "[" << cur->data << "] -> ";
    }
    std::cout << "NULL" << std::endl;
}

int uzunluk(Node* head) {
    int sayac = 0;
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        sayac++;
    }
    return sayac;
}

// -----------------------------------------------------------------------------
//  6) ARAMA  -  gezinme kalibinin icine if koymak
// -----------------------------------------------------------------------------
//  Bulursan: o node'un adresini dondur.  Bulamazsan: NULL dondur.
// -----------------------------------------------------------------------------

Node* ara(Node* head, int deger) {
    for (Node* cur = head; cur != NULL; cur = cur->next) {
        if (cur->data == deger) {
            return cur;
        }
    }
    return NULL;   // bulunamadi
}

// -----------------------------------------------------------------------------
//  7) ARAYA EKLEME (belirli bir node'dan SONRA)
// -----------------------------------------------------------------------------
//           p                    p->next
//  ONCE:  [20|*] -------------> [30|/]
//
//  1) n->next = p->next;        n:[25|*] --> [30|/]
//  2) p->next = n;              [20|*] --> [25|*] --> [30|/]
//
//  SIRA ONEMLI. Once 2'yi yaparsan [30] node'una giden tek baglanti kopar.
// -----------------------------------------------------------------------------

void sonrasinaEkle(Node* p, int deger) {
    if (p == NULL) { return; }     // guvenlik kontrolu

    Node* n = yeniNode(deger);
    n->next = p->next;             // 1
    p->next = n;                   // 2
}

// -----------------------------------------------------------------------------
//  8) BASTAN SILME
// -----------------------------------------------------------------------------
//  ONCE:   head --> [10|*] --> [20|*] --> [30|/]
//
//  1) silinecegi tut:   Node* temp = head;        temp --> [10|*]
//  2) head'i kaydir:    head = head->next;        head --> [20|*]
//  3) bellegi birak:    delete temp;
//
//  SONRA:  head --> [20|*] --> [30|/]
//
//  "delete temp" once yapilirsa head->next artik cop adrestir -> cokme.
// -----------------------------------------------------------------------------

Node* bastanSil(Node* head) {
    if (head == NULL) { return NULL; }   // bos listeyi silmeye calisma

    Node* temp = head;
    head = head->next;
    delete temp;
    return head;
}

// -----------------------------------------------------------------------------
//  9) ARADAN SILME  -  prev + cur IKILISI (en cok sinavda cikan kalip)
// -----------------------------------------------------------------------------
//  Bir node'u silmek icin ONCESINDEKI node'u bilmen gerekir.
//  Cunku tek yonlu listede geriye gidemezsin. Bu yuzden 2 pointer tasiriz:
//
//           prev        cur
//            |           |
//            v           v
//  head --> [10|*] --> [20|*] --> [30|/]
//
//  1) prev->next = cur->next;    // zinciri kopmasin diye kopru kur
//
//  head --> [10|*] ------------> [30|/]
//                   [20|*]  <-- artik kimse gostermiyor (orphan)
//
//  2) cur->next = NULL;  delete cur;  cur = NULL;
//
//  IKI POINTER ILERLETME KALIBI:
//      Node* prev = NULL;
//      Node* cur  = head;
//      while (cur != NULL && cur->data != hedef) {
//          prev = cur;
//          cur  = cur->next;
//      }
//      // dongu bitti. Simdi 3 olasilik var:
//      //   cur == NULL          -> bulunamadi
//      //   prev == NULL         -> silinecek olan ILK node
//      //   digeri               -> ortadaki/sondaki node
// -----------------------------------------------------------------------------

Node* sil(Node* head, int deger) {
    Node* prev = NULL;
    Node* cur  = head;

    while (cur != NULL && cur->data != deger) {
        prev = cur;
        cur  = cur->next;
    }

    if (cur == NULL) {           // 1) bulunamadi
        return head;
    }

    if (prev == NULL) {          // 2) ilk node siliniyor -> head degisir
        head = cur->next;
    } else {                     // 3) ortada veya sonda
        prev->next = cur->next;
    }

    cur->next = NULL;            // kopardigimiz node'u temizle
    delete cur;
    cur = NULL;
    return head;
}

// -----------------------------------------------------------------------------
//  10) TUM LISTEYI SILME (bellek sizintisini onleme)
// -----------------------------------------------------------------------------
//  HATA:                            DOGRU:
//    while (cur != NULL) {            while (cur != NULL) {
//        delete cur;                      Node* temp = cur;
//        cur = cur->next;  // <-- X       cur = cur->next;   // ONCE ilerle
//    }                                    delete temp;       // SONRA sil
//                                     }
//  Sildikten sonra cur->next okunamaz. Once adresi kopyala, sonra sil.
// -----------------------------------------------------------------------------

Node* temizle(Node* head) {
    Node* cur = head;
    while (cur != NULL) {
        Node* temp = cur;
        cur = cur->next;   // once ilerle
        delete temp;       // sonra sil
    }
    return NULL;           // head'i NULL yap, yoksa "dangling pointer" kalir
}

// -----------------------------------------------------------------------------
//  11) TERSINE CEVIRME  -  uc pointer dansi
// -----------------------------------------------------------------------------
//  prev     cur      next
//   |        |        |
//   v        v        v
//  NULL   [10|*]-->[20|*]-->[30|/]
//
//  Her adimda: next'i sakla, cur'un okunu geriye cevir, ikisini kaydir.
//
//      Node* prev = NULL;
//      Node* cur  = head;
//      while (cur != NULL) {
//          Node* next = cur->next;   // 1) yedekle (yoksa gerisini kaybederiz)
//          cur->next  = prev;        // 2) oku ters cevir
//          prev = cur;               // 3) kaydir
//          cur  = next;              // 4) kaydir
//      }
//      head = prev;                  // dongu bitince prev son node'tur
// -----------------------------------------------------------------------------

Node* tersCevir(Node* head) {
    Node* prev = NULL;
    Node* cur  = head;

    while (cur != NULL) {
        Node* next = cur->next;
        cur->next  = prev;
        prev = cur;
        cur  = next;
    }
    return prev;
}

// =============================================================================
//  DENEME: yukaridaki kaliplarin hepsi burada calisiyor
// =============================================================================

int main() {
    Node* head = NULL;                     // bos liste

    // sona ekleyerek 10 20 30 kuralim
    head = sonaEkle(head, 10);
    head = sonaEkle(head, 20);
    head = sonaEkle(head, 30);
    std::cout << "sonaEkle x3    : "; yazdir(head);

    head = basaEkle(head, 5);
    std::cout << "basaEkle(5)    : "; yazdir(head);

    std::cout << "uzunluk        : " << uzunluk(head) << std::endl;

    Node* bulunan = ara(head, 20);
    std::cout << "ara(20)        : " << (bulunan != NULL ? "bulundu" : "yok") << std::endl;

    sonrasinaEkle(bulunan, 25);            // 20'den sonra 25
    std::cout << "sonrasinaEkle  : "; yazdir(head);

    head = bastanSil(head);
    std::cout << "bastanSil      : "; yazdir(head);

    head = sil(head, 25);
    std::cout << "sil(25)        : "; yazdir(head);

    head = sil(head, 999);                 // olmayan deger: liste bozulmamali
    std::cout << "sil(999)       : "; yazdir(head);

    head = tersCevir(head);
    std::cout << "tersCevir      : "; yazdir(head);

    head = temizle(head);
    std::cout << "temizle        : "; yazdir(head);

    return 0;
}

// =============================================================================
//  ALTIN KURALLAR (sinavda hata yapmamak icin)
// =============================================================================
//  1. Pointer'da nokta yok:  cur->data   (cur.data DEGIL)
//  2. new Node() yaptin mi, next'i hemen NULL yap.
//  3. Dongude head'i ilerletme; cur kopyasini kullan.
//  4. cur = cur->next satirini yazmayi unutma -> sonsuz dongu.
//  5. cur->data yazmadan once "cur != NULL mu?" diye dusun.
//  6. && sirasi onemli:  cur != NULL && cur->data == x   (ters yazarsan cokersin)
//  7. Silmede once kopru kur (prev->next = cur->next), sonra delete.
//  8. Silinen node'u gosteren pointer'i NULL'a cek.
//  9. head degistiren fonksiyon head'i dondurmeli (veya Node*& ile almali).
// 10. Son node'u ararken:  while (cur->next != NULL)
//     Tum listeyi gezerken: while (cur != NULL)
// =============================================================================
