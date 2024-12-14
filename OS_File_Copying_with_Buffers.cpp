#include <iostream>
#include <fstream>
#include <string>

using namespace std;
bool isFile(string a);
bool isNumber(string s);

int main(int argc, char* argv[]) {

    if (argc < 3 || argc > 5) // checks amount of parameters
    {
        cout << "ERROR CODE 1: Invalid Parameters";
        return -1;
    }

    if (isFile(argv[1])) // source file ?
    {
        ifstream iFile;
        string file = argv[1];
        iFile.open(file);
        if (!iFile) {
            std::cout << "404: File Not Found";
            return -1;
        }

        if (argc == 3) // if <src> <dest>
        {
            string output = argv[2];
            if (!isFile(output)) // if no output file exists, create one
            {
                ofstream oFile(output);
                if (!oFile) {
                    std::cout << "404: File Not Found";
                    return -1;
                }

                string line;
                getline(iFile, line);
                oFile << line;

                iFile.close();
                oFile.close();
                cout << "Done! (<src> <dest>)";
                return 0;
            }
            else // open existing file
            {
                fstream oFile;
                oFile.open(output);
                if (!oFile) {
                    std::cout << "404: File Not Found";
                    return -1;
                }

                string line;
                getline(iFile, line);
                oFile << line; // copy over elements of input file

                iFile.close();
                oFile.close();
                cout << "Done! (<src> <dest>)";
                return 0;
            }
        }
        if (argc == 4)
        {
            if (isNumber(argv[2]) && !isNumber(argv[3])) // if <src> <off> <dest>
            {
                int x = stoi(argv[2]);
                string output = argv[3];
                if (!isFile(output))
                {
                    ofstream oFile(output);
                    if (!oFile) {
                        std::cout << "404: File Not Found";
                        return -1;
                    }

                    iFile.seekg(x);
                    string line;
                    getline(iFile, line);
                    oFile << line;

                    iFile.close();
                    oFile.close();
                    cout << "Done! (<src> <src_off> <dest>)";
                    return 0;
                }
                else
                {
                    fstream oFile;
                    oFile.open(output);
                    if (!oFile) {
                        std::cout << "404: File Not Found";
                        return -1;
                    }

                    iFile.seekg(x);
                    string line;
                    getline(iFile, line);
                    oFile << line;

                    iFile.close();
                    oFile.close();
                    cout << "Done! (<src> <src_off> <dest>)";
                    return 0;
                }
            }
            else if (isNumber(argv[3]) && !isNumber(argv[2])) // if <src> <dest> <off>
            {
                int x = stoi(argv[3]);
                string output = argv[2];
                if (!isFile(output))
                {
                    ofstream oFile(output);
                    if (!oFile) {
                        std::cout << "404: File Not Found";
                        return -1;
                    }

                    oFile.seekp(x);
                    string line;
                    getline(iFile, line);

                    oFile << line;

                    iFile.close();
                    oFile.close();
                    cout << "Done! (<src> <dest> <dest_off>)";
                    return 0;
                }
                else
                {
                    fstream oFile;
                    oFile.open(output);
                    if (!oFile) {
                        std::cout << "404: File Not Found";
                        return -1;
                    }

                    oFile.seekp(x);
                    string line;
                    getline(iFile, line);
                    oFile << line;

                    iFile.close();
                    oFile.close();
                    cout << "Done! (<src> <dest> <dest_off>)";
                    return 0;
                }
            }
            else
            {
                cout << "ERROR CODE 3: Invalid Parameters for (<src> <src_off> <dest>) or (<src> <dest> <dest_off>)";
                return -1;
            }
        }
        if (argc == 5)
        {
            if (isNumber(argv[2]) && !isNumber(argv[3]) && isNumber(argv[4])) // if <src> <off> <dest> <off>
            {
                int x = stoi(argv[2]);
                int y = stoi(argv[4]);
                string output = argv[3];
                if (!isFile(output))
                {
                    ofstream oFile(output);
                    if (!oFile) {
                        std::cout << "404: File Not Found";
                        return -1;
                    }

                    iFile.seekg(x);
                    oFile.seekp(y);
                    string line;
                    getline(iFile, line);
                    oFile << line;

                    iFile.close();
                    oFile.close();
                    cout << "Done! (<src> <src_off> <dest> <dest_off>)";
                    return 0;
                }
                else
                {
                    fstream oFile;
                    oFile.open(output);
                    if (!oFile) {
                        std::cout << "404: File Not Found";
                        return -1;
                    }

                    iFile.seekg(x);
                    oFile.seekp(y);
                    string line;
                    getline(iFile, line);
                    oFile << line;

                    iFile.close();
                    oFile.close();
                    cout << "Done! (<src> <src_off> <dest> <dest_off>)";
                    return 0;
                }
            }
            else
            {
                cout << "ERROR CODE 4: Invalid Parameters for (<src> <src_off> <dest> <dest_off>)";
                return -1;
            }
        }
        return 0;
    }
    else cout << "ERROR CODE 5: Input file not found";
    return -1;
}

bool isFile(string s) // checks if output file exists
{
    ifstream all(s);
    return all.good();
}

bool isNumber(string s) // checks if offset is valid number
{
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        if (!isdigit(s[i])) return false;
    }
    return true;
}
