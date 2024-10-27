#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_ROOMS = 100;       // Maximum number of rooms
const int MAX_BOOKINGS = 100;    // Maximum number of bookings

// Room structure to store room details
struct Room {
    int roomId;
    string roomType;
    bool isAvailable;
};
int stringToInt(const std::string& str) {
    int num;
    std::stringstream ss(str);
    ss >> num;
    return num;
}
// Booking structure to store booking details
struct Booking {
    int bookingId;
    string guestName;
    int roomId;
    string checkInDate;
    string checkOutDate;
};

// Function to load rooms from a file
int loadRooms(Room rooms[], const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error opening rooms file.\n";
        return 0;
    }

    string line, token;
    int count = 0;
    while (getline(file, line) && count < MAX_ROOMS) {
        stringstream ss(line);
        getline(ss, token, ','); rooms[count].roomId = stringToInt(token);
        getline(ss, token, ','); rooms[count].roomType = token;
        getline(ss, token, ','); rooms[count].isAvailable = (token == "1");
        count++;
    }
    file.close();
    return count;  // Return the number of rooms loaded
}

// Function to save rooms to a file
void saveRooms(Room rooms[], int roomCount, const string& filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error opening rooms file.\n";
        return;
    }

    for (int i = 0; i < roomCount; i++) {
        file << rooms[i].roomId << "," << rooms[i].roomType << ","
             << (rooms[i].isAvailable ? "1" : "0") << "\n";
    }
    file.close();
}

// Function to load bookings from a file
int loadBookings(Booking bookings[], const string& filename) {
    ifstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error opening bookings file.\n";
        return 0;
    }

    string line, token;
    int count = 0;
    while (getline(file, line) && count < MAX_BOOKINGS) {
        stringstream ss(line);
        getline(ss, token, ','); bookings[count].bookingId = stringToInt(token);
        getline(ss, token, ','); bookings[count].guestName = token;
        getline(ss, token, ','); bookings[count].roomId = stringToInt(token);
        getline(ss, token, ','); bookings[count].checkInDate = token;
        getline(ss, token, ','); bookings[count].checkOutDate = token;
        count++;
    }
    file.close();
    return count;  // Return the number of bookings loaded
}

// Function to save bookings to a file
void saveBookings(Booking bookings[], int bookingCount, const string& filename) {
    ofstream file(filename.c_str());
    if (!file.is_open()) {
        cerr << "Error opening bookings file.\n";
        return;
    }

    for (int i = 0; i < bookingCount; i++) {
        file << bookings[i].bookingId << "," << bookings[i].guestName << ","
             << bookings[i].roomId << "," << bookings[i].checkInDate << ","
             << bookings[i].checkOutDate << "\n";
    }
    file.close();
}

// Function to add a new room
void addRoom(Room rooms[], int &roomCount, const string& filename) {
    if (roomCount >= MAX_ROOMS) {
        cout << "Room limit reached.\n";
        return;
    }

    Room newRoom;
    cout << "Enter Room ID: ";
    cin >> newRoom.roomId;
    cin.ignore();
    cout << "Enter Room Type (Single/Double/Suite): ";
    getline(cin, newRoom.roomType);
    newRoom.isAvailable = true;

    rooms[roomCount++] = newRoom;
    saveRooms(rooms, roomCount, filename);
    cout << "Room added successfully.\n";
}

// Function to book a room
void bookRoom(Room rooms[], int roomCount, Booking bookings[], int &bookingCount,
              const string& roomFile, const string& bookingFile) {
    if (bookingCount >= MAX_BOOKINGS) {
        cout << "Booking limit reached.\n";
        return;
    }

    int roomId;
    cout << "Enter Room ID to book: ";
    cin >> roomId;
    cin.ignore();

    bool roomFound = false;
    for (int i = 0; i < roomCount; i++) {
        if (rooms[i].roomId == roomId && rooms[i].isAvailable) {
            roomFound = true;
            rooms[i].isAvailable = false;

            Booking newBooking;
            newBooking.bookingId = bookingCount + 1;
            cout << "Enter Guest Name: ";
            getline(cin, newBooking.guestName);
            newBooking.roomId = roomId;
            cout << "Enter Check-in Date (YYYY-MM-DD): ";
            getline(cin, newBooking.checkInDate);
            cout << "Enter Check-out Date (YYYY-MM-DD): ";
            getline(cin, newBooking.checkOutDate);

            bookings[bookingCount++] = newBooking;
            saveRooms(rooms, roomCount, roomFile);
            saveBookings(bookings, bookingCount, bookingFile);
            cout << "Room booked successfully.\n";
            break;
        }
    }
    if (!roomFound) {
        cout << "Room not found or already booked.\n";
    }
}

// Function to view all bookings
void viewBookings(const Booking bookings[], int bookingCount) {
    if (bookingCount == 0) {
        cout << "No bookings available.\n";
        return;
    }
    for (int i = 0; i < bookingCount; i++) {
        cout << "Booking ID: " << bookings[i].bookingId << ", Guest: " << bookings[i].guestName
             << ", Room ID: " << bookings[i].roomId << ", Check-in: " << bookings[i].checkInDate
             << ", Check-out: " << bookings[i].checkOutDate << "\n";
    }
}

// Function to cancel a booking
void cancelBooking(Room rooms[], int roomCount, Booking bookings[], int &bookingCount,
                   const string& roomFile, const string& bookingFile) {
    int bookingId;
    cout << "Enter Booking ID to cancel: ";
    cin >> bookingId;

    bool bookingFound = false;
    for (int i = 0; i < bookingCount; i++) {
        if (bookings[i].bookingId == bookingId) {
            bookingFound = true;
            int roomId = bookings[i].roomId;
            for (int j = 0; j < roomCount; j++) {
                if (rooms[j].roomId == roomId) {
                    rooms[j].isAvailable = true;
                    break;
                }
            }
            // Remove booking by shifting elements
            for (int k = i; k < bookingCount - 1; k++) {
                bookings[k] = bookings[k + 1];
            }
            bookingCount--;
            saveRooms(rooms, roomCount, roomFile);
            saveBookings(bookings, bookingCount, bookingFile);
            cout << "Booking cancelled successfully.\n";
            break;
        }
    }
    if (!bookingFound) {
        cout << "Booking ID not found.\n";
    }
}

int main() {
    Room rooms[MAX_ROOMS];
    Booking bookings[MAX_BOOKINGS];
    int roomCount = loadRooms(rooms, "rooms.txt");
    int bookingCount = loadBookings(bookings, "bookings.txt");

    int choice;
    do {
        cout << "\n--- Hotel Management System ---\n";
        cout << "1. Add New Room\n";
        cout << "2. Book Room\n";
        cout << "3. View All Bookings\n";
        cout << "4. Cancel Booking\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addRoom(rooms, roomCount, "rooms.txt");
                break;
            case 2:
                bookRoom(rooms, roomCount, bookings, bookingCount, "rooms.txt", "bookings.txt");
                break;
            case 3:
                viewBookings(bookings, bookingCount);
                break;
            case 4:
                cancelBooking(rooms, roomCount, bookings, bookingCount, "rooms.txt", "bookings.txt");
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}