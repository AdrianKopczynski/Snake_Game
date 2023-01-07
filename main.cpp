/*
�W�� powinien by� reprezentowany przez po��czone znaki hasztagu (#), a jego g�owa powinna by� oznaczona znakiem ma�py (@)
�W�� zawsze zaczyna gr� od �rodka planszy, w kierunku g�rnej kraw�dzi planszy, z d�ugo�ci� 3 segment�w (g�owa + 2 segmenty ogona)
�Sterowanie w�em powinno nast�powa� klawiszami strza�ek
�Na jednym z segment�w planszy powinna pojawia� si� porcja jedzenia. Po ka�dorazowym spo�yciu porcji przez w�a w losowej kom�rce, kt�ra nie jest zaj�ta przez �aden z segment�w w�a.
�Po ka�dym zjedzeniu porcji po�ywienia, w�� powinien si� wyd�u�a� o 1 segment.
�Pr�ba wyj�cia w�a poza plansz� lub najechanie w�a na sw�j ogon powinno ko�czy� gr� z komunikatem wskazuj�cym, ile punkt�w uda�o si� zdoby� graczowi. Jedna zjedzona porcja po�ywienia = jeden zdobyty punkt.
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <unistd.h>

using namespace std;

/*
	//zapis najwyzszego uzyskanego wyniku w pliku hScore.txt
	ofstream hScoreSave("hScore.txt"); 
	hScoreSave << hScore; 
	hScoreSave.close();*/

const int defSnakeLength = 2; // Ustanowienie domy�lnej d�ugo�ci cia�a w�a jako 2 wg specyfikacji zadania
string hScore,head,body,blank,mapBorder;
int difficulty,sizeOfMap,size,buttonPressed,snakeBodyLength,direction,tableRows,tableColumn,headCordinates,gameSpeed,tempX,tempY;
bool lose=false;
vector <int> headCords(2);
vector <int> bodyX(2);
vector <int> bodyY(2);
vector <int> bodyTemp(2);
vector <int> blankSpace(2);

void coolPrint(string string,int x){
	//fukncja wypisuje podany string znak po znaku z przerwami podanymi przez uzytkownika 
	int lenght = string.length();
	for(int i = 0;i<lenght;i++){
		cout << string[i];
		Sleep(x);
	}
	cout << endl;
}

void titlePrint(){
	system("cls");
	cout << "------------------------------------------------------------------                             HighScore:" << hScore << endl;
	cout << "    _________    ____     __       ___       __   ___  ________" << endl;
	cout << "   / ________\\  |    \\   |  |     /   \\     |  | /  / |  ______| " << endl;
	cout << "  |  |_______   |     \\  |  |    /  _  \\    |  |/  /  |  |____" << endl;	
	cout << "   \\_______  \\  |  |\\  \\ |  |   /  /_\\  \\   |     /   |  _____|" << endl;
	cout << "    _______|  | |  | \\  \\|  |  /  _____  \\  |  |\\  \\  |  |_____" << endl;	
	cout << "   /_________/  |__|  \\_____| /__/     \\__\\ |__| \\__\\ |________|" << endl << endl;
	cout << "------------------------------------------------------------------" << endl << endl;
}

void hScoreLoad(){
	//odczyt najwyzszego uzyskanego wyniku z pliku hScore.txt
	ifstream hScoreLoad("hScore.txt");
	getline(hScoreLoad, hScore); // pobieramy wartosc najwyzszego wyniku z pliku i przekazujemy te wartosc to zmiennej hScore
	hScoreLoad.close(); 	
}

void welcomeScreen(){
	coolPrint("------------------------------------------------------------------",1);
	coolPrint("    _________    ____     __       ___       __   ___  ________",1);
	coolPrint("   / ________\\  |    \\   |  |     /   \\     |  | /  / |  ______|  ",1);
	coolPrint("  |  |_______   |     \\  |  |    /  _  \\    |  |/  /  |  |____     ",1);
	coolPrint("   \\_______  \\  |  |\\  \\ |  |   /  /_\\  \\   |     /   |  _____|",1);
	coolPrint("    _______|  | |  | \\  \\|  |  /  _____  \\  |  |\\  \\  |  |_____",1);
	coolPrint("   /_________/  |__|  \\_____| /__/     \\__\\ |__| \\__\\ |________|",1);
	cout << endl;
	coolPrint("------------------------------------------------------------------",1);
	cout << endl <<"		    ";
	coolPrint("Press any key to continue",50);
	bool isKeyPressed = false;
	int keyPressed = getch();
	while (isKeyPressed = false)
        {
            	if (keyPressed>-1){
            		isKeyPressed = true;
				}
        }
    system("cls");
    titlePrint();
}

int choice(){
	int done,dif;
	do
	{
    	done = 1;
    	int c =getch(); 
    	switch( c )
    	{
        	case 49: 
        	dif = 1;
        	break;

        	case 50: 
           	dif = 2;
            break;
            
            case 51: 
           	dif = 3;
            break;

        	default: 
            done = 0;
            break;
    	}
	} while ( !done );
	return dif;
}

