#include "pharmacy.h"
#include <iomanip>

MedicineList::MedicineList() {
    head = nullptr;
    count = 0;
    nextId = 1001;
}

bool MedicineList::addMedicine(string name, string category, double price, int quantity) {
    if (price < 0 || quantity < 0)
        return false;

    Medicine med;

    med.id = nextId++;
    med.name = name;
    med.category = category;
    med.price = price;
    med.quantity = quantity;

    ListNode* node = new ListNode(med);

    node->next = head;
    head = node;

    count++;

    return true;
}

bool MedicineList::deleteMedicine(int id) {
    if (head == nullptr)
        return false;

    if (head->data.id == id) {
        ListNode* value = head;
        head = head->next;
        delete value;
        count--;
        return true;
    }

    ListNode* current = head;

    while (current->next != nullptr && current->next->data.id != id) {
        current = current->next;
    }

    if (current->next == nullptr)
        return false;

    ListNode* value = current->next;
    current->next = value->next;

    delete value;
    count--;

    return true;
}

ListNode* MedicineList::searchById(int id) {
    ListNode* current = head;

    while (current != nullptr) {
        if (current->data.id == id)
            return current;

        current = current->next;
    }

    return nullptr;
}

ListNode* MedicineList::searchByName(string name) {
    ListNode* current = head;

    while (current != nullptr) {
        if (current->data.name == name)
            return current;

        current = current->next;
    }

    return nullptr;
}

void MedicineList::displayAll() {
    if (head == nullptr) {
        cout << "\nNo medicines available.\n";
        return;
    }

    ListNode* current = head;

    cout << "\n================ MEDICINE LIST ================ \n";

    while (current != nullptr) {
        cout << "ID       : " << current->data.id << endl;
        cout << "Name     : " << current->data.name << endl;
        cout << "Category : " << current->data.category << endl;
        cout << "Price    : $" << fixed << setprecision(2) << current->data.price << endl;
        cout << "Quantity : " << current->data.quantity << endl;
        cout << "-----------------------------------------------\n";

        current = current->next;
    }

    cout << "Total Medicines: " << count << endl;
}

bool MedicineList::sellMedicine(int id, int qty, SaleRecord& record) {
    ListNode* node = searchById(id);

    if (node == nullptr)
        return false;

    if (qty <= 0)
        return false;

    if (node->data.quantity < qty)
        return false;

    node->data.quantity -= qty;

    record.medicineId = id;
    record.medicineName = node->data.name;
    record.qtySold = qty;
    record.totalCost = qty * node->data.price;

    return true;
}

bool MedicineList::restoreStock(int id, int qty) {
    ListNode* node = searchById(id);

    if (node == nullptr)
        return false;

    node->data.quantity += qty;

    return true;
}

bool MedicineList::isEmpty() {
    return head == nullptr;
}

int MedicineList::getCount() {
    return count;
}

SaleStack::SaleStack() {
    top = nullptr;
}

void SaleStack::push(SaleRecord record) {
    StackNode* node = new StackNode(record);

    node->next = top;
    top = node;
}

bool SaleStack::pop(SaleRecord& record) {
    if (top == nullptr)
        return false;

    record = top->data;

    StackNode* value = top;
    top = top->next;

    delete value;

    return true;
}

bool SaleStack::isEmpty() {
    return top == nullptr;
}

void SaleStack::displaySales() {
    if (top == nullptr) {
        cout << "\nNo medicines have been sold yet.\n";
        return;
    }

    StackNode* current = top;

    cout << "\n=============== SOLD MEDICINES =============== \n";

    while (current != nullptr) {
        cout << "Medicine ID   : " << current->data.medicineId << endl;
        cout << "Medicine Name : " << current->data.medicineName << endl;
        cout << "Quantity Sold : " << current->data.qtySold << endl;
        cout << "Total Cost    : $" << fixed << setprecision(2)
             << current->data.totalCost << endl;
        cout << "-----------------------------------------------\n";

        current = current->next;
    }
}

