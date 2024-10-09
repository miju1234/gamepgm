#include <stdio.h> //ǥ�� ����� 
#include <stdlib.h> //ǥ�� ��ƿ��Ƽ 
#include <conio.h> //���� �ܼ� ����� 
#include <windows.h> //system �Լ� ��� 
#include <time.h> //�ð� 

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

int tx[3], ty[3];      //���� ��ġ �迭 
int hx[10], hy[10];    //��Ʈ ��ġ �迭 
int tnx[10], tny[10];  //�ﰢ�� ��ġ �迭 
int cx[10], cy[10];    //�� ��ġ �迭 
    
    

int main(void)
{ 
	init();
}

void init(void){
	clock_t start, end;
	int matrix[10][10]={0}; //�� �迭
    double pst;
    char key;
    
    srand(time(NULL));   //������������ 
	display_rule();     // ���Ӽ��� ȭ�� 
    start=clock();      //���۽ð� ���� 
	system("cls");     //�ܼ������ 
	game_control(start);
    
    end=clock(); //���� �ð� ���� 
	pst=(double)(end-start)/CLK_TCK; //����ð� >1�ʿ� CLK_TCK �� �ȵ�
	gotoxy(1, 15); 
	printf("��� �ð� : %.1f ��", pst);
	
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
		printf("�ð��ʰ�. ������ �� ã�� ���߽��ϴ�. \n");
	}
	else{
		printf("��� ã�ҽ��ϴ�. ������ �����մϴ�. \n");
	} 
	
	gotoxy(1, 20);
	printf("�� Ȩ ȭ������(B)  \n");
	getch();
	key = getch();
	printf("%d\n", key);
	if(key=='B'||key=='b'){
		system("cls");//�ܼ������ 
		init();
	}
} 

void display_rule(void)
{
	char key;
	gotoxy(1, 1);
	printf("����ã��");
	gotoxy(1,3);
	printf("�Ʒ��� �ٵ��� ����� ���ڿ��� ������ \n");
	gotoxy(1,4);
	printf("������ �ֽ��ϴ�. \n");
	gotoxy(1,6);
	printf("ȭ��ǥ(�����)Ű�� �������� ã���ϴ�. \n");
	
	gotoxy(1,8);
	basic_map();  //�� ȭ�� 
	
	
	printf("\n�� ���Ӽ��� �ڼ��� ���� (space bar �Է�) \n");
	printf("�� �����Ϸ��� ������ �Է����ּ���. (1, 2, 3 �� �Է�)\n");
	
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
	printf("����ã��");
	gotoxy(1,3);
	printf("���� �ð�(30��) �ȿ� ������ ��� ã���� clear"); 
	gotoxy(1,5);
	printf("���� �ð� ���� ã�� ���� ���� ������ ����ϴ�. \n");
	gotoxy(1,6);
	printf("������ŭ ���� ������ �����˴ϴ�. \n");
	gotoxy(1,8);
	printf("2�ܰ���� �پ��� �������� ���ɴϴ�. \n");
	gotoxy(1,10);
	printf("<������ ���> \n");
	gotoxy(1,12);
	printf(" �� : ���� �ð��� �þ�� ������\n");
	gotoxy(1,13);
	printf(" �� : ���� �ð��� �پ��� ������ \n");
	gotoxy(1,14);
	printf(" �� : ������ ���� �ʱ�ȭ�Ǵ� ������ \n");

	gotoxy(1, 20);
	printf("�� Ȩ ȭ������(B)  \n");
	key = getch();
	printf("%d\n", key);
	if(key=='B'||key=='b'){
		system("cls");//�ܼ������ 
		init();
	}
}