void menu(){
	coolPrint("Selcet a difficulty level.",10);
	coolPrint("1. Easy", 10);
	coolPrint("2. Normal", 10);
	coolPrint("3. Hard", 10);
    difficulty = choice(); // czekamy az uzytkownik wybierze poziom trudnosci, 49-"1" 50-"2" 51-"3"
    titlePrint();
    string selectedDif;
    if(difficulty == 1){
    	selectedDif = "Selcected difficulty is: Easy.";
	}
	else if (difficulty == 2){
		selectedDif = "Selcected difficulty is: Normal.";
	}
	else {
		selectedDif = "Selcected difficulty is: Hard.";
	}
	coolPrint (selectedDif, 10);
    coolPrint("Select board size :",10);
    coolPrint("1. Small", 10);
	coolPrint("2. Normal", 10);
	coolPrint("3. XXL", 10);
	sizeOfMap = choice(); // czekamy az uzytkownik wybierze poziom trudnosci, 49-"1" 50-"2" 51-"3"
    titlePrint();
    string selectedSize;
    if(sizeOfMap == 1){
    	selectedSize = "Selcected size is: Small.";
	}
	else if (sizeOfMap == 2){
		selectedSize = "Selcected size is: Normal.";
	}
	else {
		selectedSize = "Selcected size is: XXL.";
	}
	coolPrint (selectedDif, 10);
	coolPrint (selectedSize, 10);
	coolPrint ("Game Starts in ",10);
	//coolPrint ("3...2...1...0",500);
}

int declareSize(int size){
	int sizeOf;
	if(size ==1){
		sizeOf = 9;
	}
	else if (size ==2){
		sizeOf = 17;
	}
	else {
		sizeOf = 27;
	}
	return sizeOf;
}

void buttonPress(){
	if (kbhit()){
		buttonPressed = getch();// lewo=75, prawo=77, d�=80, g�ra=72
		if(buttonPressed == 72 && direction != 2){
				direction = 0;
		}
		else if(buttonPressed == 77 && direction != 3){
			direction = 1;
		}
		else if(buttonPressed == 80 && direction != 0){
			direction = 2;
		}
		else if(buttonPressed == 75 && direction != 1){
			direction = 3;
		}
		else{
			direction = direction;
		}
	}
}

int main(){
	hScoreLoad();
	head = "@ ";
	body = "# ";
	blank = "  ";
	mapBorder = "X ";
	Sleep(100);
	//welcomeScreen();
	menu();
	system("cls");
	size = declareSize(sizeOfMap);
	string map[size][size];
	snakeBodyLength = 2;//na starcie cia�o w�a ma d�ugo�� 2
	direction = 0; // 0 = g�ra, 1=prawo, 2=d�, 3=lewo
	for(int i=0;i<size;i++){
		map[i][0] = mapBorder;
		map[i][size-1] = mapBorder;
		map[0][i] = mapBorder;
		map[size-1][i] = mapBorder;
		if(i != 0 && i<(size-1) ){
			for(int j=1;j<size-1;j++){
				map[i][j] = blank;
			}
		}
	}
	headCordinates = (size-1)/2;
	map[headCordinates][headCordinates] = head;
	map[headCordinates+1][headCordinates] = body;
	map[headCordinates+2][headCordinates] = body;
	system("cls");
	headCords[0]=headCordinates;
	headCords[1]=headCordinates;
	bodyX[0]=headCordinates;
	bodyX[1]=headCordinates;
	bodyY[0]=headCordinates+1;
	bodyY[1]=headCordinates+2;
	blankSpace[0]=headCordinates;
	blankSpace[1]=headCordinates+3;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<map[i][j];
			usleep(10000);
		}
	cout << endl;
	}
	if(difficulty==1){
		gameSpeed =200;
	}
	else if(difficulty==2){
		gameSpeed =100;
	}
	else if(difficulty==3){
		gameSpeed =50;
	}
	Sleep(1000);
	do{
		buttonPress();
		system("cls");
		//blank[0] = bodyX[snakeBodyLength-1];
		//blank[1] = bodyY[snakeBodyLength-1];
		tempX = bodyX[0];
		tempY = bodyY[0];
		bodyX[0] = headCords[1];
		bodyY[0] = headCords[0];	
		for(int i = 1; i==snakeBodyLength;i++){
			bodyTemp[0] = bodyY[i];
			bodyTemp[1] = bodyX[i];
			bodyX[i] = tempX;
			bodyY[i] = tempY;
			tempX = bodyTemp[1];
			tempY = bodyTemp[0];	
		}
		blankSpace[0] = tempY;
		blankSpace[1] = tempX;
		if(direction == 0){
			headCords[0] -= 1;
		}
		else if(direction == 1){
			headCords[1] += 1;
		}
		else if(direction == 2){
			headCords[0] += 1;
		}
		else if(direction == 3){
			headCords[1] -= 1;
		}
		map[headCords[0]][headCords[1]] = head;
		for(int i =0;i<snakeBodyLength;i++){
			map[bodyY[i]][bodyX[i]] = body;
		}
		map[blankSpace[0]][blankSpace[1]] = blank;
		
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				cout<<map[i][j];
			}
		cout << endl;
		}
		Sleep(gameSpeed);
		buttonPress();
		if(headCords[0]+1 == 26||headCords[1]+1==26||headCords[0]-1==0 || headCords[1]-1==0){
			lose = true;
		}
	}while(lose==false);
	
	return 0;
}
