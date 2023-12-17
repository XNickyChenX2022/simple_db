#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARGS_SIZE 100

typedef struct programmingLanguage {
	int id;
	char* language;
	int year;
	char* creator;
	char* paradigm;
	double popularityIndex;

	int isDeleted; // internal field, not accessible to user
} language_t;

// step 1: create structs for the other two tables: operatingSystems
// and databases
// include internal field
typedef struct operatingSystem {
    int id;
    char* name;
    int year;
    char* developer;
    char* kernelType;

    int isDeleted;
} os_t;

typedef struct database {
    int id;
    char* name;
    int year;
    char* type;
    char* developer;

    int isDeleted;
} db_t;
// step 2: create typedef struct for storing metadata
typedef struct metadata {
    int count;
    int nextIndex;
    int maxCount;
} md_t;
// step 3: declare the two other arrays of structs
// programmingLanguages has been defined for you already
// TODO: add operatingSystems and databases
language_t* programmingLanguages;
os_t* operatingSystems;
db_t* databases;


// step 4: declare 3 metadata structs, one for each table
md_t* languagesmd;
md_t* operatingSystemsmd;
md_t* databasemd;
// step 5: jump to L167

// void* getTableByName(char* name) {
//     if (strcmp(name, "programmingLanguages") == 0) {
//         return &programmingLanguages;
//     } else if (strcmp(name, "operatingSystems") == 0) {
//         return &operatingSystems;
//     } else if (strcmp(name, "databases") == 0) {
//         return &databases;
//     }
// }

// int getSizeOfTable(char* name) {
//     if (strcmp(name, "programmingLanguages") == 0) {
//         return sizeof(language_t);
//     } else if (strcmp(name, "operatingSystems") == 0) {
//         return sizeof(os_t);
//     } else if (strcmp(name, "databases") == 0) {
//         return sizeof(db_t);
//     }
// }

md_t* getMetaData(char* name) {
    if (strcmp(name, "programmingLanguages") == 0) {
        return languagesmd;
    } else if (strcmp(name, "operatingSystems") == 0) {
        return operatingSystemsmd;
    } else if (strcmp(name, "databases") == 0) {
        return databasemd;
    }
}
void insertLanguageData(char** args, md_t* metaData) {
    language_t* language = calloc(1, sizeof(language_t));  
    language->id = atoi(args[2]);
    language->language = malloc((strlen(args[3]) + 1) * sizeof(char));
    strcpy(language->language, args[3]);
    language->year = atoi(args[4]);
    language->creator =  malloc((strlen(args[5]) + 1) * sizeof(char));
    strcpy(language->creator, args[5]);
    language->paradigm = malloc((strlen(args[6]) + 1) * sizeof(char));
    strcpy(language->paradigm, args[6]);
    char* check;
    language->popularityIndex = strtod(args[7], &check);
    int currIndex = metaData->nextIndex;
    programmingLanguages[currIndex] = *language;
    free(language);
}
void insertOSData(char** args, md_t* metaData) {
    os_t* os = calloc(1, sizeof(os_t));
    os->id = atoi(args[2]);
    os->name = malloc((strlen(args[3]) + 1) * sizeof(char));
    strcpy(os->name, args[3]);
    os->year = atoi(args[4]);
    os->developer =  malloc((strlen(args[5]) + 1) * sizeof(char));
    strcpy(os->developer, args[5]);
    os->kernelType = malloc((strlen(args[6]) + 1) * sizeof(char));
    strcpy(os->kernelType, args[6]);
    int currIndex = metaData->nextIndex;
    operatingSystems[currIndex] = *os;
    free(os);
}
void insertDatabaseData(char** args, md_t* metaData) {
    db_t* db = calloc(1, sizeof(db_t));
    db->id = atoi(args[2]);
    db->name = malloc((strlen(args[3]) + 1) * sizeof(char));
    strcpy(db->name, args[3]);
    db->year = atoi(args[4]);
    db->type =  malloc((strlen(args[5]) + 1) * sizeof(char));
    strcpy(db->type, args[5]);
    db->developer = malloc((strlen(args[6]) + 1) * sizeof(char));
    strcpy(db->developer, args[6]);
    int currIndex = metaData->nextIndex;
    databases[currIndex] = *db;
    free(db);
}

