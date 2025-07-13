#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>


template<typename T>
class Graph {
private:
    std::map<T, std::set<T>> adjList;// Adjacency list representation of the graph


    // Helper function to generate wildcard patterns for a word
    std::vector<std::string> generateWildCards(const std::string& word); // Note: still takes std::string

public:
    Graph() = default;
    ~Graph() = default;
    Graph(std::map<T, std::set<T>> adjList) : adjList(adjList) {}

    void addNode(const T& node);
    void addEdge(const T& node1, const T& node2);

    bool hasNode(const T& node) const {
        return adjList.count(node) > 0;
    }

    std::vector<T> getAllNodes() const {
        std::vector<T> nodes;
        for (const auto& pair : adjList) {
            nodes.push_back(pair.first);
        }
        return nodes;
    }

    std::set<T> getNeighbors(const T& node);

    void buildGraph(const QString& dictionaryFile);

    std::vector<T> shortestPath(const T& start, const T& end);
};

template <typename T>
void Graph<T>::addNode(const T& node) {
    // Check if the node already exists
    if (adjList.find(node) == adjList.end()) {
        // If not, add it to the adjacency list with an empty set of neighbors
        adjList[node] = std::set<T>();
    }
    else {
        std::cerr << "Node already exists in the graph." << std::endl;
    }
}

template <typename T>
void Graph<T>::addEdge(const T& node1, const T& node2) {
    // Check if both nodes exist in the graph
    if (adjList.find(node1) != adjList.end() && adjList.find(node2) != adjList.end()) {
        adjList[node1].insert(node2);
        adjList[node2].insert(node1);
    }
    else {
        std::cerr << "One or both nodes do not exist in the graph." << std::endl;
    }
}

template <typename T>
std::set<T> Graph<T>::getNeighbors(const T& node) {
    if (adjList.find(node) != adjList.end()) {
        return adjList[node];
    }
    else {
        std::cerr << "Node does not exist in the graph." << std::endl;
        return std::set<T>();
    }
}

template <typename T>
std::vector<T> Graph<T>::shortestPath(const T& start, const T& end) {
    std::vector<T> path;
    if (adjList.find(start) == adjList.end() || adjList.find(end) == adjList.end()) {
        std::cerr << "Error: Start or end word not in graph." << std::endl;
        return path;
    }

    std::queue<T> q;
    std::map<T, T> parent;
    std::set<T> visited;

    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        T current = q.front();
        q.pop();

        if (current == end) {
            break;
        }

        for (const T& neighbor : getNeighbors(current)) {
            if (visited.find(neighbor) == visited.end()) {
                q.push(neighbor);
                visited.insert(neighbor);
                parent[neighbor] = current;
            }
        }
    }

    if (parent.find(end) != parent.end()) {
        T current = end;
        while (current != start) {
            path.push_back(current);
            current = parent[current];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
    }

    return path;
}

// Specializations for std::string implementation (still in header)
// These are still 'template <typename T>' because they are part of the
// template class, even if they explicitly use std::string.
template <typename T> // Still needs template <typename T>
std::vector<std::string> Graph<T>::generateWildCards(const std::string& word) {
    std::vector<std::string> wildCards;
    for (size_t i = 0; i < word.length(); i++) {
        std::string wildCard = word;
        wildCard[i] = '*';
        wildCards.push_back(wildCard);
    }
    return wildCards;
}

template <typename T> // Still needs template <typename T>
void Graph<T>::buildGraph(const QString& dictionaryFile) {
    QFile file(dictionaryFile); // Create a QFile object

    // Attempt to open the file
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Could not open dictionary file:" << dictionaryFile << "Error:" << file.errorString();
        // Optionally, throw an exception or return a status to MainWindow
        return;
    }

    QTextStream in(&file); // Use QTextStream to read text data line by line
    std::string word;
    std::set<std::string> wordList;

    // Read words from the file
    while (!in.atEnd()) { // Read until the end of the file
        QString qLine = in.readLine(); // Read one line as QString
        word = qLine.trimmed().toStdString(); // Convert to std::string and remove leading/trailing whitespace

        if (!word.empty()) { // Only process non-empty words
            addNode(word);
            wordList.insert(word);
        }
    }
    file.close(); // Close the file

        std::map<std::string, std::vector<std::string>> wildCardMap;

        for (const auto& word : wordList) {
            std::vector<std::string> wildCards = generateWildCards(word);
            for (const auto& wildCard : wildCards) {
                wildCardMap[wildCard].push_back(word);
            }
        }

        for (const auto& pair : wildCardMap) {
            std::vector<std::string> words = pair.second;
            for (size_t i = 0; i < words.size(); i++) {
                for (size_t j = i + 1; j < words.size(); j++)
                    addEdge(words[i], words[j]);
            }
        }
    }
