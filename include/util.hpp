// util
namespace libcp
{
	template<class Type>
	class max
	{
	public:
		Type operator()(const Type &lhs, const Type &rhs) const 
		{
			return lhs < rhs ? rhs : lhs;
		}
	};
	template<class Type>
	class min
	{
	public:
		Type operator()(const Type &lhs, const Type &rhs) const
		{
			return lhs < rhs ? lhs : rhs;
		}
	};
}
