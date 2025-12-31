#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cctype>

using namespace std;

class StringMatchingChatbot {
private:
    map<string, string> responses;
    string responsesFile;

    // Convert string to lowercase
    string toLower(const string& str) {
        string lowerStr = str;
        transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

    // Brute Force string matching algorithm
    int bruteForceMatch(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();

        for (int i = 0; i <= n - m; i++) {
            int j = 0;
            while (j < m && text[i + j] == pattern[j]) {
                j++;
            }
            if (j == m) {
                return i; // pattern found at index i
            }
        }
        return -1; // pattern not found
    }

    // Compute Longest Prefix Suffix (LPS) array for KMP algorithm
    vector<int> computeLPS(const string& pattern) {
        int m = pattern.length();
        vector<int> lps(m, 0);
        int length = 0; // length of the previous longest prefix suffix
        int i = 1;

        while (i < m) {
            if (pattern[i] == pattern[length]) {
                length++;
                lps[i] = length;
                i++;
            } else {
                if (length != 0) {
                    length = lps[length - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
        return lps;
    }

    // Knuth-Morris-Pratt (KMP) string matching algorithm
    int kmpMatch(const string& text, const string& pattern) {
        int n = text.length();
        int m = pattern.length();

        if (m == 0) return 0;

        vector<int> lps = computeLPS(pattern);
        int i = 0; // index for text
        int j = 0; // index for pattern

        while (i < n) {
            if (pattern[j] == text[i]) {
                i++;
                j++;

                if (j == m) {
                    return i - j; // pattern found at index i-j
                }
            } else {
                if (j != 0) {
                    j = lps[j - 1];
                } else {
                    i++;
                }
            }
        }
        return -1; // pattern not found
    }

public:
    StringMatchingChatbot(const string& filename = "responses.txt") : responsesFile(filename) {
        loadResponses();
    }

    // Load responses from file
    void loadResponses() {
        ifstream file(responsesFile);
        if (!file.is_open()) {
            cout << "Warning: " << responsesFile << " not found. Using default responses." << endl;
            setDefaultResponses();
            return;
        }

        string line;
        while (getline(file, line)) {
            size_t colonPos = line.find(':');
            if (colonPos != string::npos) {
                string keyword = line.substr(0, colonPos);
                string response = line.substr(colonPos + 1);
                responses[toLower(keyword)] = response;
            }
        }
        file.close();
    }

    // Set default responses if file is not found
    void setDefaultResponses() {
        responses["hello"] = "Hello! How can I help you today?";
        responses["hi"] = "Hi there! What can I do for you?";
        responses["how are you"] = "I'm just a chatbot, but I'm functioning well!";
        responses["bye"] = "Goodbye! Have a great day!";
        responses["thanks"] = "You're welcome!";
        responses["name"] = "I'm a simple string matching chatbot.";
        responses["help"] = "I can respond to greetings, questions about my name, and more. Just try talking to me!";
        responses["weather"] = "I don't have access to real-time weather data. Sorry!";
        responses["time"] = "I don't have a clock, but you can check your device for the time.";
    }

    // Save responses to file
    void saveResponses() {
        ofstream file(responsesFile);
        if (!file.is_open()) {
            cout << "Error: Could not open file for writing." << endl;
            return;
        }

        for (const auto& pair : responses) {
            file << pair.first << ":" << pair.second << endl;
        }
        file.close();
        cout << "Responses saved to " << responsesFile << endl;
    }

    // Find the best matching keyword in the user input
    string findBestMatch(const string& userInput, const string& algorithm = "kmp") {
        string lowerInput = toLower(userInput);
        string bestKeyword;
        int bestMatchLength = 0;

        for (const auto& pair : responses) {
            const string& keyword = pair.first;
            int matchPos = -1;

            if (algorithm == "kmp") {
                matchPos = kmpMatch(lowerInput, keyword);
            } else {
                matchPos = bruteForceMatch(lowerInput, keyword);
            }

            if (matchPos != -1) {
                // Prefer longer matches for better accuracy
                if (keyword.length() > bestMatchLength) {
                    bestMatchLength = keyword.length();
                    bestKeyword = keyword;
                }
            }
        }

        return bestKeyword;
    }

    // Get response based on user input
    string getResponse(const string& userInput) {
        // First try with KMP (more efficient)
        string keyword = findBestMatch(userInput, "kmp");

        // If no match found with KMP, try with brute force
        if (keyword.empty()) {
            keyword = findBestMatch(userInput, "brute");
        }

        if (!keyword.empty()) {
            return responses[keyword];
        } else {
            return "I'm not sure how to respond to that. Can you try asking something else?";
        }
    }

    // Add a new keyword-response pair
    void addResponse(const string& keyword, const string& response) {
        responses[toLower(keyword)] = response;
        cout << "Added response for '" << keyword << "'" << endl;
    }

    // Start the chat interaction
    void chat() {
        cout << "Chatbot: Hello! I'm a simple string matching chatbot. Type 'quit' to exit." << endl;

        while (true) {
            cout << "You: ";
            string userInput;
            getline(cin, userInput);

            if (toLower(userInput) == "quit") {
                cout << "Chatbot: Goodbye!" << endl;
                break;
            } else if (toLower(userInput) == "save") {
                saveResponses();
            } else if (toLower(userInput).find("add ") == 0) {
                // Simple way to add new responses: add keyword:response
                size_t spacePos = userInput.find(' ');
                if (spacePos != string::npos) {
                    string rest = userInput.substr(spacePos + 1);
                    size_t colonPos = rest.find(':');
                    if (colonPos != string::npos) {
                        string keyword = rest.substr(0, colonPos);
                        string response = rest.substr(colonPos + 1);
                        addResponse(keyword, response);
                    } else {
                        cout << "Chatbot: To add a response, use: add keyword:response" << endl;
                    }
                }
            } else {
                string response = getResponse(userInput);
                cout << "Chatbot: " << response << endl;
            }
        }
    }
};

// Create a sample responses file if it doesn't exist
void createSampleResponses(const string& filename = "responses.txt") {
    ifstream testFile(filename);
    if (testFile.good()) {
        testFile.close();
        return;
    }

    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not create sample responses file." << endl;
        return;
    }

    file << "hello:Hello! How can I help you today?" << endl;
    file << "hi:Hi there! What can I do for you?" << endl;
    file << "how are you:I'm just a chatbot, but I'm functioning well!" << endl;
    file << "bye:Goodbye! Have a great day!" << endl;
    file << "thanks:You're welcome!" << endl;
    file << "name:I'm a simple string matching chatbot." << endl;
    file << "help:I can respond to greetings, questions about my name, and more. Just try talking to me!" << endl;
    file << "weather:I don't have access to real-time weather data. Sorry!" << endl;
    file << "time:I don't have a clock, but you can check your device for the time." << endl;

    file.close();
    cout << "Created sample responses file: " << filename << endl;
}

int main() {
    // Create sample responses file if it doesn't exist
    createSampleResponses();

    // Initialize and start the chatbot
    StringMatchingChatbot chatbot;
    chatbot.chat();

    return 0;
}
