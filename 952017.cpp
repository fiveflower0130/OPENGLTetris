#include <windows.h>
#include <stdio.h>
#include <GL\glut.h>
#include <GL\gl.h>
#include <time.h>

#define GRID_WIDTH 10   //�w�q�e��10��
#define GRID_HEIGHT 20  //�w�q����20��

GLfloat Aspect = 300.0f/600.0f;			//�������e���
bool GRID[GRID_WIDTH][GRID_HEIGHT];		//�w�T�w�����
bool ifCube[GRID_WIDTH][GRID_HEIGHT];	//���U�������
bool ifTouch = true;					//�P�_�O�_���~�򩹤U���ܼ�
GLint rotateStatus = 0;					//���স��
GLint Shape;							//����Ϊ�
GLubyte BrightColor[7][3] = {{255,0,0},{0,255,0},{0,0,255},{255,255,0},{255,0,255},{0,255,255},{255,127,0}}; //������h�C��
GLubyte DarkColor[7][3] = {{200,0,0},{0,200,0},{0,0,200},{200,200,0},{200,0,200},{0,200,200},{200,100,0}};	 //����~�h�C��
GLint TimeInterval = 200; //����U�����ɶ����j
int temp[4][2]={0};		  //����Ϊ��Ȧs�Ŷ�
bool full = false;        //�P�_�O�_�����@��

