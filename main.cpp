//created by jonathan kipper on 6/2/2019
#include <map>
#include <vector>
#include <set>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

void doP(string x)  {cout << x << endl;}
set<string> criticsPick(map<string,double>&);
bool compareValues(pair<string, double> &, pair<string, double> &);

int main()
{
    map<string,double> movieList;

    string fname = "Movies.txt";
    ifstream myfile;
    myfile.open(fname);

    if (myfile.is_open() )
    { cout << "File Opened" << endl; }
    else
    {
        cout << "BAD : " +fname<< endl;
        return -99;
    }
    string nameString = "";
    string scoreString = "";

    while (myfile)
    {
        getline(myfile,nameString);
        getline(myfile,scoreString);

        movieList[nameString]= atof(scoreString.c_str());
    }

    //Uncomment this out to see the map.
    map<string,double>::iterator it = movieList.begin();
    while(it != movieList.end())
    {
      std::cout<<it->first<<" :: "<<it->second<<std::endl;
       it++;
    }

    set<string> results;
    results = criticsPick(movieList);

    for_each(results.begin(),results.end(),doP);
}
//compares the values of the rating in the first pair versus the second pair since the map is in a pair
//and the vector is in a pair as well
bool compareValues(pair<string, double> &theFirst, pair<string, double> &theSecond)
{
    return theFirst.second > theSecond.second;
}

set<string> criticsPick(map<string,double> &theMap)
{
    set<string> mySet;
    vector<pair<string,double>> myVector;

    //places map values into vector
    for (const auto &i:theMap)
    {
        myVector.emplace_back(i);
    }

    //sorts the vector
    sort(myVector.begin(), myVector.end(), compareValues);

    //this is for if it's greater than size of 10 or not so it can't error out with a map different
    //than in the size of the movies.txt file. inserts the names of the top 10 movies
    if (myVector.size() > 10)
    {
        for (int i = 0; i < 10; i++)
        {
            mySet.insert(myVector[i].first);
        }
    }
    else
    {
        for (auto & i : myVector)
        {
            mySet.insert(i.first);
        }
    }

    //returns the set
    return mySet;
}