#ifndef QEM_IS_INCLUDED
#define QEM_IS_INCLUDED

#include <ysshellext.h>
#include <unordered_map>

double CalculateQuadricErrorMetric(
    const YsShellExt &mesh,YsShellExt::VertexHandle vtHdA,YsShellExt::VertexHandle vtHdB);
bool SimplifyWithQuadricErrorMetricOneStep(YsShellExt &mesh);


class UnorderedUnsignedIntPair
{
public:
    unsigned int v[2];

};

inline bool operator==(const UnorderedUnsignedIntPair &lhs,const UnorderedUnsignedIntPair &rhs)
{
    return (lhs.v[0]==rhs.v[0] && lhs.v[1]==rhs.v[1]) || (lhs.v[0]==rhs.v[1] && lhs.v[1]==rhs.v[0]);
}
template <>
struct std::hash <UnorderedUnsignedIntPair>
{
public:
    inline size_t operator()(UnorderedUnsignedIntPair const &s) const
    {
        return s.v[0]+s.v[1];
    };
};

class QEMSimplifier
{
private:
	YsAVLTree <double,YsShell::Edge> sortedEdge;
	std::unordered_map <UnorderedUnsignedIntPair,YsAVLTree <double,YsShell::Edge>::NodeHandle> edgeToTreeNode;

public:
	void Start(YsShellExt &mesh);
	bool SimplifyOneStep(YsShellExt &mesh);
};


#endif