//----------------------------------------�إߤ��----------------------------------------
void SHAPE(GLint shape)
{
	//�N�I��������]�w��false(���)
	for (int i=0; i<GRID_WIDTH; i++)
	{
		for(int j=0; j<GRID_HEIGHT; j++)
		{
			ifCube[i][j]=false;
		}
	}
	//�ѤޤJ��shape�ȱN�s�������l��m����]�w��true
	switch(shape)
	{
	case 0:
		ifCube[5][0] = true;
		ifCube[5][1] = true;
		ifCube[5][2] = true;
		ifCube[5][3] = true;
		break;
	case 1:
		ifCube[4][0] = true;
		ifCube[4][1] = true;
		ifCube[4][2] = true;
		ifCube[5][2] = true;
		break;
	case 2:
		ifCube[5][0] = true;
		ifCube[5][1] = true;
		ifCube[5][2] = true;
		ifCube[4][2] = true;
		break;
	case 3:
		ifCube[5][0] = true;
		ifCube[4][1] = true;
		ifCube[5][1] = true;
		ifCube[6][1] = true;
		break;
	case 4:
		ifCube[4][0] = true;
		ifCube[4][1] = true;
		ifCube[5][1] = true;
		ifCube[5][2] = true;
		break;
	case 5:
		ifCube[5][0] = true;
		ifCube[5][1] = true;
		ifCube[4][1] = true;
		ifCube[4][2] = true;
		break;
	case 6:
		ifCube[4][0] = true;
		ifCube[5][0] = true;
		ifCube[4][1] = true;
		ifCube[5][1] = true;
		break;
	}
}
//----------------------------------------�e���----------------------------------------
void drawGrid(int x , int y, GLubyte ir ,GLubyte ig ,GLubyte ib, GLubyte or ,GLubyte og ,GLubyte ob){
	glColor3ub(or,og,ob);
	glRecti(x, y, x+30, y+30);
	glColor3ub(ir,ig,ib);
	glRecti(x+2, y+2, x+30-2, y+30-2 );		
}
//----------------------------------------�I������----------------------------------------
void hitTest()
{
	for (int i=0; i<GRID_WIDTH; i++){
		for (int j=0; j<GRID_HEIGHT; j++){
			if (ifCube[i][j] == true){
				if (j<GRID_HEIGHT-1){
					if (GRID[i][j+1] == true){
						for (int i1=0; i1<GRID_WIDTH; i1++){
							for (int j1=0; j1<GRID_HEIGHT; j1++){
								if (GRID[i1][j1] == false) GRID[i1][j1] = ifCube[i1][j1];
							}
						}
						ifTouch = true;
					}
				}else{
					for (int i=0; i<GRID_WIDTH; i++){
						for (int j=0; j<GRID_HEIGHT; j++){
							if (GRID[i][j] == false) GRID[i][j] = ifCube[i][j];
							}
						}
					ifTouch = true;
				}
			}
		}
	}
}
//----------------------------------------�����@��----------------------------------------
void fullLine()
{
	int count=0, a=0;
	int fullLineNum[4] = {-1};
	for (int j=0; j<GRID_HEIGHT; j++){
		for(int i=0; i<GRID_WIDTH; i++){
			if (GRID[i][j]==true) count++;
		}
		if (count == GRID_WIDTH)
		{
			fullLineNum[a] = j;
			a++;
		}
		count = 0;
	}
	for(int k=0; k<4; k++)
	{
		if (fullLineNum[k]!=-1)
		{
			for(int j=fullLineNum[k]; j>0; j--){
				for(int i=0; i<GRID_WIDTH; i++){
					GRID[i][j] = GRID[i][j-1];
					GRID[i][j-1] = false;
				}
			}
		}
	}
}
//----------------------------------------�e���c���t��----------------------------------------
void GRIDsystem(){
	//�w�w�쪺���
	for (int i1=0; i1<GRID_WIDTH; i1++){
		for(int j1=0; j1<GRID_HEIGHT; j1++){
			if (GRID[i1][j1]==true) drawGrid (i1*30, 570-j1*30,255,255,255,200,200,200);
			else					drawGrid (i1*30, 570-j1*30,0,0,0,0,0,0);
		}
	}
	//���ͷs���
	if (full==false){
		if (ifTouch==true)
		{
			fullLine();
			Shape = rand()%7;
			rotateStatus = 0;
			ifTouch = false;
			SHAPE(Shape);
			glutPostRedisplay();
		}
	//�e�X�s���
		for (int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				if (ifCube[i][j]==true)
				{
					switch (Shape){

					case 0:
						drawGrid (i*30, 570-j*30,BrightColor[Shape][0],BrightColor[Shape][1],BrightColor[Shape][2],DarkColor[Shape][0],DarkColor[Shape][1],DarkColor[Shape][2]);
						break;
					case 1:
						drawGrid (i*30, 570-j*30,BrightColor[Shape][0],BrightColor[Shape][1],BrightColor[Shape][2],DarkColor[Shape][0],DarkColor[Shape][1],DarkColor[Shape][2]);
						break;
					case 2:
						drawGrid (i*30, 570-j*30,BrightColor[Shape][0],BrightColor[Shape][1],BrightColor[Shape][2],DarkColor[Shape][0],DarkColor[Shape][1],DarkColor[Shape][2]);
						break;
					case 3:
						drawGrid (i*30, 570-j*30,BrightColor[Shape][0],BrightColor[Shape][1],BrightColor[Shape][2],DarkColor[Shape][0],DarkColor[Shape][1],DarkColor[Shape][2]);
						break;
					case 4:
						drawGrid (i*30, 570-j*30,BrightColor[Shape][0],BrightColor[Shape][1],BrightColor[Shape][2],DarkColor[Shape][0],DarkColor[Shape][1],DarkColor[Shape][2]);
						break;
					case 5:
						drawGrid (i*30, 570-j*30,BrightColor[Shape][0],BrightColor[Shape][1],BrightColor[Shape][2],DarkColor[Shape][0],DarkColor[Shape][1],DarkColor[Shape][2]);
						break;
					case 6:
						drawGrid (i*30, 570-j*30,BrightColor[Shape][0],BrightColor[Shape][1],BrightColor[Shape][2],DarkColor[Shape][0],DarkColor[Shape][1],DarkColor[Shape][2]);
						break;
					}
				}
			}
		}
	}
}
//----------------------------------------���ʤ��----------------------------------------
void moveLeft()
{
	bool edge = false;
	for(int j=0; j<GRID_HEIGHT; j++){
		if (ifCube[0][j] == true) edge = true;
	}

	for(int i=GRID_WIDTH-1; i>0; i--){
		for(int j1=0; j1<GRID_HEIGHT; j1++){
			if (ifCube[i][j1] == true && GRID[i-1][j1] == true) edge = true;
		}
	}

	if (!edge)
	{
		for(int i=0; i<GRID_WIDTH-1; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j] = ifCube[i+1][j];
				ifCube[i+1][j] = false;
			}
		}
	}
}

