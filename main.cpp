#include <algorithm>
#include <exception>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <vector>

class Library;
class Book;

namespace HashCode2020
{
	// Days -> Integer: 1 <= Days <= 10^5

	static std::vector<Library> Libraries;
	static std::vector<Book>    Books;
	static int                  Days;
}

class Book
{
	// Number of books -> Integer: 1 <= Number <= 10^5
	// Score           -> Integer: 1 <= Score  <= 10^3
public:
	Book(const int index, const int score)
		: _index(index)
		, _score(score)
	{ }

	auto  index()   const { return _index; }
	auto  score()   const { return _score; }

private:
	int _index;
	int _score;
};

class Library
{
	// Number of library -> Integer: 1 <= Number <= 10^5
public:
	Library(const int index,
		    const int capacity,
		    const int signup,
		    const int ship,
		    std::vector<const Book*>&& books)
		: _index(index)
		, _capacity(capacity)
		, _signup(signup)
		, _ship(ship)
		, _books(books)
	{
		std::sort(_books.begin(), _books.end(),
			[](const Book* a, const Book* b) -> bool
		{
			return a->score() > b->score();
		});
	}

	      auto index()    const { return _index;    } // The number of the library
		  auto capacity() const { return _capacity; } // The number of books in library
		  auto signup()   const { return _signup;   } // The number of days it takes to nish the library signup process for library
		  auto ship()     const { return _ship;     } // The number of books that can be shipped from the library to the scanning facility per day, once the library is signed up
	const auto& books()   const { return _books;    } // The books in the library

private:
	int                      _index; // -> Integer: 1 <= L <= 10^5
	int                   _capacity; // -> Integer: 1 <= N <= 10^5
	int                     _signup; // -> Integer: 1 <= T <= 10^5
	int                       _ship; // -> Integer: 1 <= M <= 10^5
	std::vector<const Book*> _books;
};

auto main(int argc, char const* argv[]) -> int
{
	std::ifstream file;

	try
	{
		if (argc != 2)
		{
			throw std::runtime_error("Invalid number of argument (one file path required)");
		}

		file.open(argv[1]);

		if (!file/*.is_open()*/)
		{
			auto message = std::string("Could not open file \"") + argv[1] + "\"";

			throw std::runtime_error(message);
		}

		// Parse 1st line (books, libraries, days)

		int     books;
		int libraries;

		file >> books
			 >> libraries
			 >> HashCode2020::Days;

		HashCode2020::Books.reserve(books);
		HashCode2020::Libraries.reserve(libraries);

		// Parse 2nd line (books score)

		for (auto i = 0; i < books; ++i)
		{
			int     score;
			file >> score;

			HashCode2020::Books.emplace_back(i, score);
		}

		// Parse libraries

		// Parse 1st library line

		for (auto i = 0; i < libraries; ++i)
		{
			int     capacity;
			file >> capacity;

			int     signup;
			file >> signup;


			int     ship;
			file >> ship;

			std::vector<const Book*> books;
			                         books.reserve(capacity);

			// Parse 2nd library line

			for (auto j = 0; j < capacity; ++j)
			{
				int     id;
				file >> id;

				books.emplace_back(std::addressof(HashCode2020::Books.data()[id]));
			}

			HashCode2020::Libraries.emplace_back(i, capacity, signup, ship, std::move(books));
		}

		// HashCode2020 //

		bool finished  = false;
		auto Libraries = HashCode2020::Libraries;
		std::cout << finished << std::endl;

		// Todo: what if () 
		std::ofstream fo("toto.txt");
		fo << HashCode2020::Libraries.size() << '\n';

		for (auto &l : HashCode2020::Libraries) {
			fo << l.books().size() << '\n';
			for (const auto* b : l.books()) {
				fo << b->index() << ' ';
			} 
		}		

	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;

		return 1;
	}
	return 0;
}
