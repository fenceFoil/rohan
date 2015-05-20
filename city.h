#ifndef CITY_H
#define CITY_H

#include <string>
#include <cstdlib>

using std::rand;
using std::string;

class City {
protected:
	string kingName;
	int year; // Current year
	int pop; // Population
	int deaths; // Deaths this year
	int stores; // bushels in store
	int planted; // Bushels planted to create next year's crop
	int yield; // bushels harvested per acre
	int landPrice; // Price of an acre
	int acres; // Acres of land
	int immigrants; // New population
	int eatenByRats; // bushels eaten by rats
	int allottedFood; // Food given to the population to eat
	int totalDeaths; // total deaths at end of game
	double popPercentStarved; // percent population starved per year on average, for end of game
	bool plagueYear; // Whether there was a plague last year
	int immigrantBonus; // Immigrants from liberated cities
	bool gameOver;

	void promptBuyLand();
	void promptFeedPeople();
	void promptPlantFields();

	void notEnoughBushels() const;
	void notEnoughAcres() const;
	void impeach();
	void setGameOver() {
		gameOver = true;
	}
	int rand1to5() const {
		return (rand() % 5) + 1;
	}
public:
	City(string kingName);
	City(const City& cityObj);
	~City();

	void reportYear() const;
	void promptPlayer();
	void runYear();
	void endMessage();

	int getPop() const {
		return pop;
	}
	void setPop(int newPop) {
		pop = newPop;
	}
	void increaseImmigrants(int bonus) {
		immigrantBonus += bonus;
	}
	/**
	 * Input: a number between 0.0 and 1.0
	 * Returns the bushels of grain lost.
	 */
	int loseStores(double proportion);
	/**
	 * Input: a number between 0.0 and 1.0
	 * Returns the acres of land lost.
	 */
	int loseLand(double proportion);
	void addLand(int acres) {
		this->acres += acres;
	}
	bool isGameOver() const {
		return gameOver;
	}
};

#endif
