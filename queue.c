/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q)
        *q = (queue_t){NULL, NULL, 0};
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (!q)
        return;
    list_ele_t *cur = q->head, *old;
    while (cur) {
        free(cur->value);
        old = cur;
        cur = cur->next;
        free(old);
    }
    free(q);
}

/* Generate a new list_ele_t instance and populate it with given string. */
list_ele_t *new_element(char *s)
{
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return NULL;
    if (!(newh->value = strdup(s))) {
        free(newh);
        return NULL;
    }
    return newh;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = new_element(s);
    if (!newh)
        return false;
    newh->next = q->head;
    q->head = newh;
    if (!q->size)
        q->tail = newh;
    q->size++;
    return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (!q)
        return false;
    list_ele_t *newh = new_element(s);
    if (!newh)
        return false;
    newh->next = NULL;
    if (!q->size)
        q->head = newh;
    else
        q->tail->next = newh;
    q->tail = newh;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (!q || !q->size)
        return false;
    list_ele_t *old = q->head;
    q->head = q->head->next;
    q->size--;
    if (!q->size)
        q->tail = NULL;
    if (sp) {
        strncpy(sp, old->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    free(old->value);
    free(old);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q && q->size > 0) {
        list_ele_t *cur = q->head->next, *old, *tail = q->head;
        while (cur) {
            old = cur;
            cur = cur->next;
            old->next = q->head;
            q->head = old;
        }
        tail->next = NULL;
        q->tail = tail;
    }
}
