#include<bits/stdc++.h>
using namespace std;
#define FR freopen("input.txt", "r", stdin);
#define FW freopen("output.txt", "w", stdout);
int suduko[10][10];

vector<set<int> > possible[10];
//collection of 9 9*9 matrix .each for number from 1 to 9
//
bool numbers[10][10][10];


//A utitlity funtion to mark false  all the cells in ith row and jth column .
//means we cant place number in all these cells
void marker(int i,int j,int number)
{

	for(int k=1;k<=9;k++)
		{
			numbers[number][k][j]=false;
			numbers[number][i][k]=false;
		}
	for(int k=1;k<=9;k++)
		{
			numbers[k][i][j]=false;
		}
}

void input()
{

	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=9;j++)
		{
			cin>>suduko[i][j];
			if(suduko[i][j])
			{
				marker(i,j,suduko[i][j]);	
			}
					
		}
	}

}
void find_possible()
{
//there are 9 3*3 cube in  a suduko so we are storing all the possible number for each cube
	for(int i=1;i<=7;i+=3)
	{
		for(int j=1;j<=7;j+=3)
		{
			bool temp[10];
			int row,col;
			row=i;
			col=j;
			int cube=i+j/3;
			memset(temp,false,sizeof(temp));
			for(int ii=1;ii<=3;ii++,row++)
			{
				for(int jj=1,col=j;jj<=3;jj++,col++)
					temp[suduko[row][col]]=true;
			}
			set<int> tt;
			for(int ii=1;ii<=9;ii++)
				if(!temp[ii])
					tt.insert(ii);			

			possible[cube].push_back(tt);
		
		}
	}	

}

void human_algo()
{


	while(1)
	{
		bool progress=false;
		
		for(int i=1;i<=7;i+=3)
		{
			for(int j=1;j<=7;j+=3)
			{
				int cube=i+j/3;
				for(auto elem : possible[cube][0])
				{
					int row,col;
					row=i;
					col=j;
					int cnt=0;
					int x,y;
					for(int ii=1;ii<=3;ii++,row++)
					{
						for(int jj=1,col=j;jj<=3;jj++,col++)
						{
							if(numbers[elem][row][col])
							{
								x=row;
								y=col;
								cnt++;
							}
						}
					}
					if(cnt==1)
					{
						suduko[x][y]=elem;
						possible[cube][0].erase(possible[cube][0].find(elem));
						marker(x,y,elem);
						progress=true;
					}
				}

			}
		}
		if(!progress)
			break;
	}

}

//Funtion to print the Suduko
void print()
{
	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=9;j++)
		{
			cout<<suduko[i][j]<<" ";
		}
		cout<<endl;
	}

}
bool check()
{
	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=9;j++)
		{
			if(suduko[i][j]==0)
				return true;
		}
	}
	return false;
}

bool findspace(int &row,int &col)
{

    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=9;j++)
        if(suduko[i][j]==0)
        {
            row=i;
            col=j;
              //  cout<<row<<' '<<col<<endl;
            return true;
        }
    }
    return false;
}


bool issafe(int num,int row,int col)
{

    bool rowf=true;
   bool gf=true;
    bool colf=true;
  
   for(int i=1;i<=9;i++)
    if(suduko[row][i]==num)
    rowf=false;
    
    
    for(int i=1;i<=9;i++)
    if(suduko[i][col]==num)
    colf=false;
    
    int ri,ci;
    
    for(int i=0,ri=row-row%3;i<3;i++,ri++)
    {
        
        for(int j=0,ci=col-col%3;j<3;j++,ci++)
        {
            if(suduko[ri+1][ci+1]==(num))
            gf=false;
        }
    }
    
    return rowf&&colf&&gf;
    
        
}

bool solver()
{
    int row,col;
    if(!findspace(row,col))
    return true;
    //cout<<row<<" "<<col<<endl;
    for(int i=1;i<=9;i++)
    {
        if(issafe(i,row,col))
        suduko[row][col]=(i);
        else
        continue;
        
        if(!solver())
        suduko[row][col]=0;
        else
        return true;
    }
    return false;
    
}

bool backtrack_algo()
{
	return solver();
}


int main()
{
	FR
	//FW
	clock_t start;
	//start of clock time
	start=clock();

	memset(numbers,true,sizeof(numbers));

	input();
	find_possible();
	human_algo();
	
	if(check())
	{
		cout<<"yes";
		//use backtraking algo if it is not possible to solve the suduko by human algo
		if(backtrack_algo())
			print();
		else
			cout<<"No solution Possible"<<endl;	

	}
	else
	{
		print();
	}



	cout<<"Time Elapsed: ";
	cout<<(clock()-start)/(double)CLOCKS_PER_SEC<<endl;
	return 0;
}
