#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int main()
{

	FILE* fp = fopen("test.txt", "r");  //test파일을 r(읽기) 모드로 열기
    char buffer[MAX] = { 0, };

    fread(buffer, 1, MAX, fp); //전체 읽기
    printf("%s", buffer);

    fclose(fp); //파일 포인터 닫기
	
    
	return 0;
}
int ch, i;
    FILE * fp = fopen("temp/data.txt", "rt");

    if(fp == NULL){
        printf("data.txt 파일이 존재하지 않습니다. \n");
        return -1;
    }

    for(i=0; i<3; i++){
        int ch = fgetc(fp);
        printf("%c \n", ch);
    }

    fclose(fp); // 스트림의 종료
    return 0;