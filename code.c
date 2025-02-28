#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <std.bool>

struct  LLNode { 
char arg ; 
char *string ;
char *value ;  
struct LLNode *next ; } 

void f(int header) {
   
}

int r(char *csv_file, int header) {
    //can handle header in here. include an int has_header
    FILE *file = fopen(csv_file, "r" );
    if(!file){
        return 0;
    }

    int ch, count = 0;
    int ch = fgetc(file);
    while(ch != EOF) {
        if(ch == '\n') {
            count++;
        }
        ch = fgetc(file);
    }

    fclose(file);
    //if there is a header. count-- . can handle has_header in main.
    if(header){
        count--;
    }

    printf("%d\n", count);
    return count;
}

void h(char *csv_file, struct LLNode *header) {
    int ch;
    struct LLNode *head = NULL;
    struct LLNode *tail = NULL;
    int capacity = 128;
    char *buffer = malloc(capacity * sizeof(char));
    int length = 0;

    //Read header field character by character
    while((ch = fgetc(file)) != EOF){
        if(ch == '\n' | ch == ','){
            //Terminate the current field string
            buffer[length] = '\0';
            
            //Allocate a new node for the header file
            struct LLNode *newNode = malloc(sizeof(struct LLNode *newNode));

        newNode->arg = 'h';
        newNode->next = NULL;

        newNode->string = malloc(length + 1);
        if(!newNode->string){
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
            buffer = realloc(buffer, capacity);
            if(!buffer){
                exit(EXIT_FAILURE);
            }
        }
        buffer[length++] = ch;
    }
    free(buffer);
    
    if(head == NULL){
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

void max() {}

void min() {}

void mean() {}

void records() {}

void call_command(char command,char csv) {

}

struct LLNode* parse_args(int argc, char *argv[]) { 
struct LLNode *head = NULL ; 
struct LLNode *tail = NULL ; 
struct LLNode *tmp_node = NULL ; 
for  (int i = 1 ; i < argc -1 ; i++ ){ 
struct tmp_node = (LLNode*) malloc(sizeof(struct LLNode)) ; 
tmp_node -> arg = '\0' ; 
tmp_node -> string = NULL ; 
tmp_node -> value = NULL ;  
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
printf("Max requires another arguement\n") ;  
exit(EXIT_FAILURE) ; 
}
}

if(strcmp(argv[i], "-min")==0){
if(i + 1 < argc-1) {
tmp_node->arg ='m' ;
tmp_node->string = argv[i+1] ; 
i++ ; 
 
}else { 
printf("min requires another arguement\n") ; 
exit(EXIT_FAILURE) ; } 
}

if(strcmp(argv[i], "-mean") == 0 ) { 

	if( i + 1 < argc -1 )  { 
	tmp_node ->arg = 'a' ; 
	tmp_node ->string = argv[ i+ 1] ; 
	i++; } 
	else { 
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
printf("Records requires field and value\n");  
exit(EXIT_FAILURE);}
}

//no match found handle case
if (tmp_node->arg == '\0'){
printf("UNKNOWN FIELD: %s\n", argv[i]) ;
exit(EXIT_FAILURE) ;  }
if(head == NULL) { 
head = tmp_node ; 
tail = head ; } 
else { 
tail ->next = tmp_node ; 
tail = tmp_node ; } 
}
return head ; }}

int main(int argc, char *argv[]){
    char *csv_file = argv[argc-1];
    LLNode *node = NULL ; 
    LLNode *head = parse_args(argc,argv) ;   
    // create helper function to read csv file
     // might need to modify the way we're reading arguments

        // i goes to argc-1 because all we want to get are the commands passed in

     
      // call helper function that compares the entry to a some expected characters, and returns...
        // get a return value




        // return EXIT_FAILURE
    
    return EXIT_SUCCESS;
}
