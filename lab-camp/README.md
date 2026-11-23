# CSE 211 Lab Kampı · C++ ve Veri Yapıları

12 haftalık, PDF tabanlı bir çalışma kampı: **46 lab**, **11 düşündüren soru seti** (LeetCode medium/hard) ve **6 küçük proje** (60–100 satır). Her lab 30–50 dakikalık bir üniversite labı gibi kurulu: İngilizce lab sorusu, verilen başlık dosyası, doldurulacak imza, test tablosu; ardından Türkçe anlatım, “kendine sor” soruları, adım adım çizimler, referans çözüm, “neden bu yol?”, alternatif ve en sonda ezberden yazılacak kısa bir varyant.

Kamp `std::vector` ile sıfırdan başlıyor ve dersin sırasını izliyor: vector → dizi → string → linked list → stack → queue → (vize provası) → graph → tree → hash → heap. Dersin kendi sınıflarını ve özel fonksiyonlarını (`pushToStack`, `popFromStack`, `dequeue(out)`, `addToTail`, `heapRebuild` …) ihtiyaç duyulan haftada, slaytlardaki ve arşivdeki gerçek imzalarıyla kullandırıyor. Labwork’lerin, ödevlerin ve vize notlarının bütün soruları bir labın parçası olarak geçiyor.

