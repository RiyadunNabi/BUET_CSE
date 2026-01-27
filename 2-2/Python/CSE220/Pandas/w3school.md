# Pandas Series Reference

## Creating a Series from a List

```python
import pandas as pd

a = [1, 7, 2]

myvar = pd.Series(a)

print(myvar)

# Output:
# 0    1
# 1    7
# 2    2
# dtype: int64

```

## Accessing Values by Default Index

```python
# First value has index 0
print(myvar[0])

# Output:
# 1

```

## Creating a Series with Custom Labels

```python
import pandas as pd

a = [1, 7, 2]

# Setting custom index labels "x", "y", "z"
myvar = pd.Series(a, index = ["x", "y", "z"])

print(myvar)

# Output:
# x    1
# y    7
# z    2
# dtype: int64

```

## Accessing Values by Custom Label

```python
print(myvar["y"])

# Output:
# 7

```

## Creating a Series from a Dictionary

```python
import pandas as pd

calories = {"day1": 420, "day2": 380, "day3": 390}

# Keys become the labels
myvar = pd.Series(calories)

print(myvar)

# Output:
# day1    420
# day2    380
# day3    390
# dtype: int64

```

## Selecting Specific Items from a Dictionary

```python
import pandas as pd

calories = {"day1": 420, "day2": 380, "day3": 390}

# Use index argument to select specific keys
myvar = pd.Series(calories, index = ["day1", "day2"])

print(myvar)

# Output:
# day1    420
# day2    380
# dtype: int64

```

## DataFrames vs Series

```python
import pandas as pd

data = {
  "calories": [420, 380, 390],
  "duration": [50, 40, 45]
}

# DataFrame is multi-dimensional (whole table), Series is 1D (column)
myvar = pd.DataFrame(data)

print(myvar)

# Output:
#    calories  duration
# 0       420        50
# 1       380        40
# 2       390        45

```

Would you like me to process the **DataFrames** section next?

---


---
# 2. Pandas DataFrames

## 2.1 Creating a DataFrame

A DataFrame is a 2-dimensional data structure, like a table with rows and columns.

```python
import pandas as pd

data = {
  "calories": [420, 380, 390],
  "duration": [50, 40, 45]
}

# load data into a DataFrame object:
df = pd.DataFrame(data)

print(df)

# Output:
#    calories  duration
# 0       420        50
# 1       380        40
# 2       390        45

```

## 2.2 Locate Row (loc)

Pandas uses the `loc` attribute to return one or more specified rows.

### 2.2.1 Return a Single Row (Series)

```python
# refer to the row index:
print(df.loc[0])

# Output:
# calories    420
# duration     50
# Name: 0, dtype: int64

```

### 2.2.2 Return Multiple Rows (DataFrame)

```python
# use a list of indexes:
print(df.loc[[0, 1]])

# Output:
#    calories  duration
# 0       420        50
# 1       380        40

```

## 2.3 Named Indexes

You can name your own indexes using the `index` argument.

```python
import pandas as pd

data = {
  "calories": [420, 380, 390],
  "duration": [50, 40, 45]
}

# Add a list of names to give each row a name
df = pd.DataFrame(data, index = ["day1", "day2", "day3"])

print(df)

# Output:
#       calories  duration
# day1       420        50
# day2       380        40
# day3       390        45

```

## 2.4 Locate Named Indexes

Use the named index in the `loc` attribute to return specific rows.

```python
# refer to the named index:
print(df.loc["day2"])

# Output:
# calories    380
# duration     40
# Name: day2, dtype: int64

```

## 2.5 Load Files Into a DataFrame

```python
import pandas as pd

# Load a comma separated file (CSV file) into a DataFrame
df = pd.read_csv('data.csv')

print(df)

```

Would you like me to process the **Read CSV** section next?

---
# 3. Pandas Read CSV

## 3.1 Reading CSV Files

CSV (Comma Separated Files) is a common format for storing big data sets.

