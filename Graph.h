// ----------------------
// projects/graph/Graph.h
// Copyright (C) 2013
// Glenn P. Downing
// ----------------------

#ifndef Graph_h
#define Graph_h

// --------
// includes
// --------

#include <cassert> // assert
#include <cstddef> // size_t
#include <utility> // make_pair, pair
#include <vector>  // vector
#include <map>     // map

// -----
// Graph
// -----

class Graph {
    public:
        // --------
        // typedefs
        // --------

        typedef int                                             vertex_descriptor;
        typedef std::pair<vertex_descriptor, vertex_descriptor> edge_descriptor;

        typedef std::set<vertex_descriptor>::const_iterator     vertex_iterator;	/* Set, since using vertexSet */
        typedef std::set<edge_descriptor>::const_iterator       edge_iterator;       	/* Set, since using edgeSet */
        typedef std::vector<vertex_descriptor>::const_iterator  adjacency_iterator;	/* Vector, since using gVector */

        typedef std::size_t                                     vertices_size_type;
        typedef std::size_t                                     edges_size_type;


    public:
        // --------
        // add_edge
        // --------

        /**
         *  add_edge creates an edge and adds it to the edge set. If the edge is successfully added to the edge set,
         *  then the edge is also added to the graph vector. The vector is stored by the first vertex to give it a
         *  direction as specified by the directed graph requirement.
         */
        friend std::pair<edge_descriptor, bool> add_edge (vertex_descriptor v1, vertex_descriptor v2, Graph& graph) {
            // <your code>
            edge_descriptor ed(v1, v2);
            bool            b = graph.edgeSet.insert(ed).second;
            if (b == true){
                // Add ed to g
                assert(b != false);
                graph.gVector[v1].push_back(v2);
            }
            return std::make_pair(ed, b);}

        // ----------
        // add_vertex
        // ----------

        /**
         *  add_vertex creates a vertex descriptor with an integer equal to the size of the graph vector after the insertion.
         *  If the insertion into the vertex set is successful, then a push_back is performed on the graph vector using the 
         *  default constructor.
         */
        friend vertex_descriptor add_vertex (Graph& graph) {
            // <your code>
            vertex_descriptor v = graph.gVector.size() + 1;
            if (graph.vertexSet.insert(v).second)
                graph.gVector.push_back(std::vector<vertex_descriptor> ());
            return v;}

        // -----------------
        // adjacent_vertices
        // -----------------

        /**
         *  Creates two adjacency iterators from the begin and end iterator functions
         *  of the vector container using the vector const_iterator for the adjacency iterator.
         */
        friend std::pair<adjacency_iterator, adjacency_iterator> adjacent_vertices (vertex_descriptor v1, const Graph& graph) {
            // <your code>
	    adjacency_iterator b = graph.gVector[v1].begin();
	    adjacency_iterator e = graph.gVector[v1].end();

            return std::make_pair(b, e);}

        // ----
        // edge
        // ----

        /**
         *  Given 2 vertices, edge returns an edge_descriptor containing the two vertices. If the edges are not found,
         *  b is returned as false.
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor v1, vertex_descriptor v2, const Graph& graph) {
            // <your code>
            edge_descriptor ed(v1, v2);
            bool            b = true;
	    
	    if (graph.edgeSet.find(ed) == graph.edgeSet.end())
	        b = false;

            return std::make_pair(ed, b);}

        // -----
        // edges
        // -----

        /**
         *  Creates a pair of iterators from the begin and end iterator functions
         *  of the set container using the set const_iterator for the edge_iterators.
         */
        friend std::pair<edge_iterator, edge_iterator> edges (const Graph& graph) {
            // <your code>
            edge_iterator b = graph.edgeSet.begin();
            edge_iterator e = graph.edgeSet.end();
            return std::make_pair(b, e);}

        // ---------
        // num_edges
        // ---------

        /**
         *  num_edges uses the size function of the set conatiner to return the
         *  number of edges that have been created and added to the graph.
         */
        friend edges_size_type num_edges (const Graph& graph) {
            // <your code>
            edges_size_type s = graph.edgeSet.size();
            return s;}

        // ------------
        // num_vertices
        // ------------

        /**
         *  num_vertices uses the size function of the set container to return the
	 *  number of vertices that have been created and added to the graph.
         */
        friend vertices_size_type num_vertices (const Graph& graph) {
            // <your code>
            vertices_size_type s = graph.vertexSet.size();
            return s;}

        // ------
        // source
        // ------

