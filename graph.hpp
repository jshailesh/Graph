#pragma once

/* File: graph.hpp
 * ---------------
 * The implementation of graph data structure
 * The data-structure has been implemented as adjacency list.
 */

#include <unordered_map>
#include <iostream>
#include <vector>
#include <utility>
#include <initializer_list>
#include <queue>

namespace sjha
{
  template <typename T>
  class graph
  {
  private:
    using AdjList = std::unordered_map<T, std::vector<T>>;
    AdjList _adjList{};
    
  public:
    graph() = default;
    ~graph() = default;

    graph(std::initializer_list<std::pair<const T, std::vector<T>>> adjList)
      : _adjList{adjList}
    {}

    void add_vertex(const T &vertex); 
    void add_edge(const T &src_vertex, const T &dst_vertex);

    // Graph search
    std::vector<T> breadth_first_search(const T &vertex) const;
    
    void print() const;
  };

  template <typename T>
  void graph<T>::add_vertex(const T &vertex)
  {
    _adjList.emplace(std::make_pair(vertex, std::vector<T> {}));
  }

  template <typename T>
  void graph<T>::add_edge(const T &src_vertex, const T &dst_vertex)
  {
    if (_adjList.find(src_vertex) != _adjList.end())
      {
	_adjList[src_vertex].push_back(dst_vertex);
      }
    else
      {
	_adjList.emplace(std::make_pair(src_vertex,
					std::vector<T> {dst_vertex}));
      }
  }

  template <typename T>
  void graph<T>::print() const
  {
     std::cout << "Adjacency List of Directed Graph: " << std::endl;
     for (const auto &vertex : _adjList)
       {
	 std::cout << vertex.first << ": ";

	 for (const auto &neighbor : vertex.second)
	   {
	     std::cout << neighbor << " ";
	   }
	 std::cout << std::endl;
       }
  }

  template <typename T>
  std::vector<T> graph<T>::breadth_first_search(const T &vertex) const
  {
    std::vector<T> result;
    enum class COLOR{WHITE, GRAY, BLACK};
    std::unordered_map<T, COLOR> traversal_info{};

    // Color all the vertices except the source vertex WHITE
    for (const auto &item : _adjList)
      {
	traversal_info.emplace(std::make_pair(item.first, COLOR::WHITE));
      }

    // Color the source vertex GRAY
    traversal_info[vertex] = COLOR::GRAY;

    // INVARIANT: The queue contains only the GRAY vertices
    std::queue<T> vertices_visited;
    vertices_visited.push(vertex);
    while (!vertices_visited.empty())
      {
	auto c_vertex = vertices_visited.front();
	vertices_visited.pop();

	// Visit all the vertices in the current vertex's adjacency list
	for (const auto &item : _adjList.at(c_vertex))
	  {
	    // If the vertex has not been visited
	    if (traversal_info[item] == COLOR::WHITE)
	      {
		// Mark the vertex as visited
		traversal_info[item] = COLOR::GRAY;
		vertices_visited.push(item);

		// Push the vertex onto the queue to maintain the invariant
		result.push_back(item);
	      }
	  }

	// All the vertices in the adjacency list of this vertex have been
	// visited - hence mark the vertex BLACK
	traversal_info[c_vertex] = COLOR::BLACK;	
      }

    return result;
  }
}
