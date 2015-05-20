#include <algorithm>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>

#include "city.h"
#include "battle.h"

using std::find;
using std::string;
using std::vector;

/**
 * Creates sets of occupied towns to fight for, and armies occupying them.
 * A normal difficulty is 1.0, hard would be 2 or 3, etc. and affects the
 * size of the occupying armies.
 */
void addOccupiedCities(vector<Battle*>& occupiedCities, const double& difficulty) {
	Battle* tempBattle;
	tempBattle = new Battle();
	tempBattle->setName("ALDBURG");
	tempBattle->createWeapons();
	tempBattle->createArmyCreature2("orc", (int) (75.0 * difficulty));
	occupiedCities.push_back(tempBattle);
	tempBattle = new Battle();
	tempBattle->setName("DUNHARROW");
	tempBattle->createWeapons();
	tempBattle->createArmyCreature2("demon", (int) (100.0 * difficulty));
	occupiedCities.push_back(tempBattle);
	tempBattle = new Battle();
	tempBattle->setName("HELM'S DEEP");
	tempBattle->createWeapons();
	tempBattle->createArmyCreature2("balrog", (int) (200.0 * difficulty));
	occupiedCities.push_back(tempBattle);
}

/**
 * Executes a battle between a number of humans and a second army, already
 * prepared in "battle".
 * Returns true if the humans win.
 */
bool runBattle(int numRiders, Battle& battle) {
	// Generate the Riders of Rohan
	battle.createArmyCreature1("human", numRiders);

	// Show a summary of the two armies
	cout << endl << "The battle for " << battle.getName() << " starts now, between:" << endl;
	battle.reportArmyCreature1();
	battle.reportArmyCreature2();

	// Print the intial stats
	cout << "Initial Stats:" << endl;
	battle.reportStats();
	cout << endl;

	// Ask whether to show detail of the battle
	cout << "Show detailed messages about the battle? (n/Y): ";
	char ans = 'n';
	bool detailedMessages = true;
	cin >> ans;
	if (tolower(ans) == 'n') {
		detailedMessages = false;
	}

	cout << endl << endl;

	// Battle until one side is vanquished
	int round = 0;
	do {
		battle.creature1Attacks();
		battle.creature2Attacks();
		round++;
		if (detailedMessages) {
			cout << "Round " << round << endl;
			battle.reportStats();
			cout << endl;

			if (round % 25 == 0) {
				char messagesAns = 'y';
				cout << "Continue messages? (Y/n) " << endl;
				cin >> messagesAns;
				if (tolower(messagesAns) == 'n') {
					detailedMessages = false;
				}
			}
		}
		if (!battle.areCreaturesAlive()) {
			cout << "One army has fallen." << endl;
			break;
		}
	} while (true);

	// If detailed messages were turned off, output final results
	if (!detailedMessages) {
		battle.reportStats();
	}
	// Output the winner to the console
	cout << "The battle is over. The " << battle.victor() << " win!" << endl;
	cout << "End of the Battle of " << battle.getName() << endl;
	cout << endl;

	// Return whether Army 1 won
	if (battle.victor() == "Riders of Rohan") {
		return true;
	} else {
		return false;
	}
}

/**
 * Prompt player to create a new statue.
 */
void createStatue(vector<string>& statues) {
	// Get statue
	cout << "A craftsman of the town offers to carve you a statue." << endl;
	cout << "You want a stone __________: ";
	// Name can contain spaces
	string newStatue;
	// Ignore any newline before the statue name is entered
	cin.ignore(256, '\n');
	getline(cin, newStatue);
	cout << endl;
	cout << "All of Edoras rejoices beneath the mighty " << newStatue << "!" << endl;
	statues.push_back(newStatue);
}

