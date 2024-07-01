#include "LinearProbing.h"
#include<bits/stdc++.h>
using namespace std;

using namespace std;

class Account {
public:
    string id;
    int balance;

    Account(string id, int balance) : id(id), balance(balance) {}
};

class BankDatabase {
private:
    vector<pair<string, int>> table;
    int size;
    int capacity;

    int hashFunction(const string& id) {
        // Simple hash function to compute hash value for the given id
        hash<string> hasher;
        return hasher(id) % capacity;
    }

    int linearProbe(int hashValue, const string& id) {
        // Find the next available slot using linear probing
        int i = hashValue;
        while (!table[i].first.empty() && table[i].first != id) {
            i = (i + 1) % capacity;
        }
        return i;
    }

public:
    BankDatabase(int cap) : capacity(cap) {
        table.resize(capacity, make_pair("", 0));
        size = 0;
    }

    void createAccount(const string& id, int initialBalance) {
        int hashValue = hashFunction(id);
        int index = linearProbe(hashValue, id);

        if (table[index].first.empty()) {
            table[index] = make_pair(id, initialBalance);
            size++;
        } else {
            table[index].second = initialBalance;
        }
    }

    vector<int> getTopKBalances(int k) {
        vector<int> balances;
        for (const auto& entry : table) {
            if (!entry.first.empty()) {
                balances.push_back(entry.second);
            }
        }
        sort(balances.rbegin(), balances.rend());
        if (balances.size() > k) {
            balances.resize(k);
        }
        return balances;
    }

    int getBalance(const string& id) {
        int hashValue = hashFunction(id);
        int index = linearProbe(hashValue, id);

        if (table[index].first == id) {
            return table[index].second;
        }
        return -1;
    }

    void addTransaction(const string& id, int amount) {
        int hashValue = hashFunction(id);
        int index = linearProbe(hashValue, id);

        if (table[index].first.empty()) {
            table[index] = make_pair(id, amount);
            size++;
        } else {
            table[index].second += amount;
        }
    }

    bool accountExists(const string& id) {
        int hashValue = hashFunction(id);
        int index = linearProbe(hashValue, id);

        return table[index].first == id;
    }

    int totalAccounts() {
        return size;
    }

    bool deleteAccount(const string& id) {
        int hashValue = hashFunction(id);
        int index = linearProbe(hashValue, id);

        if (table[index].first == id) {
            table[index] = make_pair("", 0);
            size--;
            return true;
        }
        return false;
    }
};

int main() {
    BankDatabase db(10);

    db.createAccount("A123", 1000);
    db.createAccount("B456", 2000);
    db.addTransaction("A123", 500);
    db.addTransaction("C789", 300);

    cout << "Balance of A123: " << db.getBalance("A123") << endl;
    cout << "Balance of B456: " << db.getBalance("B456") << endl;
    cout << "Balance of C789: " << db.getBalance("C789") << endl;

    vector<int> topBalances = db.getTopKBalances(2);
    cout << "Top balances: ";
    for (int bal : topBalances) {
        cout << bal << " ";
    }
    cout << endl;

    cout << "Account A123 exists: " << db.accountExists("A123") << endl;
    cout << "Account D000 exists: " << db.accountExists("D000") << endl;

    cout << "Total accounts: " << db.totalAccounts() << endl;

    db.deleteAccount("A123");
    cout << "Account A123 exists after deletion: " << db.accountExists("A123") << endl;

    return 0;
}