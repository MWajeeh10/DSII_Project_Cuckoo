#include "MovieDatabase.hpp"

void MovieDatabase::LoadMoviesFromCsv(const string &csv_file)
{
    ifstream file(csv_file);
    if (!file.is_open())
    {
        cerr << "Error opening file " << csv_file << endl;
        return;
    }
    string line;

    std::getline(file, line); // Skip header
    while (std::getline(file, line))
    {
        stringstream ss(line);
        MovieEntry entry;
        std::getline(ss, entry.Name, ',');
        ss >> entry.Rating;
        ss.ignore();
        ss >> entry.RatingCount;
        ss.ignore();
        std::getline(ss, entry.ReleaseDate, ',');
        std::getline(ss, entry.Budget, ',');
        std::getline(ss, entry.DomesticGross, ',');
        std::getline(ss, entry.DomesticGross2, ',');
        std::getline(ss, entry.DomesticWeekendGross, ',');
        std::getline(ss, entry.DomesticWeekend, ',');
        std::getline(ss, entry.DomesticWeekendDate, ',');
        std::getline(ss, entry.WorldwideGross);

        entries.push_back(entry);
    }
    file.close();
}

void MovieDatabase::PrintMovieEntries()
{
    for (const auto &entry : entries)
    {
        std::cout << "Name: " << entry.Name << "\n";
        std::cout << "Rating: " << entry.Rating << "\n";
        std::cout << "Rating Count: " << entry.RatingCount << "\n";
        std::cout << "Release Date: " << entry.ReleaseDate << "\n";
        std::cout << "Budget: " << entry.Budget << "\n";
        std::cout << "Domestic Gross: " << entry.DomesticGross << "\n";
        std::cout << "Domestic Gross 2: " << entry.DomesticGross2 << "\n";
        std::cout << "Domestic Weekend Gross: " << entry.DomesticWeekendGross << "\n";
        std::cout << "Domestic Weekend: " << entry.DomesticWeekend << "\n";
        std::cout << "Domestic Weekend Date: " << entry.DomesticWeekendDate << "\n";
        std::cout << "Worldwide Gross: " << entry.WorldwideGross << "\n\n";
    }
}



