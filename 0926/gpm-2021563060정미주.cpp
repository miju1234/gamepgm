#include <stdio.h> //표준 입출력 
#include <stdlib.h> //표준 유틸리티 
#include <conio.h> //직접 콘솔 입출력 
#include <windows.h> //system 함수 사용 
#include <time.h> //시간 

void display_rule(void);
void gotoxy(int x, int y);
void make_treasure();
void display_map(int matrix[][10]);
void basic_map(void);
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b);
void game_control(clock_t start);
void init(void);
void details_rule(void);

int count =0; 
int Lv;
int gm_rule; 
double tm_point;

int tx[3], ty[3];      //보물 위치 배열 
int hx[10], hy[10];    //하트 위치 배열 
int tnx[10], tny[10];  //삼각형 위치 배열 
int cx[10], cy[10];    //원 위치 배열 
    
    

int main(void)
{ 
	init();
}

void init(void){
	clock_t start, end;
	int matrix[10][10]={0}; //맵 배열
    double pst;
    char key;
    
    srand(time(NULL));   //랜덤난수생성 
	display_rule();     // 게임설명 화면 
    start=clock();      //시작시간 저장 
	system("cls");     //콘솔지우기 
	game_control(start);
    
    end=clock(); //끝난 시간 저장 
	pst=(double)(end-start)/CLK_TCK; //경과시간 >1초에 CLK_TCK 번 똑딱
	gotoxy(1, 15); 
	printf("경과 시간 : %.1f 초", pst);
	
	gotoxy(1, 17); 
	if(tm_point>0 && tm_point<5){
		printf("Good! \n");
	}
	else if(tm_point>5 && tm_point<10){
		printf("Very Good! \n");
	}
	else if(tm_point>10 && tm_point<20){
		printf("Excellent! \n");
	}
		else if(tm_point>20){
		printf("You're perfect! \n");
	}
	
	gotoxy(1, 18); 
	if(count!=Lv){
		printf("시간초과. 보물을 다 찾지 못했습니다. \n");
	}
	else{
		printf("모두 찾았습니다. 게임을 종료합니다. \n");
	} 
	
	gotoxy(1, 20);
	printf("▶ 홈 화면으로(B)  \n");
	getch();
	key = getch();
	printf("%d\n", key);
	if(key=='B'||key=='b'){
		system("cls");//콘솔지우기 
		init();
	}
} 

void display_rule(void)
{
	char key;
	gotoxy(1, 1);
	printf("보물찾기");
	gotoxy(1,3);
	printf("아래의 바둑판 모양의 격자에는 보물이 \n");
	gotoxy(1,4);
	printf("숨겨져 있습니다. \n");
	gotoxy(1,6);
	printf("화살표(↑↓←→)키를 움직여서 찾습니다. \n");
	
	gotoxy(1,8);
	basic_map();  //맵 화면 
	
	
	printf("\n▶ 게임설명 자세히 보기 (space bar 입력) \n");
	printf("▶ 시작하려면 레벨을 입력해주세요. (1, 2, 3 중 입력)\n");
	
	key = getch();
	if(key==32)
		details_rule();

	else if(key - '0' == 1){
		Lv = 1;
	}
	else if(key - '0' == 2){
		Lv = 2;
	}
	else if(key - '0' == 3){
		Lv = 3;
	}
}

void details_rule(void){
	char key;
	
	system("cls");
	gotoxy(1, 1);
	printf("보물찾기");
	gotoxy(1,3);
	printf("제한 시간(30초) 안에 보물을 모두 찾으면 clear"); 
	gotoxy(1,5);
	printf("빠른 시간 내에 찾을 수록 높은 점수를 얻습니다. \n");
	gotoxy(1,6);
	printf("레벨만큼 보물 갯수가 생성됩니다. \n");
	gotoxy(1,8);
	printf("2단계부터 다양한 아이템이 나옵니다. \n");
	gotoxy(1,10);
	printf("<아이템 목록> \n");
	gotoxy(1,12);
	printf(" ♥ : 제한 시간이 늘어나는 아이템\n");
	gotoxy(1,13);
	printf(" ▲ : 제한 시간이 줄어드는 아이템 \n");
	gotoxy(1,14);
	printf(" ● : 지나온 블럭이 초기화되는 아이템 \n");

	gotoxy(1, 20);
	printf("▶ 홈 화면으로(B)  \n");
	key = getch();
	printf("%d\n", key);
	if(key=='B'||key=='b'){
		system("cls");//콘솔지우기 
		init();
	}
}

