#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <string>
#include <utility>
#include <cstdlib>
using namespace std;

// OMAR ASSOUMA
// 28556

bool bingo = false;
struct element{
	string name;
	string prev;
	int distance;
};


bool add_node(unordered_map<string, vector<string> > & graph,element & node){
    if (graph.find(node.name) != graph.end())
        return false;

    vector<string> value;
    pair<string, vector<string> > keyvalue (node.name,value);
    graph.insert(keyvalue);
    return true;
}


void add_edge(unordered_map<string, vector<string> > & graph,element & firstWord,element & secondWord){
    if ( graph.find(firstWord.name) == graph.end()){
        add_node(graph,firstWord);
    }
    
    if ( graph.find(secondWord.name) == graph.end()){
        add_node(graph,secondWord);
    }

    graph[firstWord.name].push_back(secondWord.name);
  
}


void processingFunction(unordered_map<string, vector<string> > & graph,deque<element> & words){

    for ( int i = 0 ; i < words.size(); i++)
        for ( int j = 0; j < words.size(); j++)
		{
			bool alreadyAdded = false;
			element firstWord = words[i];
			element secondWord = words[j];
			int differ = firstWord.name.length() - secondWord.name.length();

			int valueToLoop = 0; 
			if ( firstWord.name.length() > secondWord.name.length() )
				valueToLoop = secondWord.name.length();
			else if ( firstWord.name.length() == secondWord.name.length() )
				valueToLoop = secondWord.name.length();
			else
				valueToLoop = firstWord.name.length();


			int index = 0;
            int diff = 0;
			for ( int letters = 0; letters < valueToLoop ; letters++){
				if ( abs(differ) >= 2 ){
					break;
				}
				else if ( words[i].name != words[j].name &&  words[i].name[letters] != words[j].name[letters] ){
					if ( diff == 0 )
						index = letters;
					diff++;
				}
            }
			if (firstWord.name.length() > secondWord.name.length() ){
				string temp = firstWord.name;
				string new_word = temp.erase(index,1);
				if ( new_word == secondWord.name){
					add_edge(graph,words[i],words[j]);
					alreadyAdded = true;
				}
			}
			else if ( firstWord.name.length() < secondWord.name.length() ){
				string temp = secondWord.name;
				string new_word = temp.erase(index,1);
				if ( new_word == firstWord.name ){
					add_edge(graph,words[i],words[j]);
					alreadyAdded = true;
				}
			}

			if ( abs(differ) == 1 )
				diff++;
				
            if ( diff <= 1 && words[i].name != words[j].name  && abs(differ) <= 1 && alreadyAdded == false)
                add_edge(graph,words[i],words[j]);

        } 
}


void bfs(unordered_map<string, vector<string> > & graph,deque<element> & paths,element firstWord,element secondWord){

    unordered_map<string,bool > visited;
	deque<element> qu;

	qu.push_front(firstWord);

    while ( qu.size() > 0 && bingo == false ){
        element current_element = qu.back();
		string current = current_element.name;
		int dist = current_element.distance;
        qu.pop_back();
        visited[current] = true;
        for ( int i = 0; i < graph[current].size(); i++ ){
            if ( visited[graph[current][i]] == false ){
                if ( graph[current][i] == secondWord.name ){
                    bingo = true;
					secondWord.prev = current;
					paths.push_back(secondWord);
                }
                else{
					element temp;
					temp.name = graph[current][i];
					temp.distance = 1+dist;
					temp.prev = current;

					bool alreadyExists = false;
					for ( int i = 0; i < qu.size(); i++){
						if (temp.name == qu[i].name)
							alreadyExists = true;
					}

					if ( alreadyExists == false ){
						qu.push_front(temp);
						paths.push_back(temp);
					}
					else
						alreadyExists = false;

                } 
            }
        }
    }
}


void print( deque<element> paths,deque<string> & names,element firstWord,element secondWord){

	string temp;
	string temp5;
	temp5 = paths.back().name;
	temp = paths.back().prev;
	names.push_back(temp);
	paths.pop_back();



	while ( paths.size() != 0 ){
		if ( temp == paths.back().name )
		{
			temp = paths.back().prev;
			names.push_back(temp);
			paths.pop_back();
		}
		else
			paths.pop_back();
	}

	names.push_front(secondWord.name);
	cout << firstWord.name << endl;
	
	string temp2;
	for ( int i = names.size()-1; i > 0; i-- ){
		if ( i > 0 )
			temp2 = names[i-1];
		else
			break;

		int valueToLoop;
		if ( names[i].length() > temp2.length() )
			valueToLoop = temp2.length();
		else if ( names[i].length() == temp2.length() )
			valueToLoop = temp2.length();
		else if ( names[i].length() < temp2.length() )
			valueToLoop = names[i].length();

		int index = 0;
		bool allCorrect = true;
		for ( int letters = 0; letters < valueToLoop; letters++ ){
	
			if ( names[i][letters] != temp2[letters] ){
				index = letters;
				allCorrect = false;
				break;
			}
			
		}
		if ( names[i] != temp2 ) {
			if ( names[i].length() < temp2.length() && allCorrect == false)
				cout << temp2 << " (insert " << temp2[index] << " after position " << index << ")" << endl;
		
			else if ( names[i].length() < temp2.length() && allCorrect == true )
				cout << temp2 << " (insert " << temp2[temp2.length()-1] << " after position " << temp2.length()-1 << ")" << endl;
		
			else if ( names[i].length() > temp2.length() && allCorrect == false )
				cout << temp2 << " (delete " << names[i][index] << " at position " << index+1 << ")" << endl;
		
			else if ( names[i].length() > temp2.length() && allCorrect == true )
				cout << temp2 << " (delete " << names[i][names[i].length()-1] << " at position " << temp2.length()+1 << ")" << endl;

			else
				cout << temp2 << " (change " << names[i][index] << " at position " << index+1 << " to " << temp2[index] << ")" << endl;
		}
	}
}


int main()
{
    unordered_map<string,vector<string> > graph;
    ifstream input;
    string fileName,word;
	element firstWord,secondWord;
	

	do{
		cout << "Please enter words file name: ";
		cin >> fileName;
		input.open(fileName.c_str());
	} while ( input.fail() );

  
    bool firstBool = false;
    bool secondBool = false;
    do{
        cout << "Enter first word and second word: " ;
        cin >> firstWord.name >> secondWord.name;
		bingo = false;

		deque<string> names;
		deque<element> paths;
		deque<element> words;
		while ( input >> word ){
			if ( word != firstWord.name){
				element temp;
				temp.name = word;
				temp.distance = 0;
				words.push_back(temp);
			}
		}
		firstWord.distance = 0;
		words.push_front(firstWord);
			

        if ( firstWord.name[0] != '*'){
            for ( unsigned int i = 0; i < words.size(); i ++){
                if ( firstWord.name == words[i].name)
                    firstBool = true;
                if ( secondWord.name == words[i].name )
                    secondBool = true;
            }
            if ( firstBool == false || secondBool == false ){
                cout << "One of the words are no in words.txt!" << endl;
                return 0;
            }
            else{
             processingFunction(graph,words);
			 bfs(graph,paths,firstWord,secondWord);
			 if ( bingo == true )

				print(paths,names,firstWord,secondWord);
			 else
				 cout << "No Sequence of letter transformation exists between " << firstWord.name << " and " << secondWord.name << "." << endl;
			 

			}
        }
    } while ( firstWord.name[0] != '*');

    return 0;
}