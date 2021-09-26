

#include "parkingLot.h"
#include<bits/stdc++.h>

using namespace std;

std::vector<std::string> readLines(const std::string &filename)
{
    std::vector<std::string> lines;
    std::ifstream input(filename);
    std::string line;
    while (std::getline(input, line))
    {
        lines.push_back(line);
    }
    return lines;
}
void tokenize(string &str, char delim, vector<string> &out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    freopen("output.txt", "w", stdout);
    vector<string>inp = readLines("input.txt");
    ParkingLot p;
    p.setRegistrationNumberPattern("^[A-Z][A-Z]-[0-9][0-9]-[A-Z][A-Z]-[0-9][0-9][0-9][0-9]$");
    for (auto inputString : inp)
    {
        vector<string>inpF;
        cout << inputString;
        tokenize(inputString, ' ', inpF);
        string s = inpF[0];
        if (s == "Create_parking_lot")
        {
            int n = stoi(inpF[1]);
            p.setSize(n);
        }
        else if (s == "Park")
        {
            string reg = inpF[1];
            string t = inpF[2];
            if (t != "driver_age")
            {
                cout << "Invalid Command!\n";
                continue;
            }
            int age = stoi(inpF[3]);
            if (!p.addCar(reg, age))
            {
                continue;
            }
        }
        else if (s == "Slot_numbers_for_driver_of_age")
        {
            int age = stoi(inpF[1]);
            string ans = p.getAllSlotNumbersByAge(age);
            cout << ans << "\n";
        }
        else if (s == "Slot_number_for_car_with_number")
        {
            string reg = inpF[1];
            int slot = p.getSlotNumberByRegId(reg);
            if (slot == -1)cout << "Invalid registration id\n";
            else
                cout << slot << endl;
        }
        else if (s == "Leave")
        {
            int slot = stoi(inpF[1]);
            p.removeCar(slot);
        }
        else if (s == "Vehicle_registration_number_for_driver_of_age")
        {
            int age = stoi(inpF[1]);
            string ans = p.getAllRegNumbersByAge(age);
            cout << ans << endl;
        }
        else if (s == "exit")
        {
            break;
        }
        else
        {
            cout << "Some invalid command entered!\n";
        }

    }


    return 0;
}