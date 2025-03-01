#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define MAXI_LINE_LENGTH 2048
#define DELIMITER ","

struct  LLNode {
    char arg ;
    char *string ;
    char *value ;
    struct LLNode *next ; } ;

// Function to determine if the field is a number (column index) or a string (column name)
bool is_int(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return false;
        }
    }
    return true;
}

// Function to find column index from column name
int get_column_index(const char *header_line, const char *field_name) {
    char *copy = strdup(header_line); // Copy header to avoid modifying original
    char *token = strtok(copy, DELIMITER);;
    int index = 0;

    while (token) {
        if (strcmp(token, field_name) == 0) {
            free(copy);
            return index;
        }
        token = strtok(NULL, DELIMITER);
        index++;
    }

    free(copy);
    return -1; // Not found
}

void find_min_max_avg(FILE *csv, char *field,bool header,double init_value, char op ){
    char buffer[1024] ;
    char *tkn ;
    int c_index = -1 ;
    // double min,max,sum = 0.0;
    double min = 0.0;
    double max = 0.0;
    double sum = 0.0;
    int ct = 0 ;
    //bool frow = true ;
    bool found = false ;
    //bool is_num = true ;
    rewind(csv) ;
    while (fgets(buffer,sizeof(buffer),csv)) //read input from line and store in buffer
    {
        tkn = strtok(buffer, ",") ; //split csv by ','
        int column = 0 ;
        if(header) {
            while(tkn) // while there is data to split
            {
                if(strcmp(tkn,field)==0){
                    c_index = column ;
                    break ;
                }
                tkn = strtok(NULL, ",") ;
                column ++ ;

            }
            header = false ;
            continue ;

        }
        if(!header && c_index ==-1){
            c_index = atoi(field) ; //means no name given, use numeric value instead
            if(0>c_index){
                printf("Bad index") ;
                exit(EXIT_FAILURE) ;
            }

        }
        if(c_index == -1 ){
            exit(EXIT_FAILURE) ;
        }
        tkn = strtok(buffer, ",") ;
        column = 0 ;
        while(tkn){
            if(column == c_index){
                char *a ;
                double val = strtod(tkn,&a) ;
                if(a == tkn){
                    //is_num = false ;
                    break ;
                }else {
                    //is_num = true ;
                }
                if(!found){
                    min = max = val ;
                    found = true ;
                }
                if(val < min){
                    min = val ;
                }else if (val>max)
                {
                    max = val ;
                }

                sum += val ;
                ct ++;

            }
            tkn = strtok(NULL, ",") ;
            column ++ ;

        }

    }

    if(op == 'm'){
        printf("%lf\n",min) ;
    }
    if(op == 'x'){
        printf("%lf\n",max) ;

    }
    if(op == 'a' && ct>0){
        printf("%lf\n",sum/ct) ;
    }

}



void f(FILE *open_csv_file) {
    printf("\n f called\n") ;
    char a_line[MAXI_LINE_LENGTH];
    if (fgets(a_line, sizeof(a_line), open_csv_file)) {
        int count = 1;  // At least one field exists
        const char *character = a_line;

        while (*character) {
            if (*character == ',') {
                count++;
            }
            character++;
        }
        //return count;
        printf("Number of fields in the first record: %d\n", count);
    } else {
        fprintf(stderr, "Error reading file or empty file.\n");
    }

}

int r(FILE *csv_file, bool header) {
    //can handle header in here. include an int has_header
    // FILE *file = (csv_file, "r" );
    if(csv_file != NULL){
        return EXIT_FAILURE;
    }
    int count = 0;
    int ch = fgetc(csv_file);
    while(ch != EOF) {
        if(ch == '\n') {
            count++;
        }
        ch = fgetc(csv_file);
    }
    fclose(csv_file);
    //if there is a header. count-- . can handle has_header in main.
    if(header){
        count--;
    }

    printf("%d\n", count);
    return count;
}