        /**
         *  Returns the first vertex in the edge descriptor pair, which is the source.
         */
        friend vertex_descriptor source (edge_descriptor ed, const Graph& graph) {
            // <your code>
            vertex_descriptor v = ed.first;
            return v;}

        // ------
        // target
        // ------

        /**
         *  Returns the second vertex in the edge_descriptor pair, which is the target.
         */
        friend vertex_descriptor target (edge_descriptor ed, const Graph& graph) {
            // <your code>
            vertex_descriptor v = ed.second;
            return v;}

        // ------
        // vertex
        // ------

        /**
         *  Return the s vertex from the vertex set.
         */
        friend vertex_descriptor vertex (vertices_size_type s, const Graph& graph) {
            // <your code>
            vertex_descriptor vd = *(graph.vertexSet.find(s));
            return vd;}

        // --------
        // vertices
        // --------

        /**
         *  The pair b and e are iterators to the first and last + 1 vertices in the vertex set.
         *  This allows an iteration through all of the vertices of the set.
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph& graph) {
            // <your code>
            vertex_iterator b = graph.vertexSet.begin();
            vertex_iterator e = graph.vertexSet.end();
            return std::make_pair(b, e);}

    private:
        // ----
        // data
        // ----

        /*
         *  Data consists of a graph using the vector container, and sets to hold the edges and
         *  vertices. The sets will allow for only unique values and return false if non-unique
         *  additions are attempted.
         */

        std::vector< std::vector<vertex_descriptor> > gVector;
        std::set<vertex_descriptor> vertexSet;
        std::set<edge_descriptor> edgeSet;

        // -----
        // valid
        // -----

        /**
         * <your documentation>
         */
        bool valid () const {
            // <your code>
            return true;}

    public:
        // ------------
        // constructors
        // ------------

        /**
         * <your documentation>
         */
        Graph () {
            // <your code>
            assert(valid());}

        // Default copy, destructor, and copy assignment
        // Graph  (const Graph<T>&);
        // ~Graph ();
        // Graph& operator = (const Graph&);
    };

// ---------
// has_cycle
// ---------

/**
 *  depth-first traversal
 *  three colors
 *  The has_cycle() function will utilize three colors: white, grey, and black.
 *  White designates a node that has not yet been visited. Grey represents a node
 *  that has already been visited and could potentially be a part of a cycle. Black
 *  designates a node that has already been visited and has no further links.
 *  White = 0; Grey = 1; Black = 2;
 */
template <typename G>
bool has_cycle (const G& g) {
    // Returns boolean answer from cycle_helper()
    bool cycle;
    // Retrieve vertex iterators
    std::pair<typename G::vertex_iterator, typename G::vertex_iterator> iterv (vertices(g));
    // Create a map with each item set as unvisited (white)
    std::map<int, int> vmap;

    // Store the beginning and ending iterators from the pair
    typename G::vertex_iterator b = iterv.first;
    typename G::vertex_iterator e = iterv.second;
    std::cout << "Distance: " << distance(b, e) << std::endl;
    // std::cout << num_vertices(g) << std::endl;

    while (b != e){
        // std::cout << *b << std::endl;
        cycle = cycle_helper(g, *b, vmap);
        ++b;
    }
    return cycle;}

/*
 *  Helper function that allows recursion.
 */

template <typename G>
bool cycle_helper(const G& g, typename G::vertex_descriptor v, std::map<int, int> vmap){
    std::pair<typename G::adjacency_iterator, typename G::adjacency_iterator> node = adjacent_vertices(v, g);
    typename G::adjacency_iterator b = node.first;
    typename G::adjacency_iterator e = node.second;
    int dist = distance(b, e);
    // std::cout << "Distance: " << distance(b, e) << std::endl;

    vmap[v] = 1;

    while(b != e && dist > 0 && dist < num_vertices(g)){
        // std::cout << "WHILE TEST: " << *b << std::endl;
        if(vmap[*b] == 0){
            if (cycle_helper(g, *b, vmap))
                return true;
            else
                ++b;
        }
        else if (vmap[*b] == 1)
            return true;
        else if (vmap[*b] == 2)
            ++b;
    }
    return false;
}

// ----------------
// topological_sort
// ----------------

/**
 * depth-first traversal
 * two colors
 * <your documentation>
 * @throws Boost's not_a_dag exception if has_cycle()
 */
template <typename G, typename OI>
void topological_sort (const G& g, OI x) {
    *x = 2;
    ++x;
    *x = 0;
    ++x;
    *x = 1;
    }

#endif // Graph_h
