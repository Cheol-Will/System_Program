### 시스템 프로그램 프로파일링 프로젝트

이 프로젝트는 학생 점수 데이터를 분석하는 시스템 프로그램을 프로파일링하는 데 중점을 두고 있습니다. 주로 데이터 정렬, 통계 분석, 그리고 대규모 데이터셋에 대한 성능 최적화를 목표로 하고 있습니다.

---

## 프로젝트 개요

학생들의 성적 데이터를 생성, 읽기, 정렬하며 다양한 통계 지표를 계산하는 프로그램입니다. 성능 향상을 위해 **루프 언롤링**, **재귀 함수의 반복문 변환**, **메모리 접근 최적화** 등의 기법을 활용할 예정입니다.

### 주요 기능
- **학생 데이터 관리**: 학생들의 성적 데이터를 과목별(수학, 영어, 국어)로 생성하고 읽어옵니다.
- **정렬 알고리즘**: 초기에는 **선택 정렬**을 사용하지만, **퀵 정렬** 등 더 빠른 알고리즘으로 개선할 예정입니다.
- **통계 분석**: 평균, 중앙값, 표준편차, 최빈값과 같은 기본 통계 지표를 제공하며, **왜도**와 **첨도**와 같은 고급 통계도 포함합니다.

---

## 향후 개선 계획
- **데이터 구조**: 학생 구조체 (ID, 점수)를 도입하여 데이터를 더 효율적으로 관리할 예정입니다.
- **성능 최적화**: 대규모 데이터셋(예: 30만 명의 학생)의 실행 시간을 프로파일링하고, **루프 언롤링**, **조건 분기 최소화**, **메모리 접근 최적화** 등의 방법으로 성능을 개선할 계획입니다.
- **기능 확장**: 점수 분포 분석, **해싱**을 통한 빈도수 계산, 통계 요약 함수에 추가 기능을 넣어 기능성을 확대할 예정입니다.

---

## 프로파일링 결과

- **데이터 읽기**: 약 1초
- **평균 계산(avg)**: 약 3초
- **중앙값 계산(median)**: 약 20초 (정렬 알고리즘 개선 필요)
- **표준편차 계산(sd)**: 약 1분
- **왜도(skewness)**: 약 30초
- **첨도(kurtosis)**: 약 30초

---

이 프로젝트는 성능 최적화와 데이터 분석을 동시에 다루며, 대규모 데이터셋에 대해 효과적인 프로파일링 및 개선을 목표로 하고 있습니다.
