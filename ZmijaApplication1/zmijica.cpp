#include<iostream>
#include<conio.h>
bool kraj, smrt;
const int shirina = 20, visina = 20;
int glavaX, votjkaX, glavaY, votjkaY, skor, brzina = 1;
int repX[1000], repY[1000], duzhina, pomX, pomY;
enum ePravac {start=0, gore, dole, levo, desno };
ePravac pravac, poslednjiPravac;
char ponovi;
void namesti() {
	duzhina = 0;
	pomX = 0;
	pomY = 0;
	pravac=start;
	poslednjiPravac = start;
	smrt = false;
	votjkaX = rand() % visina;
	votjkaY = rand() % shirina;
	glavaX = shirina / 2;
	glavaY = visina / 2;
	skor = 0;
}
void ulaz() {
	if(smrt)
		std::cin >> ponovi;
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			pravac = gore;
			break;
		case 's':
			pravac = dole;
			break;
		case 'a':
			pravac = levo;
			break;
		case 'd':
			pravac = desno;
			break;
		case 'x':
			kraj = true;
			break;
		}
	}
}
void logika() {
	if (smrt)
		if ((ponovi == 'r') || (ponovi == 'R') || (ponovi == 'Y') || (ponovi == 'y') || (ponovi == 'D') || (ponovi == 'd'))
			namesti();
		else {
			smrt = false;
			kraj = true;
		}
	pomX = glavaX;
	pomY = glavaY;
	switch (pravac)
	{
	case gore:	
		if (brzina == 7)
		if (poslednjiPravac != dole) {
				glavaY--;
				poslednjiPravac = gore;
			}
		else {
			glavaY++;
			poslednjiPravac = dole;
			}
		break;
	case dole:
		if (brzina == 7)
			if (poslednjiPravac != gore) {
				glavaY++;
				poslednjiPravac = dole;
			}
			else {
				glavaY--;
				poslednjiPravac = gore;
			}
		break;
	case levo:
		if (brzina == 7)
			if (poslednjiPravac != desno) {
				glavaX--;
				poslednjiPravac = levo;
			}
			else {
				glavaX++;
				poslednjiPravac = desno;
			}
		break;
	case desno:
		if (brzina == 7)
			if (poslednjiPravac != levo) {
				glavaX++;
				poslednjiPravac = desno;
			}
			else {
				glavaX--;
				poslednjiPravac = levo;
			}
		break;
	default:
		break;
	}
	if (glavaX == votjkaX && glavaY == votjkaY)
		if (brzina == 7) {
			votjkaX = rand() % shirina;
			votjkaY = rand() % visina;
			duzhina++;
			skor += 10; 
		}
	if (duzhina > 1 && brzina % 7 == 0) {
		int pomX2 = repX[0], pomY2 = repY[0];
		for (int i = 1; i < duzhina; i++) {
			int pomX1 = repX[i];
			int pomY1 = repY[i];
			repX[i] = pomX2;
			repY[i] = pomY2;
			pomX2 = pomX1;
			pomY2 = pomY1;
		}
	}
	if (duzhina > 0 && brzina % 7 == 0) {
		repX[0] = pomX;
		repY[0] = pomY;
	}
	for (int i = 0; i < duzhina; i++)
		if (repX[i] == glavaX && repY[i] == glavaY)
			smrt = true;
	if (glavaX<1 || glavaX>shirina + 1 || glavaY<0 || glavaY>visina - 1)
		smrt = true;
}
void crtaj() {
	system("cls");
	for (int j = 0; j < shirina+2; j++)
		std::cout << "#";
	std::cout << std::endl;
	for (int j = 0; j < visina; j++)
		for (int i = 0; i < shirina+2; i++) {
			if (i == 0)
				std::cout << "#";
			else if (j == glavaY && i == glavaX)
				std::cout << "O";
			else if (j == votjkaY && i == votjkaX)
					std::cout << "x";
			else if (i == shirina+1)
				std::cout << "#" << std::endl;
			else {
				bool rep=false;
				for (int k = 0; k < duzhina; k++)
					if (repY[k] == j && repX[k] == i) {
						std::cout << "o";
						rep = true;
					}
				if (!rep)
				std::cout << " ";
			}
		}
	for (int i = 0; i < shirina + 2; i++)
		std::cout << "#";
	std::cout << std::endl;
	std::cout << "Score: " << skor << " ";
	if (smrt) {
		std::cout << "Retry?: ";
	}
}
int main() {
	namesti();
	while (!kraj) {
		ulaz();
		logika();
		crtaj();
		if (brzina++ == 7)
			brzina = 1;
	}
	return 0;
}