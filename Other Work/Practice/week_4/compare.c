//If you get_string two strings and type the same in both then compare (a == b) them they will be considered different
//You are filling two different memory blocks with the same data, but those char * pointers will each point to
//their own unique memory locations. get_sreing returns the address of the first char in the string
//strcmp will compare correctly

//if you make a string s and then string t = s, both s and t will have the same memory location and operations
//on one will change both. You would have only copied the pointer, not made a separate memory value