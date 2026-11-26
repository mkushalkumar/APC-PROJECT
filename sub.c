#include "main.h"

int compare(Dlist *head1, Dlist *head2)
{
    int count1 = 0, count2 = 0;
    Dlist *t1 = head1, *t2 = head2;

    while (t1)
    {
        count1++;
        t1 = t1->next;
    }
    while (t2)
    {
        count2++;
        t2 = t2->next;
    }

    if (count1 > count2)
        return 1;
    if (count1 < count2)
        return -1;

    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return 1;
        if (head1->data < head2->data)
            return -1;

        head1 = head1->next;
        head2 = head2->next;
    }

    return 0;
}


int subtraction(Dlist **head, Dlist **tail, Dlist **head1, Dlist **tail1,Dlist **rhead, Dlist **rtail)
{
    if (*tail == NULL || *tail1 == NULL)
    {
        printf("hi\n");
        return FAILURE;
    }
    *rhead = NULL;
    *rtail = NULL;

    int borrow = 0, res;
    int sign = 0;

    int cmp = compare(*head, *head1);

    Dlist *temp1;
    Dlist *temp2;

    /* Decide bigger number */
    if (cmp < 0)
    {
        temp1 = *tail1;
        temp2 = *tail;
        sign = 1;
    }
    else
    {
        temp1 = *tail;
        temp2 = *tail1;
    }

    /* Subtraction logic */
    while (temp1 != NULL)
    {
        int val1 = temp1->data - borrow;
        int val2 = (temp2 != NULL) ? temp2->data : 0;

        if (val1 < val2)
        {
            val1 += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        res = val1 - val2;

        Dlist *new = malloc(sizeof(Dlist));
        if (!new)
            return FAILURE;

        new->data = res;
        new->next = NULL;
        new->prev = NULL;

        /* Insert at front */
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

        temp1 = temp1->prev;
        if (temp2)
            temp2 = temp2->prev;
    }

    /* Remove leading zeros */
    while (*rhead && (*rhead)->data == 0 && (*rhead)->next != NULL)
    {
        Dlist *temp = *rhead;
        *rhead = (*rhead)->next;
        (*rhead)->prev = NULL;
        free(temp);
    }

    /* Print result */
    printf("Result -> ");
    if (sign)
        printf("- ");

    Dlist *temp = *rhead;
    while (temp)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");

    return SUCCESS;
}