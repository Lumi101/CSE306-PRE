#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct  LLNode { 
char arg ; 
char *string ;
char *value ;  
struct LLNode *next ; } ; 

void f(int header) {
   
}
void find_min_max_avg(FILE *csv, char *field,bool header,double init_value, char op ){
    char buffer[1024] ;
    char *tkn ; 
    int c_index = -1 ; 
    double min,max,sum = 0.0 ; 
    int ct = 0 ; 
    bool frow = true ; 
    bool found = false ; 
    bool is_num = true ; 
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
                    is_num = false ; 
                    break ; 
                }else {
                    is_num = true ;
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

int r(char *csv_file, int header) {
    //can handle header in here. include an int has_header
    //FILE *file = fopen(csv_file, "r" );
    //if(!file){
    //    return 0;
   // }

    //int ch, count = 0;
   // int ch = fgetc(file);
   // while(ch != EOF) {
     //   if(ch == '\n') {
       //     count++;
       // }
       // ch = fgetc(file);
   // }

   // fclose(file);
    //if there is a header. count-- . can handle has_header in main.
   // if(header){
     //   count--;
   // }

   // printf("%d\n", count);
   // return count;
}

void h(FILE *file, struct LLNode **header) {
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
            struct LLNode *newNode = malloc(sizeof(struct LLNode));

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
          h(csv_file,&head);  
                break;
            case 'x': // For -max
                find_min_max_avg(csv_file,current->string,has_header,0.0,'x') ; 
                break;
            case 'm': // For -min
                find_min_max_avg(csv_file,current->string,has_header,0.0,'m') ; 
                break;
            case 'a': // For -mean
             find_min_max_avg(csv_file,current->string,has_header,0.0,'a') ; 
                mean(csv_file, current->string, has_header);
                break;
            case 'R': // For -records
                records(csv_file, current->string, current->value, has_header);
                break;
	default : 
		printf("Unknown arg") ; 
break ; } 
      rewind(csv_file);
      current = current ->next ; 
}
fclose(csv_file) ; } 

struct LLNode* parse_args(int argc, char *argv[]) { 
struct LLNode *head = NULL ; 
struct LLNode *tail = NULL ; 
struct LLNode *tmp_node = NULL ; 
for  (int i = 1 ; i < argc -1 ; i++ ){ 
tmp_node =  (struct LLNode *)( malloc(sizeof(struct LLNode))) ; 
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
return head ; }

int main(int argc, char *argv[]){
    char *csv_file = argv[argc-1];
   struct LLNode *node = NULL ; 
   struct LLNode *head = parse_args(argc,argv) ;   
    // create helper function to read csv file
     // might need to modify the way we're reading arguments

        // i goes to argc-1 because all we want to get are the commands passed in

     
      // call helper function that compares the entry to a some expected characters, and returns...
        // get a return value




        // return EXIT_FAILURE
    
    return EXIT_SUCCESS;
}
