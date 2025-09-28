#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"

/*
Defines the Reader struct for csv files.
*/
struct csv_reader {
    FILE *file;
    int cols;
};

/*
Opens a csv file for read.
Points the new reader to the file start.
*/
CSVReader *OpenCSV(const char *filename) {
    CSVReader *reader = (CSVReader *)malloc(sizeof(CSVReader));
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

/*
Deallocates the reader and close the csv file.
*/
void CloseCSV(CSVReader **reader) {
    if (*reader == NULL) {
        return;
    }

    fclose((*reader)->file);

    free(*reader);
    *reader = NULL;
}

/*
Verifies if the current file has a next line.
*/
bool CSVNextLine(CSVReader *reader) {
	// Not implemented
	
	return false;
}

/*
Reads the next line of the current file.
*/
char *CSVReadLine(CSVReader *reader) {
	// Not implemented
	
	return NULL;
}
