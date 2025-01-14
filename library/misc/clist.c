/*
 * $Id: misc_clist.c,v 1.0 2023-03-03 14:15:37 clib2devs Exp $
*/

#ifndef _STDIO_HEADERS_H
#include "stdio_headers.h"
#endif /* _STDIO_HEADERS_H */

#ifndef _STDLIB_HEADERS_H
#include "stdlib_headers.h"
#endif /* _STDLIB_HEADERS_H */

#include "clist.h"

typedef struct {
    int count;          /* Number of items in the list. */
    int alloc_size;     /* Allocated size in quantity of items */
    int lastSearchPos;  /* Position of last search - firstMatch or LastMatch */
    size_t item_size;   /* Size of each item in bytes. */
    void *items;        /* Pointer to the list */
} cListPriv;

int cListRealloc(CList *l, int n) {
    cListPriv *p = (cListPriv *) l->priv;
    if (n < p->count) {
        D(("CList: ERROR! Can not realloc to '%i' size - count is '%i'\n", n, p->count));
        assert(n >= p->count);
        return 0;
    }

    if (n == 0 && p->alloc_size == 0)
        n = 2;

    void *ptr = realloc(p->items, p->item_size * n);
    if (ptr == NULL) {
        D(("CList: ERROR! Can not reallocate memory!\n"));
        return 0;
    }
    p->items = ptr;
    p->alloc_size = n;
    return 1;
}

void *cListAdd(CList *l, void *o) {
    cListPriv *p = (cListPriv *) l->priv;
    if (p->count == p->alloc_size &&
        cListRealloc(l, p->alloc_size * 2) == 0)
        return NULL;

    char *data = (char *) p->items;
    data = data + p->count * p->item_size;
    memcpy(data, o, p->item_size);
    p->count++;
    return data;
}

void *cListInsert(CList *l, void *o, int n) {
    cListPriv *p = (cListPriv *) l->priv;
    if (n < 0 || n > p->count) {
        D(("CList: ERROR! Insert position outside range - %d; n - %d.\n", p->count, n));
        assert(n >= 0 && n <= p->count);
        return NULL;
    }

    if (p->count == p->alloc_size &&
        cListRealloc(l, p->alloc_size * 2) == 0)
        return NULL;

    size_t step = p->item_size;
    char *data = (char *) p->items + n * step;
    memmove(data + step, data, (p->count - n) * step);
    memcpy(data, o, step);
    p->count++;
    return data;
}

void *cListReplace(CList *l, void *o, int n) {
    cListPriv *p = (cListPriv *) l->priv;
    if (n < 0 || n >= p->count) {
        D(("CList: ERROR! Replace position outside range - %d; n - %d.\n", p->count, n));
        assert(n >= 0 && n < p->count);
        return NULL;
    }

    char *data = (char *) p->items;
    data = data + n * p->item_size;
    memcpy(data, o, p->item_size);
    return data;
}

void cListRemove(CList *l, int n) {
    cListPriv *p = (cListPriv *) l->priv;
    if (n < 0 || n >= p->count) {
        D(("CList: ERROR! Remove position outside range - %d; n - %d.\n", p->count, n));
        assert(n >= 0 && n < p->count);
        return;
    }

    size_t step = p->item_size;
    char *data = (char *) p->items + n * step;
    memmove(data, data + step, (p->count - n - 1) * step);
    p->count--;

    if (p->alloc_size > 3 * p->count && p->alloc_size >= 4) /* Dont hold much memory */
        cListRealloc(l, p->alloc_size / 2);
}

void *cListAt(CList *l, int n) {
    cListPriv *p = (cListPriv *) l->priv;
    if (n < 0 || n >= p->count) {
        D(("CList: ERROR! Get position outside range - %d; n - %d.\n", p->count, n));
        assert(n >= 0 && n < p->count);
        return NULL;
    }

    char *data = (char *) p->items;
    data = data + n * p->item_size;
    return data;
}

void *cListFirstMatch(CList *l, const void *o, size_t shift, size_t size, int string) {
    cListPriv *p = (cListPriv *) l->priv;
    char *data = (char *) p->items;
    size_t step = p->item_size;
    p->lastSearchPos = -1;

    if (shift + size > p->item_size) {
        D(("CList: ERROR! Wrong ranges for firstMatch - shift '%zu', size '%zu', item_size '%zu'\n", shift, size, p->item_size));
        assert(shift + size <= p->item_size);
        return NULL;
    }

    if (shift == 0 && size == 0)
        size = p->item_size;

    size_t i = shift;
    size_t end = p->count * step;
    int index = 0;

    if (string) {
        for (; i < end; i += step, index++) {
            if (strncmp(data + i, o, size) == 0) {
                p->lastSearchPos = index;
                return (data + i - shift);
            }
        }
    } else {
        for (; i < end; i += step, index++) {
            if (memcmp(data + i, o, size) == 0) {
                p->lastSearchPos = index;
                return (data + i - shift);
            }
        }
    }

    return NULL;
}

void *cListLastMatch(struct CList *l, const void *o, size_t shift, size_t size, int string) {
    cListPriv *p = (cListPriv *) l->priv;
    char *data = (char *) p->items;
    size_t step = p->item_size;
    p->lastSearchPos = -1;

    if (shift + size > p->item_size) {
        D(("CList: ERROR! Wrong ranges for lastMatch - shift '%zu', size '%zu', item_size '%zu'\n", shift, size, p->item_size));
        assert(shift + size <= p->item_size);
        return NULL;
    }

    if (shift == 0 && size == 0)
        size = p->item_size;

    int index = p->count - 1;
    long i = index * step + shift;
    if (string) {
        for (; i >= 0; i -= step, index--) {
            if (strncmp(data + i, o, size) == 0) {
                p->lastSearchPos = index;
                return (data + i - shift);
            }
        }
    } else {
        for (; i >= 0; i -= step, index--) {
            if (memcmp(data + i, o, size) == 0) {
                p->lastSearchPos = index;
                return (data + i - shift);
            }
        }
    }

    return NULL;
}

