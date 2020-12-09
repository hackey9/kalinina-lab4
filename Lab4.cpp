#include <iostream>
#include <Windows.h>
#include <conio.h>

class TBook
{
	char author[30] = "";
	char title[50] = "";
	int year = 0;

public:

	TBook()
	{
	}

	TBook(const char* author, const char* title, int year)
	{
		strcpy_s(this->author, author);
		strcpy_s(this->title, title);
		this->year = year;
	}

	TBook(const TBook& other)
	{
		strcpy_s(this->author, other.author);
		strcpy_s(this->title, other.title);
		this->year = other.year;
	}

	// getters
	const char* getAuthor() const { return author; }
	const char* getTitle() const { return title; }
	int getYear() const { return year; }

	// setters
	void setAuthor(const char* author) { strcpy_s(this->author, author); }
	void setTitle(const char* title) { strcpy_s(this->title, title); }
	void setYear(int year) { this->year = year; }

	// checkers
	bool isBookPublicationYear(int year) const { return this->year == year; }
	bool isBookAuthor(const char* author) const { return strcmp(this->author, author) == 0; }
};


using namespace std;

int main()
{
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода
	
	//TBook books[15];

	int count;
	cout << "Введите количество книг: " << endl;
	cin >> count;
	TBook *books = new TBook[count];

	//char buffer[50];

	for (int i = 0; i < count; i++)
	{
		cout << endl << "Книга номер " << i + 1 << endl;

		char author[50] = "";
		cout << "\tАвтор: ";
		cin >> author;
		books[i].setAuthor(author);

		char title[50] = "";
		cout << "\tНазвание: ";
		cin.getline(title, sizeof(title));
		cin >> title;
		books[i].setTitle(title);

		int year;
		cout << "\tГод издания: ";
		cin >> year;
		books[i].setYear(year);
	}

	// find a book with author

	cout << "Давайте найдём книгу" << endl;
	cout << "\tВведите автора: ";
	//memset(buffer, 0, 50);
	char author[50];
	cin >> author;

	int year;
	cout << "\tВведите год публикации: ";
	cin >> year;
	
	for (int i = 0; i < count; i++)
	{
		if (books[i].isBookAuthor(author) && books[i].getYear() >= year)
		{
			cout << "Нашёл: " << books[i].getTitle() << " (" << books[i].getYear() << "г.)" << endl;
		}
	}
	cout << "Это всё." << endl << endl;

	delete[] books;

	_getch();

	return 0;
}
