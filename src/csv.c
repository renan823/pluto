#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "csv.h"

/**/
struct csv_reader {
    FILE *file;
    int cols;
};

/**/
CSVReader *OpenCSV(const char *filename) {
    CSVReader *reader = (CSVReader*) malloc(sizeof(CSVReader));
    if (reader == NULL) {
        return NULL;
    }

    // Open file
    reader->file = fopen(filename, "r");
    if (reader->file == NULL) {
        return NULL;
    }

    reader->cols = 0;

    return reader;
}

/**/
void CloseCSV(CSVReader **reader) {
    if (*reader == NULL) {
        return;
    }

    fclose((*reader)->file);

    free(*reader);
    *reader = NULL;
}

/**/
bool CSVNextLine(CSVReader *reader) {
    return false;
}

/**/
char *CSVReadLine(CSVReader *reader) {
    return NULL;
}