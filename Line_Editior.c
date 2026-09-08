#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define INITIAL_CAPACITY 10
#define MAX_BUFFER_SIZE 1024

typedef struct {
    char **lines;
    int count;
    int capacity;
} Document;

/* Function Declarations */
void init_document(Document *doc);
void free_document(Document *doc);
int append_line(Document *doc, const char *text);
void display_document(const Document *doc);
int save_document(const Document *doc, const char *filename);
int load_document(Document *doc, const char *filename);
void search_document(const Document *doc, const char *query);
char *replace_in_string(const char *src, const char *old_text,
                        const char *new_text, int *count_out);
int replace_in_line(Document *doc, int line_num,
                    const char *old_text, const char *new_text);
int replace_all(Document *doc, const char *old_text, const char *new_text);
void print_help(void);
void trim_trailing_whitespace(char *str);
int parse_tokens(char *input, char *tokens[], int max_tokens);
const char *get_command_argument(const char *input_buffer);


/* -------------------------------------------------------------------------- */
/* Main Program                                                               */
/* -------------------------------------------------------------------------- */

int main(void)
{
    Document doc;
    init_document(&doc);

    char input_buffer[MAX_BUFFER_SIZE];
    char parse_copy[MAX_BUFFER_SIZE];
    char *tokens[10];

    printf("=======================================================\n");
    printf("        Command-Line Line Editor in C (Standard)       \n");
    printf("=======================================================\n");
    printf("Type 'help' to view available commands.\n\n");

    while (1) {
        printf("line-editor> ");

        if (!fgets(input_buffer, sizeof(input_buffer), stdin)) {
            break;
        }

        trim_trailing_whitespace(input_buffer);

        if (input_buffer[0] == '\0') {
            continue;
        }

        /*
         * parse_tokens() modifies its input string.
         * Therefore, use a copy so input_buffer remains unchanged.
         */
        strcpy(parse_copy, input_buffer);

        int token_count = parse_tokens(parse_copy, tokens, 10);

        if (token_count == 0) {
            continue;
        }

        char *cmd = tokens[0];

        /* Convert command to lowercase */
        for (int i = 0; cmd[i] != '\0'; i++) {
            cmd[i] = (char)tolower((unsigned char)cmd[i]);
        }


        /* ---------------- EXIT / QUIT ---------------- */

        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
            printf("Exiting Line Editor. Goodbye!\n");
            break;
        }


        /* ---------------- HELP ---------------- */

        else if (strcmp(cmd, "help") == 0) {
            if (token_count != 1) {
                printf("Usage: help\n");
            } else {
                print_help();
            }
        }


        /* ---------------- DISPLAY ---------------- */

        else if (strcmp(cmd, "display") == 0) {
            if (token_count != 1) {
                printf("Usage: display\n");
            } else {
                display_document(&doc);
            }
        }


        /* ---------------- APPEND ---------------- */

        else if (strcmp(cmd, "append") == 0 ||
                 strcmp(cmd, "add") == 0) {

            const char *arg_text = get_command_argument(input_buffer);

            if (!arg_text || *arg_text == '\0') {
                printf("Error: Missing text to append. Usage: append <text>\n");
            } else {
                if (append_line(&doc, arg_text)) {
                    printf("Line %d added.\n", doc.count);
                } else {
                    printf("Error: Could not add line.\n");
                }
            }
        }


        /* ---------------- SAVE ---------------- */

        else if (strcmp(cmd, "save") == 0) {

            if (token_count != 2) {
                printf("Error: Usage: save <filename>\n");
            } else {
                save_document(&doc, tokens[1]);
            }
        }


        /* ---------------- LOAD ---------------- */

        else if (strcmp(cmd, "load") == 0) {

            if (token_count != 2) {
                printf("Error: Usage: load <filename>\n");
            } else {
                load_document(&doc, tokens[1]);
            }
        }


        /* ---------------- SEARCH ---------------- */

        else if (strcmp(cmd, "search") == 0) {

            const char *query = get_command_argument(input_buffer);

            if (!query || *query == '\0') {
                printf("Error: Missing search term. Usage: search <word_or_phrase>\n");
            } else {
                search_document(&doc, query);
            }
        }


        /* ---------------- REPLACE ---------------- */

        else if (strcmp(cmd, "replace") == 0) {

            if (token_count != 4) {
                printf("Error: Usage: replace <line_number> <old_text> <new_text>\n");
                printf("Tip: Use quotes for multi-word phrases.\n");
                printf("Example: replace 1 \"old word\" \"new word\"\n");
            } else {

                char *endptr;
                long line_value = strtol(tokens[1], &endptr, 10);

                if (*tokens[1] == '\0' ||
                    *endptr != '\0' ||
                    line_value < 1 ||
                    line_value > 2147483647L) {

                    printf("Error: Invalid line number '%s'.\n", tokens[1]);
                } else {

                    replace_in_line(
                        &doc,
                        (int)line_value,
                        tokens[2],
                        tokens[3]
                    );
                }
            }
        }


        /* ---------------- REPLACE ALL ---------------- */

        else if (strcmp(cmd, "replaceall") == 0) {

            if (token_count != 3) {
                printf("Error: Usage: replaceall <old_text> <new_text>\n");
                printf("Tip: Use quotes for multi-word phrases.\n");
                printf("Example: replaceall \"old text\" \"new text\"\n");
            } else {
                replace_all(&doc, tokens[1], tokens[2]);
            }
        }


        /* ---------------- UNKNOWN COMMAND ---------------- */

        else {
            printf("Unknown command '%s'. Type 'help' for a list of valid commands.\n",
                   cmd);
        }
    }

    free_document(&doc);

    return 0;
}


