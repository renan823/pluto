#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "types/timestamp.h"
#include "types/types.h"

#include "storage/field.h"

/*
 * 
 */
typedef struct byte_field ByteField;
struct byte_field {
    size_t size;
    char *bytes;
};

/*
 * 
 */
typedef union field_data FieldData;
union field_data {
    bool b;
    int64_t i;
    Timestamp t;
    double d;
    ByteField z;
};

/*
 * 
 */
struct field {
    Types type;
    FieldData data;
};

/*
 * 
 */
size_t _ReadFieldFixedSizeData(FILE *file, FieldData *data, Types type) {
    if (type == T_INT) {
        return fread(&data->i, sizeof(int64_t), 1, file);
    }

    if (type == T_DOUBLE) {
        return fread(&data->d, sizeof(double), 1, file);
    }

    if (type == T_BOOL) {
        return fread(&data->b, sizeof(bool), 1, file);
    }
    
    if (type == T_TIMESTAMP) {
    	return fread(&data->t, sizeof(Timestamp), 1, file);
    }

    return 0;
}

/*
 * 
 */
size_t _ReadFieldVariableSizeData(FILE *file, ByteField *z) {
    // Read size
    if (fread(&(z->size), sizeof(size_t), 1, file) == 0) {
        return 0;
    }

    // Allocate buffer
    z->bytes = (char *)malloc(sizeof(char));
    if (z->bytes == NULL) {
        return 0;
    }

    // Try to read 'size' bytes from the file
    if (fread(z->bytes, sizeof(char), z->size, file) == 0) {
        free(z->bytes);
        return 0;
    }

    return 1;
}

/*
 * 
 */
size_t _WriteFieldFixedSizeData(FILE *file, FieldData *data, Types type) {
    if (type == T_INT) {
        return fwrite(&data->i, sizeof(int64_t), 1, file);
    }

    if (type == T_DOUBLE) {
        return fwrite(&data->d, sizeof(double), 1, file);
    }

    if (type == T_BOOL) {
        return fwrite(&data->b, sizeof(bool), 1, file);
    }
    
    if (type == T_TIMESTAMP) {
    	return fwrite(&data->t, sizeof(Timestamp), 1, file);
    }

    return 0;
}

/*
 * 
 */
size_t _WriteFieldVariableSizeData(FILE *file, ByteField *z) {
    // Write size
    if (fwrite(&(z->size), sizeof(size_t), 1, file) == 0) {
        return 0;
    }
    // Try to write 'size' bytes to the file
    if (fwrite(z->bytes, sizeof(char), z->size, file) == 0) {
        return 0;
    }

    return 1;
}

/*
 * 
 */
Field *ReadField(FILE *file) {
    Field *field = (Field *)malloc(sizeof(Field));
    if (field == NULL) {
        return NULL;
    }

    // Identify field type
    if (fread(&field->type, sizeof(Types), 1, file) == 0) {
        return NULL;
    }

    // Read field data
    if (field->type == T_TEXT) {
        if (_ReadFieldVariableSizeData(file, &field->data.z) == 0) {
            return NULL;
        }
    } else {
    	if (_ReadFieldFixedSizeData(file, &field->data, field->type) == 0) {
            return NULL;
        }
    }

    return field;
}

/*
 * 
 */
size_t WriteField(FILE *file, Field *field) {
	if (field == NULL) {
		return 0;
	}
	
	// Write type
	if (fwrite(&field->type, sizeof(Types), 1, file) == 0) {
		return 0;
	}
	
	// Read field data
    if (field->type == T_TEXT) {
        if (_WriteFieldVariableSizeData(file, &field->data.z) == 0) {
            return 0;
        }
    } else {
    	if (_WriteFieldFixedSizeData(file, &field->data, field->type) == 0) {
            return 0;
        }
    }
	
	return 1;
}