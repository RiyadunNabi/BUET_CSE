# Comprehensive Terminal Guide: Compiling C++ on Windows & Linux

---

## 🪟 Part 1: Windows Setup

### 1. Code in VS Code (`main.cpp`)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello from Windows terminal!" << endl;
    return 0;
}
```

### 2. Terminal Run

#### Step A: Open and Navigate

Open Command Prompt. You will start in your Windows profile directory. Move to your project folder:

```cmd
C:\Users\Riyad> cd MyFolder
C:\Users\Riyad\MyFolder> _
```

#### Step B: Compile the Code

Compile `main.cpp` into a customized executable name (e.g., `win_app`):

```cmd
C:\Users\Riyad\MyFolder> g++ main.cpp -o win_app
C:\Users\Riyad\MyFolder> _
```

> A blank line means it compiled successfully with zero errors.

#### Step C: Check Created Files

```cmd
C:\Users\Riyad\MyFolder> dir
 Directory of C:\Users\Riyad\MyFolder

01/07/2026  10:15 AM    <DIR>          .
01/07/2026  10:15 AM    <DIR>          ..
01/07/2026  10:10 AM               124 main.cpp
01/07/2026  10:15 AM            52,416 win_app.exe
```

#### Step D: Run the Program

```cmd
C:\Users\Riyad\MyFolder> win_app
Hello from Windows terminal!
C:\Users\Riyad\MyFolder> _
```

---
## Complete Single-Snippet Workflows
Here are the complete, single-snippet terminal workflows for both operating systems.
---

### 🪟 Windows (Command Prompt)

```cmd
C:\Users\Riyad> cd MyFolder
C:\Users\Riyad\MyFolder> g++ main.cpp -o win_app
C:\Users\Riyad\MyFolder> dir
 Directory of C:\Users\Riyad\MyFolder

01/07/2026  10:15 AM    <DIR>          .
01/07/2026  10:15 AM    <DIR>          ..
01/07/2026  10:10 AM               124 main.cpp
01/07/2026  10:15 AM            52,416 win_app.exe
C:\Users\Riyad\MyFolder> win_app
Hello from Windows terminal!
C:\Users\Riyad\MyFolder> _
```

---

### 🪟 Windows (Command Prompt One-Liner)

In Windows Command Prompt, use `&&` to chain commands. The second command will only run if the compilation succeeds.

```cmd
C:\Users\Riyad\MyFolder> g++ main.cpp -o win_app && win_app
Hello from Windows terminal!
C:\Users\Riyad\MyFolder> _
```

---

## 🐧 Part 2: Linux Setup (Pop!_OS / Ubuntu)

### 1. Code in VS Code (`main.cpp`)

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello from Pop!_OS terminal!" << endl;
    return 0;
}
```

### 2. Terminal Run

#### Step A: Initial Terminal Window

When you open your Linux terminal using `Ctrl + Alt + T`, your shell starts at the home (`~`) directory:

```bash
riyadunnabi@RiyadunNabi-pop-os:~$ _
```

#### Step B: Navigate to the Workspace

```bash
riyadunnabi@RiyadunNabi-pop-os:~$ cd MyFolder
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ _
```

#### Step C: Compile the Code

Compile `main.cpp` into a clean Linux binary named `linux_app`:

```bash
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ g++ main.cpp -o linux_app
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ _
```

#### Step D: Verify the Executable File

```bash
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ ls
linux_app  main.cpp
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ _
```

#### Step E: Execute the Binary

You must prefix the filename with `./` so Linux knows to check your current folder:

```bash
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ ./linux_app
Hello from Pop!_OS terminal!
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ _
```

---
---

## Complete Single-Snippet Workflows
Here are the complete, single-snippet terminal workflows for both operating systems.
---

### 🐧 Linux (Pop!_OS / Ubuntu Terminal)

```bash
riyadunnabi@RiyadunNabi-pop-os:~$ cd MyFolder
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ g++ main.cpp -o linux_app
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ ls
linux_app  main.cpp
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ ./linux_app
Hello from Pop!_OS terminal!
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ _
```

---

### 🐧 Linux (Pop!_OS / Ubuntu One-Liner)

Linux also uses `&&` to link the compiler to the execution step seamlessly.

```bash
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ g++ main.cpp -o linux_app && ./linux_app
Hello from Pop!_OS terminal!
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ _
```

---













---
# Compiling C on Windows & Linux

This is the C counterpart to `Compiling_CPP_Windows_Linux.md` The workflow is identical — only the compiler and file extension change:

- Use `gcc` instead of `g++`
- Save your file as `main.c` instead of `main.cpp`

## 1. Code (`main.c`)

```c
#include <stdio.h>

int main() {
    printf("Hello from the terminal!\n");
    return 0;
}
```

## 2. 🪟 Windows (Command Prompt)

```cmd
C:\Users\Riyad\MyFolder> gcc main.c -o win_app
C:\Users\Riyad\MyFolder> win_app
Hello from the terminal!
```

**One-liner:**

```cmd
C:\Users\Riyad\MyFolder> gcc main.c -o win_app && win_app
```

## 3. 🐧 Linux (Pop!_OS / Ubuntu)

```bash
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ gcc main.c -o linux_app
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ ./linux_app
Hello from the terminal!
```

**One-liner:**

```bash
riyadunnabi@RiyadunNabi-pop-os:~/MyFolder$ gcc main.c -o linux_app && ./linux_app
```

## Note

Everything else — navigating with `cd`, checking files with `dir` (Windows) / `ls` (Linux), and running the binary with `./` on Linux — works exactly the same as in the C++ guide.