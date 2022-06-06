/*
 * hw12-sorting-hashing.c
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */  
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE //해시테이블 크기를 배열크기와 똑같이

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a); //이중 포인터 변수 a를 매개로 하는 정수형 초기화 함수
int freeArray(int *a); // 포인터 변수 a를 매개로하는 정수형 배열 메모리 반환 함수
void printArray(int *a); // 포인터 변수 a를 매개로하는 배열 프린트 함수

int selectionSort(int *a); //포인터 변수 a를 매개로하는 정수형 선택정렬함수
int insertionSort(int *a); //포인터 변수 a를 매개로하는 정수형 삽입 정렬 함수
int bubbleSort(int *a); //포인터 변수 a를 매개로하는 버블정렬 함수
int shellSort(int *a); //포인터 변수 a를 매개로하는 셸 정렬 함수
/* recursive function으로 구현 */
int quickSort(int *a, int n); //포인터 변수 a, 정수형 변수 n을 매개로하는 퀵 정렬 함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key); //정수형 변수 key를 매개로하는 해시코드 함수

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht); //포인터 변수 a와 이중포인터변수 ht를 매개로하는 해싱 함수 

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key); //포인터 변수 ht와 정수형 변수 key를 매개로 하는 검색함수


int main()
{
	char command;
	int *array = NULL; //배열 및 해시테이블 초기화
	int *hashtable = NULL;
	int key = -1; //key값 -1로 초기화
	int index = -1; //인덱스도 -1로 초기화

	srand(time(NULL));  //난수 생성 함수

	do{
		printf("----------Kim Beom Gyu-----------------------2019062022---------\n");
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //입력받은 명령어 저장

		switch(command) { //각 명령에 맞는 기능 실행
		case 'z': case 'Z':
			initialize(&array); //배열 초기화
			break;
		case 'q': case 'Q':
			freeArray(array); //배열 메모리 반환
			break;
		case 's': case 'S':
			selectionSort(array); //선택 정렬
			break;
		case 'i': case 'I':
			insertionSort(array); //삽입 정렬
			break;
		case 'b': case 'B':
			bubbleSort(array); //버블 정렬
			break;
		case 'l': case 'L':
			shellSort(array); //셸 정렬
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n"); 
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열 출력하고
			quickSort(array, MAX_ARRAY_SIZE); // 퀵 정렬 수행
			printf("----------------------------------------------------------------\n");
			printArray(array); //다시 배열 출력

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //마찬가지로 배열 출력 후
			hashing(array, &hashtable); //해싱 작업 수행
			printArray(hashtable); // 해시테이블 출력
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //키를 입력받고
			printArray(hashtable); //해시테이블 출력
			index = search(hashtable, key); //해시테이블에서 해당 키 검색하고 인덱스에 대입
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]); 
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL; //포인터 변수 temp 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { 
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //temp에 정수형 크기 * 13만큼의 동적 메모리 할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/ 
	} else
		temp = *a; //null이 아니면 *a값을 temp에 복사함

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; 

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL) //NULL이 아닐때만 반환 실행
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) { //NULL일경우 출력 x 
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i); // 0번부터 12번까지 (크기 13) 배열 순서 순차적으로 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]); //0번부터 12번까지 배열 값 순차적 출력
	printf("\n");
}


