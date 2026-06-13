Great! Since you've already practiced the problems in the uploaded files, here are **3 fresh and intuitive hashing-based problems** for extra practice, along with their **solutions**. These are **not from your materials**, but still follow similar concepts so you can sharpen your skills effectively.

---

### 🧩 **Problem 1: Detect First Duplicate Word**

**Problem**:
Given a list of `n` strings (words), find the **first word** that appears **more than once** (i.e., its first duplicate), and output it. If no duplicate exists, print `"No duplicate"`.

**Example Input**:

```
5  
code  
hash  
array  
hash  
tree  
```

**Expected Output**:

```
hash
```

**Solution Intuition**:
Use a hash set to keep track of seen words.

**C++ Code**:

```cpp
#include <iostream>
#include <unordered_set>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_set<string> seen;
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        if (seen.count(word)) {
            cout << word << endl;
            return 0;
        }
        seen.insert(word);
    }
    cout << "No duplicate" << endl;
    return 0;
}
```

---

### 🧩 **Problem 2: Group Anagrams Together**

**Problem**:
You are given a list of strings. Group all anagrams together. Anagrams have the same letters but in different order (like `"listen"` and `"silent"`).

**Example Input**:

```
6  
listen  
silent  
code  
node  
deno  
edoc  
```

**Expected Output (any order of groups is fine)**:

```
listen silent  
code edoc  
node deno
```

**Solution Intuition**:
Use a hash map where key is the sorted version of string, value is list of anagrams.

**C++ Code**:

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    unordered_map<string, vector<string>> anagram_groups;
    for (int i = 0; i < n; ++i) {
        string word;
        cin >> word;
        string sorted_word = word;
        sort(sorted_word.begin(), sorted_word.end());
        anagram_groups[sorted_word].push_back(word);
    }
    for (auto &group : anagram_groups) {
        for (string &word : group.second) {
            cout << word << " ";
        }
        cout << endl;
    }
    return 0;
}
```

---

### 🧩 **Problem 3: Longest Substring Without Repeating Characters**

**Problem**:
Given a string `s`, find the length of the longest substring without repeating characters.

**Example Input**:

```
abcabcbb
```

**Expected Output**:

```
3
```

**Explanation**: `"abc"` is the longest substring without duplicates.

**Solution Intuition**:
Sliding window + hash map to store last seen indices.

**C++ Code**:

```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    unordered_map<char, int> last_seen;
    int max_len = 0, start = 0;
    for (int i = 0; i < s.length(); ++i) {
        if (last_seen.count(s[i]) && last_seen[s[i]] >= start) {
            start = last_seen[s[i]] + 1;
        }
        last_seen[s[i]] = i;
        max_len = max(max_len, i - start + 1);
    }
    cout << max_len << endl;
    return 0;
}
```

---

Let me know if you'd like me to quiz you with variants or help you implement these using custom hash functions. Happy practicing! 💡
---
---
---
🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯🦯
---
# Level UP
---

Here are **3 more challenging hashing problems**, designed to fit into a 45-minute window but push you beyond basic practice. Each comes with an intuitive explanation and a ready-to-go C++ solution sketch.

---

## 1. LFU Cache (Least Frequently Used)

**Problem**
Design a cache that supports `get(key)` and `put(key,value)` in O(1), and when capacity is reached, evicts the **least frequently used** key. If there’s a tie, evict the **least recently used** among those.

**Why It’s Tricky**
You need to track both **frequency** and **recency** in O(1). A naive solution scans to find the LFU entry—too slow.

### Intuition

* **Hash map** from key → (value, freq, iterator into freq-list).
* **Hash map** from freq → doubly-linked list of keys at that frequency (most recent at front).
* Maintain a **minFreq** pointer.
* On `get` or existing `put`, remove key from its current freq list, increment freq, insert at front of new freq list.
* On eviction, pop the back of the list at `minFreq`.

### C++ Sketch

```cpp
#include <unordered_map>
#include <list>
using namespace std;

class LFUCache {
    int capacity, minFreq;
    // key → (value, freq)
    unordered_map<int, pair<int,int>> kv;
    // key → iterator in freqList[freq]
    unordered_map<int, list<int>::iterator> iters;
    // freq → list of keys (most recent at front)
    unordered_map<int, list<int>> freqList;
    
public:
    LFUCache(int cap): capacity(cap), minFreq(0) {}

    int get(int key) {
        if (!kv.count(key)) return -1;
        // retrieve value and freq
        auto [val, f] = kv[key];
        // remove from old freq list
        freqList[f].erase(iters[key]);
        if (freqList[f].empty()) {
            freqList.erase(f);
            if (minFreq == f) minFreq++;
        }
        // add to new freq list
        kv[key].second++;
        f++;
        freqList[f].push_front(key);
        iters[key] = freqList[f].begin();
        return val;
    }

