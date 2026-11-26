#include "main.h"

#include "main.h"

void insert_at_front(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new)
        return;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    if (*head)
        (*head)->prev = new;
    else
        *tail = new;

    *head = new;
}

void insert_at_end(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    if (!new)
        return;

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    if (*tail)
        (*tail)->next = new;
    else
        *head = new;

    *tail = new;
}

int multiplication(Dlist **head, Dlist **tail,Dlist **head1, Dlist **tail1,Dlist **rhead, Dlist **rtail)
{
    *rhead = NULL;
    *rtail = NULL;

    /* initialize result = 0 */
    insert_at_front(rhead, rtail, 0);

    Dlist *ptr2 = *tail1;
    int zero_count = 0;

    while (ptr2)
    {
        int carry = 0;

        Dlist *temp_head = NULL;
        Dlist *temp_tail = NULL;

        Dlist *ptr1 = *tail;

        /* multiply each digit */
        while (ptr1)
        {
            int product = (ptr1->data * ptr2->data) + carry;

            int digit = product % 10;
            carry = product / 10;

            insert_at_front(&temp_head, &temp_tail, digit);

            ptr1 = ptr1->prev;
        }

        /* remaining carry */
        if (carry)
            insert_at_front(&temp_head, &temp_tail, carry);

        /* append zeros based on position */
        for (int i = 0; i < zero_count; i++)
        {
            insert_at_end(&temp_head, &temp_tail, 0);
        }

        /* add temp result to final result */
        Dlist *new_rhead = NULL;
        Dlist *new_rtail = NULL;

        addition(rhead, rtail,&temp_head, &temp_tail,&new_rhead, &new_rtail);

        *rhead = new_rhead;
        *rtail = new_rtail;

        zero_count++;
        ptr2 = ptr2->prev;
    }

    /* remove leading zero if exists */
    while (*rhead &&
           (*rhead)->data == 0 &&
           (*rhead)->next != NULL)
    {
        Dlist *temp = *rhead;
        *rhead = (*rhead)->next;
        (*rhead)->prev = NULL;
        free(temp);
    }

    /* print final result */
    printf("Result -> ");

    Dlist *temp = *rhead;
    while (temp)
    {
        printf("%d", temp->data);
        temp = temp->next;
    }

    printf("\n");

    return SUCCESS;
}