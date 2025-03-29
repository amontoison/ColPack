#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <stdarg.h> //  support for variadic functions
//#include <cctype> //for toupper()

#include <list>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <cstring>
#include <unordered_set>

#include "ColPackHeaders.h"
#include "cinterface.h"

const unordered_set<string> GENERAL_COLORING({
    "DISTANCE_ONE",
    "ACYCLIC",
    "ACYCLIC_FOR_INDIRECT_RECOVERY",
    "STAR",
    "NAIVE_STAR",
    "RESTRICTED_STAR",
    "DISTANCE_TWO",
    "TRIANGULAR"});

const unordered_set<string> PARTIAL_COLORING({
    "COLUMN_PARTIAL_DISTANCE_TWO",
    "ROW_PARTIAL_DISTANCE_TWO"});

const unordered_set<string> BICOLORING({
    "IMPLICIT_COVERING__STAR_BICOLORING",
    "EXPLICIT_COVERING__STAR_BICOLORING",
    "EXPLICIT_COVERING__MODIFIED_STAR_BICOLORING",
    "IMPLICIT_COVERING__GREEDY_STAR_BICOLORING"});

void print_output(GraphColoringInterface* g, int verbose) {
    if (verbose) {
        double t1 = g->GetVertexOrderingTime();
        double t2 = g->GetVertexColoringTime();
        std::cout << "Order and color time = " << t1 + t2 << " = " << t1 << " + " << t2 << std::endl;
        std::cout << "Number of colors: " << g->GetVertexColorCount() << std::endl;
    }
}

void print_output(BipartiteGraphPartialColoringInterface* g, int verbose) {
    if (verbose) {
        double t1 = g->GetVertexOrderingTime();
        double t2 = g->GetVertexColoringTime();
        std::cout << "Order and color time = " << t1 + t2 << " = " << t1 << " + " << t2 << std::endl;
        std::cout << "Number of colors: " << g->GetVertexColorCount() << std::endl;
    }
}

void print_output(BipartiteGraphBicoloringInterface* g, int verbose) {
    if (verbose) {
        double t1 = g->GetVertexOrderingTime();
        double t2 = g->GetVertexColoringTime();
        std::cout << "Order and color time = " << t1 + t2 << " = " << t1 << " + " << t2 << std::endl;
        std::cout << "Number of colors: " << g->GetVertexColorCount() << std::endl;
    }
}