int selectionSort(int *a)
{
	int min; //최솟값 
	int minindex; //최솟값의 인덱스
	int i, j; 

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //배열 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; //최솟값의 인덱스를 처음으로 설정하고,
		min = a[i]; //그 값을 최솟값으로 함
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //하나씩 비교해가면서 최소값 보다 a[j]가 더 작으면
			{
				min = a[j]; //최솟값을 a[j]로 변경하고
				minindex = j; //최소 인덱스도 같이 변경함
			}
		}
		a[minindex] = a[i];  // a[i]를 최소 인덱스로 다시 설정
		a[i] = min;  // 최소도 a[i]로 다시 설정하고, 비교 반복해서 정렬 수행
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬된 배열 출력
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i]; //t에 a[i] 값 대입
		j = i; //j에 i값 대입
		while (a[j-1] > t && j > 0) //j가 0보다 크고, j값 전의 배열 값이 t보다 클 떄 까지 반복
		{
			a[j] = a[j-1]; //a[j]에 a[j-1] 값 대입
			j--; //j 1씩 감소 
		}
		a[j] = t; //t를 a[j]에 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 된 배열 출력

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)
		{
			if (a[j-1] > a[j]) //a[j-1]이 a[j]보다 클 때
			{
				t = a[j-1]; //a[j-1]을 t에 대입하고
				a[j-1] = a[j]; //a[j]를 a[j-1]에 대입하고
				a[j] = t; //a[j]에는 a[j-1]을 대입 ( 간단히, 서로 값을 바꾸는 것 )
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 후 배열 출력

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬 전 배열 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //반으로 나눠서, h가 1개이상 정렬 가능할때 수행, 계속 반으로 나누면서 수행
	{  //구간을 나눈 뒤 하는 정렬은 삽입정렬 
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //a[j]값을 v에 대입
				k = j; //j는 k에 대입
				while (k > h-1 && a[k-h] > v) //k가 h-1보다 크고, a[k-h]가 v보다 크면 반복 
				{
					a[k] = a[k-h]; //a[k-h]값을 a[k]에 대입하고
					k -= h; // k에 k-h을 대입
				}
				a[k] = v; //v값을 a[k]로
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬후 배열 출력

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) //n이 1보다 클때만 수행
	{
		v = a[n-1]; //a[n-1]을 v에
		i = -1; //-1을 i에
		j = n - 1; //n-1을 j에 대입

		while(1) //무한 반복
		{
			while(a[++i] < v); //a[i]가 v보다 작으면 반복, 조건 맞으면 i+1 수행
			while(a[--j] > v); //a[j]가 v보다 크면 반복, 조건 맞으면 j-1 수행

			if (i >= j) break; //i가 j와 같아지거나 j보다 커지는 순간 반복 종료
			t = a[i]; //a[i]값을 t에 대입
			a[i] = a[j]; //a[j]값을 a[i]로
			a[j] = t; //t값을 a[j]에 대입, ( 결론 a[i]<->a[j])
		}
		t = a[i]; //a[i]값을 t에 대입
		a[i] = a[n-1]; //a[n-1] 값을 a[i]에 대입
		a[n-1] = t; //t값은 a[n-1]에 대입 (a[i] <-> a[n-1])

		quickSort(a, i); //a와 i를 매개로 퀵정렬 수행
		quickSort(a+i+1, n-i-1); //a+1+1과 n-i-1을 매개로 퀵정렬 수행
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //키값에 13나눈 나머지를 반환 해시코드 생성
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL; //해시테이블 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) { //ht가 NULL일경우만 
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //정수형 변수 크기 *13만큼의 동적 메모리 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/ //해시테이블의 주소를 *ht에 복사
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */ //아니면 *ht를 해시테이블로 사용
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1; //해시테이블 초기값 -1로 초기화

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //key값 -1로 초기화
	int hashcode = -1; //해시코드값도 -1로 초기화
	int index = -1; //index값도 -1로 초기화
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; //a[i]값을 key에 대입
		hashcode = hashCode(key); //key에대해 해시코드 함수 수행하고, 해시코드에 대입
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //해시테이블 내에서 해시코드 인덱스의 값이 -1일경우
		{
			hashtable[hashcode] = key; //거기에 key값 대입
		} else 	{

			index = hashcode; //아니면 해시코드를 index에 넣음

			while(hashtable[index] != -1) //해시테이블의 인덱스 값이 -1이 아닐때 반복 수행
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; //index에 index에 13으로 나눈 나머지 값 대입하고, index에 +1 연산 수행
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //해시테이블[index]에 해당하는 곳에 key값 대입
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //index에대해 key를 매개로하는 해시코드 함수 수행

	if(ht[index] == key) //ht[index]값이 키값과 같으면
		return index; //인덱스값 반환

	while(ht[++index] != key) //ht[index]가 키값과 다르면 반복하고, index에 +1연산 수행
	{
		index = index % MAX_HASH_TABLE_SIZE; //index에 index에 13으로 나눈 나머지 대입
	}
	return index; //index값 반환해줌
}



