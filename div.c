#include "main.h"

int is_zero(Dlist *head)
{
    while (head)
    {
        if (head->data != 0)
            return 0;
        head = head->next;
    }
    return 1;
}

Dlist *copy_list(Dlist *head)
{
    Dlist *new_head = NULL;
    Dlist *new_tail = NULL;

    while (head)
    {
        Dlist *new = malloc(sizeof(Dlist));
        if (!new)
            return NULL;

        new->data = head->data;
        new->next = NULL;
        new->prev = new_tail;

        if (new_head == NULL)
            new_head = new;

        if (new_tail)
            new_tail->next = new;

        new_tail = new;
        head = head->next;
    }

    return new_head;
}


void increment(Dlist **head, Dlist **tail)
{
    int carry = 1;
    Dlist *temp = *tail;

    while (temp && carry)
    {
        int sum = temp->data + carry;
        temp->data = sum % 10;
        carry = sum / 10;
        temp = temp->prev;
    }

    if (carry)
    {
        Dlist *new = malloc(sizeof(Dlist));
        new->data = carry;
        new->prev = NULL;
        new->next = *head;

        if (*head)
            (*head)->prev = new;
        else
            *tail = new;

        *head = new;
    }
}

int division(Dlist **head, Dlist **tail,Dlist **head1, Dlist **tail1,Dlist **rhead, Dlist **rtail)
{
    /* divisor == 0 */
    if (is_zero(*head1))
    {
        printf("Result -> 0\n");
        return SUCCESS;
    }

    /* dividend < divisor */
    if (compare(*head, *head1) < 0)
    {
        printf("Not possible\n");
        return SUCCESS;
    }

    /* copy dividend for repeated subtraction */
    Dlist *temp_head = copy_list(*head);
    Dlist *temp_tail = temp_head;

    while (temp_tail->next)
        temp_tail = temp_tail->next;

    /* initialize quotient = 0 */
    *rhead = NULL;
    *rtail = NULL;

    Dlist *new = malloc(sizeof(Dlist));
    new->data = 0;
    new->next = NULL;
    new->prev = NULL;

    *rhead = *rtail = new;

    /* continuous subtraction */
    while (compare(temp_head, *head1) >= 0)
    {
        Dlist *sub_head = NULL;
        Dlist *sub_tail = NULL;

        subtraction(&temp_head, &temp_tail,
                    head1, tail1,
                    &sub_head, &sub_tail);

        temp_head = sub_head;
        temp_tail = sub_tail;

        while (temp_tail && temp_tail->next)
            temp_tail = temp_tail->next;

        /* count iterations */
        increment(rhead, rtail);
    }

    /* print quotient */
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