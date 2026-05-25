
---

# ✅ C++ Sets – Quick Revision Guide

---

## 🔹 `unordered_set` — Hash-Based Set

### 🧠 What is it?

* Stores **unique** items with **no order**
* Backed by a **hash table**
* **Fastest** for insert/search/delete → **O(1)** on average

### 🛠️ Syntax:

```cpp
#include <unordered_set>
using namespace std;

unordered_set<int> s;
```

---

## 🔹 `set` — Tree-Based Set

### 🧠 What is it?

* Stores **unique** items in **sorted order** (default: ascending)
* Backed by a **balanced BST (Red-Black Tree)**
* Slower than `unordered_set`, but ordered → **O(log n)**

### 🛠️ Syntax:

```cpp
#include <set>
using namespace std;

set<int> s;
```

---

## 🔢 Method Comparison Table

| Method            | `unordered_set`   | `set`                   | Example                                            | Description                         |
| ----------------- | ----------------- | ----------------------- | -------------------------------------------------- | ----------------------------------- |
| `insert(x)`       | ✅ Yes             | ✅ Yes                   | `s.insert(10);`                                    | Adds `x` if not already present     |
| `count(x)`        | ✅ Yes             | ✅ Yes                   | `s.count(10);`                                     | Returns `1` if `x` exists, else `0` |
| `find(x)`         | ✅ Yes (O(1) avg)  | ✅ Yes (O(log n))        | `auto it = s.find(10);`                            | Returns iterator to `x` or `end()`  |
| `erase(x)`        | ✅ Yes             | ✅ Yes                   | `s.erase(10);`                                     | Removes `x` from the set if exists  |
| `size()`          | ✅ Yes             | ✅ Yes                   | `s.size();`                                        | Returns total number of elements    |
| `empty()`         | ✅ Yes             | ✅ Yes                   | `s.empty();`                                       | Returns `true` if the set is empty  |
| `clear()`         | ✅ Yes             | ✅ Yes                   | `s.clear();`                                       | Clears all elements from the set    |
| `begin()/end()`   | ✅ Yes (unordered) | ✅ Yes (ascending order) | `for (auto x : s)`                                 | Loop through all elements           |
| `rbegin()/rend()` | ❌ No              | ✅ Yes                   | `for (auto it = s.rbegin(); it != s.rend(); ++it)` | Reverse loop over elements          |

---

### 🌀 Custom Order for `set`:

```cpp
set<int, greater<int>> s;  // descending order
```

---

## 🔁 Summary Table

| Feature             | `unordered_set` | `set`                  |
| ------------------- | --------------- | ---------------------- |
| Order of elements   | ❌ No            | ✅ Yes (ascending)      |
| Internal structure  | Hash table      | Red-Black Tree (BST)   |
| Time complexity     | O(1) avg        | O(log n)               |
| Duplicates allowed? | ❌ No            | ❌ No                   |
| Use case            | Fast lookup     | Sorted unique elements |

---
---
---
---
---
---
---
---
---

# ✅ C++ Maps – Quick Revision Guide

---

## 🔹 `unordered_map` — Hash-Based Map

### 🧠 What is it?

* Stores **key-value pairs** with **no order**
* Keys must be **unique**
* Backed by a **hash table**
* **Very fast** for insert/search/delete → **O(1)** on average

### 🛠️ Syntax:

```cpp
#include <unordered_map>
using namespace std;

unordered_map<string, int> m;
m["apple"] = 10;
auto val = m["apple"];      // Access value
cout << m.at("apple") << endl; // Safer access (throws if not found)

// ❌ Incorrect:
// auto key = m.first; // ❌ m is not a pair
// auto value = m.second;

// ✅ Correct way:
for (auto it : m) {
    auto key = it.first;
    auto value = it.second;
}
```

---

## 🔹 `map` — Tree-Based Map

### 🧠 What is it?

* Stores **key-value pairs** in **sorted order of keys** (ascending by default)
* Keys must be **unique**
* Backed by a **balanced BST (Red-Black Tree)**
* Slower than `unordered_map`, but **keeps keys ordered** → **O(log n)**

### 🛠️ Syntax:

