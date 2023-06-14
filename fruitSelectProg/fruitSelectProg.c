#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* element;

typedef struct DListNode {
    element data;
    struct DListNode* prev;
    struct DListNode* next;
} DListNode;

DListNode* selectedFruit = NULL;
DListNode* head = NULL;
DListNode* tail = NULL;

// 초기화
void init() {
    head = (DListNode*)malloc(sizeof(DListNode));
    tail = (DListNode*)malloc(sizeof(DListNode));

    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    tail->next = NULL;
}

// 다음으로 이동
void nextFruit() {
    if (selectedFruit != NULL && selectedFruit->next != tail) {
        selectedFruit = selectedFruit->next;
    }
}

// 이전으로 이동
void prevFruit() {
    if (selectedFruit != NULL && selectedFruit->prev != head) {
        selectedFruit = selectedFruit->prev;
    }
}

// 과일 추가
void insertFruit(element fruit) {
    DListNode* newNode = (DListNode*)malloc(sizeof(DListNode));
    newNode->data = (element)malloc(strlen(fruit) + 1);
    strcpy(newNode->data, fruit);

    if (selectedFruit != NULL) {
        newNode->prev = selectedFruit;
        newNode->next = selectedFruit->next;
        selectedFruit->next->prev = newNode;
        selectedFruit->next = newNode;
    }
    else {
        newNode->prev = head;
        newNode->next = head->next;
        head->next->prev = newNode;
        head->next = newNode;
    }

    selectedFruit = newNode;
}

// 선택한 과일 삭제
void deleteSelectedFruit() {
    if (selectedFruit == NULL) {
        printf("There is no selected fruit.\n");
        return;
    }

    selectedFruit->prev->next = selectedFruit->next;
    selectedFruit->next->prev = selectedFruit->prev;

    free(selectedFruit->data);
    free(selectedFruit);
    selectedFruit = NULL;
}

// 과일 리스트 출력
void printFruitList() {
    DListNode* current = head->next;

    while (current != tail) {
        printf("%s", current->data);
        if (current == selectedFruit) {
            printf(" [O]");
        }
        printf("\n");
        current = current->next;
    }
    printf("\n");
}

// 메뉴 출력
void printMenu() {
    printf("==== Menu ====\n");
    printf("n) Next fruit\n");
    printf("p) Previous fruit\n");
    printf("d) Delete the current fruit\n");
    printf("i) Insert fruit after the current fruit\n");
    printf("o) Output the fruit list (Show [O] next to the currently selected fruit)\n");
    printf("e) Exit the program\n");
    printf("Select an option: ");
}

int main() {
    init();

    char choice;
    char fruit[100];

    while (1) {
        printMenu();
        scanf(" %c", &choice);
        getchar();  // 개행 문자 제거

        if (choice == 'n') {
            nextFruit();
        }
        else if (choice == 'p') {
            prevFruit();
        }
        else if (choice == 'd') {
            deleteSelectedFruit();
        }
        else if (choice == 'i') {
            printf("Enter the name of the fruit to add: ");
            scanf(" %s", fruit);
            insertFruit(fruit);
        }
        else if (choice == 'o') {
            printFruitList();
        }
        else if (choice == 'e') {
            DListNode* current = head->next;
            while (current != tail) {
                DListNode* next = current->next;
                free(current->data);
                free(current);
                current = next;
            }
            free(head);
            free(tail);
            printf("Exit program.\n");
            break;
        }
        else {
            printf("Invalid menu selection.\n");
        }
        printf("\n");
    }

    return 0;
}
