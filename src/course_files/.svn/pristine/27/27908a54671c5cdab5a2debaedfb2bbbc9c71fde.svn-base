#include <unordered_map>

class UnorderedUnsignedIntPair
{
public:
    unsigned int v[2];

};
bool operator==(const UnorderedUnsignedIntPair &lhs,const UnorderedUnsignedIntPair &rhs)
{
    return (lhs.v[0]==rhs.v[0] && lhs.v[1]==rhs.v[1]) || (lhs.v[0]==rhs.v[1] && lhs.v[1]==rhs.v[0]);
}
template <>
struct std::hash <UnorderedUnsignedIntPair>
{
public:
    size_t operator()(UnorderedUnsignedIntPair const &s) const
    {
        return s.v[0]+s.v[1];
    };
};
int main(void)
{
    std::unordered_map <UnorderedUnsignedIntPair,int> map;
    UnorderedUnsignedIntPair edge;
    edge.v[0]=100;
    edge.v[1]=200;
    map[edge]=100200;

    edge.v[0]=3;
    edge.v[1]=4;
    map[edge]=34;

    edge.v[0]=100;
    edge.v[1]=200;
    printf("%d\n",map[edge]);
    edge.v[1]=100;
    edge.v[0]=200;
    printf("%d\n",map[edge]);

    edge.v[0]=3;
    edge.v[1]=4;
    printf("%d\n",map[edge]);
    edge.v[1]=3;
    edge.v[0]=4;
    printf("%d\n",map[edge]);
    return 0;
}
