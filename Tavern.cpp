/*
Author: Cesar Iglesias
Course: CSCI-235
Instructor: Ligorio
Assignment: Project 4
Tavern.cpp declares the Tavern class along with its private and public members
*/

#include "Tavern.hpp"

/** Default Constructor **/
Tavern::Tavern() : ArrayBag<Character*>(), level_sum_{0}, num_enemies_{0}
{
}

/*
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows (each numbered item appears separated by comma, only one value for each numbered item):
    1. Name: An uppercase string
    2. Race: An uppercase string [HUMAN, ELF, DWARF, LIZARD, UNDEAD]
    3. Subclass: An uppercase string [BARBARIAN, MAGE, SCOUNDREL, RANGER]
    4. Level/Vitality/Armor: A positive integer
    5. Enemy: 0 (False) or 1 (True)
    6. Main: Uppercase string or strings representing the main weapon (Barbarian and Mage), Dagger type (Scoundrel), or arrows (Ranger). A ranger's arrows are of the form [TYPE] [QUANTITY];[TYPE] [QUANTITY], where each arrow type is separated by a semicolon, and the type and its quantity are separated with a space.
    7. Offhand: An uppercase string that is only applicable to Barbarians, and may be NONE if the Barbarian does not have an offhand weapon, or if the character is of a different subclass.
    8. School/Faction: Uppercase strings that represent a Mage's school of magic: [ELEMENTAL, NECROMANCY, ILLUSION] or a Scoundrel's faction: [CUTPURSE, SHADOWBLADE, SILVERTONGUE], and NONE where not applicable
    9. Summoning: 0 (False) or 1 (True), only applicable to Mages (summoning an Incarnate) and Rangers (Having an Animal Companion)
    10. Affinity: Only applicable to Rangers. Affinities are of the form [AFFINITY1];[AFFINITY2] where multiple affinities are separated by a semicolon. Th value may be NONE for a Ranger with no affinities, or characters of other subclasses.
    11. Disguise: 0 (False) or 1 (True), only applicable to Scoundrels, representing if they have a disguise.
    12. Enraged: 0 (False) or 1 (True), only applicable to Barbarians, representing if they are enraged.
    @post: Each line of the input file corresponds to a Character subclass and dynamically allocates Character derived objects, adding them to the Tavern.
*/

Tavern::Tavern(const std::string& input_file) : ArrayBag<Character*>(), level_sum_(0), num_enemies_(0) {

    //reading the file

    std::ifstream fin(input_file);

    //if my file is not reading the function will quit

    if (!fin.is_open()) {

        std::cerr << "Error: Unable to open input file." << std::endl;
        return;

    }

    //creation of variables

    std::string tvariable;
    std::string name, race, subclass, school_o_faction, main, offhand;
    int level, vitality, armor;
    bool enemy, summoning, disguise, enraged;
    std::vector<std::string> affinities;
    std::vector<Arrows> arrow;

    std::string line;

    while (std::getline(fin, line)) {

        //reading through each line and assiig 

        std::istringstream iss(line);

        std::getline(iss, name, ',');
        std::getline(iss, race, ',');
        std::getline(iss, subclass, ',');
        std::getline(iss, tvariable, ',');
        std::istringstream(tvariable) >> level;
        std::getline(iss, tvariable, ',');
        std::istringstream(tvariable) >> vitality;
        std::getline(iss, tvariable, ',');
        std::istringstream(tvariable) >> armor;
        std::getline(iss, tvariable, ',');
        std::istringstream(tvariable) >> enemy;
        std::getline(iss, main, ',');
        std::getline(iss, offhand, ',');
        std::getline(iss, school_o_faction, ',');
        std::getline(iss, tvariable, ',');
        std::istringstream(tvariable) >> summoning;
        std::getline(iss, tvariable, ',');
        int i = 0;
        while (i < tvariable.size()) {
            std::string affinity = "";
            while (tvariable[i] != ';' && i < tvariable.size()) {
                affinity += tvariable[i];
                i++;
            }
            affinities.push_back(affinity);
            i++;
        }
        std::getline(iss, tvariable, ',');
        std::istringstream(tvariable) >> disguise;
        std::getline(iss, tvariable, ',');
        std::istringstream(tvariable) >> enraged;

        //if the subclass is ranger it will have to separate each arrow with their quantities

        if (subclass == "RANGER") {

            std::istringstream arrowiss(main);
            std::string arrowinfo;

            while (std::getline(arrowiss, arrowinfo, ';')) {

                std::istringstream arrowinfoiss(arrowinfo);
                std::string arrowtype;
                int arrowquantity;

                if (arrowinfoiss >> arrowtype >> arrowquantity) {

                    Arrows tarrow;
                    tarrow.type_ = arrowtype;
                    tarrow.quantity_ = arrowquantity;
                    arrow.push_back(tarrow); //in tavern i cant acsses to private vector inn ranger.cpp

                }

            }

            Character* new_character = nullptr;
            new_character = new Ranger(name, race, vitality, armor, level, enemy, arrow, affinities, summoning); //i think i fix it (arrow)
            enterTavern(new_character);

        }

        //iff subclass is mage it will create a new character and set it with their respectives variables

        else if (subclass == "MAGE") {
            Character* new_character = nullptr;
            new_character = new Mage(name, race, vitality, armor, level, enemy, school_o_faction, main, summoning);
            enterTavern(new_character);
        }

        //iff subclass is barbarian it will create a new character and set it with their respectives variables

        else if (subclass == "BARBARIAN") {
            Character* new_character = nullptr;
            new_character = new Barbarian(name, race, vitality, armor, level, enemy, main, offhand, enraged);
            enterTavern(new_character);
        }

        //iff subclass is scoundrel it will create a new character and set it with their respectives variables

        else if (subclass == "SCOUNDREL") {
            Character* new_character = nullptr;
            new_character = new Scoundrel(name, race, vitality, armor, level, enemy, main, school_o_faction, disguise);
            enterTavern(new_character);
        }

        affinities.clear();
        arrow.clear();

    }

    fin.close();

}

