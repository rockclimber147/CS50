// RAM info that is used is cleared when program ends. Can write a more permanent file outside of RAM
// Working with files will usually have us using pointers to files
// C provides a FILE data structure, can be pointed to using FILE*
// input/output (I/O) commands used are in stdio.h

// 6 basics:  fopen()  fclose() fputc() fgetc()  fread()  fwrite()

// fopen()
// opens a file and returns a pointer to it (Check for NULL)
    FILE* pointer_to_file = fopen(<filename>,<operation>);
// operations can be read r, write w (overwrites everything), append a (adds to end)

//fclose()
// Closes pointed to file fclose(pointer_to_file);
// Can't do any more operations to file w/o reopening

// fgetc() (file get a character)
// reads and returns nex character from pointed to file (or if first call the first character)
// file must have been opened in read mode and that pointer must be used
    char ch = fgetc(pointer_to_file);
// This gets first character from file and stores it in variable ch. Can loop to go through all characters
    while(ch = fgetc(pointer_to_file) != EOF)
        printf("%c", ch);
// this will iterate through the whole file until the End Of File character is reached, printing every character.
// linux command cat will print out file contents in terminal window

// fputc()
// writes or appends specified character to the pointed to file
// Must be in write mode or append mode
    fputc(<character>,pointer_to_file);

    while(ch = fgetc(pointer_to_file) != EOF);
        fputc(ch , pointer_to_file2);
// This copies all of the first file to the second one. first file poinjter set to read, second set to write/append

// fread(<buffer>,<size>,<qty>,<file pointer>)
// reads <qty> units of <size> from file and stores them in <buffer> array. File pointer must be opened in read
    int array[10]
    fread(array, sizeof(int), 10, pointer_to_file)
// reads 10 * (4 bytes) from file opened in read and stores those bytes in array.
// Can dynamically allocate memory to array as well, since array is just a pointer to first char
    char c
    fread(&c, sizeof(char), 1, pointer_to_file);
// This is fgetc essentially, but with just a variable we need the pointer/address of it

// fwrite(same as fread)
// Just like fread but for writing