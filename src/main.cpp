#include "GameSystem.h"  
#include "FileManager.h"  
#include <iostream>  
#include <limits>  

void clearInput();  
void clearInput() {  
    std::cin.clear();  
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  
}  

Path selectPath() {  
    while (true) {  
        std::cout << "\nChoose Path:\n"  
                  << "1. Abundance (HP +50%)\n"  
                  << "2. Destruction (ATK +50%)\n"  
                  << "3. Hunt (SPD +50%)\n"  
                  << "Choice: ";  
        int choice;  
        if (std::cin >> choice && choice >= 1 && choice <= 3) {  
            return static_cast<Path>(choice - 1);  
        }  
        clearInput();  
    }  
}  

Difficulty selectDifficulty() {  
    while (true) {  
        std::cout << "\nChoose Difficulty:\n"  
                  << "1. Easy\n"  
                  << "2. Normal\n"  
                  << "3. Hard\n"  
                  << "Choice: ";  
        int choice;  
        if (std::cin >> choice && choice >= 1 && choice <= 3) {  
            return static_cast<Difficulty>(choice - 1);  
        }  
        clearInput();  
    }  
}  

int main() {  
    try {  
        Player* player = nullptr;  
          
        while (true) {  
            std::cout << "\n===== The Fantasy Adventure of Dark Tower =====\n"  
                      << "1. New Game\n"  
                      << "2. Load Save\n"  
                      << "3. Exit\n"  
                      << "Choice: ";  
              
            int choice;  
            if (!(std::cin >> choice)) {  
                clearInput();  
                continue;  
            }  

            if (choice == 1) {  
                auto diff = selectDifficulty();  
                auto path = selectPath();  
                player = new Player(path, diff);  
                break;  
            } else if (choice == 2) {  
                std::string filename;  
                std::cout << "Enter save filename: ";  
                std::cin >> filename;  
                player = new Player(Path::ABUNDANCE, Difficulty::EASY);  
                if (FileManager::load(*player, filename)) {  
                    GameSystem game(player);  
                    game.run();  
                    break;  
                }  
                delete player;  
                std::cerr << "Load failed!\n";  
            } else if (choice == 3) {  
                return 0;  
            }  
        }  

        if (player != nullptr) {  
            GameSystem game(player);  
            game.run();  
            delete player;  
        }  
    } catch (const std::exception& e) {  
        std::cerr << "Error: " << e.what() << std::endl;  
        return 1;  
    }  
    return 0;  
}  
