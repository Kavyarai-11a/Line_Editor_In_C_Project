# SIMPLE LINE EDITOR IN C

Team Members:Manasvi,Kavya Rai

SRN:R25EF134,R25EF116

Section:A

Subject:Portfolio Buliding

---

## 1. PROBLEM STATEMENT

Develop a simple **command-line Line Editor in C** that allows the user to create and modify a document one line at a time. The editor should support operations such as inserting, deleting, displaying, saving, and loading lines.

Our implementation also provides additional features such as **search, replace, replace all, undo, and word count**.

---

## 2. DATA STRUCTURE USED

### Dynamic Array of Strings

We use a **dynamic array of strings** to store the lines of the document.

```text
                 DOCUMENT
                    |
          +---------+---------+
          |         |         |
        lines      count   capacity
          |
          ↓
   +------------+
   |  Pointer   | ───→ "Hello World"
   +------------+
   |  Pointer   | ───→ "Welcome to C"
   +------------+
   |  Pointer   | ───→ "Line Editor"
   +------------+
   |  Pointer   |
   +------------+
        ...
```

### Structure

```text
        +----------------------+
        |      Document        |
        +----------------------+
        | char **lines         |
        | int count            |
        | int capacity         |
        +----------------------+
```

**lines** → stores pointers to the text lines
**count** → number of lines currently present
**capacity** → maximum number of line pointers currently allocated

### Why Dynamic Array?

A dynamic array is selected because the number of lines can change during execution. It allows the document to grow dynamically and provides easy access to lines using their line numbers.

---

## 3. BASIC WORKING OF THE EDITOR

```text
                  START
                    ↓
           Initialize Document
                    ↓
             Read User Command
                    ↓
              Parse Command
                    ↓
           Execute Operation
                    ↓
          Update the Document
                    ↓
            Display Result
                    ↓
           Read Next Command
                    ↓
             Exit / Quit?
              ↙       ↘
            NO         YES
            ↓           ↓
      Read Command     END
```

---

# 4. CORE OPERATIONS

## A. INSERT LINE

The user can insert a line at any valid position.

### Example

**Before:**

```text
1 → Hello
2 → Welcome
3 → C Programming
```

Insert `"New Line"` at position 2.

**After:**

```text
1 → Hello
2 → New Line
3 → Welcome
4 → C Programming
```

### Insert Algorithm

```text
Validate line number
        ↓
Allocate memory for new line
        ↓
Check capacity
        ↓
Increase capacity if required
        ↓
Shift existing lines RIGHT
        ↓
Place new line
        ↓
Increase count
```

---

## B. DELETE LINE

The user can delete a line using its line number.

### Example

**Before:**

```text
1 → Hello
2 → New Line
3 → Welcome
```

Delete line 2.

**After:**

```text
1 → Hello
2 → Welcome
```

### Delete Algorithm

```text
Validate line number
        ↓
Free memory of deleted line
        ↓
Shift remaining lines LEFT
        ↓
Decrease count
```

---

## C. DISPLAY DOCUMENT

Displays all current lines with their line numbers.

```text
        Document
           ↓
    Read lines[0]
           ↓
    Print "1: Hello"
           ↓
    Read lines[1]
           ↓
    Print "2: Welcome"
           ↓
          ...
```

### Example

```text
1: Hello World
2: Welcome to C
3: Simple Line Editor
```

---

# 5. SAVE AND LOAD

## SAVE

The document is stored in a text file.

```text
+----------------+
|    DOCUMENT    |
+----------------+
        |
        ↓
   fopen("file","w")
        |
        ↓
   Write each line
        |
        ↓
   fclose()
        |
        ↓
    FILE SAVED
```

## LOAD

The document is read from a text file.

```text
+----------------+
|      FILE      |
+----------------+
        |
        ↓
   fopen("file","r")
        |
        ↓
    Read lines
        |
        ↓
   Create Document
        |
        ↓
      fclose()
        |
        ↓
 DOCUMENT LOADED
```

---

# 6. BONUS FEATURES

Our editor also supports:

```text
+--------------------------------+
|        BONUS FEATURES          |
+--------------------------------+
| ✓ Search                       |
| ✓ Replace text                 |
| ✓ Replace All                  |
| ✓ Undo last modification       |
| ✓ Word Count                   |
+--------------------------------+
```

### Search

Searches for a word or phrase and displays the line numbers where it occurs.

```text
search Hello
        ↓
Check every line
        ↓
Find matching text
        ↓
Display line number
```

### Replace

Replaces specified text in a selected line.

```text
replace 2 old new
```

### Replace All

Replaces text throughout the entire document.

```text
replaceall old new
```

### Undo

The editor stores a previous copy of the document and can restore it using:

```text
undo
```

The implementation provides **one level of undo**.

### Word Count

Counts the total number of words present in the document.

```text
count
        ↓
Scan all lines
        ↓
Identify words
        ↓
Display total count
```

---

# 7. MEMORY MANAGEMENT

The editor uses dynamic memory allocation.

```text
        malloc()
           ↓
    Allocate memory
           ↓
       Store line
           ↓
    Document grows
           ↓
       realloc()
           ↓
 Increase capacity
           ↓
        free()
           ↓
 Release memory
```

### Functions Used

| Function    | Purpose                  |
| ----------- | ------------------------ |
| `malloc()`  | Allocate memory          |
| `realloc()` | Increase array capacity  |
| `free()`    | Release allocated memory |

When the array becomes full, its capacity is increased dynamically.

---

# 8. COMMANDS

```text
+------------------------------------------------+
| Command | Purpose                              |
+------------------------------------------------+
| append  | Add line at the end                 |
| insert  | Insert line at a position           |
| delete  | Delete a line                       |
| display | Display document                    |
| save    | Save document to a file             |
| load    | Load document from a file           |
| search  | Search for text                     |
| replace | Replace text in a line              |
| replaceall | Replace text everywhere           |
| undo    | Undo last modification              |
| count   | Count total words                   |
| help    | Display available commands         |
| exit    | Exit the editor                     |
+------------------------------------------------+
```

---

# 9. TIME COMPLEXITY

| Operation | Complexity         |
| --------- | ------------------ |
| Append    | O(1) amortized     |
| Insert    | O(n)               |
| Delete    | O(n)               |
| Display   | O(n)               |
| Search    | O(n) approximately |
| Save      | O(n)               |
| Load      | O(n)               |

Here, **n represents the number of lines in the document.**

---

# 10. ERROR HANDLING

The editor handles:

```text
✓ Invalid line numbers
✓ Empty document
✓ Deleting from an empty document
✓ Missing command arguments
✓ Invalid commands
✓ File opening errors
✓ Memory allocation failures
✓ Empty search/replace targets
```

---

## 11. OVERALL DESIGN

```text
                    SIMPLE LINE EDITOR
                           |
             +-------------+-------------+
             |             |             |
          INSERT        DELETE        DISPLAY
             |             |             |
             +-------------+-------------+
                           |
                     SAVE / LOAD
                           |
             +-------------+-------------+
             |             |             |
          SEARCH        REPLACE         UNDO
                           |
                       WORD COUNT
```

### Conclusion

The **Simple Line Editor in C** demonstrates the use of **dynamic arrays, pointers, structures, dynamic memory allocation, string manipulation, file handling, and command parsing** to create a functional command-line text editor.