```cpp
#include <map>
using namespace std;

map<string, int> m;
m["banana"] = 5;
auto val = m["banana"];
cout << m.at("banana") << endl;

// ❌ Incorrect:
// auto key = m.first;
// auto value = m.second;

// ✅ Correct way:
for (auto it : m) {
    auto key = it.first;
    auto value = it.second;
}
```

---

## 🧱 Accessing Key-Value Pairs (`first`, `second`)

When iterating, you get a `pair<const Key, Value>`. Use:

```cpp
for (auto it : m) {
    cout << it.first << " → " << it.second << endl;
}
```

Or using iterator:

```cpp
for (auto it = m.begin(); it != m.end(); ++it) {
    cout << it->first << " = " << it->second << endl;
}
```

⚠️ **Common Confusion:** You can't do `m.first` or `m.second` directly because `m` is not a pair — it's a container (map). Only its **elements** are pairs.

---

## 🔢 Method Comparison Table

| Method            | `unordered_map`   | `map`                   | Example                                            | Description                           |
| ----------------- | ----------------- | ----------------------- | -------------------------------------------------- | ------------------------------------- |
| `insert({k,v})`   | ✅ Yes             | ✅ Yes                   | `m.insert({"apple", 10});`                         | Adds a key-value pair                 |
| `m[k] = v`        | ✅ Yes             | ✅ Yes                   | `m["apple"] = 10;`                                 | Inserts or updates value for key      |
| `count(k)`        | ✅ Yes             | ✅ Yes                   | `m.count("apple")`                                 | Returns 1 if key exists, else 0       |
| `find(k)`         | ✅ Yes (O(1))      | ✅ Yes (O(log n))        | `auto it = m.find("apple");`                       | Returns iterator to pair or `m.end()` |
| `erase(k)`        | ✅ Yes             | ✅ Yes                   | `m.erase("apple");`                                | Removes pair with key                 |
| `size()`          | ✅ Yes             | ✅ Yes                   | `m.size();`                                        | Number of key-value pairs             |
| `empty()`         | ✅ Yes             | ✅ Yes                   | `m.empty();`                                       | Returns `true` if map is empty        |
| `clear()`         | ✅ Yes             | ✅ Yes                   | `m.clear();`                                       | Removes all entries                   |
| `begin()/end()`   | ✅ Yes (unordered) | ✅ Yes (ascending order) | `for (auto p : m)`                                 | Loop through key-value pairs          |
| `rbegin()/rend()` | ❌ No              | ✅ Yes                   | `for (auto it = m.rbegin(); it != m.rend(); ++it)` | Reverse loop (only in ordered map)    |

---

## 🔁 Summary Table

| Feature            | `unordered_map` | `map`                 |
| ------------------ | --------------- | --------------------- |
| Key Order          | ❌ No            | ✅ Yes (ascending)     |
| Internal Structure | Hash table      | Red-Black Tree (BST)  |
| Time Complexity    | O(1) avg        | O(log n)              |
| Duplicate Keys?    | ❌ No            | ❌ No                  |
| Use Case           | Fast key lookup | Ordered key traversal |

---

## 🧩 Why Use `map`/`unordered_map` Over `set`?

**`set`** only stores **keys**, but **`map`** stores **(key → value)** relationships.
If you want to associate information with a key — like a phone number with a name — use a map.

---

## 🧠 When to Use What?

