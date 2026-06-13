A quick and intuitive summary of the **`multi`** and **`unordered_multi`** versions of `set` and `map`:

---

## 🔁 **Allow Duplicate Keys** – That’s the key difference!
### 🔹 `multiset`

* ✅ **Duplicates allowed**
* 🔢 Sorted order
* ⚙️ Backed by: **Red-Black Tree (BST)**
* 🕒 Time: **O(log n)**
* 🧠 Use when you need to **store repeated values in order**

```cpp
multiset<int> ms;
ms.insert(5);
ms.insert(5); // both stored
```

---

### 🔹 `unordered_multiset`

* ✅ **Duplicates allowed**
* ❌ No order
* ⚙️ Backed by: **Hash Table**
* 🕒 Time: **O(1)** avg
* 🧠 Use when you need **fast insert/search with duplicates**

```cpp
unordered_multiset<int> ums;
ums.insert(5);
ums.insert(5); // both stored
```

---

### 🔹 `multimap`

* ✅ **Duplicate keys allowed**
* 🔢 Sorted by key
* ⚙️ Backed by: **Red-Black Tree**
* 🕒 Time: **O(log n)**
* 🧠 Use when one key maps to **multiple values**, and order matters

```cpp
multimap<string, int> mm;
mm.insert({"apple", 10});
mm.insert({"apple", 20}); // both stored
```

---

### 🔹 `unordered_multimap`

* ✅ **Duplicate keys allowed**
* ❌ No order
* ⚙️ Backed by: **Hash Table**
* 🕒 Time: **O(1)** avg
* 🧠 Use when one key maps to **multiple values**, and order doesn’t matter

```cpp
unordered_multimap<string, int> umm;
umm.insert({"apple", 10});
umm.insert({"apple", 20});
```

---

## 🧠 Summary Table

| Container            | Ordered? | Duplicates? | Backed By      | Time (avg) |
| -------------------- | -------- | ----------- | -------------- | ---------- |
| `set`                | ✅ Yes    | ❌ No        | Red-Black Tree | O(log n)   |
| `unordered_set`      | ❌ No     | ❌ No        | Hash Table     | O(1)       |
| `multiset`           | ✅ Yes    | ✅ Yes       | Red-Black Tree | O(log n)   |
| `unordered_multiset` | ❌ No     | ✅ Yes       | Hash Table     | O(1)       |
| `map`                | ✅ Yes    | ❌ No        | Red-Black Tree | O(log n)   |
| `unordered_map`      | ❌ No     | ❌ No        | Hash Table     | O(1)       |
| `multimap`           | ✅ Yes    | ✅ Yes       | Red-Black Tree | O(log n)   |
| `unordered_multimap` | ❌ No     | ✅ Yes       | Hash Table     | O(1)       |

Let me know if you want this added to your main note!

--------------------

----------------------
## ✅ Shared Methods for All Multisets & Multimaps

| Method           | Description                                           | Multiset Example        | Multimap Example              |
| ---------------- | ----------------------------------------------------- | ----------------------- | ----------------------------- |
| `insert(x)`      | Inserts an element (even if duplicate)                | `ms.insert(5);`         | `mm.insert({"apple", 10});`   |
| `count(x)`       | Returns how many times `x` appears                    | `ms.count(5);`          | `mm.count("apple");`          |
| `find(x)`        | Returns iterator to **first** matching element        | `auto it = ms.find(5);` | `auto it = mm.find("apple");` |
| `equal_range(x)` | Returns pair of iterators: range of all matching keys | `ms.equal_range(5);`    | `mm.equal_range("apple");`    |
| `erase(x)`       | Erases **all entries** with key `x`                   | `ms.erase(5);`          | `mm.erase("apple");`          |
| `erase(it)`      | Erases by iterator (removes one at a time)            | `ms.erase(it);`         | `mm.erase(it);`               |
| `size()`         | Number of total elements                              | `ms.size();`            | `mm.size();`                  |
| `empty()`        | Returns `true` if container is empty                  | `ms.empty();`           | `mm.empty();`                 |
| `clear()`        | Erases all elements                                   | `ms.clear();`           | `mm.clear();`                 |

---

### 💡 `equal_range()` Example (for multimaps):

```cpp
multimap<string, int> mm;
mm.insert({"apple", 10});
mm.insert({"apple", 20});

auto range = mm.equal_range("apple");
for (auto it = range.first; it != range.second; ++it)
    cout << it->first << ": " << it->second << endl;
```

---

### 💡 `equal_range()` Example (for unordered\_multimap):

Let’s say we insert keys like: `2, 5, 6, 5, 7, 5, 9` into an `unordered_multiset`. When you call `equal_range(5)`, it returns a pair of iterators:

* `range.first` → points to the **first 5**
* `range.second` → points **just past the last 5**

So looping from `range.first` to `range.second` visits **all the 5s**, even if they're not stored contiguously in memory (because it's unordered).

Same idea works in `unordered_multimap` with key-value pairs:

```cpp
unordered_multimap<string, int> umm;
umm.insert({"apple", 10});
umm.insert({"apple", 20});

auto range = umm.equal_range("apple");
for (auto it = range.first; it != range.second; ++it)
    cout << it->first << ": " << it->second << endl;
```

---

### ❗️ Key Notes:

* `find()` only gives **the first match**.
* To get **all duplicates**, use `equal_range()`.
* `unordered_` variants behave the same, but no ordering.
