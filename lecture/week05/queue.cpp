#include <iostream>

/*
 * Bu uygulama "bağlı liste (linked list)" ile yapılmıştır:
 *
 *   frontPtr -> [A | next] -> [B | next] -> [C | NULL] <- backPtr
 *
 * - Queue FIFO'dur (First In, First Out): ilk giren ilk çıkar.
 *   Stack ise LIFO'ydu (son giren ilk çıkar) - tek fark bu!
 * - frontPtr en ÖNDEKİ (en eski) düğümü, backPtr en ARKADAKİ (en yeni) düğümü gösterir.
 * - Boş queue'da ikisi de NULL'dır.
 * - enqueue ARKADAN ekler, dequeue ÖNDEN siler. İki uçtan da pointer tuttuğumuz
 *   için her ikisi de O(1)'dir. (backPtr olmasa her ekleme icin listeyi
 *   sonuna kadar gezmemiz gerekirdi -> O(n))
 */

// Queue'nun hangi tipte veri tuttuğunu burada belirliyoruz.
// Tek satırı değiştirerek tüm queue'yu int, double, char... yapabiliriz.
typedef char QueueItemType;

class Queue {
public:
    Queue();
    Queue(const Queue& Q);
    ~Queue();

    bool isEmpty() const;
    bool enqueue(QueueItemType item);
    bool dequeue();
    bool dequeue(QueueItemType& queueFront);
    bool getFront(QueueItemType& queueFront) const;

private:

    struct QueueNode {
        QueueItemType item;
        QueueNode *next;
    };

    QueueNode *backPtr;
    QueueNode *frontPtr;
};

// Constructor: başlangıçta queue boştur, iki pointer da hiçbir yeri göstermez.
// Bunu yazmazsan pointer'lar çöp (garbage) değer taşır ve program çöker!
Queue::Queue() {
    frontPtr = NULL;
    backPtr = NULL;
}

// Copy constructor: yeni queue'yu başka bir queue'nun KOPYASI olarak kurar.
// Dikkat: sadece "frontPtr = Q.frontPtr" yazmak YETMEZ! O zaman iki queue
// aynı düğümleri paylaşır (shallow copy); biri delete edince diğeri çöker.
// Bu yüzden her düğümü tek tek yeniden oluşturuyoruz (deep copy). Süre: O(n)
Queue::Queue(const Queue& Q) {
    frontPtr = NULL;
    backPtr = NULL;

    // Kaynak queue'yu baştan sona gez, her item'ı kendi queue'muza ekle.
    for (QueueNode *cur = Q.frontPtr; cur != NULL; cur = cur->next) {
        enqueue(cur->item);
    }
}

// Destructor: queue yok olurken geride kalan tüm düğümleri siler.
// Yazmazsan new ile ayrılan bellek asla geri verilmez -> memory leak.
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// isEmpty: Queue boş mu?
// frontPtr == NULL ise hiç düğüm yok demektir. Süre: O(1)
bool Queue::isEmpty() const {
    if (frontPtr == NULL) {
        return true;
    } else {
        return false;
    }
}

// enqueue: Kuyruğun SONUNA yeni eleman ekler.
// Adımlar:
//   1) Yeni düğüm oluştur, next'i NULL yap (artık son düğüm bu)
//   2) Queue boşsa: tek düğüm var, frontPtr de backPtr de onu göstersin
//      Queue doluysa: eski son düğümün next'ini yeni düğüme bağla
//   3) backPtr'yi yeni düğüme çevir
// Başarılıysa true, bellek ayrılamadıysa false döner. Süre: O(1)
bool Queue::enqueue(QueueItemType item) {
    QueueNode *newNode = new QueueNode;
    if (newNode == NULL) {
        return false; // bellek ayrılamadı
    }
    newNode->item = item;
    newNode->next = NULL; // 1) yeni düğüm sonda, arkasında kimse yok

    if (isEmpty()) {
        frontPtr = newNode; // 2a) ilk düğüm: hem ön hem arka o
    } else {
        backPtr->next = newNode; // 2b) eski sonu yeni düğüme bağla
    }
    backPtr = newNode; // 3) yeni arka artık bu
    return true;
}

// dequeue: ÖNDEKİ elemanı siler (değeri döndürmez!).
// Adımlar:
//   1) Boşsa silinecek bir şey yok -> false
//   2) Silinecek düğümü temp'te sakla (yoksa adresini kaybedip leak olur)
//   3) frontPtr'yi bir sonraki düğüme kaydır
//   4) Queue boşaldıysa backPtr'yi de NULL yap!
//      (Yoksa backPtr silinmiş belleği gösterir = dangling pointer)
//   5) temp'i delete et
// Süre: O(1)
bool Queue::dequeue() {
    if (isEmpty()) {
        return false; // queue boş
    }
    QueueNode *temp = frontPtr;
    frontPtr = frontPtr->next;

    if (frontPtr == NULL) {
        backPtr = NULL; // 4) son düğümü de sildik, queue tamamen boşaldı
    }
    delete temp;
    return true;
}

