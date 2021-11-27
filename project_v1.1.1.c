#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
typedef struct{
	char* name;
	int id;
	int score;
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
	float avg;
	int med, Q1, Q3;
	double std;
	double skew;
	double kurtosis;
	Range* range;	
	int Outlier;
} Summary;	

void ReadData(char* name, Class* myclass);
void SWAP_STD(Class* myclass, int x, int y);
void CreateClass(Class* class, int num);
void CreateSummary(Summary* summary);
void printClass(Class* myclass);
long sum_score(Class* myclass);
void SummaryAvg(Class* myclass, Summary* summary);
void sort(Class* myclass);
void SummaryMed(Class* myclass, Summary* summary);
void SummaryStd(Class* myclass, Summary* summary);
void SummarySkew(Class* myclass, Summary* summary);
void SummaryKurto(Class* myclass, Summary* summary);
double square(double x);
void CreateRange(Summary* summary);
void SummaryHists(Class* myclass, Summary* summary);
void NumOfOutlier(Class* myclass, Summary* summary);
void PrintOutlier(Class* myclass);

int main(void)
{
	Class myclass;
	Summary summary;
	
	
	CreateClass(&myclass, 100000);
	CreateSummary(&summary);
	CreateRange(&summary);
	ReadData("score.txt", &myclass);

	SummaryAvg(&myclass, &summary);
	SummaryMed(&myclass, &summary);
	SummaryStd(&myclass, &summary);
	SummarySkew(&myclass, &summary);
	SummaryKurto(&myclass, &summary);


	printf("%lf\n", summary.avg);
	printf("%d %d %d\n", summary.Q1, summary.med, summary.Q3);
	printf("%lf\n", summary.std);
	printf("%lf\n", summary.skew);
	printf("%lf\n", summary.kurtosis);

	SummaryHists(&myclass, &summary);
	for(int i = 0; i<20; i++)
		printf("%d ", summary.range[i].count);
	
	printf("\n");

	NumOfOutlier(&myclass, &summary);
	printf("%d\n", summary.Outlier);

	return 0;
}

