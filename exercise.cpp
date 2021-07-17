#include <fstream>

#include <string>

#include <sstream>

#include <bits/stdc++.h>

using namespace std;

// struct for each trade
struct trade {
  int time;
  int quantity;
  int price;
};

// struct for the symbol 
//  tr  -- vector of trades under this symbol
struct symbol {
  vector < trade > tr;
};

int main(int argc, char * argv[]) {

  // input and outut file names
  string input = argv[1];
  string output = argv[2];

  
  map < string, symbol > symbol_cur;
  
  // readin  data from input file
  ifstream inFile(input);
  string line;

  while (getline(inFile, line)) {

    vector < int > data_line;
    string data;
    istringstream readstr(line);
    trade tmp_tr;
    string tmp_symbol;
    for (int j = 0; j < 4; j++) {
      getline(readstr, data, ',');
      switch (j) {
      case 0:
        tmp_tr.time = atoi(data.c_str());
        break;
      case 1:
        tmp_symbol = data.c_str();
        break;
      case 2:
        tmp_tr.quantity = atoi(data.c_str());
        break;
      case 3:
        tmp_tr.price = atoi(data.c_str());
        break;
      }
    }

    // update data in the map 
    if (symbol_cur.find(tmp_symbol) != symbol_cur.end()) {
      symbol_cur[tmp_symbol].tr.push_back(tmp_tr);
    } else {
      symbol tmp_sy;
      tmp_sy.tr.push_back(tmp_tr);
      symbol_cur[tmp_symbol] = tmp_sy;
    }
  }

  ofstream outFile;
  outFile.open(output);
  for (auto sym: symbol_cur) {
    
    int maxTimeGap = 0;
    int volume = 0;
    int weightedAveragePrice = 0;
    int maxPrice = 0;
    
    //process the data needed
    for (int i = 0; i < sym.second.tr.size(); i++) {
      if (i != 0) {
        maxTimeGap = max(maxTimeGap, sym.second.tr[i].time - sym.second.tr[i - 1].time);
      }
      volume += sym.second.tr[i].quantity;
      weightedAveragePrice += sym.second.tr[i].quantity * sym.second.tr[i].price;
      maxPrice = max(maxPrice, sym.second.tr[i].price);
    }
    // output to csv
    outFile << sym.first << ",";
    outFile << maxTimeGap << "," << volume << "," << weightedAveragePrice / volume << "," << maxPrice << endl;
  }

  outFile.close();

  return 0;
}