void modifyLanguages(char** args, md_t* metaData, int id){
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        language_t* currLanguage = &programmingLanguages[i];
        if (currLanguage->id == id && currLanguage->isDeleted != 1) {
            free(currLanguage->language);
            free(currLanguage->creator);
            free(currLanguage->paradigm);
            currLanguage->id = atoi(args[3]);
            currLanguage->language = malloc((strlen(args[4]) + 1) * sizeof(char));
            strcpy(currLanguage->language, args[4]);
            currLanguage->year = atoi(args[5]);
            currLanguage->creator =  malloc((strlen(args[6]) + 1) * sizeof(char));
            strcpy(currLanguage->creator, args[6]);
            currLanguage->paradigm = malloc((strlen(args[7]) + 1) * sizeof(char));
            strcpy(currLanguage->paradigm, args[7]);
            char* check;
            currLanguage->popularityIndex = strtod(args[8], &check);
        }
    }
}
void modifyOperatingSystems(char** args, md_t* metaData, int id){
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        os_t* currOS = &operatingSystems[i];
        if (currOS->id == id  && currOS->isDeleted != 1) {
            free(currOS->name);
            free(currOS->developer);
            free(currOS->kernelType);
            currOS->id = atoi(args[3]);
            currOS->name = malloc((strlen(args[4]) + 1) * sizeof(char));
            strcpy(currOS->name, args[4]);
            currOS->year = atoi(args[5]);
            currOS->developer =  malloc((strlen(args[6]) + 1) * sizeof(char));
            strcpy(currOS->developer, args[6]);
            currOS->kernelType = malloc((strlen(args[7]) + 1) * sizeof(char));
            strcpy(currOS->kernelType, args[7]);
        }
    }
}
void modifyDatabases(char** args, md_t* metaData, int id){
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        db_t* currDB = &databases[i];
        if (currDB->id == id && currDB->isDeleted != 1) {
            free(currDB->name);
            free(currDB->type);
            free(currDB->developer);
            currDB->id = atoi(args[3]);
            currDB->name = malloc((strlen(args[4]) + 1) * sizeof(char));
            strcpy(currDB->name, args[4]);
            currDB->year = atoi(args[5]);
            currDB->type =  malloc((strlen(args[6]) + 1) * sizeof(char));
            strcpy(currDB->type, args[6]);
            currDB->developer = malloc((strlen(args[7]) + 1) * sizeof(char));
            strcpy(currDB->developer, args[7]);
        }
    }
}

void deleteLanguages(int id, md_t* metaData){
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        language_t* currLanguage = &programmingLanguages[i];
        if (currLanguage->id == id) {
            currLanguage->isDeleted = 1;
        }
    }
}
void deleteOperatingSystems(int id, md_t* metaData){
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        os_t* currOS = &operatingSystems[i];
        if (currOS->id == id) {
            currOS->isDeleted = 1;
        }
    }
}
void deleteDatabases(int id, md_t* metaData){
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        db_t* currDB = &databases[i];
        if (currDB->id == id) {
            currDB->isDeleted = 1;
        }
    }
}
void getLanguages(md_t* metaData){
    printf("id,language,year,creator,paradigm,popularityIndex\n");
    int count = metaData->count;
    for(int i = 0; i < count; i++) { 
        language_t* currLanguage = &programmingLanguages[i];
        if (currLanguage->isDeleted == 0){
            printf("%i,%s,%i,%s,%s,%lf\n",currLanguage->id,currLanguage->language,
            currLanguage->year,currLanguage->creator,currLanguage->paradigm,
            currLanguage->popularityIndex);
        }
    }
}
void getOperatingSystems(md_t* metaData){
    printf("id,name,year,developer,kernelType\n");
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        os_t* currOS = &operatingSystems[i];
        if (currOS->isDeleted == 0){
            printf("%i,%s,%i,%s,%s\n",currOS->id,currOS->name,currOS->year,
            currOS->developer,currOS->kernelType);
        }
    }
}
void getDatabases(md_t* metaData){
    printf("id,name,year,type,developer\n");
    int count = metaData->count;
    for(int i = 0; i < count; i++) {
        db_t* currDB = &databases[i];
        if (currDB->isDeleted == 0){
            printf("%i,%s,%i,%s,%s\n", currDB->id,currDB->name,currDB->year,
            currDB->type,currDB->developer);
        }
    }
}
// This function takes the user's input and splits it by spaces
// into an array of strings, ignoring spaces that are wrapped in quotes
// There is no need to modify this code.
// You do not need to understand this code
// but you are welcome to research its application
void splitInput(char* input, char** args, int* arg_count) {
    *arg_count = 0;
    int in_quotes = 0; // Flag to track whether we are inside quotes
    char* token_start = input;

    for (char* ptr = input; *ptr != '\0'; ptr++) {
        if (*ptr == '"') {
            in_quotes = !in_quotes; // Toggle the in_quotes flag when a quote is encountered
        }

        if ((*ptr == ' ' || *ptr == '\n') && !in_quotes) {
            // If not inside quotes and a space or newline is found, consider it as a separator
            *ptr = '\0'; // Replace space or newline with null terminator
            args[(*arg_count)++] = token_start;
            token_start = ptr + 1; // Start of the next token
        }
    }

    // Add the last token (if any) after the loop
    if (*token_start != '\0') {
        // Remove leading and trailing double quotes if they exist
        if (token_start[0] == '"' && token_start[strlen(token_start) - 1] == '"') {
            token_start[strlen(token_start) - 1] = '\0'; // Remove trailing quote
            args[(*arg_count)++] = token_start + 1; // Remove leading quote
        } else {
            args[(*arg_count)++] = token_start;
        }
    }
    args[*arg_count] = NULL;
}

