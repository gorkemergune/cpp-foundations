# CSE 211 lab API örnekleri

Labda ilk olarak verilen `.h` dosyasına bak. Sınıfın adını, fonksiyonun tam yazımını, dönüş tipini ve boş yapı davranışını işaretle. Örneğin `pop()` tek başına değerin döndürülüp döndürülmediğini söylemez.

## Derle ve çalıştır

Depo kökünde PowerShell ile çalıştır. İlk dosya standart kütüphane ve kamp API’leriyle, ikinci dosya arşivdeki Linked List, Campus Friends ve Heap sınıflarıyla küçük örnekler çalıştırır. Her bölüm beklenen değerleri `assert` ile kontrol eder.

```powershell
$labApiExe = Join-Path ([System.IO.Path]::GetTempPath()) 'cse211-lab-api.exe'
g++ -std=c++17 -Wall -Wextra -pedantic practice/midterm-camp/examples/lab_api.cpp -o $labApiExe
if ($LASTEXITCODE -eq 0) { & $labApiExe }
```

```powershell
$archiveApiExe = Join-Path ([System.IO.Path]::GetTempPath()) 'cse211-archive-api.exe'
g++ -std=c++17 -Wall -Wextra -pedantic practice/midterm-camp/examples/archive_api.cpp materials/labworks/lw1-singly-linked-list/archive-solution/intSLList.cpp materials/labworks/lw8-min-heap/archive-solution/heap.cpp materials/practice-labs/pl4-campus-friends/practicelab4_solution/Graph.cpp materials/practice-labs/pl4-campus-friends/practicelab4_solution/Student.cpp -o $archiveApiExe
if ($LASTEXITCODE -eq 0) { & $archiveApiExe }
```

[Kamp ve STL örnekleri](lab_api.cpp) · [Arşiv sınıflarının örnekleri](archive_api.cpp)

## Aynı işlem için farklı fonksiyonlar

| İşlem | Standart C++ | Ders veya kamp |
| --- | --- | --- |
| Arkaya ekle | `v.push_back(x)` · `vector`, `deque`, `list` | Linked list’te `pushBack(head, x)`, `addToTail(x)`, `addToDLLTail(x)` |
| Öne ekle | `d.push_front(x)` · `deque`, `list` | `addToHead(x)`, `addToDLLHead(x)` |
| Önden veya arkadan çıkar | `pop_front()` ve `pop_back()` · `void` | `deleteFromHead()`, `deleteFromTail()`, `deleteFromDLLHead()`, `deleteFromDLLTail()` değer döndürür |
| Stack’e ekle | `st.push(x)` | `st.pushToStack(x)` |
| Stack tepesini silmeden oku | `st.top()` | Kamp `st.peek()` · ST-2. `LLStack` içindeki `top` özel veri alanı |
| Stack’ten çıkar | `st.top()` ile oku, `st.pop()` ile sil · `pop()` dönüşü `void` | `st.popFromStack()` değer döndürür |
| Queue’ya arkadan ekle | `q.push(x)` | `q.enqueue(x)` · kampta `void`, dersteki `Queue` sınıfında `bool` |
| Queue’nun önünü oku | `q.front()` | Kamp `q.getFront()` · QU-2. Derste `q.getFront(out)` · `bool` |
| Queue’nun arkasını oku | `q.back()` | Kamp `q.getRear()` · QU-2 |
| Queue’dan önden çıkar | `q.front()` ile oku, `q.pop()` ile sil · `pop()` dönüşü `void` | Kamp `q.dequeue()` değer döndürür. Derste `q.dequeue()` veya `q.dequeue(out)` · ikisi de `bool` |
| Boş mu? | `st.empty()`, `q.empty()` | `st.isEmpty()`, `q.isEmpty()` |
| Öncelikli öğeyi oku ve çıkar | `pq.top()` ardından `pq.pop()` · `pop()` dönüşü `void` | Labwork 8’de `heap.delete_min()` · `void` |