/* -------------------------------------------------------------------------- */
/* Document & Memory Management                                               */
/* -------------------------------------------------------------------------- */

void init_document(Document *doc)
{
    doc->count = 0;
    doc->capacity = INITIAL_CAPACITY;

    doc->lines = malloc(doc->capacity * sizeof(char *));

    if (!doc->lines) {
        fprintf(stderr,
                "Fatal Memory Error: Failed to allocate document.\n");
        exit(EXIT_FAILURE);
    }
}


void free_document(Document *doc)
{
    if (doc == NULL) {
        return;
    }

    if (doc->lines != NULL) {

        for (int i = 0; i < doc->count; i++) {
            free(doc->lines[i]);
        }

        free(doc->lines);
        doc->lines = NULL;
    }

    doc->count = 0;
    doc->capacity = 0;
}


/* -------------------------------------------------------------------------- */
/* Append Line                                                                */
/* -------------------------------------------------------------------------- */

int append_line(Document *doc, const char *text)
{
    if (doc == NULL || text == NULL) {
        return 0;
    }

    /* Expand pointer array if necessary */
    if (doc->count >= doc->capacity) {

        int new_capacity = doc->capacity * 2;

        char **new_lines =
            realloc(doc->lines, new_capacity * sizeof(char *));

        if (!new_lines) {
            fprintf(stderr,
                    "Memory Error: Failed to expand document.\n");
            return 0;
        }

        doc->lines = new_lines;
        doc->capacity = new_capacity;
    }

    size_t len = strlen(text);

    char *new_line = malloc(len + 1);

    if (!new_line) {
        fprintf(stderr,
                "Memory Error: Failed to allocate memory for line.\n");
        return 0;
    }

    strcpy(new_line, text);

    doc->lines[doc->count] = new_line;
    doc->count++;

    return 1;
}


/* -------------------------------------------------------------------------- */
/* Display Document                                                           */
/* -------------------------------------------------------------------------- */

void display_document(const Document *doc)
{
    if (doc->count == 0) {
        printf("(The document is currently empty)\n");
        return;
    }

    printf("\n--- Document Start (%d line%s) ---\n",
           doc->count,
           doc->count == 1 ? "" : "s");

    for (int i = 0; i < doc->count; i++) {
        printf("%d. %s\n", i + 1, doc->lines[i]);
    }

    printf("--- Document End ---\n\n");
}


/* -------------------------------------------------------------------------- */
/* Save Document                                                              */
/* -------------------------------------------------------------------------- */

