#ifndef PHARMACY_H
#define PHARMACY_H

#include <iostream>
#include <string>
using namespace std;

struct Medicine
{
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

struct ListNode
{
    Medicine data;
    ListNode* next;

    ListNode(Medicine med) {
        data = med;
        next = nullptr;
    }
};

struct SaleRecord
{
    int medicineId;
    string medicineName;
    int qtySold;
    double totalCost;
};

struct StackNode
{
    SaleRecord data;
    StackNode* next;

    StackNode(SaleRecord record) {
        data = record;
        next = nullptr;
    }
};

class MedicineList
{
private:
    ListNode* head;
    int count;
    int nextId;

public:
    MedicineList();

    bool addMedicine(string name, string category, double price, int quantity);
    bool deleteMedicine(int id);
    bool sellMedicine(int id, int qty, SaleRecord& record);
    bool restoreStock(int id, int qty);

    ListNode* searchById(int id);
    ListNode* searchByName(string name);

    void displayAll();

    bool isEmpty();
    int getCount();
};

class SaleStack
{
private:
    StackNode* top;

public:
    SaleStack();

    void push(SaleRecord record);
    bool pop(SaleRecord& record);
    bool isEmpty();

    void displaySales();
};

class PharmacySystem
{
private:
    MedicineList inventory;
    SaleStack saleHistory;

public:
    void run();
};

#endif
