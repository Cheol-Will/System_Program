# System Program Profiling Project  
- input: one integer  
- set seed  
- input: two integer -> # of students and # of subjects
- create student's score data: <strong>done</strong>
- read student's score data: <strong>done</strong>
- sorting 
- 
---  
# what about making a student structure??  
 - id  
 - next  
 - math  
 - eng  
 - kor  
1) sorting by id  
2) dist of scores 
# std, class, summary


	// 사용자 정의 function: 15개 이상...
	// what is the purpose of my project?

	// 함수 작성할 `x if 문으로 ㅈㄴ 분기 -> 나중에 ternary, sequential 등으로 작업
	// recursive ㅈㄴ 사용 -> for 문으로 전환
	// for문 사용할 때 loop unrolling 작업 나중에
	// selection sort -> quick sort ...?
	// hash fuction...?
    // 지금 내가 하고 싶은 거는 일단 sorting 했고
	// 뭔가 기능을 추가해?
	// 각 점수마다 linked list로 만들까? -> 왜...?
	// 일단 점수마다 count 해주고
	// 그 다음에 출력하는 함수 뭐 

# Test Simulation for Teacher...?
수능시험 시뮬레이션
학생 수 30만명, 그리고 또 해야하는 거 뭐 있는데...  
일단 수능시험에서 평균, 표준편차만 제공된다고 치자  
정규분포로 생성을 하고 sorting, median, avg, 또 구할 거 뭐 있냐  
summary 함수에 이것저것 다 대입을 해줄 것이야.   
summary 함수에 대입을 할 때 무조건 계속 구조체 포인터 사용하고 나중에 개선할 때   
local로 만들어서 마지막에 대입하는 거로 수정을 해보자  
또 시도해볼 수 있는 게 뭐가 있을까

create and read : done
# Process  
- 일단 데이터 생성 ( 보류 -> R로 수행 )  
- 데이터 읽고  (kor, eng, math 다 따로 받을 것인가?) -> 1초  
- 데이터 sorting?  ( kor를 select sort 한다 치자 근데 뭐 )  
- 사용자에게 점수를 입력받아서 같은 점수 몇 명 있는지 파악    
- 이게 정규분포인거는 모르니까 그거 뭐냐  
- sum 함수 구현하고, avg 구하고, sd 구하고, 또...  
- 통계적으로 뭔가 할 수 있는 것들이 있을까?  
- mode : 그냥 mode?  
- mymode: 점수대 구간 별로 어디가 가장 높은가? -> hashing으로 해봐...? 
- if else로 코딩하고 나중에 hashing으로 바꾸자
- 현재 함수 11개
- 통계값 다른 거 좀 더 넣어주자

# 실행시간 (data 10만개 기준) 프로파일링 전 3분 정도
## Works Correctly and 
 - 데이터 읽기: 1초  
 - avg(sum) : 3초 정도
 - med(sort) : 20초 정도 -> sort함수 다른 알고리즘 사용
 - sd : 1분 걸리나...? -> avg_kor을 loop 밖에서 local로 선언
 - range : 0.1초면 끝나는 것 같아 -> modular로 if문 없이 사용
 - skewness: 30초
 - kurtosis: 
 - outlier:  


프로파일링 리스트: 
- 메모리 접근에 관하여  
- 한 함수에서 내부적으로 다른 함수를 call한다면 일단 summary에 그 값이 있는지부터 확인 그 후에 그 값이 없다면 call을 한다. ex) skew와 kurto 함수에서 std 값 있는지 확인부터 하고 0이면 std 실행 후 계산, 0 아니면 실행 없이 계산  
- avg를 사용하는 함수도 avg 있는지부터 확인하고 계산  
- 또 뭐냐 loop unrolling 해야하고, accumulator 사용해야지 2x2로 unrolling하자  
- 


	int med;
	int Q1;
	int Q3;
	int min;
	int max;# System_Program
