Alright Riyad 👍
I’ll teach you **LaTeX tables from absolute scratch**, slowly, clearly, and with intuition.
No slide-copying. You’ll *feel* what’s happening.

---

# 1️⃣ First idea: What is a LaTeX table?

A table in LaTeX has **two layers**:

1. **`tabular`** → draws rows & columns (MOST IMPORTANT)
2. **`table`** → floating container (caption, label, positioning)

👉 You can use **`tabular` alone** when learning.
👉 `table` is optional.

---

# 2️⃣ The simplest possible table (start here)

```latex
\begin{tabular}{c c c}
A & B & C \\
1 & 2 & 3 \\
4 & 5 & 6
\end{tabular}
```

### 🔍 Understand this line-by-line

#### `{c c c}`

This defines **columns**.

* `c` → center aligned column
* 3 times `c` → 3 columns

Think:

> “I want 3 vertical boxes, centered”

---

#### `&` → column separator

#### `\\` → end of row

So:

```latex
A & B & C \\   % row 1
1 & 2 & 3 \\   % row 2
```

---

# 3️⃣ Add borders (this is what people usually want)

```latex
\begin{tabular}{|c|c|c|}
\hline
A & B & C \\
\hline
1 & 2 & 3 \\
\hline
4 & 5 & 6 \\
\hline
\end{tabular}
```

### New things:

* `|` → vertical line
* `\hline` → horizontal line

📌 Visual rule:

* `|` → vertical borders
* `\hline` → horizontal borders

---

# 4️⃣ Column alignment types (VERY IMPORTANT)

| Symbol | Meaning       |
| ------ | ------------- |
| `l`    | left aligned  |
| `c`    | centered      |
| `r`    | right aligned |

Example:

```latex
\begin{tabular}{|l|c|r|}
\hline
Name & Age & GPA \\
\hline
Riyad & 23 & 3.75 \\
Nabi & 22 & 3.60 \\
\hline
\end{tabular}
```

---

# 5️⃣ Column headers (bold)

```latex
\textbf{Name} & \textbf{Age} & \textbf{GPA}
```

Full example:

```latex
\begin{tabular}{|c|c|c|}
\hline
\textbf{Name} & \textbf{Age} & \textbf{GPA} \\
\hline
Riyad & 23 & 3.75 \\
\hline
\end{tabular}
```

---

# 6️⃣ The `table` environment (caption + numbering)

Now we wrap `tabular` inside `table`.

```latex
\begin{table}[h]
\centering
\caption{Student Information}
\begin{tabular}{|c|c|c|}
\hline
Name & Age & GPA \\
\hline
Riyad & 23 & 3.75 \\
\hline
\end{tabular}
\end{table}
```

### New things:

* `[h]` → place table **here**
* `\centering` → center table
* `\caption{}` → table title

---

# 7️⃣ Common beginner mistakes (you MUST know)

### ❌ Forgetting `\\`

```latex
A & B & C   % WRONG
```

### ❌ Extra `&`

```latex
A & B & C & \\   % WRONG
```

Rule:

> Number of `&` = columns − 1

---

# 8️⃣ Merging columns (`\multicolumn`) — basic

```latex
\multicolumn{2}{c}{Total}
```

Example:

```latex
\begin{tabular}{|c|c|c|}
\hline
Name & Marks & Grade \\
\hline
Riyad & \multicolumn{2}{c|}{85 (A)} \\
\hline
\end{tabular}
```

Meaning:

> Merge 2 columns, center text, keep right border

---

# 9️⃣ Mental model (remember this forever)

Think of tables like this:

```
|  cell  |  cell  |  cell  |
    &        &        \\
```

* `&` → move right
* `\\` → go down

---

# 🔥 Your practice task (DO THIS)

Create a table with:

* 3 columns: **Course | Code | Grade**
* At least 3 rows
* Borders
* Caption

Write it, paste it here, and I’ll **correct it line by line** like a real teacher.

Next lesson (if you want):

* column width control (`p{}`)
* row spacing
* professional tables (`booktabs`)
* long tables (multiple pages)

Your move 💪
