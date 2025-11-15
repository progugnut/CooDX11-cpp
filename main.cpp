#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits> // Required for std::numeric_limits

// Helper to clear input buffer after numerical reads
void clear_input_buffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Function to display the editor menu
void display_menu() {
    std::cout << "\n--- 🐦 Coodx11 Command Line Editor ---" << std::endl;
    std::cout << "1. Start/Continue Editing" << std::endl;
    std::cout << "2. **Save Document**" << std::endl;
    std::cout << "3. Load Document" << std::endl;
    std::cout << "4. Exit Editor" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

// Function to handle saving the document
void save_document(const std::string& filename, const std::vector<std::string>& content) {
    // std::ofstream opens the file for writing. If the file exists, it is overwritten.
    std::ofstream outfile(filename);

    if (outfile.is_open()) {
        for (const auto& line : content) {
            // Write each line of text followed by a newline character
            outfile << line << "\n";
        }
        outfile.close(); // Close the file stream
        std::cout << "\n[SUCCESS] Document saved successfully to: **" << filename << "**\n";
    }
    else {
        std::cerr << "\n[ERROR] Unable to open or create file for saving: " << filename << "\n";
        std::cerr << "Check file permissions or the path.\n";
    }
}

// Function to handle loading the document
std::vector<std::string> load_document(const std::string& filename) {
    std::vector<std::string> content;
    std::ifstream infile(filename);
    std::string line;

    if (infile.is_open()) {
        while (std::getline(infile, line)) {
            content.push_back(line);
        }
        infile.close();
        std::cout << "\n[SUCCESS] Document loaded from: **" << filename << "**\n";
    }
    else {
        std::cerr << "\n[ERROR] Unable to open file for loading: " << filename << "\n";
    }
    return content;
}

// Function to start the editing session
void start_editing(std::vector<std::string>& content) {
    std::cout << "\n*** START EDITING ***\n";
    std::cout << "Current Content (" << content.size() << " lines):\n";
    for (size_t i = 0; i < content.size(); ++i) {
        std::cout << (i + 1) << ": " << content[i] << std::endl;
    }

    std::cout << "\nType your new lines below. Type **'EOF'** on a new line to finish and return to the menu.\n";

    std::string line;
    // We already cleared the buffer after menu selection, so we can start reading lines.
    while (std::getline(std::cin, line)) {
        if (line == "EOF") {
            break;
        }
        content.push_back(line);
    }
    std::cout << "\n*** EDITING SESSION ENDED ***\n";
}


int main() {
    std::vector<std::string> document_content;
    int choice;
    std::string filename;

    std::cout << "Welcome to Coodx11 - The Pigeon Editor!\n";

    while (true) {
        display_menu();

        if (!(std::cin >> choice)) {
            // Handle non-integer input
            std::cerr << "\n[ERROR] Invalid input. Please enter a number.\n";
            std::cin.clear();
            clear_input_buffer();
            continue;
        }

        // Clear buffer AFTER reading the choice, before any subsequent line reading
        clear_input_buffer();

        switch (choice) {
        case 1:
            start_editing(document_content);
            break;

        case 2:
            std::cout << "Enter filename (e.g., my_notes.txt): ";
            std::getline(std::cin, filename); // Use getline for filename in case of spaces
            save_document(filename, document_content);
            break;

        case 3:
            std::cout << "Enter filename to load: ";
            std::getline(std::cin, filename);
            document_content = load_document(filename);
            break;

        case 4:
            std::cout << "Coodx11 closing. Coo coo!\n";
            return 0;

        default:
            std::cout << "\n[INFO] Invalid choice. Please select 1-4.\n";
            break;
        }
    }
    return 0;
}
