#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void formatLine(char *str);
void replaceTabs(char *str);
void parseLine(char *inputLine, int outputValues[]);
void sortJobList(char *selectSort, int jobList[][3], int jobListSize);
void FIFOscheduling(int jobList[][3], int FIFOjobs[][5], int jobListSize);

int main(int argc, char **argv) {
	FILE *fp;
	char *line = NULL;
	size_t linesize = 0;
	ssize_t linelen;
	int job[3];
	int jobList[100][3];
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

		for(int i = 0; i < jobIndex; i++) {
			printf("job_id = %i\n", jobList[i][0]);
			printf("arrival_time = %i\n", jobList[i][1]);
			printf("duration = %i\n\n", jobList[i][2]);
		}
		sortJobList("arrival_time", jobList, jobIndex);

		for(int i = 0; i < jobIndex; i++) {
			printf("job_id = %i\n", jobList[i][0]);
			printf("arrival_time = %i\n", jobList[i][1]);
			printf("duration = %i\n\n", jobList[i][2]);
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
	int i, j;
	int key[3];
	for(i = 1; i < jobListSize; i++) {
		key[0] = jobList[i][0];
		key[1] = jobList[i][1];
		key[2] = jobList[i][2];
		j = i - 1;
		
		if(strncmp("job_id", selectSort, 6) == 0) {
			while (j >= 0 && jobList[j][0] > key[0]) {
				jobList[j + 1][0] = jobList[j][0];
				jobList[j + 1][1] = jobList[j][1];
				jobList[j + 1][2] = jobList[j][2];
				j = j - 1;
			}
		} else if(strncmp("arrival_time", selectSort, 12) == 0) {
			while (j >= 0 && jobList[j][1] > key[1]) {
				jobList[j + 1][0] = jobList[j][0];
				jobList[j + 1][1] = jobList[j][1];
				jobList[j + 1][2] = jobList[j][2];
				j = j - 1;
			}
		} else if(strncmp("duration", selectSort, 12) == 0) {
			while (j >= 0 && jobList[j][2] > key[2]) {
				jobList[j + 1][0] = jobList[j][0];
				jobList[j + 1][1] = jobList[j][1];
				jobList[j + 1][2] = jobList[j][2];
				j = j - 1;
			}
		}
		jobList[j + 1][0] = key[0];
		jobList[j + 1][1] = key[1];
		jobList[j + 1][2] = key[2];
	}
}

void FIFOscheduling(int jobList[][3], int FIFOjobs[][5], int jobListSize) {
	for(int i = 0; i < jobListSize; i++) {
		FIFOjobs[i][0] = jobList[i][0];
		
	}
}
