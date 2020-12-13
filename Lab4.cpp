#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <string>


void getline(std::istream& cin, std::string& str)
{
	do
	{
		std::getline(cin, str);
	} while (str.length() == 0);
	//std::cout << str;
}

class TBook
{
	std::string author = "";
	std::string title = "";
	int year = 0;

public:

	TBook()
	{
	}

	TBook(const std::string& author, const std::string& title, int year)
		: author(author), title(title), year(year)
	{
	}

	// getters
	const std::string& getAuthor() const { return author; }
	const std::string& getTitle() const { return title; }
	int getYear() const { return year; }

	// setters
	void setAuthor(const std::string& author) { this->author = author; }
	void setTitle(const std::string& title) { this->title = title; }
	void setYear(int year) { this->year = year; }

	// checkers
	bool isBookPublicationYear(int year) const { return this->year == year; }
	bool isBookAuthor(const std::string& author) const { return this->author == author; }
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

		std::string author;
		cout << "\tАвтор: ";
		getline(cin, author);
		books[i].setAuthor(author);

		string title;
		cout << "\tНазвание: ";
		getline(cin, title);
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
	string author;
	getline(cin, author);

	int year;
	cout << "\tВведите год публикации: ";
	cin >> year;

	cout << setw(20) << "Автор"
		<< setw(20) << "Название"
		<< setw(20) << "Год публикации"
		<< endl;
	for (int i = 0; i < count; i++)
	{
		if (books[i].isBookAuthor(author) && books[i].getYear() >= year)
		{
			cout << setw(20) << books[i].getAuthor()
				<< setw(20) << books[i].getTitle()
				<< setw(20) << books[i].getYear()
				<< endl;
		}
	}
	cout << "Это всё." << endl << endl;

	delete[] books;

	_getch();

	return 0;
}