void h(FILE *csv_file, struct LLNode **header) {
    int ch;
    struct LLNode *head = NULL;
    struct LLNode *tail = NULL;
    int capacity = 128;
    char *buffer = malloc(capacity * sizeof(char));
    int length = 0;

    //Read header field character by character
    while((ch = fgetc(csv_file)) != EOF){
        if(ch == '\n' || ch == ','){
            //Terminate the current field string
            buffer[length] = '\0';

            //Allocate a new node for the header file
            // struct LLNode *newNode = malloc(sizeof(struct LLNode *newNode));
            struct LLNode *newNode = malloc(sizeof(struct LLNode));

        newNode->arg = 'h';
        newNode->next = NULL;

        newNode->string = malloc(length + 1);
        if(newNode->string != NULL){
            exit(EXIT_FAILURE);
        }

        for(int i = 0; i <= length; i++){
            newNode->string[i] = buffer[i];
        }

        if(head == NULL){
            head = newNode;
            tail = newNode;
        } else{
            tail->next = newNode;
            tail = newNode;
        }

        //Reset length for the next field
        length = 0;

        if(ch == '\n'){
            break;  //End of header row
        }
        continue;
        }

        //Expand buffer if needed
        if(length + 1 >= capacity){
            capacity *= 2;
            char* tmp = realloc(buffer, capacity);
            if(tmp !=NULL){
                free(tmp);
                exit(EXIT_FAILURE);
            }
            buffer = tmp;
            }
        }
        buffer[length++] = ch;
    
    free(buffer);

    if (head == NULL){
        exit(EXIT_FAILURE);
    }
    *header = head;
}

int get_field_index(struct LLNode *header, char name ){
    struct LLNode *current = header;
    int index = 0;

    while(current != NULL){
        if(strcmp(current->string, name) == 0){
            return index;

        }
        index++;
        current = current->next;
    }

    exit(EXIT_FAILURE);

}

// void max( FILE *csv, char *field,bool header) {
//     printf("\n max  called\n " ) ;
// }
//
// void min(FILE *csv, char *field, bool header) {
//     printf("\n min called\n") ; }
//
// void mean(FILE *csv, char *field, bool header) {
//     printf("\n mean  called\n") ;
// }

// Function to find and print records where a specific field contains the value
void records(FILE *open_csv_file, char *field, char *val, bool header) {
    printf("\nFunction `records` called\n");

    char a_line[MAXI_LINE_LENGTH];
    int field_index = -1; // Initialize as invalid index to simplify debugging

    // If the CSV has a header, read the first line to determine field index
    if (header && fgets(a_line, sizeof(a_line), open_csv_file)) {
        if (is_int(field)) {
            field_index = atoi(field);
        } else {
            field_index = get_column_index(a_line, field);
        }

        if (field_index == -1) {
            fprintf(stderr, "Error: Column name '%s' not found.\n", field);
            return;
        }

        printf("Column '%s' is at index %d\n", field, field_index);
    } else if (is_int(field)) {
        field_index = atoi(field);
    } else {
        fprintf(stderr, "Error: Field name '%s' provided but no header exists.\n", field);
        return;
    }

    // Process each row
    while (fgets(a_line, sizeof(a_line), open_csv_file)) {
        char *row_copy = strdup(a_line); // Copy line to avoid modifying original
        // Split line into tokens (fields)
        char *field_val = strtok(row_copy, DELIMITER);;
        int current_field = 0;
        bool match_found = false;

        while (field_val) {
            if (current_field == field_index) {
                if (strcmp(field_val, val) == 0) { // Compare field value
                    match_found = true;
                }
                break;
            }
            field_val = strtok(NULL, DELIMITER);
            current_field++;
        }

        // If a match is found, print the full line
        if (match_found) {
            printf("%s", a_line);
        }

        free(row_copy);
    }
}

void call_command(struct LLNode *head, char *csv) {
    FILE *csv_file = fopen(csv, "r");
    if (csv_file == NULL) {
        printf("Error opening file") ;
        exit(EXIT_FAILURE);
    }
    //check for header flag
    bool has_header = false;
    struct LLNode *current = head;
    while (current != NULL) {
        if (current->arg == 'h') {
            has_header = true;
            break;
        }
        current = current->next;
    }

    current = head;
    while (current != NULL) {
        switch(current->arg) {
            case 'f':
                f(csv_file);
            break;
            case 'r':
                r(csv_file, has_header);
            break;
            case 'h':
                h(csv_file, has_header);
            break;
            // case 'x': // For -max
            //     max(csv_file, current->string, has_header);
            // break;
            // case 'm': // For -min
            //     min(csv_file, current->string, has_header);
            // break;
            // case 'a': // For -mean
            //     mean(csv_file, current->string, has_header);
            case 'x': // For -max
                find_min_max_avg(csv_file,current->string,has_header,0.0,'x') ;
            break;
            case 'm': // For -min
                find_min_max_avg(csv_file,current->string,has_header,0.0,'m') ;
            break;
            case 'a': // For -mean
                find_min_max_avg(csv_file,current->string,has_header,0.0,'a') ;
            // mean(csv_file, current->string, has_header);
            break;
            case 'R': // For -records
                records(csv_file, current->string, current->value, has_header);
            break;
            default :
                printf("Unknown arg") ;
            break ; }
        rewind(csv_file);
        current = current->next;
    }

    fclose(csv_file);
}

