# Banking System with Hashmap Collision Resolution

This project is a C++ implementation of a banking system using a hashmap with various collision resolution strategies. The system allows for the creation and management of bank accounts, handling transactions, and retrieving account information efficiently.

## Features

- **Account Creation:** Create new bank accounts with a unique ID and an initial balance.
- **Balance Retrieval:** Check the balance of a specific account using its ID.
- **Transaction Processing:** Add transactions to accounts, including deposits and withdrawals.
- **Top K Balances:** Retrieve the top K account balances.
- **Account Existence Check:** Verify if an account exists in the database.
- **Total Accounts:** Get the total number of accounts currently stored.
- **Account Deletion:** Delete accounts from the database.

## Technologies Used

- **C++**: Core programming language used for implementing the banking system.
- **Hashmap with Collision Resolution**: Data structure used for efficient storage and retrieval of account information.
    - **Linear Probing**
    - **Quadratic Probing**
    - **Cubic Probing**
    - **Chaining**

## Collision Resolution Strategies

### Linear Probing

Linear probing is used to resolve collisions by linearly probing the next available slot in the hashmap when a collision occurs.

### Quadratic Probing

Quadratic probing resolves collisions by probing the next available slot using a quadratic function. This helps in reducing clustering issues compared to linear probing.

### Cubic Probing

Cubic probing introduces a more sophisticated approach by using cubic increments to find the next available slot. This technique aims to distribute data evenly and mitigate clustering issues.

### Chaining

Chaining handles collisions by creating linked lists at each hash table index. Each list manages all accounts that share the same hash code, ensuring data remains organized and accessible even during collisions.

## Implementation Details

### Hash Function

A simple hash function is used to compute the hash value for a given account ID. The hash value is then used to determine the index in the hashmap where the account information is stored.

### Key Functions

- **createAccount**: Creates a new account with a given ID and initial balance.
- **getTopKBalances**: Retrieves the top K balances from the database.
- **getBalance**: Returns the current balance of a specified account.
- **addTransaction**: Adds a transaction to a specified account.
- **accountExists**: Checks if an account with a given ID exists in the database.
- **totalAccounts**: Returns the total number of accounts in the database.
- **deleteAccount**: Deletes an account from the database.

## Code Overview

Here's an example implementation using quadratic probing. Other probing techniques can be implemented similarly by modifying the probing function.

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

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
        hash<string> hasher;
        return hasher(id) % capacity;
    }

    int quadraticProbe(int hashValue, const string& id, int i) {
        return (hashValue + i * i) % capacity;
    }

public:
    BankDatabase(int cap) : capacity(cap) {
        table.resize(capacity, make_pair("", 0));
        size = 0;
    }

    void createAccount(const string& id, int initialBalance) {
        int hashValue = hashFunction(id);
        int i = 0;
        int index = quadraticProbe(hashValue, id, i);

        while (!table[index].first.empty() && table[index].first != id) {
            i++;
            index = quadraticProbe(hashValue, id, i);
        }

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
        int i = 0;
        int index = quadraticProbe(hashValue, id, i);

        while (!table[index].first.empty() && table[index].first != id) {
            i++;
            index = quadraticProbe(hashValue, id, i);
        }

        if (table[index].first == id) {
            return table[index].second;
        }
        return -1;
    }

    void addTransaction(const string& id, int amount) {
        int hashValue = hashFunction(id);
        int i = 0;
        int index = quadraticProbe(hashValue, id, i);

        while (!table[index].first.empty() && table[index].first != id) {
            i++;
            index = quadraticProbe(hashValue, id, i);
        }

        if (table[index].first.empty()) {
            table[index] = make_pair(id, amount);
            size++;
        } else {
            table[index].second += amount;
        }
    }

    bool accountExists(const string& id) {
        int hashValue = hashFunction(id);
        int i = 0;
        int index = quadraticProbe(hashValue, id, i);

        while (!table[index].first.empty() && table[index].first != id) {
            i++;
            index = quadraticProbe(hashValue, id, i);
        }

        return table[index].first == id;
    }

    int totalAccounts() {
        return size;
    }

    bool deleteAccount(const string& id) {
        int hashValue = hashFunction(id);
        int i = 0;
        int index = quadraticProbe(hashValue, id, i);

        while (!table[index].first.empty() && table[index].first != id) {
            i++;
            index = quadraticProbe(hashValue, id, i);
        }

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
```
## How to run
	1.	Clone the repository or download the source code files.
	2.	Compile the code using a C++ compiler. For example, using g++:

 ```bash
g++ -o BankSystem BankSystem.cpp
```
	3.	Run the executable:
 ```bash
./BankSystem
```