```python
import pandas as pd

# Load the CSV into a DataFrame
df = pd.read_csv('data.csv')

# Use to_string() to print the entire DataFrame
print(df.to_string()) 

```

## 3.2 Default Printing (Large DataFrames)

If a DataFrame contains many rows, Pandas will only return the headers and the first and last 5 rows.

```python
import pandas as pd

df = pd.read_csv('data.csv')

print(df) 

```

## 3.3 Managing `max_rows`

The number of rows returned is defined by Pandas option settings (default is often 60).

### 3.3.1 Check Maximum Rows

```python
import pandas as pd

print(pd.options.display.max_rows) 

# Output (example):
# 60

```

### 3.3.2 Increase Maximum Rows

You can change the setting to display more rows (e.g., to print the entire DataFrame).

```python
import pandas as pd

# Increase the maximum number of rows to display
pd.options.display.max_rows = 9999

df = pd.read_csv('data.csv')

print(df) 

```

Would you like me to process the **Read JSON** section next?

---
# 4. Pandas Read JSON

## 4.1 Read JSON Files

Big data sets are often stored as JSON. JSON is plain text, but has the format of an object.

```python
import pandas as pd

# Load the JSON file into a DataFrame
df = pd.read_json('data.json')

# use to_string() to print the entire DataFrame
print(df.to_string()) 

```

## 4.2 Dictionary as JSON

If your JSON code is not in a file, but in a Python Dictionary, you can load it into a DataFrame directly.

```python
import pandas as pd

data = {
  "Duration":{
    "0":60,
    "1":60,
    "2":60,
    "3":45,
    "4":45,
    "5":60
  },
  "Pulse":{
    "0":110,
    "1":117,
    "2":103,
    "3":109,
    "4":117,
    "5":102
  },
  "Maxpulse":{
    "0":130,
    "1":145,
    "2":135,
    "3":175,
    "4":148,
    "5":127
  },
  "Calories":{
    "0":409,
    "1":479,
    "2":340,
    "3":282,
    "4":406,
    "5":300
  }
}

df = pd.DataFrame(data)

print(df) 

# Output:
#    Duration  Pulse  Maxpulse  Calories
# 0        60    110       130       409
# 1        60    117       145       479
# 2        60    103       135       340
# 3        45    109       175       282
# 4        45    117       148       406
# 5        60    102       127       300

```

Would you like me to process the **Analyzing Data** section next?

---
# 5. Pandas Analyzing Data

## 5.1 Viewing the Data (Head)

The `head()` method returns the headers and a specified number of rows, starting from the top.

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Get the first 10 rows of the DataFrame
print(df.head(10))

# Note: if no number is specified, head() returns the top 5 rows.
print(df.head()) 

```

## 5.2 Viewing the Data (Tail)

The `tail()` method returns the headers and a specified number of rows, starting from the bottom.

```python
# Get the last 5 rows of the DataFrame
print(df.tail()) 

```

## 5.3 Info About the Data

The `info()` method gives you more information about the data set, such as the number of rows/columns, data types, and memory usage.

```python
print(df.info()) 

# Output:
# <class 'pandas.core.frame.DataFrame'>
# RangeIndex: 169 entries, 0 to 168
# Data columns (total 4 columns):
#  #   Column    Non-Null Count  Dtype  
# ---  ------    --------------  -----  
#  0   Duration  169 non-null    int64  
#  1   Pulse     169 non-null    int64  
#  2   Maxpulse  169 non-null    int64  
#  3   Calories  164 non-null    float64
# dtypes: float64(1), int64(3)
# memory usage: 5.4 KB
# None

