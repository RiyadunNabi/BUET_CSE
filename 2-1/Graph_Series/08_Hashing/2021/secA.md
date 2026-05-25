### Problem A Explanation (from "Online 4 (Hashing) A.pdf"):

#### 🧬 **What’s the task?**

You are given a list of DNA sequences, and your goal is to **find and print all the pairs** of sequences that are **reverse complements** of each other.

---

#### 🔄 **What is a reverse complement?**

Think of it in two steps:

1. **Complement** each letter in the DNA:

   * A ↔ T
   * C ↔ G

   For example:

   ```
   Original:   A  T  G  C
   Complement: T  A  C  G
   ```

2. **Reverse** that complemented string.

   So, if original is `ATGC`:

   * Complement → `TACG`
   * Reverse → `GCAT`

   ✅ `GCAT` is the **reverse complement** of `ATGC`.

---

#### 🧠 **What do you need to do?**

Given `n` DNA sequences (each of length `l`), **find and print all pairs** where one sequence is the reverse complement of the other.

* **Each pair** should be printed **once**.
* Complexity must be **O(l × n)** — so your solution should be efficient.

---

#### 🧪 **Sample Example:**

Input:

```
5 4
ATGC
GCAT
TACG
CGTA
TTAA
```

Here:

* `ATGC` → reverse complement is `GCAT` → ✅ a pair.
* `TACG` → reverse complement is `CGTA` → ✅ another pair.
* `TTAA` → reverse complement is also `TTAA` → ✅ valid if exact match.

Output:

```
ATGC GCAT
TACG CGTA
```

(Note: Even though `TTAA` is its own reverse complement, it appears only once — maybe this one was excluded in output depending on the implementation.)

---

#### 🚀 **How to implement? (Intuition)**

1. Create a function to get the reverse complement of a DNA string.
2. Use a dictionary (hash map) to store all sequences.
3. For each sequence, compute its reverse complement and check if it already exists in the dictionary.

   * If yes → print the pair.
   * Be careful not to print the same pair twice.

Let me know if you want the actual code or visual walkthrough!