void basic_map(void)
{
	int i, j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			printf("■");
		printf("\n");
	}
}


void make_treasure()
{
	int i,j;
    for(i=0; i<Lv; i++)
    {	
		do
		{
			tx[i]=rand()%11; //보물의 x좌표
			ty[i]=rand()%11; //보물의 y좌표
			
			if(i == 1 && tx[i] == tx[i-1] && ty[i] == ty[i-1]) continue; //같은 자리에 생성x i의 앞에 i-1이니까 앞에꺼에 들어가있는지(1) 
			 
			
		}while((tx[i]<=1) || (ty[i]<=1));  
    }
     

    for(i=0; i<Lv-1; i++){     //하트 생성 
	   	do{
	    	hx[i]=rand()%11;  //하트의 x좌표
			hy[i]=rand()%11;  //하트의 y좌표
			for(j=0; j<Lv; j++){
				if(tx[j]==hx[j] && ty[j]==hy[j]){
					hx[j] = 1;
					hy[j] = 1;
					break;
				}
			}
			if(i == 1 && hx[i] == hx[i-1] && hy[i] == hy[i-1]) continue;
				
		}while((hx[i]<=1) || (hy[i]<=1));
	} 
	
	if(Lv>1)          //삼각형 생성 
	{
    	for(i=0; i<Lv; i++){
	    	do{
	    		tnx[i]=rand()%11; //삼각형 x좌표
				tny[i]=rand()%11; //삼각형 y좌표
				for(j=0; j<Lv; j++){
					if(tnx[j]==tx[j] && tny[j]==ty[j]){
						if(tnx[j]==hx[j] && tny[j]==hy[j]){
							if(tnx[j]==cx[j] && tny[j]==cy[j]){
								cx[j] = 1;
								cy[j] = 1;
								break;
							}
							break;
						}
						break;
					}
				}
				if(i == 1 && tnx[i] == tnx[i-1] && tny[i] == tny[i-1]) continue;
			}while((tnx[i]<=1) || (tny[i]<=1));
		} 
	}
	
	if(Lv>1)          //폭탄(원) 생성 
	{
    	for(i=0; i<Lv; i++){
	    	do{
	    		cx[i]=rand()%11; //폭탄(원)의 x좌표
				cy[i]=rand()%11; //폭탄(원)의 y좌표
				for(j=0; j<Lv; j++){
					if(cx[j]==tx[j] && cy[j]==ty[j]){
						if(cx[j]==hx[j] && cy[j]==hy[j]){
							cx[j] = 1;
							cy[j] = 1;
							break;
						}
						break;
					}
				}
				
				if(i == 1 && cx[i] == cx[i-1] && cy[i] == cy[i-1]) continue;
				
			}while((cx[i]<=1) || (cy[i]<=1));
		} 
	}
	

}



