#ifndef CITYGEN_STREAMLINE_H
#define CITYGEN_STREAMLINE_H

#include "GenericTypes.h"
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <cassert>

namespace CityGen
{
class Edge;
class Streamline;

class Vertex
{
public:
	Vertex(Vector2 pos) : _pos(pos), _id(_nextId++) {}

	Vector2 getPos() const
	{
		return _pos;
	}

	const std::vector<Edge> &getEdges() const
	{
		return _edges;
	}

	std::size_t getId() const
	{
		return _id;
	}

	void addEdge(const Edge &edge)
	{
		_edges.push_back(edge);
	}

	bool removeEdge(const Edge &edge)
	{
		const auto it = std::find(std::begin(_edges), std::end(_edges), edge);
		bool res = false;

		if (it != std::end(_edges))
		{
			_edges.erase(it);
			res = true;
		}

		return res;
	}

	std::size_t getEdgesCount() const
	{
		return _edges.size();
	}

	bool operator==(const Vertex &rhs) const
	{
		return getId() == rhs.getId();
	}

private:
	const Vector2 _pos;
	const std::size_t _id;

	std::vector<Edge> _edges;

	static std::size_t _nextId;
};

std::size_t Vertex::_nextId = 0;

class Edge
{
public:
	Edge(Streamline &streamline, const Vertex &a, const Vertex &b)
		: _a(a), _b(b), _streamline(streamline)
	{
		if (_a == _b)
		{
			throw std::invalid_argument{ "Cannot create an edge with two identical vertices." };
		}

		_direction = { _b.getPos() - _a.getPos() };
		
		_direction.normalize();
		// BUG: This is probably incorrect as we have local copies of vertecies
		_a.addEdge(*this);
		_b.addEdge(*this);
	}

	const Vertex &getA() const
	{
		return _a;
	}

	const Vertex &getB() const
	{
		return _b;
	}

	Vector2 getDirection() const
	{
		return _direction;
	}

	const Streamline &getStreamline() const
	{
		return _streamline;
	}

	std::pair<Edge, Edge> split(const Vertex &mid)
	{
		if (!_streamline.addVertex(mid))
		{
			assert(false);
		}

		if (!_a.removeEdge(*this) || !_b.removeEdge(*this))
		{
			assert(false);
		}

		return { Edge{ _streamline, _a, mid }, Edge{ _streamline, mid, _b } };
	}

private:
	Vertex _a;
	Vertex _b;
	Vector2 _direction;
	Streamline &_streamline;
};

class Streamline
{
public:
	Streamline(const Vertex &start)
		: _first(start), _last(start)
	{

	}

	const Vertex &getFirst() const
	{
		return _first;
	}

	const Vertex &getLast() const
	{
		return _last;
	}

	bool addVertex(const Vertex &vertex)
	{
		return _vertices.insert(vertex).second;
	}

	bool removeVertex(const Vertex &vertex)
	{
		return _vertices.erase(vertex) != 0;
	}

	bool containsVertex(const Vertex &vertex) const
	{
		return _vertices.find(vertex) != std::end(_vertices);
	}

	Edge extand(const Vertex &vertex)
	{
		if (vertex != _first && !addVertex(vertex))
		{
			assert(false);
		}

		const Vertex &a = _last;
		const Vertex &b = vertex;

		if (std::any_of(std::begin(a.getEdges()), std::end(a.getEdges()), [a, b](const Edge &edge)
		{
			return a == edge.getA() && b == edge.getB() || a == edge.getB() && b == edge.getA();
		}))
		{
			assert(false);
		}

		_last = b;

		return { *this, a, b };
	}

private:
	Vertex _first;
	Vertex _last;

	std::unordered_set<Vertex> _vertices;
};
}

#endif
