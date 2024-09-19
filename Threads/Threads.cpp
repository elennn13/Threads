#include <iostream>
#include <thread> // подключение библиотеки для создания потоков и управления ими.
#include <chrono> // подключение библиотеки, содержащей в себе комнады для управления временем, в стиле языка с++
#include <conio.h> // БИБЛИОТЕКА ЯЗЫКА С ДЛЯ УДОБНОГО ВЗАИМОДЕЙСТВИЯ С КОНСОЛЬЮ
#include <string>
#include <Windows.h>
void doSomething() { // функция для обработки сложных данных
	for (rsize_t i = 0; i < 10; ++i) {
		std::cout << "Thread №" << std::this_thread::get_id() <<
			"\tdoSomething()\t" << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void calculate(double num1, double num2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	std::cout << "Thread №" << std::this_thread::get_id() <<
		"\tSTART CALCULATE============\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	std::cout << "Thread №" << std::this_thread::get_id() <<
		'\t' << num1 << "+" << num2 << "=" << num1 + num2 << std::endl;

	std::this_thread::sleep_for(std::chrono::milliseconds(1500));

	std::cout << "Thread №" << std::this_thread::get_id() <<
		"\tEND CALCULATE==============\n";
}

void calculateTo(double& result, double num1, double num2) {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::cout << "Thread №" << std::this_thread::get_id() <<
		"\tSTART CALCULATE TO REF============\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(3000));

	// возврат значения
	result = num1 + num2;



	std::cout << "Thread №" << std::this_thread::get_id() <<
		"\tEND CALCULATE TO REF==============\n";
}

void pressBtn(char& key, bool& pressed) {
	while (true) {
		if (_kbhit()) {
			key = _getch();
			pressed = true;

		}
	}
}

void fieldEvents() {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coords{ 0,0 };
	while(true) {
		coords.X = rand() % 11;
		coords.Y = rand() % 11;
		SetConsoleCursorPosition(handle, coords);
		std::cout << '.';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}


int main() {
	setlocale(LC_ALL, "ru");
	double n;

	// потоки
	/*
	std::cout << "START\n";
    // doSomething();         // плохо так как нагружается основной поток
	// calculate(5, 7);       // плохо так как нагружается основной поток
	// calculateTo(n, 7, 15); // плохо так как нагружается основной поток

	// std::thread th1(doSomething); 
	// th1.detach(); // остановка потока при завершении основной программы main 
	// std::thread th2(doSomething);
	// std::thread th3(calculate, 6,7); 

	std::thread th4(calculateTo, std::ref(n), 42, 105);


	for (rsize_t i = 0; i < 10; ++i) {
		std::cout << "Thread №" << std::this_thread::get_id() <<
			"\tmain()\t\t" << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // усыпляет программу 
	}
	// th1.join(); // "усыпление" текущего потока до тех пор пока не будет завершен поток th1(основной поток)
	// th2.join(); 
	// th3.join();
	th4.join();

	std::cout << "Calculation result is " << n << std::endl;

	std::cout << "END\n";
	*/


	COORD coords{ 0,0 }; // координаты нашего персонажа
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout << 'H'; // вывод персонажа

	char pressedKey = 0;
	bool isPressed = false;

	std::thread btnTh(pressBtn, std::ref(pressedKey), std::ref(isPressed));
	std::thread spawnTh(fieldEvents);
	btnTh.detach();
	spawnTh.detach();



	bool loop = true;
	while (true) {
		if (isPressed) {
			SetConsoleCursorPosition(handle, coords);
			std::cout << ' ';
			switch (std::tolower(pressedKey)) { // регистр клавиш
			case'w':

				if (coords.Y > 0)
					coords.Y -= 1;
				break;
			case'a': // движение влево

				if (coords.X > 0)
					coords.X -= 1;
				break;
			case's': // движение вниз

				coords.Y += 1;
				break;
			case'd': // движение вправо

				if (coords.X < 30)
					coords.X += 1;
				break;
			case'q': // клавиша на выход
				loop = false;
				break;
			}
			SetConsoleCursorPosition(handle, coords);
			std::cout << 'H';
			if (!loop) break;
			isPressed = false;
		}
	}
	system("cls");
	std::cout << "THE END\n";

	return 0;
}