int cListIndex(CList *l) {
    cListPriv *p = (cListPriv *) l->priv;
    return p->lastSearchPos;
}

int cListSwap(CList *l, int a, int b) {
    cListPriv *p = (cListPriv *) l->priv;

    if (a < 0 || a >= p->count || b < 0 || b >= p->count) {
        D(("CList: ERROR! Swap position outside range - %i, %i; count - %d.\n", a, b, p->count));
        assert(a >= 0 && a < p->count && b >= 0 && b < p->count);
        return 0;
    }

    if (a == b) return 1; /* ? Good ? :D */

    char *data = (char *) p->items;
    size_t step = p->item_size;

    if (p->count == p->alloc_size &&
        cListRealloc(l, p->alloc_size + 1) == 0)
        return 0;

    memcpy(data + p->count * step, data + a * step, step);
    memcpy(data + a * step, data + b * step, step);
    memcpy(data + b * step, data + p->count * step, step);
    return 1;
}

int cListCount(CList *l) {
    cListPriv *p = (cListPriv *) l->priv;
    return p->count;
}

int cListAllocSize(CList *l) {
    cListPriv *p = (cListPriv *) l->priv;
    return p->alloc_size;
}

size_t cListItemSize(CList *l) {
    cListPriv *p = (cListPriv *) l->priv;
    return p->item_size;
}

void cListClear(CList *l) {
    cListPriv *p = (cListPriv *) l->priv;
    free(p->items);
    p->items = NULL;
    p->alloc_size = 0;
    p->count = 0;
}

void cListFree(CList *l) {
    ENTER();
    SHOWPOINTER(l);

    cListPriv *p = (cListPriv *) l->priv;
    if (p->items) {
        free(p->items);
        p->items = NULL;
    }
    if (p) {
        free(p);
        p = NULL;
    }

    free(l);
    l = NULL;

    LEAVE();
}

void cListPrint(CList *l, size_t shift, int n, const char *type) {
    cListPriv *p = (cListPriv *) l->priv;

    if (shift >= p->item_size) {
        D(("CList: ERROR! Wrong shift value for list print - " "shift '%zu', item_size '%zu'\n", shift, p->item_size));
        assert(shift < p->item_size);
        return;
    }

    printf("\nCList:  count = %i  item_size = %zu   alloc_size = %i   type = %s\n",
           p->count, p->item_size, p->alloc_size, type);

    if (n > 0) {
        int tp = -1;
        if (type == NULL) tp = 0;  /* Print out pointers */
        else if (strcmp(type, "char") == 0) tp = 1;
        else if (strcmp(type, "short") == 0) tp = 2;
        else if (strcmp(type, "int") == 0) tp = 3;
        else if (strcmp(type, "long") == 0) tp = 4;
        else if (strcmp(type, "uintptr_t") == 0) tp = 5;
        else if (strcmp(type, "size_t") == 0) tp = 6;
        else if (strcmp(type, "double") == 0) tp = 7;
        else if (strcmp(type, "string") == 0) tp = 8;

        if (tp == -1) {
            D(("CList: Can not print - not supported type - %s\n\n", type));
            return;
        }

        n = (n > p->count) ? p->count : n;
        char *data = (char *) p->items + shift;
        size_t step = p->item_size;
        int i = 0;
        for (; i < n; i++) {
            switch (tp) {
                case 0:
                    printf("%p  ", data);
                    break;
                case 1:
                    printf("%c ", *(char *) data);
                    break;
                case 2:
                    printf("%hi  ", *(short *) data);
                    break;
                case 3:
                    printf("%i  ", *(int *) data);
                    break;
                case 4:
                    printf("%li  ", *(long *) data);
                    break;
                case 5:
                    printf("0x%lx  ", *(uintptr_t *) data);
                    break;
                case 6:
                    printf("%zu  ", *(size_t *) data);
                    break;
                case 7:
                    printf("%f  ", *(double *) data);
                    break;
                case 8:
                    printf("%s\n", data);
                    break;
                default:
                    return;
            }

            data += step;
        }
        printf("\n\n");
    }
}

CList *CList_init(size_t objSize) {
    CList *lst = malloc(sizeof(CList));
    cListPriv *p = malloc(sizeof(cListPriv));
    if (!lst || !p) {
        D(("CList: ERROR! Can not allocate CList!\n"));
        return NULL;
    }
    p->count = 0;
    p->alloc_size = 0;
    p->lastSearchPos = -1;
    p->item_size = objSize;
    p->items = NULL;
    lst->add = &cListAdd;
    lst->insert = &cListInsert;
    lst->replace = &cListReplace;
    lst->remove = &cListRemove;
    lst->at = &cListAt;
    lst->realloc = &cListRealloc;
    lst->count = &cListCount;
    lst->firstMatch = &cListFirstMatch;
    lst->lastMatch = &cListLastMatch;
    lst->index = &cListIndex;
    lst->swap = &cListSwap;
    lst->allocSize = &cListAllocSize;
    lst->itemSize = &cListItemSize;
    lst->print = &cListPrint;
    lst->clear = &cListClear;
    lst->free = &cListFree;
    lst->priv = p;
    return lst;
}
