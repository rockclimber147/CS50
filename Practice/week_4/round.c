#include <stdio.h>
#include <math.h>

int main(void)
{
    int a = 20;
    int b = 21;
    int c = 21;
    float three = 3;

    int roundabc = round((a + b + c) / 3);
    float abcover3 = (a + b + c) / 3.000;
    int roundfloat = round(abcover3);
    printf("int roundabc = %i, float abcover3 = %f, int roundfloat = %i\n", roundabc, abcover3, roundfloat);

    for (int i = 0; i < 3; i++)
    {
        printf("%i", i);
    }
    printf("\n");
    for (int i = 0; i <=3; i++)
    {
        printf("%i", i);
    }
    printf("\n");



    int A[6];
    int total;
    int total2;
    for (int i = 0; i < 6; i++)
    {
        A[i] = i;
        total = total + i;
    }
    for (int i = 0; i < 15
    ; i++)
    {
        total2 = A[i] + total2;
        printf("%i\n", A[i]);
    }
    printf("%i\n%i\n", total, total2);
}