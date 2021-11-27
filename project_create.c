#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int main()
{
    FILE* fp = fopen("test.txt","w"); //test파일을 w(쓰기) 모드로 열기
	int num;
	
    for (int i = 0; i < MAX; i++) {
        fprintf(fp, "%d %d %d %d\n", i, rand() % (100+1-10) + 10, rand() % (100+1-10) + 10, rand() % (100+1-10) + 10); //문자열 입력
    }

    fclose(fp); //파일 포인터 닫기


	
    
	return 0;
}