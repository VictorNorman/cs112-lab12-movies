#include "App.h"

#include <iostream>

#include "Bridges.h"
#include "DataSource.h"
#include "Menu.h"
#include "data_src/MovieActorWikidata.h"

using namespace std;
using namespace bridges;

App::App(vector<MovieActorWikidata> &movies_vector) {
    cout << "Got " << movies_vector.size() << " movies...\n";

    // iterate through the vector and gather the actors into each movie record.
    for (vector<MovieActorWikidata>::iterator it = movies_vector.begin();
         it != movies_vector.end(); ++it) {

        // this line is equivalent to all the others just below!
        movies_by_name[it->getMovieName()].insert(it->getActorName());

        // db_iter found_movie = movies_by_name.find(it->getMovieName());
        // if (found_movie == movies_by_name.end()) {
        //     set<string> actors;
        //     actors.insert(it->getActorName());
        //     pair<string, set<string>> entry(it->getMovieName(), actors);
        //     movies_by_name.insert(entry);
        // } else {
        //     // must be in the data structure already, so update with another
        //     // actor name.
        //     found_movie->second.insert(it->getActorName());
        // }

    }
}

void App::showAllMovies() {
    for (db_iter it = movies_by_name.begin(); it != movies_by_name.end();
         ++it) {
        cout << "Movie: " << it->first << endl;
        showActorsInAMovie(it);
    }
}

void App::showActorsInAMovie(const db_iter &movie_it) {
    for (set<string>::iterator actors_it = movie_it->second.begin();
         actors_it != movie_it->second.end(); ++actors_it) {
        cout << "\t" << *actors_it << endl;
    }
}

void App::getMovieNameAndShowActors() {
    string movie_name;
    cout << "Enter a movie name to see the list of actors: ";
    cin.ignore();
    getline(cin, movie_name);

    db_iter it = movies_by_name.find(movie_name);
    if (it == movies_by_name.end()) {
        cout << "No movie found by that name\n";
    } else {
        cout << "Actors in " << movie_name << ": \n";
        showActorsInAMovie(it);
    }
}


void App::showAllMoviesForAnActor() {
    set<string> movies_by_actor;

    string actor_name;
    cout << "Enter an actor name to show all movies for that actor: ";
    cin.ignore();
    getline(cin, actor_name);

    for (db_iter it = movies_by_name.begin(); it != movies_by_name.end();
         ++it) {
        for (set<string>::iterator actors_it = it->second.begin();
             actors_it != it->second.end(); ++actors_it) {
            if (*actors_it == actor_name) {
                movies_by_actor.insert(it->first);
            }
        }
    }

    for (set<string>::iterator it = movies_by_actor.begin();
         it != movies_by_actor.end(); ++it) {
        cout << *it << endl;
    }
}

void App::run() {
    while (true) {
        char choice = getMenuChoice();
        if (choice == Menu::QUIT) {
            break;
        }
        perform(choice);
    }
}

void App::perform(char choice) {
    switch (choice) {
        case 'a':
            showAllMovies();
            break;
        case 'b':
            getMovieNameAndShowActors();
            break;
        case 'c':
            showAllMoviesForAnActor();
            break;
        default:
            cerr << "\n*** choice " << choice << " is not supported\n" << endl;
    }
}

char App::getMenuChoice() const {
    Menu menu;
    char choice;
    while (true) {
        cout << '\n' << menu << flush;
        cin >> choice;
        if (menu.containsChoice(choice)) {
            break;
        }
        cout << "\n*** " << choice << " is not supported!\n" << endl;
    }
    return choice;
}