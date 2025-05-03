#include "GameSystem.h"
#include "FileManager.h"
#include <iostream>
#include <limits>
void clearInput();
void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

- player = new Player(Path::ABUNDANCE, EASY); // 临时对象
+ player = new Player(Path::ABUNDANCE, Difficulty::EASY); // 带作用域
Path selectPath() {
    while (true) {
        std::cout << "\n选择命途:\n"
                  << "1. 丰饶（生命+50%）\n"
                  << "2. 毁灭（攻击+50%）\n"
                  << "3. 巡猎（速度+50%）\n"
                  << "选择: ";
        int choice;
        if (std::cin >> choice && choice >= 1 && choice <= 3) {
            return static_cast<Path>(choice - 1);
        }
        clearInput();
    }
}

Difficulty selectDifficulty() {
    while (true) {
        std::cout << "\n选择难度:\n"
                  << "1. 简单\n"
                  << "2. 普通\n"
                  << "3. 困难\n"
                  << "选择: ";
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
            std::cout << "\n===== 大黑塔的奇幻冒险 =====\n"
                      << "1. 新游戏\n"
                      << "2. 加载存档\n"
                      << "3. 退出\n"
                      << "选择: ";
            
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
                std::cout << "输入存档文件名: ";
                std::cin >> filename;
                player = new Player(Path::ABUNDANCE, Difficulty::EASY); // 临时对象
                if (FileManager::load(*player, filename)) {
                    GameSystem game(player);
                    game.run();
                    break;
                }
                delete player;
                std::cerr << "加载失败！\n";
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
        std::cerr << "发生错误: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