int save_document(const Document *doc, const char *filename)
{
    FILE *fp = fopen(filename, "w");

    if (!fp) {
        printf("Error: Could not open file '%s' for writing.\n",
               filename);
        return 0;
    }

    for (int i = 0; i < doc->count; i++) {

        if (fprintf(fp, "%s\n", doc->lines[i]) < 0) {
            printf("Error: Failed while writing to '%s'.\n", filename);
            fclose(fp);
            return 0;
        }
    }

    if (fclose(fp) != 0) {
        printf("Error: Failed to close file '%s'.\n", filename);
        return 0;
    }

    printf("Successfully saved %d line(s) to '%s'.\n",
           doc->count,
           filename);

    return 1;
}


/* -------------------------------------------------------------------------- */
/* Load Document                                                              */
/* -------------------------------------------------------------------------- */

int load_document(Document *doc, const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (!fp) {
        printf("Error: Could not open file '%s' for reading.\n",
               filename);
        return 0;
    }

    /*
     * First create a temporary document.
     * This prevents losing the current document if loading fails.
     */
    Document temp;
    init_document(&temp);

    char buffer[MAX_BUFFER_SIZE];
    int lines_loaded = 0;

    while (fgets(buffer, sizeof(buffer), fp)) {

        trim_trailing_whitespace(buffer);

        if (!append_line(&temp, buffer)) {
            printf("Error: Memory allocation failed while loading line %d.\n",
                   lines_loaded + 1);

            free_document(&temp);
            fclose(fp);

            return 0;
        }

        lines_loaded++;
    }

    if (ferror(fp)) {
        printf("Error: Failed while reading '%s'.\n", filename);

        free_document(&temp);
        fclose(fp);

        return 0;
    }

    fclose(fp);

    /* Loading succeeded, so replace old document */
    free_document(doc);

    *doc = temp;

    printf("Successfully loaded %d line(s) from '%s'.\n",
           lines_loaded,
           filename);

    return 1;
}


/* -------------------------------------------------------------------------- */
/* Search                                                                     */
/* -------------------------------------------------------------------------- */

void search_document(const Document *doc, const char *query)
{
    if (doc->count == 0) {
        printf("Document is empty. Nothing to search.\n");
        return;
    }

    if (query == NULL || *query == '\0') {
        printf("Error: Search query cannot be empty.\n");
        return;
    }

    char clean_query[MAX_BUFFER_SIZE];

    strncpy(clean_query, query, MAX_BUFFER_SIZE - 1);
    clean_query[MAX_BUFFER_SIZE - 1] = '\0';

    /*
     * get_command_argument() normally removes quotes,
     * but keep this check for safety.
     */
    size_t qlen = strlen(clean_query);

    if (qlen >= 2 &&
        clean_query[0] == '"' &&
        clean_query[qlen - 1] == '"') {

        clean_query[qlen - 1] = '\0';

        memmove(
            clean_query,
            clean_query + 1,
            qlen
        );
    }

    if (clean_query[0] == '\0') {
        printf("Error: Search query cannot be empty.\n");
        return;
    }

    int match_count = 0;

    for (int i = 0; i < doc->count; i++) {

        if (strstr(doc->lines[i], clean_query) != NULL) {
            printf("Found in line %d\n", i + 1);
            match_count++;
        }
    }

    if (match_count == 0) {
        printf("Phrase \"%s\" was not found in the document.\n",
               clean_query);
    } else {
        printf("Found in %d line(s).\n", match_count);
    }
}


/* -------------------------------------------------------------------------- */
/* Replace String                                                             */
/* -------------------------------------------------------------------------- */