| Scenario                                    | Use                       |
| ------------------------------------------- | ------------------------- |
| Fast lookup by key (order doesn't matter)   | ✅ `unordered_map`         |
| Need keys in sorted order                   | ✅ `map`                   |
| Only need to store unique items (no values) | ✅ `set` / `unordered_set` |
| Need reverse iteration or ordered traversal | ✅ `map` or `set`          |

---

## 🧪 Runtime Use Case Comparison (from your files):

| Problem                                     | Structure Used  | Why                                  | Complexity |    |   |    |   |    |   |
| ------------------------------------------- | --------------- | ------------------------------------ | ---------- | -- | - | -- | - | -- | - |
| Store/search citizen info by name/NID/phone | `unordered_map` | Fast lookup with key-value data      | O(         | s1 | + | s2 | + | s3 | ) |
| Count k-mer frequency in DNA sequence       | `unordered_map` | Fast frequency map                   | O(kn)      |    |   |    |   |    |   |
| Detect reverse-complement DNA pairs         | `unordered_map` | Store DNA → check reverse complement | O(ln)      |    |   |    |   |    |   |

---
---
---
---
Yes, you **can perform all tasks without explicitly using** `insert({k, v})`, by using the syntax `m[k] = v;` — **but only in certain contexts**, and it's important to understand how they differ:

---

### ✅ What does `m.insert({k, v})` do?

* **Only inserts** the key-value pair if the key doesn't exist.
* **Does not update** the value if key already exists.
* Returns a flag indicating if the insert was successful.

**Example:**

```cpp
map<string, int> m;
m.insert({"apple", 10});  // Inserts
m.insert({"apple", 20});  // Fails silently, does not update
```

---

### ✅ What does `m[k] = v` do?

* **Always sets** the value for key `k` to `v`.
* If `k` **doesn’t exist**, it inserts it.
* If `k` **does exist**, it **updates** the value.

**Example:**

```cpp
map<string, int> m;
m["apple"] = 10;  // Inserts
m["apple"] = 20;  // Updates
```

---

### 🔍 In your project context

From the files, especially in `HashTable.h`, your own `insert()` function:

```cpp
void insert(string &key, int value)
```

Is customized to your hash table logic (handling collisions, strategies, etc.). If you **skip calling this function**, then things like:

* Collision counting
* Probing for open addressing
* BST handling in chaining

**won't happen correctly.**

---

### 🔴 So, should you avoid `insert()`?

**No — in your hash table implementation (`HashTable` class), you must use the `insert()` function you wrote.** You **cannot replace** it with `m[k] = v;` because:

* `m` is not a `map`, it’s a custom hash table.
* Your `insert()` does more than just adding values — it ensures the logic of hash functions, probing, tree balancing, and collision handling works correctly.

---

### ✅ Summary:

| Syntax            | Works in `std::map`? | Works in your custom `HashTable`? | Inserts new key     | Updates value          |
| ----------------- | -------------------- | --------------------------------- | ------------------- | ---------------------- |
| `m.insert({k,v})` | ✅ Yes                | ❌ No (unless implemented)         | ✅ Yes (only if new) | ❌ No                   |
| `m[k] = v;`       | ✅ Yes                | ❌ No (unless you overload `[]`)   | ✅ Yes               | ✅ Yes                  |
| `ht.insert(k, v)` | ❌ No                 | ✅ Yes (your logic)                | ✅ Yes               | ❌/✅ (depends on logic) |

If you're using your own `HashTable` class, you must call its `insert()` method to ensure all behavior works correctly. Let me know if you'd like help adding `operator[]` to your custom class for more intuitive syntax.

---
---
---
---
# ⁉️ So can I say all of them are example of hash? ❓🤔

Good question! The short answer is:

**Not all of them are examples of hashing.**

Let’s clarify:

---

### ✅ **Hash-Based Containers (use hashing internally):**

These are built on **hash tables**, so yes, they are examples of **hash-based structures**.

* `unordered_map` ✅
* `unordered_set` ✅
* `unordered_multimap` ✅
* `unordered_multiset` ✅

They use **a hash function** to map keys to positions in memory (buckets), so operations like `insert`, `find`, and `erase` are **O(1)** on average.

---

### ❌ **Tree-Based Containers (not hash-based):**

These are built on **balanced binary search trees** (like Red-Black Trees), **not** on hash tables.

* `map` ❌
* `set` ❌
* `multimap` ❌
* `multiset` ❌

They keep elements **sorted**, and operations take **O(log n)** time.

---

### 🧠 Summary:

| Container Type  | Hash-Based? | Internals Used       |
| --------------- | ----------- | -------------------- |
| `unordered_map` | ✅ Yes       | Hash Table           |
| `unordered_set` | ✅ Yes       | Hash Table           |
| `map`           | ❌ No        | Red-Black Tree (BST) |
| `set`           | ❌ No        | Red-Black Tree (BST) |

So you can say:

> "Only the **unordered\_**\* containers are examples of hashing-based data structures."

Let me know if you want a quick diagram showing this visually!



---