void moveRight()
{
	bool edge = false;
	for(int j=0; j<GRID_HEIGHT; j++){
		if (ifCube[GRID_WIDTH-1][j] == true) edge = true;
	}

	for(int i=0; i<GRID_WIDTH-1; i++){
		for(int j1=0; j1<GRID_HEIGHT; j1++){
			if (ifCube[i][j1] == true && GRID[i+1][j1] == true) edge = true;
		}
	}

	if (!edge)
	{
		for(int i=GRID_WIDTH-1; i>0; i--){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j] = ifCube[i-1][j];
				ifCube[i-1][j] = false;
			}
		}
	}
}

void moveDown()
{
	bool edge = false;
	for(int i=0; i<GRID_WIDTH; i++){
		if (ifCube[i][GRID_HEIGHT] == true) edge = true;
	}

	for(int i1=0; i1<GRID_WIDTH; i1++){
		for(int j=0; j<GRID_HEIGHT-1; j++){
			if (ifCube[i1][j] == true && GRID[i1][j+1] == true) edge = true;
		}
	}

	if (!edge)
	{
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=GRID_HEIGHT-1; j>0; j--){
				ifCube[i][j] = ifCube[i][j-1];
				ifCube[i][j-1] = false;
			}
		}
	}
}
//----------------------------------------�������----------------------------------------
void rotate_0();
void rotate_1();
void rotate_2();
void rotate_3();
void rotate_4();
void rotate_5();

void rotateSystem()
{
	int a=0;
	for(int j=0; j<GRID_HEIGHT; j++){
		for(int i=0; i<GRID_WIDTH; i++){
			if(ifCube[i][j]==true){
				temp[a][0]=i;
				temp[a][1]=j;
				a++;
			}
		}
	}
	
	switch(Shape){
		case 0:
			rotate_0();
			break;
		case 1:
			rotate_1();
			break;
		case 2:
			rotate_2();
			break;
		case 3:
			rotate_3();
			break;
		case 4:
			rotate_4();
			break;
		case 5:
			rotate_5();
			break;
		case 6:
		    //����Τ�����
			break;
	}
}

void rotate_0()
{
	//�����k
	if(rotateStatus==0){
		temp[0][0]-=1;
		temp[0][1]+=0;
		temp[1][0]+=0;
		temp[1][1]-=1;
		temp[2][0]+=1;
		temp[2][1]-=2;
		temp[3][0]+=2;
		temp[3][1]-=3;
	}else{
		temp[0][0]+=1;
		temp[0][1]+=0;
		temp[1][0]+=0;
		temp[1][1]+=1;
		temp[2][0]-=1;
		temp[2][1]+=2;
		temp[3][0]-=2;
		temp[3][1]+=3;
	}
	//�P�_�����O�_����
	int tempi=0,tempj=0;
    bool touch = false;

	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			if(j==0){
				tempi=temp[i][0];
			}else{
				tempj=temp[i][1];	
			}
		}
		if(GRID[tempi][tempj] == true) touch = true;
		if (tempi<0 || tempi>GRID_WIDTH-1) touch = true;
	}
	//����!!
	if(touch ==false){
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j]=false;
			}
		}
		for(int i1=0; i1<4; i1++){
			for(int j1=0; j1<2; j1++){
				if(j1==0){
					tempi = temp[i1][0];
				}else{
					tempj = temp[i1][1];	
				}
			}
			ifCube[tempi][tempj]=true;
		}
		rotateStatus++;
		if(rotateStatus == 2) rotateStatus=0;
	}
}

