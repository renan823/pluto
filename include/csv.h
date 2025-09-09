#ifndef CSV_H_
    #define CSV_H_

    #include <stdbool.h>

    typedef struct csv_reader CSVReader;

    CSVReader *OpenCSV(const char *filename);
    void CloseCSV(CSVReader **reader);

    bool CSVNextLine(CSVReader *reader);

    char *CSVReadLine(CSVReader *reader);
#endif