// dequeue (overload): Öndeki elemanı hem OKUR hem SİLER.
// Üstteki dequeue()'dan tek farkı, silmeden önce değeri queueFront'a yazmasıdır.
// Aynı kodu iki kere yazmamak için getFront + dequeue'yu birleştiriyoruz. Süre: O(1)
bool Queue::dequeue(QueueItemType& queueFront) {
    if (!getFront(queueFront)) {
        return false; // queue boş, okunacak eleman yok
    }
    return dequeue();
}

// getFront: Öndeki elemanı SİLMEDEN okur (diğer dillerdeki peek/front).
// Değer referans parametre (queueFront) ile geri verilir,
// dönüş değeri başarı durumudur. Boş queue'da false döner. Süre: O(1)
bool Queue::getFront(QueueItemType& queueFront) const {
    if (isEmpty()) {
        return false;
    }
    queueFront = frontPtr->item;
    return true;
}

// Test sonucunu okunaklı yazdıran yardımcı fonksiyon
void check(const char *name, bool condition) {
    std::cout << (condition ? "[OK]   " : "[FAIL] ") << name << std::endl;
}

int main() {
    Queue q;
    char c;

    std::cout << "--- 1) Bos queue testleri ---" << std::endl;
    check("yeni queue bos", q.isEmpty());
    check("bos queue'da dequeue false doner", !q.dequeue());
    check("bos queue'da getFront false doner", !q.getFront(c));

    std::cout << "\n--- 2) enqueue / getFront ---" << std::endl;
    check("enqueue('A')", q.enqueue('A'));
    check("enqueue('B')", q.enqueue('B'));
    check("enqueue('C')", q.enqueue('C'));
    check("queue artik bos degil", !q.isEmpty());
    check("getFront basarili", q.getFront(c));
    check("on 'A' (ILK giren)", c == 'A');

    std::cout << "\n--- 3) dequeue (FIFO sirasi: A, B, C) ---" << std::endl;
    check("dequeue deger dondurur", q.dequeue(c));
    std::cout << "Cikan: " << c << std::endl;
    check("cikan 'A'", c == 'A');
    check("dequeue #2", q.dequeue(c));
    std::cout << "Cikan: " << c << std::endl;
    check("cikan 'B'", c == 'B');
    check("dequeue #3", q.dequeue(c));
    std::cout << "Cikan: " << c << std::endl;
    check("cikan 'C'", c == 'C');
    check("queue tekrar bos", q.isEmpty());
    check("bos queue'da dequeue yine false", !q.dequeue());

    std::cout << "\n--- 4) Bosalttiktan sonra tekrar kullanilabilir mi? ---" << std::endl;
    // Bu test dequeue'daki backPtr = NULL satirini kontrol eder.
    // O satir olmasa burada dangling pointer'a yazardik.
    check("enqueue('X')", q.enqueue('X'));
    check("getFront 'X'", q.getFront(c) && c == 'X');

    std::cout << "\n--- 5) Copy constructor (deep copy) ---" << std::endl;
    Queue original;
    original.enqueue('1');
    original.enqueue('2');
    original.enqueue('3');

    Queue copy(original); // kopya olustur

    check("kopya ayni sirayla okunuyor: 1", copy.dequeue(c) && c == '1');
    check("kopya ayni sirayla okunuyor: 2", copy.dequeue(c) && c == '2');
    // Kopyadan 2 eleman sildik; orijinal etkilenmemeli (deep copy kaniti)
    check("orijinalin onu halen '1'", original.getFront(c) && c == '1');
    check("kopyada 1 eleman kaldi", copy.dequeue(c) && c == '3' && copy.isEmpty());
    check("orijinal halen dolu", !original.isEmpty());

    std::cout << "\n--- 6) Ornek uygulama: kelimeyi sirayla yazdir ---" << std::endl;
    // Stack ile yapsak kelime TERS yazilirdi; queue ile ayni sirada cikar.
    const char *word = "yeditepe";
    Queue q2;
    for (int i = 0; word[i] != '\0'; i++) {
        q2.enqueue(word[i]);
    }
    std::cout << word << " -> ";
    while (q2.dequeue(c)) { // queue bosalana kadar oku ve sil
        std::cout << c;
    }
    std::cout << std::endl;

    std::cout << "\n--- 7) Ornek uygulama: siraya giren musteriler ---" << std::endl;
    Queue bank;
    std::cout << "Siraya giriyor: Ali, Beyza, Can" << std::endl;
    bank.enqueue('A'); // Ali
    bank.enqueue('B'); // Beyza
    bank.enqueue('C'); // Can

    while (bank.dequeue(c)) {
        std::cout << "Gise cagiriyor: " << c << std::endl;
    }
    std::cout << "Sira bosaldi: " << (bank.isEmpty() ? "evet" : "hayir") << std::endl;

    return 0;
}
