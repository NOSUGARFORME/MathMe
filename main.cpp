#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include "FunctionSettings.cpp"

using namespace std;

void clear_screen()
{
#ifdef WINDOWS
    std::system("cls");
#else
    std::system ("clear");
#endif
}

void viewLoadedFunctions(std::vector<FunctionSettings<double>> & functions) {
    for(auto & function : functions){
        cout << function.expression_string << endl;
    }
}

FunctionSettings<double> splitToFunctionObject(const string& s, const string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        if (token.empty()) {
            throw std::invalid_argument( "Input string is doesn't current" );
        }
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));

    // TODO: handle errors
    if (res.size() != 5) {
        throw std::invalid_argument( "Input string is doesn't current" );
    }

    FunctionSettings<double> obj = FunctionSettings<double>(
            res[0],
            res[1],
            std::stod(res[2]),
            std::stod(res[3]),
            std::stod(res[4])
            );
    return obj;
}

bool getFunctionsFromPath(const std::string& fileName, std::vector<FunctionSettings<double>> & functions)
{
    functions.clear();
    std::ifstream in(fileName.c_str());
    if(!in) {
        std::cerr << "Cannot open the File : "<<fileName<<std::endl;
        return false;
    }

    std::string str;
    while (std::getline(in, str))
    {
        if(!str.empty())
            try {
                functions.push_back(splitToFunctionObject(str, "|"));
            }
            catch (std::invalid_argument const& ex) {
                std::cerr << ex.what() << " Cannot parse string: " << str << " This line will not be processed." <<std::endl;
            }

    }

    in.close();
    return true;
}

void GoldenSlice(vector<FunctionSettings<double>> & functions) {
    for(auto & function : functions){
        try {
            double res = function.GetMin(function.lower_limit, function.higher_limit);
            cout << fixed << function.expression_string << "  result=" << res << endl;
        } catch(std::invalid_argument const& e) {
            cout << function.expression_string << " throws exception " << e.what() << endl;
        }
    }
}

int main() {
    clear_screen();
    int choice = -1;
    bool isLoaded = false;
    
    std::vector<FunctionSettings<double>> functions;
    while (choice != 0) {
        std::cout << "1 - Load functions from existing file\n";
        if (isLoaded) {
            std::cout << "2 - View loaded functions\n";
            std::cout << "3 - Find extremum\n";
        }
        std::cout << "9 - Info\n";
        std::cout << "0 - Exit\n";

        std::cout << "Your choice: ";
        std::cin >> choice;
        clear_screen();

        switch (choice)
        {
            case 1: {
                string path;
                cout << "Write a path: ";
                cin >> path;
                cout << endl;

                bool result = getFunctionsFromPath(path, functions);
                if (result) isLoaded = true;
                else isLoaded = false;
                break;
            }
            case 2:
                viewLoadedFunctions(functions);
                break;
            case 3: {
                GoldenSlice(functions);
                break;
            }
            case 9: {
                cout << "2023c Ivan Bolsun" << endl;
                break;
            }
            default:
                std::cout << "Not a Valid Choice. \n";
                std::cout << "Choose again.\n";
                break;
        }
    }
    return 0;
}
