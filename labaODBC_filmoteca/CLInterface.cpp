#include "pch.h"
#include "CLInterface.h"



void CLInterface::printFilm(Film film)
{
	cout << ":::Film:::" << endl;

	cout << "Id:" << film.getId() << endl;

	cout << "Title: " << *film.getTitle() << endl;

	vector<Genre*>* genres = &*film.getGenres();
	cout << "Genres: " << endl;
	for (Genre* genre : *genres) {
		cout << '\t' << genre->getName() << endl;
	}

	vector<Actor*>* actors = film.getActors();
	cout << "Actors: " << endl;
	for (Actor* actor : *actors) {
		cout << '\t' << actor->getFirstName() << " " << actor->getSecondName() << endl;
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

void CLInterface::printFilmEditMenu()
{
	cout << ":::::::: Edit menu ::::::::" << endl;

	cout << "1. Edit title" << endl;
	cout << "2. Edit genres" << endl;
	cout << "3. Edit actros" << endl;
	cout << "4. Edit rating" << endl;
	cout << "5. Edit watched" << endl;
	cout << ":::::::::::::::::::::::::::" << endl;
}

void CLInterface::printAllFilms()
{
	set<Film*>* films = reposService.getDB()->getAllFilm();

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

	Film *film = new Film(title, genres, actors, rating, isWatched);

	reposService.getDB()->addFilm(film);
	delete film;
}

void CLInterface::editFilm()
{
	cout << "::: Edit of film :::" << endl;

	int id = inputIdFilm();
	printFilmEditMenu();

	int cont = 0;

	switch (cont)
	{
	case 1:
		editFilmTitle();
		break;
	case 2:
		editFilmGenre();
		break;
	case 3:
		editFilmActor();
		break;
	case 4:
		editFilmRating();
		break;
	case 5:
		editFilmWatched();
	default:
		cout << "Incorrect input!!!" << endl;
		break;
	}
}

void CLInterface::removeFilm()
{
	cout << "::: Removing film :::" << endl;

	int id = inputIdFilm();
	
	if (id != -1)
		reposService.getDB()->removeFilmById(id);
}

int CLInterface::inputIdFilm()
{
	int id;
	cout << "Id of film: ";
	cin >> id;
	if (id < 1)
	{
		cout << "Incorrect input" << endl;
		return -1;
	}
	return id;
}

void CLInterface::editFilmTitle()
{
}

void CLInterface::editFilmGenre()
{
}

void CLInterface::editFilmActor()
{
}

void CLInterface::editFilmRating()
{
}

void CLInterface::editFilmWatched()
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
		}
		else {
			break;
		}
		cout << endl;
	}

	return title;
}

vector<Genre*>* CLInterface::selectGenres()
{
	set<Genre*>* existsGenres; 
	set<int>* selectedIdsGenres = new set<int>();
	vector<Genre*>* listGenres = new vector<Genre*>();

	int contr = -2;

	while (contr != 0) {
		existsGenres = reposService.getDB()->getAllGenres();

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
		}
		else {
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
}

vector<Actor*>* CLInterface::selectActors()
{
	set<Actor*>* existsActor;
	set<int>* selectedIdsActors = new set<int>();
	vector<Actor*>* listActros = new vector<Actor*>();

	int contr = -2;

	while (contr != 0) {
		existsActor = reposService.getDB()->getAllActors();

		cout << "::Actor::" << endl;
		for (Actor *actor : *existsActor) {
			if (selectedIdsActors->find(actor->getId()) == selectedIdsActors->end()) {
				cout << '\t' << actor->getId() << ". "
					<< actor->getFirstName() << " " << actor->getSecondName() << endl;
			}
		}

		cout << endl;
		cout << "-1. Add new actor" << endl;
		cout << "0. Exit" << endl;

		cout << "Input id of actor: ";
		cin >> contr;

		if (contr == 0) {
			break;
		}

		if (contr == -1) {
			addNewActor();
		}
		else {
			bool isFind = false;
			int idActor;
			for (Actor *actor : *existsActor) {
				idActor = actor->getId();

				if (idActor == contr && selectedIdsActors->find(idActor) == selectedIdsActors->end()) {
					listActros->push_back(actor);
					selectedIdsActors->insert(idActor);
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

	delete selectedIdsActors;
	delete existsActor;

	return listActros;
}

double CLInterface::selectRating()
{
	cout << "Rate the film for range(0..10) " << endl;

	double rate = -1;
	while (rate < 0 || rate > 10)
	{
		cout << "Input rate: ";
		cin >> rate;

		if (rate < 0 || rate > 10) {
			cout << "Incorrect input" << endl;
		}
	}

	return rate;
}

bool CLInterface::selectWatched()
{
	char watched;
	bool isWatched;
	while (true)
	{
		cout << "Did you watched this film? (y/n)" << endl;
		cin >> watched;
		watched = tolower(watched);
		if (watched == 'y' || watched == 'n') {
			if (watched == 'y') {
				isWatched = true;
			}
			else {
				isWatched = false;
			}
			break;
		}
		else {
			cout << "Incorrect input!" << endl;
		}
		cout << endl;
	}

	return isWatched;
}

void CLInterface::addNewGenre()
{
	cout << "::: Adding new genre :::" << endl;
	
	string newGenre;
	cout << "Input new genre: ";
	cin >> newGenre;

	Genre genre(newGenre);
	reposService.getDB()->addGenre(genre);
}

void CLInterface::addNewActor()
{
	cout << "::: Adding new actor :::" << endl;

	string firstName, secondName;
	cout << "Input new firstName of actor: ";
	cin >> firstName;
	cout << "Input new secondName of actor: ";
	cin >> secondName;

	Actor actor(firstName, secondName);
	reposService.getDB()->addActor(actor);
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