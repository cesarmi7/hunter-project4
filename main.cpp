#include "Tavern.hpp"

int main() {
    //Tavern tavern;
    Tavern tavern("characters.csv");

    /*Character* char1 = new Barbarian("Bonk", "HUMAN", 11, 5, 5, 1, "MACE", "ANOTHERMACE", 1);
    tavern.enterTavern(char1);
    Character* char2 = new Mage("Spynach","ELF",6,4,4,0,"Illusion","Wand",1);
    tavern.enterTavern(char2);
    Character* char3 = new Ranger("Marrow","UNDEAD",9,4,6,0,{{"WOOD",30},{"FIRE",5}},{"Fire", "Poison"},1);
    tavern.enterTavern(char3);
    Character* char4 = new Scoundrel("Flea","DWARF",6,4,4,1,"adamant","cutpurse",1);
    tavern.enterTavern(char4);*/

    
    //tavern.tavernReport();
    tavern.displayCharacters();
    //tavern.displayRace("HUMAN");
}