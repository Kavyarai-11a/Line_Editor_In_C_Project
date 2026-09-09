# Line_Editor_In_C_Project

# Simple Line Editor in C

##  Project Overview

The **Simple Line Editor** is a command-line text editor developed using the **C programming language**.

It allows users to create and edit a document one line at a time using simple commands. The editor supports operations such as inserting, deleting, displaying, saving, loading, searching, replacing text, counting words, and undoing the last modification.

The project uses a **dynamic array of strings** to store the lines of the document.

---

##  Objectives

* Implement a simple text editor using C.
* Store and manage multiple lines dynamically.
* Allow users to insert and delete lines.
* Display the current document with line numbers.
* Save the document to a file and load it back.
* Provide additional features such as search, replace, word count, and undo.
* Practice dynamic memory allocation and string manipulation in C.

---

##  Data Structure Used

The project uses a **dynamic array of strings**.

```c
typedef struct {
    char **lines;
    int count;
    int capacity;
} Document;
```

### Components

* `lines` – Stores pointers to dynamically allocated strings.
* `count` – Stores the current number of lines.
* `capacity` – Stores the total number of lines that can currently be stored.

The array automatically grows when its capacity is reached.

### Why Dynamic Array?

A dynamic array was selected because:

* It allows the document to grow dynamically.
* Lines can be accessed easily using their line number.
* Memory is allocated only when required.
* It is simple to implement and understand in C.

---

## ⚙️ Features

### 1. Append a Line

Adds a new line at the end of the document.

```text
append Hello World
```

or

```text
add Hello World
```

---

### 2. Insert a Line

Inserts a line at a specified position.

```text
insert 2 "This is a new line"
```

The existing lines are shifted to make space for the new line.

---

### 3. Delete a Line

Deletes a line using its line number.

```text
delete 2
```

The remaining lines are shifted to fill the empty position.

---

### 4. Display Document

Displays all current lines along with their line numbers.

```text
display
```

Example:

```text
1: Hello World
2: This is a new line
3: Welcome to C
```

---

### 5. Save Document

Saves the current document into a text file.

```text
save document.txt
```

---

### 6. Load Document

Loads the contents of a text file into the editor.

```text
load document.txt
```

---

### 7. Search

Searches for a word or phrase in the document.

```text
search Hello
```

The editor displays the line numbers where the search text occurs.

---

### 8. Replace Text in a Line

Replaces text in a specific line.

```text
replace 2 old new
```

Example:

```text
replace 2 cat dog
```

---

### 9. Replace All

Replaces a word or phrase throughout the document.

```text
replaceall old new
```

---

### 10. Undo

Reverts the document to its previous state.

```text
undo
```

The project supports **one level of undo**.

---

### 11. Word Count

Counts the total number of words in the document.

```text
count
```

---

### 12. Help

Displays the available commands and their usage.

```text
help
```

---

### 13. Exit

Exits the line editor.

```text
exit
```

or

```text
quit
```

---

##  Header Files Used

The project uses the following standard C header files:

| Header File | Purpose                                        |
| ----------- | ---------------------------------------------- |
| `stdio.h`   | Input/output and file handling                 |
| `stdlib.h`  | Dynamic memory allocation and conversions      |
| `string.h`  | String manipulation                            |
| `ctype.h`   | Character checking and conversion              |
| `stdint.h`  | Provides `SIZE_MAX` for safe size calculations |

---

##  Memory Management

Dynamic memory allocation is used to store the document.

The project uses:

* `malloc()` – Allocates memory.
* `realloc()` – Increases the capacity of the line array.
* `free()` – Releases allocated memory.

When the document reaches its current capacity, the capacity is increased dynamically.

---

##  How the Editor Works

The basic flow of the program is:

```text
Start
  ↓
Initialize Document
  ↓
Read User Command
  ↓
Parse Command
  ↓
Execute Operation
  ↓
Update Document
  ↓
Display Result
  ↓
Read Next Command
  ↓
Exit
```

---

##  Error Handling

The program handles several invalid situations, including:

* Invalid line numbers.
* Attempting to delete from an empty document.
* Missing command arguments.
* Invalid commands.
* File opening errors.
* Memory allocation failures.
* Empty search or replacement targets.

This makes the editor more robust and user-friendly.

---

##  Example Usage

```text
> append Hello World
Line appended.

> append Welcome to C
Line appended.

> display

1: Hello World
2: Welcome to C

> insert 2 "This is a Line Editor"
Line inserted.

> display

1: Hello World
2: This is a Line Editor
3: Welcome to C

> search World
Found at line 1.

> delete 2
Line deleted.

> count
Total words: 5

> save document.txt
Document saved successfully.

> exit
```

---

##  Project Structure

```text
Line_Editor_In_C_Project/
│
├── Line_Editior.c
├── README.md
└── HELP.md
```

> The C source file contains the implementation of the line editor and its features.

---

## 🛠️ Technologies Used

* **Programming Language:** C
* **Data Structure:** Dynamic Array of Strings
* **File Handling:** C File I/O
* **Memory Management:** Dynamic Memory Allocation
* **Compiler:** GCC
* **Development Environment:** VS Code
* **Version Control:** Git and GitHub

---

##  Compilation and Execution

### Compile

Using GCC:

```bash
gcc Line_Editior.c -o Line_Editor
```

### Run

On Windows PowerShell:

```powershell
.\Line_Editor.exe
```

On Linux/macOS:

```bash
./Line_Editor
```

---

##  Team Project

This project was developed as a team project to demonstrate the implementation of a basic command-line line editor using C.

The project focuses on:

* Data structures
* Dynamic memory allocation
* String handling
* File handling
* Command parsing
* Error handling

---

##  Learning Outcomes

Through this project, we learned how to:

* Work with structures in C.
* Use pointers and pointer-to-pointer concepts.
* Allocate and free memory dynamically.
* Store strings using a dynamic array.
* Insert and delete elements from an array.
* Perform file operations in C.
* Search and replace strings.
* Implement a basic undo mechanism.
* Handle user commands and invalid input.

---

## 📄 License

This project is created for **educational and academic purposes**.