void rotate_1()
{
	//�����k
	if(rotateStatus==0){
		temp[0][0]+=2;
		temp[0][1]+=0;
		temp[1][0]+=1;
		temp[1][1]-=1;
		temp[2][0]+=0;
		temp[2][1]-=2;
		temp[3][0]-=1;
		temp[3][1]-=1;
	}else if(rotateStatus==1){
		temp[0][0]-=0;
		temp[0][1]+=0;
		temp[1][0]+=0;
		temp[1][1]+=0;
		temp[2][0]-=1;
		temp[2][1]+=1;
		temp[3][0]+=1;
		temp[3][1]+=1;
	}else if(rotateStatus==2){
		temp[0][0]+=1;
		temp[0][1]+=0;
		temp[1][0]-=0;
		temp[1][1]+=1;
		temp[2][0]-=1;
		temp[2][1]+=0;
		temp[3][0]-=2;
		temp[3][1]-=1;
	}else if(rotateStatus==3){
		temp[0][0]-=1;
		temp[0][1]-=0;
		temp[1][0]+=1;
		temp[1][1]+=0;
		temp[2][0]+=0;
		temp[2][1]+=1;
		temp[3][0]+=0;
		temp[3][1]+=1;
	}
	//�P�_�����O�_����
	int tempi=0,tempj=0;
    bool touch=false;

	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			if(j==0){
				tempi=temp[i][0];
			}else{
				tempj=temp[i][1];	
			}
		}
		if(GRID[tempi][tempj] == true) touch = true;
		if(tempi<0 || tempi>GRID_WIDTH-1) touch = true;
	}
	//����!!
	if(touch ==false){
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j]=false;
			}
		}
		for(int i1=0; i1<4; i1++){
			for(int j1=0; j1<2; j1++){
				if(j1==0){
					tempi = temp[i1][0];
				}else{
					tempj = temp[i1][1];	
				}
			}
			ifCube[tempi][tempj]=true;
		}
		rotateStatus++;
		if(rotateStatus == 4) rotateStatus=0;
	}
}

void rotate_2()
{
	if(rotateStatus==0){
		temp[0][0]-=1;
		temp[0][1]+=0;
		temp[1][0]-=1;
		temp[1][1]-=0;
		temp[2][0]+=1;
		temp[2][1]-=1;
		temp[3][0]+=1;
		temp[3][1]-=1;
	}else if(rotateStatus==1){
		temp[0][0]-=0;
		temp[0][1]+=0;
		temp[1][0]+=1;
		temp[1][1]-=1;
		temp[2][0]-=1;
		temp[2][1]+=0;
		temp[3][0]-=2;
		temp[3][1]+=1;
	}else if(rotateStatus==2){
		temp[0][0]-=1;
		temp[0][1]+=0;
		temp[1][0]-=1;
		temp[1][1]+=0;
		temp[2][0]+=1;
		temp[2][1]-=1;
		temp[3][0]+=1;
		temp[3][1]-=1;
	}else if(rotateStatus==3){
		temp[0][0]+=2;
		temp[0][1]-=0;
		temp[1][0]+=1;
		temp[1][1]+=1;
		temp[2][0]+=0;
		temp[2][1]+=2;
		temp[3][0]-=1;
		temp[3][1]+=1;
	}
	//�P�_�����O�_����
	int tempi=0,tempj=0;
    bool touch=false;

	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			if(j==0){
				tempi=temp[i][0];
			}else{
				tempj=temp[i][1];	
			}
		}
		if(GRID[tempi][tempj] == true) touch = true;
		if (tempi<0 || tempi>GRID_WIDTH-1) touch = true;
	}
	//����!!
	if(touch ==false){
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j]=false;
			}
		}
		for(int i1=0; i1<4; i1++){
			for(int j1=0; j1<2; j1++){
				if(j1==0){
					tempi = temp[i1][0];
				}else{
					tempj = temp[i1][1];	
				}
			}
			ifCube[tempi][tempj]=true;
		}
		rotateStatus++;
		if(rotateStatus == 4) rotateStatus=0;
	}
}