```

Would you like me to process the **Cleaning Data** section next?

---
# 6. Pandas Cleaning Data

The table below contains the raw data we will be analyzing in the upcoming sections. Please review the values for Duration, Date, Pulse, Maxpulse, and Calories.

---

| Index | Duration | Date | Pulse | Maxpulse | Calories |
| --- | --- | --- | --- | --- | --- |
| **0** | 60 | 2020/12/01 | 110 | 130 | 409.1 |
| **1** | 60 | 2020/12/02 | 117 | 145 | 479.0 |
| **2** | 60 | 2020/12/03 | 103 | 135 | 340.0 |
| **3** | 45 | 2020/12/04 | 109 | 175 | 282.4 |
| **4** | 45 | 2020/12/05 | 117 | 148 | 406.0 |
| **5** | 60 | 2020/12/06 | 102 | 127 | 300.0 |
| **6** | 60 | 2020/12/07 | 110 | 136 | 374.0 |
| **7** | 450 | 2020/12/08 | 104 | 134 | 253.3 |
| **8** | 30 | 2020/12/09 | 109 | 133 | 195.1 |
| **9** | 60 | 2020/12/10 | 98 | 124 | 269.0 |
| **10** | 60 | 2020/12/11 | 103 | 147 | 329.3 |
| **11** | 60 | 2020/12/12 | 100 | 120 | 250.7 |
| **12** | 60 | 2020/12/12 | 100 | 120 | 250.7 |
| **13** | 60 | 2020/12/13 | 106 | 128 | 345.3 |
| **14** | 60 | 2020/12/14 | 104 | 132 | 379.3 |
| **15** | 60 | 2020/12/15 | 98 | 123 | 275.0 |
| **16** | 60 | 2020/12/16 | 98 | 120 | 215.2 |
| **17** | 60 | 2020/12/17 | 100 | 120 | 300.0 |
| **18** | 45 | 2020/12/18 | 90 | 112 | **NaN** |
| **19** | 60 | 2020/12/19 | 103 | 123 | 323.0 |
| **20** | 45 | 2020/12/20 | 97 | 125 | 243.0 |
| **21** | 60 | 2020/12/21 | 108 | 131 | 364.2 |
| **22** | 45 | **NaN** | 100 | 119 | 282.0 |
| **23** | 60 | 2020/12/23 | 130 | 101 | 300.0 |
| **24** | 45 | 2020/12/24 | 105 | 132 | 246.0 |
| **25** | 60 | 2020/12/25 | 102 | 126 | 334.5 |
| **26** | 60 | 2020/12/26 | 100 | 120 | 250.0 |
| **27** | 60 | 2020/12/27 | 92 | 118 | 241.0 |
| **28** | 60 | 2020/12/28 | 103 | 132 | **NaN** |
| **29** | 60 | 2020/12/29 | 100 | 132 | 280.0 |
| **30** | 60 | 2020/12/30 | 102 | 129 | 380.3 |
| **31** | 60 | 2020/12/31 | 92 | 115 | 243.0 |

**Observations on the Data:**

* **Missing Values:** Note the `NaN` values in Rows 18, 22, and 28.
* **Outliers/Typos:** Row 7 has a duration of `450`, which appears to be an error (likely meant to be 45).
* **Duplicates:** Row 12 appears to be an exact duplicate of Row 11.

* NaN = Not a Number
* NaT = Not a Time

## 6.1 Cleaning Empty Cells

Empty cells can potentially give you a wrong result when you analyze data.

### 6.1.1 Remove Rows

One way to deal with empty cells is to remove rows that contain empty cells.

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Return a new DataFrame with no empty cells
new_df = df.dropna() #Drop NA

print(new_df.to_string())
# Note: By default, the dropna() method returns a new DataFrame, and will not change the original.

```

**If you want to change the original DataFrame, use the `inplace = True` argument:**

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Remove all rows with NULL values from the original DataFrame
df.dropna(inplace = True)

print(df.to_string())

```

```python
#remove from specific column
df.dropna(subset=["Calories"], inplace = True)

df.dropna(subset=["Pulse"], inplace = True)

df.dropna(subset=["Calories","Pulse"], inplace=True)
```

### 6.1.2 Replace Empty Values

Another way of dealing with empty cells is to insert a new value instead.

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Replace NULL values with the number 130
df.fillna(130, inplace = True)

```

