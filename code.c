#include <stdlib.h>
// #include <stdio.h>
// #include <string.h>


struct CSV(
    Node *header
    Node *rows;
    int num_fields;
    int num_rows;
    )CSV;

void f(int header) {
   
}

int r(char *csv_file) {
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
    }
    fclose(file);
    //if there is a header. count-- . can handle has_header in main. 

    printf("%d\n", count);
}

void h() {}

void max() {}

void min() {}

void mean() {}

void records() {}

void call_command(char command) {}

void csv_file_reader(char csv_file) {}

int main(int argc, char *argv[]) {
    char *csv_file = argv[argc-1];
    // create helper function to read csv file
    for (int i = 0; i < argc-1; i++) { // might need to modify the way we're reading arguments
        // i goes to argc-1 because all we want to get are the commands passed in

        // call helper function that compares the entry to a some expected characters, and returns...
        // get a return value




        // return EXIT_FAILURE
    }
    return EXIT_SUCCESS;
}
