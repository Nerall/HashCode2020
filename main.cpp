#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <set>
#include <unordered_set>

using namespace std;

void parser() {

	int nb_books;
	int nb_libraries;

	cin >> nb_books;
	cin >> nb_libraries;
	cin >> Days;

	for (auto i = 0; i < nb_books; ++i) {
		int bscore;
		cin >> bscore;
		Book book(i, bscore, nullptr);
		books.push_back(book);
	}
	for (auto i = 0; i < nb_libraries; ++i) {
		int lcap;
		int lsignup;
		int lship;
		cin >> lcap;
		cin >> lsignup;
		cin >> lship;
		vector<Book*> booksptrvec;
		for (auto j = 0; j < lcap; ++j) {
			int id;
			cin >> id;
			Book* booksptr = &books[i];
			booksptrvec.push_back(booksptr);
		}
		Library library(i, lcap, lsignup, lship, booksptrvec);
		libraries.push_back(library);
		for (auto j = 0; j < lcap; ++j) {
			library.books[i] = &library;
		}
	}
}

int main() {
	parser();
	ofstream fo("toto.txt");
	fo << libraries.size() << '\n';

	for (auto l : libraries) {
		fo << l.books.size() << '\n';
		for (auto b : l.books) {
			fo << b->index() << ' ';
		} 
	}
}

