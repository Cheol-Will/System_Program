#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h> 
typedef struct{
	int id;
	int score;
} Student;
typedef struct{
	int num;
	Student** head;
} Class;
typedef struct{
	int key; 
	int UB, LB; 
	int count; 
} Range;
typedef struct{
	float avg;
	int mode;
	int med;
	int Q1;
	int Q3;
	int min;
	int max;
	double std;
	double skew;
	double kurtosis;
	Range* range;
	int NumOut;
} Summary;	

void ReadData(char* name, Class* myclass);
void SWAP_STD(Class* myclass, int x, int y);
void CreateClass(Class* class, int num);
void CreateSummary(Summary* summary);
long sum_score(Class* myclass);
void SummaryAvg(Class* myclass, Summary* summary);
void SummaryMode(Class* myclass, Summary* summary);
void sort(Class* myclass);
void SummaryMed(Class* myclass, Summary* summary);
void SummaryStd(Class* myclass, Summary* summary);
void SummarySkew(Class* myclass, Summary* summary);
void SummaryKurto(Class* myclass, Summary* summary);
void CreateRange(Summary* summary);
void SummaryHists(Class* myclass, Summary* summary);
void NumOfOutlier(Class* myclass, Summary* summary);
void PrintOutlier(Class* myclass, Summary* summary);

int main(void)
{
	Class myclass;
	Summary summary;
	
	CreateClass(&myclass, 100000);
	CreateSummary(&summary);
	CreateRange(&summary);
	ReadData("score.txt", &myclass);


	SummaryAvg(&myclass, &summary);
	SummaryMode(&myclass, &summary);
	SummaryMed(&myclass, &summary);
	SummaryStd(&myclass, &summary);
	SummarySkew(&myclass, &summary);
	SummaryKurto(&myclass, &summary);

	printf("%lf\n", summary.avg);
	printf("%d %d\n", summary.min, summary.max);
	printf("%d\n", summary.mode);
	printf("%d %d %d\n", summary.Q1, summary.med, summary.Q3);
	printf("%lf\n", summary.std);
	printf("%lf\n", summary.skew);
	printf("%lf\n", summary.kurtosis);

	SummaryHists(&myclass, &summary);
	for(int i = 0; i<20; i++)
		printf("%d ", summary.range[i].count);
	printf("\n");

	NumOfOutlier(&myclass, &summary);
	printf("%d\n", summary.NumOut);

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
	summary->avg = 0;
	summary->mode = 0;
	summary->med = 0;
	summary->Q1 = 0;
	summary->Q3 = 0;
	summary->min = 0;
	summary->max = 0;
	summary->range = NULL;
	summary->std = 0;
	summary->skew = 0;
	summary->kurtosis = 0;
	summary->range = NULL;
	summary->NumOut = 0;
}
void ReadData(char* name, Class* myclass){

	FILE* fp = fopen(name, "r"); 
	// check whether the file exists 
	if(fp == NULL){
        printf("파일이 존재하지 않습니다. \n");
        exit(1);
	}
	// load file
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
void SummaryMode(Class* myclass, Summary* summary){
	// Initialize the value
	int a[101] = { 0, };
	int temp;
	// Count the every scores
	for(int i = 0; i<myclass->num; i++)
		a[myclass->head[i]->score]++;
	int max = 0;
	int idx;
	for(int i = 0; i<101; i++){
		if(a[i] > max){
			idx = i;
			max = a[i];
		}	
	}
	summary->mode = idx;
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
	// First Sort
	sort(myclass); 

	// Second find values
	summary->med = myclass->head[(int) (myclass->num * 0.5)]->score;
	summary->Q1 = myclass->head[(int) (myclass->num * 0.25)]->score;
	summary->Q3 = myclass->head[(int) (myclass->num * 0.75)]->score;
	summary->min = myclass->head[0]->score;
	summary->max = myclass->head[myclass->num-1]->score;
}
void SummaryStd(Class* myclass, Summary* summary){
	// Initialize std
	summary->std = 0;

	for(int i = 0; i<myclass->num; i++)
        summary->std += (myclass->head[i]->score - avg_score(myclass)) * (myclass->head[i]->score - avg_score(myclass));
	
	summary->std = summary->std/(myclass->num - 1);
	summary->std = sqrt(summary->std);
}
void SummarySkew(Class* myclass, Summary* summary){
	// Initialize skew
	summary->skew = 0;
	double a;

	// Compute standard deviation
	SummaryStd(myclass, summary);

	for(int i = 0; i<myclass->num; i++){
		a = myclass->head[i]->score - avg_score(myclass);
		a = pow(a, 3);
		a = a/myclass->num;
		a = a/pow(summary->std, 3);
		summary->skew += a;
	}
}
void SummaryKurto(Class* myclass, Summary* summary){
	// Initialize Kurtosis
	summary->kurtosis = 0;
	double a;

	// Compute standard deviation
	SummaryStd(myclass, summary);

	for(int i = 0; i<myclass->num; i++){
		a = myclass->head[i]->score - avg_score(myclass);
		a = pow(a, 4);
		a = a/myclass->num;
		a = a/pow(summary->std, 4);
		summary->kurtosis += a;
	}
}
void CreateRange(Summary* summary){
	// dynamic memory allocation
	Range* a = (Range*)malloc(sizeof(Range)*20);
	summary->range = a;

	// set key value, upper bound, and lower bound according to index i
	// set count to 0 
	for(int i = 0; i < 20; i++){
		summary->range[i].key = i;
		summary->range[i].count = 0;
		summary->range[i].LB = 5*i+1;
		summary->range[i].UB = 5*(i+1);
	}

	// when key value is 0, this range covers 0 to 5.
	summary->range[0].LB = 0;
}
void SummaryHists(Class* myclass, Summary* summary){
	int idx;
	// dynamic memory allocation
	summary->range = (Range* )malloc(sizeof(Range)*20);

	// increase count according to score
	for(int i = 0; i<myclass->num; i++){
        idx = (myclass->head[i]->score - 1) / 5;
        summary->range[idx].count++;
	}
}
void NumOfOutlier(Class* myclass, Summary* summary){
	// initialize count
	int count = 0;

	// First sort 
	sort(myclass);

	// Second compute first quantile and third quantile
	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->score;
	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->score;

	// Third Compute upper bound and lower bound 
	float LC = Q1 - 1.5 * (Q3 - Q1); 
	float UC = Q3 + 1.5 * (Q3 - Q1);

	// Fourth increase count by 1 
	// when the score is smaller than lower bound 
	// or larger than upper bound
	for(int i = 0; i<myclass->num; i++) {
		if(myclass->head[i]->score < LC) count++;
		else if(myclass->head[i]->score > UC) count++; 
	}

	// Assign number of outlier
	summary->NumOut = count;
}
void PrintOutlier(Class* myclass, Summary* summary){
	// First sort 
	sort(myclass);

	// Second compute first quantile and third quantile	
	int Q1 = myclass->head[(int) (myclass->num * 0.25)]->score;
	int Q3 = myclass->head[(int) (myclass->num * 0.75)]->score;

	// Third Compute upper bound and lower bound 
	float LC = Q1 - 1.5 * (Q3 - Q1); 
	float UC = Q3 + 1.5 * (Q3 - Q1);

	// When the score is smaller than lower bound or larger than upper bound
	// print out the score
	for(int i = 0; i<=100; i++){
		if(i < LC) printf("%d ", i);
	}
	printf("\n");
	for(int i = 0; i<=100; i++){
		if(i > UC) printf("%d ", i);
	}
}