// void csv_file_reader(char csv_file) {}
struct LLNode* parse_args(int argc, char *argv[]) {
   struct  LLNode *head = NULL ;
   struct  LLNode *tail = NULL ;
   struct  LLNode *tmp_node = NULL ;
    for  (int i = 1 ; i < argc -1 ; i++ ){
        tmp_node = ( struct LLNode*) malloc(sizeof( struct LLNode)) ;
        tmp_node -> arg = '\0' ;
        tmp_node -> string = NULL ;
        tmp_node -> value = NULL ;
    tmp_node ->next = NULL ; 
        if (strcmp(argv[i],"-f") == 0 ) {
            tmp_node ->arg = 'f' ; }
        if(strcmp(argv[i],"-r")== 0) {
            tmp_node->arg = 'r' ;
        }

        if(strcmp(argv[i],"-h") == 0){
            tmp_node->arg = 'h' ;
        }
        if(strcmp(argv[i],"-max") == 0 ) {
            //check to make sure there is a next value if max is provided
            if(i + 1 < argc -1) {
                tmp_node->arg = 'x' ;
                tmp_node->string = argv[i+1] ;
                //ensure next iteration of the loop skips over field arg
                i++ ;
            }else
            {
        free(tmp_node) ; 
                printf("Max requires another arguement\n") ;
                exit(EXIT_FAILURE) ;
            }
        }
        if(strcmp(argv[i], "-min")==0){
            if(i + 1 < argc-1) {
                tmp_node->arg ='m' ;
                tmp_node->string = argv[i+1] ;
                i++ ;

            } else {
        free(tmp_node) ; 
                printf("min requires another arguement\n") ;
                exit(EXIT_FAILURE) ; }
        }

        if(strcmp(argv[i], "-mean") == 0 ) {

            if( i + 1 < argc -1 )  {
                tmp_node ->arg = 'a' ;
                tmp_node ->string = argv[ i+ 1] ;
                i++; }
            else {
        free(tmp_node) ; 
                printf("Mean needs another arguement\n") ;
                exit(EXIT_FAILURE) ; }
        }
        if (strcmp(argv[i], "-records") == 0) {
            if ( i + 2 < argc -1 ) {
                tmp_node ->arg = 'R' ;
                tmp_node ->string = argv[i+1] ;
                tmp_node ->value = argv[i+ 2 ] ;
                i += 2 ;  }
            else {
        free(tmp_node) ; 
                printf("Records requires field and value\n");
                exit(EXIT_FAILURE);}
        }

        //no match found handle case
        if (tmp_node->arg == '\0'){
            printf("UNKNOWN FIELD: %s\n", argv[i]) ;
        free(tmp_node) ; 
            exit(EXIT_FAILURE) ;  }
        if(head == NULL) {
            head = tmp_node ;
            tail = head ; }
        else {
            tail ->next = tmp_node ;
            tail = tmp_node ; }
    }
    return head ;
}


void free_list(struct LLNode *head) {
    struct LLNode *node = head ;
    struct LLNode *next ;
    while(node != NULL ) {
        next  = node -> next ;
        free(node) ;
        node = next ; }
}



int main(int argc, char *argv[]) {
    char *csv_file = argv[argc-1];
    struct LLNode *head = parse_args(argc,argv) ;
    if(head !=NULL) {
        call_command(head,csv_file) ;
        free_list(head) ;
    }  else {
        return EXIT_FAILURE ;
    }
    return EXIT_SUCCESS;
    // create helper function to read csv file
    // might need to modify the way we're reading arguments
    // i goes to argc-1 because all we want to get are the commands passed in
    //call_command(*argv[i], csv_file); the function call
    // call helper function that compares the entry to a some expected chara
}


