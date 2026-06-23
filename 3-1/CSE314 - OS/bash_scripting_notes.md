# Bash Scripting — Complete Beginner's Notes
> Based on the *Bash Scripting Full Course (3 Hours)* by Linux Hint  
> Written in beginner-friendly language with examples and expected outputs

---

## Table of Contents

1. [Hello Bash Scripting](#1-hello-bash-scripting)
2. [Redirect Output to File](#2-redirect-output-to-file)
3. [Comments](#3-comments)
4. [Conditional Statements (if / else / case)](#4-conditional-statements)
5. [Loops (while / until / for / break / continue)](#5-loops)
6. [Script Input](#6-script-input)
7. [Script Output (stdout & stderr)](#7-script-output)
8. [Sending Output from One Script to Another](#8-sending-output-between-scripts)
9. [String Processing](#9-string-processing)
10. [Numbers and Arithmetic](#10-numbers-and-arithmetic)
11. [The `declare` Command](#11-the-declare-command)
12. [Arrays](#12-arrays)
13. [Functions](#13-functions)
14. [Files and Directories](#14-files-and-directories)
15. [Sending Email via Script](#15-sending-email-via-script)
16. [curl in Scripts](#16-curl-in-scripts)
17. [Professional Menus (select loop)](#17-professional-menus)
18. [Waiting for Filesystem Events with inotify](#18-inotify)
19. [Introduction to grep](#19-introduction-to-grep)
20. [Introduction to awk](#20-introduction-to-awk)
21. [Introduction to sed](#21-introduction-to-sed)
22. [Debugging a Bash Script](#22-debugging-a-bash-script)

---

## 1. Hello Bash Scripting

### What is Bash?

**Bash** stands for **Born Again Shell**. It is the default command-line interpreter on most Linux distributions. When you write a *bash script*, you are writing a text file full of shell commands that the computer will execute one by one — just like a recipe.

### Checking available shells

```bash
cat /etc/shells
```

**Output:**
```
/bin/sh
/bin/bash
/usr/bin/bash
/bin/rbash
...
```

This lists all shells available on your system. We only care about `/bin/bash`.

### Finding the path to bash

```bash
which bash
```

**Output:**
```
/bin/bash
```

This is the path you'll put at the top of every script (called the **shebang**).

### Creating your first script

```bash
touch hello_script.sh
```

Open `hello_script.sh` in a text editor and write:

```bash
#!/bin/bash
echo "Hello Bash Scripting"
```

> **What is `#!/bin/bash`?**  
> This is called the **shebang** (or hashbang). It tells the OS: *"use /bin/bash to run this file."* Every bash script must start with this line.

> **What is `echo`?**  
> `echo` is a command that prints text to the terminal. Think of it as `print()` in Python or `System.out.println()` in Java.

### Making the script executable

By default, a new file cannot be *run* as a program. You need to give it **execute permission**:

```bash
chmod +x hello_script.sh
```

Check the permissions:

```bash
ls -al hello_script.sh
```

**Before chmod:**
```
-rw-r--r-- 1 user user 32 Jan 1 10:00 hello_script.sh
```

**After chmod:**
```
-rwxr-xr-x 1 user user 32 Jan 1 10:00 hello_script.sh
```

The `x` means executable. The file also turns green in most terminals.

### Running the script

```bash
./hello_script.sh
```

**Output:**
```
Hello Bash Scripting
```

> **Why `./`?**  
> The `./` means "in the current directory." Without it, the shell would look for the script in system folders like `/usr/bin` — not your folder.

---

## 2. Redirect Output to File

Sometimes you don't want output on the screen — you want it saved to a file. You can do this with the `>` (overwrite) and `>>` (append) operators.

### Overwrite (`>`)

```bash
#!/bin/bash
echo "Hello Bash Linux Audience" > file.txt
```

After running `./hello_script.sh`, a `file.txt` is created with:

```
Hello Bash Linux Audience
```

> ⚠️ Every time you run the script, the file gets **overwritten** (old content is deleted).

### Append (`>>`)

```bash
#!/bin/bash
cat >> file.txt
```

This opens an interactive mode where you type into the terminal and it gets **added** to `file.txt` without erasing existing content. Press `Ctrl+D` to finish.

**Typing:**
```
This is a new line
Another line of text
```

Press `Ctrl+D`. Now `file.txt` contains both old and new content.

---

## 3. Comments

Comments are lines in your script that the computer **ignores**. They exist only to explain the code to humans.

### Single-line comment

Use `#` at the start of a line:

```bash
#!/bin/bash
# This is a comment — the computer ignores this line
echo "Hello"   # you can also comment after a command
```

**Output:**
```
Hello
```

### Multi-line comment

If you have many lines to comment out, use this syntax:

```bash
: '
This is line 1
This is line 2
This is line 3
All ignored by bash
'
```

> **How it works:** `: '...'` is a bash trick — `:` is a no-op command that does nothing, and the single-quoted string is passed to it as an argument (which is then ignored).

### Here-Doc (`<<`)

A *heredoc* is like a multi-line string — but unlike a regular comment, its content **does appear in the output**:

```bash
#!/bin/bash
cat << CREATIVE
This is hello creative text
Add another line
And one more
CREATIVE
```

**Output:**
```
This is hello creative text
Add another line
And one more
```

> **How it works:** `CREATIVE` is a custom **delimiter** (you can name it anything). Everything between `<< CREATIVE` and the closing `CREATIVE` is passed to `cat` and printed.

---

## 4. Conditional Statements

### if statement

```bash
#!/bin/bash
count=10

if [ $count -eq 10 ]; then
    echo "The condition is true"
fi
```

**Output:**
```
The condition is true
```

> **Important:** Always put a **space** after `[` and before `]`. Without spaces, bash gives an error.

### if-else statement

```bash
#!/bin/bash
count=9

if [ $count -eq 10 ]; then
    echo "The condition is true"
else
    echo "The condition is false"
fi
```

**Output:**
```
The condition is false
```

### Comparison operators

| Operator | Meaning           | Example              |
|----------|-------------------|----------------------|
| `-eq`    | equal to          | `[ $a -eq 10 ]`     |
| `-ne`    | not equal to      | `[ $a -ne 10 ]`     |
| `-gt`    | greater than      | `[ $a -gt 5 ]`      |
| `-lt`    | less than         | `[ $a -lt 5 ]`      |
| `-ge`    | greater or equal  | `[ $a -ge 5 ]`      |
| `-le`    | less or equal     | `[ $a -le 5 ]`      |

You can also use **angle brackets** with double parentheses:

```bash
if (( $count > 9 )); then
    echo "Greater"
fi
```

### if-elif-else statement

```bash
#!/bin/bash
count=10

if [ $count -lt 9 ]; then
    echo "First condition is true"
elif [ $count -lt 9 ]; then
    echo "Second condition is true"
else
    echo "The condition is false"
fi
```

**Output:**
```
The condition is false
```

### AND operator (`&&` / `-a`)

Both conditions must be true:

```bash
#!/bin/bash
age=30

if [ "$age" -gt 18 ] && [ "$age" -lt 40 ]; then
    echo "Age is correct"
else
    echo "Age is not correct"
fi
```

**Output:**
```
Age is correct
```

Three equivalent syntaxes for AND:
```bash
[ "$age" -gt 18 ] && [ "$age" -lt 40 ]   # double brackets with &&
[[ "$age" -gt 18 && "$age" -lt 40 ]]     # double square brackets
[ "$age" -gt 18 -a "$age" -lt 40 ]       # -a flag (older style)
```

### OR operator (`||` / `-o`)

At least one condition must be true:

```bash
#!/bin/bash
age=50

if [ "$age" -gt 18 ] || [ "$age" -lt 40 ]; then
    echo "Age is correct"
else
    echo "Age is not correct"
fi
```

**Output:**
```
Age is correct
```

(Because `50 > 18` is true, even though `50 < 40` is false.)

If **both** are false:

```bash
age=10
if [ "$age" -gt 40 ] || [ "$age" -lt 0 ]; then ...
```

This would go to `else` because neither condition is true.

### case statement

The `case` statement is like multiple `if-elif` checks but cleaner:

```bash
#!/bin/bash
car="BMW"

case $car in
    BMW)
        echo "BMW selected" ;;
    Mercedes)
        echo "Mercedes selected" ;;
    Toyota)
        echo "Toyota selected" ;;
    *)
        echo "Unknown car" ;;
esac
```

**Output:**
```
BMW selected
```

> `*)` is the **default** case (like `else`). `;;` ends each case block. `esac` is `case` spelled backwards — it closes the statement.

---

## 5. Loops

### while loop

Runs **as long as** the condition is true:

```bash
#!/bin/bash
number=1

while [ $number -le 10 ]; do
    echo $number
    number=$(( number + 1 ))
done
```

**Output:**
```
1
2
3
...
10
```

> `$(( number + 1 ))` is how you do arithmetic in bash. The `$((...))` syntax evaluates the math expression inside.

### until loop

Runs **until** the condition becomes true (opposite of while):

```bash
#!/bin/bash
number=1

until [ $number -ge 10 ]; do
    echo $number
    number=$(( number + 1 ))
done
```

**Output:**
```
1
2
3
...
9
```

> The loop stops *before* printing 10 because when `number=10`, `10 -ge 10` becomes true, so the loop exits.

**Mental model:**
- `while`: "Keep going while this is true."
- `until`: "Keep going until this becomes true."

### for loop — list style

```bash
#!/bin/bash
for i in 1 2 3 4 5; do
    echo $i
done
```

**Output:**
```
1
2
3
4
5
```

For a range:

```bash
for i in {0..20}; do
    echo $i
done
```

**Output:** `0 1 2 ... 20`

With a step (increment of 2):

```bash
for i in {0..20..2}; do
    echo $i
done
```

**Output:** `0 2 4 6 8 10 12 14 16 18 20`

### for loop — C-style

```bash
#!/bin/bash
for (( i=0; i<5; i++ )); do
    echo $i
done
```

**Output:**
```
0
1
2
3
4
```

### break statement

Immediately exits the loop:

```bash
#!/bin/bash
for (( i=0; i<=10; i++ )); do
    if [ $i -gt 5 ]; then
        break
    fi
    echo $i
done
```

**Output:**
```
0
1
2
3
4
5
```

When `i` becomes 6, `6 > 5` is true → `break` fires → loop ends.

### continue statement

Skips the **current iteration** and goes back to the top of the loop:

```bash
#!/bin/bash
for (( i=0; i<=10; i++ )); do
    if [ $i -eq 3 ] || [ $i -eq 7 ]; then
        continue
    fi
    echo $i
done
```

**Output:**
```
0
1
2
4
5
6
8
9
10
```

3 and 7 are skipped.

> **break vs continue:**
> - `break` → exits the loop completely
> - `continue` → skips current step, goes back to the loop condition

---

## 6. Script Input

### Command-line arguments (`$1`, `$2`, `$3`, ...)

When you run a script, you can pass values to it:

```bash
./hello_script.sh BMW Mercedes Toyota
```

Inside the script:
- `$0` → script name
- `$1` → first argument (`BMW`)
- `$2` → second argument (`Mercedes`)
- `$3` → third argument (`Toyota`)

```bash
#!/bin/bash
echo $0 $1 $2 $3
```

**Run as:** `./hello_script.sh BMW Mercedes Toyota`

**Output:**
```
./hello_script.sh BMW Mercedes Toyota
```

### Storing all arguments in an array

```bash
#!/bin/bash
args=("$@")

echo ${args[0]}
echo ${args[1]}
echo ${args[2]}
```

**Run as:** `./hello_script.sh BMW Honda Mercedes`

**Output:**
```
BMW
Honda
Mercedes
```

Print **all** arguments at once:

```bash
echo "$@"
```

Get the **count** of arguments:

```bash
echo $#
```

**Run as:** `./hello_script.sh BMW Honda Toyota`  
**Output:** `3`

### Reading a file line by line via stdin

```bash
#!/bin/bash
while IFS= read -r line; do
    echo "$line"
done < "$1"
```

**Run as:** `./hello_script.sh myfile.txt`  
This reads `myfile.txt` line by line and prints each line.

If you run without a file argument:
```bash
./hello_script.sh
```
The terminal itself acts as input — whatever you type gets echoed back. Press `Ctrl+Z` to stop.

---

## 7. Script Output

Bash has two output streams:

| Stream | Number | Meaning |
|--------|--------|---------|
| **stdout** | 1 | Normal output |
| **stderr** | 2 | Error output |

### Redirect stdout and stderr to separate files

```bash
#!/bin/bash
ls -al 1> file1.txt 2> file2.txt
```

- Correct commands → output goes to `file1.txt`
- Errors → go to `file2.txt`

### Redirect both to the same file

```bash
ls -al > file1.txt 2>&1
```

Or the shortcut:

```bash
ls -al &> file1.txt
```

**Example with an error:**

```bash
ls +al &> file1.txt
```

`file1.txt` will contain the error message:
```
ls: invalid option -- '+'
```

---

## 8. Sending Output Between Scripts

You can export a variable from one script to make it available in another.

**hello_script.sh:**
```bash
#!/bin/bash
message="Hello Linux Audience"
export message
./second_script.sh
```

**second_script.sh:**
```bash
#!/bin/bash
echo "Message from hello script is: $message"
```

Make sure to give execute permission: `chmod +x second_script.sh`

**Run:** `./hello_script.sh`

**Output:**
```
Message from hello script is: Hello Linux Audience
```

> `export` makes a variable available to **child processes** (scripts called from within this script).

---

## 9. String Processing

### Read strings from user

```bash
#!/bin/bash
echo "Enter first string:"
read st1

echo "Enter second string:"
read st2
```

### Compare strings (equal / not equal)

```bash
if [ "$st1" == "$st2" ]; then
    echo "Strings match"
else
    echo "Strings don't match"
fi
```

### Compare strings (alphabetical order)

```bash
if [[ "$st1" < "$st2" ]]; then
    echo "$st1 is smaller than $st2"
elif [[ "$st2" < "$st1" ]]; then
    echo "$st2 is smaller than $st1"
else
    echo "Both strings are equal"
fi
```

**Example run:**
```
Enter first string: abc
Enter second string: linux
abc is smaller than linux
```

### Concatenate strings

```bash
c="$st1 $st2"
echo "$c"
```

**Example:**
```
Enter first string: Linux
Enter second string: Hint
Linux Hint
```

### Uppercase and lowercase conversion

```bash
echo "${st1,,}"   # all lowercase
echo "${st1^^}"   # all UPPERCASE
```

**Example:**
```
Enter first string: LinuxHint
linuxhint
LINUXHINT
```

Capitalize **only the first letter**:

```bash
echo "${st1^L}"   # capitalize the 'L' specifically
```

---

## 10. Numbers and Arithmetic

### Basic arithmetic with `$(( ))`

```bash
#!/bin/bash
n1=4
n2=20

echo $(( n1 + n2 ))   # Addition
echo $(( n1 - n2 ))   # Subtraction
echo $(( n1 * n2 ))   # Multiplication
echo $(( n2 / n1 ))   # Division (integer only)
echo $(( n2 % n1 ))   # Remainder (modulo)
```

**Output:**
```
24
-16
80
5
0
```

> ⚠️ Bash only does **integer** arithmetic. `4 / 20` gives `0`, not `0.2`. Use `bc` for decimals.

### Arithmetic with `expr`

```bash
echo $(expr $n1 + $n2)
echo $(expr $n1 \* $n2)   # Note: * must be escaped with \
```

**Output:**
```
24
80
```

### Convert hexadecimal to decimal

```bash
#!/bin/bash
echo "Enter a hex number:"
read hex

echo "Decimal value:"
echo "obase=10; ibase=16; $hex" | bc
```

**Example run:**
```
Enter a hex number: FFFFFF
Decimal value:
16777215
```

> `bc` is the **bash calculator**. `ibase` sets input base (16 = hex), `obase` sets output base (10 = decimal).

---

## 11. The `declare` Command

Bash is **loosely typed** — variables don't have strict types. But `declare` lets you add constraints.

### View all variables

```bash
declare -p
```

### Declare and set a variable

```bash
declare myvar=22
declare -p myvar
```

**Output:**
```
declare -- myvar="22"
```

### Read-only variable (`-r`)

```bash
#!/bin/bash
declare -r pwdfile="/etc/passwd"
echo $pwdfile

pwdfile="/etc/abc.txt"   # This will fail!
echo $pwdfile
```

**Output:**
```
/etc/passwd
bash: pwdfile: readonly variable
/etc/passwd
```

The value doesn't change because it's read-only.

---

## 12. Arrays

An array stores multiple values in one variable.

### Declare an array

```bash
#!/bin/bash
cars=("BMW" "Toyota" "Honda")
```

### Print all elements

```bash
echo "${cars[@]}"
```

**Output:**
```
BMW Toyota Honda
```

### Print by index

Arrays start at index **0**:

```bash
echo "${cars[0]}"   # BMW
echo "${cars[1]}"   # Toyota
echo "${cars[2]}"   # Honda
```

### Print all indexes

```bash
echo "${!cars[@]}"
```

**Output:**
```
0 1 2
```

### Count elements

```bash
echo "${#cars[@]}"
```

**Output:**
```
3
```

### Delete an element

```bash
unset cars[2]   # removes Honda (index 2)
echo "${cars[@]}"
```

**Output:**
```
BMW Toyota
```

### Add / replace an element

```bash
cars[2]="Mercedes"
echo "${cars[@]}"
```

**Output:**
```
BMW Toyota Mercedes
```

---

## 13. Functions

A function is a **reusable block of code**. Instead of copy-pasting 60 lines five times, you write those 60 lines once inside a function and just *call* the function wherever you need it.

### Basic function

```bash
#!/bin/bash
function my_function {
    echo "This is a new function"
}

my_function   # calling the function
```

**Output:**
```
This is a new function
```

> Without calling `my_function`, nothing happens!

### Function with arguments

```bash
#!/bin/bash
function print_msg {
    echo "$1"
}

print_msg "Hi there"
```

**Output:**
```
Hi there
```

Multiple arguments:

```bash
function print_all {
    echo "$1 $2 $3 $4"
}

print_all "Hi" "this" "is" "Linux"
```

**Output:**
```
Hi this is Linux
```

### Local variables inside functions

Variables declared inside a function are **local** — they don't affect variables with the same name outside:

```bash
#!/bin/bash
returning_value="I love Mac"

function function_check {
    returning_value="I love Linux"
    echo $returning_value
}

echo $returning_value   # prints before function runs
function_check          # function changes the variable
echo $returning_value   # what does it print now?
```

**Output:**
```
I love Mac
I love Linux
I love Linux
```

> The function **modifies** the outer variable (no `local` keyword was used). If you want to keep the function's variable truly local, use `local returning_value="I love Linux"` inside the function.

---

## 14. Files and Directories

### Create a directory

```bash
mkdir -p my_directory
```

`-p` means "create parent directories if needed, and don't error if it already exists."

### Check if a directory exists

```bash
#!/bin/bash
echo "Enter directory name to check:"
read direc

if [ -d "$direc" ]; then
    echo "Directory exists"
else
    echo "Directory does not exist"
fi
```

**Example run:**
```
Enter directory name to check: my_directory
Directory exists
```

### Create a file

```bash
#!/bin/bash
echo "Enter file name to create:"
read filename
touch "$filename"
```

### Check if a file exists

```bash
if [ -f "$filename" ]; then
    echo "$filename exists"
else
    echo "$filename does not exist"
fi
```

> **Key flags:**
> - `-d` → checks for a **directory**
> - `-f` → checks for a **file**

### Append text to a file

```bash
#!/bin/bash
echo "Enter file name:"
read filename

if [ -f "$filename" ]; then
    echo "Enter text to append:"
    read file_text
    echo "$file_text" >> "$filename"
else
    echo "$filename doesn't exist"
fi
```

> Use `>` to **overwrite**, `>>` to **append**.

### Read a file line by line

```bash
#!/bin/bash
echo "Enter file name to read:"
read filename

if [ -f "$filename" ]; then
    while IFS= read -r line; do
        echo "$line"
    done < "$filename"
else
    echo "$filename doesn't exist"
fi
```

### Delete a file

```bash
#!/bin/bash
echo "Enter file name to delete:"
read filename

if [ -f "$filename" ]; then
    rm "$filename"
    echo "File deleted successfully"
else
    echo "$filename doesn't exist"
fi
```

---

## 15. Sending Email via Script

### Setup steps

1. Install `ssmtp`:
   ```bash
   sudo apt install ssmtp
   ```

2. In your Google account → **Security** → turn on **Less Secure App Access**.

3. Edit the config file:
   ```bash
   sudo nano /etc/ssmtp/ssmtp.conf
   ```
   Add:
   ```
   root=youremail@gmail.com
   mailhub=smtp.gmail.com:587
   AuthUser=youremail@gmail.com
   AuthPass=yourpassword
   UseSTARTTLS=yes
   ```

### Script to send email

```bash
#!/bin/bash
ssmtp recipient@gmail.com
```

When you run this, bash opens an interactive prompt. Type the email structure:

```
To: recipient@gmail.com
From: youremail@gmail.com
CC: youremail@gmail.com
Subject: Test

This is the body.
```

Press `Ctrl+D` to send.

> ⚠️ Use a throwaway email account for this. Enabling "Less Secure App Access" weakens your account's security.

---

## 16. curl in Scripts

`curl` is a command to **download files or fetch URLs** from the internet.

### Download a file (keeping original name)

```bash
#!/bin/bash
url="https://example.com/testfile.dat"
curl -O "$url"
```

`-O` keeps the original filename from the server.

### Download with a custom filename

```bash
curl -o mydownload.dat "$url"
```

### Redirect output to a file

```bash
curl "$url" > outputfile.dat
```

### Fetch only the HTTP headers (no download)

```bash
curl -I "$url"
```

**Output:**
```
HTTP/1.1 200 OK
Date: Mon, 01 Jan 2024 10:00:00 GMT
Server: Apache
Content-Length: 1048576
Content-Type: application/octet-stream
```

This is useful for **checking** if a file is valid before downloading all of it.

---

## 17. Professional Menus

### select loop

`select` automatically creates a numbered menu from a list and waits for the user to pick one:

```bash
#!/bin/bash
select car in BMW Mercedes Tesla Rover Toyota; do
    echo "You have selected $car"
done
```

**Output:**
```
1) BMW
2) Mercedes
3) Tesla
4) Rover
5) Toyota
#? 
```

If user types `2`:
```
You have selected Mercedes
```

### select with case (handle invalid input)

```bash
#!/bin/bash
select car in BMW Mercedes Tesla Rover Toyota; do
    case $car in
        BMW)
            echo "BMW selected" ;;
        Mercedes)
            echo "Mercedes selected" ;;
        Tesla)
            echo "Tesla selected" ;;
        Rover)
            echo "Rover selected" ;;
        Toyota)
            echo "Toyota selected" ;;
        *)
            echo "Error: please select between 1 to 5" ;;
    esac
done
```

### Waiting for a keypress

```bash
#!/bin/bash
echo "Press any key to continue..."

while true; do
    read -t 3
    if [ $? == 0 ]; then
        echo "You have terminated the script"
        exit
    else
        echo "Waiting for you to press a key, sir..."
    fi
done
```

**Output (before keypress, every 3 seconds):**
```
Press any key to continue...
Waiting for you to press a key, sir...
Waiting for you to press a key, sir...
```

**After pressing any key:**
```
You have terminated the script
```

> `read -t 3` waits 3 seconds for input. `$?` holds the exit status of the last command: `0` means input was received.

---

## 18. inotify

`inotify` (**inode notify**) is a Linux kernel feature that **monitors files and directories for changes** and reports them in real time.

### Install

```bash
sudo apt install inotify-tools
```

### Create a directory and watch it

```bash
#!/bin/bash
mkdir -p /tmp/new_folder
inotifywait -m /tmp/new_folder
```

**Output (waiting):**
```
Setting up watches.
Watches established.
```

Now open that folder in a file manager or create a file inside it in another terminal:

```bash
touch /tmp/new_folder/file1.txt
echo "Hello" > /tmp/new_folder/file1.txt
```

**inotify output:**
```
/tmp/new_folder/ CREATE file1.txt
/tmp/new_folder/ OPEN file1.txt
/tmp/new_folder/ MODIFY file1.txt
/tmp/new_folder/ CLOSE_WRITE,CLOSE file1.txt
```

> `-m` means **monitor** (keep watching; don't exit after first event).

---

## 19. Introduction to grep

`grep` searches for a **pattern** (text or regex) inside a file and prints matching lines.

### Basic usage

```bash
grep "Linux" file.txt
```

Prints all lines in `file.txt` that contain the word "Linux".

### Case-insensitive search (`-i`)

```bash
grep -i "linux" file.txt
```

Matches `Linux`, `LINUX`, `linux`, etc.

### Show line numbers (`-n`)

```bash
grep -in "linux" file.txt
```

**Output:**
```
1:This is Linux
4:This is Linux
7:This is Linux
```

### Count matches (`-c`)

```bash
grep -ic "windows" file.txt
```

**Output:**
```
8
```

(The word "windows" appears 8 times.)

### Invert match — lines that do NOT contain the word (`-v`)

```bash
grep -iv "windows" file.txt
```

Prints all lines that do **not** contain "windows".

### In a script

```bash
#!/bin/bash
echo "Enter file name to search:"
read filename

if [ -f "$filename" ]; then
    echo "Enter text to search:"
    read grep_var
    grep -in "$grep_var" "$filename"
else
    echo "File doesn't exist"
fi
```

---

## 20. Introduction to awk

`awk` is a **mini programming language** built into bash, used for processing structured text data (like CSV or space-separated columns).

### Key concept: fields

`awk` splits each line into **fields** (columns) separated by whitespace:

| Line content | `$1` | `$2` | `$3` | `$4` |
|---|---|---|---|---|
| `This is Linux 2000` | `This` | `is` | `Linux` | `2000` |
| `This is Windows 3000` | `This` | `is` | `Windows` | `3000` |

### Print entire file

```bash
awk '{print}' file.txt
```

### Print lines matching a pattern

```bash
awk '/Windows/ {print}' file.txt
```

Only prints lines containing "Windows".

### Print a specific field

```bash
awk '/Windows/ {print $2}' file.txt
```

**Output:** `is`  (the 2nd word of each Windows line)

```bash
awk '/Windows/ {print $4}' file.txt
```

**Output:** `3000`

### Print multiple fields

```bash
awk '/Windows/ {print $1, $3}' file.txt
```

**Output:** `This Windows`

### In a script

```bash
#!/bin/bash
echo "Enter file name:"
read filename

if [ -f "$filename" ]; then
    awk '/Windows/ {print $1, $4}' "$filename"
else
    echo "File doesn't exist"
fi
```

---

## 21. Introduction to sed

`sed` stands for **Stream Editor**. It reads text line by line and performs transformations — most commonly **find-and-replace**.

### Basic substitution

```bash
cat file.txt | sed "s/old_text/new_text/"
```

Or without pipe:

```bash
sed "s/old_text/new_text/" file.txt
```

`s` = substitute. Format: `s/find/replace/`

> ⚠️ By default this only replaces the **first occurrence** on each line.

### Replace all occurrences on every line (`g` flag)

```bash
sed "s/i/I/g" file.txt
```

Replaces every lowercase `i` with uppercase `I` throughout the file.

### Case-insensitive replace (`i` flag)

```bash
sed "s/linux/Unix/gi" file.txt
```

### Replace whole words

```bash
sed "s/Linux/Unix/g" file.txt
```

### Save output to a new file

```bash
sed "s/2000/8000/g" file.txt > newfile.txt
```

### Modify the file in-place (`-i` flag)

```bash
sed -i "s/Linux/Unix/g" file.txt
```

> ⚠️ This **permanently modifies** `file.txt`. There's no undo. Always make a backup first.

### In a script

```bash
#!/bin/bash
echo "Enter file name to substitute:"
read filename

if [ -f "$filename" ]; then
    cat "$filename" | sed "s/i/I/g"
else
    echo "File doesn't exist"
fi
```

---

## 22. Debugging a Bash Script

When your script has a bug, bash gives errors like:

```
./hello_script.sh: line 6: [: missing `]'
```

For complex scripts, you need more visibility. Bash has built-in debugging tools.

### Method 1: Run with `bash -x`

```bash
bash -x hello_script.sh
```

This shows **every line as it executes**, with a `+` prefix:

```
+ echo 'Enter file name:'
Enter file name:
+ read filename
file.txt
+ '[' -f file.txt ']'
+ echo 'File exists'
File exists
```

### Method 2: Add `-x` to the shebang

```bash
#!/bin/bash -x
```

Now the script always runs in debug mode.

### Method 3: Debug only part of the script

Use `set -x` to start debugging and `set +x` to stop:

```bash
#!/bin/bash
echo "This line is NOT debugged"
read filename

set -x    # debugging starts here
if [ -f "$filename" ]; then
    echo "File exists"
fi
set +x    # debugging stops here

echo "This line is NOT debugged either"
```

**Output:**
```
This line is NOT debugged
file.txt
+ '[' -f file.txt ']'
+ echo 'File exists'
File exists
+ set +x
This line is NOT debugged either
```

> Debugging only the middle section is useful for large scripts where you already know which part is broken.

---

## Quick Reference Card

```
Variables:     name="value"     echo $name
Arithmetic:    $(( a + b ))     expr $a + $b
Conditions:    [ -eq -ne -gt -lt -ge -le ]
Strings:       == != < >
File tests:    -f (file)  -d (directory)
Arrays:        arr=(a b c)   ${arr[@]}   ${#arr[@]}   ${!arr[@]}
Functions:     function name { ... }   name arg1 arg2
Loops:         while/until/for ... do ... done
I/O:           read var   echo   >  >>  <  2>  &>
Search:        grep -in pattern file
Process:       awk '{print $1}' file
Replace:       sed "s/old/new/g" file
Debug:         bash -x script.sh   or   set -x / set +x
```

---

*Happy scripting, Riyad! 🚀*