void PharmacySystem::run() {
    int choice;

    do
    {
        cout << "\n============= PHARMACY SYSTEM ============= \n";
        cout << "1. Add Medicine\n";
        cout << "2. Display Medicines\n";
        cout << "3. Search Medicine\n";
        cout << "4. Sell Medicine\n";
        cout << "5. Delete Medicine\n";
        cout << "6. Undo Last Sale\n";
        cout << "7. Display Sold Medicines\n";
        cout << "8. Exit\n";
        cout << "=========================================== \n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
            {
                string name, category;
                double price;
                int quantity;

                cout << "\nMedicine Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Category: ";
                getline(cin, category);

                cout << "Price: ";
                cin >> price;

                cout << "Quantity: ";
                cin >> quantity;

                if (inventory.addMedicine(name, category, price, quantity))
                    cout << "\nMedicine added successfully.\n";
                else
                    cout << "\nFailed to add medicine.\n";

                break;
            }

            case 2:
            {
                inventory.displayAll();
                break;
            }

            case 3:
            {
                int searchChoice;

                cout << "\nSearch by:\n";
                cout << "1. ID\n";
                cout << "2. Name\n";
                cout << "Choice: ";
                cin >> searchChoice;

                ListNode* result = nullptr;

                if (searchChoice == 1) {
                    int id;
                    cout << "Enter Medicine ID: ";
                    cin >> id;

                    result = inventory.searchById(id);
                }
                else if (searchChoice == 2) {
                    string name;
                    cout << "Enter Medicine Name: ";
                    cin.ignore();
                    getline(cin, name);

                    result = inventory.searchByName(name);
                } else {
                    cout << "\nInvalid search choice.\n";
                    break;
                }

                if (result != nullptr) {
                    cout << "\nMedicine Found:\n";
                    cout << "ID       : " << result->data.id << endl;
                    cout << "Name     : " << result->data.name << endl;
                    cout << "Category : " << result->data.category << endl;
                    cout << "Price    : $" << fixed << setprecision(2)
                         << result->data.price << endl;
                    cout << "Quantity : " << result->data.quantity << endl;
                } else {
                    cout << "\nMedicine not found.\n";
                }

                break;
            }
            case 4:
            {
                int id, quantity;

                cout << "\nEnter Medicine ID: ";
                cin >> id;

                cout << "Enter Quantity to Sell: ";
                cin >> quantity;

                SaleRecord record;

                if (inventory.sellMedicine(id, quantity, record)) {
                    saleHistory.push(record);

                    cout << "\nSale completed successfully.\n";
                    cout << "Medicine : " << record.medicineName << endl;
                    cout << "Quantity : " << record.qtySold << endl;
                    cout << "Total    : $" << fixed << setprecision(2)
                         << record.totalCost << endl;
                } else {
                    cout << "\nSale failed. Check ID or available quantity.\n";
                }

                break;
            }

            case 5:
            {
                int id;

                cout << "\nEnter Medicine ID to delete: ";
                cin >> id;

                if (inventory.deleteMedicine(id))
                    cout << "\nMedicine deleted successfully.\n";
                else
                    cout << "\nMedicine not found.\n";

                break;
            }

            case 6:
            {
                SaleRecord record;

                if (saleHistory.pop(record)) {
                    if (inventory.restoreStock(record.medicineId, record.qtySold)) {
                        cout << "\nLast sale undone successfully.\n";
                        cout << "Restored Medicine : " << record.medicineName << endl;
                        cout << "Restored Quantity : " << record.qtySold << endl;
                    } else {
                        cout << "\nCould not restore stock. Medicine may be deleted.\n";
                    }
                } else {
                    cout << "\nNo sales available to undo.\n";
                }

                break;
            }

            case 7:
            {
                saleHistory.displaySales();
                break;
            }

            case 8:
            {
                cout << "\nGoodbye.\n";
                break;
            }

            default:
            {
                cout << "\nInvalid choice. Try again.\n";
            }
        }
    } while (choice != 8);
}
