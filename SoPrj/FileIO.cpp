#include "FileIO.h"

void FileIO::save(Date* date_data) {
    // File structure
    // File descriptor
    // Date count(366-constant variable)
    // Date (20200101)
    // Schedule count;
    // Schedule
    // Schedule keyword
    // Schedule content

    // Date again(iterated)

    ofstream outfile("userInfo");
    string tmp = "";

    // File Descriptor
    outfile << "This is T3 from SoPrj\n";
    outfile << max << "\n";

    for (int i = 0; i < max; i++) {
        // Date
        tmp.append(date_data[i].getDate() + "\n");
        
        // Schedule count
        tmp.append(date_data[i].getSchedules().size() + "\n");

        // Schedule
        for (int a = 0; a < date_data[i].getSchedules().size(); a++) {
            // Schedule keyword
            tmp.append(date_data[i].getSchedules().at(a).getKeyword() + "\n");
            // Schedule content
            tmp.append(date_data[i].getSchedules().at(a).getContent() + "\n");
        }
    }
    tmp = encryptString(tmp);

    // save string data to file
    outfile << tmp << endl;
}

void FileIO::load(Date* date_data) {
    ifstream inputFile("userInput");
    if (!(inputFile.is_open())) {
        return; // File dose not exists.
    }
    string tmpEncoded; // File to string storation directory

    // Allocate memory dynamically
    inputFile.seekg(0, ios::end);
    tmpEncoded.reserve(inputFile.tellg());
    inputFile.seekg(0, ios::beg);

    tmpEncoded.assign((std::istreambuf_iterator<char>(inputFile)),
        std::istreambuf_iterator<char>());

    // Decrypt String first.
    tmpEncoded = decryptString(tmpEncoded);

    // Save decrypted string to file
    ofstream outputTmp("userInputTMP");
    outputTmp << tmpEncoded;
    outputTmp.close(); // close

    // Class should be created by now. Skipping nullptr check.

    // Open decrypted file
    string tmp;
    ifstream fileDecrypted("userInputTMP");

    // Check File descriptor
    getline(fileDecrypted, tmp);
    if (tmp == "This is T3 from SoPrj") {
        // This is correct file
    } else {
        // that kinda thing does not exists
        return;
    }

    // Assume descriptor is Correct.
    for (int i = 0; i < max; i++) {
        // Date determination - do we need this?
        // Anyway. flush away buffer since its in string data;
        getline(fileDecrypted, tmp); // Ahhh handling needed if something happens

        // Schedule count --> Reserve
        getline(fileDecrypted, tmp);
        int schedule_count = atoi(tmp.c_str());
        date_data[i].getSchedules().reserve(schedule_count);

        // Schedule
        for (int a = 0; a < schedule_count; a++) {
            // Schedule keyword
            getline(fileDecrypted, tmp);
            date_data[i].getSchedules().at(a).setKeyword(tmp);

            // Schedule content
            getline(fileDecrypted, tmp);
            date_data[i].getSchedules().at(a).setContent(tmp);
        }
    }

    remove("userInputTMP");
}

string FileIO::decryptString(string encoded) {
    string decoded = "";
    for (int i = 0; i < encoded.length(); i++) {
        decoded += encoded.at(i) - key;
    }

    return decoded;
}

string FileIO::encryptString(string decoded) {
    // let's say string contains "test"
    string encoded = "";

    for (int i = 0; i < decoded.length(); i++) {
        encoded += decoded.at(i) + key;
    }

    return encoded;
}