void gotoxy(int x, int y)
{
   COORD Pos = {x - 1, y - 1};
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void display_map(int matrix[][11])
{	
	gotoxy(1,1);
	int i, j;
	basic_map();
	for(i=1;i<=10;i++)
		for(j=1;j<=10;j++)
			if (matrix[i][j]==1)
			{
				gotoxy(2*i-1, j);
				printf("□");
			}
			else if (matrix[i][j]==2)
			{
				gotoxy(2*i-1, j);
				printf("★");
			}
			else if (matrix[i][j]==3)
			{
				gotoxy(2*i-1, j);
				printf("♥");
			}
			else if (matrix[i][j]==4)
			{
				gotoxy(2*i-1, j);
				printf("▲");
			}
			else if (matrix[i][j]==5)
			{
				gotoxy(2*i-1, j);
				printf("●");
			}

	gotoxy(25, 1);
    printf("%d %d %d %d %d %d 하트 : %d %d %d %d %d %d 원: %d %d %d %d %d %d", ty[0], tx[0], ty[1], tx[1], ty[2], tx[2], hx[0], hy[0],hx[1], hy[1],hx[2], hy[2], cx[0], cy[0],cx[1], cy[1],cx[2], cy[2]);
}
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch(key)
	{
	case 72:  //위쪽(상) 방향의 화살표 키 입력
		*y1=*y1-1;
		if (*y1<1)	*y1=1; //y좌표의 최소값
		break;
	case 75:  //왼쪽(좌) 방향의 화살표 키 입력
		*x1=*x1-2;            //x좌표의 감소값
		if (*x1<1)	*x1=1; //x좌표의 최소값
		break;
	case 77:  //오른쪽(우) 방향의 화살표 키 입력
		*x1=*x1+2;               //x좌표의 증가값
		if (*x1>x_b)  *x1=x_b; //x좌표의 최대값
		break;
	case 80:  //아래쪽(하) 방향의 화살표 키 입력
		*y1=*y1+1;
		if (*y1>y_b)  *y1=y_b; //y좌표의 최대값
		break;
	default:
		return;
	}
}

void game_control(clock_t start)
{
	char key;
	int i, j;
	int x=1, y=1;
	int sec5;
	int matrix[11][11]={0};
	clock_t current;
	double pst;
	double game_t = 30;
	double tm;
	
	make_treasure();
	
	do
	{
		current = clock(); //현재시간을 가져오기 
		pst=(double)(current-start)/CLK_TCK;
		gotoxy(x, y); 
		printf("□");
		matrix[(x+1)/2][y]=1;

		for(i=0;i<Lv;i++)
			if (((x+1)/2==tx[i]) && (y==ty[i]))
				matrix[(x+1)/2][y]=2;
				
		for(i=0;i<Lv;i++)
			if (((x+1)/2==hx[i]) && (y==hy[i]))
				matrix[(x+1)/2][y]=3;
				
		for(i=0;i<Lv;i++)
			if (((x+1)/2==tnx[i]) && (y==tny[i]))
				matrix[(x+1)/2][y]=4;
						
		for(i=0;i<Lv;i++)
			if (((x+1)/2==cx[i]) && (y==cy[i]))
				matrix[(x+1)/2][y]=5;

		gotoxy(1, 1);
		display_map(matrix);      
		
		count=0;
		for(i=1;i<=10;i++){    
			for(j=1;j<=10;j++){
				if (matrix[i][j]==2)
					count=count+1;
					
				else if (matrix[i][j]==3){	//하트를 먹으면 시간 더 줌 
					pst -= 10;
						
				}
				else if(matrix[i][j]==4){  //삼각형을 먹으면 시간 줄어듬 
					pst += 5;
				}
					
				else if(matrix[i][j]==5){  //폭탄을 먹으면 지나온 블록 리셋 
					Sleep(500);
					for(i=1;i<=10;i++){
						for(j=1;j<=10;j++){
							matrix[i][j]=0;
						}
					}
					display_map(matrix); 
				}			
			}
		}            
					
		gotoxy(1,12);
		sec5 = (game_t - pst) / 6;   //남은시간(6초단위) 
		
		if(sec5==0){
			printf("남은시간 : ■□□□□");
		}
		else if(sec5==1){
			printf("남은시간 : ■■□□□");
		}
		else if(sec5==2){
			printf("남은시간 : ■■■□□");
		}
		else if(sec5==3){
			printf("남은시간 : ■■■■□");
		}
		else if(sec5==4){
			printf("남은시간 : ■■■■■");
		}
		
		gotoxy(1,13);
   		printf("찾은 보물(★)의 개수 : %d", count);
		
		key=getch();
		move_arrow_key(key, &x, &y, 19, 10);
		
	}while(count<Lv && game_t > pst);

	if (game_t - pst <= 0)
	{
		gotoxy(1,12);
		printf("남은시간 : □□□□□");
	} 
	
	tm_point = game_t - pst;
}