### 6.1.3 Replace Only for Specified Columns

To only replace empty values for one column, specify the column name for the DataFrame.

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Replace NULL values in the "Calories" columns with the number 130
df["Calories"].fillna(130, inplace = True)
#df.fillna({"Calories": 130}, inplace=True)

```

### 6.1.4 Replace Using Mean, Median, or Mode

A common way to replace empty cells is to calculate the mean, median or mode value of the column.

**Calculate Mean:**

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Mean = the average value
x = df["Calories"].mean()

df["Calories"].fillna(x, inplace = True)

```

**Calculate Median:**

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Median = the value in the middle
x = df["Calories"].median()

df["Calories"].fillna(x, inplace = True)

```

**Calculate Mode:**

```python
import pandas as pd

df = pd.read_csv('data.csv')

# Mode = the value that appears most frequently
x = df["Calories"].mode()[0]

df["Calories"].fillna(x, inplace = True)

```

## 6.2 Cleaning Wrong Format

Cells with data of wrong format can make it difficult, or even impossible, to analyze data.

### 6.2.1 Convert Into a Correct Format

To fix it, you have two options: remove the rows, or convert all cells in the columns into the same format.

```python
import pandas as pd

data = {
  "Date": ['2020/12/01', '2020/12/02', '20201226'],
  "duration": [50, 40, 45]
}

df = pd.DataFrame(data)

# Convert to datetime format
df['Date'] = pd.to_datetime(df['Date'], format="mixed")

print(df.to_string())

#         Date  duration
# 0 2020-12-01        50
# 1 2020-12-02        40
# 2 2020-12-26        45
```
* but
```python
import pandas as pd
data = {
  "Date": ['2020/12/01', '2020/12/02', '2020/1203', '20201204'],
  "duration": [50, 40, 45, 60]
}
df = pd.DataFrame(data)
# Use errors='coerce' to turn '2020/1203' into NaT instead of crashing
df['Date'] = pd.to_datetime(df['Date'], format='mixed', errors='coerce')

print(df.to_string())


#         Date  duration
# 0 2020-12-01        50
# 1 2020-12-02        40
# 2        NaT        45
# 3 2020-12-04        60

```

### 6.2.2 Removing Rows

The result from the converting in the example above gave us a NaT value, which can be removed as a NULL value.

```python
df.dropna(subset=['Date'], inplace = True)

```

## 6.3 Cleaning Wrong Data

"Wrong data" does not have to be "empty cells" or "wrong format", it can just be wrong, like if someone registered "199" instead of "1.99".

### 6.3.1 Replacing Values

One way to fix wrong values is to replace them with something else.

```python
# Set "Duration" = 45 in row 7
df.loc[7, 'Duration'] = 45

```

**For small data sets you might be able to replace the wrong data one by one, but not for big data sets.**
To replace wrong data for larger data sets you can create some rules, e.g. set some boundaries for legal values, and replace any values that are outside of the boundaries.

```python
# Loop through all values in the "Duration" column.
# If the value is higher than 120, set it to 120:

for x in df.index:
  if df.loc[x, "Duration"] > 120:
    df.loc[x, "Duration"] = 120

```

### 6.3.2 Removing Rows

Another way of handling wrong data is to remove the rows that contains wrong data.

```python
# Delete rows where "Duration" is higher than 120:

for x in df.index:
  if df.loc[x, "Duration"] > 120:
    df.drop(x, inplace = True)

```

## 6.4 Removing Duplicates

Duplicate rows are rows that have been registered more than one time.

### 6.4.1 Discovering Duplicates

The `duplicated()` method returns a Boolean values for each row.

```python
print(df.duplicated())

# Output:
# 0    False
# 1    False
# 12    True (Example)

```

### 6.4.2 Removing Duplicates

To remove duplicates, use the `drop_duplicates()` method.

```python
df.drop_duplicates(inplace = True)

```

Would you like me to process the **Correlations** section next?