#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define PI 3.141592
typedef struct{
	char* name;
	int id;
	int kor;
} Student;
typedef struct{
	int num;
	Student** head;
} Class;
typedef struct{
	int key; // index...? key값
	int UB, LB; // upper bound, lower bound
	int count; // 몇 개 카운트...?
} Range;

typedef struct{
	float med;
	float avg;
	double std;
	double skew;
	Range* range;	

} Summary;


void ReadData(char* name, Class* myclass);
void SWAP_STD(Class* myclass, int x, int y);
void sort(Class* myclass);
void CreateClass(Class* class, int num);
void CreateSummary(Summary* summary);
void printClass(Class* myclass);

long sum_kor(Class* myclass);
float med_kor(Class* myclass);
float avg_kor(Class* myclass);

double std_kor(Class* myclass);
void SummaryStd(Class* myclass, Summary* summary);

void SummarySum(Class* myclass, Summary* summary);
double square(double x);
void hist(Class* myclass, int* a);

double skewness(Class* myclass);
void SummarySkew(Class* myclass, Summary* summary);

int NumOfOutlier(Class* myclass);
void PrintOutlier(Class* myclass);

int main(void)
{
	Class myclass;
	Summary summary;
	
	// create("sample.txt", 300000);
	
	CreateClass(&myclass, 100000);
	CreateSummary(&summary);
	ReadData("score.txt", &myclass);
	SummarySkew(&myclass, &summary);
	printf("%lf\n", summary.skew);
    // printf("%lf \n", avg_kor(&myclass));
    // printf("%lf \n", med_kor(&myclass));
	// printf("%lf \n", std_kor(&myclass));
	
	// int a[20] = { 0, };
	// hist(&myclass, a);
	// for(int i = 0; i<20; i++)
	// 	printf("%d ", a[i]);
	
	// printf("%d\n", NumOfOutlier(&myclass));
	// PrintOutlier(&myclass);

	// sort(&myclass);
	// printf("%d \n", myclass.head[0]->kor);
	// printf("%d \n", myclass.head[1]->kor);
	// printf("%d \n", myclass.num);
	// printf("%d \n", myclass.head[myclass.num/2]->kor);
    // printf("after sorting\n\n");
	// SummarySum(&myclass, &summary);
	// printf("%d", summary.kor_summary[0]);
	// printClass(&myclass);
	

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
    }
}
void CreateSummary(Summary* summary){
	// summary->when_exam = when;
	summary->avg = 0;
	summary->med = 0;
	summary->range = NULL;
	summary->skew = 0;
	summary->std = 0;
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
void sort(Class* myclass){
	int min;
    for (int i = 0; i < myclass->num-1; i++)
    {
        min = i;
		for (int j = i + 1; j < myclass->num; j++)
		{
		// Find an index with the minimum element.
			if (myclass->head[j]->kor < myclass->head[min]->kor)
				min = j;
		}
    	// Exchange the minimum element and the i-th element.
        SWAP_STD(myclass, min, i);
    }
}

void SWAP_STD(Class* myclass, int x, int y){
	Student* temp;
	temp = myclass->head[x];
	myclass->head[x] = myclass->head[y];
	myclass->head[y] = temp;
}
void printClass(Class* myclass){
	for(int i=0; i < myclass->num; i++)
		printf("%d %d\n", myclass->head[i]->id, myclass->head[i]->kor);
}
long sum_kor(Class* myclass){
	int result = 0;
	for(int i=0; i < myclass->num; i++)
		result += myclass->head[i]->kor;

	return result;
}
void SummaryAvg(Class* myclass, Summary* summary){

}
// void SummarySum(Class* myclass, Summary* summary){
// 	summary->kor_summary[0] = 0;
// 	for(int i=0; i < myclass->num; i++)
// 		summary->kor_summary[0] += myclass->head[i]->kor;
// }

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

float avg_kor(Class* myclass){
	float result;
	result = (float)sum_kor(myclass)/myclass->num;

	return result;
}
double std_kor(Class* myclass){
    double result = 0;
    for(int i = 0; i<myclass->num; i++)
        result += (myclass->head[i]->kor - avg_kor(myclass)) * (myclass->head[i]->kor - avg_kor(myclass));
    
	return sqrt(result/(myclass->num-1));
}
void SummaryStd(Class* myclass, Summary* summary){
	summary->std = 0;

	for(int i = 0; i<myclass->num; i++)
        summary->std += (myclass->head[i]->kor - avg_kor(myclass)) * (myclass->head[i]->kor - avg_kor(myclass));
}
double square(double x){
    return x*x;
}
void hist(Class* myclass, int* a){
	for(int i = 0; i<myclass->num; i++){
		if(myclass->head[i]->kor <= 5) a[0]++;
		else if(myclass->head[i]->kor <= 10) a[1]++;
		else if(myclass->head[i]->kor <= 15) a[2]++;
		else if(myclass->head[i]->kor <= 20) a[3]++;
		else if(myclass->head[i]->kor <= 25) a[4]++;
		else if(myclass->head[i]->kor <= 30) a[5]++;
		else if(myclass->head[i]->kor <= 35) a[6]++;
		else if(myclass->head[i]->kor <= 40) a[7]++;
		else if(myclass->head[i]->kor <= 45) a[8]++;
		else if(myclass->head[i]->kor <= 50) a[9]++;
		else if(myclass->head[i]->kor <= 55) a[10]++;
		else if(myclass->head[i]->kor <= 60) a[11]++;
		else if(myclass->head[i]->kor <= 65) a[12]++;
		else if(myclass->head[i]->kor <= 70) a[13]++;
		else if(myclass->head[i]->kor <= 75) a[14]++;
		else if(myclass->head[i]->kor <= 80) a[15]++;
		else if(myclass->head[i]->kor <= 85) a[16]++;
		else if(myclass->head[i]->kor <= 90) a[17]++;
		else if(myclass->head[i]->kor <= 95) a[18]++;
		else a[19]++;
	}
}
double skewness(Class* myclass){
	double result = 0;
	for(int i = 0; i<myclass->num; i++) {
		result += pow((myclass->head[i]->kor - avg_kor(myclass)), 3);
	}
	return result/pow(std_kor(myclass), 3)/myclass->num; 
}
void SummarySkew(Class* myclass, Summary* summary){
	summary->skew = 0;

	for(int i = 0; i<myclass->num; i++)
        summary->skew += pow((myclass->head[i]->kor - avg_kor(myclass)), 3)/myclass->num;

	summary->skew /= pow(std_kor(myclass), 3); 
}

int NumOfOutlier(Class* myclass){
	int count = 0;

	sort(myclass);
	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->kor;
	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->kor;

	float LC = Q1 - 1.5 * (Q3 - Q1); 
	float UC = Q3 + 1.5 * (Q3 - Q1);
	for(int i = 0; i<myclass->num; i++) {
		if(myclass->head[i]->kor < LC) count++;
		else if(myclass->head[i]->kor > UC) count++; 
	}
	// for (int i = 0; i<20; i++) {
	// 	if(i < Q1/5)
	// 		count++;
	// 	if(i >= Q3/5)
	// 		count++;
	// }

	return count;
}
void PrintOutlier(Class* myclass){
	sort(myclass);

	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->kor;
	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->kor;

	float LC = Q1 - 1.5 * (Q3 - Q1); 
	float UC = Q3 + 1.5 * (Q3 - Q1);

	for(int i = 0; i<=100; i++){
		if(i < LC) printf("%d ", i);
	}
	printf("\n");
	for(int i = 0; i<=100; i++){
		if(i > UC) printf("%d ", i);
	}
	
}
int* outlier(Class* myclass){
	int* a = (int*)malloc(sizeof(int)*20);
	
	sort(myclass);
	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->kor;
	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->kor;

	float LC = Q1 - 1.5 * (Q3 - Q1); 
	float UC = Q3 + 1.5 * (Q3 - Q1);

	int* b;
	hist(myclass, b);

	for (int i = 0; i<20; i++) {
		if(i < Q1/5)
			a[i]++;
		if(i >= Q3/5)
			a[i]++;
	}

	return a;
}