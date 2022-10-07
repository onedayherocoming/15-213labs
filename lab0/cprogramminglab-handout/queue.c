/**
 * @file queue.c
 * @brief Implementation of a queue that supports FIFO and LIFO operations.
 *
 * This queue implementation uses a singly-linked list to represent the
 * queue elements. Each queue element stores a string value.
 *
 * Assignment for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Extended to store strings, 2018
 *
 * TODO: fill in your name and Andrew ID
 * @author XXX <XXX@andrew.cmu.edu>
 */

#include "queue.h"
#include "harness.h"

#include <stdlib.h>
#include <string.h>
/**
 * @brief Allocates a new queue
 * @return The new queue, or NULL if memory allocation failed
 */
queue_t *queue_new(void) {
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/**
 * @brief Frees all memory used by a queue
 * @param[in] q The queue to free
 */
void queue_free(queue_t *q) {
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    list_ele_t *p = q->head;
    while (p) {
        list_ele_t *tmp = p->next;
        if (p->value) {
            free(p->value);
        }
        free(p);
        p = tmp;
    }
    free(q);
}

char *char_copy(const char *s) {
    if (s == NULL) {
        return NULL;
    }
    char *s_copy = malloc((strlen(s) + 1) * sizeof(char));
    if (s_copy == NULL) {
        return NULL;
    }
    memcpy(s_copy, s, strlen(s));
    s_copy[strlen(s)] = 0;
    return s_copy;
}

/**
 * @brief Attempts to insert an element at head of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_head(queue_t *q, const char *s) {
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    newh->value = char_copy(s);
    if (s != NULL && newh->value == NULL) {
        free(newh);
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (q->tail == NULL) {
        q->tail = newh;
    }
    q->size++;
    return true;
}

/**
 * @brief Attempts to insert an element at tail of a queue
 *
 * This function explicitly allocates space to create a copy of `s`.
 * The inserted element points to a copy of `s`, instead of `s` itself.
 *
 * @param[in] q The queue to insert into
 * @param[in] s String to be copied and inserted into the queue
 *
 * @return true if insertion was successful
 * @return false if q is NULL, or memory allocation failed
 */
bool queue_insert_tail(queue_t *q, const char *s) {
    if (q == NULL) {
        return false;
    }
    /* You need to write the complete code for this function */
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    newh->value = char_copy(s);
    if (s != NULL && newh->value == NULL) {
        free(newh);
        return false;
    }
    newh->next = NULL;

    if (q->tail == NULL) {
        q->head = newh;
        q->tail = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    q->size++;
    return true;
}

/**
 * @brief Attempts to remove an element from head of a queue
 *
 * If removal succeeds, this function frees all memory used by the
 * removed list element and its string value before returning.
 *
 * If removal succeeds and `buf` is non-NULL, this function copies up to
 * `bufsize - 1` characters from the removed string into `buf`, and writes
 * a null terminator '\0' after the copied string.
 *
 * @param[in]  q       The queue to remove from
 * @param[out] buf     Output buffer to write a string value into
 * @param[in]  bufsize Size of the buffer `buf` points to
 *
 * @return true if removal succeeded
 * @return false if q is NULL or empty
 */
bool queue_remove_head(queue_t *q, char *buf, size_t bufsize) {
    if (q == NULL) {
        return false;
    }
    /* You need to fix up this code. */
    if (q->head == NULL) {
        return false;
    }
    list_ele_t *node = q->head;
    q->head = q->head->next;
    q->size--;
    if (q->head == NULL) {
        q->tail = NULL;
    }
    if (buf != NULL) {
        if (node->value == NULL) {
            buf[0] = 0;
        } else {
            size_t num = strlen(node->value) < bufsize - 1 ? strlen(node->value)
                                                           : bufsize - 1;
            memcpy(buf, node->value, num);
            buf[num] = 0;
        }
    }
    if (node->value) {
        free(node->value);
    }
    free(node);
    return true;
}

/**
 * @brief Returns the number of elements in a queue
 *
 * This function runs in O(1) time.
 *
 * @param[in] q The queue to examine
 *
 * @return the number of elements in the queue, or
 *         0 if q is NULL or empty
 */
size_t queue_size(queue_t *q) {
    if (q == NULL) {
        return 0;
    }
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    return q->size;
}

/**
 * @brief Reverse the elements in a queue
 *
 * This function does not allocate or free any list elements, i.e. it does
 * not call malloc or free, including inside helper functions. Instead, it
 * rearranges the existing elements of the queue.
 *
 * @param[in] q The queue to reverse
 */
void queue_reverse(queue_t *q) {
    /* You need to write the code for this function */
    if (q == NULL || q->head == NULL) {
        return;
    }
    list_ele_t *p = q->head;
    list_ele_t *head = NULL;
    q->tail = p;
    while (p) {
        list_ele_t *tmp = p->next;
        p->next = head;
        head = p;
        p = tmp;
        if (p && p->next == NULL) {
            q->head = p;
        }
    }
}
