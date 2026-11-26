
/*documentation :-

Name :- kushal kumar.
start date :- 10/04/2025.
description :-  APC Calculator is a big integer calculator implemented using doubly linked lists to
 perform arithmeticoperations on very large numbers beyond normal data type limits.
It supports addition, subtraction, multiplication, and division by storing each digit as a separate node
in the linked list.
This project helps in understanding dynamic memory allocation, linked list manipulation, and
manual arithmetic operation logic in C.
*/

#include "main.h"

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        printf("Insufficient input\n");
        return 0;
    }

    char *operand1 = argv[1];
    char *operand2 = argv[3];
    char *operator = argv[2];

    int i = 0;

    /* Sign handling */
    int sign1 = 1;
    int sign2 = 1;

    if (operand1[0] == '-')
    {
        sign1 = -1;
        operand1 = operand1 + 1;
    }

    if (operand2[0] == '-')
    {
        sign2 = -1;
        operand2 = operand2 + 1;
    }

    /* Validate operand1 */
    i = 0;
    while (operand1[i])
    {
        if (operand1[i] >= '0' && operand1[i] <= '9')
        {
            i++;
            continue;
        }

        printf("Enter only digits\n");
        return 0;
    }

    /* Validate operand2 */
    i = 0;
    while (operand2[i])
    {
        if (operand2[i] >= '0' && operand2[i] <= '9')
        {
            i++;
            continue;
        }

        printf("Enter only digits\n");
        return 0;
    }

    /* Validate operator */
    if (!(operator[0] == '+' ||
          operator[0] == '-' ||
          operator[0] == 'x' ||
          operator[0] == '/'))
    {
        printf("Invalid operator\n");
        return 0;
    }

    Dlist *head = NULL;
    Dlist *tail = NULL;

    Dlist *head1 = NULL;
    Dlist *tail1 = NULL;

    Dlist *rhead = NULL;
    Dlist *rtail = NULL;

    /* Convert operand1 */
    if (convert_string_to_linkedlist(operand1, &head, &tail) == FAILURE)
    {
        printf("Failed to create list for operand1\n");
        return FAILURE;
    }

    /* Convert operand2 */
    if (convert_string_to_linkedlist(operand2, &head1, &tail1) == FAILURE)
    {
        printf("Failed to create list for operand2\n");
        return FAILURE;
    }

    /* Operation handling */

    if (operator[0] == '+')
    {
        if (sign1 == sign2)
        {
            if (sign1 == -1)
                printf("Result -> -");

            addition(&head, &tail,
                     &head1, &tail1,
                     &rhead, &rtail);
        }
        else
        {
            subtraction(&head, &tail,
                        &head1, &tail1,
                        &rhead, &rtail);
        }
    }

    else if (operator[0] == '-')
    {
        if (sign1 != sign2)
        {
            if (sign1 == -1)
                printf("Result -> -");

            addition(&head, &tail,
                     &head1, &tail1,
                     &rhead, &rtail);
        }
        else
        {
            subtraction(&head, &tail,
                        &head1, &tail1,
                        &rhead, &rtail);
        }
    }

    else if (operator[0] == 'x')
    {
        if (sign1 != sign2)
            printf("Result -> -");

        multiplication(&head, &tail,
                       &head1, &tail1,
                       &rhead, &rtail);
    }

    else if (operator[0] == '/')
    {
        if (sign1 != sign2)
            printf("Result -> -");

        division(&head, &tail,
                &head1, &tail1,
                &rhead, &rtail);
    }

    return SUCCESS;
}


int convert_string_to_linkedlist(char *operand,
                                 Dlist **head,
                                 Dlist **tail)
{
    int i = 0;

    while (operand[i])
    {
        Dlist *new = malloc(sizeof(Dlist));

        if (new == NULL)
            return FAILURE;

        new->data = operand[i] - '0';
        new->next = NULL;
        new->prev = NULL;

        if (*head == NULL)
        {
            *head = new;
            *tail = new;
        }
        else
        {
            new->prev = *tail;
            (*tail)->next = new;
            *tail = new;
        }

        i++;
    }

    return SUCCESS;
}