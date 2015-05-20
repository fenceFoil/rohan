#include "city.h"
#include <iostream>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::min;

City::City(string kingName) {
	this->kingName = kingName;

	year = 1; // Current year
	pop = 100; // Population
	deaths = 0; // Deaths this year
	stores = 2800; // bushels in store
	planted = 0; // Bushels planted to create next year's crop
	yield = 3; // bushels harvested per acre
	landPrice = 17; // Price of an acre
	acres = 1000; // Acres of land
	immigrants = 5; // New population
	eatenByRats = acres * yield - stores; // bushels eaten by rats
	allottedFood = 0; // Food given to the population to eat
	totalDeaths = 0; // total deaths at end of game
	popPercentStarved = 0; // percent population starved per year on average, for end of game
	plagueYear = false; // Whether there was a plague last year
	immigrantBonus = 0; // Immigrants from liberated cities
	gameOver = false; // Flag that is true if the player really angers the city
}

City::City(const City& cityObj) {
	kingName = cityObj.kingName;

	year = cityObj.year;
	pop = cityObj.pop;
	deaths = cityObj.deaths;
	stores = cityObj.stores;
	planted = cityObj.planted;
	yield = cityObj.yield;
	landPrice = cityObj.landPrice;
	acres = cityObj.acres;
	immigrants = cityObj.immigrants;
	eatenByRats = cityObj.eatenByRats;
	allottedFood = cityObj.allottedFood;
	totalDeaths = cityObj.totalDeaths;
	popPercentStarved = cityObj.popPercentStarved;
	plagueYear = cityObj.plagueYear;
	immigrantBonus = cityObj.immigrantBonus;
	gameOver = cityObj.gameOver;
}

City::~City() {
	// No dynamically allocated data
}

void City::impeach() {
	cout << "Due to this extreme mismangement you have not only" << endl;
	cout << "been impeached and thrown out of office but you have" << endl;
	cout << "also been declared National Fink!!!!" << endl;
	setGameOver();
}

void City::notEnoughBushels() const {
	cout << kingName << ": think again. You have only " << endl;
	cout << stores << " bushels of grain. Now then, " << endl;
}

void City::notEnoughAcres() const {
	cout << kingName << ": think again. You own only " << acres << " acres.  Now then, " << endl;
}

void City::endMessage() {
	cout << "In your " << year << "-year term of office, " << popPercentStarved << " percent of the" << endl;
	cout << "population starved per year on the average, i.e. a total of" << endl;
	cout << totalDeaths << " people starved!!" << endl;
	int acresPerPerson = acres / pop;
	cout << "You started with 10 acres per person and ended with" << endl;
	cout << acresPerPerson << " acres per person." << endl;
	cout << endl;

	// Check for any loss conditions
	if ((popPercentStarved > 33) || (acresPerPerson < 7)) {
		impeach();
	} else if ((popPercentStarved > 10) || (acresPerPerson < 9)) {
		cout << "Your heavy-handed performance smacks of Thorin and Saruman." << endl;
		cout << "The people (remaining) find you an unpleasant ruler, and," << endl;
		cout << "frankly, hate your guts!!" << endl;
		setGameOver();
	} else if ((popPercentStarved > 3) || (acresPerPerson < 10)) {
		cout << "Your performance could have been somewhat better, but" << endl;
		cout << "really wasn't too bad at all. ";
		cout << (rand() % (pop * 4 / 5)) << " people " << endl;
		cout << "dearly like to see you assassinated but we all have our" << endl;
		cout << "trivial problems." << endl;
		setGameOver();
	} else {
		// No loss found, victory attained!
		cout << "A fantastic performance!!! Galadriel, Bard, and" << endl;
		cout << "Aragorn combined could not have done better!" << endl;
		setGameOver();
	}
}

void City::runYear() {
	// Harvest
	yield = rand1to5();
	int harvest = planted * yield;

	// Risk of rats eating stores
	int ratChance = rand1to5();
	if (ratChance % 2 == 0) {
		eatenByRats = stores / ratChance;
	} else {
		eatenByRats = 0;
	}
	stores = stores - eatenByRats + harvest;

	// Decide next year's land prices
	landPrice = (rand() % 10) + 17;

	// *** Let's have some babies
	if (pop < 1) {
		pop = 1;
	}
	immigrants = (float) rand1to5() * (20.0 * acres + stores) / (float) pop / 100.0 + 1 + immigrantBonus;

	// *** How many people had full tummies?
	int maxFedPeople = allottedFood / 20;
	if (maxFedPeople >= pop) {
		deaths = 0;
		popPercentStarved = ((double) (year - 1) * popPercentStarved) / (double) (year);
	} else {
		// *** Starve enough for impeachment?
		deaths = pop - maxFedPeople;
		if (deaths > 0.45 * pop) {
			cout << endl;
			cout << "You starved " << deaths << " people in one year!!!" << endl;
			impeach();
		}
		popPercentStarved = ((double) (year - 1) * popPercentStarved + (double) deaths * 100.0 / (double) pop) / (double) (year);
		pop = maxFedPeople;
		totalDeaths += deaths;
	}

	// Update population
	pop += immigrants;

	// *** Horror, a 15% chance of plague
	// Equivalent to a random int from -3 to 16, where <= 0 brings plague.
	if ((rand() % 20) - 3 <= 0) {
		plagueYear = true;
		pop = pop / 2;
	} else {
		plagueYear = false;
	}

	// Increment year
	year++;
}

