# Ders materyalleri · CSE 211

Bu klasörde dersin bütün kaynakları konuya göre toplandı: slaytlar, labwork’ler, ödevler, pratik lablar ve ders içi kodlar. Her labwork ve ödevin yanında aynı soruları çözen, derlenen ve testten geçen bir **`solution/`** klasörü var. Önceki dönemlerden kalan çözümler **`archive-solution/`** klasöründe değiştirilmeden duruyor. Aşağıdaki tablolarda bu çözümlerdeki hatalar da listeleniyor, çünkü onları bulmak iyi bir alıştırma.

- [Klasör düzeni](#klasör-düzeni)
- [Testleri çalıştır](#testleri-çalıştır)
- [Labwork’ler](#labworkler)
- [Ödevler · 2017 bahar](#ödevler--2017-bahar)
- [Ödevler · 2021 güz ve dönem projesi](#ödevler--2021-güz-ve-dönem-projesi)
- [Pratik lablar ve ders kodu](#pratik-lablar-ve-ders-kodu)
- [Dersin özel fonksiyonları (slaytlardan)](#dersin-özel-fonksiyonları-slaytlardan)
- [Ek kaynaklar](#ek-kaynaklar)

## Klasör düzeni

```
materials/
├── slides/            CSE 211 slaytları (01–17) + konu/sayfa dizini (slides/README.md)
├── cse211-syllabus.pdf
├── labworks/          lw1 … lw8: görev PDF’i, archive-solution/, solution/
├── assignments/
│   ├── 2017-spring/   as1 … as5 (Grades, Big-O, stack ifadeleri, calendar, ağaç/graf/heap)
│   └── 2021-fall/     a1 … a5 + term-project-text-editor (given/, archive-solution/, solution/)
├── practice-labs/     pl2 linked list (6 soru), pl4 Campus Friends (graph)
├── lecture-code/      derste yazılan kodlar (week01 … week06)
├── exams/             vize-notlari.txt
├── cpp-reference/     ek okuma: SUSTech CS205 “C/C++ Program Design” ders notları ve lab örnekleri
└── _check/            check.h + run_all.py (bütün solution/ testleri)
```

`cpp-reference/` başka bir üniversitenin C/C++ dersidir. Bu klasör yalnızca okuma ve örnek kod kaynağı olarak duruyor. İçindeki alıştırmalar CSE 211’in parçası olmadığı için çözülmedi.

## Testleri çalıştır

Depo kökünden:

```powershell
python materials/_check/run_all.py          # 18 çözümün hepsi
python materials/_check/run_all.py lw6      # yolunda "lw6" geçenler
```

Her `solution/test.cpp`, görev PDF’indeki örnek çıktıları ve sınır durumlarını kontrol eder. Örnek olarak boş yapı, tek eleman, baş ve son düğüm ile tekrar eden değerler sınanır. `main*.cpp` dosyaları ödevin istediği gösterim programlarıdır. Bu dosyalar da derlenip uyarı vermediği kontrol edilir. Tek bir ödevi elle derlemek için ilgili `main.cpp` dosyasının ilk satırındaki komutu kullan.

## Labwork’ler

| Klasör | Sorular | Çözüm dosyaları | Arşiv çözümünde dikkat | Lab kampı |
| --- | --- | --- | --- | --- |
| [lw1-singly-linked-list](labworks/lw1-singly-linked-list/) | `IntSLList::remove_even()`, `duplicate_fives()` | `intSLList.cpp` | `duplicate_fives` her 5’te `tail`’i yeni düğüme çekiyor. `5 → 7` listesinde sonraki `addToTail` 7’yi kaybediyor. `remove_even` her silmede listeyi baştan tarıyor (`O(n²)`). | 4. hafta |
| [lw2-doubly-linked-list](labworks/lw2-doubly-linked-list/) | `append(const DoublyLinkedList&)`, `split()` + quiz | `genDLList.h` | `append` boş listeye eklerken `tail->next` ile çöküyor. `A.append(A)` sonsuz döngüye giriyor. `split` boş ve tek elemanlı listede çöküyor. | 5. hafta |
| [lw3-stack-palindrome](labworks/lw3-stack-palindrome/) | DLL üzerinde `push/top/pop`, yalnız bunlarla `is_palindrome` | `genDLList.h`, `palindrome.cpp` | Doğru çalışıyor. Döngüde `int` ile `size()` karşılaştırması uyarı veriyor. | 6. hafta |
| [lw5-priority-queue](labworks/lw5-priority-queue/) | `enqueue(el, priority)` (eşit öncelikte FIFO), `T& dequeue()`, menü | `priority_queue.h`, `session.cpp` | `dequeue` geçici değere referans döndürüyor (dangling reference, g++ uyarısı). Menü döngüsü `priority == 0` girişinde de bitiyor. | 7. hafta |
| [lw6-graph-degrees](labworks/lw6-graph-degrees/) | `indegree`, `outdegree`, `num_edges` + grafı kurup DFS/BFS/en kısa yol yazdıran main | `graph.cpp`, `lab6_graph.h`, `main.cpp` | İstenen üç fonksiyon hiç yazılmamış, dosya link aşamasında hata veriyor. Grafın kenarları PDF’teki şekilden okundu: 14 yönlü kenar. | 9. hafta |
| [lw7-bst-queries](labworks/lw7-bst-queries/) | `printsmallerthan`, `getnthelement`, `isbalanced` | `genBST.h` | Ders dosyası GCC’de derlenmiyor: bir `;` eksik ve `top()/front()` için `this->` gerekiyor (çözümde düzeltildi). `printsmallerthan` boşluksuz yazdırıyor. `getnthelement(n > size)` dizinin dışına okuyor. | 10. hafta |
| [lw8-min-heap](labworks/lw8-min-heap/) | `percolate_down`, `delete_min`, `heapify`, `print`, kurucu (kopya), `inorder` + main | `heap.cpp`, `main.cpp` | Kurucu diziyi kopyalamıyor, çağıranın dizisini yeniden sıralıyor. `min` aslında maksimumu buluyor. Boş heap’te `delete_min` `data[-1]`’e yazıyor. | 12. hafta |

**Labwork 2 quiz cevabı** (`remove_sequential_duplicates` kodundaki dört hata):
1. `new IntSLLNode` ile gereksiz bir düğüm oluşturuluyor ve hemen ardından `current = head` yazılıyor. O düğüm sızıyor (memory leak).
2. Boş listede `current->next` null pointer’a erişiyor. Döngüden önce `head == nullptr` kontrolü gerekiyor.
3. Silmeden sonra `current = current->next` ile bir adım ilerleniyor. Üç ve daha fazla ardışık tekrar olduğunda (`5 5 5`) ikinci kopya atlanıyor. Silme yapıldıysa ilerlememek gerekir. Son düğüm silindiğinde de `current` null olur ve `current->next` çöker.
4. Son düğüm silindiğinde `tail` güncellenmiyor. `tail` silinmiş düğümü göstermeye devam ediyor ve sonraki `addToTail` tanımsız davranışa yol açıyor.

## Ödevler · 2017 bahar

| Klasör | Sorular | Çözüm | Not | Lab kampı |
| --- | --- | --- | --- | --- |
| [as1-grades-linked-list](assignments/2017-spring/as1-grades-linked-list/) | `Grades` sınıfı (IntSLList ile not listesi), komut satırı menüsü | `Grades.cpp`, `menu.cpp` | Arşiv çözümü `IntSLList`’in `head`’ini `public` yapıyor ve değişken adı olarak `not` kullanıyor. `not` C++’ta anahtar kelime olduğu için kod derlenmiyor. Çözüm `friend class Grades` kullanıyor. | 4. hafta |
| [as2-algorithm-analysis](assignments/2017-spring/as2-algorithm-analysis/) | büyüme hızı sıralama, 4 kat yavaş makine, Big-O | [`ANSWERS.md`](assignments/2017-spring/as2-algorithm-analysis/solution/ANSWERS.md), `test.cpp` döngüleri sayıyor | Arşiv cevabında iki hata var. `n^(7/6)` yanlış sırada. 4c için `O(0)` yazılmış ama doğru cevap `O(N)`. | 9. hafta |
| [as3-stack-expressions](assignments/2017-spring/as3-stack-expressions/) | parantez kontrolü, infix→postfix, postfix hesaplama (her adımda stack) | `expr.cpp`, `main.cpp` adım adım çıktı verir | `10-4*2/2+5*9+1 = 52`, `6*((5-2)*(2+1))-9/3 = 51` | 6. hafta |
| [as4-calendar-classes](assignments/2017-spring/as4-calendar-classes/) | `date`, `bday`, `calendar` (artık yıl, `const` üye fonksiyonlar, `std::list`) | `date.cpp`, `bday.cpp`, `calendar.cpp`, üç örnek main | Doğum günü her yıl tekrarlanır. Yıl sonunu aşan 7 günlük pencere de test ediliyor. | 3. hafta |
| [as5-trees-graphs-heaps](assignments/2017-spring/as5-trees-graphs-heaps/) | traversal’lardan ağaç, BST ekle/sil, graf matrisi/BFS/DFS, heap kur/sil/ekle, preorder’dan heap, BST fonksiyonları | `as5.cpp`, `main.cpp` bütün cevapları yazdırır | Graf, docx’teki çizimden okundu (13 ok). Arşivdeki öğrenci cevabında build-heap dizisi yanlış. Doğrusu `4 10 7 12 11 19 14 25 41 28 18 67 37 52 22`. Sorudaki `21 19 24 …` preorder dizilimi geçerli bir heap değil. | 9, 10, 12. hafta |

## Ödevler · 2021 güz ve dönem projesi

| Klasör | Sorular | Çözüm | Arşiv çözümünde dikkat | Lab kampı |
| --- | --- | --- | --- | --- |
| [a1-sll-sort-swap](assignments/2021-fall/a1-sll-sort-swap/) | `find_min`, `sort_list` (orijinal değişmez), `swap_nodes(val)` | `intsllist.cpp` | `swap_nodes` düğümleri değil değerleri değiştiriyor. Görev bunu açıkça yasaklıyor. Sınıfta kopya kurucu ve kopya atama yok. `list2 = list.sort_list();` aynı düğümleri iki nesneye verip iki kez siliyor (rule of three). Çözüm bu ikisini ekliyor. | 4. hafta |
| [a2-code-stack-undo](assignments/2021-fall/a2-code-stack-undo/) | `pushToStack(const char*)`, `string popFromStack()`, `printStack`, `printReverseStack`, `/delete` ve `/undo` | `codeStack.cpp`, `editor.cpp` | Verilen main, `undoStk.~codeStack()` ile yıkıcıyı elle çağırıyor ve nesneyi sonra kullanmaya devam ediyor. Bu tanımsız davranış. Boş stack’te `popFromStack` değer döndürmeden bitiyor. | 6. hafta |
| [a3-directed-graph](assignments/2021-fall/a3-directed-graph/) | dosyadan adjacency list (IntSLList), `printAdjList`, `performBFS` (ödevin queue sınıfıyla), `isThereWay`, bonus `findRoutes` | `intDrGraph.h` | `while (!file.eof())` dosya sonunda boş satır varsa son kenarı iki kez okur. Çözüm okumayı döngü koşulunda yapıyor. | 9. hafta |
| [a4-tree-functions](assignments/2021-fall/a4-tree-functions/) | `insertBST`, `insertWrong`, `isThisaBST`, `findHeight`, `findOnlyChild`, `inOrder` | `tree.h` | Verilen iskelette `std::vector` için `std::` eksik olduğundan derlenmiyor. Yıkıcı da yok. Yalnızca ebeveyne bakan bir `isThisaBST` derindeki ihlalleri kaçırır, testte bunun örneği var. | 10. hafta |
| [a5-hashing](assignments/2021-fall/a5-hashing/) | int ve en çok 4 karakterli string için zincirli hash (10 bucket, IntSLList), insert ve search | `hashing.cpp` | Arşiv çözümü tür listesine bakmıyor. `656565` sayısı ile `"AAA"` stringi aynı kayıt sayılıyor. Negatif sayıda `input % 10` negatif bir indeks veriyor. | 11. hafta |
| [term-project-text-editor](assignments/2021-fall/term-project-text-editor/) | satırları linked list’te tutan, 10 satırlık sayfalarla gösteren, `open/save/insert/delete/move/replace/next/prev/undo` destekli editör | `editor.cpp`, `main.cpp` | Çözüm her komutu geri almak için bir `Action` kaydını stack’e koyuyor. `open` komutu undo stack’ini boşaltıyor. | 8. hafta (proje) |

## Pratik lablar ve ders kodu

| Klasör | İçerik | Durum |
| --- | --- | --- |
| [pl2-linked-list](practice-labs/pl2-linked-list/) | Practice Lab 2: tek konumlar, iteratif/recursive uzunluk, orta eleman, sıralı ekleme, ters çevirme, circular kontrol | `solution/q1.cpp … q6.cpp`. Hepsi uyarısız derleniyor. |
| [pl4-campus-friends](practice-labs/pl4-campus-friends/) | Campus Friends: BFS/DFS, en popüler, ortak arkadaş, grup sayısı, öneri | `practicelab4_solution/`: `tests.cpp` 5/5 soruyu geçiyor (`make test`). |
| [lecture-code](lecture-code/) | Derste yazılan örnekler. Week 5 `queue.cpp`, slaytlardaki `bool dequeue()` / `dequeue(out)` arayüzünü uyguluyor. | okuma |
| [exams/vize-notlari.txt](exams/vize-notlari.txt) | Vizede çıkan başlıklar | Lab kampında L03, L09, L10, L18, L19, L23, L27, L28 ve 8. haftanın provalarına dağıtıldı. |

## Dersin özel fonksiyonları (slaytlardan)

Slayt metinlerinden çıkarılan gerçek imzalar. Lab kampı bu adları kullanıyor, arşivde olmayan bir adı dersin API’si gibi göstermiyor.

| Yapı | Slayttaki imza | Kaynak |
| --- | --- | --- |
| List (ADT) | `bool insert(int index, ListItemType newItem)`, `bool remove(int index)`, `bool retrieve(int index, ListItemType& dataItem) const`, `int getLength() const`, `bool isEmpty() const`. İndeksler 1’den başlar. | [08-linked-lists](slides/08-linked-lists.ppt), slayt 17–28 |
| Stack | `bool push(StackItemType newItem)`, `bool pop()` (yalnızca siler), `bool pop(StackItemType& stackTop)` (değeri parametreye yazar), `bool getTop(StackItemType& stackTop) const`, `bool isEmpty() const` | [09-stacks](slides/09-stacks.ppt), slayt 3–8 ve 15–32 |
| Queue | `bool enqueue(QueueItemType newItem)`, `bool dequeue()`, `bool dequeue(QueueItemType& queueFront)`, `bool getFront(QueueItemType& queueFront) const`, `bool isEmpty() const` | [10-queues](slides/10-queues.ppt), slayt 2–29 |
| Labwork sınıfları | `IntSLList`: `addToHead`, `addToTail`, `int deleteFromHead()`, `int deleteFromTail()`, `int isEmpty()`. `DoublyLinkedList<T>`: `addToDLLHead/Tail`, `T deleteFromDLLHead/Tail()`, `T& firstEl()` | [lw1](labworks/lw1-singly-linked-list/), [lw2](labworks/lw2-doubly-linked-list/) |
| Ödev sınıfları | `codeStack::pushToStack(const char*)`, `string popFromStack()`. A3 `queue<T>`: `enqueue`, `T dequeue()`, `T firstElement()` | [a2](assignments/2021-fall/a2-code-stack-undo/), [a3](assignments/2021-fall/a3-directed-graph/) |
| Heap | `heapInsert`, `heapDelete`, `heapRebuild(int root)` (slayt), labwork’te `percolate_down`, `delete_min`, `heapify` | [16-heaps](slides/16-heaps.pptx), slayt 11–15 · [lw8](labworks/lw8-min-heap/) |
| Hash | `int hash(const string& key, int tableSize)`. Not: slayt 31’deki örnek `'a'` için 98 kullanıyor ve 8172 buluyor. `'a'` = 97, doğru sonuç `hash("ali", 10007) = 6803` (Lab 40). | [17-hash-tables](slides/17-hash-tables.pptx), slayt 29–31 |

## Ek kaynaklar

Konu sırasıyla, her biri ücretsiz:

| Konu | Okuma | Görsel ve alıştırma |
| --- | --- | --- |
| C++ temelleri, vector, string | [learncpp.com](https://www.learncpp.com/) bölüm 1–5, 12 (referanslar), 16 (`std::vector`) · [cppreference `std::vector`](https://en.cppreference.com/w/cpp/container/vector) · [cppreference `std::string`](https://en.cppreference.com/w/cpp/string/basic_string) | [cpp-reference/week01–07](cpp-reference/) örnek kodları · [Compiler Explorer](https://godbolt.org/) |
| Pointer, bellek, sınıflar | learncpp bölüm 12 (pointer), 14–15 (sınıflar), 19 (`new`/`delete`) · [C++ Core Guidelines: R (kaynak yönetimi)](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-resource) | [Python Tutor (C++ modu)](https://pythontutor.com/cpp.html): pointer ve düğümleri adım adım çizer |
| Linked list, stack, queue | Open Data Structures, bölüm 2–3: [opendatastructures.org](https://opendatastructures.org/) | [VisuAlgo: Linked List, Stack, Queue](https://visualgo.net/en/list) |
| Karmaşıklık | [Big-O cheat sheet](https://www.bigocheatsheet.com/) · slayt 11 | [2017 AS2 çözümü](assignments/2017-spring/as2-algorithm-analysis/solution/ANSWERS.md): döngü sayan testler |
| Graph | Open Data Structures, bölüm 12 | [VisuAlgo: Graph Traversal](https://visualgo.net/en/dfsbfs) |
| Tree, BST, AVL | Open Data Structures, bölüm 6–8 | [VisuAlgo: BST/AVL](https://visualgo.net/en/bst) · [USFCA AVL animasyonu](https://www.cs.usfca.edu/~galles/visualization/AVLtree.html) |
| Hash | Open Data Structures, bölüm 5 | [VisuAlgo: Hash Table](https://visualgo.net/en/hashtable) |
| Heap | Open Data Structures, bölüm 10 | [VisuAlgo: Binary Heap](https://visualgo.net/en/heap) |
