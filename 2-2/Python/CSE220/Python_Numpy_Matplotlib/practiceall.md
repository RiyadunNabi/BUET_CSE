Here are the solutions for each of the four questions. I have separated them into distinct code blocks for clarity.

### **1. Signal Events Analysis**

This script parses the signal events, calculates the total duration and energy for each distinct label, and sorts the output as requested.

**Key Logic:**

* **Energy Formula:** 
* **Tie-breaking:** If total energies are equal, the lexicographically smaller label (alphabetical order) is chosen.

```python
# --- Solution for Question 1 ---

def analyze_signals():
    # Reading N (number of lines)
    try:
        n_input = input("Enter N (number of events): ")
        if not n_input: return # Handle empty input case
        N = int(n_input)
    except ValueError:
        print("Invalid input for N.")
        return

    events = []
    
    print(f"Enter {N} lines of events (label amp dur):")
    for _ in range(N):
        line = input().split()
        label = line[0]
        amp = int(line[1])
        dur = int(line[2])
        events.append((label, amp, dur))

    summary = {}

    # Process events
    for label, amp, dur in events:
        energy = (amp * amp) * dur
        
        if label not in summary:
            summary[label] = {'total_dur': 0, 'total_energy': 0}
        
        summary[label]['total_dur'] += dur
        summary[label]['total_energy'] += energy

    print("\nOutput:")
    # Print sorted by label
    sorted_labels = sorted(summary.keys())
    
    max_energy_label = None
    max_energy_val = -1

    for label in sorted_labels:
        stats = summary[label]
        print(f"{label} {stats['total_dur']} {stats['total_energy']}")
        
        # Check for max energy (strict > ensures lexicographical winner keeps spot in tie if sorted)
        # However, to be explicit about ties:
        current_energy = stats['total_energy']
        if current_energy > max_energy_val:
            max_energy_val = current_energy
            max_energy_label = label
        elif current_energy == max_energy_val:
            # If tie, choose the lexicographically smaller one
            if max_energy_label is None or label < max_energy_label:
                max_energy_label = label

    print(f"TOP {max_energy_label} {max_energy_val}")

# To run the function, uncomment the line below:
# analyze_signals()

```

---

### **2. Matrix Analysis (Numpy)**

This solution uses the `numpy` library to efficiently handle matrix operations for normalization, statistical summaries, and grade counting.

**Assumptions:**

* The `best_sub` and `top_student` indices correspond to the 0-based index of the columns/rows.

```python
# --- Solution for Question 2 ---
import numpy as np

def analyze_marks(A, max_marks, K):
    A = np.array(A)
    max_marks = np.array(max_marks)
    S, M = A.shape

    # 1. Normalize marks (Percentage Matrix P)
    # Avoid division by zero if max_marks has 0 (though unlikely in valid data)
    P = 100 * (A / max_marks) 
    print("Percentage Matrix (P):\n", np.round(P, 2))

    # 2. Student Summary
    # Average across columns (axis 1)
    student_avgs = np.mean(P, axis=1)
    # Index of max value across columns
    best_sub_indices = np.argmax(P, axis=1)
    
    print("\nStudent Summary:")
    for i in range(S):
        print(f"Student {i}: Avg = {student_avgs[i]:.2f}%, Best Subject Index = {best_sub_indices[i]}")

    # 3. Subject Summary
    # Average across rows (axis 0)
    sub_means = np.mean(P, axis=0)
    top_student_indices = np.argmax(P, axis=0)
    
    print("\nSubject Summary:")
    for j in range(M):
        print(f"Subject {j}: Mean = {sub_means[j]:.2f}%, Top Student Index = {top_student_indices[j]}")

    # 4. Best K Summary
    # Sort indices based on average, then reverse to get descending order
    sorted_indices = np.argsort(student_avgs)[::-1]
    top_k_indices = sorted_indices[:K]
    print(f"\nBest {K} Student IDs (Indices): {top_k_indices}")

    # 5. Unique Grade Count
    grade_counts = {'A': 0, 'B': 0, 'C': 0, 'D': 0}
    
    # Flatten the matrix to iterate easily or use vectorization
    flat_P = P.flatten()
    
    # Vectorized counting
    grade_counts['A'] = np.sum(flat_P >= 80)
    grade_counts['B'] = np.sum((flat_P >= 60) & (flat_P < 80))
    grade_counts['C'] = np.sum((flat_P >= 40) & (flat_P < 60))
    grade_counts['D'] = np.sum(flat_P < 40)
    
    print("\nUnique Grade Count:")
    for grade, count in grade_counts.items():
        print(f"{grade}: {count}")

# --- Test Data for Question 2 ---
# 5 Students, 3 Subjects
matrix_A = [
    [45, 80, 70],
    [90, 95, 85],
    [30, 40, 35],
    [60, 60, 60],
    [75, 85, 90]
]
max_marks_vec = [100, 100, 100]
K_val = 2

analyze_marks(matrix_A, max_marks_vec, K_val)

```

---

### **3. Student Class (OOP)**

This creates a class structure to manage student data. I have used the grading logic provided in Question 2's table (, etc.) as the grading logic was not explicitly defined in the OOP image but is contextually linked.