void City::reportYear() const {
	cout << endl << endl << kingName << ":  I beg to report to you," << endl;
	cout << "In year " << year << ", " << deaths << " people starved, " << immigrants << " came to the city, " << endl;
	if (immigrants - immigrantBonus > 25) {
		// ignoring the immigrantBonus to stop this message from appearing too often
		cout << "The city's unclaimed wealth attracted many new citizens." << endl;
	}
	if (immigrants - immigrantBonus > 200) {
		cout << "It's a land-rush!" << endl;
	}
	if (plagueYear) {
		cout << "A horrible plague struck! Half the people died." << endl;
	}
	cout << "Population is now " << pop << endl;
	cout << "The city now owns " << acres << " acres." << endl;
	cout << "You harvested " << yield << " bushels per acre." << endl;
	cout << "Rats ate " << eatenByRats << " bushels." << endl;
	cout << "You now have " << stores << " bushels in store." << endl << endl;
}

void City::promptPlayer() {
	promptBuyLand();
	promptFeedPeople();
	promptPlantFields();
}

void City::promptBuyLand() {
	cout << "Land is trading at " << landPrice << " bushels per acre." << endl;

	while (true) {
		cout << "How many acres do you wish to buy/sell (+/-): ";
		int tradeAcres = 0;
		cin >> tradeAcres;

		// Handle trading based on whether it is buying or selling
		if (tradeAcres > 0) {
			// Buying
			// Reprompt if the transaction cannot be made
			if (landPrice * tradeAcres > stores) {
				notEnoughBushels();
				continue;
			}
			// Execute buy
			acres += tradeAcres;
			stores -= landPrice * tradeAcres;
		} else if (tradeAcres < 0) {
			// Selling
			// Fix tradeAcres to be positive first
			tradeAcres = -tradeAcres;
			// Reprompt if transaction cannot be made
			if (tradeAcres > acres) {
				notEnoughAcres();
				continue;
			}
			// Execute sell
			acres -= tradeAcres;
			stores += landPrice * tradeAcres;
		}
		if (tradeAcres != 0) {
			cout << "You now have " << stores << " bushels in store." << endl;
		}

		// If we fell through to here, no problems with the transaction.
		break;
	}
}

void City::promptFeedPeople() {
	// Feeding people bushels
	do {
		cout << "How many bushels do you wish to feed your people: ";
		cin >> allottedFood;
		if (allottedFood < 0) {
			cout << endl;
			cout << kingName << ": I cannot do what you wish." << endl;
			cout << "Get yourself another steward!!!!!" << endl;
			continue;
		}
		// *** Trying to use more grain than is in silos?
		if (allottedFood > stores) {
			notEnoughBushels();
		}
	} while (allottedFood > stores);
	stores = stores - allottedFood;
}

void City::promptPlantFields() {
	do {
		int maxAcres = min(stores * 2, min(acres, pop * 10));
		cout << "How many acres do you wish to plant with seed (" << maxAcres << " max): ";
		cin >> planted;
		if (planted == 0) {
			break;
		}
		if (planted < 0) {
			cout << endl;
			cout << kingName << ": I cannot do what you wish." << endl;
			cout << "Get yourself another steward!!!!!" << endl;
			continue;
		}
		// *** Trying to plant more acres than you own?
		if (planted > acres) {
			notEnoughAcres();
			continue;
		}
		// *** Enough grain for seed?
		if ((int) (planted / 2) > stores) {
			notEnoughBushels();
			continue;
		}
		// *** Enough people to tend the crops?
		if (planted > 10 * pop) {
			cout << "But you have only " << pop << " people to tend the fields (10 acres/person)! Now then," << endl;
			continue;
		}
		break;
	} while (true);

	stores = stores - (int) (planted / 2);
	cout << "You now have " << stores << " bushels in store." << endl;
}

int City::loseLand(double proportion) {
	int lost = (int) (proportion * acres);
	acres -= lost;
	return lost;
}

int City::loseStores(double proportion) {
	int lost = (int) (proportion * stores);
	stores -= lost;
	return lost;
}