int main(int argc, char* argv[]) {
	srand(time(NULL));

	// Show intro
	cout << "\t\t\t\tRiders of Rohan" << endl;
	cout << "\t\t\tEnter your name: ";
	// Ask name
	string kingName;
	// Name can contain spaces
	getline(cin, kingName);
	// Change name to uppercase
	for (unsigned int i = 0; i < kingName.length(); i++) {
		kingName[i] = toupper(kingName[i]);
	}
	// Continue intro
	cout << endl;
	cout << "Wise " << kingName << ", we welcome you as our ruler. Your riders," << endl;
	cout << "your steward, and your capital, Edoras, tremble beneath your " << endl;
	cout << "might, and shall never know a contradicted monarch." << endl;

	// Create capital city
	City* edoras = new City(kingName);

	// Create list of statues
	vector<string> statues;

	// Create sites of battles for occupied cities
	vector<Battle*> occupiedCities;
	double difficulty = 1.0;
	addOccupiedCities(occupiedCities, difficulty);

	// Set up statistics
	int battlesFought = 0;
	int battlesWon = 0;
	int surpriseAttacks = 0;
	int surpriseAttacksRepelled = 0;

	// Run game
	int scoutingLeft = 0;
	int surpriseAttackTurnsLeft = 10;
	do {
		cout << endl << endl << "\t*** A year passes... ***" << endl;

		// Announce a statue festival, if it is one
		if (rand() % 5 == 0 && statues.size() > 0) {
			int celebrated = rand() % statues.size();
			cout << "*** It is the " << statues[celebrated] << " festival! ***" << endl;
		}

		// Show the player what happened this year, and ask for the year's
		// instructions
		edoras->reportYear();
		edoras->promptPlayer();

		// Run special events
		// Check for scouts returning
		if (scoutingLeft <= 0) {
			// Scouts have returned!
			cout << endl;
			cout << kingName << ": Your SCOUTS have returned, ";
			cout << occupiedCities.size() << " cities are occupied by the dark forces of Mordor:" << endl;
			if (occupiedCities.size() > 0) {
				// Summarize cities
				for (vector<Battle*>::iterator i = occupiedCities.begin(); i != occupiedCities.end(); i++) {
					// Dereference the iterator, which gives a pointer to a battle.
					// Dereference that, and print a summary of the city.
					(**i).printScoutSummary();
				}
				// Note how restless next army is
				if (surpriseAttackTurnsLeft < 2) {
					cout << "The army at " << occupiedCities[0]->getName() << " is marching towards Edoras!" << endl;
				} else if (surpriseAttackTurnsLeft < 6) {
					cout << "The army at " << occupiedCities[0]->getName() << " are restless, and may make an attack soon." << endl;
				}
				// Ask whether the player wants to start battling the next city
				cout << kingName << ": do you wish to liberate " << occupiedCities[0]->getName() << " (y/N): ";
				char reply;
				cin >> reply;
				if (tolower(reply) == 'y') {
					// Attack the next city
					int committed = 0;
					cout << endl;
					cout << "The Riders of Rohan will ride at dawn the strike the foe, " << kingName << "!" << endl;
					if (edoras->getPop() <= 0) {
						cout << "... but there are no Riders, Edoras has 0 population." << endl;
						cout << "I shall strike the foe myself, my King, with you by my side!" << endl;

						edoras->setPop(2);
						committed = 1;
					} else {
						do {
							cout << "How many citizens will you send (of " << edoras->getPop() << "): ";
							cin >> committed;

							if (committed < edoras->getPop() / 2) {
								cout << "You should commit at least half of the city to the battle." << endl;
								continue;
							} else if (committed > edoras->getPop()) {
								cout << "There are only " << edoras->getPop() << " citizens to commit. Now then," << endl;
								continue;
							}
							break;
						} while (true);
					}

					// Run the battle
					bool ridersWon = runBattle(committed, *occupiedCities[0]);
					battlesFought++;
					if (ridersWon) {
						battlesWon++;
					}
					int ridersDead = committed - occupiedCities[0]->getArmy1Size();
					edoras->setPop(edoras->getPop() - ridersDead);
					if (edoras->getPop() <= 0) {
						edoras->setPop(1);
					}
					if (ridersWon) {
						cout << committed << " Riders of Rohan fought in the battle, and " << ridersDead << " died." << endl;

						cout << "Grateful citizens of " << occupiedCities[0]->getName() << " flock to Edoras, increasing immmigration by +5 per year!" << endl;
						edoras->increaseImmigrants(5);

						int retakenLand = rand() % 250 + 100;
						cout << "You have retaken land from the enemy as well: " << retakenLand << " acres!" << endl;
						edoras->addLand(retakenLand);

						// Get statue
						createStatue(statues);

						// Remove liberated city
						cout << occupiedCities[0]->getName() << " has been liberated by your might, o " << kingName << "!" << endl;
						occupiedCities.erase(occupiedCities.begin());
					} else {
						cout << kingName << ":  Your Riders fought bravely against the foe, but" << endl;
						cout << "all " << committed << " fell." << endl;
					}

					// If attack was successful, rest surprise attack from next city.
					// If attack failed, city was still shocked, and surprise attack counter is reset.
					surpriseAttackTurnsLeft = (rand() % 15) + 1;
				}
			} else {
				// Victory reminder message. Quit option.
				cout << "The armies of Mordor have been flushed from the plains of Rohan!" << endl;
				cout << "Quit, or Increase difficulty (q/I)? ";
				char reply = 'i';
				cin >> reply;
				if (tolower(reply) == 'q') {
					cout << endl;
					break;
				} else {
					cout << "Even as the scouts left, however, the forces of evil were " << endl;
					cout << "reconquering the cities of Rohan, more terrible than ever before..." << endl;
					difficulty += 2;
					addOccupiedCities(occupiedCities, difficulty);
				}
			}

			// write out a message, and send them back out
			cout << endl;
			cout << "SCOUTS have been sent to survey your kingdom." << endl;
			scoutingLeft = rand() % 3 + 1;
		} else {
			// Scouts still scouting...
			scoutingLeft--;
		}

		// Update surprise attacks
		if (surpriseAttackTurnsLeft <= 0 && occupiedCities.size() > 0) {
			// Announce surprise attack!
			cout << endl;
			cout << endl;
			cout << kingName << ": The army at " << occupiedCities[0]->getName() << " has attacked Edoras by surprise!" << endl;
			cout << "All of Edoras is preparing as we speak to defend the city:" << endl;
			if (edoras->getPop() <= 0) {
				cout << "... but there are no Riders, Edoras has 0 population." << endl;
				cout << "I shall defend the city myself, my King, with you by my side!" << endl;
				edoras->setPop(2);
			}
			// Run the surprise attack
			surpriseAttacks++;
			if (runBattle(edoras->getPop(), *occupiedCities[0])) {
				// Riders win
				surpriseAttacksRepelled++;
				// Put 10 soldiers back into the attacking city as a token force
				occupiedCities[0]->createArmyCreature2("orc", 10);

				createStatue(statues);

				edoras->setPop(occupiedCities[0]->getArmy1Size());
			} else {
				// Riders lose
				// Lose assets
				edoras->loseStores(0.8);
				cout << "The invaders burned most of the city's bushels of grain," << endl << "and ";
				cout << edoras->loseLand(0.36) << " acres of land were taken by the invading army." << endl;
				cout << endl;

				// Possibly lose a statue
				if (rand() % 3 <= 1 && statues.size() > 0) {
					int destroyedStatue = rand() % statues.size();
					cout << "During the invasion, the " << statues[destroyedStatue] << " fell to Sauron's dark forces." << endl;
					statues.erase(statues.begin() + destroyedStatue);
				}

				// Statues conceal some citizens
				cout << "The last Rider was fought back to the ";
				if (statues.size() > 0) {
					cout << "base of the statue " << endl;
					cout << "of " << statues[rand() % statues.size()] << ", where " << (10 * statues.size()) << " citizens hid, concealed, inside." << endl;
					// Put the hidden citizens back into Edoras
					edoras->setPop(statues.size() * 10);
				} else {
					// No statues, no citizens concealed. Land rush incoming...
					cout << "plinth where one day a" << endl;
					cout << "mighty statue may stand." << endl;
					edoras->setPop(1);
				}
			}
			// Handle aftermath for both wins and losses
			cout << endl;
			cout << edoras->getPop() << " citizens of Edoras survived the battle." << endl;

			// Wait for a while before the next surprise attack
			surpriseAttackTurnsLeft = (rand() % 15) + 1;
		}
		surpriseAttackTurnsLeft--;

		// Run Edoras for another year, with any changes to the population
		edoras->runYear();
	} while (!(edoras->isGameOver()));

	// Show final statistics for town
	cout << endl;
	edoras->endMessage();

	// Show final statistics for battles and statues
	cout << endl;
	cout << kingName << ":" << endl;
	// Victories
	cout << "The armies of Mordor attacked Edoras " << surpriseAttacks << " times," << endl;
	cout << "and were repelled " << surpriseAttacksRepelled << " times." << endl;
	cout << "You fought " << battlesFought << " battles, and liberated " << battlesWon << " cities." << endl;
	// Statues
	cout << "In gratitude for all these victories, citizens gifted you " << statues.size() << " statues";
	if (statues.size() > 0) {
		cout << ":" << endl;
		for (unsigned int i = 0; i < statues.size(); i++) {
			cout << "\t" << statues[i] << endl;
		}
	} else {
		cout << "." << endl;
	}
	// Final Difficulty
	cout << "Your final difficulty was " << difficulty << endl;
	cout << endl;
	cout << "The End" << endl;

	// Destroy city
	delete edoras;
	edoras = NULL;
}

