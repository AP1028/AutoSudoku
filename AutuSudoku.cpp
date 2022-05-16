//
//  main.cpp
//  AutoSuduku2.0
//
//  Created by TianYiXia on 2020/6/12.
//  Copyright 漏 2020 TianYiXia. All rights reserved.
//

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_GREEN); //改变颜色输出代码样例 
//0 黑色
//1 蓝色
//2 绿色
//3 湖蓝色
//4 红色
//5 紫色
//6 黄色
//7 白色
//8 灰色
//9 淡蓝色
//A 淡绿色
//B 淡浅绿色
//C 淡红色
//D 淡紫色
//E 淡黄色
//F 亮白色 
struct met //定义表格主结构体 
{
    int val=0; //存图 
    int x[10]={0,0,0,0,0,0,0,0,0,0}; //存行 
    int y[10]={0,0,0,0,0,0,0,0,0,0}; //存列 
    int z[10]={0,0,0,0,0,0,0,0,0,0}; //存表格 
    int sx[10]={0,0,0,0,0,0,0,0,0,0}; //存行（算法预处理） 
    int sy[10]={0,0,0,0,0,0,0,0,0,0}; //存列（算法预处理）
    int sum=0; //存三个占据方向的占据数量 
    bool array=0;
    bool hash[10]={0,0,0,0,0,0,0,0,0,0}; //存三个占据方向的占据情况 
    int color=2; 
}sud[10][10];
struct met2 //定义表格结构体 
{
	bool hash[10]={0,0,0,0,0,0,0,0,0,0}; //存表格情况 
	int sum=0; //存占据数据总量 
}ar[4][4];
int tempcolor=2; //临时颜色数据 
int cchain[(0xe)+2]; //定义颜色数据链 
bool pa=0; //是否自动延时 
int cnt=0; //记录总操作数 
int delay2=0; //转为int类型延时数据 
double delay; //定义延时变量 
int dmode; //记录操作数据 
int total;
void debug();
void console();
void array();
bool check() //检查算法 
{
	for(int i=1;i<=9;i++)
	{
		bool check[10]={0,0,0,0,0,0,0,0,0,0};
		for(int j=1;j<=9;j++)
		{
			if(check[sud[i][j].val]==1) return 1;
			check[sud[i][j].val]=1;
		}
	}
	return 0;
}
void Input() //输入函数 
{
    cout<<"Please input the suduku in 9 strings and replace space with 0.\nExample:\n103040608\n004678100\n000103000\n070000050\n380090046\n010000080\n000709000\n001582900\n702030805\n";
    cout<<"Input:\n";
    char temp[10][10];
    for (int i = 1; i <= 9; i++)
    {
        for (int j = 1; j <= 9; j++)
        {
            cin >> temp[i][j];
            sud[i][j].val = temp[i][j] - '0';
            if(sud[i][j].val)
            {
            	sud[i][j].color=7;
			}
        }
    }
    cout<<endl;
    char temp1;
    cout<<"Auto delay?(Y/N)"; //输入是否自动延时的参数 
    cin>>temp1;
    if(temp1=='Y'|| temp1=='y')
    {
    	pa=1;
    	cout<<"Input the dalay in seconds: "; //输入延时时间 
    	cin>>delay;
    	cout<<endl;
	}
    else
	{
		pa=0;
		delay=0;
	}
    //debug
    //cout<<"input complete"<<endl;
    return;
}
void Output() //输出函数 
{
	array(); //调用数组标记函数 
	Sleep(delay2);  //延时 
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    printf("\n+---+---+---+\n");
    for (int i = 1; i <= 9; i++)
    {
        printf("|");
        for (int j = 1; j <= 9; j++)
        {
        	if(sud[i][j].val) //以颜色打印 
        	{
        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),sud[i][j].color);
            	printf("%d",sud[i][j].val);
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
        	}
        	else if(sud[i][j].array==1) //打印数组 
        	{
        		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
            	printf("*");
            	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
			}
            else
            	printf(" ");
            if (j % 3 == 0)
            {
                printf("|");
            }
        }
        printf("\n");
        if (i % 3 == 0)
        {
            printf("+---+---+---+\n");
        }
    }
    //清空数组情况 
    for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			sud[i][j].array=0;
    cout<<"Total write and erace: "<<cnt<<endl; //输出读写操作 
    //输出图例 
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    cout<<"X";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    cout<<"---Static parts.\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),2);
    cout<<"X";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    cout<<"---Sured numbers.\n";
    int i=9;
    int c=1;
    while(i!=4)
    {
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),i);
	    cout<<"X";
	    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
	    cout<<"---Layer "<<c<<" guessings.\n";
	    i=cchain[i];
	    c++;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),4);
    cout<<"X";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    cout<<"---Layer "<<c<<" or more guessings.\n";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),6);
    printf("*");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
    cout<<"---Detected arrays.\n";
    if(pa==0)
    {
    	system("pause"); //手动继续 
	}
    //sleep(1000);
    return;
}
void update() //刷新函数 
{
	//total=0;
	//刷新行和列 
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
			for(int k=1;k<=9;k++)
			{
				sud[i][j].hash[k]=0;
				sud[i][j].x[k]=0;
				sud[i][j].y[k]=0;
				sud[i][j].z[k]=0;
				sud[i][j].sum=0;
			}
	//刷新九宫格 
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
        {
            for(int k=1;k<=9;k++)
            {
                sud[i][j].x[sud[k][j].val]=1;
                sud[i][j].y[sud[i][k].val]=1;
                sud[i][j].hash[sud[k][j].val]=1;
                sud[i][j].hash[sud[i][k].val]=1;
            }
            int x,y;
            x=int((i-1)/3)+1;
            y=int((j-1)/3)+1;
            for(int k=3*x-2;k<=3*x;k++)
            {
                for(int l=3*y-2;l<=3*y;l++)
                {
                    sud[i][j].z[sud[k][l].val]=1;
                    sud[i][j].hash[sud[k][l].val]=1;
                }
        	}
            for(int k=1;k<=9;k++)
            {
                sud[i][j].sum+=sud[i][j].hash[k];
                total+=sud[i][j].hash[k];
            }
        }
    return;
}
void supdate(int x,int y,bool type) //未debug完刷新函数 
{
    int temp=sud[x][y].val;
    if(type)
    {
        for(int i=1;i<=9;i++)
        {
            sud[i][y].x[temp]=1;
            sud[i][y].hash[temp]=1;
            if(sud[i][y].y[temp]==0 || sud[i][y].z[temp]==0)
            {
                sud[i][y].sum++;
                total++;
            }
        }
        for(int i=1;i<=9;i++)
        {
            sud[x][i].y[temp]=1;
            sud[x][i].hash[temp]=1;
            if(sud[x][i].y[temp]==0 || sud[x][i].z[temp]==0)
            {
                sud[i][y].sum++;
                total++;
            }
        }
        x=int((x-1)/3)+1;
        y=int((y-1)/3)+1;
        for(int k=3*x-2;k<=3*x;k++)
            for(int l=3*y-2;l<=3*y;l++)
            {
                sud[k][l].z[temp]=1;
                sud[k][l].hash[temp]=0;
                if(sud[k][l].x[temp]==0 || sud[k][l].y[temp]==0)
                {
                    sud[k][l].sum++;
                    total++;
                }
            }
    }
    else
    {
        for(int i=1;i<=9;i++)
        {
            sud[i][y].x[temp]=0;
            if(sud[i][y].y[temp]==0 && sud[i][y].z[temp]==0)
            {
                sud[i][y].hash[temp]=0;
                sud[i][y].sum--;
                total--;
            }
        }
        for(int i=1;i<=9;i++)
        {
            sud[x][i].y[temp]=0;
            if(sud[x][i].y[temp]==0 && sud[x][i].z[temp]==0)
            {
                sud[x][i].hash[temp]=0;
                sud[x][i].sum--;
                total--;
            }
        }
        x=int((x-1)/3)+1;
        y=int((y-1)/3)+1;
        for(int k=3*x-2;k<=3*x;k++)
            for(int l=3*y-2;l<=3*y;l++)
            {
                sud[k][l].z[temp]=0;
                if(sud[k][l].x[temp]==0 && sud[k][l].y[temp]==0)
                {
                    sud[k][l].hash[temp]=0;
                    sud[k][l].sum--;
                    total--;
                }
            }
    }
    return;
}
bool basic()
{
	bool flag=0;
	int min=0x7fffffff;
    int x,y;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            if(sud[i][j].val==0 && sud[i][j].sum==8)
            {
                for(int k=1;k<=9;k++)
                {
                	if(!sud[i][j].hash[k])
                	{
                		flag=1; 
                		sud[i][j].val=k; 
                		cnt++;
                		update();
                		Output();
                		break;
					}
				}
            }
    return flag;
}
bool basic2()
{
	for(int i=1;i<=9;i++) //i:lane
	{
		for(int j=1;j<=9;j++) //j:target
		{
			int sign=0;
			int tar=0;
			for(int k=1;k<=9;k++) //k:every unit
			{
				if(sud[i][k].hash[j]==0 && sign==0)
				{
					sign=1;
					tar=k;
				}
				else if(sign)
				{
					sign=2;
					break;
				}
			}
			if(sign==1)
			{
				sud[i][tar].val=j;
				sud[i][tar].color=2;
				cnt++;
				update();
                Output();
                //cout<<"basic2 detected on "<<i<<" "<<tar<<" with the value of"<<j<<endl;
				//system("pause");
				return true;
			}
		}
	}
	for(int i=1;i<=9;i++) //i:lane num
	{
		for(int j=1;j<=9;j++) //j:target
		{
			int sign=0;
			int tar=0;
			for(int k=1;k<=9;k++) //k:every unit in lane
			{
				if(sud[k][i].hash[j]==0 && sign==0)
				{
					sign=1;
					tar=k;
				}
				else if(sign)
				{
					sign=2;
					break;
				}
			}
			if(sign==1)
			{
				sud[tar][i].val=j;
				sud[tar][i].color=2;
				//cout<<"basic2 detected on "<<tar<<" "<<i<<" with the value of"<<j<<endl;
				//system("pause"); 
				update();
                Output();
				return true;
			}
		}
	}
	update();
	//arupdate();
	for(int i=1;i<=3;i++)      //metrix 3x3 in 9x9
		for(int j=1;j<=3;j++)  //metrix 3x3 in 9x9
			for(int k=1;k<=9;k++) //select the target
			{
				int sign=0;
				int tarx=0;
				int tary=0;
				for(int l=3*i-2;l<=3*i;l++) 		//metrix in 3x3
				{
					for(int m=3*i-2;m<=3*i;m++)		//metrix in3x3
					{
						if(sud[l][m].hash[k]==0 && sign==0)
						{
							sign=1;
							tarx=l;
							tary=m;
						}
						else if(sign)
						{
							sign=2;
							break;
						}
					}
				}
				if(sign==1)
				{
					sud[tarx][tary].val=k;
					cout<<"basic2 detected on "<<tarx<<" "<<tary<<" with the value of"<<j<<endl;
					update();
	                Output();
					return true;
				}
			}
	//cout<<"Nothing found with 2 :("<<endl;
	return false;
}
void array() //数组显示 
{
	int sum[9][3]; //1=row, 2=lane, 3=block
	int ans_x[9];
	int ans_y[9]; 
	int T=0;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
		{
			if(sud[i][j].color==6)
			{
				sud[i][j].color=7;
			}			
		}
	T=1;
	for ( int i = 1 ; i <= 9 ; i ++ )//i行 
	{
		memset(ans_x,0,sizeof(ans_x));
		memset(ans_y,0,sizeof(ans_y));
		int tot = 0 ;//存储这一行的答案 
		for ( int j = 1 ; j <= 9 ; j ++ ) //j列 
		{
			if(sud[i][j].val==0) //没填 
			{
				sum[i][T]++;
				ans_x[++tot]=i;
				ans_y[tot]=j;
			}
		}
		if(sum[i][T]>=2 && sum[i][T]<=3)
		{
			for(int k=1;k<=tot;k++)
			{
				sud[ans_x[k]][ans_y[k]].array=1;
			}
		 } 
	}
	T=2;
	for(int j=1;j<=9;j++)//j列 
	{
		memset(ans_x,0,sizeof(ans_x));
		memset(ans_y,0,sizeof(ans_y));
		int tot = 0 ;//存储这一行的答案 
		for(int i=1;i<=9;i++) //j列 
		{
			if(sud[i][j].val==0) //没填 
			{
				sum [j][T] ++ ;
				ans_x[++tot] = i ;
				ans_y[tot] = j ;
			}
		}
		if(sum[j][T]>=2 && sum[j][T]<=3)
		{
			for(int k=1;k<=tot;k++)
			{
				sud[ans_x[k]][ans_y[k]].array=1;
			}
		 } 
	}
}
void arupdate()
{
	for(int i=1;i<=3;i++)
		for(int j=1;j<=3;j++)
			for(int k=1;k<=9;k++)
			{
				ar[i][j].hash[k]=sud[3*i][3*j].z[k];
				ar[i][j].sum+=sud[3*i][3*j].z[k];
			}
}
void dfs() //深搜 
{
	int t=0;
	for(int j=1;j<=9;j++)
		for(int k=1;k<=9;k++)
			if(sud[j][k].val) t++; //记录总数 
    if(t>=81) //确认越界后返回 
    {
    	return;
    }
    int min=0x7fffffff;
    int x,y; //定义目标坐标 
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            if(sud[i][j].val==0 && 9-sud[i][j].sum<min && sud[i][j].sum<9) //如果找到没填满的空格 
            {
                x=i;y=j;min=9-sud[i][j].sum; //记录该坐标，刷新min 
            }
            else if(sud[i][j].val==0 && sud[i][j].sum>=9) return; //如果找到不符数字直接结束 
    for(int i=1;i<=9;i++) //枚举该元素hash数组 
    {
        if(!sud[x][y].hash[i]) //找到可以填的数 
        {
            sud[x][y].val=i; //写入 
            int ttcolor=tempcolor; //更新颜色 
            int tcolor=sud[x][y].color; //记录原有颜色 
            if(min>1) //如果不确认推进颜色 
            {
            	sud[x][y].color=cchain[tempcolor];
            	tempcolor=sud[x][y].color;
			}
			else //写入应有颜色 
				sud[x][y].color=tempcolor;
            cnt++; //更新计数器 
            Output(); //输出 
            update(); //更新 
            dfs(); //继续深搜 
            int t=0;
            for(int j=1;j<=9;j++)
            	for(int k=1;k<=9;k++)
            		if(sud[j][k].val) t++;

            if(t<81)
            {
                sud[x][y].val=0;
                if(min>1)
                {
                	sud[x][y].color=tcolor;
                	tempcolor=ttcolor;
            	}
                cnt++;
                update();
                Output();
            }
            else
            {
            	return;
			}
        }
    }
    return;
}
void debug() //debug用输出函数 
{
	for(int i=1;i<=9;i++)
	{
		for(int j=1;j<=9;j++)
			cout<<sud[i][j].val<<"("<<sud[i][j].sum<<") ";
		cout<<endl;
	}	
	return;
}
void sdebug(int x,int y)  //debug用数据提取函数 
{
	cout<<"val="<<sud[x][y].val<<endl;
	cout<<"x=";
	for(int i=1;i<=9;i++)
	{
		cout<<sud[x][y].x[i]<<" ";
	}
	cout<<endl;
	cout<<"y=";
	for(int i=1;i<=9;i++)
	{
		cout<<sud[x][y].y[i]<<" ";
	}
	cout<<endl;
	cout<<"z=";
	for(int i=1;i<=9;i++)
	{
		cout<<sud[x][y].z[i]<<" ";
	}
	cout<<endl;
	cout<<"hash=";
	for(int i=1;i<=9;i++)
	{
		cout<<sud[x][y].hash[i]<<" ";
	}
	cout<<endl;
	cout<<"sum="<<sud[x][y].sum<<endl;
}
void console() //debug用命令行函数 
{
	string str;
	while(true)
	{
		cout<<"console>";
		cin>>str;
		if(str=="exit")
		{
			break;
		}
		else if(str=="main")
		{
			Input();
    		update();
    		dfs();
    		Output();
		}
		else if(str=="update")
		{
			update();
		}
		else if(str=="supdate")
		{
			int x,y;
			bool type;
			cout<<"x=";
			cin>>x;
			cout<<endl;
			cout<<"y=";
			cin>>y;
			cout<<endl;
			cout<<"type=";
			cin>>type;
			cout<<endl;
			supdate(x,y,type);
		}
		else if(str=="write")
		{
			int x,y,val;
			cout<<"x=";
			cin>>x;
			cout<<endl;
			cout<<"y=";
			cin>>y;
			cout<<"val=";
			cin>>val;
			sud[x][y].val=val;
		}
		else if(str=="output")
		{
			Output();
		}
		else if(str=="input")
		{
			Input();
		}
		else if(str=="help")
		{
			cout<<"help\ninput\noutput\nwrite(x,y,val)\nupdate\nsupdate(x,y,type)\nmain\ndebug"<<endl;
		}
		else if(str=="debug")
		{
			debug();
		}
		else if(str=="sdebug")
		{
			int x,y;
			cout<<"x=";
			cin>>x;
			cout<<"y=";
			cin>>y;
			sdebug(x,y);
		}
		else
		{
			cout<<"Unknown command\n";
		}
	}
} 
int main() 
{
	system("cls"); 
	//定义颜色数据链 
	cchain[7]=7;
	cchain[2]=3;
	cchain[3]=9;
	cchain[9]=1;
	cchain[1]=0xe;
	cchain[0xe]=0xc;
	cchain[0xc]=4;
	cchain[4]=4;
//	string mode;
//	cout<<"Please input the solving mode:\n's'---solve only\n'v'---verify only\n'vs'---solve after verify\nInput>";
//	cin>>mode; //计算模式
	Input(); //输入 
//	if(mode[0]=='v')
//	{
//		dmode=1;
//	}
//	else if(mode[0]=='s')
//	{
//		dmode=2;
//	}
    delay2=int(delay*1000); //转化实数数据 
    update();
    //算法预处理 
    while(1)
    {
    	if(basic()) 
		{  
			//cout<<"basic=1"<<endl;
		}
		else if(basic2())
		{
			cout<<"Found basic2!"<<endl;
		}
    	else 
		{
			//cout<<"Nothing found, break!"<<endl;
			break; 
		}
    	update();
	}
	update();
    dfs(); //开始深搜 
    Output();
    int n=0;
    //检查是否填满 
    for(int i=1;i<=9;i++)
    	for(int j=1;j<=9;j++)
    		if(sud[i][j].val) n++;
    //根据是否填满确认输出情况 
    if(n==81) //确认填满 
    {
		for(int i=1;i<=9;i++)
			for(int j=1;j<=9;j++)
			{
				if(sud[i][j].color!=7)
					sud[i][j].color=2; //全部除原来的数输出绿色 
			} 
		Output();
		cout<<"Finished!\n";
	}
    else
    	cout<<"Something is wrong. Try a new input.\n"; //输出错误信息 
    system("pause");
    system("cls"); 
    return 0;
}
