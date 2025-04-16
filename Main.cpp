#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ===== Base Ticket Class =====
class Ticket {
protected:
    string movieName;
    double basePrice;
public:
    Ticket(string movie, double price) : movieName(movie), basePrice(price) {}
    virtual double calculatePrice() = 0;
    virtual void showTicketInfo() = 0;
    virtual ~Ticket() {}
};

// ===== Standard Ticket =====
class StandardTicket : public Ticket {
public:
    StandardTicket(string movie) : Ticket(movie, 150.0) {}
    double calculatePrice() override {
        return basePrice;
    }
    void showTicketInfo() override {
        cout << "Standard Ticket - Movie: " << movieName << " | Price: Rs." << calculatePrice() << endl;
    }
};

// ===== Premium Ticket =====
class PremiumTicket : public Ticket {
public:
    PremiumTicket(string movie) : Ticket(movie, 150.0) {}
    double calculatePrice() override {
        return basePrice + 100.0;
    }
    void showTicketInfo() override {
        cout << "Premium Ticket - Movie: " << movieName << " | Price: Rs." << calculatePrice() << endl;
    }
};

// ===== Base Customer Class =====
class Customer {
protected:
    string name;
public:
    Customer(string n) : name(n) {}
    virtual void bookTicket(Ticket* ticket) = 0;
    virtual ~Customer() {}
};

// ===== Regular Customer =====
class RegularCustomer : public Customer {
public:
    RegularCustomer(string n) : Customer(n) {}
    void bookTicket(Ticket* ticket) override {
        cout << "Regular Customer: " << name << " booked ";
        ticket->showTicketInfo();
    }
};

// ===== VIP Customer =====
class VIPCustomer : public Customer {
public:
    VIPCustomer(string n) : Customer(n) {}
    void bookTicket(Ticket* ticket) override {
        cout << "VIP Customer: " << name << " booked ";
        double price = ticket->calculatePrice() * 0.8;
        cout << "VIP Discounted Price: Rs." << price << endl;
    }
};

// ===== Booking System =====
class BookingSystem {
private:
    vector<Ticket*> tickets;
public:
    void createBooking(Customer* customer, Ticket* ticket) {
        tickets.push_back(ticket);
        customer->bookTicket(ticket);
    }

    ~BookingSystem() {
        for (auto ticket : tickets) {
            delete ticket;
        }
    }
};

// ===== Main Function =====
int main() {
    BookingSystem system;

    int numBookings;
    cout << "Enter number of bookings: ";
    cin >> numBookings;

    for (int i = 0; i < numBookings; ++i) {
        string customerType, name, ticketType, movie;
        cout << "\nBooking " << i + 1 << ":\n";

        cout << "Enter customer type (Regular/VIP): ";
        cin >> customerType;

        cout << "Enter customer name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter ticket type (Standard/Premium): ";
        cin >> ticketType;

        cout << "Enter movie name: ";
        cin.ignore();
        getline(cin, movie);

        Customer* customer = nullptr;
        if (customerType == "Regular" || customerType == "regular")
            customer = new RegularCustomer(name);
        else if (customerType == "VIP" || customerType == "vip")
            customer = new VIPCustomer(name);
        else {
            cout << "Invalid customer type. Skipping booking.\n";
            continue;
        }

        Ticket* ticket = nullptr;
        if (ticketType == "Standard" || ticketType == "standard")
            ticket = new StandardTicket(movie);
        else if (ticketType == "Premium" || ticketType == "premium")
            ticket = new PremiumTicket(movie);
        else {
            cout << "Invalid ticket type. Skipping booking.\n";
            delete customer;
            continue;
        }

        system.createBooking(customer, ticket);
        delete customer; // Only ticket is managed by system
    }

    return 0;
}