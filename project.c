#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define PI 3.141592
typedef struct{
	char* name;
	int id;
	int kor, eng, math;
} Student;
typedef struct{
	int num;
	Student** head;
} Class;
typedef struct{
	char* when_exam; // middle or final -> what about using bool?
	int kor_summary[3]; // mean, medium, sd ...
	int* eng_summary;
	int* math_summary;
} Summary;

void create(char* name, int num);
void read(char* name, Class* myclass);
void ReadData(char* name, Class* myclass);
int normal(float stddev, float mean);
void SWAP(int x, int y);
void SWAP_STD(Class* myclass, int x, int y);
void sort(Class* myclass);
void CreateClass(Class* class, int num);
void CreateSummary(Summary* summary, char* when);
void printClass(Class* myclass);
long sum_kor(Class* myclass);
long sum_eng(Class* myclass);
long sum_math(Class* myclass);
float med_kor(Class* myclass);
float med_eng(Class* myclass);
float med_math(Class* myclass);
float avg_kor(Class* myclass);
float avg_eng(Class* myclass);
float avg_math(Class* myclass);
void SummarySum(Class* myclass, Summary* summary);

int main(void)
{
	Class myclass;
	Summary summary;
	
	// create("sample.txt", 300000);
	
	CreateClass(&myclass, 300000);
	CreateSummary(&summary, "middle");
	read("sample.txt", &myclass);
	// printf("\n\n");

	sort(&myclass);
	printf("after sorting\n\n");
	SummarySum(&myclass, &summary);
	printf("%d", summary.kor_summary[0]);
	// printClass(&myclass);
	// printf("%ld %ld %ld\n", sum_kor(&myclass),  sum_eng(&myclass),  sum_math(&myclass));
	// printf("%lf %lf %lf\n", med_kor(&myclass),  med_eng(&myclass),  med_math(&myclass));
	// printf("%lf %lf %lf\n", avg_kor(&myclass),  avg_eng(&myclass),  avg_math(&myclass));


	return 0;
}
void CreateClass(Class* class, int num)
{
    class->num = num;
    class->head = (Student **)malloc(sizeof(Student*)* num);
    for (int i = 0; i < num; i++) {
    // Make a dummy node.
        class->head[i] = (Student *)malloc(sizeof(Student));
        class->head[i]->kor = 0;
		class->head[i]->eng = 0;
		class->head[i]->math = 0;
    }
}
void CreateSummary(Summary* summary, char* when){
	summary->when_exam = when;
	for(int i = 0; i<3; i++)
		summary->kor_summary[i] = 0;
	summary->eng_summary = NULL;
	summary->math_summary = NULL;
}
void create(char* name, int num){
	FILE* fp = fopen(name, "w");
	for (int i = 1; i<num+1; i++)
		fprintf(fp, "%d %d %d %d\n", i, normal(10, 60), normal(10, 60), normal(10, 60));
		// fprintf(fp, "%d %d %d %d\n", i, rand() % (100+1-10) + 10, rand() % (100+1-10) + 10, rand() % (100+1-10) + 10);
	fclose(fp);
}
void ReadData(char* name, Class* myclass){
	FILE* fp = fopen(name, "r");  //test파일을 r(읽기) 모드로 열기
	if(fp == NULL){
        printf("파일이 존재하지 않습니다. \n");
        exit(1);
	}
	for(int i=0; i < myclass->num; i++){
		fscanf(fp, "%d", &myclass->head[i]->kor);
		myclass->head[i]->id = i+1;
		// printf("%d %d %d %d\n", myclass->head[i]->id, myclass->head[i]->kor, myclass->head[i]->eng, myclass->head[i]->math);
	}
}
void read(char* name, Class* myclass){
	// myclass->head[0]->kor;
	FILE* fp = fopen(name, "r");  //test파일을 r(읽기) 모드로 열기
	if(fp == NULL){
        printf("파일이 존재하지 않습니다. \n");
        exit(1);
	}

	for(int i=0; i < myclass->num; i++){
		fscanf(fp, "%d %d %d %d", &myclass->head[i]->id, &myclass->head[i]->kor, &myclass->head[i]->eng, &myclass->head[i]->math);
		// printf("%d %d %d %d\n", myclass->head[i]->id, myclass->head[i]->kor, myclass->head[i]->eng, myclass->head[i]->math);
	}
	// &myclass->head[i].id, &myclass->head[i]->kor, &myclass->head[i]->eng, &myclass->head[i]->math
	// myclass->head[i]->id, myclass->head[i]->kor, myclass->head[i]->eng, myclass->head[i]->math
}
int normal(float stddev, float mean)
{
    double r1, r2, z1, result, dt, num;
    int i;

    result = 0.0;
    dt = 1.0/100.0;

    for (i = 0; i < 100; i++)
    {
        r1 = (float)rand() / (float)RAND_MAX;
        r2 = (float)rand() / (float)RAND_MAX;

        z1 = sqrt(-2 * log(r1)) * cos(2 * PI * r2);

        num = (mean * dt) + (stddev *z1 * sqrt(dt));
        result += num;
    }
    return (int)result;
}
void sort(Class* myclass){
	int min;
    for (int i = 0; i < myclass->num; i++)
    {
        min = i;
		for (int j = i + 1; j < myclass->num; j++)
		{
		// Find an index with the minimum element.
			if (myclass->head[j]->kor < myclass->head[i]->kor)
				min = j;
		}
    	// Exchange the minimum element and the i-th element.
        SWAP_STD(myclass, min, i);
		
		// SWAP(myclass->head[i]->kor, myclass->head[min]->kor);
    }
}
void SWAP(int x, int y){
    x += y;
    y = x - y;
    x -= y;
}
void SWAP_STD(Class* myclass, int x, int y){
	Student* temp;
	temp = myclass->head[x];
	myclass->head[x] = myclass->head[y];
	myclass->head[y] = temp;
}
void printClass(Class* myclass){
	for(int i=0; i < myclass->num; i++)
		printf("%d %d %d %d\n", myclass->head[i]->id, myclass->head[i]->kor, myclass->head[i]->eng, myclass->head[i]->math);
}
long sum_kor(Class* myclass){
	int result = 0;
	for(int i=0; i < myclass->num; i++)
		result += myclass->head[i]->kor;

	return result;
}
void SummarySum(Class* myclass, Summary* summary){
	summary->kor_summary[0] = 0;
	for(int i=0; i < myclass->num; i++)
		summary->kor_summary[0] += myclass->head[i]->kor;
}
long sum_eng(Class* myclass){
	int result = 0;
	for(int i=0; i < myclass->num; i++)
		result += myclass->head[i]->eng;

	return result;
}
long sum_math(Class* myclass){
	int result = 0;
	for(int i=0; i < myclass->num; i++)
		result += myclass->head[i]->math;

	return result;
}
float med_kor(Class* myclass){
	sort(myclass); 
	int idx, result;
	if(myclass->num % 2 == 0){
		idx = myclass->num/2;
		result = (myclass->head[idx-1]->kor + myclass->head[idx]->kor)/2; 
		return result;
	} else {
		idx = myclass -> num/2;
		result = myclass->head[idx]->kor;
		return result;
	}
}
float med_eng(Class* myclass){
	sort(myclass); 
	int idx, result;
	if(myclass->num % 2 == 0){
		idx = myclass->num/2;
		result = (myclass->head[idx-1]->eng + myclass->head[idx]->eng)/2; 
		return result;
	} else {
		idx = myclass -> num/2;
		result = myclass->head[idx]->eng;
		return result;
	}
}
float med_math(Class* myclass){
	sort(myclass); 
	int idx, result;
	if(myclass->num % 2 == 0){
		idx = myclass->num/2;
		result = (myclass->head[idx-1]->math + myclass->head[idx]->math)/2; 
		return result;
	} else {
		idx = myclass -> num/2;
		result = myclass->head[idx]->math;
		return result;
	}
}
float avg_kor(Class* myclass){
	int result;
	result = sum_kor(myclass)/myclass->num;

	return result;
}
float avg_eng(Class* myclass){
	int result;
	result = sum_eng(myclass)/myclass->num;

	return result;
}
float avg_math(Class* myclass){
	int result;
	result = sum_math(myclass)/myclass->num;

	return result;
}




// void SelectionSort(Data* list, int n)
// {
//     int min;
//     for (int i = 0; i < n - 1; i++)
//     {
//         min = i;
//     for (int j = i + 1; j < n; j++)
//     {
//     // Find an index with the minimum element.
//         if (list[j] < list[min])
//             min = j;
//     }
//     // Exchange the minimum element and the i-th element.
//         SWAP(list[i], list[min]);
//     }
// }