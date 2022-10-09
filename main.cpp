#include <iostream>

using namespace std;

int main() {
	// Выставить в консоли кодировку ascii 1251, тк стандартный ascii не работает с русскими символами.
	setlocale(LC_ALL, "Russian");
	system("chcp 1251");

	// Максимальная память для выделения под слово, тк самое большое русское слово содержит 35 символов:
	// превысокомногорассмотрительствующий
	const unsigned int maxWordLength = 35;
	char* currentWord = new char[maxWordLength];
	char* maxWord = new char[maxWordLength];
	unsigned int currentVowels = 0, maxVowels = 0, i = 0, maxSize = 0;
	char ch;

	// Проверяем, не явсляется ли введённый символ переносом строки, считывеаем символы
	while ((ch = getchar()) != '\n') {
		// если символ пробел - смотрим: нужно ли записать новое слово, в котором больше гласных, и обнуляем
		// все переменные - не к чему хранить лишние слова
		if (ch == ' ') {
			if (currentVowels > maxVowels) {
				maxVowels = currentVowels;

				delete[] maxWord;
				maxWord = new char[maxWordLength];
				maxSize = i;

				for (int j = 0; j < i; j++) {
					maxWord[j] = currentWord[j];
				}
			}

			delete[] currentWord;
			currentWord = new char[maxWordLength];

			i = 0;
			currentVowels = 0;
		}
		// Если пробел пока не встретился - работаем в рамках одного слова и подсчитываем его гласные
		else {
			if (ch == 'а' || ch == 'е' || ch == 'и') {
				currentVowels++;
			}

			currentWord[i] = ch;
			i++;
		}
	}

	// Немного костыль, но while не обработает последнее слово, тк перенос строки закончит его выполнение.
	// для этого здесь копипаста условного оператора из цикла
	if (currentVowels > maxVowels) {
		maxVowels = currentVowels;

		delete[] maxWord;
		maxWord = new char[maxWordLength];
		maxSize = i;

		for (int j = 0; j < i; j++) {
			maxWord[j] = currentWord[j];
		}
	}

	if (maxVowels == 0) {
		cout << "В тексте нет слов содержащих гласные 'a' 'е' 'и'";
	}
	else {
		for (int j = 0; j < maxSize; j++) {
			cout << maxWord[j];
		}
	}

	// очищаем память
	delete[] maxWord;
	delete[] currentWord;

	return 0;
}
