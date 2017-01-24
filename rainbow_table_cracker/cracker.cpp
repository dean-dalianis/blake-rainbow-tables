#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include "info.h"
#include "hash\hash.h"
#include "reduce\reduction_function.h"

using namespace std;

string analyse_chain(string, string);

int main(int argc, char **argv){
	/************ LOAD RAINBOW TABLE ************/
	string my_hash = "";
	string in = outputPath;
	in.append(fileName);
	ifstream read(in);
	unordered_map<string, string> rbt;
	string pass, hash;
	while (read >> pass >> hash) {
		rbt[hash] = pass;
	}
	read.close();
	cout << rbt.size() <<" entries loaded.\n"<< endl;
	/*********************************************/

	bool found = false;
	while (true){
		std::cout << "\nGive a hash" << endl;
		cin >> my_hash;

		if (my_hash == "end")
			return 0;

		unordered_map<string, string>::const_iterator it = rbt.find(my_hash);

		if (it != rbt.end()){
			// hash found in rainbow table endings
			string result = analyse_chain(rbt[my_hash], my_hash);
			cout << "Password: " << result << endl;
		}
		else{
			// hash not found, start reduce & hash operations
			bool found = false;
			int c = chainLen - 1;

			for (int i = 0; i < chainLen; i++) {
				string temp_hash = my_hash;

				// string to bitsequence hash
				BitSequence bmy_hash[64];
				int hex;
				for (int x = 0; x < 32; ++x){
					sscanf(temp_hash.c_str(), "%02x", &hex);
					temp_hash.erase(0, 2);
					bmy_hash[x] = (unsigned char)hex;
				}

				char temp_pass[7];

				for (int j = c; j < chainLen - 1; j++){
					// reduce
					char *ptemp_pass = reduction_function256(bmy_hash, j);
					strcpy(temp_pass, ptemp_pass);
					temp_pass[6] = '\0';
					// char* to bitsequence pass
					BitSequence bpass[6];
					for (int x = 0; x < 6; x++){
						bpass[x] = temp_pass[x];
					}

					// hash
					BitSequence * bhash = hash_blake256(bpass);
					for (int l = 0; l < 64; l++){
						bmy_hash[l] = bhash[l];
					}
					// bitsequence to string hash
					string shashed = "";
					char temp[2];
					for (int j = 0; j < 32; j++) {
						sprintf(temp, "%02x", bmy_hash[j]);
						shashed.append(temp);
					}
				}

				// bitsequence to string hash
				string shashed = "";
				char temp[2];
				for (int j = 0; j < 32; j++) {
					sprintf(temp, "%02x", bmy_hash[j]);
					shashed.append(temp);
				}

				// check for existance
				unordered_map<string, string>::const_iterator it = rbt.find(shashed);
				if (it != rbt.end()){
					// found a chain
					string chain_start = rbt[shashed];
					string result = analyse_chain(chain_start, my_hash);
					if (result != ""){
						// found password from chain
						found = true;
						cout << "Password: " << result << endl;
						break;
					}
				}
				if (found)
					break;
				c--;
			}
		}
	}
}

string analyse_chain(string start_pass, string target_hash){
	char *temp_pass = new char[start_pass.length() + 1];
	strcpy(temp_pass, start_pass.c_str());
	for (int i = 0; i < chainLen; i++){
		BitSequence bpass[6];
		for (int x = 0; x < 6; x++){
			bpass[x] = temp_pass[x];
		}	
		BitSequence * bhash = hash_blake256(bpass);
		string shashed = "";
		char temp[2];
		for (int j = 0; j < 32; j++) {
			sprintf(temp, "%02x", bhash[j]);
			shashed.append(temp);
		}
		if (shashed == target_hash){
			temp_pass[6] = '\0';
			return string(temp_pass);
		}

		char *ptemp_pass = reduction_function256(bhash, i);

		strcpy(temp_pass, ptemp_pass);
	}
	free(temp_pass);
	return "";
}
