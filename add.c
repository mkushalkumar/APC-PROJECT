#include "main.h"

int addition(Dlist **head, Dlist **tail,Dlist **head1, Dlist **tail1,Dlist **rhead, Dlist **rtail)
{
    int carry = 0;
    int res;

    Dlist *temp1 = *tail;
    Dlist *temp2 = *tail1;

    while (temp1 != NULL || temp2 != NULL || carry)
    {
        int val1, val2;

        if (temp1 != NULL)
            val1 = temp1->data;
        else
            val1 = 0;

        if (temp2 != NULL)
            val2 = temp2->data;
        else
            val2 = 0;

        res = val1 + val2 + carry;

        carry = res / 10;
        res = res % 10;

        Dlist *new = malloc(sizeof(Dlist));
        if (new == NULL)
        {
            return FAILURE;
        }

        new->data = res;
        new->next = NULL;
        new->prev = NULL;

        
        if (*rhead == NULL)
        {
            *rhead = *rtail = new;
        }
        else
        {
            new->next = *rhead;
            (*rhead)->prev = new;
            *rhead = new;
        }

        if (temp1 != NULL)
            temp1 = temp1->prev;

        if (temp2 != NULL)
            temp2 = temp2->prev;
    }

    
    Dlist *rtemp = *rhead;
    printf("Result -> ");
    while (rtemp != NULL)
    {
        printf("%d ", rtemp->data);
        rtemp = rtemp->next;
    }
    printf("\n");

    return SUCCESS;
}