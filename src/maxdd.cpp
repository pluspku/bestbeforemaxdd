#include <iostream>
#include <algorithm>
#include <cstring>
#include <boost/intrusive/rbtree.hpp>

#include "maxdd.h"

using namespace boost::intrusive;

struct maxddnode : public set_base_hook<optimize_size<true> > {
    maxddnode(int t, double x): _t(t), _x(x) {}
    int _t;
    double _x;
    friend inline std::ostream& operator<<(std::ostream&, const maxddnode&);
    friend bool operator<(const maxddnode&, const maxddnode&);
    friend bool operator>(const maxddnode&, const maxddnode&);
    friend bool operator==(const maxddnode&, const maxddnode&);
    friend double operator-(const maxddnode&, const maxddnode&);
};

std::ostream& operator<<( std::ostream& os, const maxddnode& x) {
    os << x._t << "," << x._x;
    return os;
};

struct delete_disposer{
    void operator()(maxddnode *node){
        delete node;
    }
};

bool operator<(const maxddnode&  lhs, const maxddnode& rhs) { return lhs._x < rhs._x; }
bool operator>(const maxddnode&  lhs, const maxddnode& rhs) { return lhs._x > rhs._x; }
bool operator==(const maxddnode& lhs, const maxddnode& rhs) { return lhs._x == rhs._x; }
double operator-(const maxddnode& lhs, const maxddnode& rhs) { return lhs._x - rhs._x; }

typedef rbtree<maxddnode> tree_t;


void best_before_maxdd(double *x, int r, double threshold, int dir, int *results){
    tree_t * tree = new tree_t();
    int link[r];
    memset(link, 0, sizeof(int) * r);
    for (int i=0; i<r; i++){
        maxddnode *node = new maxddnode(i, x[i] * dir);
        for (tree_t::const_iterator it = tree->cbegin(); it != tree->lower_bound(*node); it++){
            link[it->_t] = i;
        }
        tree->erase_and_dispose(tree->cbegin(), tree->lower_bound(*node), delete_disposer());

        maxddnode target(-1, x[i] * dir + threshold);
        for (tree_t::const_iterator it = tree->lower_bound(target); it!=tree->cend(); it++){
            results[it->_t] = i; 
        }
        tree->erase_and_dispose(tree->lower_bound(target), tree->cend(), delete_disposer());
        tree->insert_equal(*node);
    }
    maxddnode node(r-1, x[r-1] * dir);
    for (tree_t::const_iterator it = tree->cbegin(); it!=tree->cend(); it++){
        results[it->_t] = r-1;
    }
    tree->clear_and_dispose(delete_disposer());
    for (int i = r-1; i>=0; i--){
        if (link[i] > 0){
            results[i] = results[link[i]];
        }
    }
    delete tree;
}

