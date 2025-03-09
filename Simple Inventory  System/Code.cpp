#include <iostream>
#include <map>
#include <fstream>
#include <thread>
#include <mutex>
#include <limits>

std::mutex inventoryMutex; // Mutex for thread safety

class Inventory {
    std::map<std::string, int> items;

public:
    void addItem(const std::string &name, int quantity) {
        std::lock_guard<std::mutex> lock(inventoryMutex);
        items[name] += quantity;
        std::cout << "✅ Added " << quantity << " of " << name << "\n";
    }

    void removeItem(const std::string &name, int quantity) {
        std::lock_guard<std::mutex> lock(inventoryMutex);
        if (items.find(name) == items.end()) {
            throw std::runtime_error("❌ Item not found!");
        }
        if (items[name] < quantity) {
            throw std::runtime_error("❌ Not enough stock!");
        }
        items[name] -= quantity;
        std::cout << "✅ Removed " << quantity << " of " << name << "\n";
    }

    void displayInventory() {
        std::lock_guard<std::mutex> lock(inventoryMutex);
        std::cout << "\n📦 Current Inventory:\n";
        for (auto &item : items) {
            std::cout << " - " << item.first << ": " << item.second << "\n";
        }
        std::cout << "-------------------------\n";
    }

    void saveToFile() {
        std::lock_guard<std::mutex> lock(inventoryMutex);
        std::ofstream file("inventory.txt");
        for (auto &item : items) {
            file << item.first << " " << item.second << "\n";
        }
        file.close();
        std::cout << "📂 Inventory saved to file.\n";
    }

    void loadFromFile() {
        std::lock_guard<std::mutex> lock(inventoryMutex);
        std::ifstream file("inventory.txt");
        std::string name;
        int quantity;
        while (file >> name >> quantity) {
            items[name] = quantity;
        }
        file.close();
        std::cout << "📂 Inventory loaded from file.\n";
    }
};

// Function to handle user input in a separate thread
void userInputThread(Inventory &inventory) {
    while (true) {
        std::cout << "\n📌 Choose an option:\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Remove Item\n";
        std::cout << "3. Display Inventory\n";
        std::cout << "4. Save & Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 4) {
            inventory.saveToFile();
            break;
        }

        std::string name;
        int quantity;
        std::cout << "Enter item name: ";
        std::cin >> name;
        std::cout << "Enter quantity: ";
        std::cin >> quantity;

        try {
            switch (choice) {
                case 1:
                    inventory.addItem(name, quantity);
                    break;
                case 2:
                    inventory.removeItem(name, quantity);
                    break;
                case 3:
                    inventory.displayInventory();
                    break;
                default:
                    std::cout << "❌ Invalid choice! Try again.\n";
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << "\n";
        }
    }
}

int main() {
    Inventory inventory;
    inventory.loadFromFile();

    std::thread userThread(userInputThread, std::ref(inventory));
    userThread.join();

    return 0;
}
