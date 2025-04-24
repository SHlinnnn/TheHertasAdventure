#include "GameSystem.h"
#include "FileManager.h"
#include <iostream>
#include <limits>

// 输入验证辅助函数
template<typename T>
T getValidInput(const std::string& prompt, T min, T max) {
    T value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= min && value <= max) {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "无效输入，请重新输入 (" << min << "-" << max << ")\n";
    }
    return value;
}

int main() {
    try {
        GameSystem game;
        
        // 主界面
        std::cout << "\n======== 星穹铁道：赫塔的冒险 ========\n";
        const int choice = getValidInput<int>(
            "1. 新旅程\n2. 继续冒险\n3. 离开\n选择: ", 1, 3);

        if (choice == 1) {
            const int diff = getValidInput<int>(
                "\n=== 选择命途难度 ===\n"
                "1. 简单（适合新人）\n"
                "2. 普通（平衡体验）\n"
                "3. 困难（星神挑战）\n"
                "选择: ", 1, 3);
            
            game.startGame(static_cast<Difficulty>(diff-1));
            
            // 命途选择
            const int pathChoice = getValidInput<int>(
                "\n=== 选择命途 ===\n"
                "1. 丰饶（生命加成）\n"
                "2. 毁灭（攻击加成）\n"
                "3. 巡猎（速度加成）\n"
                "选择: ", 1, 3);
            
            game.selectPath(static_cast<Path>(pathChoice-1));
        }
        else if (choice == 2) {
            std::string filename;
            std::cout << "输入存档文件名: ";
            std::cin >> filename;
            
            int loadedStage = 0;
            if (!FileManager::loadGame(game.getPlayer(), loadedStage, filename)) {
                throw std::runtime_error("无法加载存档文件");
            }
            game.setCurrentStage(loadedStage);
        }
        else {
            return 0;
        }

        game.mainLoop();

        // 自动存档提示
        if (game.shouldAutoSave()) {
            FileManager::saveGame(game.getPlayer(), 
                                  game.getCurrentStage(), 
                                  "autosave.dat");
            std::cout << "进度已自动保存至 autosave.dat\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "\n错误发生: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
