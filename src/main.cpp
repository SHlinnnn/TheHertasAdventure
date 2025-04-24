#include "GameSystem.h"
#include "FileManager.h"
#include <iostream>

void showMainMenu() {
    std::cout << "\n======== 大黑塔的冒险 ========\n"
              << "1. 新的旅程\n"
              << "2. 继续冒险\n"
              << "3. 离开游戏\n"
              << "请选择: ";
}

Path selectPath() {
    int choice;
    std::cout << "\n=== 选择命途 ===\n"
              << "1. 丰饶 - 生命加成\n"
              << "2. 毁灭 - 攻击加成\n"
              << "3. 巡猎 - 速度加成\n"
              << "请选择: ";
    std::cin >> choice;
    return static_cast<Path>(choice - 1);
}

int main() {
    GameSystem game;
    
    try {
        while (true) {
            showMainMenu();
            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            if (choice == 1) {
                int diff;
                std::cout << "\n=== 选择难度 ===\n"
                          << "1. 简单\n2. 普通\n3. 困难\n选择: ";
                std::cin >> diff;
                
                Path path = selectPath();
                game.startGame(static_cast<Difficulty>(diff - 1));
                game.getPlayer()->chosenPath = path;
                game.mainLoop();
                
            } else if (choice == 2) {
                std::string filename;
                std::cout << "输入存档文件名: ";
                std::cin >> filename;
                
                int stage;
                if (FileManager::loadGame(*game.getPlayer(), stage, filename)) {
                    game.setCurrentStage(stage);
                    game.mainLoop();
                } else {
                    std::cerr << "存档加载失败！\n";
                }
                
            } else if (choice == 3) {
                break;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "发生错误: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