void rotate_3()
{
	if(rotateStatus==0){
		temp[0][0]-=0;
		temp[0][1]+=0;
		temp[1][0]+=1;
		temp[1][1]-=0;
		temp[2][0]+=1;
		temp[2][1]-=0;
		temp[3][0]-=1;
		temp[3][1]+=1;
	}else if(rotateStatus==1){
		temp[0][0]-=1;
		temp[0][1]+=0;
		temp[1][0]+=0;
		temp[1][1]-=1;
		temp[2][0]+=0;
		temp[2][1]-=1;
		temp[3][0]-=0;
		temp[3][1]-=1;
	}else if(rotateStatus==2){
		temp[0][0]+=1;
		temp[0][1]+=0;
		temp[1][0]-=1;
		temp[1][1]+=1;
		temp[2][0]-=1;
		temp[2][1]+=1;
		temp[3][0]+=0;
		temp[3][1]+=1;
	}else if(rotateStatus==3){
		temp[0][0]+=0;
		temp[0][1]-=0;
		temp[1][0]+=0;
		temp[1][1]+=0;
		temp[2][0]+=0;
		temp[2][1]+=0;
		temp[3][0]+=1;
		temp[3][1]-=1;
	}
	//�P�_�����O�_����
	int tempi=0,tempj=0;
    bool touch=false;

	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			if(j==0){
				tempi=temp[i][0];
			}else{
				tempj=temp[i][1];	
			}
		}
		if(GRID[tempi][tempj] == true) touch = true;
		if (tempi<0 || tempi>GRID_WIDTH-1) touch = true;
	}
	//����!!
	if(touch ==false){
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j]=false;
			}
		}
		for(int i1=0; i1<4; i1++){
			for(int j1=0; j1<2; j1++){
				if(j1==0){
					tempi = temp[i1][0];
				}else{
					tempj = temp[i1][1];	
				}
			}
			ifCube[tempi][tempj]=true;
		}
		rotateStatus++;
		if(rotateStatus == 4) rotateStatus=0;
	}
}
void rotate_4()
{
	if(rotateStatus==0){
		temp[0][0]-=0;
		temp[0][1]+=0;
		temp[1][0]+=1;
		temp[1][1]-=1;
		temp[2][0]-=2;
		temp[2][1]-=0;
		temp[3][0]-=1;
		temp[3][1]-=1;
	}else if(rotateStatus==1){
		temp[0][0]-=0;
		temp[0][1]+=0;
		temp[1][0]-=1;
		temp[1][1]+=1;
		temp[2][0]+=2;
		temp[2][1]-=0;
		temp[3][0]+=1;
		temp[3][1]+=1;
	}
	//�P�_�����O�_����
	int tempi=0,tempj=0;
    bool touch=false;

	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			if(j==0){
				tempi=temp[i][0];
			}else{
				tempj=temp[i][1];	
			}
		}
		if(GRID[tempi][tempj] == true) touch = true;
		if (tempi<0 || tempi>GRID_WIDTH-1) touch = true;
	}
	//����!!
	if(touch ==false){
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j]=false;
			}
		}
		for(int i1=0; i1<4; i1++){
			for(int j1=0; j1<2; j1++){
				if(j1==0){
					tempi = temp[i1][0];
				}else{
					tempj = temp[i1][1];	
				}
			}
			ifCube[tempi][tempj]=true;
		}
		rotateStatus++;
		if(rotateStatus == 2) rotateStatus=0;
	}
}

