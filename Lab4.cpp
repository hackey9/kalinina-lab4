#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <iomanip>
#include <string>


const int author_l = 24;
const int title_l = 24;
const int year_l = 15;


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

	TBook(const char* author, const char* title, int year)
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
	bool isBookPublicationYear(const int year) const { return this->year == year; }
	bool isBookAuthor(const std::string& author) const { return this->author == author; }

	// operators
	bool operator>(const int year) const { return this->year > year; }
	bool operator<(const int year) const { return this->year < year; }
	bool operator>=(const int year) const { return this->year >= year; }
	bool operator<=(const int year) const { return this->year <= year; }
	bool operator==(const int year) const { return isBookPublicationYear(year); }
	bool operator==(const std::string& author) const { return isBookAuthor(author); }


	friend std::ostream& operator<<(std::ostream& out, const TBook& book)
	{
		out << std::setw(author_l) << book.author
			<< std::setw(title_l) << book.title
			<< std::setw(year_l) << book.year;
		
		return out;
	}

	friend std::istream& operator>>(std::istream& cin, TBook& book)
	{
		std::cout << "Автор: ";
		getline(cin, book.author);

		std::cout << "Название: ";
		getline(cin, book.title);

		std::cout << "Год издания: ";
		cin >> book.year;
		return cin;
	}
};


using namespace std;

int main()
{
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	int count;
	cout << "Введите количество книг: ";
	cin >> count;
	TBook* books = new TBook[count];

	for (int i = 0; i < count; i++)
	{
		cout << endl << "Книга номер " << i + 1 << endl;
		cin >> books[i];
	}

	// find a book with author

	cout << "Давайте найдём книгу" << endl;
	cout << "\tВведите автора: ";
	//memset(buffer, 0, 50);
	string author;
	getline(cin, author);

	cout << "\tВведите год публикации: ";
	int year;
	cin >> year;
	
	cout << endl
		<< std::setw(author_l) << "Автор"
		<< std::setw(title_l) << "Название"
		<< std::setw(year_l) << "Год издания"
		<< endl;
	
	for (int i = 0; i < count; i++)
	{
		// this is overload operators
		if (books[i] == author && books[i] >= year)
		{
			cout << books[i] << endl;
		}
	}
	cout << "Это всё." << endl << endl;

	delete[] books;

	_getch();

	return 0;
}
