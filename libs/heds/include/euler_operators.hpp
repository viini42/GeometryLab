#ifndef DRAWER_EULER_OPERATORS_HPP
#define DRAWER_EULER_OPERATORS_HPP

struct Vertex;
struct Edge;
struct HalfEdge;
struct Face;
struct Loop;
struct Solid;

void op_mvfs(Solid* sol, double x, double y);
void op_kvfs(Solid* sol, double x, double y);
void op_mev(Solid* sol, Vertex* v, double x, double y);
void op_kev(Solid* sol, Vertex* v, Edge* e);
void op_mef(Solid* sol, Vertex* v1, Vertex* v2)

#endif // DRAWER_EULER_OPERATORS_HPP
