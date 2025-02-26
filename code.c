#include <stdlib.h>
#include <string.h>
//#include <stdbool.h>
#include <stdio.h>


struct  LLNode {
    char arg ;
    char *string ;
    char *value ;
    struct LLNode *next ; } ;


void f() {}

void r() {}

void h() {}

void max() {}

void min() {}

void mean() {}

void records() {}

void call_command(char command, char *csv_file) {
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

            } else {
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
    return head ;
}



int main(int argc, char *argv[]) {
    char *csv_file = argv[argc-1];
    // create helper function to read csv file
    for (int i = 0; i < argc-1; i++) { // might need to modify the way we're reading arguments
        // i goes to argc-1 because all we want to get are the commands passed in
        //call_command(*argv[i], csv_file); the function call
        // call helper function that compares the entry to a some expected characters, and returns a bool...

        if (!(call_command(*argv[i], csv_file))) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}
