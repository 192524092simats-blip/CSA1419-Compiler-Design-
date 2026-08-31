#include <stdio.h>

int main()
{
    int intVal;
    float floatVal;

    float implicitResult;
    int explicitResult;

    printf("Enter Integer Value: ");
    scanf("%d", &intVal);

    printf("Enter Float Value: ");
    scanf("%f", &floatVal);

    implicitResult = intVal + floatVal;


    explicitResult = intVal + (int)floatVal;

    printf("\n----- TYPE CONVERSION RESULTS -----\n");

    printf("\nInteger Value = %d", intVal);
    printf("\nFloat Value   = %.2f", floatVal);

    printf("\n\nImplicit Conversion:");
    printf("\nint + float = float");

    printf("\nResult = %.2f", implicitResult);

    printf("\n\nExplicit Conversion:");
    printf("\nfloat converted to int using (int)");

    printf("\nResult = %d", explicitResult);

    return 0;
}
