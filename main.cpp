/*
•W¹¿ powinien byæ reprezentowany przez po³¹czone znaki hasztagu (#), a jego g³owa powinna byæ oznaczona znakiem ma³py (@)
•W¹¿ zawsze zaczyna grê od œrodka planszy, w kierunku górnej krawêdzi planszy, z d³ugoœci¹ 3 segmentów (g³owa + 2 segmenty ogona)
•Sterowanie wê¿em powinno nastêpowaæ klawiszami strza³ek
•Na jednym z segmentów planszy powinna pojawiaæ siê porcja jedzenia. Po ka¿dorazowym spo¿yciu porcji przez wê¿a w losowej komórce, która nie jest zajêta przez ¿aden z segmentów wê¿a.
•Po ka¿dym zjedzeniu porcji po¿ywienia, w¹¿ powinien siê wyd³u¿aæ o 1 segment.
•Próba wyjœcia wê¿a poza planszê lub najechanie wê¿a na swój ogon powinno koñczyæ grê z komunikatem wskazuj¹cym, ile punktów uda³o siê zdobyæ graczowi. Jedna zjedzona porcja po¿ywienia = jeden zdobyty punkt.
*/

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>

using namespace std;

/*
	//zapis najwyzszego uzyskanego wyniku w pliku hScore.txt
	ofstream hScoreSave("hScore.txt"); 
	hScoreSave << hScore; 
	hScoreSave.close();*/

const int defSnakeLength = 2; // Ustanowienie domyœlnej d³ugoœci cia³a wê¿a jako 2 wg specyfikacji zadania
string hScore;
int difficulty;
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
	cout << "------------------------------------------------------------------" << endl;
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
	coolPrint("------------------------------------------------------------------",10);
	coolPrint("    _________    ____     __       ___       __   ___  ________",10);
	coolPrint("   / ________\\  |    \\   |  |     /   \\     |  | /  / |  ______| ",10);
	coolPrint("  |  |_______   |     \\  |  |    /  _  \\    |  |/  /  |  |____",10);
	coolPrint("   \\_______  \\  |  |\\  \\ |  |   /  /_\\  \\   |     /   |  _____|",10);
	coolPrint("    _______|  | |  | \\  \\|  |  /  _____  \\  |  |\\  \\  |  |_____",10);
	coolPrint("   /_________/  |__|  \\_____| /__/     \\__\\ |__| \\__\\ |________|",10);
	cout << endl;
	coolPrint("------------------------------------------------------------------",10);
	cout << endl <<"			    ";
	coolPrint("Press any key",50);
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
    system("cls");
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
}
int main(){
	Sleep(100);
	welcomeScreen();
	menu();
	return 0;
}
