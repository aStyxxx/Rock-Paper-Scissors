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
void raund(int playerChoice, int computerChoice, int difficulty, int& score, int& streak, int& highScore, bool& hasShield, bool& hasBooster, int &highestStreak)
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

		if (streak > highestStreak)
			highestStreak = streak;

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
		cout << "     Desc: Reach 100 points." << endl;
	}
	else
	{
		cout << " [ ] MONSTER (Locked)" << endl;
		cout << "     Need " << (100 - score) << " more points." << endl;
	}
	cout << "==========================================" << endl;
}

void shopMenu(int& score, bool& hasShield, bool& hasBooster, bool &hasGodMode, bool &hasSuperHit) {
	while (true) { // loop to allow multiple purchases
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
		SetColor(11); cout << " 1. SHIELD"; 
		SetColor(7);
		cout << "        (Cost: 5)" << endl;
		cout << "    Protects from one losing round." << endl;

		if (hasShield) { SetColor(10); cout << "    STATUS: ACTIVE" << endl; SetColor(7); }
		else { SetColor(8); cout << "    STATUS: Not owned" << endl; SetColor(7); }

		cout << "--------------------------" << endl;

		// PRODUCT 2: BOOSTER X2
		SetColor(11);
		cout << " 2. X2 BOOSTER";
		SetColor(7);
		cout << "     (Cost: 10)" << endl;
		cout << "    Doubles points for next win." << endl;

		if (hasBooster) { SetColor(10); cout << "    STATUS: ACTIVE" << endl; SetColor(7); }
		else { SetColor(8); cout << "    STATUS: Not owned" << endl; SetColor(7); }

		cout << "--------------------------" << endl;

		// PRODUCT 3: MYSTERY BOX
		SetColor(11);
		cout << " 3. MYSTERY BOX";
		SetColor(7);
		cout << "   (Cost: 3)" << endl;
		SetColor(13); 
		cout << "    Try your luck! Possible rewards: +10 pts, Shield, SUPER HIT (5%), GOD MODE (5%), nothing or trap." << endl;
		SetColor(7);
		cout << "--------------------------" << endl;

		// PRODUCT 4: GOD MODE
		SetColor(12);
		cout << " 4. GOD MODE";
		SetColor(7); 
		cout << "     (Cost: 100)" << endl;
		cout << "    Grants +10 HP for next boss fight (useable any time during boss fight)." << endl;

		if (hasGodMode) { SetColor(10); cout << "    STATUS: OWNED (one-time use)" << endl; SetColor(7); }
		else { SetColor(8); cout << "    STATUS: Not owned" << endl; SetColor(7); }

		cout << "--------------------------" << endl;

		// PRODUCT 5: SUPER HIT
		SetColor(14);
		cout << " 5. SUPER HIT"; SetColor(7);
		cout << "    (Cost: 150)" << endl;
		cout << "    Instantly reduce boss HP by 50% when used during boss fight." << endl;

		if (hasSuperHit) { SetColor(10); cout << "    STATUS: OWNED (one-time use)" << endl; SetColor(7); }
		else { SetColor(8); cout << "    STATUS: Not owned" << endl; SetColor(7); }

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
				else if (luck < 25) { // 5% - SUPER HIT
					SetColor(13);
					cout << ">>> You found a SUPER HIT! (one-time) <<<" << endl;
					hasSuperHit = true;
				}
				else if (luck < 30) { // 5% - GOD MODE
					SetColor(12);
					cout << ">>> You found GOD MODE! (one-time) <<<" << endl;
					hasGodMode = true;
				}
				else if (luck < 50) { // 20% chance - Shield
					SetColor(11);
					cout << ">>> You found a SHIELD! <<<" << endl;
					hasShield = true;
				}
				else if (luck < 80) { // 30% chance - Nothing
					SetColor(8);
					cout << ">>> Empty... Just dust inside. <<<" << endl;
				}
				else { // 20% chance - Bad luck 
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
		// GOD MODE
		else if (choice == 4) 
		{
			if (hasGodMode) cout << "\n> YOU ALREADY OWN GOD MODE!" << endl;
			else if (score >= 100) 
			{
				score -= 100;
				hasGodMode = true;
				Beep(500, 100); Beep(1000, 100); Beep(1500, 300); 
				SetColor(12);
				cout << "\n>>> GOD MODE PURCHASED! Use it during boss fight to gain +10 HP. <<<" << endl;
				SetColor(7);
			}
			else 
			{
				cout << "\n> Not enough points! (Need 100)" << endl;
			}
		}
		// SUPER HIT
		else if (choice == 5)
		{
			if (hasSuperHit) cout << "\n> You already own SUPER HIT!" << endl;
			else if (score >= 150)
			{
				score -= 150;
				hasSuperHit = true;
				Beep(1400, 150);
				SetColor(14);
				cout << "\n> SUPER HIT PURCHASED! Use during boss fight to cut boss HP by 50%." << endl;
				SetColor(7);
			}
			else cout << "\n> Not enough points!" << endl;
		}
		else {
			cout << "\n> Invalid choice, try again." << endl;
		}

		system("pause"); 
	}
}

//Boss
void drawHP(int current, int max, int color)
{
	SetColor(color);

	cout << "  [ ";
	for (int i = 0; i < max; i++)
	{
		if (i < current)
			cout << (char)3;
		else
			cout << " ";
	}
	cout << " ] " << current << "/" << max << endl;
}

void bossBattle(int& score, bool& hasShield, bool& hasBooster, bool &hasGodMode, bool &hasSuperHit, int difficulty)
{
	system("cls");

	//Fight Settings
	int playerHP = 3;
	int maxPlayerHP = 3;
	int bossHP;
	int roundCount = 1;

	if (difficulty == 1) bossHP = 5;
	else if (difficulty == 2) bossHP = 10;

	SetColor(12);
	cout << "\n =============================================" << endl;
	cout << "   OHHH YOU WOKE UP THE BOSS. GOOD LUCK!" << endl;
	cout << " ============================================= \n" << endl;
	Beep(200, 300); Beep(150, 400); Beep(200, 300); Beep(150, 400);
	SetColor(7);
	system("pause");

	//Main Fight Logic 
	while (bossHP > 0 && playerHP > 0)
	{
		system("pause");

		// Allow player to use items at any moment before making a move
		if (hasSuperHit || hasGodMode)
		{
			SetColor(13);
			cout << "\nYou can use an item now: ";
			int opt = 0;
			cout << "(0 - No";
			if (hasSuperHit) cout << ", 1 - SUPER HIT";
			if (hasGodMode) cout << ", 2 - GOD MODE";
			cout << "): ";
			SetColor(7);
			cin >> opt;

			if (opt == 1 && hasSuperHit)
			{
				int reduced = bossHP / 2;
				bossHP -= reduced;
				if (bossHP < 1) bossHP = 1;
				hasSuperHit = false;
				SetColor(14);
				cout << "\n>>> SUPER HIT used! Boss lost " << reduced << " HP! <<<" << endl;
				SetColor(7);
				Beep(1200, 200);
				Sleep(800);
			}
			else if (opt == 2 && hasGodMode)
			{
				playerHP += 10;
				maxPlayerHP += 10;
				hasGodMode = false;
				SetColor(14);
				cout << "\n>>> GOD MODE activated! You gained +10 HP! <<<" << endl;
				SetColor(7);
				Beep(1000, 200);
				Sleep(800);
			}
		}

		if (bossHP <= 0) break;

		if (difficulty == 1) { SetColor(12); cout << " BOSS HP:   "; drawHP(bossHP, 5, 12); }
		else if (difficulty == 2) { SetColor(12); cout << " BOSS HP:   "; drawHP(bossHP, 10, 12); }

		SetColor(10); cout << " YOUR HP:   "; drawHP(playerHP, maxPlayerHP, 10); SetColor(7);
		
		cout << "_____________________________________________" << endl;
		cout << " ROUND" << roundCount << endl;

		if (hasBooster) { SetColor(13); cout << " (Status: X2 DAMAGE READY)" << endl; SetColor(7); }
		if (hasShield) { SetColor(11); cout << " (Status: SHIELD ACTIVE)" << endl; SetColor(7); }

		//Fight
		int playerCoice;
		cout << " \n 1-Rock, 2-Paper, 3-Scissors: ";
		cin >> playerCoice;

		if (playerCoice < 1 || playerCoice > 3) continue;

		int computerCoice = rand() % 3 + 1;


		//Drawing Hands
		SetColor(11);
		cout << " \n YOU: \n"; SetColor(7); drawHand(playerCoice); cout << endl;
		SetColor(7);
		cout << " VS \n" << endl;
		SetColor(12);
		cout << " BOSS: \n"; SetColor(7); drawHand(computerCoice); cout << endl;

		//Game Logic
		if (playerCoice == computerCoice) 
		{
			SetColor(14); cout << "\n >>> BLOCKED! NO DAMAGE! <<<" << endl; SetColor(7);
			Beep(500, 100);
		}
		else if ((computerCoice == 1 && playerCoice == 3) ||
				 (computerCoice == 2 && playerCoice == 1) ||
				 (computerCoice == 3 && playerCoice == 2)   )
		{
			cout << "\n"; SetColor(12); cout << " >>> BOSS HITS YOU! (-1 HP) <<<" << endl; SetColor(7);

			if (hasShield) 
			{
				SetColor(11); cout << " [SHIELD BLOCKED THE ATTACK!]" << endl; SetColor(7);
				hasShield = false; 
				Beep(1000, 200);
			}
			else
			{
				playerHP--; // reduce player HP if no shield
			}
		}
		else 
		{
			cout << "\n"; SetColor(10); cout << " >>> YOU HIT THE BOSS! <<<" << endl; SetColor(7);

			int damage = 1;
			if (hasBooster) 
			{
				SetColor(13); cout << " [CRITICAL HIT! X2 DAMAGE!]" << endl; SetColor(7);
				damage = 2;
				hasBooster = false; // booster consumed
			}

			bossHP -= damage;
			Beep(1000, 100); Beep(1200, 100);
		}

		roundCount++;
		Sleep(1500); // Pause to see result
	}
	
	//Fight Final
	system("cls");

	if (playerHP > 0) //win
	{
		int reward = (difficulty == 2) ? 500 : 50;

		SetColor(10);
		cout << "\n####################################" << endl;
		cout << "#         BOSS DEFEATED!           #" << endl;
		cout << "#     REWARD: +" << reward << " SCORE POINTS     #" << endl;
		cout << "####################################\n" << endl;
		score += reward;
		Beep(500, 100); Beep(700, 100); Beep(900, 100); Beep(1200, 500); 
		SetColor(7);
	}
	else
	{
		SetColor(12);
		cout << "\n####################################" << endl;
		cout << "#           YOU DIED...            #" << endl;
		cout << "#        GAME OVER (BOSS)          #" << endl;
		cout << "####################################\n" << endl;
		score = score / 2;
		Beep(200, 1000);
		SetColor(7);
	}
	system("pause");
}

int main()
{
	bool end = false;
	bool hasShield = false;
	bool hasBooster = false;
	bool hasGodMode = false;
	bool hasSuperHit = false;

	srand((unsigned int)time(0)); // using for rand

	int playerChoice = -1;
	int computerChoice;
	int score = 0;
	int difficulty;
	int streak = 0;
	int highScore = 0;
	int highestStreak = 0;


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
		cout << " SCORE: " << score << " | HIGH: " << highScore << " | STREAK: " << streak << " | HIGHEST STREAK: " << highestStreak;
		if (hasShield)
			cout << " | [SHIELD]";
		else
			cout << " ";
		if (hasBooster)
			cout << " | [X2 BOOST]";
		else
			cout << "  ";
		if (hasSuperHit)
			cout << " | [SUPER HIT]";
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
		cout << "  |     6 - FIGHT BOSS    |" << endl;
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
			shopMenu(score, hasShield, hasBooster, hasGodMode, hasSuperHit);
			system("pause");
			continue; 
		}

		//Boss Fight
		if (playerChoice == 6) 
		{
			bossBattle(score, hasShield, hasBooster, hasGodMode, hasSuperHit, difficulty);
			continue; 
		}

		//Test for invalid input
		if (playerChoice < 0 || playerChoice > 6)
		{
			cout << "- - - - - - - - - - - - - - - - - - - - - \n" << endl;
			cout << "          Incorrect input!\n" << endl;
			cout << "- - - - - - - - - - - - - - - - - - - - - \n" << endl;
			system("pause");
			continue;
		}


		computerChoice = rand() % 3 + 1; // rand() % 3 -> (0,1,2) then +1

		raund(playerChoice, computerChoice, difficulty, score, streak, highScore, hasShield, hasBooster, highestStreak);

		achievements(score);

		system("pause");

	} while (!end);

	cout << "- - - - - - - - - - - - - - - - - - \n" << endl;
	cout << "        THX For Game! GL \n" << endl;
	cout << "- - - - - - - - - - - - - - - - - - \n" << endl;

	return 0;
}




//Final version of the game. Nothing more will be added/