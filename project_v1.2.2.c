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
int Partition(Class* myclass, int left, int right);
void sort(Class* myclass, int left, int right);
// void sort(Class* myclass);
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
	long result0 = 0;
    int result1 = 0;
    int i;
    int num = myclass->num;
	for(i=0; i < num; i+=2){
        result0 += myclass->head[i]->score;
        result1 += myclass->head[i+1]->score;
    }
    for(; i < num; i++)
        result0 += myclass->head[i]->score;

	return result0+result1;
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

int Partition(Class* myclass, int left, int right)
{   
    Student** head = myclass->head;
    int pivot = head[left]->score, temp;
    int low = left + 1, high = right;
    while (1) {
        while (low < right && head[low]->score < pivot)
            low++; // Move low until pivot < L[low]
        while (high > left && head[high]->score >= pivot)
            high--; // Move high until pivot >= L[low]
        if (low < high)
        // Swap list[low] and list[high].
            SWAP_STD(myclass, low, high);
        else break;
    }
    SWAP_STD(myclass, left, high);

    return high; // return the pivot position.
}
void sort(Class* myclass, int left, int right)
{
    if (left < right) {
        // The mid refers to the pivot position.
        int mid = Partition(myclass, left, right);
        // All elements are less than the pivot.
        sort(myclass, left, mid - 1);
        // All elements are greater than the pivot.
        sort(myclass, mid + 1, right);
    }
}
void SummaryMed(Class* myclass, Summary* summary){	
	// First Sort
	sort(myclass, 0, myclass->num-1); 

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
    float avg = summary->avg == 0? avg_score(myclass) : summary->avg;
	for(int i = 0; i<myclass->num; i++)
        summary->std += (myclass->head[i]->score - avg) * (myclass->head[i]->score - avg);
	
	summary->std = summary->std/(myclass->num - 1);
	summary->std = sqrt(summary->std);
}
void SummarySkew(Class* myclass, Summary* summary){
	// Initialize skew
	summary->skew = 0;
	double a;
    float avg = summary->avg == 0? avg_score(myclass) : summary->avg;
	// Compute standard deviation
	SummaryStd(myclass, summary);

	for(int i = 0; i<myclass->num; i++){
		a = myclass->head[i]->score - avg;
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
    float avg = summary->avg == 0? avg_score(myclass) : summary->avg;
	// Compute standard deviation
	SummaryStd(myclass, summary);

	for(int i = 0; i<myclass->num; i++){
		a = myclass->head[i]->score - avg;
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

	// dynamic memory allocation
	summary->range = (Range* )malloc(sizeof(Range)*20);

	// increase count according to score
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
	// initialize count
	int count = 0;

	// First sort 
	sort(myclass, 0, myclass->num-1);

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
	sort(myclass, 0, myclass->num-1);

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
