#include <bits/stdc++.h>
#include "Chaining.h"
using namespace std;

class BankAccount {
public:
    std::string id;
    int balance;

    BankAccount(const std::string& id, int balance) : id(id), balance(balance) {}
};

class BankingSystem {
private:
    std::vector<std::list<BankAccount>> table;
    int capacity;
    int size;

    int hashFunction(const std::string& id) {
        std::hash<std::string> hashFunc;
        return hashFunc(id) % capacity;
    }

    typename std::list<BankAccount>::iterator findAccount(const std::string& id, int index) {
        return std::find_if(table[index].begin(), table[index].end(),
                            [&id](const BankAccount& account) { return account.id == id; });
    }

public:
    BankingSystem(int cap) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    void createAccount(const std::string& id, int initialBalance) {
        int index = hashFunction(id);
        auto it = findAccount(id, index);

        if (it == table[index].end()) {
            table[index].emplace_back(id, initialBalance);
            size++;
        }
    }

    int getBalance(const std::string& id) {
        int index = hashFunction(id);
        auto it = findAccount(id, index);

        if (it != table[index].end()) {
            return it->balance;
        }
        return -1;
    }

    void addTransaction(const std::string& id, int amount) {
        int index = hashFunction(id);
        auto it = findAccount(id, index);

        if (it == table[index].end()) {
            if (amount >= 0) {
                createAccount(id, amount);
            }
        } else {
            if (it->balance + amount >= 0) {
                it->balance += amount;
            }
        }
    }

    std::vector<int> getTopBalances(int k) {
        std::vector<int> balances;
        for (const auto& chain : table) {
            for (const auto& account : chain) {
                balances.push_back(account.balance);
            }
        }
        std::sort(balances.rbegin(), balances.rend());
        if (balances.size() > k) balances.resize(k);
        return balances;
    }

    bool accountExists(const std::string& id) {
        int index = hashFunction(id);
        return findAccount(id, index) != table[index].end();
    }

    int totalAccounts() {
        return size;
    }

    bool deleteAccount(const std::string& id) {
        int index = hashFunction(id);
        auto it = findAccount(id, index);

        if (it != table[index].end()) {
            table[index].erase(it);
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