extern "C" int build_coloring_from_file(void** ref, int* len, const char* filename, const char* method, const char* order, int verbose) {
    string _filename = string(filename);
    string _method = string(method);
    string _order = string(order);
    vector<int> coloring;

    std::ifstream file(_filename);
    if (!file.good()) {
        std::cerr << "ColPack: Unable to open file " << _filename << std::endl;
        return 0;
    }
    file.close();

    if (verbose) {
        std::cout << "Filename: " << _filename << "\norder: " << _order << "\nmethod: " << _method << "\n";
    }

    if (GENERAL_COLORING.count(method)) {
        if (verbose) std::cout << "General Graph Coloring\n";
        GraphColoringInterface* g = new GraphColoringInterface(SRC_FILE, _filename.c_str(), "AUTO_DETECTED");
        g->Coloring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        g->GetVertexColors(coloring);
        *len = static_cast<int>(coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_partial_coloring_from_file(void** ref, int* len, const char* filename, const char* method, const char* order, int verbose) {
    string _filename = string(filename);
    string _method = string(method);
    string _order = string(order);
    vector<int> coloring;

    std::ifstream file(_filename);
    if (!file.good()) {
        std::cerr << "ColPack: Unable to open file " << _filename << std::endl;
        return 0;
    }
    file.close();

    if (verbose) {
        std::cout << "Filename: " << _filename << "\norder: " << _order << "\nmethod: " << _method << "\n";
    }

    if (PARTIAL_COLORING.count(method)) {
        if (verbose) std::cout << "Partial Distance Two Bipartite Graph Coloring\n";
        BipartiteGraphPartialColoringInterface* g = new BipartiteGraphPartialColoringInterface(SRC_FILE, _filename.c_str(), "AUTO_DETECTED");
        g->PartialDistanceTwoColoring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        if (_method == "ROW_PARTIAL_DISTANCE_TWO") {
            g->GetLeftVertexColors(coloring);
        }
        else {
            g->GetRightVertexColors(coloring);
        }
        *len = static_cast<int>(coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_bicoloring_from_file(void** ref, int* len1, int* len2, const char* filename, const char* method, const char* order, int verbose) {
    string _filename = string(filename);
    string _method = string(method);
    string _order = string(order);
    vector<int> left_coloring;
    vector<int> right_coloring;

    std::ifstream file(_filename);
    if (!file.good()) {
        std::cerr << "ColPack: Unable to open file " << _filename << std::endl;
        return 0;
    }
    file.close();

    if (verbose) {
        std::cout << "Filename: " << _filename << "\norder: " << _order << "\nmethod: " << _method << "\n";
    }

    if (BICOLORING.count(method)) {
        if (verbose) std::cout << "Bipartite Bipartite Graph Coloring\n";
        BipartiteGraphBicoloringInterface* g = new BipartiteGraphBicoloringInterface(SRC_FILE, _filename.c_str(), "AUTO_DETECTED");
        g->Bicoloring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        g->GetLeftVertexColors(left_coloring);
        *len1 = static_cast<int>(left_coloring.size());
        g->GetRightVertexColors(right_coloring);
        *len2 = static_cast<int>(right_coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_coloring_from_adolc(void** ref, int* len, unsigned int** adolc, int nrows, const char* method, const char* order, int verbose) {
    if (ref == nullptr || len == nullptr || adolc == nullptr || method == nullptr || order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string _method = string(method);
    string _order = string(order);
    vector<int> coloring;

    if (GENERAL_COLORING.count(method)) {
        GraphColoringInterface* g = new GraphColoringInterface(SRC_MEM_ADOLC, adolc, nrows);
        g->Coloring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        g->GetVertexColors(coloring);
        *len = static_cast<int>(coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}


extern "C" int build_partial_coloring_from_adolc(void** ref, int* len, unsigned int** adolc, int nrows, int ncols, const char* method, const char* order, int verbose) {
    if (ref == nullptr || len == nullptr || adolc == nullptr || method == nullptr || order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string _method = string(method);
    string _order = string(order);
    vector<int> coloring;

    if (PARTIAL_COLORING.count(method)) {
        BipartiteGraphPartialColoringInterface* g = new BipartiteGraphPartialColoringInterface(SRC_MEM_ADOLC, adolc, nrows, ncols);
        g->PartialDistanceTwoColoring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        if (_method == "ROW_PARTIAL_DISTANCE_TWO") {
            g->GetLeftVertexColors(coloring);
        }
        else {
            g->GetRightVertexColors(coloring);
        }
        *len = static_cast<int>(coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_bicoloring_from_adolc(void** ref, int* len1, int* len2, unsigned int** adolc, int nrows, int ncols, const char* method, const char* order, int verbose) {
    if (ref == nullptr || len1 == nullptr || len2 == nullptr || adolc == nullptr || method == nullptr || order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string _method = string(method);
    string _order = string(order);
    vector<int> left_coloring;
    vector<int> right_coloring;

    if (BICOLORING.count(method)) {
        BipartiteGraphBicoloringInterface* g = new BipartiteGraphBicoloringInterface(SRC_MEM_ADOLC, adolc, nrows, ncols);
        g->Bicoloring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        g->GetLeftVertexColors(left_coloring);
        *len1 = static_cast<int>(left_coloring.size());
        g->GetRightVertexColors(right_coloring);
        *len2 = static_cast<int>(right_coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_partial_coloring_from_csr(void** ref, int* len, int* rowptr, int* colval, int nrows, int ncols, const char* method, const char* order, int verbose) {
    if (ref == nullptr || len == nullptr || rowptr == nullptr || colval == nullptr || method == nullptr || order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string _method = string(method);
    string _order = string(order);
    vector<int> coloring;

    if (PARTIAL_COLORING.count(method)) {
        BipartiteGraphPartialColoringInterface* g = new BipartiteGraphPartialColoringInterface(SRC_MEM_CSR, rowptr, nrows, ncols, colval);
        g->PartialDistanceTwoColoring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        if (_method == "ROW_PARTIAL_DISTANCE_TWO") {
            g->GetLeftVertexColors(coloring);
        }
        else {
            g->GetRightVertexColors(coloring);
        }
        *len = static_cast<int>(coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_bicoloring_from_csr(void** ref, int* len1, int* len2, int* rowptr, int* colval, int nrows, int ncols, const char* method, const char* order, int verbose) {
    if (ref == nullptr || len1 == nullptr || len2 == nullptr || rowptr == nullptr || colval == nullptr || method == nullptr || order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string _method = string(method);
    string _order = string(order);
    vector<int> left_coloring;
    vector<int> right_coloring;

    if (BICOLORING.count(method)) {
        BipartiteGraphBicoloringInterface* g = new BipartiteGraphBicoloringInterface(SRC_MEM_CSR, rowptr, nrows, ncols, colval);
        g->Bicoloring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        g->GetLeftVertexColors(left_coloring);
        *len1 = static_cast<int>(left_coloring.size());
        g->GetRightVertexColors(right_coloring);
        *len2 = static_cast<int>(right_coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_partial_coloring_from_csc(void** ref, int* len, int* rowval, int* colptr, int nrows, int ncols, const char* method, const char* order, int verbose) {
    if (ref == nullptr || len == nullptr || rowval == nullptr || colptr == nullptr || method == nullptr || order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string _method = string(method);
    string _order = string(order);
    vector<int> coloring;

    if (PARTIAL_COLORING.count(method)) {
        BipartiteGraphPartialColoringInterface* g = new BipartiteGraphPartialColoringInterface(SRC_MEM_CSC, rowval, nrows, ncols, colptr);
        g->PartialDistanceTwoColoring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        if (_method == "ROW_PARTIAL_DISTANCE_TWO") {
            g->GetLeftVertexColors(coloring);
        }
        else {
            g->GetRightVertexColors(coloring);
        }
        *len = static_cast<int>(coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" int build_bicoloring_from_csc(void** ref, int* len1, int* len2, int* rowval, int* colptr, int nrows, int ncols, const char* method, const char* order, int verbose) {
    if (ref == nullptr || len1 == nullptr || len2 == nullptr || rowval == nullptr || colptr == nullptr || method == nullptr || order == nullptr) {
        std::cerr << "ColPack: Invalid input parameters\n";
        return 0;
    }

    string _method = string(method);
    string _order = string(order);
    vector<int> left_coloring;
    vector<int> right_coloring;

    if (BICOLORING.count(method)) {
        BipartiteGraphBicoloringInterface* g = new BipartiteGraphBicoloringInterface(SRC_MEM_CSC, rowval, nrows, ncols, colptr);
        g->Bicoloring(_order.c_str(), _method.c_str());
        *ref = static_cast<void*>(g);
        g->GetLeftVertexColors(left_coloring);
        *len1 = static_cast<int>(left_coloring.size());
        g->GetRightVertexColors(right_coloring);
        *len2 = static_cast<int>(right_coloring.size());
        print_output(g, verbose);
    }
    else {
        std::cerr << "ColPack: Invalid coloring method selected\n";
        return 0;
    }

    return 1;
}

extern "C" void order_coloring(void* ref, int* ordering) {
    GraphColoringInterface* g = static_cast<GraphColoringInterface*>(ref);
    vector<int> _ordering;
    g->GetOrderedVertices(_ordering);
    memcpy(ordering, _ordering.data(), _ordering.size() * sizeof(int));
}

extern "C" void order_partial_coloring(void* ref, int* ordering) {
    BipartiteGraphPartialColoringInterface* g = static_cast<BipartiteGraphPartialColoringInterface*>(ref);
    vector<int> _ordering;
    g->GetOrderedVertices(_ordering);
    memcpy(ordering, _ordering.data(), _ordering.size() * sizeof(int));
}

extern "C" void order_bicoloring(void* ref, int* ordering) {
    BipartiteGraphBicoloringInterface* g = static_cast<BipartiteGraphBicoloringInterface*>(ref);
    vector<int> _ordering;
    g->GetOrderedVertices(_ordering);
    memcpy(ordering, _ordering.data(), _ordering.size() * sizeof(int));
}

extern "C" double timer_order_coloring(void* ref) {
    GraphColoringInterface *g = (GraphColoringInterface*) ref;
    return g->TimerOrdering();
}

extern "C" double timer_order_partial_coloring(void* ref) {
    BipartiteGraphPartialColoringInterface *pg = (BipartiteGraphPartialColoringInterface*) ref;
    return pg->TimerOrdering();
}

extern "C" double timer_order_bicoloring(void* ref) {
    BipartiteGraphBicoloringInterface *bg = (BipartiteGraphBicoloringInterface*) ref;
    return bg->TimerOrdering();
}

extern "C" void colors_coloring(void* ref, int* coloring) {
    GraphColoringInterface* g = static_cast<GraphColoringInterface*>(ref);
    vector<int> _coloring;
    g->GetVertexColors(_coloring);
    memcpy(coloring, _coloring.data(), _coloring.size() * sizeof(int));
}

extern "C" void colors_partial_coloring(void* ref, int* coloring) {
    BipartiteGraphPartialColoringInterface* g = static_cast<BipartiteGraphPartialColoringInterface*>(ref);
    vector<int> _left_coloring;
    vector<int> _right_coloring;
    g->GetLeftVertexColors(_left_coloring);
    g->GetRightVertexColors(_right_coloring);

    if (!_left_coloring.empty()) {
        memcpy(coloring, _left_coloring.data(), _left_coloring.size() * sizeof(int));
    }
    else {
        memcpy(coloring, _right_coloring.data(), _right_coloring.size() * sizeof(int));
    }
}

extern "C" void colors_bicoloring(void* ref, int* left_coloring, int* right_coloring) {
    BipartiteGraphBicoloringInterface* g = static_cast<BipartiteGraphBicoloringInterface*>(ref);
    vector<int> _left_coloring;
    vector<int> _right_coloring;
    g->GetLeftVertexColors(_left_coloring);
    g->GetRightVertexColors(_right_coloring);
    memcpy(left_coloring, _left_coloring.data(), _left_coloring.size() * sizeof(int));
    memcpy(right_coloring, _right_coloring.data(), _right_coloring.size() * sizeof(int));
}

extern "C" double timer_colors_coloring(void* ref) {
    GraphColoringInterface *g = (GraphColoringInterface*) ref;
    return g->TimerColoring();
}

extern "C" double timer_colors_partial_coloring(void* ref) {
    BipartiteGraphPartialColoringInterface *pg = (BipartiteGraphPartialColoringInterface*) ref;
    return pg->TimerColoring();
}

extern "C" double timer_colors_bicoloring(void* ref) {
    BipartiteGraphBicoloringInterface *bg = (BipartiteGraphBicoloringInterface*) ref;
    return bg->TimerColoring();
}

extern "C" int ncolors_coloring(void* ref) {
    GraphColoringInterface *g = (GraphColoringInterface*) ref;
    return g->GetVertexColorCount();
}

extern "C" int ncolors_partial_coloring(void* ref) {
    BipartiteGraphPartialColoringInterface *pg = (BipartiteGraphPartialColoringInterface*) ref;
    return pg->GetVertexColorCount();
}

extern "C" int ncolors_bicoloring(void* ref) {
    BipartiteGraphBicoloringInterface *bg = (BipartiteGraphBicoloringInterface*) ref;
    return bg->GetVertexColorCount();
}

extern "C" void free_coloring(void* ref) {
    delete static_cast<GraphColoringInterface*>(ref);
}

extern "C" void free_partial_coloring(void* ref) {
    delete static_cast<BipartiteGraphPartialColoringInterface*>(ref);
}

extern "C" void free_bicoloring(void* ref) {
    delete static_cast<BipartiteGraphBicoloringInterface*>(ref);
}