void CreateClass(Class* class, int num)
{
    class->num = num;
    class->head = (Student **)malloc(sizeof(Student*)* num);
    for (int i = 0; i < num; i++) {
    // Make a dummy node.
        class->head[i] = (Student *)malloc(sizeof(Student));
        class->head[i]->score = 0;
    }
}
void CreateSummary(Summary* summary){
	// summary->when_exam = when;
	summary->avg = 0;
	summary->med = 0;
	summary->range = NULL;
	summary->skew = 0;
	summary->kurtosis = 0;
	summary->std = 0;
}
void ReadData(char* name, Class* myclass){
	FILE* fp = fopen(name, "r");  //test파일을 r(읽기) 모드로 열기
	if(fp == NULL){
        printf("파일이 존재하지 않습니다. \n");
        exit(1);
	}
	for(int i=0; i < myclass->num; i++){
		fscanf(fp, "%d", &myclass->head[i]->score);
		myclass->head[i]->id = i+1;
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
		printf("%d %d\n", myclass->head[i]->id, myclass->head[i]->score);
}

long sum_score(Class* myclass){
	int result = 0;
	for(int i=0; i < myclass->num; i++)
		result += myclass->head[i]->score;

	return result;
}
float avg_score(Class* myclass){
	float result;
	result = (float)sum_score(myclass)/myclass->num;

	return result;
}

void SummaryAvg(Class* myclass, Summary* summary){
	summary->avg = (float)sum_score(myclass)/myclass->num;
}



void sort(Class* myclass){
	int min;
    for (int i = 0; i < myclass->num-1; i++)
    {
        min = i;
		for (int j = i + 1; j < myclass->num; j++)
		{
		// Find an index with the minimum element.
			if (myclass->head[j]->score < myclass->head[min]->score)
				min = j;
		}
    	// Exchange the minimum element and the i-th element.
        SWAP_STD(myclass, min, i);
    }
}
void SummaryMed(Class* myclass, Summary* summary){	
	sort(myclass); 

	summary->med = myclass->head[(int) (myclass->num * 0.5)]->score;
	summary->Q1 = myclass->head[(int) (myclass->num * 0.25)]->score;
	summary->Q3 = myclass->head[(int) (myclass->num * 0.75)]->score;
}
float med_score(Class* myclass){
	sort(myclass); 
	int idx, result;
	if(myclass->num % 2 == 0){
		idx = myclass->num/2;
		result = (myclass->head[idx-1]->score + myclass->head[idx]->score)/2; 
		return result;
	} else {
		idx = myclass -> num/2;
		result = myclass->head[idx]->score;
		return result;
	}
}


void SummaryStd(Class* myclass, Summary* summary){
	summary->std = 0;

	for(int i = 0; i<myclass->num; i++)
        summary->std += (myclass->head[i]->score - avg_score(myclass)) * (myclass->head[i]->score - avg_score(myclass));
	summary->std = summary->std/(myclass->num - 1);
	summary->std = sqrt(summary->std);
}

void SummarySkew(Class* myclass, Summary* summary){
	summary->skew = 0;

	SummaryStd(myclass, summary);

	for(int i = 0; i<myclass->num; i++)
        summary->skew += pow((myclass->head[i]->score - avg_score(myclass)), 3) / myclass->num / pow(summary->std, 3);
}

void SummaryKurto(Class* myclass, Summary* summary){
	summary->kurtosis = 0;

	SummaryStd(myclass, summary);

	for(int i = 0; i<myclass->num; i++)
        summary->kurtosis += pow((myclass->head[i]->score - avg_score(myclass)), 4) / myclass->num / pow(summary->std, 4);
}

void CreateRange(Summary* summary){
	Range* a = (Range*)malloc(sizeof(Range)*20);
	summary->range = a;
	for(int i = 0; i < 20; i++){
		summary->range[i].key = i;
		summary->range[i].count = 0;
		summary->range[i].LB = 5*i+1;
		summary->range[i].UB = 5*(i+1);
	}

	summary->range[0].LB = 0;
}

void SummaryHists(Class* myclass, Summary* summary){
	summary->range = (Range* )malloc(sizeof(Range)*20);
	summary->range[0].count++;
	for(int i = 0; i<myclass->num; i++){
		if(myclass->head[i]->score <= 5) summary->range[0].count++;
		else if(myclass->head[i]->score <= 10) summary->range[1].count++;
		else if(myclass->head[i]->score <= 15) summary->range[2].count++;
		else if(myclass->head[i]->score <= 20) summary->range[3].count++;
		else if(myclass->head[i]->score <= 25) summary->range[4].count++;
		else if(myclass->head[i]->score <= 30) summary->range[5].count++;
		else if(myclass->head[i]->score <= 35) summary->range[6].count++;
		else if(myclass->head[i]->score <= 40) summary->range[7].count++;
		else if(myclass->head[i]->score <= 45) summary->range[8].count++;
		else if(myclass->head[i]->score <= 50) summary->range[9].count++;
		else if(myclass->head[i]->score <= 55) summary->range[10].count++;
		else if(myclass->head[i]->score <= 60) summary->range[11].count++;
		else if(myclass->head[i]->score <= 65) summary->range[12].count++;
		else if(myclass->head[i]->score <= 70) summary->range[13].count++;
		else if(myclass->head[i]->score <= 75) summary->range[14].count++;
		else if(myclass->head[i]->score <= 80) summary->range[15].count++;
		else if(myclass->head[i]->score <= 85) summary->range[16].count++;
		else if(myclass->head[i]->score <= 90) summary->range[17].count++;
		else if(myclass->head[i]->score <= 95) summary->range[18].count++;
		else summary->range[19].count++;
	}
}

void NumOfOutlier(Class* myclass, Summary* summary){
	int count = 0;

	sort(myclass);
	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->score;
	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->score;

	float LC = Q1 - 1.5 * (Q3 - Q1); 
	float UC = Q3 + 1.5 * (Q3 - Q1);

	for(int i = 0; i<myclass->num; i++) {
		if(myclass->head[i]->score < LC) count++;
		else if(myclass->head[i]->score > UC) count++; 
	}

	summary->Outlier = count;
}

void PrintOutlier(Class* myclass){
	sort(myclass);

	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->score;
	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->score;

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


// int* outlier(Class* myclass){
// 	int* a = (int*)malloc(sizeof(int)*20);
	
// 	sort(myclass);
// 	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->score;
// 	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->score;

// 	float LC = Q1 - 1.5 * (Q3 - Q1); 
// 	float UC = Q3 + 1.5 * (Q3 - Q1);

// 	int* b;
// 	hist(myclass, b);

// 	for (int i = 0; i<20; i++) {
// 		if(i < Q1/5)
// 			a[i]++;
// 		if(i >= Q3/5)
// 			a[i]++;
// 	}

// 	return a;
// }