#include <iostream>

/*
 * Bu uygulama "bağlı liste (linked list)" ile yapılmıştır:
 *
 *   top -> [C | next] -> [B | next] -> [A | NULL]
 *
 * - top her zaman en üstteki (en son eklenen) düğümü gösterir.
 * - Boş stack'te top == NULL'dır.
 * - Hem push hem pop sadece listenin BAŞINDA çalışır, bu yüzden O(1)'dir.
 */

class Stack {
public:
    Stack();

    bool isEmpty();
    bool push(char c);
    bool pop();
    bool getTop(char &c);

private:
    struct StackNode {
        char data;
        StackNode *next;
    };

    StackNode *top;
};

// Constructor: başlangıçta stack boştur, top hiçbir yeri göstermez.
// Bunu yazmazsan top çöp (garbage) değer taşır ve program çöker!
Stack::Stack() {
    top = NULL;
}

// isEmpty: Stack boş mu?
// top == NULL ise hiç düğüm yok demektir. Süre: O(1)
bool Stack::isEmpty() {
    if (top == NULL) {
        return true;
    } else {
        return false;
    }
}

// push: Yığının tepesine yeni eleman ekler.
// Adımlar:
//   1) Yeni düğüm oluştur
//   2) Düğümün next'ini mevcut top yap (eski tepeye bağla)
//   3) top'u yeni düğüme çevir
// Başarılıysa true, bellek ayrılamadıysa false döner. Süre: O(1)
bool Stack::push(char c) {
    StackNode *newNode = new StackNode;
    if (newNode == NULL) {
        return false; // bellek ayrılamadı
    }
    newNode->data = c;
    newNode->next = top; // 2) eski tepeye bağla
    top = newNode;       // 3) yeni tepe artık bu
    return true;
}

// pop: Tepedeki elemanı siler (değeri döndürmez!).
// Adımlar:
//   1) Boşsa silinecek bir şey yok -> false
//   2) Silinecek düğümü temp'te sakla (yoksa adresini kaybedip leak olur)
//   3) top'u bir alttaki düğüme kaydır
//   4) temp'i delete et
// Süre: O(1)
bool Stack::pop() {
    if (isEmpty()) {
        return false; // stack boş
    }
    StackNode *temp = top;
    top = top->next;
    delete temp;
    return true;
}

// getTop: Tepedeki elemanı SİLMEDEN okur (diğer dillerdeki peek/top).
// Değer referans parametre (c) ile geri verilir, dönüş değeri başarı durumudur.
// Boş stack'te okunacak eleman olmadığı için false döner. Süre: O(1)
bool Stack::getTop(char &c) {
    if (isEmpty()) {
        return false;
    }
    c = top->data;
    return true;
}

// Test sonucunu okunaklı yazdıran yardımcı fonksiyon
void check(const char *name, bool condition) {
    std::cout << (condition ? "[OK]   " : "[FAIL] ") << name << std::endl;
}

int main() {
    Stack s;
    char c;

    std::cout << "--- 1) Bos stack testleri ---" << std::endl;
    check("yeni stack bos", s.isEmpty());
    check("bos stack'te pop false doner", !s.pop());
    check("bos stack'te getTop false doner", !s.getTop(c));

    std::cout << "\n--- 2) push / getTop ---" << std::endl;
    check("push('A')", s.push('A'));
    check("push('B')", s.push('B'));
    check("push('C')", s.push('C'));
    check("stack artik bos degil", !s.isEmpty());
    check("getTop basarili", s.getTop(c));
    check("tepe 'C' (son giren)", c == 'C');

    std::cout << "\n--- 3) pop (LIFO sirasi: C, B, A) ---" << std::endl;
    s.getTop(c);
    std::cout << "Tepe: " << c << " -> pop" << std::endl;
    check("pop #1", s.pop());
    s.getTop(c);
    check("yeni tepe 'B'", c == 'B');
    std::cout << "Tepe: " << c << " -> pop" << std::endl;
    check("pop #2", s.pop());
    s.getTop(c);
    check("yeni tepe 'A'", c == 'A');
    std::cout << "Tepe: " << c << " -> pop" << std::endl;
    check("pop #3", s.pop());
    check("stack tekrar bos", s.isEmpty());
    check("bos stack'te pop yine false", !s.pop());

    std::cout << "\n--- 4) Ornek uygulama: kelimeyi tersten yazdir ---" << std::endl;
    const char *word = "yeditepe";
    Stack s2;
    for (int i = 0; word[i] != '\0'; i++) {
        s2.push(word[i]);
    }
    std::cout << word << " -> ";
    while (s2.getTop(c)) { // getTop false donene kadar = stack bosalana kadar
        std::cout << c;
        s2.pop();
    }
    std::cout << std::endl;

    std::cout << "\n--- 5) Ornek uygulama: parantez dengesi kontrolu ---" << std::endl;
    const char *exprs[] = {"(a+b)*[c-d]", "((a+b)", "{[()]}", "([)]"};
    for (int k = 0; k < 4; k++) {
        const char *expr = exprs[k];
        Stack s3;
        bool balanced = true;
        for (int i = 0; expr[i] != '\0' && balanced; i++) {
            char ch = expr[i];
            if (ch == '(' || ch == '[' || ch == '{') {
                s3.push(ch); // acan parantezi yigina at
            } else if (ch == ')' || ch == ']' || ch == '}') {
                char open;
                if (!s3.getTop(open)) {  // kapatacak bir sey yok
                    balanced = false;
                } else if ((ch == ')' && open != '(') ||
                           (ch == ']' && open != '[') ||
                           (ch == '}' && open != '{')) {
                    balanced = false;   // tur uyusmuyor
                } else {
                    s3.pop();           // eslesti, ciftleri at
                }
            }
        }
        if (s3.isEmpty() == false) {
            balanced = false; // acik kalan parantez var
        }
        std::cout << expr << " -> " << (balanced ? "dengeli" : "dengesiz") << std::endl;
    }

    return 0;
}