    void put(int key, int value) {
        if (capacity <= 0) return;
        if (get(key) != -1) {
            kv[key].first = value;
            return;
        }
        if ((int)kv.size() >= capacity) {
            // evict least freq & least recent
            int evict = freqList[minFreq].back();
            freqList[minFreq].pop_back();
            kv.erase(evict);
            iters.erase(evict);
            if (freqList[minFreq].empty()) freqList.erase(minFreq);
        }
        // insert new key with freq=1
        kv[key] = {value, 1};
        freqList[1].push_front(key);
        iters[key] = freqList[1].begin();
        minFreq = 1;
    }
};
```

---

## 2. Substring with Concatenation of All Words

**Problem**
Given string `s` and an array of words `words[]` (all same length), find **all starting indices** in `s` of substrings formed by **concatenating each word exactly once** in any order, **without intervening characters**.

Example:

```
s = "barfoothefoobarman"
words = ["foo","bar"]
→ [0,9]   // "barfoo" at 0, "foobar" at 9
```

**Why It’s Tricky**
Sliding window of fixed total length, but words can be in any order; you must maintain counts of how many times each word appears in the window.

### Intuition

* Let `wordLen = words[0].length()`, `totalLen = wordLen * words.size()`.
* Build a **target map** of word → required count.
* For each `offset` in `[0…wordLen-1]`, slide a window stepping by `wordLen`:

  * Extract the next chunk of length `wordLen`, update a **window map** of seen words.
  * If a word’s count exceeds target, **shrink** the window from the left, removing one word at a time.
  * Whenever window size == `totalLen`, record the left index.

### C++ Sketch

```cpp
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

vector<int> findSubstring(string s, vector<string>& words) {
    vector<int> res;
    int n = s.size(), k = words.size();
    if (!n || !k) return res;
    int wl = words[0].size(), total = wl * k;
    unordered_map<string,int> target;
    for (auto &w : words) target[w]++;

    for (int off = 0; off < wl; ++off) {
        int left = off, count = 0;
        unordered_map<string,int> window;
        for (int j = off; j + wl <= n; j += wl) {
            string piece = s.substr(j, wl);
            if (target.count(piece)) {
                window[piece]++;
                count++;
                // Too many of this word → shrink
                while (window[piece] > target[piece]) {
                    string leftWord = s.substr(left, wl);
                    window[leftWord]--;
                    left += wl;
                    count--;
                }
                if (count == k) {
                    res.push_back(left);
                    // move left one word to look for next
                    string leftWord = s.substr(left, wl);
                    window[leftWord]--;
                    left += wl;
                    count--;
                }
            } else {
                // reset window
                window.clear();
                count = 0;
                left = j + wl;
            }
        }
    }
    return res;
}
```

---

## 3. Count Distinct Elements in Every Window of Size k

**Problem**
Given an array `arr[]` of size `n` and an integer `k`, for **every** contiguous subarray (window) of size `k`, count the number of **distinct** elements. Return a list of these counts.

**Example**:

```
arr = [1, 2, 1, 3, 4, 2, 3], k = 4  
Windows: [1,2,1,3]→3, [2,1,3,4]→4, [1,3,4,2]→4, [3,4,2,3]→3  
Answer = [3,4,4,3]
```

**Why It’s Tricky**
You must slide the window in O(1) or amortized O(1) per move, updating distinct counts efficiently.

### Intuition

* Use a **hash map** `countMap` of element → its count within the current window.
* Start by processing the first `k` elements, counting distinct as `countMap.size()`.
* Then for each slide:

  * **Remove** the element exiting the window: decrement its count; if it drops to 0, erase it → distinct–.
  * **Add** the new entering element: if it wasn’t present, distinct++; then increment its count.
* Append the new `countMap.size()` to the result each time.

### C++ Sketch

```cpp
#include <vector>
#include <unordered_map>
using namespace std;

vector<int> countDistinctInWindow(vector<int>& arr, int k) {
    vector<int> res;
    unordered_map<int,int> cnt;
    int n = arr.size();
    // First window
    for (int i = 0; i < k; ++i) cnt[arr[i]]++;
    res.push_back(cnt.size());
    // Slide
    for (int i = k; i < n; ++i) {
        // remove arr[i-k]
        if (--cnt[arr[i-k]] == 0) cnt.erase(arr[i-k]);
        // add arr[i]
        cnt[arr[i]]++;
        res.push_back(cnt.size());
    }
    return res;
}
```

---

### Tips for a 45-Min Slot

1. **Read & Plan (5 – 7 min):** Parse input constraints, choose appropriate data structures.
2. **Write Core Logic (25 – 30 min):** Focus on the hash-based data structures—maps, sets, lists.
3. **Test & Edge Cases (8 – 10 min):** Small custom tests, empty inputs, all unique/all same cases.

Good luck leveling up your hashing game! Let me know if you need deeper walkthroughs or more variations.