char *replace_in_string(const char *src,
                        const char *old_text,
                        const char *new_text,
                        int *count_out)
{
    if (count_out == NULL) {
        return NULL;
    }

    *count_out = 0;

    if (src == NULL || old_text == NULL || new_text == NULL) {
        return NULL;
    }

    size_t old_len = strlen(old_text);
    size_t new_len = strlen(new_text);
    size_t src_len = strlen(src);

    /* Empty old text is not a valid replacement target */
    if (old_len == 0) {

        char *copy = malloc(src_len + 1);

        if (copy) {
            strcpy(copy, src);
        }

        return copy;
    }


    /* Count occurrences */
    size_t occurrences = 0;
    const char *tmp = src;

    while ((tmp = strstr(tmp, old_text)) != NULL) {

        occurrences++;

        tmp += old_len;
    }


    /* No match */
    if (occurrences == 0) {

        char *copy = malloc(src_len + 1);

        if (copy) {
            strcpy(copy, src);
        }

        return copy;
    }


    /*
     * Calculate resulting length safely.
     *
     * If new text is longer:
     *     src_len + occurrences * (new_len - old_len)
     *
     * If new text is shorter:
     *     src_len - occurrences * (old_len - new_len)
     */
    size_t result_len;

    if (new_len >= old_len) {

        size_t increase = new_len - old_len;

        if (occurrences > (SIZE_MAX - src_len) / increase) {
            fprintf(stderr,
                    "Memory Error: Replacement string is too large.\n");
            return NULL;
        }

        result_len = src_len + occurrences * increase;

    } else {

        size_t decrease = old_len - new_len;

        if (occurrences * decrease > src_len) {
            fprintf(stderr,
                    "Memory Error: Invalid replacement size.\n");
            return NULL;
        }

        result_len = src_len - occurrences * decrease;
    }


    char *result = malloc(result_len + 1);

    if (!result) {
        fprintf(stderr,
                "Memory Error: Failed to allocate replacement buffer.\n");
        return NULL;
    }


    /* Perform replacement */
    const char *p = src;
    char *q = result;

    while (*p != '\0') {

        if (strncmp(p, old_text, old_len) == 0) {

            if (new_len > 0) {
                memcpy(q, new_text, new_len);
                q += new_len;
            }

            p += old_len;
            (*count_out)++;

        } else {

            *q = *p;
            q++;
            p++;
        }
    }

    *q = '\0';

    return result;
}


/* -------------------------------------------------------------------------- */
/* Replace In One Line                                                        */
/* -------------------------------------------------------------------------- */

int replace_in_line(Document *doc,
                    int line_num,
                    const char *old_text,
                    const char *new_text)
{
    if (doc->count == 0) {
        printf("Error: Document is empty.\n");
        return 0;
    }

    if (line_num < 1 || line_num > doc->count) {
        printf("Error: Invalid line number %d. Valid range is 1 to %d.\n",
               line_num,
               doc->count);
        return 0;
    }

    if (old_text == NULL || old_text[0] == '\0') {
        printf("Error: Old text cannot be empty.\n");
        return 0;
    }

    if (new_text == NULL) {
        new_text = "";
    }

    int idx = line_num - 1;
    int replacements = 0;

    char *new_line =
        replace_in_string(
            doc->lines[idx],
            old_text,
            new_text,
            &replacements
        );

    if (!new_line) {
        printf("Error: Replacement failed due to memory error.\n");
        return 0;
    }

    if (replacements > 0) {

        free(doc->lines[idx]);

        doc->lines[idx] = new_line;

        printf("Replaced %d occurrence(s) on line %d.\n",
               replacements,
               line_num);

    } else {

        free(new_line);

        printf("Phrase \"%s\" was not found on line %d.\n",
               old_text,
               line_num);
    }

    return replacements;
}


/* -------------------------------------------------------------------------- */
/* Replace All                                                                */
/* -------------------------------------------------------------------------- */

int replace_all(Document *doc,
                const char *old_text,
                const char *new_text)
{
    if (doc->count == 0) {
        printf("Error: Document is empty.\n");
        return 0;
    }

    if (old_text == NULL || old_text[0] == '\0') {
        printf("Error: Old text cannot be empty.\n");
        return 0;
    }

    if (new_text == NULL) {
        new_text = "";
    }

    int total_replacements = 0;
    int lines_affected = 0;

    for (int i = 0; i < doc->count; i++) {

        int line_replacements = 0;

        char *new_line =
            replace_in_string(
                doc->lines[i],
                old_text,
                new_text,
                &line_replacements
            );

        if (!new_line) {
            printf("Error: Replacement failed on line %d.\n", i + 1);
            return 0;
        }

        if (line_replacements > 0) {

            free(doc->lines[i]);

            doc->lines[i] = new_line;

            total_replacements += line_replacements;
            lines_affected++;

        } else {

            free(new_line);
        }
    }

    if (total_replacements > 0) {

        printf("Replaced %d occurrence(s) across %d line(s).\n",
               total_replacements,
               lines_affected);

    } else {

        printf("Phrase \"%s\" was not found anywhere in the document.\n",
               old_text);
    }

    return total_replacements;
}


