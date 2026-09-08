# Command-Line Line Editor in C

A simple command-line text editor written in C. It supports creating, editing, searching, replacing, saving, loading, and undoing changes.

## Commands

| Command         | Syntax                       | Description                          |
| --------------- | ---------------------------- | ------------------------------------ |
| `append`        | `append <text>`              | Adds a new line at the end           |
| `insert`        | `insert <line> <text>`       | Inserts a line at the given position |
| `delete`        | `delete <line>`              | Deletes the specified line           |
| `display`       | `display`                    | Displays all lines with line numbers |
| `search`        | `search <text>`              | Searches for text in the document    |
| `replace`       | `replace <line> <old> <new>` | Replaces text in one line            |
| `replaceall`    | `replaceall <old> <new>`     | Replaces text in all lines           |
| `count`         | `count`                      | Shows total lines and words          |
| `undo`          | `undo`                       | Reverts the last supported edit      |
| `save`          | `save <filename>`            | Saves the document to a file         |
| `load`          | `load <filename>`            | Loads a document from a file         |
| `help`          | `help`                       | Shows available commands             |
| `exit` / `quit` | `exit`                       | Exits the editor                     |

## Examples

```text
append Hello World
append This is my document

display

insert 1 "Welcome to Line Editor"
delete 2

search "document"

replace 1 "Hello" "Hi"
replaceall "old" "new"

count

save file.txt
load file.txt

undo
```

## Notes

* Line numbers start from `1`.
* Use quotes for text containing spaces.
* Search and replace are case-sensitive.
* The editor supports one level of undo.
* Input is limited to approximately 1023 characters per command.
* The program runs through the command line.

