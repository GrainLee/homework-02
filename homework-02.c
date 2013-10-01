#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M 256
int input[M][M]={0};
int result[M][M]={0};

int main(int argc,char *argv[])
{
	int line , row;
	int i ,j;//Variable

	//Temp variable
	char read[M];
	int temp=0,flag=0;
	int length;
	FILE *in;
	int isV=0,isH=0,isA=0;//flag
	
	for (i=1;i<argc-1;i++)
	{
		if (!strcmp(argv[i],"/v"))
			isV = 1;
		else if (!strcmp(argv[i],"/h"))
			isH = 1;
		else if (!strcmp(argv[i],"/a"))
			isA = 1;
		else{
			printf("command input error\n");
			return 0;
		}
	}

	//File input
	if((in = fopen(argv[argc-1], "r")) == NULL){
		printf("file open failed\n");
		return 0;
	}
	//row and line input
	if(fgets(read, 256, in) == NULL){
		printf("file input error\n");
		return 0;
	}
	line = convertToNum(read);
	if(fgets(read, 256, in) == NULL){
		printf("file input error\n");
		return 0;
	}
	row = convertToNum(read);

	//Main array input
	for (i=0;i<line;i++)
	{
		
		//getline
		if(fgets(read, 256, in) == NULL){
			printf("file input error\n");
			return 0;
		}
		
		length = strlen(read);
		temp =0;
		flag=0;
		for(j=0;j<length;j++)
		{
			if(read[j]<='9'&&read[j]>='0'&& flag==0)
				input[i][temp] = input[i][temp]*10+read[j]-'0';

			else if(read[j]<='9'&&read[j]>='0'&& flag==1)
			{
				input[i][temp] = -input[i][temp];
				input[i][temp] = -(input[i][temp]*10+read[j]-'0');

			}
			else if(read[j] == ','||read[j]=='，')
			{
				temp++;
				flag=0;
			}
			else if(read[j]=='-')
				flag=1;
		}
		if(temp<row-1)
		{
			printf("file input error\n");
			return 0;
		}
	}
	//closefile
	fclose(in);



	
	
	switch (choose(isV,isH,isA))
	{
	case 1 :
		maxSum_2(row ,line,isV,isH);return 1;//Without /v,/h
	case 2 :
		maxSum_2(row ,line,isV,isH);return 1;//Without /a
	case 3:
		maxSum_3();return 1;
	default:
		printf("ERROR:command input error");
		return 0;
	}

	
	//input 
	 
}
int convertToNum(char charArr[])
{
	int result=0;
	int length,i;
	length = strlen(charArr);
	
	for(i=0;i<length-1;i++)
	{
		if(charArr[i]<='9'&&charArr[i]>='0')
			result = result*10+charArr[i]-'0';
		else if(charArr[i] == ',')
			return result;
	}
	return -1;
}
// choose the right function
int choose(int isV,int isH,int isA)
{
	if (!isV&&!isH&&!isA)
		return 1;
	else if((isV||isH)&&!isA)
		return 2;
	else if (isA)
		return 3;

	return 0;
}

int maxSum_1(int row ,int line,int isV,int isH)
{
	int max,maxend;
	int ult,super,tmpsum;
	int i,j,k,m;
	ult = input[0][0];
	for(i = 0; i < line; i++){
		for(j = i; j < (isV ? line+i : line); j++){
			super = input[0][0];
			for(m = 0; m < (isH ? row : 1); m++){
				max = sum(line, row, i, j, m);
				maxend = max;
				for(k = m+1; k < (isH ? row+m : row); k++){
					tmpsum = sum(line, row, i, j, k);
					maxend = maxend+tmpsum > tmpsum ? maxend+tmpsum : tmpsum;
					max = max > maxend ? max : maxend;
				}
				super = max > super ? max : super;
			}
			ult = super > ult ? super : ult;
		}
	}
	printf("%d\n", ult);


}
int maxSum_2(int row ,int line,int isV,int isH)
{
	int max,maxend;
	int ult,super,tmpsum;
	int i,j,k,m;
	ult = input[0][0];
	for(i = 0; i < line; i++){
		for(j = i; j < (isV ? line+i : line); j++){
			super = input[0][0];
			for(m = 0; m < (isH ? row : 1); m++){
				max = sum(line, row, i, j, m);
				maxend = max;
				for(k = m+1; k < (isH ? row+m : row); k++){
					tmpsum = sum(line, row, i, j, k);
					maxend = maxend+tmpsum > tmpsum ? maxend+tmpsum : tmpsum;
					max = max > maxend ? max : maxend;
				}
				super = max > super ? max : super;
			}
			ult = super > ult ? super : ult;
		}
	}
	printf("%d\n", ult);


}
int maxSum_3()
{
	printf("Sorry,this version can't support this function");
}
int sum(int line, int row, int i, int j, int k){
	int a, tmpnum, s = 0;
	for(a = i; a <= j; a++){
		s += input[(a >= line ? a-line: a)][(k >= row ? k-row : k)];
	}
	return s;
}