- [Bir labı nasıl çalışırım?](#bir-labı-nasıl-çalışırım)
- [Haftalık dizin](#haftalık-dizin)
- [Vize başlıklarının dağılımı](#vize-başlıklarının-dağılımı)
- [Labwork ve ödevler nerede?](#labwork-ve-ödevler-nerede)
- [Özel fonksiyonlar haritası](#özel-fonksiyonlar-haritası)
- [Tekrar planı](#tekrar-planı)
- [Klasör düzeni ve PDF üretimi](#klasör-düzeni-ve-pdf-üretimi)

## Bir labı nasıl çalışırım?

1. Labın PDF’ini aç. İlk sayfalar İngilizce lab sorusu: problem, verilen kod, doldurulacak imza, kısıtlar, adım adım örnek ve test tablosu.
2. İlk haftalarda bir ısınma programı var. Çıktısını önce kâğıda yaz, sonra derle (`g++ -std=c++17 -Wall warmup.cpp -o warmup.exe`).
3. `labXX.cpp` içinde her fonksiyonun `TODO();` satırını silip gövdeyi yaz. `labXX.h` dosyasına dokunma.
4. Testleri çalıştır. PDF’teki tablonun her satırı bir test, arkasından çoğu soruda 200 rastgele girdi çalışıyor.
5. Testler yeşil olunca ya da süre bitince Türkçe bölüme geç. Referans çözüm bir sonraki sayfada başlıyor.

```powershell
cd lab-camp
.\run.ps1                 # labların listesi
.\run.ps1 L01             # Lab 01'in bütün soruları
.\run.ps1 L01 L01-M       # tek soru
.\run.ps1 L01 -Solution   # aynı testler referans çözümle (takıldığında karşılaştırmak için)
.\run.ps1 C09             # challenge seti, .\run.ps1 P04 proje
```

Git Bash’te: `./run.sh L01`, `./run.sh L01 L01-M`, `./run.sh L01 --solution`

| İşaret | Anlamı |
| --- | --- |
| `✓ 206/206` | bütün kontroller geçti |
| `✗ 3/8` | bazı satırlar yanlış. Girdi, beklenen ve senin sonucun yazılıyor |
| `· not written yet` | `TODO();` hâlâ duruyor |
| `· needs L03-A first` | yazdığın fonksiyon, henüz yazılmamış başka bir fonksiyonu çağırıyor |
| `💥` | çökme: dizi dışı indeks, null pointer ya da silinmiş düğüm |
| `⏱` | 3 saniyede bitmedi, büyük olasılıkla sonsuz döngü |

Soru kimlikleri her labda aynı düzende: **A, B** kısa hazırlık alıştırmaları, **M** (veya M1, M2 …) ana problem, **X** isteğe bağlı LeetCode/GeeksforGeeks uyarlaması, **V** ezberden yazılacak varyant. Süreli lablarda ve vize provalarında parçalar **A, B, C** olarak adlandırılıyor. Özet satırı yalnızca zorunlu soruları sayar.

- **L** = günlük lab (haftada 3–4; 4. gün genellikle süreli, sınav koşullarında çöz).
- **C** = haftanın düşündüren soru seti: o haftanın labları bittikten sonra, her soruya en az 25 dakika ver; ipuçları PDF’in ortasında, çözümler sonunda.
- **P** = küçük proje: 60–100 satırlık kendi kodun, hazır bir `main_demo.cpp` ile gerçekten çalışan bir program (derleme komutu dosyanın ilk satırında).

## Haftalık dizin

Bir sonraki konuya, önceki haftanın PDF’inin sonundaki kontrol listesini tamamlayınca geç. “Ders materyali” satırları `../materials` klasörüne gider; her PDF ayrıca ilgili slayt numaralarını yazar.

### 1. hafta · `std::vector`
Ders materyali: [06-arrays-and-vectors](../materials/slides/06-arrays-and-vectors.ppt), [05-functions](../materials/slides/05-functions.ppt) (referans parametreleri), C++ temelleri için [cpp-reference](../materials/cpp-reference/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L01 | 1 | First Steps with `std::vector`: Running Totals | 35 dk | `std::vector<int>`, `push_back`, `size`, `[]`, range-for, compiling a C++ file, passing a vector by value | [LC 1480](https://leetcode.com/problems/running-sum-of-1d-array/) · [LC 1929](https://leetcode.com/problems/concatenation-of-array/) | [PDF](week01/L01-vector-first-steps/L01-vector-first-steps.pdf) · [klasör](week01/L01-vector-first-steps/) |
| L02 | 2 | References: Removing and Inserting Inside a Vector | 45 dk | pass by value vs. `&` vs. `const&`, `int&` in range-for, `size` vs. `capacity`, `reserve`/`resize`, `at()` vs. `[]`, shifting elements by index | [LC 27](https://leetcode.com/problems/remove-element/) | [PDF](week01/L02-references-and-in-place-edits/L02-references-and-in-place-edits.pdf) · [klasör](week01/L02-references-and-in-place-edits/) |
| L03 | 3 | Two Indexes: Reversing Alternate Groups of Three | 45 dk | two indexes moving toward each other, `std::swap`, inclusive ranges, loop bounds for groups, the `size_t` underflow trap | [LC 344](https://leetcode.com/problems/reverse-string/) | [PDF](week01/L03-two-index-reversal/L03-two-index-reversal.pdf) · [klasör](week01/L03-two-index-reversal/) |
| L04 | 4 | Timed Lab: Compacting and Rotating a Vector | 50 dk, süreli | everything from Labs 01–03: `const&` vs. `&`, building a new vector, in-place index work, `%` for wrapping indexes, two-index reversal | [LC 283](https://leetcode.com/problems/move-zeroes/) · [LC 189](https://leetcode.com/problems/rotate-array/) | [PDF](week01/L04-timed-lab-rotate/L04-timed-lab-rotate.pdf) · [klasör](week01/L04-timed-lab-rotate/) |
| C01 | C | Thinking Problems on Vectors | 60–90 dk | prefix/suffix products, two pointers with a proof, in-place index placement (cyclic sort) | [LC 238](https://leetcode.com/problems/product-of-array-except-self/) · [LC 11](https://leetcode.com/problems/container-with-most-water/) · [LC 41](https://leetcode.com/problems/first-missing-positive/) | [PDF](week01/C01-challenge-vector/C01-challenge-vector.pdf) · [klasör](week01/C01-challenge-vector/) |

### 2. hafta · C tipi dizi, `std::array`, pointer
Ders materyali: [06-arrays-and-vectors](../materials/slides/06-arrays-and-vectors.ppt), [07-pointers](../materials/slides/07-pointers.ppt).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L05 | 1 | C-Style Arrays: Passing an Array and Its Length | 40 dk | `int a[N]`, initialization, `sizeof`, array-to-pointer decay, passing `(const int a[], int n)`, `int&` output parameters, returning `bool` for “no answer” | [GfG Min and Max in Array](https://www.geeksforgeeks.org/problems/find-minimum-and-maximum-element-in-an-array4428/1) (L05-X) · [GfG Second Largest](https://www.geeksforgeeks.org/problems/second-largest3735/1) (L05-V) | [PDF](week02/L05-c-style-arrays/L05-c-style-arrays.pdf) · [klasör](week02/L05-c-style-arrays/) |
| L06 | 2 | std::array and Your First Function Template | 45 dk | `std::array<T, N>`, `.size()`, `.at()`, copying arrays, `struct` return values, function templates `template <typename T>` and `template <std::size_t N>`, why templates live in headers | [LC 1550](https://leetcode.com/problems/three-consecutive-odds/) (L06-X) | [PDF](week02/L06-std-array-and-templates/L06-std-array-and-templates.pdf) · [klasör](week02/L06-std-array-and-templates/) |
| L07 | 3 | Pointers Into Arrays and 2-D Arrays | 45 dk | pointer arithmetic (`p + k`, `p - q`, `*p`, `p++`), half-open ranges `[begin, end)`, `nullptr`, 2-D arrays `int m[R][C]` and how they are passed | [LC 1572](https://leetcode.com/problems/matrix-diagonal-sum/) (M1) · [LC 867](https://leetcode.com/problems/transpose-matrix/) (L07-X) | [PDF](week02/L07-pointers-into-arrays/L07-pointers-into-arrays.pdf) · [klasör](week02/L07-pointers-into-arrays/) |
| L08 | 4 | Timed Lab: Merging Sorted Arrays | 50 dk, süreli | two-index merge, filling from the back, intersection of sorted ranges, C arrays and `std::vector` in one lab | [LC 88](https://leetcode.com/problems/merge-sorted-array/) (Part B, same signature) · [LC 977](https://leetcode.com/problems/squares-of-a-sorted-array/) (L08-X) | [PDF](week02/L08-timed-lab-merge/L08-timed-lab-merge.pdf) · [klasör](week02/L08-timed-lab-merge/) |
| C02 | C | Thinking Problems on Matrices | 60–90 dk | boundary-shrinking loops, rotation as transpose + reverse, using the input itself as marker storage | [LC 54](https://leetcode.com/problems/spiral-matrix/) · [LC 48](https://leetcode.com/problems/rotate-image/) · [LC 73](https://leetcode.com/problems/set-matrix-zeroes/) | [PDF](week02/C02-challenge-matrix/C02-challenge-matrix.pdf) · [klasör](week02/C02-challenge-matrix/) |

### 3. hafta · `std::string`, `getline`, sınıflar ve `.h/.cpp`
Ders materyali: [01-intro-to-cpp](../materials/slides/01-intro-to-cpp.ppt), [02-classes-and-objects](../materials/slides/02-classes-and-objects.ppt), [2017 AS4 takvim sınıfları](../materials/assignments/2017-spring/as4-calendar-classes/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L09 | 1 | Strings: Indexing, find and substr | 40 dk | `std::string` vs. `char[]`, `+=`, `s[i]`, `find`/`npos`, `substr`, comparing strings, `<cctype>` with `unsigned char` | [LC 125](https://leetcode.com/problems/valid-palindrome/) (M2) · [LC 344](https://leetcode.com/problems/reverse-string/) (L09-X) | [PDF](week03/L09-strings/L09-strings.pdf) · [klasör](week03/L09-strings/) |
| L10 | 2 | Reading Lines: getline and istringstream | 45 dk | `cin >> x` vs. `getline`, the leftover newline, `in.ignore`, `std::istringstream` to split a line, testing `if (in >> x)`, `std::istream&` parameters | [LC 2042](https://leetcode.com/problems/check-if-numbers-are-ascending-in-a-sentence/) (L10-X) | [PDF](week03/L10-reading-lines/L10-reading-lines.pdf) · [klasör](week03/L10-reading-lines/) |
| L11 | 3 | Header and Source: Your First Class | 45 dk | `class`, `public`/`private`, constructor with initializer list, `const` member functions, `ClassName::member` definitions in a `.cpp`, include guards, compiling several files, objects passed by reference | [LC 58](https://leetcode.com/problems/length-of-last-word/) (L11-X) | [PDF](week03/L11-header-and-source-class/L11-header-and-source-class.pdf) · [klasör](week03/L11-header-and-source-class/) |
| L12 | 4 | Timed Lab: Word Processing | 50 dk, süreli | everything from Labs 09–11: `istringstream`, building strings with `+=`, runs of equal characters, reference outputs | [LC 151](https://leetcode.com/problems/reverse-words-in-a-string/) (Part A) · [LC 14](https://leetcode.com/problems/longest-common-prefix/) (L12-X) | [PDF](week03/L12-timed-lab-words/L12-timed-lab-words.pdf) · [klasör](week03/L12-timed-lab-words/) |
| C03 | C | Thinking Problems on Strings | 60–90 dk | sliding window with a “last seen” table, expanding around a centre, careful parsing with overflow checks | [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [LC 5](https://leetcode.com/problems/longest-palindromic-substring/) · [LC 8](https://leetcode.com/problems/string-to-integer-atoi/) | [PDF](week03/C03-challenge-strings/C03-challenge-strings.pdf) · [klasör](week03/C03-challenge-strings/) |
| P01 | P | Gradebook: Read, Validate, Report | 90–120 dk | a class over a `std::vector` of structs, input validation with `istringstream`, `getline` loops over a stream, `const` member functions, formatted output with `<iomanip>`, building a small command-line program from tested parts | — | [PDF](week03/P01-gradebook-project/P01-gradebook-project.pdf) · [klasör](week03/P01-gradebook-project/) |

### 4. hafta · Pointer ve singly linked list
Ders materyali: [08-linked-lists](../materials/slides/08-linked-lists.ppt), [Labwork 1](../materials/labworks/lw1-singly-linked-list/), [Practice Lab 2](../materials/practice-labs/pl2-linked-list/), [2021 A1](../materials/assignments/2021-fall/a1-sll-sort-swap/), [2017 AS1](../materials/assignments/2017-spring/as1-grades-linked-list/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L13 | 1 | Paper Lab: Tracing Nodes and Arrows | 40 dk | `struct Node` with a constructor, `new` / `delete`, `nullptr`, `->`, walking a list, reading `next` before `delete`, `Node*&` to change the caller's head | [LC 1290](https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/) (L13-X) | [PDF](week04/L13-paper-lab-nodes/L13-paper-lab-nodes.pdf) · [klasör](week04/L13-paper-lab-nodes/) |
| L14 | 2 | pushBack(Node*& head, int value): Positions in a List | 45 dk | `Node*` vs. `Node*&` parameters, the empty-list case, walking to the node before a position, unlink then `delete`, returning a new head vs. changing it by reference | [GfG Linked List End Insertion](https://www.geeksforgeeks.org/problems/linked-list-insertion-1587115620/1) (L14-X) | [PDF](week04/L14-pushback-and-node-ref/L14-pushback-and-node-ref.pdf) · [klasör](week04/L14-pushback-and-node-ref/) |
| L15 | 3 | The Course Class IntSLList | 50 dk | a list class with `head` and `tail`, keeping both correct after every operation, preconditions (`isEmpty()` before `delete…`), destructor, `const` member functions | [LC 203](https://leetcode.com/problems/remove-linked-list-elements/) (L15-X, on IntSLList) | [PDF](week04/L15-course-class-intsllist/L15-course-class-intsllist.pdf) · [klasör](week04/L15-course-class-intsllist/) |
| L16 | 4 | Timed Lab: Reverse, Remove, Find the Middle | 50 dk, süreli | three-pointer reversal, removal with a predecessor, slow/fast pointers | [LC 206](https://leetcode.com/problems/reverse-linked-list/) (A) · [LC 876](https://leetcode.com/problems/middle-of-the-linked-list/) (C) · [LC 234](https://leetcode.com/problems/palindrome-linked-list/) (L16-X) | [PDF](week04/L16-timed-lab-reverse-remove/L16-timed-lab-reverse-remove.pdf) · [klasör](week04/L16-timed-lab-reverse-remove/) |
| C04 | C | Thinking Problems on Linked Lists | 60–90 dk | dummy (sentinel) head node, carry propagation, a gap of n between two pointers, split + reverse + merge | [LC 2](https://leetcode.com/problems/add-two-numbers/) · [LC 19](https://leetcode.com/problems/remove-nth-node-from-end-of-list/) · [LC 143](https://leetcode.com/problems/reorder-list/) | [PDF](week04/C04-challenge-linked-list/C04-challenge-linked-list.pdf) · [klasör](week04/C04-challenge-linked-list/) |

### 5. hafta · Doubly ve circular linked list
Ders materyali: [08-linked-lists](../materials/slides/08-linked-lists.ppt), [Labwork 2](../materials/labworks/lw2-doubly-linked-list/), [dönem projesi (metin editörü)](../materials/assignments/2021-fall/term-project-text-editor/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L17 | 1 | The Doubly Linked List Template | 50 dk | class templates (`template <class T>` before every member definition), `prev` and `next` kept consistent, `O(1)` removal at both ends, unlinking a node from the middle, in-place reversal | [LC 707](https://leetcode.com/problems/design-linked-list/) (same operations, as practice on the site) | [PDF](week05/L17-doubly-linked-list-template/L17-doubly-linked-list-template.pdf) · [klasör](week05/L17-doubly-linked-list-template/) |
| L18 | 2 | Delete the Middle Node | 40 dk | slow/fast pointers with an offset, stopping one node before a target, unlink + `delete`, the 0-, 1- and 2-node edge cases | [LC 2095](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/) (M and L18-X) | [PDF](week05/L18-delete-middle-node/L18-delete-middle-node.pdf) · [klasör](week05/L18-delete-middle-node/) |
| L19 | 3 | A Circular List Kept by last | 45 dk | circular lists, keeping only `last`, `do … while` for one full round, the one-node circle (`last->next == last`), `Node*& last` | — | [PDF](week05/L19-circular-list-last/L19-circular-list-last.pdf) · [klasör](week05/L19-circular-list-last/) |
| L20 | 4 | Timed Lab: Merging and Cleaning Lists | 50 dk, süreli | deleting in place without moving forward, merging by relinking with a dummy node, Floyd's cycle detection | [LC 83](https://leetcode.com/problems/remove-duplicates-from-sorted-list/) (A) · [LC 21](https://leetcode.com/problems/merge-two-sorted-lists/) (B) · [LC 141](https://leetcode.com/problems/linked-list-cycle/) (C) | [PDF](week05/L20-timed-lab-merge-lists/L20-timed-lab-merge-lists.pdf) · [klasör](week05/L20-timed-lab-merge-lists/) |
| C05 | C | Thinking Problems on Linked Lists II | 60–100 dk | the math behind Floyd's algorithm, reversing a sub-list between two boundary nodes, interleaving copies to avoid a hash map | [LC 142](https://leetcode.com/problems/linked-list-cycle-ii/) · [LC 25](https://leetcode.com/problems/reverse-nodes-in-k-group/) · [LC 138](https://leetcode.com/problems/copy-list-with-random-pointer/) | [PDF](week05/C05-challenge-linked-list-2/C05-challenge-linked-list-2.pdf) · [klasör](week05/C05-challenge-linked-list-2/) |
| P02 | P | Playlist on a Doubly Linked List | 90–120 dk | a doubly linked list hidden inside a class, a third pointer (`cur`) that must stay valid, relinking two neighbours, formatting time | — | [PDF](week05/P02-playlist-project/P02-playlist-project.pdf) · [klasör](week05/P02-playlist-project/) |

### 6. hafta · Stack
Ders materyali: [09-stacks](../materials/slides/09-stacks.ppt), [Labwork 3](../materials/labworks/lw3-stack-palindrome/), [2021 A2 codeStack](../materials/assignments/2021-fall/a2-code-stack-undo/), [2017 AS3](../materials/assignments/2017-spring/as3-stack-expressions/), [ders kodu week04](../materials/lecture-code/week04/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L21 | 1 | std::stack and the Slides' Stack: empty() vs. !empty() | 40 dk | LIFO, `std::stack` (`push`, `top`, `pop` returning `void`, `empty`), the slides' `bool` API (`pop()`, `pop(item&)`, `getTop(item&)`), guarding every read with an emptiness check | [LC 20](https://leetcode.com/problems/valid-parentheses/) (M1, M2) · [LC 1047](https://leetcode.com/problems/remove-all-adjacent-duplicates-in-string/) (L21-X) | [PDF](week06/L21-std-stack-and-slides-stack/L21-std-stack-and-slides-stack.pdf) · [klasör](week06/L21-std-stack-and-slides-stack/) |
| L22 | 2 | Your Own LLStack<T> | 50 dk | a class template over a linked list, the course names `pushToStack` / `popFromStack` (returns the value), exceptions for an empty stack, destructor, moving a node between two stacks, copy constructor (rule of three) | [LC 155](https://leetcode.com/problems/min-stack/) (next lab) · [LC 232](https://leetcode.com/problems/implement-queue-using-stacks/) (Lab 23) | [PDF](week06/L22-your-own-llstack/L22-your-own-llstack.pdf) · [klasör](week06/L22-your-own-llstack/) |
| L23 | 3 | Two Stacks | 45 dk | moving elements between stacks, how pouring reverses order, comparing two stacks top by top, amortized analysis of a two-stack queue | [LC 232](https://leetcode.com/problems/implement-queue-using-stacks/) (M2) · [LC 946](https://leetcode.com/problems/validate-stack-sequences/) (L23-X) | [PDF](week06/L23-two-stacks/L23-two-stacks.pdf) · [klasör](week06/L23-two-stacks/) |
| L24 | 4 | Timed Lab: Postfix and Min Stack | 50 dk, süreli | postfix evaluation (operand order!), a second stack for extra information, operator precedence with a stack (shunting-yard) | [LC 150](https://leetcode.com/problems/evaluate-reverse-polish-notation/) (A) · [LC 155](https://leetcode.com/problems/min-stack/) (B) · [LC 682](https://leetcode.com/problems/baseball-game/) (L24-X) | [PDF](week06/L24-timed-lab-postfix-minstack/L24-timed-lab-postfix-minstack.pdf) · [klasör](week06/L24-timed-lab-postfix-minstack/) |
| C06 | C | Thinking Problems on Stacks | 60–100 dk | monotonic stacks (“who is waiting for a bigger value?”), a stack of partial results for nested brackets, left/right boundaries found by one stack | [LC 739](https://leetcode.com/problems/daily-temperatures/) · [LC 394](https://leetcode.com/problems/decode-string/) · [LC 84](https://leetcode.com/problems/largest-rectangle-in-histogram/) | [PDF](week06/C06-challenge-stack/C06-challenge-stack.pdf) · [klasör](week06/C06-challenge-stack/) |

### 7. hafta · Queue
Ders materyali: [10-queues](../materials/slides/10-queues.ppt), [ders kodu week05](../materials/lecture-code/week05/), [Labwork 5](../materials/labworks/lw5-priority-queue/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L25 | 1 | std::queue and the Slides' Queue | 45 dk | FIFO, `std::queue` (`push`, `front`, `back`, `pop` returning `void`), the slides' `bool` API: `dequeue()` only removes, `dequeue(item&)` reads and removes, `getFront(item&)` only reads; copy constructor | [LC 933](https://leetcode.com/problems/number-of-recent-calls/) (M1) · [LC 1700](https://leetcode.com/problems/number-of-students-unable-to-eat-lunch/) (L25-X) | [PDF](week07/L25-std-queue-and-slides-queue/L25-std-queue-and-slides-queue.pdf) · [klasör](week07/L25-std-queue-and-slides-queue/) |
| L26 | 2 | LLQueue<T> and the Circular Array Queue | 50 dk | two ends of a linked list (`front`, `rear`), resetting `rear` when the queue empties, a value-returning `dequeue()`, an array whose indexes wrap around with `%`, telling “full” from “empty” with a counter | [LC 622](https://leetcode.com/problems/design-circular-queue/) (M2) · [LC 2073](https://leetcode.com/problems/time-needed-to-buy-tickets/) (L26-X) | [PDF](week07/L26-llqueue-and-circular-array/L26-llqueue-and-circular-array.pdf) · [klasör](week07/L26-llqueue-and-circular-array/) |
| L27 | 3 | Alternate Triples With a Queue and a Stack | 45 dk | the rotation pattern (process exactly `n` elements by moving them to the back), a stack to reverse a group, counting groups without indexes | [GfG Reverse First K of Queue](https://www.geeksforgeeks.org/problems/reverse-first-k-elements-of-queue/1) (B and L27-X) | [PDF](week07/L27-alternate-triples-queue-stack/L27-alternate-triples-queue-stack.pdf) · [klasör](week07/L27-alternate-triples-queue-stack/) |
| L28 | 4 | Delete the Middle, Build a Queue | 45 dk | combining two structures: a linked list of `char` and the slides' `Queue`; middle deletion (Lab 18) + FIFO output; freeing everything at the end | [LC 2095](https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/) · [GfG Queue using Linked List](https://www.geeksforgeeks.org/problems/implement-queue-using-linked-list/1) (L28-X) | [PDF](week07/L28-delete-middle-build-queue/L28-delete-middle-build-queue.pdf) · [klasör](week07/L28-delete-middle-build-queue/) |
| C07 | C | Thinking Problems on Queues and Deques | 60–100 dk | simulating rounds with two queues, a circular array with insertions at both ends, a monotonic deque | [LC 649](https://leetcode.com/problems/dota2-senate/) · [LC 641](https://leetcode.com/problems/design-circular-deque/) · [LC 239](https://leetcode.com/problems/sliding-window-maximum/) | [PDF](week07/C07-challenge-queue/C07-challenge-queue.pdf) · [klasör](week07/C07-challenge-queue/) |

### 8. hafta · Vize provası (üç süreli deneme) ve proje
Ders materyali: [vize notları](../materials/exams/vize-notlari.txt), eski [vize kampı](../practice/midterm-camp/) (30 soru, aynı test düzeni).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L29 | 1 | Midterm Mock A: Lists and Stacks | 50 dk, süreli | the midterm topics in new clothes: two stacks with the slides' API, `empty()`/`!empty()`, deleting the middle of a doubly linked list | — | [PDF](week08/L29-midterm-mock-a/L29-midterm-mock-a.pdf) · [klasör](week08/L29-midterm-mock-a/) |
| L30 | 2 | Midterm Mock B: Strings, Stacks, Queues | 50 dk, süreli | the midterm topics with harder input and the course's own APIs: numbers inside text, two slides' stacks, alternate groups with the slides' queue and stack | — | [PDF](week08/L30-midterm-mock-b/L30-midterm-mock-b.pdf) · [klasör](week08/L30-midterm-mock-b/) |
| L31 | 3 | Midterm Mock C: Variants With Your Own Classes | 50 dk, süreli | the same midterm topics, one step away from what you practised: a different node of the circle, the camp's value-returning APIs, a different output queue | — | [PDF](week08/L31-midterm-mock-c/L31-midterm-mock-c.pdf) · [klasör](week08/L31-midterm-mock-c/) |
| P03 | P | Browser: History With Two Stacks, Downloads in a Queue | 90–120 dk | two stacks as “past” and “future”, clearing a stack, reading a stack without changing it (work on a copy), a FIFO queue with partial progress on its front element | [LC 1472](https://leetcode.com/problems/design-browser-history/) (part B) | [PDF](week08/P03-browser-project/P03-browser-project.pdf) · [klasör](week08/P03-browser-project/) |

### 9. hafta · Graph
Ders materyali: [12-graphs](../materials/slides/12-graphs.pptx), [11-algorithm-analysis](../materials/slides/11-algorithm-analysis.pptx), [Labwork 6](../materials/labworks/lw6-graph-degrees/), [2021 A3](../materials/assignments/2021-fall/a3-directed-graph/), [Practice Lab 4](../materials/practice-labs/pl4-campus-friends/), [2017 AS2](../materials/assignments/2017-spring/as2-algorithm-analysis/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L32 | 1 | Adjacency Matrix and Adjacency List | 40 dk | vertices and edges, directed vs. undirected, the two representations and their costs, degrees from rows and columns, counting edges | [LC 997](https://leetcode.com/problems/find-the-town-judge/) (L32-X) | [PDF](week09/L32-adjacency-matrix-and-list/L32-adjacency-matrix-and-list.pdf) · [klasör](week09/L32-adjacency-matrix-and-list/) |
| L33 | 2 | Breadth-First and Depth-First Traversal | 45 dk | BFS with a queue, DFS recursively and with a stack, the visited array, shortest paths in edges, connected components | [LC 1971](https://leetcode.com/problems/find-if-path-exists-in-graph/) (L33-X) · [GfG BFS of graph](https://www.geeksforgeeks.org/problems/bfs-traversal-of-graph/1) · [GfG DFS of Graph](https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1) | [PDF](week09/L33-bfs-dfs/L33-bfs-dfs.pdf) · [klasör](week09/L33-bfs-dfs/) |
| L34 | 3 | Topological Sorting and Cycles | 45 dk | directed acyclic graphs, the slides' `topSort1`, Kahn's algorithm with a queue, detecting a cycle with a three-colour DFS | [LC 1557](https://leetcode.com/problems/minimum-number-of-vertices-to-reach-all-nodes/) (L34-X) · [GfG Topological sort](https://www.geeksforgeeks.org/problems/topological-sort/1) · [GfG Detect cycle in a directed graph](https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1) | [PDF](week09/L34-topological-sort/L34-topological-sort.pdf) · [klasör](week09/L34-topological-sort/) |
| L35 | 4 | Spanning Trees and Prim's Algorithm | 45 dk | spanning trees from DFS and BFS, weighted graphs as matrices, the minimum spanning tree, Prim's algorithm with `best`/`from` arrays | [LC 1584](https://leetcode.com/problems/min-cost-to-connect-all-points/) (L35-X) · [GfG Minimum Spanning Tree](https://www.geeksforgeeks.org/problems/minimum-spanning-tree/1) | [PDF](week09/L35-spanning-trees-prim/L35-spanning-trees-prim.pdf) · [klasör](week09/L35-spanning-trees-prim/) |
| C09 | C | Thinking Problems on Graphs | 60–100 dk | recognising a graph inside a story: prerequisites as a directed graph, a grid as a graph, two-colouring with BFS | [LC 207](https://leetcode.com/problems/course-schedule/) · [LC 994](https://leetcode.com/problems/rotting-oranges/) · [LC 785](https://leetcode.com/problems/is-graph-bipartite/) | [PDF](week09/C09-challenge-graph/C09-challenge-graph.pdf) · [klasör](week09/C09-challenge-graph/) |
| P04 | P | Metro Route Planner | 90–120 dk | a graph whose vertices have names (`std::map` name → number), edges that carry data, BFS with a `parent` array to rebuild the path, distances | [LC 815](https://leetcode.com/problems/bus-routes/) (the hard version: fewest buses instead of fewest stops) | [PDF](week09/P04-metro-project/P04-metro-project.pdf) · [klasör](week09/P04-metro-project/) |

### 10. hafta · Tree ve BST
Ders materyali: [13-trees](../materials/slides/13-trees.pptx), okuma: [14-avl-trees](../materials/slides/14-avl-trees.pptx), [15-2-3-trees-red-black](../materials/slides/15-2-3-trees-red-black.pptx); [Labwork 7](../materials/labworks/lw7-bst-queries/), [2021 A4](../materials/assignments/2021-fall/a4-tree-functions/), [2017 AS5](../materials/assignments/2017-spring/as5-trees-graphs-heaps/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L36 | 1 | Binary Trees: Counting, Traversals, Height | 45 dk | binary tree terminology, recursion on trees (base case = empty tree), preorder/inorder/postorder, height, level order with a queue, freeing a tree in postorder | [LC 102](https://leetcode.com/problems/binary-tree-level-order-traversal/) · [LC 104](https://leetcode.com/problems/maximum-depth-of-binary-tree/) · [LC 226](https://leetcode.com/problems/invert-binary-tree/) (L36-X) | [PDF](week10/L36-binary-tree-traversals/L36-binary-tree-traversals.pdf) · [klasör](week10/L36-binary-tree-traversals/) |
| L37 | 2 | Binary Search Trees | 45 dk | the BST property, insert and search along one path (`O(h)`), min/max, checking the property with ranges, treesort, printing a tree's shape | [LC 98](https://leetcode.com/problems/validate-binary-search-tree/) · [LC 700](https://leetcode.com/problems/search-in-a-binary-search-tree/) · [LC 108](https://leetcode.com/problems/convert-sorted-array-to-binary-search-tree/) (L37-X) | [PDF](week10/L37-binary-search-tree/L37-binary-search-tree.pdf) · [klasör](week10/L37-binary-search-tree/) |
| L38 | 3 | Deleting From a Binary Search Tree | 45 dk | the three cases of deletion (leaf, one child, two children), the inorder successor and predecessor, deletion by copying vs. by merging, pointer-to-pointer links | [LC 450](https://leetcode.com/problems/delete-node-in-a-bst/) · [LC 669](https://leetcode.com/problems/trim-a-binary-search-tree/) (L38-X) | [PDF](week10/L38-bst-deletion/L38-bst-deletion.pdf) · [klasör](week10/L38-bst-deletion/) |
| L39 | 4 | Tree Questions From the Course Archive | 50 dk | inorder with a counter, pruning a BST search, height-balance in one pass, sibling checks, rebuilding a tree from two traversals | [LC 230](https://leetcode.com/problems/kth-smallest-element-in-a-bst/) · [LC 110](https://leetcode.com/problems/balanced-binary-tree/) · [LC 105](https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/) · [LC 1382](https://leetcode.com/problems/balance-a-binary-search-tree/) (L39-X) | [PDF](week10/L39-tree-archive-questions/L39-tree-archive-questions.pdf) · [klasör](week10/L39-tree-archive-questions/) |
| C10 | C | Thinking Problems on Binary Trees | 60–100 dk | returning information upward from subtrees, carrying information downward (prefix sums), the difference between “the best answer” and “what the parent may use” | [LC 236](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) · [LC 437](https://leetcode.com/problems/path-sum-iii/) · [LC 124](https://leetcode.com/problems/binary-tree-maximum-path-sum/) | [PDF](week10/C10-challenge-tree/C10-challenge-tree.pdf) · [klasör](week10/C10-challenge-tree/) |
| P05 | P | Phone Book on a Binary Search Tree | 90–120 dk | a BST class with string keys and a value, private recursive helpers, `Entry**` links, deletion by copying, a pruned range query, saving in preorder, the rule of three | [LC 208](https://leetcode.com/problems/implement-trie-prefix-tree/) (the structure made for prefix searches) | [PDF](week10/P05-phonebook-project/P05-phonebook-project.pdf) · [klasör](week10/P05-phonebook-project/) |

### 11. hafta · Hash
Ders materyali: [17-hash-tables](../materials/slides/17-hash-tables.pptx), [2021 A5](../materials/assignments/2021-fall/a5-hashing/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L40 | 1 | Hash Functions and Separate Chaining | 45 dk | hash tables, hash functions for strings (sum, Horner with 37), collisions, separate chaining with `std::list`, the load factor, negative keys and `%` | [LC 705](https://leetcode.com/problems/design-hashset/) · [LC 1](https://leetcode.com/problems/two-sum/) (L40-X) | [PDF](week11/L40-hash-functions-chaining/L40-hash-functions-chaining.pdf) · [klasör](week11/L40-hash-functions-chaining/) |
| L41 | 2 | Open Addressing: Linear, Quadratic, Double Hashing | 45 dk | probe sequences, primary clustering, why quadratic probing can miss free slots, double hashing, the three slot states and why deletion needs a DELETED mark | [LC 706](https://leetcode.com/problems/design-hashmap/) · [GfG Linear Probing in Hashing](https://www.geeksforgeeks.org/problems/linear-probing/1) | [PDF](week11/L41-open-addressing/L41-open-addressing.pdf) · [klasör](week11/L41-open-addressing/) |
| L42 | 3 | unordered_map, unordered_set and map | 45 dk | the library's hash tables, `operator[]` vs `find`/`count`, counting with a map, “last index seen”, sliding windows, `std::map` when the order matters | [LC 387](https://leetcode.com/problems/first-unique-character-in-a-string/) · [LC 219](https://leetcode.com/problems/contains-duplicate-ii/) · [LC 242](https://leetcode.com/problems/valid-anagram/) · [LC 3](https://leetcode.com/problems/longest-substring-without-repeating-characters/) · [LC 205](https://leetcode.com/problems/isomorphic-strings/) (L42-X) | [PDF](week11/L42-unordered-map-set/L42-unordered-map-set.pdf) · [klasör](week11/L42-unordered-map-set/) |
| C11 | C | Thinking Problems on Hashing | 60–90 dk | choosing the key of a hash map (a canonical form), “is this the start of a run?”, prefix sums counted in a map | [LC 49](https://leetcode.com/problems/group-anagrams/) · [LC 128](https://leetcode.com/problems/longest-consecutive-sequence/) · [LC 560](https://leetcode.com/problems/subarray-sum-equals-k/) | [PDF](week11/C11-challenge-hash/C11-challenge-hash.pdf) · [klasör](week11/C11-challenge-hash/) |

### 12. hafta · Heap ve öncelik kuyruğu
Ders materyali: [16-heaps](../materials/slides/16-heaps.pptx), [Labwork 8](../materials/labworks/lw8-min-heap/), [Labwork 5](../materials/labworks/lw5-priority-queue/), [2017 AS5 Q4](../materials/assignments/2017-spring/as5-trees-graphs-heaps/).

| No | Gün | Başlık | Süre | Konu | Benzer sorular | PDF |
| --- | --- | --- | --- | --- | --- | --- |
| L43 | 1 | The Slides' Max-Heap in an Array | 45 dk | complete binary trees stored in arrays, the heap property, trickle up (insert), trickle down (rebuild a semiheap), delete the root, bottom-up heap construction in `O(n)` | [LC 1046](https://leetcode.com/problems/last-stone-weight/) (L43-X) · [GfG Does array represent Heap](https://www.geeksforgeeks.org/problems/does-array-represent-heap/1) | [PDF](week12/L43-max-heap/L43-max-heap.pdf) · [klasör](week12/L43-max-heap/) |
| L44 | 2 | Min-Heap Questions From the Archive | 45 dk | a min-heap in a 1-based array (children 2i and 2i+1), percolate down with a loop, bottom-up construction, delete-min, insert, reading a heap's shape from its preorder | [GfG Heap Sort](https://www.geeksforgeeks.org/problems/heap-sort/1) · [LC 1046](https://leetcode.com/problems/last-stone-weight/) | [PDF](week12/L44-min-heap-archive/L44-min-heap-archive.pdf) · [klasör](week12/L44-min-heap-archive/) |
| L45 | 3 | Heapsort and std::priority_queue | 45 dk | heapsort in place (`O(n log n)`, no extra array), the library's heap `std::priority_queue` (max by default, min with `greater`, custom comparators), “keep the best k” with a heap of size k | [LC 215](https://leetcode.com/problems/kth-largest-element-in-an-array/) · [GfG Nearly sorted](https://www.geeksforgeeks.org/problems/nearly-sorted-1587115620/1) · [LC 973](https://leetcode.com/problems/k-closest-points-to-origin/) (L45-X) | [PDF](week12/L45-heapsort-priority-queue/L45-heapsort-priority-queue.pdf) · [klasör](week12/L45-heapsort-priority-queue/) |
| L46 | 4 | Priority Queues at Work | 50 dk | a stable priority queue with arrival numbers, Dijkstra's shortest paths, Prim with a heap (`O(E log V)`), simulating a scheduler, lazy deletion (“skip stale entries”) | [LC 743](https://leetcode.com/problems/network-delay-time/) · [LC 1834](https://leetcode.com/problems/single-threaded-cpu/) · [LC 1642](https://leetcode.com/problems/furthest-building-you-can-reach/) (L46-X) | [PDF](week12/L46-priority-queue-applications/L46-priority-queue-applications.pdf) · [klasör](week12/L46-priority-queue-applications/) |
| C12 | C | Thinking Problems on Heaps | 60–100 dk | a heap of list heads, two heaps that balance each other, counting with a map then keeping the best k | [LC 23](https://leetcode.com/problems/merge-k-sorted-lists/) · [LC 295](https://leetcode.com/problems/find-median-from-data-stream/) · [LC 347](https://leetcode.com/problems/top-k-frequent-elements/) | [PDF](week12/C12-challenge-heap/C12-challenge-heap.pdf) · [klasör](week12/C12-challenge-heap/) |
| P06 | P | Emergency Room Triage on Your Own Heap | 100–120 dk | a heap of structs with a two-level priority (severity, then arrival), sift up and sift down as helpers, changing the priority of an item inside the heap, removing from the middle, reporting through a copy | [LC 1845](https://leetcode.com/problems/seat-reservation-manager/) · [LC 2353](https://leetcode.com/problems/design-a-food-rating-system/) (priority changes) | [PDF](week12/P06-triage-project/P06-triage-project.pdf) · [klasör](week12/P06-triage-project/) |

## Vize başlıklarının dağılımı

[Vize notundaki](../materials/exams/vize-notlari.txt) her başlık önce tek başına öğretiliyor, sonra asıl veri yapısıyla soruluyor, 8. haftada da süreli olarak, biraz değiştirilmiş hâliyle tekrar geliyor. Notta yazmayan kurallar (grup sayma, eksik grup, çift uzunlukta “orta”, boşken davranış) ilgili PDF’te **alıştırma varsayımı** olarak açıkça yazılı.

| Vize başlığı | Hazırlık | Asıl lab | Süreli tekrar |
| --- | --- | --- | --- |
| İki stack’te push ve pop | L21, L22 (`pushToStack`/`popFromStack`) | L23 | L29-A |
| `st.empty()` ve `!st.empty()` farkı | L21 | L23 | L29-B |
| İki string birbirinin tersi mi (iki stack) | L03 (vektör), L09 (string) | L23 | L30-B |
| Sayıları üçerli döndürme `1…9 → 3 2 1 4 5 6 9 8 7` | L03 (vektör, yerinde) | L27 (queue + tek stack) | L30-C, L31-B |
| String’deki minimum sayı, geçici değişkenle | L10 | L12 | L30-A |
| Ortadaki elemanı düğümden silip yeni queue’da yazdırma | L16, L18 (silme) | L28 | L29-C (doubly), L31-C |
| Circular listede `last` düğümünü silip yeniden bağlama | L13 (kâğıt izi) | L19 | L31-A |

## Labwork ve ödevler nerede?

Arşivdeki her sorunun derlenen ve testten geçen çözümü [`../materials`](../materials/README.md) altında duruyor. Kamp aynı soruları lab formatında, testli ve adım adım çözümlü olarak tekrar soruyor:

| Arşiv | Kampta |
| --- | --- |
| Labwork 1 (`IntSLList`) · Labwork 2 (`genDLList`) · Labwork 3 (DLL üzerinde stack, palindrome) | L15 · L17 · L17, L24 |
| Labwork 5 (öncelik kuyruğu, eşitlikte FIFO) | L46-A, P06 |
| Labwork 6 (`indegree`, `outdegree`, `num_edges`) | L32 (M1, M2) |
| Labwork 7 (`getnthelement`, `printsmallerthan`, `isbalanced`, silme) | L38, L39 |
| Labwork 8 (`percolate_down`, `delete_min`, `heapify`, `inorder`) | L44 |
| Practice Lab 2 (linked list soruları) · Practice Lab 4 (Campus Friends: BFS, DFS, grup sayısı) | L13–L16, L19, L20 · L33 |
| 2017 AS1 (notlar listesi) · AS2 (karmaşıklık) · AS3 (stack ile ifadeler) · AS4 (sınıflar) | P01 · L32 · L24 · L11 |
| 2017 AS5 Q1, Q2, Q4, Q5 (ağaç kurma, BST şekli ve silme, heap) | L39-M3, L37-M4, L38-V, L44, L36-V, L37-V |
| 2021 A1 (sıralama, düğüm takası) · A2 (`codeStack`, undo) · A3 (yönlü graf, BFS) | L15, L16 · L22, P03 · L33, P04 |
| 2021 A4 (`isThisaBST`, `findHeight`, `findOnlyChild`) · A5 (zincirli hash) | L37-M2, L36-M2, L39-M2 · L40 |

## Özel fonksiyonlar haritası

Aynı işlem farklı sınıflarda farklı adla ve farklı dönüş tipiyle geliyor. Tablo, adın nereden geldiğini ve kampta hangi labda kullanıldığını gösteriyor. “Alıştırma imzası” yazan adlar arşivde yok; ilgili labda imzası açıkça verilen bir alıştırma olarak öğretiliyor, dersin gerçek API’si sayılmıyor.

| İşlem | Standart C++ | Arşivdeki gerçek ad ve sözleşme | Lab |
| --- | --- | --- | --- |
| Sona ekle | `v.push_back(x)` | `pushBack(Node*& head, int value)` ([Practice Lab 2](../materials/practice-labs/pl2-linked-list/solution/q3.cpp)) · `addToTail(int)` ([IntSLList](../materials/labworks/lw1-singly-linked-list/solution/intSLList.h)) · `addToDLLTail(const T&)` ([genDLList](../materials/labworks/lw2-doubly-linked-list/solution/genDLList.h)) · `pushToBack`: alıştırma imzası | L01, L14, L15, L17 |
| Başa ekle | `d.push_front(x)` (`deque`, `list`) | `addToHead(int)`, `addToDLLHead(const T&)` | L15, L17 |
| Baştan/sondan sil | `pop_front()`, `pop_back()` → `void` | `deleteFromHead()`, `deleteFromTail()` → `int`, boş listede tanımsız (önce `isEmpty()`); `deleteFromDLLHead/Tail()` → `T` | L15, L17 |
| Stack’e ekle | `st.push(x)` | slayt: `bool push(StackItemType)` · `pushToStack(const char*)` ([A2 codeStack](../materials/assignments/2021-fall/a2-code-stack-undo/given/codeStack.h)) · `pushToStack(const T&)` (kamp `LLStack`) | L21, L22 |
| Stack’ten çıkar | `st.top()` ile oku, `st.pop()` ile sil (`void`) | slayt: `bool pop()` yalnızca siler, `bool pop(item&)` değeri yazar, `bool getTop(item&) const` · `popFromStack()` değeri döndürür (A2’de `string`, kampta `T`) | L21, L22, L23 |
| Taşı | — | `pushFromStack(src, dst)`: alıştırma imzası | L22, L23 |
| Queue’ya ekle | `q.push(x)` | slayt: `bool enqueue(item)` · A3 ve kamp `LLQueue`: `void enqueue` | L25, L26 |
| Queue’dan çıkar | `q.front()` ile oku, `q.pop()` ile sil (`void`) | slayt: `bool dequeue()` yalnızca siler, `bool dequeue(item&)` değeri yazar, `bool getFront(item&) const` · A3 ve kamp `dequeue()` değeri döndürür | L25–L28 |
| Boş mu? | `empty()` | `isEmpty()`: IntSLList’te `int`, diğerlerinde `bool` | L15, L21, L25 |
| Heap | `std::priority_queue`, `push_heap`/`pop_heap` | slayt: `heapInsert`, `heapDelete(item&)`, `heapRebuild(root)` · Labwork 8: `percolate_down`, `delete_min`, `heapify` | L43, L44, L45 |
| Hash | `std::unordered_map`, `unordered_set` | slayt: `int hash(const string& key, int tableSize)` · A5: `insertIntoHashTable`, `searchInHashTable`, `encodeString` | L40, L41, L42 |

## Tekrar planı

- **Her haftanın sonunda:** PDF’in sonundaki kontrol listesi. Bir maddeye “hayır” diyorsan o labı boş dosyadan tekrar yaz (`lab.cpp`’yi silip `git checkout` ile başlangıç hâline getirebilirsin).
- **V soruları:** her labın sonundaki ezberden varyantı 48 saat sonra, PDF’e bakmadan, süre tutarak yaz. Kampın ezber kartları bunlar.
- **Vizeden önce (4–8. haftalar):** L29–L31’i 50 dakikalık sınav koşullarında çöz. 80’in altında kalan her parçanın labı provanın cevap anahtarında yazıyor.
- **Finalden önce (9–12. haftalar):** her haftanın 4. labını (L35, L39, L42, L46) süre tutarak tekrar çöz; slayttaki izleri (BFS/DFS sırası, `topSort1`, Prim, BST silme, açık adresleme tabloları, heap kurma/silme) kâğıtta yap ve sonucunu programla karşılaştır.
- **Projeler:** her projenin PDF’indeki “genişletme fikirleri”nden birini seç; kendi testini yazarak ekle.

## Klasör düzeni ve PDF üretimi

```
lab-camp/
├── README.md               bu dizin
├── run.ps1, run.sh         derle + test et
├── week01/ … week12/
│   └── L01-vector-first-steps/
│       ├── L01-vector-first-steps.pdf   ← lab sorusu, Türkçe anlatım, çözüm
│       ├── lab01.h                      verilen başlık (dokunma)
│       ├── lab01.cpp                    ← SEN BURADA ÇALIŞIYORSUN
│       ├── warmup.cpp                   ısınma programı (ilk haftalarda)
│       └── tests/                       testler + PDF tablolarından üretilen pdf_cases.inc
├── solutions/L01/          referans çözüm ve PDF’teki alternatifler (çözümden sonra bak)
├── framework/              küçük test çatısı: test.h, todo.h, tree_build.h (ağaç testleri)
└── _tools/                 PDF üretimi: labs/*.html şablonları, build.py, draw.py, style.css
```

PDF’leri yeniden üretmek ya da yeni bir lab eklemek için `python _tools/build.py L01` (Microsoft Edge ve `pygments` gerekir) ve `python _tools/build.py verify L01` kullan. `verify`, başlangıç dosyalarının derlendiğini ve hepsinin “not written yet” verdiğini, referans çözümlerin bütün testleri geçtiğini ve ısınma programlarının uyarısız derlendiğini kontrol eder. PDF’teki kod blokları derlenen dosyalardan, test tabloları da testlerin okuduğu `pdf_cases.inc` dosyasından geliyor; bu yüzden PDF ile testler birbirinden ayrışamaz.
