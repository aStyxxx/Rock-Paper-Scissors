#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

//Adding Color
void SetColor(int color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void drawHand(int choice) 
{
	if (choice == 1) // Rock
	{ 
		cout << "    _______" << endl;
		cout << "---'   ____)" << endl;
		cout << "      (_____)" << endl;
		cout << "      (_____)" << endl;
		cout << "      (____)" << endl;
		cout << "---.__(___)" << endl;
		cout << "  [ ROCK ]  " << endl;
	}
	else if (choice == 2) // Paper
	{ 
		cout << "     _______" << endl;
		cout << "---'    ____)____" << endl;
		cout << "           ______)" << endl;
		cout << "          _______)" << endl;
		cout << "         _______)" << endl;
		cout << "---.__________) " << endl;
		cout << "  [ PAPER ]  " << endl;
	}
	else if (choice == 3) // Scissors
	{ 
		cout << "    _______" << endl;
		cout << "---'   ____)____" << endl;
		cout << "          ______)" << endl;
		cout << "       __________)" << endl;
		cout << "      (____)" << endl;
		cout << "---.__(___)" << endl;
		cout << " [ SCISSORS ] " << endl;
	}
}

//Game Logic
void raund(int playerChoice, int computerChoice, int difficulty, int& score, int& streak, int& highScore, bool& hasShield, bool& hasBooster)
{
	//Color the pictures

	SetColor(11); // Blue color
	cout << "\n-----------------------------------" << endl;
	cout << "YOU CHOSE:" << endl;
	SetColor(7); // White for drawing
	drawHand(playerChoice);

	// Showing active bonuses
	if (hasShield) {
		SetColor(14); // Yellow for the shield
		cout << " [SHIELD ACTIVE] ";
		SetColor(7);
	}
	if (hasBooster) {
		SetColor(13); // Pink/Purple for booster
		cout << " [X2 BOOSTER ACTIVE] ";
		SetColor(7);
	}
	cout << endl; 

	SetColor(11); 
	cout << "\nVS\n" << endl;
	cout << "COMPUTER CHOSE:" << endl;
	SetColor(7); 
	drawHand(computerChoice);

	SetColor(11); 
	cout << "-----------------------------------\n" << endl;
	SetColor(7); 

	// Game Logic

	// 1 DRAW 
	if (computerChoice == playerChoice)
	{
		SetColor(14); 
		cout << "                DRAW! " << endl;
		SetColor(7);  
		cout << "- - - - - - - - - - - - - - - - - - - - - \n" << endl;
	}
	// 2 LOSE 
	else if ((computerChoice == 1 && playerChoice == 3) ||
		(computerChoice == 2 && playerChoice == 1) ||
		(computerChoice == 3 && playerChoice == 2))
	{
		SetColor(12); // Red 
		cout << "               YOU LOSE! " << endl;

		// Shield Check
		if (hasShield) {
			SetColor(11); 
			cout << "   [SHIELD ACTIVATED! NO PENALTY] " << endl;
			hasShield = false; 
		}
		else {
			// If there is no shield
			streak = 0;
			cout << "            Streak lost..." << endl;

			// Hard Mode
			if (difficulty == 2)
			{
				if (score > 0)
				{
					score--;
					cout << "          Penalty: -1 Score" << endl;
				}
				else
				{
					cout << "    Score is 0, nothing to lose." << endl;
				}
			}
		}
		SetColor(7); 
		cout << "- - - - - - - - - - - - - - - - - - - - - \n" << endl;

		Beep(300, 500); // Low "Bruuuum" sound
	}
	// WIN
	else
	{
		SetColor(10); // Green
		cout << "                YOU WIN! " << endl;
		streak++;

		int pointsEarned = 1; 

		// Combo Logic
		if (streak >= 3) {
			SetColor(14); // Gold for super bonus
			cout << "       COMBO X2! Super Points!        " << endl;
			SetColor(10); 
			pointsEarned = 2; 
		}
		else {
			cout << "               +1 Score!" << endl;
		}

		//Logic X2 Booster
		if (hasBooster) {
			SetColor(13); // Pink
			cout << "     [X2 BOOSTER APPLIED!]      " << endl;
			pointsEarned *= 2; 
			hasBooster = false; 
			SetColor(10);
		}

		score += pointsEarned;
		cout << "      Total gained: +" << pointsEarned << " pts" << endl;


		// High Score
		if (score > highScore) {
			highScore = score;
			SetColor(14); 
			cout << "           NEW HIGH SCORE!" << endl;
			SetColor(10); 
		}

		SetColor(7); 
		cout << "- - - - - - - - - - - - - - - - - - - - - \n" << endl;

		Beep(750, 300); // 750 Hz, 300 milliseconds
		Beep(1000, 300); // Even higher
	}
}

//Achievements
void achievements(int score)
{
	if (score == 10)
	{
		cout << "\n ########################################" << endl;
		cout << " #    ACHIEVEMENT UNLOCKED: BEGINNER!   #" << endl;
		cout << " #       You reached 10 points!         #" << endl;
		cout << " ######################################## \n" << endl;
	}
	if (score == 20)
	{
		cout << "\n ########################################" << endl;
		cout << " #     ACHIEVEMENT UNLOCKED: MASTER!    #" << endl;
		cout << " #       You reached 20 points!         #" << endl;
		cout << " ######################################## \n" << endl;
	}
	if (score == 50)
	{
		cout << "\n ########################################" << endl;
		cout << " #     ACHIEVEMENT UNLOCKED: LEGEND!    #" << endl;
		cout << " #       You reached 50 points!         #" << endl;
		cout << " ######################################## \n" << endl;
	}
	if (score == 100)
	{
		cout << "\n ########################################" << endl;
		cout << " #     ACHIEVEMENT UNLOCKED: MONSTER!   #" << endl;
		cout << " #       You reached 100 points!        #" << endl;
		cout << " ######################################## \n" << endl;
	}
}

void showAchievementsMenu(int score) {
	system("cls");

	cout << " ==========================================" << endl;
	cout << "           YOUR ACHIEVEMENTS              " << endl;
	cout << " ==========================================" << endl;
	cout << "   Current Score: " << score << "\n" << endl;

	if (score >= 10) {
		cout << " [X] BEGINNER (Unlocked!)" << endl;
		cout << "     Desc: Reach 10 points." << endl;
	}
	else {
		cout << " [ ] BEGINNER (Locked)" << endl;
		cout << "     Need " << (10 - score) << " more points." << endl;
	}
	cout << "------------------------------------------" << endl;

	if (score >= 20) {
		cout << " [X] MASTER (Unlocked!)" << endl;
		cout << "     Desc: Reach 20 points." << endl;
	}
	else {
		cout << " [ ] MASTER (Locked)" << endl;
		cout << "     Need " << (20 - score) << " more points." << endl;
	}
	cout << "------------------------------------------" << endl;

	if (score >= 50) {
		cout << " [X] LEGEND (Unlocked!)" << endl;
		cout << "     Desc: Reach 50 points." << endl;
	}
	else {
		cout << " [ ] LEGEND (Locked)" << endl;
		cout << "     Need " << (50 - score) << " more points." << endl;
	}
	cout << "------------------------------------------" << endl;

	if (score >= 100)
	{
		cout << " [X] MONSTER (Unlocked!)" << endl;
		cout << "     Desc: Reach 50 points." << endl;
	}
	else
	{
		cout << " [ ] MONSTER (Locked)" << endl;
		cout << "     Need " << (100 - score) << " more points." << endl;
	}
	cout << "==========================================" << endl;
}

void shopMenu(int& score, bool& hasShield, bool& hasBooster) {
	while (true) { // make a loop so that we can buy several things
		system("cls");
		SetColor(14); 
		cout << "========== SHOP ==========" << endl;
		SetColor(7);
		cout << " You have: ";
		SetColor(10); 
		cout << score << " points" << endl;
		SetColor(7);
		cout << "--------------------------" << endl;

		// PRODUCT 1: SHIELD
		cout << " 1. SHIELD (Cost: 5)" << endl;
		cout << "    [Protects from 1 loss]" << endl;
		if (hasShield) { SetColor(10); cout << "    STATUS: ACTIVE" << endl; SetColor(7); }
		else { SetColor(8); cout << "    STATUS: Not owned" << endl; SetColor(7); }

		cout << "--------------------------" << endl;

		// PRODUCT 2: BOOSTER X2
		cout << " 2. X2 BOOSTER (Cost: 10)" << endl;
		cout << "    [Doubles points for NEXT win]" << endl;
		if (hasBooster) { SetColor(10); cout << "    STATUS: ACTIVE" << endl; SetColor(7); }
		else { SetColor(8); cout << "    STATUS: Not owned" << endl; SetColor(7); }

		cout << "--------------------------" << endl;

		// PRODUCT 3: MYSTERY BOXING
		cout << " 3. MYSTERY BOX (Cost: 3)" << endl;
		SetColor(13); 
		cout << "    [Try your luck! ?????]" << endl;
		SetColor(7);

		cout << "==========================" << endl;
		cout << " 0. Exit Shop" << endl;
		cout << " Choice: ";

		int choice;
		cin >> choice;

		if (choice == 0) break; 

		// BUYING A SHIELD
		if (choice == 1) {
			if (hasShield) cout << "\n> You already have a shield!" << endl;
			else if (score >= 5) {
				score -= 5;
				hasShield = true;
				Beep(1000, 100); 
				cout << "\n> SHIELD PURCHASED!" << endl;
			}
			else cout << "\n> Not enough points!" << endl;
		}
		// PURCHASE OF BOOSTER X2
		else if (choice == 2) {
			if (hasBooster) cout << "\n> You already have a booster!" << endl;
			else if (score >= 10) {
				score -= 10;
				hasBooster = true;
				Beep(1200, 100);
				cout << "\n> X2 BOOSTER PURCHASED!" << endl;
			}
			else cout << "\n> Not enough points!" << endl;
		}
		// Mystery box
		else if (choice == 3) {
			if (score >= 3) {
				score -= 3;
				Beep(600, 100); Beep(800, 100); Beep(1000, 100); 

				cout << "\n> Opening box..." << endl;
				Sleep(1000); 

				int luck = rand() % 100; 

				if (luck < 20) { // 20% chance - JACKPOT
					SetColor(14);
					cout << ">>> JACKPOT!!! +10 POINTS! <<<" << endl;
					score += 10;
					Beep(1500, 500);
				}
				else if (luck < 40) { // 20% chance - Shield
					SetColor(11);
					cout << ">>> You found a SHIELD! <<<" << endl;
					hasShield = true;
				}
				else if (luck < 70) { // 30% chance - Nothing
					SetColor(8);
					cout << ">>> Empty... Just dust inside. <<<" << endl;
				}
				else { // 30% chance - Bad luck 
					SetColor(12);
					cout << ">>> TRAP! You lost 2 points! <<<" << endl;
					if (score >= 2) score -= 2;
					else score = 0;
					Beep(200, 500);
				}
				SetColor(7);
			}
			else cout << "\n> Not enough points!" << endl;
		}

		system("pause"); 
	}
}



int main()
{
	bool end = false;
	bool hasShield = false;
	bool hasBooster = false;

	srand((unsigned int)time(0)); // using for rand

	int playerChoice = -1;
	int computerChoice;
	int score = 0;
	int difficulty;
	int streak = 0;
	int highScore = 0;


	//Welcome Menu
	cout << "        Welcome To 'Rock-Papre-Scissors' Game!\n" << endl;
	cout << "  __________________________________________________" << endl;
	cout << "  |  Before Starte Game, Select Difficulty Level:  |" << endl;
	cout << "  |________________________________________________|" << endl;
	cout << "  |        1 - Easy (No penalty for losing)        |" << endl;
	cout << "  |     2 - Hard (You lose points for losing)      |" << endl;
	cout << "  |________________________________________________|" << endl;
	cout << "    Choice: ";
	cin >> difficulty;

	//Difficulty LVL
	if (difficulty != 1 && difficulty != 2)
	{
		cout << "   Invalid choice! Setting to Easy mode by default." << endl;
		difficulty = 1;
	}

	do {

		system("cls");

		cout << "===================================================" << endl;
		cout << " SCORE: " << score << " | HIGH: " << highScore << " | STREAK: " << streak;
		if (hasShield)
			cout << " | [SHIELD]";
		else
			cout << " ";
		if (hasBooster)
			cout << " | [X2 BOOST]";
		else
			cout << "  ";
		cout << "\n===================================================" << endl;

		//menu
		cout << "- - - - - - - - - Rules - - - - - - - - - " << endl;
		cout << "  _________________________" << endl;
		cout << "  |       1 - Rock        |" << endl;
		cout << "  | - - - - - - - - - - - |" << endl;
		cout << "  |       2 - Paper       |" << endl;
		cout << "  | - - - - - - - - - - - |" << endl;
		cout << "  |      3 - Scissors     |" << endl;
		cout << "  | - - - - - - - - - - - |" << endl;
		cout << "  |   4 - ACHIEVEMENTS    |" << endl;
		cout << "  | - - - - - - - - - - - |" << endl;
		cout << "  |       5 - SHOP        |" << endl;
		cout << "  | - - - - - - - - - - - |" << endl;
		cout << "  |        0 - Exit       |" << endl;
		cout << "  |_______________________| \n" << endl;
		cout << "  Enter Your Choice: ";
		cin >> playerChoice;

		//Exit
		if (playerChoice == 0)
		{
			end = true;
			break;
		}
		
		//Achievements 
		if (playerChoice == 4)
		{
			showAchievementsMenu(score);
			system("pause");
			continue;
		}

		//Shop
		if (playerChoice == 5) {
			shopMenu(score, hasShield, hasBooster);
			system("pause");
			continue; 
		}

		//Test for idiot
		if (playerChoice < 0 || playerChoice > 4)
		{
			cout << "- - - - - - - - - - - - - - - - - - - - - \n" << endl; // OR cout << "----------------------------------- \n" << endl;
			cout << "          Incorrect input!\n" << endl;
			cout << "- - - - - - - - - - - - - - - - - - - - - \n" << endl;
			system("pause");
			continue;
		}

		computerChoice = rand() % 3 + 1; // rand() % 3 'its ranodm number (0, 1, 2)' but need 1, 2, 3; then use + 1 

		raund(playerChoice, computerChoice, difficulty, score, streak, highScore, hasShield, hasBooster);

		achievements(score);

		system("pause");

	} while (!end);

	cout << "- - - - - - - - - - - - - - - - - - \n" << endl;
	cout << "        THX For Game! GL \n" << endl;
	cout << "- - - - - - - - - - - - - - - - - - \n" << endl;

	return 0;
}





//Maybe in the future I'll add some boss.
//Maybe he'll be available for purchase in the store or I'll figure out how to do it differently.