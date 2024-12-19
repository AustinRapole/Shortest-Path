#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<unordered_map>
#include<cstring>
#include<unordered_set>
#include<queue>
#include "math.h"

using namespace std;

struct Coordinate{
  int x;
  int y;
  string toString() const;
  bool operator<(const Coordinate& b) const;
  bool operator==(const Coordinate& b) const;
  bool operator!=(const Coordinate& b) const;
};


string Coordinate::toString() const{
  string result = "";
  result ="(" + to_string(x) + "," + to_string(y) + ")";
  return result;
}

struct Weight{
  double gValue;
  double hValue;
};

unordered_map<string, Weight> notworld;
unordered_map<string, Coordinate> pathing;
string heuristic = "none";
unordered_set<string> explored;
vector<Coordinate> character;
vector<Coordinate> destination;
bool Coordinate::operator<(const Coordinate& b)const{
  bool value = false;
  Weight x = notworld[toString()];
  Weight y = notworld[b.toString()];
  double wa = x.hValue + x.gValue;
  double wb = y.hValue + y.gValue;
  if(wa == wb){
    if(x.hValue == 0 and y.hValue == 0){
      return x.gValue < y.gValue;
    }
    return x.hValue < y.hValue;
  }
  value = wa > wb;
  return value;
}

bool Coordinate::operator==(const Coordinate& b)const{
  return x == b.x and y == b.y;
}
bool Coordinate::operator!=(const Coordinate& b)const{
  return x != b.x or y != b.y;
}

priority_queue<Coordinate> workingset;

double manhattan(Coordinate current, Coordinate finish){
  double x = (current.x - finish.x);
  double y = (current.y - finish.y);
  double total = abs(x) + abs(y);
  return total;
}

double euclidean(Coordinate current, Coordinate finish){
  double x = (current.x - finish.x);
  x = x*x;
  double y = (current.y - finish.y);
  y = y*y;
  double total = sqrt(x+y);
  return total;
}

double heuristicFunction(Coordinate current, Coordinate finsih){
  if(heuristic == "manhattan"){
    double total = manhattan(current, finsih);
    return total;
  }
  if(heuristic == "euclidean"){
    double total = euclidean(current, finsih);
    return total;
  }
  if(heuristic == "dijkstra"){
    return 0;
  }
}
bool explore(Coordinate start, Coordinate finish){
  workingset.push(start);
  Coordinate cur;
  while(workingset.empty() == false){
    cur = workingset.top();
    if(cur == finish){
      return true;
    }
    Coordinate temp = cur;
    Coordinate n = cur;
    Coordinate e = cur;
    Coordinate x = cur;
    Coordinate t = cur;
    explored.insert(cur.toString());
    character.push_back(cur);
    workingset.pop();

    n.x +=1;
    if(notworld.count(n.toString()) ==1  and explored.count(n.toString()) != 1){
      if(notworld[n.toString()].gValue == -1){
	notworld[n.toString()].gValue = notworld[cur.toString()].gValue + 1;
	workingset.push(n);
	pathing[n.toString()] = cur;
	if(n == finish){
	  return true;
	  notworld[finish.toString()].gValue = notworld[cur.toString()].gValue + 1; 
	}
      }
    }

    e.x -=1;
    if(notworld.count(e.toString()) ==1  and explored.count(e.toString()) != 1){
      if(notworld[e.toString()].gValue == -1){
	notworld[e.toString()].gValue = notworld[cur.toString()].gValue + 1;
	workingset.push(e);
	pathing[e.toString()] = cur;
	if(e == finish){
	  return true;
	  notworld[finish.toString()].gValue = notworld[cur.toString()].gValue + 1; 
	}
      }
    }

    x.y +=1;
    if(notworld.count(x.toString()) ==1  and explored.count(x.toString()) != 1){
      if(notworld[x.toString()].gValue == -1){
	notworld[x.toString()].gValue = notworld[cur.toString()].gValue + 1;
	workingset.push(x);
	pathing[x.toString()] = cur;
	if(x == finish){
	  return true;
	  notworld[finish.toString()].gValue = notworld[cur.toString()].gValue + 1; 
	}
      }
    }

    t.y -=1;
    if(notworld.count(t.toString()) ==1  and explored.count(t.toString()) != 1){
      if(notworld[t.toString()].gValue == -1){
	notworld[t.toString()].gValue = notworld[cur.toString()].gValue + 1;
	workingset.push(t);
	pathing[t.toString()] = cur;
	if(t == finish){
	  return true;
	  notworld[finish.toString()].gValue = notworld[cur.toString()].gValue + 1; 
	}
      }
    }
  }
  return false;
}