// step 7: implement setup function
// this function is responsible for dynamically allocating the
// particular table. Use the tables declared on L27.
void setup(char* table, int numRows) {
    if (strcmp(table, "programmingLanguages") == 0) {
        programmingLanguages = malloc(numRows * sizeof(language_t));
    } else if (strcmp(table, "operatingSystems") == 0) {
        operatingSystems = malloc(numRows * sizeof(os_t));
    } else if (strcmp(table, "databases") == 0) {
        databases = malloc(numRows * sizeof(db_t));
    }
    md_t* metaData = getMetaData(table);
    metaData->maxCount = numRows;
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("setup complete\n");
}

// step 8: implement insert function
// this function is responsible for updating the corresponding
// fields of the struct located at the next available index
// make sure to use and update your metadata.

// autograder print for insufficient capacity:
// fprintf(stderr, "cannot insert due to insufficient capacity.\n");
void insert(char** args) {
    char* tableName = args[1];
    md_t* metaData = getMetaData(tableName);
    if (metaData->count == metaData->maxCount) {
        fprintf(stderr, "cannot insert due to insufficient capacity.\n");
        return;
    }
    if (strcmp(tableName, "programmingLanguages") == 0) {
        insertLanguageData(args, metaData);
    } else if (strcmp(tableName, "operatingSystems") == 0) {
        insertOSData(args, metaData);
    } else if (strcmp(tableName, "databases") == 0) {
        insertDatabaseData(args, metaData);
    }
    metaData->count += 1;
    metaData->nextIndex += 1;
// 	// DO NOT TOUCH THIS PRINT
// 	// REQUIRED FOR AUTOGRADER
	printf("insert complete\n");
}

// step 9: implement soft delete function
// this function is responsible for marking a record as deleted
// you should be updating an internal field flag so that get will
// not display this record. 
// You should not be attempting to free/overwrite this record - it remains alloc
// with a updated field
// make use of your metadata
void delete(char* table, int id) {
    md_t* metaData = getMetaData(table);
    if (strcmp(table, "programmingLanguages") == 0) {
        deleteLanguages(id, metaData);
    } else if (strcmp(table, "operatingSystems") == 0) {
        deleteOperatingSystems(id, metaData);
    } else if (strcmp(table, "databases") == 0) {
        deleteDatabases(id, metaData);
    }
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("delete complete\n");
}

// step 10: implement modify function
// this function is responsible for overwriting all of the contents of all
// records that match an ID.
// make use of your metadata
// !!!NOTE: The structs store pointers. Make sure to free any allocated
// memory before overwriting it!!!
void modify(char** args) {
    char* tableName = args[1];
    md_t* metaData = getMetaData(tableName);
    int id = atoi(args[2]);
    if (strcmp(tableName, "programmingLanguages") == 0) {
        modifyLanguages(args, metaData, id);
    } else if (strcmp(tableName, "operatingSystems") == 0) {
        modifyOperatingSystems(args, metaData, id);
    } else if (strcmp(tableName, "databases") == 0) {
        modifyDatabases(args, metaData, id);
    }
	// DO NOT TOUCH THIS PRINT
	// REQUIRED FOR AUTOGRADER
	printf("modify complete\n");
}

