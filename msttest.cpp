#include <iostream>
#include "header.h"
#include <string>
#include <cmath>

int main(){

	std::string line;
	Graph graph;


	while(getline(std::cin, line)){
        if (line.substr(0, 1) == "i"){
            int pos = (line.substr(2)).find(";");
            int u = std::stoi(line.substr(2, pos));

            std::string line1 = line.substr(pos+3);
            pos = line1.find(";");
            int v = std::stoi(line1.substr(0, pos));

            line1 = line1.substr(pos+1);
            pos = line1.find(";");
            double w = std::stof(line1.substr(0, pos));

            graph.insert_edge(u, v, w);
        }
        else if (line.substr(0, 2) == "d "){
            int pos = line.find(";");
            int u = std::stoi(line.substr(1, pos));

            int v = std::stoi(line.substr(pos+1));

            graph.delete_edge(u, v);
        }
        else if (line.substr(0, 6) == "degree"){
            int u = std::stoi(line.substr(6));
            int temp = graph.degree(u);
        }
        else if (line.substr(0, 10) == "edge_count"){
            int temp1 = graph.total_edges();
        }
        else if (line.substr(0, 5) == "clear"){
            graph.clear();
        }
        else if (line.substr(0, 3) == "mst"){
            graph.mst();
        }
        else if (line.substr(0, 1) == "n"){
            int u = std::stoi(line.substr(1));
            graph.create_graph(u);
        } 
	}
	return 0;
}