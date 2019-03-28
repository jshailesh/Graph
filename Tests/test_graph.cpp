#include "../graph.hpp"
#include <gtest/gtest.h>
#include <string>

TEST(GraphTest, InitializerList)
{
  sjha::graph<int> my_graph{
    {1, {2, 4}},
      {2, {5}},
	{3, {5, 6}},
	  {5, {2}},
	    {5, {4}},
	      {6, {6}}};
  my_graph.print();

  int start_vertex = 2;
  auto bfs_traversal = my_graph.breadth_first_search(start_vertex);
  std::cout << "BFS Traversal WRT Vertex " << start_vertex
	    << ": ["; 
  for (const auto &item : bfs_traversal)
    {
      std::cout << item << " ";
    }
  std::cout << "]" << std::endl;
}

TEST(GraphTest, DefaultGraph)
{
  sjha::graph<int> my_graph{};
  my_graph.add_vertex(1);
  my_graph.add_vertex(2);
  my_graph.add_vertex(3);
  my_graph.add_vertex(4);
  my_graph.add_vertex(5);
  my_graph.add_vertex(6);
  my_graph.add_edge(1, 2);
  my_graph.add_edge(1, 4);
  my_graph.add_edge(2, 5);
  my_graph.add_edge(3, 5);
  my_graph.add_edge(3, 6);
  my_graph.add_edge(4, 2);
  my_graph.add_edge(5, 4);
  my_graph.add_edge(6, 6);
  my_graph.print();
}

TEST(GraphTest, BFS)
{
  sjha::graph<std::string> my_graph{
    {"r", {"s", "v"}},
      {"s", {"r", "w"}},
	{"t", {"u", "w", "x"}},
	  {"u", {"t", "x", "y"}},
	    {"v", {"r"}},
	      {"w", {"s", "t", "x"}},
		{"x", {"t", "u", "w"}},
		  {"y", {"u", "x"}}};

  my_graph.print();

  std::string start_vertex = "s";
  auto bfs_traversal = my_graph.breadth_first_search(start_vertex);
  std::cout << "BFS Traversal WRT Vertex " << start_vertex
	    << ": ["; 
  for (const auto &item : bfs_traversal)
    {
      std::cout << item << " ";
    }
  std::cout << "]" << std::endl;
		
}
