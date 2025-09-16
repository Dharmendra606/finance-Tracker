

       #include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct Vehicle {
    string licensePlate;
    string ownerName;
    int parkingSpot;
};

class ParkingLot {
private:
    int capacity;
    vector<Vehicle> parkedVehicles;
    vector<bool> spots;  // true if spot is taken

public:
    ParkingLot(int cap) : capacity(cap), spots(cap, false) {}

    void parkVehicle() {
        if (parkedVehicles.size() >= capacity) {
            cout << "Parking lot is full! Cannot park more vehicles.\n";
            return;
        }

        string plate, owner;
        cout << "Enter vehicle license plate: ";
        cin >> plate;
        cout << "Enter owner's name: ";
        cin.ignore();
        getline(cin, owner);

        // Find first free spot
        int spot = -1;
        for (int i = 0; i < capacity; i++) {
            if (!spots[i]) {
                spot = i;
                break;
            }
        }

        if (spot == -1) {
            cout << "No free parking spots available!\n";
            return;
        }

        Vehicle v{plate, owner, spot + 1};
        parkedVehicles.push_back(v);
        spots[spot] = true;

        cout << "Vehicle parked at spot #" << v.parkingSpot << endl;
    }

    void removeVehicle() {
        if (parkedVehicles.empty()) {
            cout << "Parking lot is empty!\n";
            return;
        }

        string plate;
        cout << "Enter license plate of vehicle to remove: ";
        cin >> plate;

        bool found = false;
        for (auto it = parkedVehicles.begin(); it != parkedVehicles.end(); ++it) {
            if (it->licensePlate == plate) {
                spots[it->parkingSpot - 1] = false;
                parkedVehicles.erase(it);
                cout << "Vehicle removed from the parking lot.\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Vehicle not found in the parking lot.\n";
        }
    }

    void displayStatus() {
        cout << "\nParking Lot Status (" << parkedVehicles.size() << "/" << capacity << " occupied):\n";
        if (parkedVehicles.empty()) {
            cout << "No vehicles parked currently.\n";
            return;
        }
        cout << left << setw(10) << "Spot#" << setw(15) << "License" << setw(20) << "Owner" << endl;
        cout << "------------------------------------------\n";
        for (const auto& v : parkedVehicles) {
            cout << setw(10) << v.parkingSpot << setw(15) << v.licensePlate << setw(20) << v.ownerName << endl;
        }
    }
};

int main() {
    int capacity;
    cout << "Enter parking lot capacity: ";
    cin >> capacity;

    ParkingLot lot(capacity);

    int choice;
    do {
        cout << "\n--- Smart Parking Lot Management ---\n";
        cout << "1. Park Vehicle\n";
        cout << "2. Remove Vehicle\n";
        cout << "3. Display Parking Status\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                lot.parkVehicle();
                break;
            case 2:
                lot.removeVehicle();
                break;
            case 3:
                lot.displayStatus();
                break;
            case 4:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }
    } while(choice != 4);

    return 0;
}
