#include<bits/stdc++.h>
using namespace std;
class ParkingLot
{
private:
    map<int, set<int>> mapAgeToSlots;
    map<int, string> mapSlotToRegNumber;
    priority_queue<int, vector<int>, greater<int>> slots; // min heap
    string registrationPattern;
    bool checkRegistrationNumber(string reg_number)
    {
        regex reg(registrationPattern);
        return regex_match(reg_number, reg);
    }

    int findAge(int slot_number)
    {
        for(auto it : mapAgeToSlots)
        {
            for(auto it2 : it.second)
            {
                if(it2 == slot_number)
                {
                    return it.first;
                }
            }
        }
        return -1;
    }
public:
    ParkingLot() {}
    void setSize(int size)
    {
        // fill slots in priority queue
        for(int i = 0; i < size; i++)
        {
            slots.push(i + 1);
            mapSlotToRegNumber[i + 1] = "";
        }
        cout << "Created parking of " << size << " slots\n";
    }
    void setRegistrationNumberPattern(string patternRegex)
    {
        registrationPattern = patternRegex;
    }
    bool addCar(string reg_number, int age)
    {
        if(slots.empty())
        {
            cout << "Car cannnot be parked as no space is available!\n";
            return 0;
        }
        if(!checkRegistrationNumber(reg_number))
        {
            cout << "Invalid Registration Number provided!\n";
            return 0;
        }
        int slotAssigned = slots.top();
        slots.pop();
        // Map slot and registration number
        mapSlotToRegNumber[slotAssigned] = reg_number;
        // Map slot to age
        mapAgeToSlots[age].insert(slotAssigned);

        cout << "Car with vehicle registration number \"" << reg_number << "\" has been parked at slot number " << slotAssigned << endl;
        return 1;
    }
    void removeCar(int slot_number)
    {
        // check if slot is assigned already
        if(mapSlotToRegNumber[slot_number] == "")
        {
            cout << "Empty slot provided!\n";
        }
        int age = findAge(slot_number);
        for(auto regs : mapAgeToSlots)
        {
            auto it = regs.second.find(slot_number);
            if(it != regs.second.end())
            {
                cout << "Slot number " << slot_number << " vacated, the car with vehicle registration number \"" << mapSlotToRegNumber[slot_number] << "\" left the space, the driver of the car was of age " << age << "\n";
                regs.second.erase(slot_number);
            }
        }
        mapSlotToRegNumber[slot_number] = "";
        slots.push(slot_number);
    }
    string getAllSlotNumbersByAge(int age)
    {
        string ans = "";
        for(auto slot : mapAgeToSlots[age])
        {
            ans += to_string(slot) + ",";
        }
        if(ans.size())
            ans.pop_back();
        return ans;
    }
    int getSlotNumberByRegId(string reg_number)
    {
        if(!checkRegistrationNumber(reg_number))return -1;
        for(auto reg_pair : mapSlotToRegNumber)
        {
            if(reg_number == reg_pair.second)
            {
                return reg_pair.first;
            }
        }
        return -1;
    }
    string getAllRegNumbersByAge(int age)
    {
        string ans = "";
        for(auto slot : mapAgeToSlots[age])
        {
            ans += mapSlotToRegNumber[slot] + ",";
        }
        if(ans.size())
            ans.pop_back();
        return ans;
    }
};
