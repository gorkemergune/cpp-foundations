# CSE 211 Lab Kampı · C++ ve Veri Yapıları

Her çalışma gününde bir lab var. Her lab 30–50 dakikalık bir PDF, ayrı başlangıç dosyaları ve hazır testlerle geliyor. Kamp C++’a `std::vector` ile sıfırdan başlıyor. Dersin sınıflarını ve özel fonksiyonlarını (`pushToStack`, `popFromStack`, `dequeue(out)`, `addToTail` …) ihtiyaç duyulan haftada, arşivdeki gerçek imzalarıyla kullandırıyor.

Önceki [vize kampı](../camp/README.md) 30 soruluk tek bir setti. Bu kamp aynı test düzenini kullanıyor (`TODO();` sil, yaz, `run.ps1` ile sına), ama her günü ayrı bir üniversite labı olarak kuruyor.

- [Bir labı nasıl çalışırım?](#bir-labı-nasıl-çalışırım)
- [Haftalık dizin](#haftalık-dizin)
- [Vize başlıklarının dağılımı](#vize-başlıklarının-dağılımı)
- [Özel fonksiyonlar haritası](#özel-fonksiyonlar-haritası)
- [Klasör düzeni](#klasör-düzeni)

## Bir labı nasıl çalışırım?

1. Labın PDF’ini aç. İlk sayfalar İngilizce lab sorusu: problem, verilen kod, doldurulacak imza, izinli fonksiyonlar, kısıtlar, adım adım örnek ve test tablosu.
2. Isınma programının çıktısını önce kâğıda yaz, sonra derle (`g++ -std=c++17 -Wall warmup.cpp -o warmup.exe`).
3. `labXX.cpp` içinde her fonksiyonun `TODO();` satırını silip gövdeyi yaz. `labXX.h` dosyasına dokunma.
4. Testleri çalıştır. PDF’teki tablonun her satırı bir test. Arkasından 200 rastgele girdi çalışıyor.
5. Testler yeşil olunca ya da süre bitince Türkçe bölüme geç: anlatım, “kendine sor” soruları, görsel iz, referans çözüm, alternatifler ve en sonda ezberden yazılacak kısa varyant.

```powershell
cd lab-camp
.\run.ps1                 # labların listesi
.\run.ps1 L01             # Lab 01'in bütün soruları
.\run.ps1 L01 L01-M       # tek soru
.\run.ps1 L01 -Solution   # aynı testler referans çözümle (takıldığında karşılaştırmak için)
```

Git Bash’te: `./run.sh L01`, `./run.sh L01 L01-M`, `./run.sh L01 --solution`

| İşaret | Anlamı |
| --- | --- |
| `✓ 206/206` | bütün kontroller geçti |
| `✗ 3/8` | bazı satırlar yanlış. Girdi, beklenen ve senin sonucun yazılıyor |
| `· not written yet` | `TODO();` hâlâ duruyor |
| `· needs L03-A first` | yazdığın fonksiyon, henüz yazılmamış başka bir fonksiyonu çağırıyor |
| `💥` | çökme: vektör dışı indeks, null pointer ya da silinmiş düğüm |
| `⏱` | 3 saniyede bitmedi, büyük olasılıkla sonsuz döngü |

Soru kimlikleri her labda aynı düzende: **A, B** kısa hazırlık alıştırmaları, **M** (veya M1, M2) ana problem, **X** isteğe bağlı LeetCode/GeeksforGeeks uyarlaması, **V** ezberden yazılacak varyant. Süreli lablarda parçalar **A, B, C** olarak adlandırılıyor. Özet satırı yalnızca zorunlu soruları sayar.

## Haftalık dizin

Haftada 3–4 lab var. Her lab tek bir çalışma gününe sığacak şekilde hazırlandı. Bir haftanın son labı genellikle süreli. Onu sınav koşullarında çöz. Bir sonraki konuya, önceki haftanın kontrol listesini tamamlayınca geç.

### 1. hafta · `std::vector` · hazır

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L01 | 1 | First Steps with `std::vector`: Running Totals | 35 dk | vektör tanımlama, ilk dosyayı derleme, `push_back`, `size`, `[]`, range-for, değerle geçirme · LC 1480, LC 1929 | [PDF](week01/L01-vector-first-steps/L01-vector-first-steps.pdf) · [klasör](week01/L01-vector-first-steps/) |
| L02 | 2 | References: Removing and Inserting Inside a Vector | 45 dk | `&`, `const&`, `int&` ile range-for, `reserve`/`resize`, `at`/`[]`, elle kaydırma · LC 27 | [PDF](week01/L02-references-and-in-place-edits/L02-references-and-in-place-edits.pdf) · [klasör](week01/L02-references-and-in-place-edits/) |
| L03 | 3 | Two Indexes: Reversing Alternate Groups of Three | 45 dk | `swap`, iki indeks, `size_t` tuzağı · **vize:** üçlü döndürme, iki dizi birbirinin tersi mi · GfG Reverse in groups | [PDF](week01/L03-two-index-reversal/L03-two-index-reversal.pdf) · [klasör](week01/L03-two-index-reversal/) |
| L04 | 4 | Timed Lab: Compacting and Rotating a Vector | 50 dk, süreli | `moveZeroes`, `%` ile başa sarma, üç ters çevirmeyle döndürme · LC 283, LC 189 | [PDF](week01/L04-timed-lab-rotate/L04-timed-lab-rotate.pdf) · [klasör](week01/L04-timed-lab-rotate/) |

### 2. hafta · C tipi dizi ve `std::array`

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L05 | 1 | C-Style Arrays: Passing an Array and Its Length | 40 dk | `int a[N]`, `sizeof`, dizinin pointer’a dönüşmesi, uzunluğu ayrı iletme, `int&` çıkış parametresi (`minMaxIndex`) | hazırlanacak |
| L06 | 2 | `std::array` and Your First Function Template | 45 dk | `std::array<T, N>`, `.size()`, `.at()`, `template <typename T>`, `template <size_t N>` · LC 1550 | hazırlanacak |
| L07 | 3 | Pointers Into Arrays and 2-D Arrays | 45 dk | **önce kâğıtta pointer izi:** `int* p = a; *(p + 2); p++`, sonra `int m[R][C]` satır/sütun toplamları · LC 1572 | hazırlanacak |
| L08 | 4 | Timed Lab: Merging Sorted Arrays | 50 dk, süreli | iki sıralı C dizisini üçüncü diziye birleştirme, LC 88 imzası | hazırlanacak |

### 3. hafta · `std::string`, `getline`, parametreler, `.h/.cpp`

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L09 | 1 | Strings: Indexing, `substr`, `find` | 40 dk | `std::string` ve `char[]` farkı, `+=`, `substr`, `find`/`npos`, `unsigned char` ile `isalnum` · **vize:** iki string birbirinin tersi mi (string sürümü) · LC 344, LC 125 | hazırlanacak |
| L10 | 2 | Reading Lines: `getline` and `istringstream` | 45 dk | `cin >>` sonrası `getline`, boşluklu satırlar · **vize:** stringden minimum sayı, geçici değişkenle karşılaştırma (`bool minToken(const string&, int&)`) · LC 2042 | hazırlanacak |
| L11 | 3 | Header and Source: Your First Class | 45 dk | `.h` / `.cpp` ayrımı, include guard, constructor ve initializer list, `const` üye fonksiyon, çok dosyalı derleme · LC 58 | hazırlanacak |
| L12 | 4 | Timed Lab: Word Processing | 50 dk, süreli | kelimeleri ters çevirme (LC 151), `minToken` varyantı, sınır satırları | hazırlanacak |

### 4. hafta · Pointer ve Linked List I

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L13 | 1 | Paper Lab: Tracing Nodes and Arrows | 35 dk | **kod yazmadan önce:** `struct Node`, `new`/`delete`, `Node*` kutu-ok çizimi, her satırdan sonra bağlantıları kâğıtta güncelleme, ardından küçük doğrulama programı | hazırlanacak |
| L14 | 2 | `pushBack(Node*& head, int value)` | 45 dk | arşivdeki gerçek imza (Linked-Ex), `Node*` ile `Node*&` farkı, yazdırma, uzunluk, listeyi serbest bırakma · alıştırma imzası `pushToBack` · GfG Linked List Insertion at End | hazırlanacak |
| L15 | 3 | The Course Class `IntSLList` | 50 dk | Labwork 1 başlığı: `addToHead`, `addToTail`, `deleteFromHead`, `deleteFromTail` (`int` döndürür, boşken tanımsız), `int isEmpty()`, destructor | hazırlanacak |
| L16 | 4 | Timed Lab: Reverse and Remove | 50 dk, süreli | yerinde ters çevirme (LC 206), ilk eşleşeni silme, `head`/`tail` güncellemesi | hazırlanacak |

### 5. hafta · Linked List II

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L17 | 1 | Doubly Linked List Template | 50 dk | `genDLList.h`: `addToDLLHead`, `addToDLLTail`, `deleteFromDLLHead`, `deleteFromDLLTail` (`T` döndürür), sınıf şablonu sözdizimi, ileri-geri dolaşım | hazırlanacak |
| L18 | 2 | Delete the Middle Node | 40 dk | **vize:** ortadaki düğümü silme, iki pointer, `delete` ve `head` güncellemesi · LC 2095 | hazırlanacak |
| L19 | 3 | Circular List With `last` | 45 dk | **vize:** `last` ile tutulan çember, `deleteLast(Node*& last)`, tek ve iki düğüm durumları | hazırlanacak |
| L20 | 4 | Timed Lab: Merging and Cleaning Lists | 50 dk, süreli | LC 21 Merge Two Sorted Lists, LC 83 Remove Duplicates from Sorted List | hazırlanacak |

### 6. hafta · Stack

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L21 | 1 | `std::stack` and the Lecture Stack | 40 dk | `push`, `top`, `pop` (yalnızca siler), `empty`; dersteki `bool pop()` + `getTop(char&)` · **vize:** `empty()` ile `!empty()` · LC 20 | hazırlanacak |
| L22 | 2 | Your Own `LLStack<T>` | 50 dk | template sınıf, constructor/destructor, `pushToStack`, değer döndüren `popFromStack()`, `isEmpty`, `peek` · alıştırma imzası `pushFromStack(src, dst)` | hazırlanacak |
| L23 | 3 | Two Stacks | 45 dk | **vize:** iki stack’te push/pop ile taşıma, iki string birbirinin tersi mi (iki stack ile) · LC 232 | hazırlanacak |
| L24 | 4 | Timed Lab: Postfix and Min Stack | 50 dk, süreli | LC 150 (operand sırası), LC 155 | hazırlanacak |

### 7. hafta · Queue

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L25 | 1 | `std::queue` and the Lecture Queue | 45 dk | `push`/`front`/`pop`/`back`; dersteki `enqueue`, `dequeue()` (yalnızca siler), `dequeue(out)`, `getFront(out)` · LC 933 | hazırlanacak |
| L26 | 2 | `LLQueue<T>` and a Circular Array Queue | 50 dk | değer döndüren `dequeue()`, `getFront`, `getRear`, son eleman çıkınca `rear`, A3’teki `firstElement()` · LC 622 | hazırlanacak |
| L27 | 3 | Alternate Triples With a Queue and a Stack | 45 dk | **vize:** üçlü grupları queue + tek stack ile çevirme · GfG Reverse First K of a Queue | hazırlanacak |
| L28 | 4 | Delete the Middle, Build a Queue | 45 dk | **vize:** ortadaki düğümü silip kalanları yeni queue’ya aktarma, `dequeue`/`empty` ile yazdırma | hazırlanacak |

### 8. hafta · Vize provası

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L29 | 1 | Midterm Mock A | 50 dk, süreli | linked list + stack: iki stack ile push/pop, `empty`/`!empty`, ortadaki düğüm | hazırlanacak |
| L30 | 2 | Midterm Mock B | 50 dk, süreli | queue + string: üçlü gruplar, stringden minimum, iki string ters mi | hazırlanacak |
| L31 | 3 | Midterm Mock C | 50 dk, süreli | yeni varyantlar: circular `last` silme, farklı grup boyu, farklı API ile aynı soru | hazırlanacak |

### 9. hafta · Graph

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L32 | 1 | Adjacency Matrix and Adjacency List | 40 dk | kenar listesinden iki temsil, yönlü/yönsüz, derece, komşu sırası | hazırlanacak |
| L33 | 2 | BFS With a Queue | 45 dk | `visited`, mesafe, erişilemeyen düğüm `-1` · GfG BFS of Graph | hazırlanacak |
| L34 | 3 | DFS: Recursion and Stack | 45 dk | iki DFS’in sırası, bağlı bileşen sayısı · LC 200 | hazırlanacak |
| L35 | 4 | Timed Lab: Campus Friends | 50 dk, süreli | `Graph-Ex` sınıfı: `bfs`, `dfs`, `countGroups`, `mutualFriends`, geçersiz ID | hazırlanacak |

### 10. hafta · Tree

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L36 | 1 | Binary Tree Recursion | 40 dk | `size`, `height`, `countLeaves`, recursive dönüş değeri · LC 104 | hazırlanacak |
| L37 | 2 | Traversals and Level Order | 45 dk | preorder, inorder, postorder, queue ile seviye sırası · LC 102 | hazırlanacak |
| L38 | 3 | BST Insert and Search | 45 dk | Labwork 7 `genBST.h` adları, min/max · LC 700, LC 701 | hazırlanacak |
| L39 | 4 | Timed Lab: BST Delete | 50 dk, süreli | `findAndDeleteByCopying`, kökü silme, GfG Check for BST | hazırlanacak |

### 11. hafta · Hash

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L40 | 1 | `unordered_map`: `find` vs. `[]` | 40 dk | kelime sıklığı, eksik anahtar, `count` · LC 1 | hazırlanacak |
| L41 | 2 | Chaining Hash Table | 45 dk | bucket dizisi, `put`/`get`/`erase`, negatif anahtar, load factor | hazırlanacak |
| L42 | 3 | Timed Lab: Linear Probing | 50 dk, süreli | probe dizisi, tombstone, başa sarma, dolu tablo | hazırlanacak |

### 12. hafta · Heap ve final provası

| No | Gün | Başlık | Süre | Konu | PDF |
| --- | --- | --- | --- | --- | --- |
| L43 | 1 | Heap as an Array | 45 dk | ağaç-dizi eşlemesi, `siftUp`, `siftDown`, `buildHeap` elle ve kodla | hazırlanacak |
| L44 | 2 | `MinHeap` Class | 50 dk | `push`/`top`/`pop`/`empty`; Labwork 8 `heap(int*, int)` ve `delete_min()` | hazırlanacak |
| L45 | 3 | `priority_queue` and Comparators | 45 dk | LC 215, öncelik + geliş sırası ile görev kuyruğu | hazırlanacak |
| L46 | 4 | Final Mock | 50 dk, süreli | graph BFS mesafesi, BST kök silme, probing `erase`, heap `pop` | hazırlanacak |

## Vize başlıklarının dağılımı

[Vize notundaki](../arc/vize.txt) her başlık önce tek başına öğretiliyor, sonra asıl veri yapısıyla soruluyor, 8. haftada da süreli olarak tekrar geliyor. Notta yazmayan kurallar (grup sayma, eksik grup, çift uzunlukta “orta”, boşken davranış) ilgili PDF’te **alıştırma varsayımı** olarak açıkça yazılıyor.

| Vize başlığı | Hazırlık | Asıl lab | Süreli tekrar |
| --- | --- | --- | --- |
| İki stack’te push ve pop | L22 (kendi `pushToStack`/`popFromStack`) | L23 | L29 |
| `st.empty()` ve `!st.empty()` farkı | L21 | L23 | L29 |
| İki string birbirinin tersi mi (iki stack) | L03-B (vektör), L09 (string) | L23 | L30 |
| Sayıları üçerli döndürme `1…9 → 3 2 1 4 5 6 9 8 7` | L03-M (vektör, yerinde) | L27 (queue + stack) | L30 |
| String’deki minimum sayı, geçici değişkenle | L10 | L12 | L30 |
| Ortadaki elemanı düğümden silip yeni queue’da yazdırma | L18 (silme) | L28 | L31 |
| Circular listede `last` düğümünü silip yeniden bağlama | L13 (kâğıt izi) | L19 | L31 |

## Özel fonksiyonlar haritası

Aynı işlem farklı sınıflarda farklı adla ve farklı dönüş tipiyle geliyor. Tablo, adın nereden geldiğini ve kampta hangi labda kullanıldığını gösteriyor. “Alıştırma imzası” yazan adlar arşivde yok. Bu adlar ilgili labda imzası açıkça verilmiş bir alıştırma sınıfıyla öğretiliyor, dersin gerçek API’si sayılmıyor.

| İşlem | Standart C++ | Arşivdeki gerçek ad ve sözleşme | Lab |
| --- | --- | --- | --- |
| Sona ekle | `v.push_back(x)` | `pushBack(Node*& head, int value)` ([Linked-Ex](../Linked-Ex/q3.cpp)) · `addToTail(int)` ([IntSLList](../doc/cse211/Labwork%201/intSLList.h)) · `addToDLLTail(const T&)` ([genDLList](../doc/cse211/Labwork%202/genDLList.h)) · `pushToBack`: alıştırma imzası | L01, L14, L15, L17 |
| Başa ekle | `d.push_front(x)` (`deque`, `list`) | `addToHead(int)`, `addToDLLHead(const T&)` | L15, L17, L25 |
| Baştan/sondan sil | `pop_front()`, `pop_back()` → `void` | `deleteFromHead()`, `deleteFromTail()` → `int`, boş listede tanımsız (önce `isEmpty()`); `deleteFromDLLHead/Tail()` → `T` | L02, L15, L17 |
| Stack’e ekle | `st.push(x)` | `pushToStack(const char*)` ([A2 codeStack](../projects/2021-2022%20Fall/CSE%20211%20-%20Data%20Structures/Assignments/A2/Original_Codes/codeStack.h)) · `pushToStack(const T&)` ([kamp LLStack](../camp/ds/LLStack.h)) · dersteki `bool push(char)` ([lecture/week04](../lecture/week04/func.cpp)) | L21, L22 |
| Stack’ten çıkar | `st.top()` ile oku, `st.pop()` ile sil (`void`) | `popFromStack()` değeri döndürür (A2’de `string`, kampta `T`, boşken `runtime_error`) · dersteki `bool pop()` yalnızca siler, değer `bool getTop(char&)` ile alınır | L21, L22, L23 |
| Taşı | — | `pushFromStack(src, dst)`: alıştırma imzası | L22, L23 |
| Silmeden oku | `st.top()`, `q.front()`, `q.back()` | kampta `peek()`, `getFront()`, `getRear()` alıştırma fonksiyonları · A3’te `firstElement()` · dersteki `bool getFront(QueueItemType&) const` | L22, L25, L26 |
| Queue’ya ekle | `q.push(x)` | `enqueue(x)`: derste `bool`, kampta ve A3’te `void` | L25, L26 |
| Queue’dan çıkar | `q.front()` ile oku, `q.pop()` ile sil (`void`) | dersteki `bool dequeue()` yalnızca siler, `bool dequeue(out)` değeri parametreye yazar · kamp ve A3 `dequeue()` değeri döndürür | L25, L26, L27 |
| Boş mu? | `empty()` | `isEmpty()`: IntSLList’te `int`, diğerlerinde `bool` | L21, L25 |

## Klasör düzeni

```
lab-camp/
├── README.md               bu dizin
├── run.ps1, run.sh         derle + test et
├── week01/
│   └── L01-vector-first-steps/
│       ├── L01-vector-first-steps.pdf   ← lab sorusu, Türkçe anlatım, çözüm
│       ├── lab01.h                      verilen başlık (dokunma)
│       ├── lab01.cpp                    ← SEN BURADA ÇALIŞIYORSUN
│       ├── warmup.cpp                   ısınma programı
│       └── tests/                       testler + PDF tablolarından üretilen pdf_cases.inc
├── solutions/L01/          referans çözüm ve PDF’teki alternatifler (çözümden sonra bak)
├── framework/              küçük test çatısı (camp/framework/test.h’den uyarlandı)
└── _tools/                 PDF üretimi: labs/LXX.html şablonları, build.py, style.css
```

PDF’leri yeniden üretmek ya da yeni bir lab eklemek için `python _tools/build.py` (Microsoft Edge ve `pygments` gerekir) ve `python _tools/build.py verify` kullan. `verify`, başlangıç dosyalarının derlendiğini, referans çözümlerin bütün testleri geçtiğini, alternatif çözümlerin `assert` kontrollerini geçtiğini ve ısınma programlarının uyarısız derlendiğini kontrol eder. PDF’teki kod blokları derlenen dosyalardan, test tabloları da testlerin okuduğu `pdf_cases.inc` dosyasından geliyor. Bu yüzden PDF ile testler birbirinden ayrışamıyor.
