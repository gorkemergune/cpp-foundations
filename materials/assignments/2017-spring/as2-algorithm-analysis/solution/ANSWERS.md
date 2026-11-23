# Assignment 2 (2017) · Algoritma analizi · çözüm

## 1. Büyüme hızlarını sırala (yavaştan hızlıya)

| Sıra | İfade | Baskın terim | Sınıf |
| --- | --- | --- | --- |
| 1 | iv. `90000 + log n` | `log n` | `O(log n)` |
| 2 | ii. `50000·n + 3·log n` | `n` | `O(n)` |
| 3 | v. `log n + n·log n` | `n log n` | `O(n log n)` |
| 4 | iii. `n^(7/6) + n^(5/6)` | `n^(7/6)` | `O(n^(7/6))` |
| 5 | i. `n² + n` | `n²` | `O(n²)` |
| 6 | viii. `4ⁿ + n^500000` | `4ⁿ` | `O(4ⁿ)` |
| 7 | vi. `n! + 2ⁿ` | `n!` | `O(n!)` |
| 8 | vii. `(n+1)! + 20000ⁿ` | `(n+1)!` | `O((n+1)!)` |

Notlar:
- `n log n` ile `n^(7/6)`: `log n` her pozitif kuvvetten (`n^(1/6)` dahil) yavaş büyür, bu yüzden `n log n` önce gelir. Arşivdeki cevap `n^(7/6)`’yı `n²`’den sonraya koyuyor. Bu yanlış: `7/6 < 2`.
- `n^500000` bir polinom. Çok büyük `n` için her üstel fonksiyon (`4ⁿ`) her polinomu geçer. Küçük `n`’lerde tersi görünse de sıralama asimptotiktir.
- `(n+1)! = (n+1)·n!`. Aynı sınıfa yakın görünür ama `n!`’in sabit katı değildir, daha hızlı büyür. `20000ⁿ` üstel olduğu için faktöriyelin yanında kaybolur.

## 2. Dört kat yavaş bilgisayar

Algoritma `c·n²` adım atıyor. C bilgisayarı `t` sürede `c·1000²` adım atıyor. D, C’den 4 kat yavaş olduğu için aynı sürede bunun dörtte birini atar: `n² = 1000² / 4` → **n = 500**.

## 3. Kaynak kodu olmadan iki programı karşılaştırma

Aynı makinede, aynı girdilerle ve birçok farklı girdi boyutunda (`n`, `2n`, `4n` …) iki programı çalıştırıp süreleri ölç (benchmark). Tek bir ölçüm yetmez. Süre `n` ikiye katlandığında yaklaşık 2 katına çıkıyorsa doğrusal, 4 katına çıkıyorsa karesel bir büyüme vardır. Her ölçümü birkaç kez tekrarlayıp ortalama al. İsteğe bağlı olarak bellek kullanımını da karşılaştır.

## 4. Kod parçalarının Big-O’su

| Parça | Cevap | Neden |
| --- | --- | --- |
| a | `O(N²)` | iç içe iki döngü `N²` + ayrı bir döngü `N` → `N² + N` |
| b | `O(N²)` | iç döngü `N − i` kez döner: toplam `N + (N−1) + … + 1 = N(N+1)/2` |
| c | `O(N)` | `j = 1; j > N` koşulu `N ≥ 1` için baştan yanlış, iç döngü hiç dönmez. **Dış döngü yine de `N` kez döner.** Arşivdeki “O(0)” cevabı yanlış. |
| d | `O(1)` | `10000 · 49` sabit sayıda adım, `N`’ye bağlı değil |

`test.cpp`, (a)–(d) parçalarındaki iç gövdenin kaç kez çalıştığını sayarak bu tabloyu doğruluyor.