void basic_map(void)
{
	int i, j;
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
			printf("��");
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
			tx[i]=rand()%11; //������ x��ǥ
			ty[i]=rand()%11; //������ y��ǥ
			
			if(i == 1 && tx[i] == tx[i-1] && ty[i] == ty[i-1]) continue; //���� �ڸ��� ����x i�� �տ� i-1�̴ϱ� �տ����� ���ִ���(1) 
			 
			
		}while((tx[i]<=1) || (ty[i]<=1));  
    }
     

    for(i=0; i<Lv-1; i++){     //��Ʈ ���� 
	   	do{
	    	hx[i]=rand()%11;  //��Ʈ�� x��ǥ
			hy[i]=rand()%11;  //��Ʈ�� y��ǥ
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
	
	if(Lv>1)          //�ﰢ�� ���� 
	{
    	for(i=0; i<Lv; i++){
	    	do{
	    		tnx[i]=rand()%11; //�ﰢ�� x��ǥ
				tny[i]=rand()%11; //�ﰢ�� y��ǥ
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
	
	if(Lv>1)          //��ź(��) ���� 
	{
    	for(i=0; i<Lv; i++){
	    	do{
	    		cx[i]=rand()%11; //��ź(��)�� x��ǥ
				cy[i]=rand()%11; //��ź(��)�� y��ǥ
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
				printf("��");
			}
			else if (matrix[i][j]==2)
			{
				gotoxy(2*i-1, j);
				printf("��");
			}
			else if (matrix[i][j]==3)
			{
				gotoxy(2*i-1, j);
				printf("��");
			}
			else if (matrix[i][j]==4)
			{
				gotoxy(2*i-1, j);
				printf("��");
			}
			else if (matrix[i][j]==5)
			{
				gotoxy(2*i-1, j);
				printf("��");
			}

	gotoxy(25, 1);
    printf("%d %d %d %d %d %d ��Ʈ : %d %d %d %d %d %d ��: %d %d %d %d %d %d", ty[0], tx[0], ty[1], tx[1], ty[2], tx[2], hx[0], hy[0],hx[1], hy[1],hx[2], hy[2], cx[0], cy[0],cx[1], cy[1],cx[2], cy[2]);
}
void move_arrow_key(char key, int *x1, int *y1, int x_b, int y_b)
{
	switch(key)
	{
	case 72:  //����(��) ������ ȭ��ǥ Ű �Է�
		*y1=*y1-1;
		if (*y1<1)	*y1=1; //y��ǥ�� �ּҰ�
		break;
	case 75:  //����(��) ������ ȭ��ǥ Ű �Է�
		*x1=*x1-2;            //x��ǥ�� ���Ұ�
		if (*x1<1)	*x1=1; //x��ǥ�� �ּҰ�
		break;
	case 77:  //������(��) ������ ȭ��ǥ Ű �Է�
		*x1=*x1+2;               //x��ǥ�� ������
		if (*x1>x_b)  *x1=x_b; //x��ǥ�� �ִ밪
		break;
	case 80:  //�Ʒ���(��) ������ ȭ��ǥ Ű �Է�
		*y1=*y1+1;
		if (*y1>y_b)  *y1=y_b; //y��ǥ�� �ִ밪
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
		current = clock(); //����ð��� �������� 
		pst=(double)(current-start)/CLK_TCK;
		gotoxy(x, y); 
		printf("��");
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
					
				else if (matrix[i][j]==3){	//��Ʈ�� ������ �ð� �� �� 
					pst -= 10;
						
				}
				else if(matrix[i][j]==4){  //�ﰢ���� ������ �ð� �پ�� 
					pst += 5;
				}
					
				else if(matrix[i][j]==5){  //��ź�� ������ ������ ��� ���� 
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
		sec5 = (game_t - pst) / 6;   //�����ð�(6�ʴ���) 
		
		if(sec5==0){
			printf("�����ð� : ������");
		}
		else if(sec5==1){
			printf("�����ð� : ������");
		}
		else if(sec5==2){
			printf("�����ð� : ������");
		}
		else if(sec5==3){
			printf("�����ð� : ������");
		}
		else if(sec5==4){
			printf("�����ð� : ������");
		}
		
		gotoxy(1,13);
   		printf("ã�� ����(��)�� ���� : %d", count);
		
		key=getch();
		move_arrow_key(key, &x, &y, 19, 10);
		
	}while(count<Lv && game_t > pst);

	if (game_t - pst <= 0)
	{
		gotoxy(1,12);
		printf("�����ð� : ������");
	} 
	
	tm_point = game_t - pst;
}
