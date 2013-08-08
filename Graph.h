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
         * <your documentation>
         */
        friend std::pair<edge_descriptor, bool> edge (vertex_descriptor, vertex_descriptor, const Graph&) {
            // <your code>
            edge_descriptor ed;
            bool            b;
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
         * <your documentation>
         */
        friend vertex_descriptor source (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v;
            return v;}

        // ------
        // target
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor target (edge_descriptor, const Graph&) {
            // <your code>
            vertex_descriptor v;
            return v;}

        // ------
        // vertex
        // ------

        /**
         * <your documentation>
         */
        friend vertex_descriptor vertex (vertices_size_type, const Graph&) {
            // <your code>
            vertex_descriptor vd;
            return vd;}

        // --------
        // vertices
        // --------

        /**
         * <your documentation>
         */
        friend std::pair<vertex_iterator, vertex_iterator> vertices (const Graph&) {
            // <your code>
            vertex_iterator b = vertex_iterator();
            vertex_iterator e = vertex_iterator();
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
 * depth-first traversal
 * three colors
 * <your documentation>
 */
template <typename G>
bool has_cycle (const G& g) {
    return true;}

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