/*
    @post: For every character in the tavern, displays each character's information
*/

void Tavern::displayCharacters() {

    for (int i = 0; i < item_count_;i++) {
        items_[i]->display();
    }

}

/*
    @param: a string reference to a race
    @post: For every character in the tavern of the given race (only exact matches to the input string), displays each character's information
*/

void Tavern::displayRace(const std::string& race) {

    int curr_index = 0;

    while (curr_index < item_count_) {

        if (items_[curr_index]->getRace() == race) {

            items_[curr_index]->display();

        }
        curr_index++;

    }

}

/*
    @post: Every character in the tavern eats a tainted stew.
*/

void Tavern::taintedStew() {

    int curr_index = 0;

    while (curr_index < item_count_) {

        items_[curr_index]->eatTaintedStew();
        curr_index++;

    }

}

/** 
    @param:   A reference to a Character entering the Tavern
    @return:  returns true if a Character was successfully added to items_, false otherwise
    @post:    adds Character to the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::enterTavern(Character* a_character)
{

  if(add(a_character))
  {
    level_sum_ += a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_++;
     
    return true;
  }
  else
  {
    return false;
  }
}

/** @param:   A reference to a Character leaving the Tavern  
    @return:  returns true if a character was successfully removed from items_, false otherwise
    @post:    removes the character from the Tavern and updates the level sum and the enemy count if the character is an enemy.
**/
bool Tavern::exitTavern(Character* a_character)
{
  if(remove(a_character))
  {
    level_sum_ -= a_character->getLevel();
    if(a_character->isEnemy())
      num_enemies_--;
      
    return true;
  }
  return false;
}



/** 
    @return:  The integer level count of all the characters currently in the Tavern
**/
int Tavern::getLevelSum()
{
   return level_sum_;
}



/** 
    @return:  The average level of all the characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the average level of the Tavern rounded to the NEAREST integer, and returns the integer value.
**/
int Tavern::calculateAvgLevel()
{
   return (level_sum_>0) ? round(double(level_sum_) / item_count_) : 0.0;

}



/** 
    @return:  The integer enemy count of the Tavern
    **/
    int Tavern::getEnemyCount()
    {
      return num_enemies_;
    }



/** 
    @return:  The percentage (double) of all the enemy characters in the Tavern
    @post:    Considers every character currently in the Tavern, updates the enemy percentage of the Tavern rounded to 2 decimal places, and returns the double value.
**/
double Tavern::calculateEnemyPercentage()
{
  double enemy_percent = (num_enemies_>0) ?  (double(num_enemies_) / item_count_) * 100: 0.0;
  return std::ceil(enemy_percent*100.0) / 100.0; //round up to to decimal places
 
}


/** 
    @param:   A string reference to a race 
    @return:  An integer tally of the number of characters in the Tavern of the given race
**/
int Tavern::tallyRace(const std::string &race)
{
  int frequency = 0;
  int curr_index = 0;   
  while (curr_index < item_count_)
  {
    if (items_[curr_index]->getRace() == race)
    {
      frequency++;
    } 

    curr_index++; 
  }

  return frequency;
}


/**
  @post:    Outputs a report of the characters currently in the tavern in the form:
  "Humans: [x] \nElves: [x] \nDwarves: [x] \nLizards: [x] \nUndead: [x] \n\nThe average level is: [x] \n[x]% are enemies.\n\n"

  Example output: 
  Humans: 5
  Elves: 8
  Dwarves: 3
  Lizards: 7
  Undead: 2

  The average level is: 16
  24% are enemies.
*/
void Tavern::tavernReport()
{
  int humans = tallyRace("HUMAN");
  int elves = tallyRace("ELF");
  int dwarves = tallyRace("DWARF");
  int lizards = tallyRace("LIZARD");
  int undead = tallyRace("UNDEAD");
  
  std::cout << "Humans: " << humans << std::endl;
  std::cout << "Elves: " << elves << std::endl;
  std::cout << "Dwarves: " << dwarves << std::endl;
  std::cout << "Lizards: " << lizards << std::endl;
  std::cout << "Undead: " << undead << std::endl;
  std::cout << "\nThe average level is: " << calculateAvgLevel() << std::endl;
  std::cout << std::fixed << std::setprecision(2) << calculateEnemyPercentage() << "% are enemies.\n\n";
}