```python
# --- Solution for Question 3 ---

class Student:
    # Class Attribute
    university_name = "Tech University"

    def __init__(self, name, student_id):
        self.name = name
        self.student_id = student_id
        self.grades = []

    def add_grade(self, grade):
        self.grades.append(grade)

    def get_average(self):
        if not self.grades:
            return 0.0
        return sum(self.grades) / len(self.grades)

    def get_letter_grade(self):
        avg = self.get_average()
        if avg >= 80:
            return 'A'
        elif 60 <= avg < 80:
            return 'B'
        elif 40 <= avg < 60:
            return 'C'
        else:
            return 'D'

    def __str__(self):
        return (f"Student: {self.name} (ID: {self.student_id}) | "
                f"Avg: {self.get_average():.2f} | Grade: {self.get_letter_grade()}")

# --- Driver Code ---
# Creating 5 students
students_data = [
    ("Alice", 101),
    ("Bob", 102),
    ("Charlie", 103),
    ("David", 104),
    ("Eve", 105)
]

students_obj = []

# Mock grades for 3 subjects
import random
# Ensure reproducibility for testing
random.seed(42) 

print(f"University: {Student.university_name}\n")

for name, s_id in students_data:
    s = Student(name, s_id)
    # Adding 3 random grades between 30 and 100
    for _ in range(3):
        s.add_grade(random.randint(30, 100))
    students_obj.append(s)
    
    # Testing methods
    print(f"Input for {name}: {s.grades}")
    print(s)  # Calls __str__
    print("-" * 30)

```

---

### **4. Product Sales Visualization**

This uses `matplotlib` to generate the 4 specific subplots requested.

```python
# --- Solution for Question 4 ---
import numpy as np
import matplotlib.pyplot as plt

# 1. Data Setup
months = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'Jun', 'Jul', 'Aug', 'Sep', 'Oct', 'Nov', 'Dec']
product_a = np.array([23, 25, 28, 30, 35, 38, 42, 45, 48, 50, 53, 55])
product_b = np.array([30, 32, 31, 33, 35, 37, 39, 41, 43, 45, 47, 50])
product_c = np.array([15, 18, 22, 25, 28, 32, 35, 38, 42, 45, 48, 52])

# Initialize Figure
fig, axes = plt.subplots(2, 2, figsize=(14, 10))
fig.suptitle("2024 Product Sales Analysis", fontsize=16)

# --- Plot 1 (Top-Left): Line Plot ---
ax1 = axes[0, 0]
ax1.plot(months, product_a, color='blue', linestyle='-', label='Product A')
ax1.plot(months, product_b, color='green', linestyle='--', label='Product B')
ax1.plot(months, product_c, color='red', linestyle=':', label='Product C')
ax1.set_title("Monthly Sales Trends 2024")
ax1.set_xlabel("Month")
ax1.set_ylabel("Sales (in thousands)")
ax1.legend()
ax1.grid(True)

# --- Plot 2 (Top-Right): Bar Chart (December Only) ---
ax2 = axes[0, 1]
dec_sales = [product_a[-1], product_b[-1], product_c[-1]]
products = ['Product A', 'Product B', 'Product C']
colors = ['blue', 'green', 'red']
ax2.bar(products, dec_sales, color=colors)
ax2.set_title("December Sales Comparison")
ax2.set_xlabel("Product")
ax2.set_ylabel("Sales (in thousands)")
ax2.grid(axis='y')

# --- Plot 3 (Bottom-Left): Scatter Plot (Product A) ---
ax3 = axes[1, 0]
ax3.scatter(months, product_a, color='blue', s=50)
ax3.set_title("Product A Sales Distribution")
ax3.set_xlabel("Month")
ax3.set_ylabel("Sales (in thousands)")
ax3.grid(True)

# --- Plot 4 (Bottom-Right): Stacked Bar Chart (Quarterly) ---
ax4 = axes[1, 1]

# Calculate Quarterly Sums
# Q1: 0-3, Q2: 3-6, Q3: 6-9, Q4: 9-12
q_indices = [(0, 3), (3, 6), (6, 9), (9, 12)]
quarters = ['Q1', 'Q2', 'Q3', 'Q4']

q_a = [np.sum(product_a[i:j]) for i, j in q_indices]
q_b = [np.sum(product_b[i:j]) for i, j in q_indices]
q_c = [np.sum(product_c[i:j]) for i, j in q_indices]

# Plotting Stacked Bars
# The 'bottom' parameter creates the stack
ax4.bar(quarters, q_a, label='Product A', color='blue')
ax4.bar(quarters, q_b, bottom=q_a, label='Product B', color='green')
# Bottom for C is sum of A and B
q_ab_sum = np.add(q_a, q_b) 
ax4.bar(quarters, q_c, bottom=q_ab_sum, label='Product C', color='red')

ax4.set_title("Quarterly Sales (Stacked)")
ax4.set_xlabel("Quarter")
ax4.set_ylabel("Total Sales (in thousands)")
ax4.legend()
ax4.grid(axis='y')

plt.tight_layout()
plt.show()

```