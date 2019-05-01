#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatLine(char *str);
void replaceTabs(char *str);
void parseLine(char *inputLine, int outputValues[]);
void sortJobList(char *selectSort, int jobList[][3], int jobListSize);
void FIFOscheduling(int jobList[][3], int FIFOjobs[][5], int jobListSize);
void SJFscheduling(int jobList[][3], int SJFjobs[][5], int jobListSize);
void BJFscheduling(int jobList[][3], int BJFjobs[][5], int jobListSize);

void SJFschedulingTest(int jobList[][3], int jobListSorted[100][3], int jobListSize);

int main(int argc, char **argv) {
	FILE *fp;
	char *line = NULL;
	size_t linesize = 0;
	ssize_t linelen;
	int job[3];
	int jobList[100][3];
	int jobListSorted[100][3];
	int jobIndex = 0;
	int FIFOjobs[100][5];
	int SJFjobs[100][5];
	int BJFjobs[100][5];
	int STCFjobs[100][5];
	int RRjobs[100][5];

	if(argc == 2) {
		fp = fopen(argv[1], "r");
		if(fp == NULL) exit(EXIT_FAILURE);
		while((linelen = getline(&line, &linesize, fp)) != -1) {
			if(strncmp("exit", line, 4) == 0) {
				exit(0);
			}
			formatLine(line);
			replaceTabs(line);
			parseLine(line, job);
			jobList[jobIndex][0] = job[0];
			jobList[jobIndex][1] = job[1];
			jobList[jobIndex][2] = job[2];
			if(jobIndex < 100) jobIndex++;
		}

		sortJobList("fifo", jobList, jobIndex);
		FIFOscheduling(jobList, FIFOjobs, jobIndex);

		sortJobList("sjf", jobList, jobIndex);
		SJFscheduling(jobList, SJFjobs, jobIndex);

		sortJobList("bjf", jobList, jobIndex);
		BJFscheduling(jobList, BJFjobs, jobIndex);

		printf("\nFIFO Scheduling:\nJob ID:\tStart:\tFinish:\tTotal:\tResponse:\n");
		for(int i = 0; i < jobIndex; i++) {
			printf("%i\t%i\t%i\t%i\t%i\n", FIFOjobs[i][0], FIFOjobs[i][1], FIFOjobs[i][2], FIFOjobs[i][3], FIFOjobs[i][4]);
		}

		printf("\nSJF Scheduling:\nJob ID:\tStart:\tFinish:\tTotal:\tResponse:\n");
		for(int i = 0; i < jobIndex; i++) {
			printf("%i\t%i\t%i\t%i\t%i\n", SJFjobs[i][0], SJFjobs[i][1], SJFjobs[i][2], SJFjobs[i][3], SJFjobs[i][4]);
		}

		printf("\nBJF Scheduling:\nJob ID:\tStart:\tFinish:\tTotal:\tResponse:\n");
		for(int i = 0; i < jobIndex; i++) {
			printf("%i\t%i\t%i\t%i\t%i\n", BJFjobs[i][0], BJFjobs[i][1], BJFjobs[i][2], BJFjobs[i][3], BJFjobs[i][4]);
		}
	}
}

void formatLine(char *str) {
	char *src, *dst;
	char *space = " ";
	char *tab = "\t";
	int skip = 1;

	for(src = dst = str; *src != '\0'; src++) {
		*dst = *src;
		if((*dst != *space && *dst != *tab) || skip == 1) {
			if(*dst == *space || *dst == *tab) {
				skip = 0;
			} else {
				skip = 1;
			}
			dst++;
		}
	}
	*dst = '\0';
}

void replaceTabs(char *str) {
	char *src, *dst;
	char *space = " ";
	char *tab = "\t";

	for(src = dst = str; *src != '\0'; src++) {
		*dst = *src;
		dst++;
		if(*dst == *tab) *dst = *space;
	}
	*dst = '\0';
}

void parseLine(char *inputLine, int outputValues[]) {
	int parseIndex = 0;
	char *subLine = (char *)malloc(10);
	char *lineToParse = (char *)malloc(10);
	strcpy(lineToParse, inputLine);

	subLine = strsep(&lineToParse, " ");
	outputValues[0] = atoi(subLine);
	
	subLine = strsep(&lineToParse, " ");
	outputValues[1] = atoi(subLine);

	subLine = strsep(&lineToParse, " ");
	outputValues[2] = atoi(subLine);
}

