# Line_Editor_In_C_Project

# Command-Line Line Editor in C

A lightweight, interactive command-line line editor written in standard C. This application allows users to create, view, edit, search, and save text documents using a simple line-based interface with dynamic memory management.

---

## Features

- **Dynamic Document Allocation**: Automatically expands document storage as new lines are added.
- **Line Editing & Replacement**: Replace occurrences of text on specific lines or globally across the entire document.
- **Search Functionality**: Quickly locate lines containing specific keywords or multi-word phrases.
- **File I/O Support**: Save current documents to external text files and load existing files into the editor.
- **Quoted Arguments**: Supports multi-word search queries and replacements using double quotes (`"..."`).

---

## Usage & Commands

Run the compiled executable and enter any of the following commands at the `line-editor>` prompt:

| Command             | Usage                            | Description                                             |
| :------------------ | :------------------------------- | :------------------------------------------------------ |
| **`append`**        | `append <text>`                  | Adds a new line of text to the end of the document.     |
| **`display`**       | `display`                        | Displays all document lines with their line numbers.    |
| **`search`**        | `search <word_or_phrase>`        | Searches for and lists all lines containing the phrase. |
| **`replace`**       | `replace <line_num> <old> <new>` | Replaces target text on a specific line number.         |
| **`replaceall`**    | `replaceall <old> <new>`         | Replaces target text across all lines in the document.  |
| **`save`**          | `save <filename>`                | Saves the current document to a file.                   |
| **`load`**          | `load <filename>`                | Loads content from a text file into the document.       |
| **`help`**          | `help`                           | Shows available commands and usage examples.            |
| **`exit` / `quit`** | `exit`                           | Exits the editor program.                               |

---

## Examples

```bash
line-editor> append "Hello world, this is line one."
Line 1 added.

line-editor> append "This is line two."
Line 2 added.

line-editor> display

--- Document Start (2 lines) ---
1. Hello world, this is line one.
2. This is line two.
--- Document End ---

line-editor> replace 1 "line one" "the first line"
Replaced 1 occurrence(s) on line 1.

line-editor> replaceall "line" "row"
Replaced 2 occurrence(s) across 2 line(s).

line-editor> save output.txt
Successfully saved 2 line(s) to 'output.txt'.

line-editor> exit
Exiting Line Editor. Goodbye!
```