Arşivde sona ekleme için gerçek yazımlardan biri `pushBack(Node*& head, int value)`. Sorduğun `pushToBack` ve `pushFromStack` adları taradığım kaynaklarda geçmediği için bunları örnek dosyada **alıştırma imzası** olarak tanımladım. `pushToBack(items, value)` arkaya ekliyor. `pushFromStack(source, destination)` kaynak stack’in tepesini hedef stack’e taşıyor. Labda bu adlardan biri verilirse imzayı ve davranışı sorunun başlığından al. [Practice Lab 2 kaynak kodu](../../../materials/practice-labs/pl2-linked-list/solution/q3.cpp)

## Push, pop ve boşluk kontrolü

`st.empty()` boşken `true`, `!st.empty()` eleman varken `true`. Std stack veya queue’da okunan değeri silmeden önce bir değişkene al. `auto&` ile aldığın referansı öğe silindikten sonra kullanma.

```cpp
// std::stack<int> st
while (!st.empty()) {
    const int value = st.top();
    st.pop();
    std::cout << value << ' ';
}
```

```cpp
// LLStack<int> st
while (!st.isEmpty()) {
    const int value = st.popFromStack();
    std::cout << value << ' ';
}
```

Dersteki `Queue` örneğinde aşağıdaki döngü FIFO sırasını verir. `dequeue(out)` değeri parametreye yazar ve başarıyı döndürür. Parametresiz `dequeue()` yalnızca çıkarır ve başarıyı döndürür. Aynı satırı kampın değer döndüren `dequeue()` fonksiyonuyla yazarsan, kuyruktan çıkan `0` yanlışlıkla döngüyü keser. [Dersteki Queue sınıfı ve çalışan testleri](../../../materials/lecture-code/week05/queue.cpp)

```cpp
Queue q;
q.enqueue('A');
q.enqueue('B');
char out{};
while (q.dequeue(out)) {
    std::cout << out << ' ';
}
```

Kampın `popFromStack()` ve `dequeue()` işlevleri boş yapıda `std::runtime_error` fırlatır. `IntSLList` ve `DoublyLinkedList` çıkarma işlevlerinde önce `isEmpty()` ile kontrol et. [LLStack](../ds/LLStack.h) · [LLQueue](../ds/LLQueue.h) · [IntSLList](../../../materials/labworks/lw1-singly-linked-list/archive-solution/intSLList.h) · [DoublyLinkedList](../../../materials/labworks/lw2-doubly-linked-list/archive-solution/genDLList.h)

## Okurken karşılaşacağın diğer özel imzalar

