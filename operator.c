#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef char element; // char 자료형인 element 선언

typedef struct { // linked list의 구조체
    element data;
    struct stackNode* link;
} stackNode;

typedef struct { // capacity와 top을 저장하는 스택 구조체 선언
    int capacity;
    struct stackNode* top;
} LinkedStack;


LinkedStack* createStack() { // 스택 초기화
    LinkedStack* S = (LinkedStack*)malloc(sizeof(LinkedStack)); // 스택의 동적 메모리 할당
    S->capacity = 10; // 스택 : capacity을 10으로 초기화
    S->top = NULL; // top을 NULL로 초기화
    return S;
}

LinkedStack* PUSH(LinkedStack* S, element n) { // PUSH : 스택에 값을 넣는 PUSH 함수
    stackNode* tmp = (stackNode*)malloc(sizeof(stackNode)); // listnode에 동적 메모리 할당
    tmp->data = n;

    if (isEmpty(S)) { // 스택에 값이 없을 때
        S->top = tmp;
        tmp->link = NULL; // 이전 node가 없기때문에 link값에 NULL 입력
    }
    else if (isfull(S)) { // 스택이 한계치까지 찼을 때
        printf("스택 오버플로우\n");
    }
    else { // 정상
        tmp->link = S->top; // link를 이동
        S->top = tmp; // top 이전
    }
    return S;
}

char POP(LinkedStack* S) { // POP : 스택의 탑을 출력하고 제거
    stackNode* tmp = NULL;
    char ch;
    if (isEmpty(S)) { // 스택에 값이 없을 때
        printf("스택 공백 에러\n");
    }
    else {
        tmp = S->top; // tmp에 top값을 할당
        ch = tmp->data;
        S->top = tmp->link; // top node의 다음 노드를 top에 입력
        free(tmp); // top node의 메모리 초기화
    }
    return ch;
}

void PEEK(LinkedStack* S) { // PEEK : 스택의 top을 출력
    stackNode* tmp = NULL;
    if (isEmpty(S)) {
        printf("스택 공백 에러\n");
    }
    else {
        tmp = S->top; // 현재 top의 주소를 tmp node에 할당
    }
    return;
}


int isEmpty(LinkedStack* S) { // 비어있는지 확인
    return (S->top == NULL);
}
int isfull(LinkedStack* S) { // 스택의 포화여부를 반환하는 함수
    int n = 0;
    stackNode* p = S->top;
    while (p->link != NULL) {
        p = p->link;
        n++;
    }
    return (n == S->capacity - 1);
}

void printStack(LinkedStack* S) { // 스택 출력 함수
    int n = 0;
    stackNode* p = S->top;
    if (isEmpty(S)) {
        printf("스택에 값이 없습니다.\n");
    }
    else {
        while (p != NULL) {
            printf("[%d] -> ", p->data); // top부터 차례대로 출력
            p = p->link;
        }
        printf("\n");
    }
    return;
}
void deleteStack(LinkedStack* S) { // 스택 삭제 함수
    printf("\n==========삭제 완료==========\n");
    while (!isEmpty(S)) { // listnode를 반복하여 삭제
        stackNode* tmp = NULL;
        tmp = S->top;
        S->top = tmp->link;
        free(tmp); // node를 삭제
    }
    free(S); // 스택 구조체 삭제
    return;
}

void check_matching(char* expr, LinkedStack* S) { // 괄호 체크 함수
    int i = 0;
    element ch; // 괄호를 저장할 변수 선언
    printf("%s\n", expr);
    while (expr[i] != NULL) {
        ch = expr[i++]; // 배열의 형태인 문자열을 차례대로 입력
        switch (ch) { // ch의 상태에 따라 case 실행
        case '(': case '[': case '{': { // 여는 괄호일 때 값을 push
            printf("%c ", ch);
            PUSH(S, ch);
            break;
        }
        case ')': { // 닫는 소괄호일떄
            printf("%c ", ch);
            if (isEmpty(S)) { // 닫는괄호가 있지만 비교할 여는괄호가 스택에 없을 때
                printf("\nno open bracket !\n");
                exit(1);
            }
            else {
                if (POP(S) != '(') { // 여는괄호가 소괄호가 아닐 떄
                    printf("\nwrong pair !\n");
                    exit(1);
                }
            }
            break;
        }
        case '}': { // 닫는 중괄호일떄
            printf("%c ", ch);
            if (isEmpty(S)) { // 닫는괄호가 있지만 비교할 여는괄호가 스택에 없을 때
                printf("\nno open bracket !\n");
                exit(1);
            }
            else {
                if (POP(S) != '{') { // 여는괄호가 중괄호가 아닐 떄
                    printf("\nwrong pair !\n");
                    exit(1);
                }
            }
            break;
        }
        case ']': { // 닫는 대괄호일떄
            printf("%c ", ch);
            if (isEmpty(S)) { // 닫는괄호가 있지만 비교할 여는괄호가 스택에 없을 때
                printf("\nno open bracket !\n");
                exit(1);
            }
            else {
                if (POP(S) != '[') { // 여는괄호가 대괄호가 아닐 떄
                    printf("\nwrong pair !\n");
                    exit(1);
                }
            }
            break;
        }
        }
    }
    if (!isEmpty(S)) { // 닫는괄호를 전부 검사하였지만 여는괄호가 스택에 남았을 때
        printf("\nno closed bracket !\n");
        exit(1);
    }
    printf("\nBracket Check Completed !\n"); // switch문에서 성공적으로 빠져나왔을 때
    return;
}

int main(void) {
    LinkedStack* myS; // linkedstack 변수 선언
    myS = createStack(); // 변수 초기화

    //char* exp = "[({2+3}*4)+9]"; // 정상 출력
    //char* exp = "[({2+3*4)}+9]"; // wrong pair
    //char* exp = "[({2+3}*4)+9"; // no closed bracket
    char* exp = "({2+3}*4)+9]"; // no open bracket

    check_matching(exp, myS); // 괄호 체크

    deleteStack(&myS); // 스택 노드 제거

    return 0;
}