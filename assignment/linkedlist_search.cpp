#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* newNode(int x) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = x;
    temp->next = NULL;
    return temp;
}

struct Node* middle(struct Node* start, struct Node* last) {
    if (start == NULL)
        return NULL;

    struct Node* slow = start;
    struct Node* fast = start->next;

    while (fast != last) {
        fast = fast->next;
        if (fast != last) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    return slow;
}

struct Node* binarySearch(struct Node* head, int value) {
    struct Node* start = head;
    struct Node* last = NULL;

    do {
        struct Node* mid = middle(start, last);
        if (mid == NULL)
            return NULL;
        if (mid->data == value)
            return mid;
        else if (mid->data < value)
            start = mid->next;
        else
            last = mid;
    } while (last == NULL || last != start);

    return NULL;
}

void insertEnd(struct Node** head_ref, int new_data) {
    struct Node* new_node = newNode(new_data);
    struct Node* last = *head_ref;
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }
    while (last->next != NULL)
        last = last->next;
    last->next = new_node;
}

void displayList(struct Node* node) {
    while (node != NULL) {
        printf("%d -> ", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main() 
{
    struct Node* head = NULL;
    int n, value;

    printf("Enter the number of elements in the linked list: ");
    scanf("%d", &n);
    printf("Enter the elements of the linked list:\n");

    for (int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertEnd(&head, data);
    }

    printf("The linked list is:\n");
    displayList(head);

    printf("Enter the value to search for: ");
    scanf("%d", &value);

    struct Node* result = binarySearch(head, value);
    if (result == NULL)
        printf("Value not present in the linked list.\n");
    else
        printf("Value %d found in the linked list.\n", result->data);

    return 0;
}