| Kaynak | Çağrılar ve dikkat edilecek sözleşme |
| --- | --- |
| [Kamp stack](../ds/LLStack.h) | `peek`, `contains`, `size`, `reverseStack`, `removeAll`, `sortStack` soru fonksiyonları. İlgili ST görevini bitirdikten sonra kullan. |
| [Kamp queue](../ds/LLQueue.h) | `size`, `getFront`, `getRear`, `contains`, `countGreater`, `reverse`, `removeAll`, `rotate`, `reverseFirstK`, `interleave` soru fonksiyonları. İlgili QU görevini bitirdikten sonra kullan. |
| [Kamp linked list](../ds/LinkedList.h) | `count`, `countValue`, `indexOfMax`, `insertAtEnd`, `removeFirst`, `reverse`, `insertSorted`, `insertAfterEach`, `removeDuplicates`, `swapPairs` LL görevlerinde tamamlanıyor. |
| [A2 codeStack](../../../materials/assignments/2021-fall/a2-code-stack-undo/given/codeStack.h) | `pushToStack(const char*)`, `popFromStack() -> std::string`, `isEmpty()`, `printStack()`, `printReverseStack()`. `std::string line` ile `st.pushToStack(line.c_str())` yazılır. |
| [A3 queue](../../../materials/assignments/2021-fall/a3-directed-graph/given/queue.h) | `enqueue(T)`, `dequeue() -> T`, `firstElement() -> T`, `isEmpty()`, `Average1()`. `firstElement()` silmeden okur. |
| [DoublyLinkedList](../../../materials/labworks/lw2-doubly-linked-list/archive-solution/genDLList.h) | `firstEl() -> T&`, `find(value) -> T*`, `append(other)`, `split()`, `clear()`. `find` sonucunu dereference etmeden önce `nullptr` kontrolü yap. |
| [Campus Friends Graph](../../../materials/practice-labs/pl4-campus-friends/practicelab4_solution/Graph.h) | `addStudent`, `addFriendship`, `getSize`, `indexOf`, `getStudent`, `bfs`, `dfs`, `mostPopular`, `mutualFriends`, `countGroups`, `suggestFriends`, `printNetwork`. Geçersiz ID’de `getStudent` null, `indexOf` `-1`. |
| [Labwork 7 BST](../../../materials/labworks/lw7-bst-queries/archive-solution/genBST.h) | `insert`, `recursiveInsert`, `search`, `recursiveSearch`, traversal’lar ve `findAndDeleteByCopying` / `findAndDeleteByMerging`. Aynı dosyadaki özel `Stack<T>::pop() -> T` ve `Queue<T>::dequeue() -> T` değer döndürür. Bu arşiv başlığında GCC’nin işaretlediği eksik noktalı virgül ve template üye erişimi hataları var. |
| [Labwork 8 heap](../../../materials/labworks/lw8-min-heap/archive-solution/heap.h) | `heap(int*, int)` verilen diziyi yerinde düzenler. `delete_min()`, `print()`, `inorder()` herkese açık. Örnekte kalan eleman sayısı biliniyor. Boşken arşivdeki `delete_min()` çağrısına girme. |
| [Labwork 5 PriorityQueue](../../../materials/labworks/lw5-priority-queue/archive-solution/priority_queue.h) | `enqueue(value, priority)`, `isEmpty()`, `dequeue()`. Arşivde `dequeue` dönüşü `T&` ilan edilmiş, gövde `T` geçici değeri döndürüyor. Bu imzayı çalışır bir örnek için kopyalamadan önce dönüş tipini sözleşmeye göre düzeltmek gerekir. |

## Lab ödevleri

1. **Aynı soruyu iki stack API’si ile çöz.** A’ya sırayla 4 ve 9, B’ye 7 ekle. A’nın tepesini B’ye taşı. Taşıma sonrası A’nın tepesi 4, B’ninki 9 olsun. Önce yalnızca `push/top/pop/empty`, sonra `pushToStack/popFromStack/isEmpty`. Boş A’da B’yi koru.
2. **Queue API’sini değiştir.** Giriş 0, 3 ve 5 olsun. FIFO sırasını önce `std::queue`, sonra `LLQueue`, sonra `dequeue(out)` kullanan ders sınıfıyla yazdır. Üç sürümde de 0’ın çıktığını kontrol et.
3. **Aynı uç işlemini farklı sınıflarla yap.** Öne 1, arkaya 2, arkaya 3 ekle. Önce arkadan, sonra önden çıkar. Ortada 2 kalsın. `deque`, `IntSLList` ve `DoublyLinkedList` sürümlerinde fonksiyon adlarını başlıktan seç.
4. **İlk k öğeyi ters çevir.** Örnek dosyadaki çözümü bir kez incele. Ardından kapatıp `1 2 3 4 5`, `k=3` için sonucu `3 2 1 4 5` veren sürümü yaz. `k=0`, `k>n` ve `k=n` testlerini ekle. [GeeksforGeeks Reverse First K of a Queue](https://www.geeksforgeeks.org/problems/reverse-first-k-elements-of-queue/1)
5. **İki stack ile FIFO.** Hangi stack’e ekleyeceğini ve ne zaman aktaracağını çiz. Yeni öğeleri araya eklerken önceki öğelerin önde kaldığını test et. [LeetCode Implement Queue using Stacks](https://leetcode.com/problems/implement-queue-using-stacks/)
