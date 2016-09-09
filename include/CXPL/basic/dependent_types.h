#ifndef __CXPL_BASIC_DEPENDENT_TYPES_H__
#define __CXPL_BASIC_DEPENDENT_TYPES_H__

#include <functional>
#include <vector>

namespace CXPL
{
	using namespace std;

	/// \class Var
	/// \brief Base class for dependent-types and independent-types
	///
	class Var
	{
	protected:
		/// pointers to vars that dependent on this
		vector<Var*> m_dependency;
		/// update indicator
		bool m_updated;
		/// Unmark this and dependencies' updated flags
		template <class T>
		friend class DependentVar;
		void m_UnmarkUpdate()
		{
			m_updated = false;
			for (auto i : m_dependency)
			{
				i->m_UnmarkUpdate();
			}
		}
		Var() {}
		virtual ~Var() {}
	};

	/// \class SpecializedVar
	/// \brief Template inheritance of Var for different types of realization
	///
	/// \tparam Data type
	template <class T>
	class SpecializedVar : public Var
	{
	public:
		/// \brief Interface for converting to original type
		virtual operator T() = 0;
	protected:
		/// content
		T m_value;
		/// private constructors/destructors
		SpecializedVar(T initial)
		: m_value(initial) {}
		SpecializedVar() {}
		virtual ~SpecializedVar() {}
	};

	/// \class DependentVar
	/// \brief Base class for dependent-types
	///
	/// \tparam Data type
	template <class T>
	class DependentVar : public SpecializedVar<T>
	{
	public:
		/// \brief Realization of conversion interface
		operator T() override
		{
			if (!Var::m_updated)
			{
				SpecializedVar<T>::m_value = m_func();
				Var::m_updated = true;
			}
			return SpecializedVar<T>::m_value;
		}
		/// \brief Constructor
		/// \param func Relationship of dependency.
		DependentVar(function<T()> func, const vector<Var*> &depend_list)
		: m_func(func)
		{
			for (auto i : depend_list)
			{
				i->m_dependency.push_back(this);
			}
			SpecializedVar<T>::m_value = m_func();
			Var::m_updated = true;
		}
		/// \brief Destructor
		~DependentVar() {}

		/// \brief Redefine dependent relationship (Prohibited: would cause circular reference)
		/// \param func Relationship of dependency.
	//    void Redirect(function<T()> func)
	//    {
	//        m_func = func;
	//        m_value = m_func();
	//    }
	private:
		function<T()> m_func;
	};

	/// \class IndependentVar
	/// \brief Base class for independent-types
	///
	/// \tparam Data type
	template <class T>
	class IndependentVar : public SpecializedVar<T>
	{
	public:
		/// \brief Realization of conversion interface
		operator T() override
		{
			return SpecializedVar<T>::m_value;
		}
		/// \brief Reassign the independent value
		T& operator = (T value)
		{
			Var::m_UnmarkUpdate();
			SpecializedVar<T>::m_value = value;
			Var::m_updated = true;
			return SpecializedVar<T>::m_value;
		}
		/// \brief Constructor
		/// \param initial Initial value.
		IndependentVar(T initial)
		: SpecializedVar<T>(initial) {}
		/// \brief Denstructor
		~IndependentVar() {}
	};

	/// Inherited dependent types
	typedef DependentVar<int> Int;
	typedef DependentVar<unsigned int> Uint;
	typedef DependentVar<int32_t> Int32;
	typedef DependentVar<uint32_t> Uint32;
	typedef DependentVar<double> Double;
	typedef DependentVar<float> Float;

	/// Inherited independent types
	typedef IndependentVar<int> IInt;
	typedef IndependentVar<unsigned int> IUint;
	typedef IndependentVar<int32_t> IInt32;
	typedef IndependentVar<uint32_t> IUint32;
	typedef IndependentVar<double> IDouble;
	typedef IndependentVar<float> IFloat;

}

#endif
