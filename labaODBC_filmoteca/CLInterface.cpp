#include "pch.h"
#include "CLInterface.h"



void CLInterface::printFilm(Film film)
{
	cout << ":::Film:::" << endl;

	cout << "Title: " << *film.getTitle() << endl;

	vector<Genre*>* genres = &*film.getGenres();
	cout << "Genres: " << endl;
	for (Genre* genre : *genres) {
		cout << '\t' << genre->getName() << endl;
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
	set<Film*>* films = RepositoryService().getDB()->getAllFilm();

	for (Film* film : *films) {
		printFilm(*film);
	}
}

void CLInterface::printFilm()
{

}

void CLInterface::addFilm()
{
	cout << ":::Adding Film:::" << endl;

	string *title = inputTitle();

	vector<Genre*>* genres = selectGenres();
	
	vector<Actor*>* actors = selectActors();

	double rating = selectRating();

	bool isWatched = selectWatched();

	Film film(title, genres, actors, rating, isWatched);

	RepositoryService().getDB()->addFilm(film);
}

void CLInterface::editFilm()
{
}

void CLInterface::removeFilm()
{
}

string* CLInterface::inputTitle()
{
	string* title = new string();

	while (true)
	{	
		cout << "Title: " << endl;
		cin >> *title;
		if (title->size() == 0) {
			cout << "Incorrect input!" << endl;
		} else {
			break;
		}
		cout << endl;
	}

	return title;
}

vector<Genre*>* CLInterface::selectGenres()
{
	set<Genre*>* existsGenres = RepositoryService().getDB()->getAllGenres();
	set<int>* selectedIdsGenres = new set<int>();
	vector<Genre*>* listGenres = new vector<Genre*>();

	int contr = -2;

	while (contr != 0) {
		cout << "::Genres::" << endl;
		for (Genre *genre : *existsGenres) {
			if (selectedIdsGenres->find(genre->getId()) == selectedIdsGenres->end()) {
				cout << '\t' << genre->getId() << ". " << genre->getName() << endl;
			}
		}

		cout << endl;
		cout << "-1. Add new genre" << endl;
		cout << "0. Exit" << endl;

		cout << "Input id of genre: ";
		cin >> contr;

		if (contr == 0) {
			break;
		}

		if (contr == -1) {
			addNewGenre();
		} else {
			bool isFind = false;
			int idGenre;
			for (Genre *genre : *existsGenres) {
				idGenre = genre->getId();
				
				if (idGenre == contr && selectedIdsGenres->find(idGenre) == selectedIdsGenres->end()) {
					listGenres->push_back(genre);
					selectedIdsGenres->insert(idGenre);
					isFind = true;
					break;
				}
			}

			if (!isFind) {
				cout << "Inputed incorrect id!" << endl;
			}
		}

		cout << endl;
	}

	delete selectedIdsGenres;
	delete existsGenres;

	return listGenres;
;
}

vector<Actor*>* CLInterface::selectActors()
{
	return nullptr;
}

double CLInterface::selectRating()
{
	return 0.0;
}

bool CLInterface::selectWatched()
{
	return false;
}

void CLInterface::addNewGenre()
{
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