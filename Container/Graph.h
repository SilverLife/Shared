// ☕ Привет
#pragma once

#include "StaticVector.h"
#include <map>

namespace Shared
{
	namespace Containers
	{
		struct Blank {};
		std::ostream& operator<<(std::ostream& os, Blank b)
		{
			return os;
		}

		template <class TNodeId = int, class TNodeData = Blank , class TEdgeData = Blank, size_t kMaxAdjacentNodes = 10 >
		class Graph
		{
			struct Edge;

			struct Node
			{
				TNodeId _id;
				TNodeData _data;
				StaticVector<Node*, kMaxAdjacentNodes> _adjacent_nodes;
				StaticVector<Edge*, kMaxAdjacentNodes> _adjacent_edges;

				Node(TNodeId id, const TNodeData& data)
				: _id(id),
				  _data(data)
				{}
			};

			struct Edge
			{
				TEdgeData _data;
				Node* _node_1 = nullptr;
				Node* _node_2 = nullptr;

				Edge(const TEdgeData& data, Node* node_1, Node* node_2)
					:_data(data), _node_1(node_1), _node_2(node_2)
				{}
			};								

			std::map<TNodeId, Node> _nodes;
			std::vector<Edge> _edges;

		public:

			bool AddNode(TNodeId node_id, const TNodeData& data = {}) 
			{
				const auto[it, is_success] = _nodes.emplace(node_id, Node{ node_id, data });
				return is_success;
			}
			
			
			bool AddEdge(TNodeId node1_id, TNodeId node2_id, const TEdgeData& data = {}) 
			{
				const auto node_1_it = _nodes.find(node1_id);
				if (node_1_it == _nodes.end())
				{
					return false;
				}
				const auto node_2_it = _nodes.find(node2_id);
				if (node_2_it == _nodes.end())
				{
					return false;
				}

				Node* node_1 = &(node_1_it)->second;
				Node* node_2 = &(node_2_it)->second;

				_edges.emplace_back(data, node_1, node_2);

				Edge* edge = &_edges.back();

				node_1->_adjacent_nodes.push_back(node_2);
				node_1->_adjacent_edges.push_back(edge);

				node_2->_adjacent_nodes.push_back(node_1);
				node_2->_adjacent_edges.push_back(edge);
			}


			bool AddEdge(TNodeId node1_id, TNodeId node2_id, const TNodeData& node_data_1, const TNodeData& node_data_2,
				const TEdgeData& value = {})
				 {}

			size_t NodesCount() const { return _nodes.count(); }
			size_t EdgesCount() const { return _edges.count(); }

			void Print()
			{
				for (auto&[node_id, node] : _nodes)
				{
					std::cout << node_id << ": {" << node._data << "} ";
					for (auto& adj_node : node._adjacent_nodes)
					{
						std::cout << adj_node->_id << " ";
					}
					std::cout << std::endl;
				}
			}

		};
	}
}