void rotate_5()
{
	if(rotateStatus==0){
		temp[0][0]-=1;
		temp[0][1]+=0;
		temp[1][0]+=1;
		temp[1][1]-=1;
		temp[2][0]-=0;
		temp[2][1]-=0;
		temp[3][0]+=2;
		temp[3][1]-=1;
	}else if(rotateStatus==1){
		temp[0][0]+=1;
		temp[0][1]-=0;
		temp[1][0]-=1;
		temp[1][1]+=1;
		temp[2][0]-=0;
		temp[2][1]-=0;
		temp[3][0]-=2;
		temp[3][1]+=1;
	}
	//�P�_�����O�_����
	int tempi=0,tempj=0;
    bool touch=false;

	for(int i=0; i<4; i++){
		for(int j=0; j<2; j++){
			if(j==0){
				tempi=temp[i][0];
			}else{
				tempj=temp[i][1];	
			}
		}
		if(GRID[tempi][tempj] == true) touch = true;
		if (tempi<0 || tempi>GRID_WIDTH-1) touch = true;
	}
	//����!!
	if(touch ==false){
		for(int i=0; i<GRID_WIDTH; i++){
			for(int j=0; j<GRID_HEIGHT; j++){
				ifCube[i][j]=false;
			}
		}
		for(int i1=0; i1<4; i1++){
			for(int j1=0; j1<2; j1++){
				if(j1==0){
					tempi = temp[i1][0];
				}else{
					tempj = temp[i1][1];	
				}
			}
			ifCube[tempi][tempj]=true;
		}
		rotateStatus++;
		if(rotateStatus == 2) rotateStatus=0;
	}
}
//----------------------------------------�C������----------------------------------------
void gameOver()
{
	if (full == false)
	{
		for(int i=0; i<GRID_WIDTH; i++)
		{
			if (GRID[i][3] == true) full = true;
		}	
	}else{
		glColor3f(1.0,0.0,0.0);
		glRecti(20 , 600 , 280 , 0 );
	}
}

void myInit(void)
{
	glClearColor(0.0,0.0,0.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,300.0,0.0,600.0);
	
	for (int i=0; i<GRID_WIDTH; i++)
	{
		for(int j=0; j<GRID_HEIGHT; j++)
			GRID[i][j] = false;
	} //��l�Ʈ��I���e

	srand((unsigned)time(NULL));
}



void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	GRIDsystem();
	gameOver();
	glutSwapBuffers();
}
void myTimer(int);
void mySpecialKey(int key, int x, int y)
{
	switch (key){

	case GLUT_KEY_UP:
		rotateSystem();
		break;
	case GLUT_KEY_DOWN:
		hitTest();
		if (ifCube[3][0] == false) moveDown();
		break;
	case GLUT_KEY_LEFT:
		moveLeft();
		break;
	case GLUT_KEY_RIGHT:
		moveRight();
		break;
	}
	glutPostRedisplay();
}

void myTimer(int NewBlock)
{
	hitTest();
	if (NewBlock == 1)
	{
		GRIDsystem();
		glutTimerFunc(TimeInterval,myTimer,0);
	}else{
		printf("move\n");
		if (!ifTouch)
		{
			for (int i=0; i<GRID_WIDTH; i++){
				for (int j=GRID_HEIGHT-1; j>0; j--){
					ifCube[i][j] = ifCube[i][j-1];
					ifCube[i][j-1] = false;
				}
			}
		}
		glutTimerFunc(TimeInterval,myTimer,1);
	}
	glutPostRedisplay();
}


void myReshape(int width, int height)
{
	if ((GLfloat)height * Aspect > width)
		glViewport(0,0,width,(GLfloat)width/Aspect);
	else
		glViewport(0,0,(GLfloat)height*Aspect,height);
}

void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(300,600);
	glutInitWindowPosition(100,150);
	glutCreateWindow("952017");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutSpecialFunc(mySpecialKey);
	glutTimerFunc(TimeInterval,myTimer,1);
	myInit();
	
	glutMainLoop();
}