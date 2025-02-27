#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>


struct  LLNode {
    char arg ;
    char *string ;
    char *value ;
    struct LLNode *next ; } ;


void f(FILE *csv) {
printf("\n f called\n") ; }

void r(FILE *csv_file, bool header ) {
printf("\n r called\n") ; 
}

void h() {
printf("\n h called\n") ; 
}

void max( FILE *csv, char *field,bool header) {
printf("\n max  called\n " ) ; 
}

void min(FILE *csv, char *field, bool header) {
printf("\n min called\n") ; }

void mean(FILE *csv, char *field, bool header) {
printf("\n mean  called\n") ; 

}

void records(FILE *csv, char *field, char *val, bool header) 
{
printf("\n records called\n") ; 
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
          h();  
                break;
            case 'x': // For -max
                max(csv_file, current->string, has_header);
                break;
            case 'm': // For -min
                min(csv_file, current->string, has_header);
                break;
            case 'a': // For -mean
                mean(csv_file, current->string, has_header);
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
