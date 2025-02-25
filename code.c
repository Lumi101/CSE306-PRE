#include <stdlib.h>
#include <stdbool.h>
// #include <stdio.h>
// #include <string.h>



void f() {}

void r() {}

void h() {}

void max() {}

void min() {}

void mean() {}

void records() {}

bool call_command(char command, char *csv_file) {
    if (command == 'placeholder') {
        bool command_return;
        return command_return;
    }
}

// void csv_file_reader(char csv_file) {}

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
