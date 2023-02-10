#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef char element; // char �ڷ����� element ����

typedef struct { // linked list�� ����ü
    element data;
    struct stackNode* link;
} stackNode;

typedef struct { // capacity�� top�� �����ϴ� ���� ����ü ����
    int capacity;
    struct stackNode* top;
} LinkedStack;


LinkedStack* createStack() { // ���� �ʱ�ȭ
    LinkedStack* S = (LinkedStack*)malloc(sizeof(LinkedStack)); // ������ ���� �޸� �Ҵ�
    S->capacity = 10; // ���� : capacity�� 10���� �ʱ�ȭ
    S->top = NULL; // top�� NULL�� �ʱ�ȭ
    return S;
}

LinkedStack* PUSH(LinkedStack* S, element n) { // PUSH : ���ÿ� ���� �ִ� PUSH �Լ�
    stackNode* tmp = (stackNode*)malloc(sizeof(stackNode)); // listnode�� ���� �޸� �Ҵ�
    tmp->data = n;

    if (isEmpty(S)) { // ���ÿ� ���� ���� ��
        S->top = tmp;
        tmp->link = NULL; // ���� node�� ���⶧���� link���� NULL �Է�
    }
    else if (isfull(S)) { // ������ �Ѱ�ġ���� á�� ��
        printf("���� �����÷ο�\n");
    }
    else { // ����
        tmp->link = S->top; // link�� �̵�
        S->top = tmp; // top ����
    }
    return S;
}

char POP(LinkedStack* S) { // POP : ������ ž�� ����ϰ� ����
    stackNode* tmp = NULL;
    char ch;
    if (isEmpty(S)) { // ���ÿ� ���� ���� ��
        printf("���� ���� ����\n");
    }
    else {
        tmp = S->top; // tmp�� top���� �Ҵ�
        ch = tmp->data;
        S->top = tmp->link; // top node�� ���� ��带 top�� �Է�
        free(tmp); // top node�� �޸� �ʱ�ȭ
    }
    return ch;
}

void PEEK(LinkedStack* S) { // PEEK : ������ top�� ���
    stackNode* tmp = NULL;
    if (isEmpty(S)) {
        printf("���� ���� ����\n");
    }
    else {
        tmp = S->top; // ���� top�� �ּҸ� tmp node�� �Ҵ�
    }
    return;
}


int isEmpty(LinkedStack* S) { // ����ִ��� Ȯ��
    return (S->top == NULL);
}
int isfull(LinkedStack* S) { // ������ ��ȭ���θ� ��ȯ�ϴ� �Լ�
    int n = 0;
    stackNode* p = S->top;
    while (p->link != NULL) {
        p = p->link;
        n++;
    }
    return (n == S->capacity - 1);
}

void printStack(LinkedStack* S) { // ���� ��� �Լ�
    int n = 0;
    stackNode* p = S->top;
    if (isEmpty(S)) {
        printf("���ÿ� ���� �����ϴ�.\n");
    }
    else {
        while (p != NULL) {
            printf("[%d] -> ", p->data); // top���� ���ʴ�� ���
            p = p->link;
        }
        printf("\n");
    }
    return;
}
void deleteStack(LinkedStack* S) { // ���� ���� �Լ�
    printf("\n==========���� �Ϸ�==========\n");
    while (!isEmpty(S)) { // listnode�� �ݺ��Ͽ� ����
        stackNode* tmp = NULL;
        tmp = S->top;
        S->top = tmp->link;
        free(tmp); // node�� ����
    }
    free(S); // ���� ����ü ����
    return;
}

void check_matching(char* expr, LinkedStack* S) { // ��ȣ üũ �Լ�
    int i = 0;
    element ch; // ��ȣ�� ������ ���� ����
    printf("%s\n", expr);
    while (expr[i] != NULL) {
        ch = expr[i++]; // �迭�� ������ ���ڿ��� ���ʴ�� �Է�
        switch (ch) { // ch�� ���¿� ���� case ����
        case '(': case '[': case '{': { // ���� ��ȣ�� �� ���� push
            printf("%c ", ch);
            PUSH(S, ch);
            break;
        }
        case ')': { // �ݴ� �Ұ�ȣ�ϋ�
            printf("%c ", ch);
            if (isEmpty(S)) { // �ݴ°�ȣ�� ������ ���� ���°�ȣ�� ���ÿ� ���� ��
                printf("\nno open bracket !\n");
                exit(1);
            }
            else {
                if (POP(S) != '(') { // ���°�ȣ�� �Ұ�ȣ�� �ƴ� ��
                    printf("\nwrong pair !\n");
                    exit(1);
                }
            }
            break;
        }
        case '}': { // �ݴ� �߰�ȣ�ϋ�
            printf("%c ", ch);
            if (isEmpty(S)) { // �ݴ°�ȣ�� ������ ���� ���°�ȣ�� ���ÿ� ���� ��
                printf("\nno open bracket !\n");
                exit(1);
            }
            else {
                if (POP(S) != '{') { // ���°�ȣ�� �߰�ȣ�� �ƴ� ��
                    printf("\nwrong pair !\n");
                    exit(1);
                }
            }
            break;
        }
        case ']': { // �ݴ� ���ȣ�ϋ�
            printf("%c ", ch);
            if (isEmpty(S)) { // �ݴ°�ȣ�� ������ ���� ���°�ȣ�� ���ÿ� ���� ��
                printf("\nno open bracket !\n");
                exit(1);
            }
            else {
                if (POP(S) != '[') { // ���°�ȣ�� ���ȣ�� �ƴ� ��
                    printf("\nwrong pair !\n");
                    exit(1);
                }
            }
            break;
        }
        }
    }
    if (!isEmpty(S)) { // �ݴ°�ȣ�� ���� �˻��Ͽ����� ���°�ȣ�� ���ÿ� ������ ��
        printf("\nno closed bracket !\n");
        exit(1);
    }
    printf("\nBracket Check Completed !\n"); // switch������ ���������� ���������� ��
    return;
}

int main(void) {
    LinkedStack* myS; // linkedstack ���� ����
    myS = createStack(); // ���� �ʱ�ȭ

    //char* exp = "[({2+3}*4)+9]"; // ���� ���
    //char* exp = "[({2+3*4)}+9]"; // wrong pair
    //char* exp = "[({2+3}*4)+9"; // no closed bracket
    char* exp = "({2+3}*4)+9]"; // no open bracket

    check_matching(exp, myS); // ��ȣ üũ

    deleteStack(&myS); // ���� ��� ����

    return 0;
}