/* -------------------------------------------------------------------------- */
/* Trim Whitespace                                                            */
/* -------------------------------------------------------------------------- */

void trim_trailing_whitespace(char *str)
{
    if (!str) {
        return;
    }

    size_t len = strlen(str);

    while (len > 0 &&
           isspace((unsigned char)str[len - 1])) {

        str[len - 1] = '\0';
        len--;
    }
}


/* -------------------------------------------------------------------------- */
/* Get Command Argument                                                       */
/* -------------------------------------------------------------------------- */

const char *get_command_argument(const char *input_buffer)
{
    static char argument[MAX_BUFFER_SIZE];

    if (input_buffer == NULL) {
        return NULL;
    }

    const char *p = input_buffer;

    /* Skip command */
    while (*p && !isspace((unsigned char)*p)) {
        p++;
    }

    /* Skip spaces after command */
    while (*p && isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '\0') {
        argument[0] = '\0';
        return argument;
    }

    /*
     * Copy the entire argument.
     * This allows append/search to accept spaces.
     */
    strncpy(argument, p, MAX_BUFFER_SIZE - 1);
    argument[MAX_BUFFER_SIZE - 1] = '\0';

    size_t len = strlen(argument);

    /*
     * Remove surrounding quotes.
     *
     * Example:
     * append "hello world"
     *
     * becomes:
     * hello world
     */
    if (len >= 2 &&
        argument[0] == '"' &&
        argument[len - 1] == '"') {

        argument[len - 1] = '\0';

        memmove(
            argument,
            argument + 1,
            len
        );
    }

    return argument;
}


/* -------------------------------------------------------------------------- */
/* Tokenizer                                                                  */
/* -------------------------------------------------------------------------- */

int parse_tokens(char *input,
                 char *tokens[],
                 int max_tokens)
{
    int count = 0;
    char *p = input;

    while (*p && count < max_tokens) {

        /* Skip whitespace */
        while (*p && isspace((unsigned char)*p)) {
            p++;
        }

        if (!*p) {
            break;
        }

        /*
         * Quoted token
         *
         * Example:
         * "hello world"
         *
         * becomes one token:
         * hello world
         */
        if (*p == '"') {

            p++;

            tokens[count++] = p;

            while (*p && *p != '"') {
                p++;
            }

            if (*p == '"') {
                *p = '\0';
                p++;
            }

        } else {

            tokens[count++] = p;

            while (*p && !isspace((unsigned char)*p)) {
                p++;
            }

            if (*p) {
                *p = '\0';
                p++;
            }
        }
    }

    return count;
}


/* -------------------------------------------------------------------------- */
/* Help                                                                       */
/* -------------------------------------------------------------------------- */

void print_help(void)
{
    printf("\nAvailable Commands:\n");

    printf("  append <text>                           "
           "Add a new line of text at the end\n");

    printf("  display                                 "
           "Display all lines with line numbers\n");

    printf("  save <filename>                         "
           "Save document to a text file\n");

    printf("  load <filename>                         "
           "Load document from a text file\n");

    printf("  search <word_or_phrase>                 "
           "Find all lines containing phrase\n");

    printf("  replace <line_num> <old> <new>          "
           "Replace phrase on a specific line\n");

    printf("  replaceall <old> <new>                  "
           "Replace phrase across all lines\n");

    printf("  help                                    "
           "Show this help message\n");

    printf("  exit / quit                             "
           "Exit the line editor\n");

    printf("\nExamples:\n");

    printf("  append Hello world\n");
    printf("  append \"This is one complete line\"\n");
    printf("  search \"Hello world\"\n");
    printf("  replace 1 \"old text\" \"new text\"\n");
    printf("  replaceall \"old text\" \"new text\"\n");

    printf("\n");
}


