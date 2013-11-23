#include<iostream>
#include<fstream>
#include<vector>
#include<string.h>
#include"svd.c"
using namespace std;

int row, col;
float **a;

void displayMatrix(float **mat, int row, int col)
{
	/* Function to display a row x col matrix
	   Input: 
		mat: matrix to be displayed
		row: number of rows
		col: number of columns */
	int i,j;
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			printf("%f ",mat[i][j]);
		}
		printf("\n");
	}
}

void displayVector(float* vec, int size)
{
	/* Function to display a one dimensional array
	   Input:
		vec: vector to be displayed
		size: number of elements in the vector */
	int i;
	for(i = 0; i < size; i++)
		printf("%f ",vec[i]);
	printf("\n");
}

void readFromFile(char *filename)
{
	/* Function to read a matrix from a file
	   Input:
		filename: path to the file which contains the matrix */
	size_t len;
	char *line = NULL;
	string str();
	vector<string> numbers;
	int r = 0,c = 0;

	FILE *fp = fopen(filename, "r");
	
	if(!fp)
	{
		cout<<"Error\n";
		return;
	}
	while(getline(&line, &len, fp) != -1)
	{
		r++;
		c = 0;
		int startpos = 0;
		int endpos = 0;
		for(int i = 0; line[i] != '\0'; i++)
		{
			if(line[i] == ' ')
			{
				c++;
				string tempstr("");
				for(int j = startpos; j <= endpos; j++)
				{
					tempstr += line[j];
				}
				numbers.push_back(tempstr);
				startpos = endpos + 1;
				endpos = startpos;
			}
			else
				endpos++;
		}
		c++;
		string tempstr("");
		for(int j = startpos; j <= endpos; j++)
		{
			tempstr += line[j];
		}
		numbers.push_back(tempstr);
		free(line);
		line = NULL;
	}

	a = (float **) malloc(r * sizeof(float*));
	for(int i = 0; i < r; i++)
	{
		*(a+i) = (float*) malloc(c * sizeof(float));
	}	

	for(int i = 0; i < r; i++)
	{
		for(int j = 0; j < c; j++)
		{
			a[i][j] = atof(numbers[i*c+j].c_str());
		}
	}
	row = r;
	col = c;
}

void writeToFile(float **a, int row, int col, char * filename, char classLabel[] = "$~DELIM~$")
{
	/* Function to write a matrix to an output file
	   Input:
		a: matrix to be written to the file
		row: number of rows of the matrix
		col: number of columns of the matrix
		filename: path to the output file */
	int i,j;
	ofstream fout(filename);
	for(i = 0; i < row; i++)
	{
		for(j = 0; j < col; j++)
		{
			fout<<a[i][j];
			if(j != col - 1)
				fout<<",";
		}
		if(!strcmp(classLabel,"$~DELIM~$"))
			fout<<endl;
		else
		{
			fout<<"|"<<classLabel<<endl;
		}
	}
	fout.close();
}

void PCA(float *w, int col)
{
	/* Function to perform PCA
	   Input:
	w: The vector of sigma values
	col: number of elements in the vector */
	int i;
	float sum = 0, sum99Percent, currentSum = 0;
	for(i = 0; i < col; i++)
	{
		sum += w[i];
	}
	
	sum99Percent = sum * 99.0/100.0;
	
	for(i = 0;i < col; i++)
	{
		if(currentSum >= sum99Percent)
			w[i]=0;
		currentSum += w[i];
	}
}

void swapColumns(float **u, int i, int j, int row, int col)
{
	/* Function to swap two columns of a matrix
	   Input:
		u: matrix whose columns are to be swapped
		i: index of first column
		j: index of second column
		row: number of rows in the matrix
		col: number of columns in the matrix */
	int index;
	for(index=0;index<row;index++)
	{
		float temp = u[index][i];
		u[index][i] = u[index][j];
		u[index][j] = temp;
	}
}

void sortSigmaValues(float **u, float *w, float **v, int row, int col)
{
	/* Function to sort the sigma values (and correspondingly sort other matrices) in decreasing order
	   Input:
		u, w, v : the resultant matrices from SVD
		row: number of rows of u
		col: number of columns of u 
	   Uses:
	   	- swapColumns() */
	int i,j;
	for(i = 0; i < col; i++)
	{
		for(j = i + 1; j < col; j++)
		{
			if(w[i] < w[j])
			{
				float temp = w[i];
				w[i] = w[j];
				w[j] = temp;
				swapColumns(u, i, j, row, col);
				swapColumns(v, i, j, row, col);
			}
		}
	}
}


int main(int argc, char **argv)
{
	int i,j,k;
	char inputfilename[] = "sampleinput.txt";

	if(argc < 3)
	{
		printf("USAGE: ./svd inputFile OutputFile [classLabel]\n");
		return -1;
	}

	// Initialize
	readFromFile(argv[1]);

	// Setting up RESULT
	float **res = (float**) malloc(row * sizeof(float*));
	for(i = 0; i < row; i++)
	{
		*(res+i) = (float*) malloc(col * sizeof(float));
	}

	printf("\nInitial matrix\n");
	displayMatrix(a, row, col);	

	// Setting up V	
	float **v = (float**) malloc(col * sizeof(float*));
	for(i=0;i<col;i++)
	{
		*(v+i) = (float*) malloc(col * sizeof(float));
	}

	// Setting up W
	float *w = (float*) malloc(col * sizeof(float));

	// Calling SVD
	dsvd(a, row, col, w, v);

	// Sort the sigma values in decreasing order
	sortSigmaValues(a, w, v, row, col);

	// Perform principal component ananlysis
	PCA(w, col);

	// Perform first multiplication u.v
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			float sum = 0;
			for(k=0;k<col;k++)
			{
				if(k==j)
					sum += a[i][k] * w[k];
			}
			a[i][j]=sum;
		}
	}	

	// Perform second multiplication (uv).w
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			float sum = 0;
			for(k=0;k<col;k++)
			{
				sum += a[i][k] * v[j][k];
			}
			res[i][j]= sum;
		}
	}

	printf("\nMultiplied Matrix\n");
	displayMatrix(res, row, col);
	
	if(argc >= 4)
		writeToFile(res, row, col, argv[2], argv[3]);
	else
		writeToFile(res, row, col, argv[2]);

	// Cleanup
	for(i=0;i<row;i++)
	{
		free(a[i]);
		free(res[i]);
	}

	for(i=0;i<col;i++)
	{
		free(v[i]);
	}
	free(a);
	free(v);
	free(w);
}
