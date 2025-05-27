//Text-Based Adventure Game
//This program simulates a simple text-based adventure game where the player can explore rooms, collect items, and interact with objects.
#include <iostream>
#include <string>
using namespace std;

class AnimeAdventureGame {
private:
    string playerName;
    string characterClass;

    void intro() {
        cout << "Welcome, young warrior...\n";
        cout << "Enter your name: ";
        getline(cin, playerName);
        cout << "\nGreetings, " << playerName << ". The fate of Neo-Tokyo rests in your hands.\n";
        cout << "Before we begin, choose your class:\n";
        cout << "1. Spirit Mage\n";
        cout << "2. Swordmaster\n";
        cout << "3. Demon Hunter\n";
        cout << "4. Cyber Ninja\n";
        cout << "5. Alchemist\n";
        cout << "Choose your class (1-5): ";
        int choice;
        cin >> choice;

        if (choice == 1)
            characterClass = "Spirit Mage";
        else if (choice == 2)
            characterClass = "Swordmaster";
        else if (choice == 3)
            characterClass = "Demon Hunter";
        else if (choice == 4)
            characterClass = "Cyber Ninja";
        else if (choice == 5)
            characterClass = "Alchemist";
        else
            characterClass = "Spirit Mage";

        cout << "You have chosen: " << characterClass << ". Your journey begins...\n";
    }

    void crossroads() {
        int choice;
        cout << "\nThe city of Neo-Tokyo is in turmoil. The Dark Shogun's forces are invading.\n";
        cout << "You stand at a crossroads, with options to save the city.\n";
        cout << "1. Enter the Spirit Shrine to seek guidance from the ancient spirits.\n";
        cout << "2. Join forces with the underground rebellion to fight the Shogun's soldiers.\n";
        cout << "3. Seek out the mysterious blacksmith who forged the legendary sword of fate.\n";
        cout << "4. Visit the Hidden Temple to unlock the secrets of the Dark Shogun's power.\n";
        cout << "5. Travel to the demon-infested mountains to seek advice from the Demon King.\n";
        cout << "6. Find the sacred Oracle who can predict the outcome of the coming battle.\n";
        cout << "7. Visit the high-tech city lab to enhance your powers with cybernetic implants.\n";
        cout << "8. Seek out the legendary Alchemist who can create potions to aid in your journey.\n";
        cout << "Choose your path (1-8): ";
        cin >> choice;

        switch (choice) {
            case 1:
                spiritShrine();
                break;
            case 2:
                rebellionPath();
                break;
            case 3:
                blacksmithPath();
                break;
            case 4:
                hiddenTemplePath();
                break;
            case 5:
                demonKingPath();
                break;
            case 6:
                oraclePath();
                break;
            case 7:
                cityLabPath();
                break;
            case 8:
                alchemistPath();
                break;
            default:
                cout << "Invalid choice. The world is in chaos, and you're still lost.\n";
                crossroads();
        }
    }

    void spiritShrine() {
        cout << "\nYou arrive at the Spirit Shrine, surrounded by glowing cherry blossoms.\n";
        cout << "An old monk greets you, offering you the Spirit Stone.\n";
        cout << "Do you accept the stone to gain spiritual power? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "The Spirit Stone imbues you with ancient powers, unlocking the ability to control the elements.\n";
        } else {
            cout << "You walk away, but the spirits' whispers haunt you forever.\n";
        }
    }

    void rebellionPath() {
        cout << "\nYou join the underground rebellion, led by the fierce Captain Haru.\n";
        cout << "The rebels are preparing for a massive assault on the Dark Shogun's army.\n";
        cout << "Do you lead the charge? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "With your leadership, the rebellion successfully breaks the enemy's lines!\n";
        } else {
            cout << "You wait in the shadows, but the battle turns in the rebels' favor anyway.\n";
        }
    }

    void blacksmithPath() {
        cout << "\nYou visit the blacksmith, an enigmatic man who never speaks.\n";
        cout << "He forges a powerful sword capable of slaying the Dark Shogun. The blade is covered in ancient runes.\n";
        cout << "Do you accept the sword? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "The sword glows with a blue aura, ready to strike down any evil.\n";
        } else {
            cout << "You leave the sword behind, but the Shogun's minions ambush you later.\n";
        }
    }

    void hiddenTemplePath() {
        cout << "\nYou enter the Hidden Temple, a dark place shrouded in mystery.\n";
        cout << "You encounter a powerful sorceress who reveals the secret to defeating the Dark Shogun.\n";
        cout << "Do you trust the sorceress and accept her offer? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "The sorceress gives you the Forbidden Spell that can break the Dark Shogun's shield.\n";
        } else {
            cout << "You leave, but the Dark Shogun’s forces get stronger without your help.\n";
        }
    }

    void demonKingPath() {
        cout << "\nYou travel to the Demon King's lair, a fiery mountain full of peril.\n";
        cout << "The Demon King offers you his power to fight the Dark Shogun.\n";
        cout << "Do you accept the Demon King's offer? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "You gain incredible strength and dark powers, but at what cost?\n";
        } else {
            cout << "You refuse his offer, but you gain the respect of the demon army.\n";
        }
    }

    void oraclePath() {
        cout << "\nYou seek the Oracle, who resides in the tallest tower of Neo-Tokyo.\n";
        cout << "The Oracle offers a prophecy that foretells the outcome of the battle.\n";
        cout << "Do you believe the prophecy and prepare accordingly? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "The prophecy guides you to victory against the Dark Shogun!\n";
        } else {
            cout << "You ignore the Oracle's warning, but a twist of fate still grants you victory.\n";
        }
    }

    void cityLabPath() {
        cout << "\nYou visit the high-tech city lab, where scientists enhance warriors with cybernetic implants.\n";
        cout << "The scientist offers to augment your physical abilities with advanced technology.\n";
        cout << "Do you accept the cybernetic enhancements? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "The enhancements grant you superhuman strength and speed, making you a force to be reckoned with!\n";
        } else {
            cout << "You leave the lab, but the lack of enhancements makes the upcoming battle harder.\n";
        }
    }

    void alchemistPath() {
        cout << "\nYou seek the legendary Alchemist who lives deep in the forest.\n";
        cout << "The Alchemist offers to brew powerful potions to aid in your journey.\n";
        cout << "Do you drink the potions to increase your strength and agility? (y/n): ";
        char choice;
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            cout << "The potions increase your power, but they come with dangerous side effects.\n";
        } else {
            cout << "You refuse the potions, relying on your own strength to face the challenges ahead.\n";
        }
    }

public:
    void start() {
        intro();
        crossroads();
        cout << "\nThe battle against the Dark Shogun has been decided. Thank you for playing, " << playerName << "!\n";
    }
};

int main() {
    AnimeAdventureGame game;
    game.start();
    return 0;
}
