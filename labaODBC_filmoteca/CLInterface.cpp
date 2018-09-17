#include "pch.h"
#include "CLInterface.h"



void CLInterface::printFilm(Film film)
{
	cout << ":::Film:::" << endl;

	cout << "Title: " << *film.getTitle() << endl;

	vector<string*>* genres = &*film.getGenres();
	cout << "Genres: " << endl;
	for (string* genre : *genres) {
		cout << '\t' << *genre << endl;
	}

	vector<Actor*>* actors = film.getActors();
	cout << "Actors: " << endl;
	for (Actor* actor : *actors) {
		cout << '\t' << *actor->getFirstName() << " " << *actor->getSecondName() << endl;
	}

	cout << "Rating: " << film.getRating() << endl;
	cout << "Watched: " << film.getWatched() << endl;
	cout << endl;
}

void CLInterface::printMenu()
{
	cout << ":::Menu:::" << endl;

	cout << "1. Get all films." << endl;
	cout << "2. Add a film." << endl;
	cout << "3. Edit a film." << endl;
	cout << "4. Delete a film" << endl;

	cout << endl;
	cout << "0. Exit." << endl;
}

void CLInterface::printAllFilms()
{
	vector<Film*>* films = RepositoryService::getDB()->getAllFilm();

	for (Film* film : *films) {
		printFilm(*film);
	}
}

void CLInterface::printFilm()
{

}

void CLInterface::addFilm()
{
	cout << "Adding Film" << endl;

	cout << "Title: " << endl;
	string title;
	cin >> title;

	cout << "Genres" << endl;
	vector<Genre*> genres = selectGenres();
	
	RepositoryService::getDB()->addFilm()
}

void CLInterface::editFilm()
{
}

void CLInterface::removeFilm()
{
}

vector<Genre*>* CLInterface::selectGenres()
{
	vector<string*>* existsGenres = RepositoryService::getDB()->getAllGenres();
	for (string *genre : *existsGenres) {
		cout << genre << endl;
	}
}

void CLInterface::run()
{
	int cont = -1;

	while (cont != 0)
	{
		printMenu();

		cin >> cont;

		switch (cont)
		{
		case 1:
			printAllFilms();
			break;
		case 2:
			addFilm();
			break;
		case 3:
			editFilm();
			break;
		case 4:
			removeFilm();
			break;
		case 0:
			break;
		default:
			cout << "Incorrect input!!!" << endl;
			break;
		}
	}
}