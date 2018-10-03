#include "pch.h"
#include "CLInterface.h"



void CLInterface::printFilm(Film film)
{
	cout << ":::::::: Film ::::::::" << endl;

	cout << "Id:" << film.getId() << endl;

	cout << "Title: " << *film.getTitle() << endl;

	vector<Genre*>* genres = film.getGenres();
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
	cout << ":::::::::::::::::::::::::::" << endl;

}

void CLInterface::printFilms(set<Film*>* films)
{
	if (films->size() > 0) {
		for (Film* film : *films) {
			printFilm(*film);
		}
	}
	else {
		printMessage(MESSAGE_FILM_NOT_FOUND);
	}
}

void CLInterface::printMenu()
{
	cout << ":::::::: Menu ::::::::" << endl;

	cout << "1. Get all films." << endl;
	cout << "2. Add a film." << endl;
	cout << "3. Edit a film." << endl;
	cout << "4. Delete a film" << endl;
	cout << "5. Search" << endl;

	cout << endl;
	cout << "0. Exit." << endl;
	cout << ":::::::::::::::::::::::::::" << endl;

}

void CLInterface::printFilmEditMenu()
{
	cout << ":::::::: Edit menu ::::::::" << endl;

	cout << "1. Edit title" << endl;
	cout << "2. Edit genres" << endl;
	cout << "3. Edit actros" << endl;
	cout << "4. Edit rating" << endl;
	cout << "5. Edit watched" << endl;
	cout << endl;

	cout << "0. Exit" << endl;
	cout << ":::::::::::::::::::::::::::" << endl;
}

void CLInterface::printSearchMenu()
{
	cout << ":::::::: Search menu ::::::::" << endl;

	cout << "1. Search by title" << endl;
	cout << "2. Search by genre" << endl;
	cout << "3. Search by actor" << endl;
	cout << "4. Search by rating(not watched)" << endl;
	cout << endl;

	cout << "0. Exit" << endl;
	cout << ":::::::::::::::::::::::::::" << endl;
}

void CLInterface::printAllFilms()
{
	set<Film*>* films = reposService.getDB()->getAllFilm();

	for (Film* film : *films) {
		printFilm(*film);
	}
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

	printFilmEditMenu();

	int cont = 0;
	cin >> cont;

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
	case 0:
		break;
	default:
		printMessage(MESSAGE_INCORRECT_INPUT);
		break;
	}
}

void CLInterface::removeFilm()
{
	cout << "::: Removing film :::" << endl;

	int id = inputIdFilm();

	if (id != -1)
		if (!reposService.getDB()->removeFilmById(id)) {
			printMessage(MESSAGE_ERROR_DELETE);
		}
}

void CLInterface::searchFilm()
{
	cout << "::: Search of film :::" << endl;

	int cont = 0;
	printSearchMenu();

	cin >> cont;

	switch (cont)
	{
	case 1:
		searchByTitle();
		break;
	case 2:
		searchByGenre();
		break;
	case 3:
		searchByActor();
		break;
	case 4:
		searchByRatingNotWatched();
		break;
	case 0:
		break;
	default:
		printMessage(MESSAGE_INCORRECT_INPUT);
		break;
	}
}

int CLInterface::inputIdFilm()
{
	int id;
	cout << "Id of film: ";
	cin >> id;

	if (id < 1)
	{
		printMessage(MESSAGE_INCORRECT_INPUT);
		return -1;
	}
	return id;
}

void CLInterface::editFilmTitle()
{
	int id;
	string *title;
	cout << ":::::: Edit title ::::::" << endl;
	cout << "Input id of film: ";
	cin >> id;
	title = inputTitle();

	if (!reposService.getDB()->updateTitleById(id, *title)) {
		printMessage(MESSAGE_ERROR_UPDATE);
	}
	cout << ":::::::::::::::::::::::::::" << endl;
	delete title;
}

void CLInterface::editFilmGenre()
{
	int id;
	cout << ":::::: Edit genres ::::::" << endl;
	cout << "Input id of film: ";
	cin >> id;
	cout << "Select new genres: " << endl;
	vector<Genre*>* genres = selectGenres();

	if (!reposService.getDB()->updateGenreById(id, genres)) {
		printMessage(MESSAGE_ERROR_UPDATE);
	}
	cout << ":::::::::::::::::::::::::::" << endl;
}

void CLInterface::editFilmActor()
{
	int id;
	cout << ":::::: Edit actos ::::::" << endl;
	cout << "Input id of film: ";
	cin >> id;
	cout << "Select new actors: " << endl;
	vector<Actor*>* actors = selectActors();

	if (!reposService.getDB()->updateActorById(id, actors)) {
		printMessage(MESSAGE_ERROR_UPDATE);
	}
	cout << ":::::::::::::::::::::::::::" << endl;
}

void CLInterface::editFilmRating()
{
	int id;
	double rating;
	cout << ":::::: Edit rating ::::::" << endl;
	cout << "Input id of film: ";
	cin >> id;
	
	rating = selectRating();
	if (!reposService.getDB()->updateRatingById(id, rating)) {
		printMessage(MESSAGE_ERROR_UPDATE);
	}
	cout << ":::::::::::::::::::::::::::" << endl;
}

void CLInterface::editFilmWatched()
{
	int id;
	bool watched;
	cout << ":::::: Edit watched ::::::" << endl;
	cout << "Input id of film: ";
	cin >> id;
	watched = selectWatched();

	if (!reposService.getDB()->updateWatchedById(id, watched)) {
		printMessage(MESSAGE_ERROR_UPDATE);
	}
	cout << ":::::::::::::::::::::::::::" << endl;
}

void CLInterface::searchByTitle()
{
	string title;

	cout << "Input title: ";
	cin >> title;

	set<Film*>* films = reposService.getDB()->getFilmsByTitle(title);

	printFilms(films);
}

void CLInterface::searchByGenre()
{
	string genre;

	cout << "Input genre: ";
	cin >> genre;

	set<Film*>* films = reposService.getDB()->getFilmsByGenre(genre);

	printFilms(films);

}

void CLInterface::searchByActor()
{
	string firstNameActor, secondNameActor;

	cout << "Input firstname of actor: ";
	cin >> firstNameActor;
	cout << "Input secondname of actor: ";
	cin >> secondNameActor;

	set<Film*>* films = reposService.getDB()->getFilmsByActor(Actor(firstNameActor, secondNameActor));

	printFilms(films);

}

void CLInterface::searchByRatingNotWatched()
{
	double rating;

	cout << "Input rating (more than): ";
	cin >> rating;

	set<Film*>* films = reposService.getDB()->getFilmsByRatingAndWathced(rating, false);

	printFilms(films);
}

void CLInterface::printMessage(const char * str)
{
	cout << str << endl;
}

string* CLInterface::inputTitle()
{
	char title[BUFFER_SIZE];

	while (true)
	{
		cout << "Title: " << endl;
		cin.ignore();
		cin.getline(title, BUFFER_SIZE);
		if ( sizeof(title)/sizeof(*title) == 0) {
		}
		else {
			break;
		}
		cout << endl;
	}

	return new string (title);
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
			printMessage(MESSAGE_INCORRECT_INPUT);
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
			printMessage(MESSAGE_INCORRECT_INPUT);
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
		case 5:
			searchFilm();
			break;
		case 0:
			break;
		default:
			printMessage(MESSAGE_INCORRECT_INPUT);
			break;
		}
	}
}