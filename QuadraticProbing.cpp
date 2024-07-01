#include "QuadraticProbing.h"
#include<bits/stdc++.h>
using namespace std;

class BankAccount {
public:
    std::string id;
    int balance;
    bool active;

    BankAccount() : id(""), balance(0), active(false) {}
    BankAccount(const std::string& id, int balance)
        : id(id), balance(balance), active(true) {}
};

class BankingSystem {
private:
    std::vector<BankAccount> table;
    int capacity;
    int size;

    int hashFunction(const std::string& id) {
        std::hash<std::string> hashFunc;
        return hashFunc(id) % capacity;
    }

    int findSlot(const std::string& id) {
        int index = hashFunction(id);
        int i = 0;

        while (table[index].active && table[index].id != id) {
            i++;
            index = (index + i * i) % capacity;
            if (i >= capacity) return -1; // Table is full
        }
        return index;
    }

public:
    BankingSystem(int cap) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    void createAccount(const std::string& id, int initialBalance) {
        int index = findSlot(id);
        if (index != -1 && !table[index].active) {
            table[index] = BankAccount(id, initialBalance);
            size++;
        }
    }

    int getBalance(const std::string& id) {
        int index = findSlot(id);
        if (index != -1 && table[index].active) {
            return table[index].balance;
        }
        return -1;
    }

    void addTransaction(const std::string& id, int amount) {
        int index = findSlot(id);
        if (index != -1) {
            if (!table[index].active) {
                if (amount >= 0) {
                    table[index] = BankAccount(id, amount);
                    size++;
                }
            } else {
                if (table[index].balance + amount >= 0) {
                    table[index].balance += amount;
                }
            }
        }
    }

    std::vector<int> getTopBalances(int k) {
        std::vector<int> balances;
        for (const auto& account : table) {
            if (account.active) {
                balances.push_back(account.balance);
            }
        }
        std::sort(balances.rbegin(), balances.rend());
        if (balances.size() > k) balances.resize(k);
        return balances;
    }

    bool accountExists(const std::string& id) {
        int index = findSlot(id);
        return index != -1 && table[index].active;
    }

    int totalAccounts() {
        return size;
    }

    bool deleteAccount(const std::string& id) {
        int index = findSlot(id);
        if (index != -1 && table[index].active) {
            table[index].active = false;
            size--;
            return true;
        }
        return false;
    }
};

int main() {
    BankingSystem bank(10);

    bank.createAccount("123ABC", 1000);
    bank.addTransaction("123ABC", 200);
    bank.addTransaction("456DEF", 500);
    bank.addTransaction("123ABC", -300);

    std::cout << "Balance of 123ABC: " << bank.getBalance("123ABC") << std::endl;
    std::cout << "Top 2 balances: ";
    for (int balance : bank.getTopBalances(2)) {
        std::cout << balance << " ";
    }
    std::cout << std::endl;
    std::cout << "Account 456DEF exists: " << bank.accountExists("456DEF") << std::endl;
    std::cout << "Total accounts: " << bank.totalAccounts() << std::endl;
    std::cout << "Deleting account 123ABC: " << bank.deleteAccount("123ABC") << std::endl;
    std::cout << "Account 123ABC exists: " << bank.accountExists("123ABC") << std::endl;

    return 0;
}