// step 11: implement get function
// this function is responsible for fetching all non-deleted records
// make use of your metadata
// Make sure to follow guidelines for format in writeup
// see examples as well
// Use %lf for formatting double data type
void get(char* table) {
    md_t* metaData = getMetaData(table);
    if (strcmp(table, "programmingLanguages") == 0) {
        getLanguages(metaData);
    } else if (strcmp(table, "operatingSystems") == 0) {
        getOperatingSystems(metaData);
    } else if (strcmp(table, "databases") == 0) {
        getDatabases(metaData);
    }
}

// step 12: implement exit function
// this function should free all allocated memory
// Make sure to avoid memory leaks by freeing any allocated memory
// inside a struct (char*) before freeing the struct pointer
void exitProgram() {
    int maxLanguage = languagesmd->maxCount;
    int maxOS = operatingSystemsmd->maxCount;
    int maxDB = databasemd->maxCount;
    if (maxLanguage != 0) {
        int count = languagesmd->count;
        for(int i = 0; i < count; i ++) {
            free(programmingLanguages[i].language);
            free(programmingLanguages[i].creator);
            free(programmingLanguages[i].paradigm);
        }
        free(programmingLanguages);
    }
    if (maxOS != 0) {
        int count = operatingSystemsmd->count;
        for(int i = 0; i < count; i ++) {
            free(operatingSystems[i].name);
            free(operatingSystems[i].developer);
            free(operatingSystems[i].kernelType);
        }
        free(operatingSystems);
    }
    if (maxDB != 0) {
        int count = databasemd->count;
        for(int i = 0; i < count; i ++) {
            free(databases[i].name);
            free(databases[i].type);
            free(databases[i].developer);
        }
        free(databases);
    }
    free(languagesmd);
    free(operatingSystemsmd);
    free(databasemd);
    
    exit(0);
}

// this code is responsible for parsing the user's
// input, and determining based on the command
// which function to send it to.
// You do not have to modify this code, but you should
// understand it.
void execute_cmd(char** args, int arg_count) {
	char* cmd = args[0];
	if (strcmp(cmd, "setup") == 0) {
		setup(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "insert") == 0) {
		insert(args);
	} else if (strcmp(cmd, "delete") == 0) {
		delete(args[1], atoi(args[2]));
	} else if (strcmp(cmd, "modify") == 0) {
		modify(args);
	} else if (strcmp(cmd, "get") == 0) {
		get(args[1]);
	} else if (strcmp(cmd, "exit") == 0) {
		exitProgram();
	} else {
		printf("\n");
	}
}

// step 6: initialize the default metadata values here
// jump to L76
void initializeMetadata() {
    languagesmd = calloc(1, sizeof(md_t));
    operatingSystemsmd = calloc(1,sizeof(md_t));
    databasemd = calloc(1,sizeof(md_t));
}

// this code creates the interactive shell
// you do not need to modify this
// You do not need to understand this code
// but you are welcome to research its application
void cmd_loop() {
	char input[MAX_INPUT_SIZE];
    ssize_t bytes_read;
	printf("Usage: \n");
	printf("setup {table} {numRows}\n");
	printf("insert {table} {data}\n");
	printf("delete {table} {id}\n");
	printf("modify {table} {id} {data}\n");
	printf("get {table}\n\n");
	initializeMetadata();
    while (1) {
        printf("CS211> ");
		fflush(stdout);
        
        // Read user input using the read() system call
        bytes_read = read(STDIN_FILENO, input, sizeof(input));
        
        if (bytes_read == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        
        if (bytes_read == 0) {
			printf("\n");
            break;
        }
        
        // Null-terminate the input
        input[bytes_read] = '\0';

		char** args = (char**)malloc(MAX_ARGS_SIZE * sizeof(char*));
		int arg_count;

		splitInput(input, args, &arg_count);
        
        // Execute the user's command
        execute_cmd(args, arg_count);
		free(args);
    }
}


int main() {
	cmd_loop();
}