void sortJobList(char *selectSort, int jobList[][3], int jobListSize) {
	int i, j, k;
	int finalTime = 0;
	int key[3];
	for(i = 1; i < jobListSize; i++) {
		key[0] = jobList[i][0];
		key[1] = jobList[i][1];
		key[2] = jobList[i][2];
		j = i - 1;
		k = j;
		
		if(strncmp("job_id", selectSort, 6) == 0) {
			while(j >= 0 && jobList[j][0] > key[0]) {
				jobList[j + 1][0] = jobList[j][0];
				jobList[j + 1][1] = jobList[j][1];
				jobList[j + 1][2] = jobList[j][2];
				j = j - 1;
			}
			jobList[j + 1][0] = key[0];
			jobList[j + 1][1] = key[1];
			jobList[j + 1][2] = key[2];
		} else if(strncmp("fifo", selectSort, 4) == 0) {
			while(j >= 0 && jobList[j][1] > key[1]) {
				jobList[j + 1][0] = jobList[j][0];
				jobList[j + 1][1] = jobList[j][1];
				jobList[j + 1][2] = jobList[j][2];
				j = j - 1;
			}
			jobList[j + 1][0] = key[0];
			jobList[j + 1][1] = key[1];
			jobList[j + 1][2] = key[2];
		} else if(strncmp("sjf", selectSort, 3) == 0) {
			while(j >= 0 && jobList[j][1] > key[1]) {
				jobList[j + 1][0] = jobList[j][0];
				jobList[j + 1][1] = jobList[j][1];
				jobList[j + 1][2] = jobList[j][2];
				j = j - 1;
			}
			jobList[j + 1][0] = key[0];
			jobList[j + 1][1] = key[1];
			jobList[j + 1][2] = key[2];
			while(k >= 0 && jobList[k][1] == jobList[k + 1][1] && jobList[k][2] > key[2]) {
				jobList[k + 1][0] = jobList[k][0];
				jobList[k + 1][1] = jobList[k][1];
				jobList[k + 1][2] = jobList[k][2];
				k = k - 1;
			}
			jobList[k + 1][0] = key[0];
			jobList[k + 1][1] = key[1];
			jobList[k + 1][2] = key[2];
		} else if(strncmp("bjf", selectSort, 3) == 0) {
			while(j >= 0 && jobList[j][1] > key[1]) {
				jobList[j + 1][0] = jobList[j][0];
				jobList[j + 1][1] = jobList[j][1];
				jobList[j + 1][2] = jobList[j][2];
				j = j - 1;
			}
			jobList[j + 1][0] = key[0];
			jobList[j + 1][1] = key[1];
			jobList[j + 1][2] = key[2];
			while(k >= 0 && jobList[k][1] == jobList[k + 1][1] && jobList[k][2] < key[2]) {
				jobList[k + 1][0] = jobList[k][0];
				jobList[k + 1][1] = jobList[k][1];
				jobList[k + 1][2] = jobList[k][2];
				k = k - 1;
			}
			jobList[k + 1][0] = key[0];
			jobList[k + 1][1] = key[1];
			jobList[k + 1][2] = key[2];
		}
	}
}

void FIFOscheduling(int jobList[][3], int FIFOjobs[][5], int jobListSize) {
	int startTime = jobList[0][1];
	int finishTime = 0;
	for(int i = 0; i < jobListSize; i++) {
		FIFOjobs[i][0] = jobList[i][0];
		//Start Time For Each Job
		if(i == 0) {
			FIFOjobs[i][1] = jobList[i][1];
		} else {
			if(startTime < jobList[i][1]) {
				FIFOjobs[i][1] = jobList[i][1];				
			} else {
				FIFOjobs[i][1] = startTime;
			}
		}
		//Finish Time For Each Job
		finishTime = startTime + jobList[i][2];
		FIFOjobs[i][2] = finishTime;
		if(startTime < jobList[i][1]) {
			startTime = jobList[i][1] + jobList[i][2];
		} else {
			startTime = startTime + jobList[i][2];
		}
		//Total Time Elapsed For Each Job
		FIFOjobs[i][3] = finishTime - jobList[i][1];
		//Response Time For Each Job
		if(i == 0) {
			FIFOjobs[i][4] = jobList[i][1];
		} else {
			FIFOjobs[i][4] = startTime - jobList[i][1];
		}
	}
}

void SJFscheduling(int jobList[][3], int SJFjobs[][5], int jobListSize) {	
	int startTime = jobList[0][1];
	int finishTime = 0;
	for(int i = 0; i < jobListSize; i++) {
		SJFjobs[i][0] = jobList[i][0];
		//Start Time For Each Job
		if(i == 0) {
			SJFjobs[i][1] = jobList[i][1];
		} else {
			if(startTime < jobList[i][1]) {
				SJFjobs[i][1] = jobList[i][1];				
			} else {
				SJFjobs[i][1] = startTime;
			}
		}
		//Finish Time For Each Job
		finishTime = startTime + jobList[i][2];
		SJFjobs[i][2] = finishTime;
		if(startTime < jobList[i][1]) {
			startTime = jobList[i][1] + jobList[i][2];
		} else {
			startTime = startTime + jobList[i][2];
		}
		//Total Time Elapsed For Each Job
		SJFjobs[i][3] = finishTime - jobList[i][1];
		//Response Time For Each Job
		if(i == 0) {
			SJFjobs[i][4] = jobList[i][1];
		} else {
			SJFjobs[i][4] = startTime - jobList[i][1];
		}
	}
}

void BJFscheduling(int jobList[][3], int BJFjobs[][5], int jobListSize) {
	int startTime = jobList[0][1];
	int finishTime = 0;
	for(int i = 0; i < jobListSize; i++) {
		BJFjobs[i][0] = jobList[i][0];
		//Start Time For Each Job
		if(i == 0) {
			BJFjobs[i][1] = jobList[i][1];
		} else {
			if(startTime < jobList[i][1]) {
				BJFjobs[i][1] = jobList[i][1];				
			} else {
				BJFjobs[i][1] = startTime;
			}
		}
		//Finish Time For Each Job
		finishTime = startTime + jobList[i][2];
		BJFjobs[i][2] = finishTime;
		if(startTime < jobList[i][1]) {
			startTime = jobList[i][1] + jobList[i][2];
		} else {
			startTime = startTime + jobList[i][2];
		}
		//Total Time Elapsed For Each Job
		BJFjobs[i][3] = finishTime - jobList[i][1];
		//Response Time For Each Job
		if(i == 0) {
			BJFjobs[i][4] = jobList[i][1];
		} else {
			BJFjobs[i][4] = startTime - jobList[i][1];
		}
	}
}