int main(int argc, char* argv[]){
  ifstream fin;
  //string filename = argv[1];
  //determining which heuersitic function to use
  //string hueristic = "";
  if(argc < 2 or argc >3){
    cout<< "Invalid amount of arguments!" << endl;
    return -1;
  }
  else if(argc == 3){
    if(argv[2] == string("manhattan")){
      heuristic = "manhattan";
    }
    else if(argv[2] == string("euclidean")){
      heuristic = "euclidean";
    }
    else{
      heuristic = "dijkstra";
    }
  }

  string filename = argv[1];
  fin.open(filename);
  string temp;
  double rv;
  vector<vector<char>> grid;
  vector<Coordinate> walls;
  Coordinate finish = Coordinate();
  Coordinate start = Coordinate();
  Coordinate current = Coordinate();
  Coordinate updated = Coordinate();
  Coordinate add = Coordinate();
  Weight wcurrent = Weight();
  int rows;
  int columns;

  //getting and storing the row size
  getline(fin, temp, ' ');
  columns = stoi(temp);

  //getting and storing the column size
  getline(fin, temp);
  rows = stoi(temp);

  //finding each character of the grid and storing it
  grid.resize(rows);
  for(int l = 0; l <rows; ++l){
    grid[l].resize(columns);
  }

  for(int i = 0; i < rows; ++i){
    getline(fin,temp);
    for(int j = 0; j < columns; ++j){
      grid[i][j] = temp[j];
      if(temp[j] == '*'){
	finish.x = j;
	finish.y = i;
      }
      if(temp[j] == 'o'){
	start.x = j;
	start.y = i;
      }
      if(temp[j] == '#'){
	//	walls.push_back();
      }
      if(temp[j] != '#'){
	current.x = j;
	current.y = i;
	wcurrent.gValue = -1;
	wcurrent.hValue = heuristicFunction(current, finish);
	notworld[current.toString()] = wcurrent;
      }
    }
  }
  wcurrent.gValue = 0;
  wcurrent.hValue = heuristicFunction(start, finish);
  notworld[start.toString()] = wcurrent;
  /*
     workingset.push(start);

     while(!workingset.empty()){
     explored.insert(workingset.top().toString());
     workingset.pop();

     }
   */
  bool didComplete = explore(start, finish);
  //if(didComplete == true){
    //cout << "Path found " << destination.size() << endl;
  //}
  //else{
    //cout << "No path found" << endl;
  //}
  /*
     for(int i = 0; i < workingset.size(); ++i){
     cout << "workingset size: ";
     cout << workingset.top().toString() << endl;
     workingset.pop();
     }
     for(auto it = explored.begin(); it != explored.end(); ++it)
     cout << ' ' << *it;
     cout << endl;
   */
  updated = finish;
  //auto it = pathing.find(finish.toString());
  //destination.push_back(it->second);
  while(updated != start and didComplete == true){
    //auto its = pathing.find(it->second.toString());
    //destination.push_back(its->second);

    destination.push_back(updated);
    auto it = pathing.find(updated.toString());
    destination.push_back(it->second);
    updated = it->second;
  }
  int counter = 0;


  for(int i = 0; i < character.size(); ++i){
    grid[character[i].y][character[i].x] = '-';
  }
  for(int i = 0; i < destination.size(); ++i){
    grid[destination[i].y][destination[i].x] = '+';
  }
  grid[start.y][start.x] = 'o';
  grid[finish.y][finish.x] = '*';
  counter +=2;

  //print statements
  cout << columns << " " << rows << endl;
  //cout << heuristic << endl;
  for(int i = 0; i < rows; ++i){
    for(int j = 0; j < columns; ++j){
      cout << grid[i][j];
      if(grid[i][j] == '+'){
	counter += 1;
      }
    }
    cout << endl;
  }
  if(didComplete == true){
    cout << "Path found with length " << notworld[finish.toString()].gValue << endl;
  }
  else{
    cout << "No path found" << endl;
  }

  fin.close();
  return 0;
}
