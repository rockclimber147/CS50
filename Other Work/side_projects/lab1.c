
#include <stdio.h>

int main(void)
{
    // Lab1a:


    // Name
    // Student ID

    printf("Hello, world!\n");
    printf("This is my first python program!\n");  // you don't get a new line for free, you have to type it in manually (the \n character).

    // Lab1b:

    // Print the statement “Enter your name:”
    // Get the user’s name from the console and save it to a variable called name
    // Print the statement “Hello, <Name>” where <Name> is the name entered by the user

    char your_name[100];  // C doesn't have a built in string datatype, it uses an array of characters. your_name has room for 100 characters. If you input more than 100 characters, the program will break. There's definitely a better way to do this but I don't know how to.

    printf("Enter your name: ");
    scanf("%s", your_name);  
    printf("Hello, %s\n", your_name);

    // Ask the user to input an integer value and assign in to the variable x_value
    // Ask the user to input another integer value and assign it to the variable y_value
    // Create a variable called xy_sum and assign it the sum of x_value and y_value
    // Print the xy_sum using the created variables from above.
    // For example:
    // If x_value was 5 and y_value was 10 then the output should be
    // “ 5 + 10 = 15 ”

    int x;
    int y;

    printf("Please enter an integer: ");
    scanf("%i", &x);

    printf("Please enter another integer: ");
    scanf("%i", &y);

    int xy = x + y;

    printf("%i + %i = %i\n", x, y, xy);

    // Create a variable called a_value and assign it the float value 10.5.
    // Create a variable called b_value and assign it the float value 4.0.
    // Create a variable called c_value and assign it to the a_value multiplied by the b_value.
    // Print the statement: “10.5 * 4.0 = 42.0” using the variables you created above

    float a_value = 10.5;
    float b_value = 4.0;
    float c_value = a_value * b_value;

    printf("%0.2f * %0.2f = %0.2f\n", a_value, b_value, c_value);

    // Print the difference between c_value and xy_sum (i.e., c_value – xy_sum).
    // Convert the c_value to an integer when subtracting.
    // Note: You can do this directly in the parentheses of the print() statement.

    printf("%i\n", (int)c_value - xy);

    // Answer the following question in a comment:
    // How is the output different if you don’t convert c_value to an int?

    // If you don't convert the c_value to an int, your program won't compile (run). The compiler expects to be printing an integer but is given a float and can't handle that automatically like python can.

    return 0;
}

// Output:

// Hello, world!
// This is my first python program!
// Enter your name: Bob
// Hello, Bob
// Please enter an integer: 5
// Please enter another integer: 10
// 5 + 10 = 15
// 10.50 * 4.00 = 42.00
// 27