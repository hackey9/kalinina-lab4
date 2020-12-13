#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <iomanip>


const int author_l = 20;
const int title_l = 20;
const int year_l = 10;
const int section_l = 20;
const int price_l = 20;

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
protected:
	std::string author = "";
	std::string title = "";
	int year = 0;

public:
	TBook()
	{
	}

	TBook(const std::string& author, const std::string& title, int year)
	{
		this->author = author;
		this->title = title;
		this->year = year;
	}

	// getters
	std::string getAuthor() const { return author; }
	std::string getTitle() const { return title; }
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
		//cin >> book.author;
		getline(cin, book.author);
		//in.get(book.author);

		std::cout << "Название: ";
		//cin >> book.title;
		getline(cin, book.title);

		std::cout << "Год издания: ";
		cin >> book.year;
		return cin;
	}
};

class PaidBook : public TBook
{
protected:
	std::string section = "";
	int price = 0;

public:
	PaidBook()
		: TBook()
	{
	}

	PaidBook(const std::string& author, const std::string& title, int year, const std::string& section, int price)
		: TBook(author, title, year)
	{
		this->section = section;
		this->price = price;
	}

	bool isSectionMatch(const std::string& section) const { return this->section == section; }

	static PaidBook* findBooksBySection(PaidBook* books, int count, const std::string& section, int& found_count)
	{
		found_count = 0;

		int* ids = new int[count];

		for (int i = 0; i < count; i++)
		{
			if (books[i].isSectionMatch(section))
			{
				ids[found_count] = i;
				found_count++;
			}
		}

		if (found_count == 0)
		{
			delete[] ids;
			return nullptr;
		}

		PaidBook* found = new PaidBook[found_count];

		for (int i = 0; i < found_count; i++)
		{
			found[i] = books[ids[i]];
		}
		delete[] ids;

		return found;
	}

	static void freeBooks(PaidBook* books)
	{
		delete[] books;
	}

	friend std::ostream& operator<<(std::ostream& out, const PaidBook& book)
	{
		out << static_cast<const TBook&>(book);

		out << std::setw(section_l) << book.section
			<< std::setw(price_l) << book.price;

		return out;
	}

	friend std::istream& operator>>(std::istream& cin, PaidBook& book)
	{
		cin >> static_cast<TBook&>(book);

		std::cout << "Раздел знаний: ";
		//cin >> book.section;
		getline(cin, book.section);

		std::cout << "Цена: ";
		cin >> book.price;

		return cin;
	}
};


using namespace std;

int main()
{
	//setlocale(LC_ALL, "rus");
	
	SetConsoleCP(1251); // установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	int count;
	cout << "Введите количество книг: ";
	cin >> count;
	PaidBook* books = new PaidBook[count];

	for (int i = 0; i < count; i++)
	{
		cout << endl << "Книга номер " << i + 1 << endl;
		cin >> books[i];
	}

	// find a book

	cout << endl;
	cout << "Давайте найдём книги!" << endl;
	cout << "\tВведите раздел знаний: ";
	//memset(buffer, 0, 50);
	std::string section;
	//cin >> section;
	getline(cin, section);

	int found_count;
	PaidBook* found = PaidBook::findBooksBySection(books, count, section, found_count);

	cout << "Нашёл книг: " << found_count << endl;

	cout << setw(author_l) << "Автор"
		<< setw(title_l) << "Название"
		<< setw(year_l) << "Год"
		<< setw(section_l) << "Раздел знаний"
		<< setw(price_l) << "Цена"
		<< endl;
	
	for (int i = 0; i < found_count; i++)
	{
		cout << found[i] << endl;
	}

	PaidBook::freeBooks(found);

	cout << "Это всё." << endl << endl;

	delete[] books;

	_getch();

	return 0;
}
