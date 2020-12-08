#include <iostream>
#include <Windows.h>

class TBook
{
protected:
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
		CopyFrom(other);
	}

	virtual void CopyFrom(const TBook& other)
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
	bool isBookPublicationYear(const int year) const { return this->year == year; }
	bool isBookAuthor(const char* author) const { return strcmp(this->author, author) == 0; }

	// operators
	bool operator>(const int year) const { return this->year > year; }
	bool operator<(const int year) const { return this->year < year; }
	bool operator>=(const int year) const { return this->year >= year; }
	bool operator<=(const int year) const { return this->year <= year; }
	bool operator==(const int year) const { return isBookPublicationYear(year); }
	bool operator==(const char* author) const { return isBookAuthor(author); }


	friend std::ostream& operator<<(std::ostream& out, const TBook& book)
	{
		out << "Автор: " << book.author << std::endl;
		out << "Название: " << book.title << std::endl;
		out << "Год издания: " << book.year << std::endl;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, TBook& book)
	{
		std::cout << "Автор: ";
		in >> book.author;

		std::cout << "Название: ";
		in >> book.title;

		std::cout << "Год издания: ";
		in >> book.year;
		return in;
	}
};

class PaidBook : public TBook
{
protected:
	char section[50] = "";
	int price = 0;

public:
	PaidBook()
		: TBook()
	{
	}

	PaidBook(const PaidBook& other)
		//: TBook(other)
	{
		CopyFrom(other);
	}

	virtual void CopyFrom(const PaidBook& other)
	{
		TBook::CopyFrom(other);
		strcpy_s(this->section, other.section);
		this->price = other.price;
	}

	PaidBook(const char* author, const char* title, int year, const char* section, int price)
		: TBook(author, title, year)
	{
		strcpy_s(this->section, section);
		this->price = price;
	}

	bool isSectionMatch(const char* section) const { return strcmp(this->section, section) == 0; }

	static PaidBook* findBooksBySection(PaidBook* books, int count, const char* section, int& found_count)
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
			found[i].CopyFrom(books[ids[i]]);
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

		out << "Раздел знаний: " << book.section << std::endl;
		out << "Цена: " << book.price << std::endl;

		return out;
	}

	friend std::istream& operator>>(std::istream& in, PaidBook& book)
	{
		in >> static_cast<TBook&>(book);

		std::cout << "Раздел знаний: ";
		in >> book.section;

		std::cout << "Цена: ";
		in >> book.price;

		return in;
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
	char section[50];
	cin >> section;

	int found_count;
	PaidBook* found = PaidBook::findBooksBySection(books, count, section, found_count);

	cout << "Нашёл книг: " << found_count << endl;
	for (int i = 0; i < found_count; i++)
	{
		cout << "Книга : " << i + 1 << endl;
		cout << found[i] << endl;
	}

	PaidBook::freeBooks(found);

	cout << "Это всё." << endl << endl;

	delete[] books;

	return 0;
}
