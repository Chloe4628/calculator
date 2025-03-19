// 栈实现 算术表达式 
#include <stdio.h> 
#include <stdlib.h>

#define MAX_SIZE 1000

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -1 

int mat[7][7] = {
	{1,1,-1,-1,-1,1,1},
	{1,1,-1,-1,-1,1,1},
	{1,1,1,1,-1,1,1},
	{1,1,1,1,-1,1,1},
	{-1,-1,-1,-1,-1,0,-2},
	{1,1,1,1,-2,1,1},
	{-1,-1,-1,-1,-1,-2,0}
};

typedef int Status;
typedef char OptrType;
typedef int NumType;

typedef struct{
	OptrType data[MAX_SIZE]; 
	int top;
}OptrStack;

typedef struct{
	NumType data[MAX_SIZE];
	int top;
}NumStack;

Status Init_Stack(OptrStack &s);
Status IsEmpty(OptrStack s);
Status IsFull(OptrStack s);
Status Push(OptrStack &s, OptrType e);
Status Pop(OptrStack &s, OptrType &e);
Status GetTop(OptrStack s, OptrType &e);

Status Init_Stack(NumStack &s);
Status IsEmpty(NumStack s);
Status IsFull(NumStack s);
Status Push(NumStack &s, NumType e);
Status Pop(NumStack &s, NumType &e);
Status GetTop(NumStack s, NumType &e);

Status trans(int a);
Status cmp(int x, int y);
NumType operate(int a, int b, char e);
NumType calculate();

int main(){
	printf("%d", calculate());	
	return 0;
}

Status Init_Stack(OptrStack &s){
	s.top = -1;
	return OK;
}

Status IsEmpty(OptrStack s){
	if (s.top != -1){
		return FALSE;
	} else {
		return TRUE;
	}
}

Status IsFull(OptrStack s){
	if (s.top != MAX_SIZE - 1){
		return FALSE;
	} else {
		return TRUE;
	}
}

Status Push(OptrStack &s, OptrType e){
	if (IsFull(s)){
		return OVERFLOW;
	}
	s.top++;
	s.data[s.top] = e;
	return OK;
}

Status Pop(OptrStack &s, OptrType &e){
	if (IsEmpty(s)){
		return OVERFLOW;
	}
	e = s.data[s.top];
	s.top--;
	return OK;
}

Status GetTop(OptrStack s, OptrType &e){
	if (IsEmpty(s)){
		return ERROR;
	}
	e = s.data[s.top];
	return OK;
}

Status Init_Stack(NumStack &s){
	s.top = -1;
	return OK;
}

Status IsEmpty(NumStack s){
	if (s.top != -1){
		return FALSE;
	} else {
		return TRUE;
	}
}

Status IsFull(NumStack s){
	if (s.top != MAX_SIZE - 1){
		return FALSE;
	} else {
		return TRUE;
	}
}

Status Push(NumStack &s, NumType e){
	if (IsFull(s)){
		return OVERFLOW;
	}
	s.top++;
	s.data[s.top] = e;
	return OK;
}

Status Pop(NumStack &s, NumType &e){
	if (IsEmpty(s)){
		return OVERFLOW;
	}
	e = s.data[s.top];
	s.top--;
	return OK;
}

Status GetTop(NumStack s, NumType &e){
	if (IsEmpty(s)){
		return ERROR;
	}
	e = s.data[s.top];
	return OK;
}

Status trans(int a){
	// 0-6运算符 7其他 8数字 
	Status ret;
	if (a >= '0' && a <= '9'){
		return 8;
	}
	switch (a){
		case '+': ret = 0; break;
		case '-': ret = 1; break;
		case '*': ret = 2; break;
		case '/': ret = 3; break;
		case '(': ret = 4; break;
		case ')': ret = 5; break;
		case '#': ret = 6; break;
		default: ret = 7; break;
	}
	return ret;
}

Status cmp(int x, int y){
	return mat[trans(x)][trans(y)];
}

NumType operate(int a, int b, char e){
	NumType ret;
	switch (e){
		case '+': ret = a + b; break;
		case '-': ret = a - b; break;
		case '*': ret = a * b; break;
		case '/': ret = a / b; break;
	}
	return ret;
}

NumType calculate(){
	puts("please enter the string until #:"); 
	OptrStack optr;
	NumStack opnd;
	NumType num = 0, ret; // 临时存储多位数
	Status flag_num = 0; // 是否是数字的标志 
	
	Init_Stack(optr);
	Init_Stack(opnd);
	Push(optr, '#');
	
	OptrType ch, top_optr, e;
	ch = getchar();
	GetTop(optr, top_optr);
	while (ch != '#' || top_optr != '#'){
		while (trans(ch) == 8){
			flag_num = 1;
			num = num * 10 + ch - '0';
			ch = getchar();
		}
		if (flag_num){
			Push(opnd, num);
			// 还原 
			num = 0;
			flag_num = 0;
		}
		if (trans(ch) >= 0 && trans(ch) <= 6){
			GetTop(optr, e);
			if (cmp(e, ch) == -1){
				Push(optr, ch);
				ch = getchar();
			} else if (cmp(e, ch) == 1){
				Pop(optr, e);
				int a, b;
				Pop(opnd, b);
				Pop(opnd, a);
				num = operate(a, b, e);
				Push(opnd, num);
				// 还原 
				num = 0;
				// 不用读取 和optr前一个继续比较 
			} else if (cmp(e, ch) == 0){
				Pop(optr, e);
				ch = getchar();
			}
		} else {
			ch = getchar();
		}
		GetTop(optr, top_optr);
	}
	Pop(opnd, ret);
	return ret;
}
