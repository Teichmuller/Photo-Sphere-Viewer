#ifndef CXPL_BASIC_DEPENDENTVAR_H_
#define CXPL_BASIC_DEPENDENTVAR_H_

#include <memory>
#include <functional>
#include <list>
#include <vector>

using namespace std;

namespace cxpl
{
    /// Internal types
    class Var_Proxy;
    template <typename T>
    class TVar_Proxy;
    template <typename T>
    class DVar_Proxy;
    template <typename T>
    class IVar_Proxy;

    /// \class Var
    /// \brief Base class for dependent-types and independent-types
    ///
    class Var
    {
    public:
        virtual ~Var() {}
        virtual operator shared_ptr<Var_Proxy>() = 0;
    protected:
        Var() {}
    };

    /// \class SpecializedVar
    /// \brief Template inheritance of Var for different types of realization
    ///
    /// \tparam Data type
    template <class T>
    class TVar : public Var
    {
    public:
        /// \brief Interface for converting to original type
        virtual operator T() = 0;
        virtual ~TVar() {}
    protected:
        /// private constructors
        TVar() {}
    };

    /// \class DVar
    /// \brief Base class for dependent-types
    ///
    /// \tparam Data type
	template <class T>
    class DVar : public TVar<T>
	{
	public:
		/// \brief Realization of conversion interface
		operator T() override
        {
            return m_internal->GetValue();
		}
        /// \brief Realization of conversion interface
        operator shared_ptr<Var_Proxy>() override
        {
            return static_pointer_cast<Var_Proxy>(m_internal);
        }
		/// \brief Constructor
		/// \param func Relationship of dependency.
        /// \param depend_list All variables this variable depends on
        DVar(function<T()> func, const vector<shared_ptr<Var_Proxy>> &depend_list)
        : m_internal(make_shared<DVar_Proxy<T>>(func))
        {
            m_internal->SetDependentList(depend_list, m_internal);
		}
		/// \brief Destructor
        ~DVar() {}
    private:
        shared_ptr<DVar_Proxy<T>> m_internal;
	};

    /// \class IVar
	/// \brief Base class for independent-types
	///
	/// \tparam Data type
	template <class T>
    class IVar : public TVar<T>
	{
	public:
		/// \brief Realization of conversion interface
		operator T() override
        {
            return m_internal->GetValue();
		}
        /// \brief Realization of conversion interface
        operator shared_ptr<Var_Proxy>() override
        {
            return static_pointer_cast<Var_Proxy>(m_internal);
        }
		/// \brief Reassign the independent value
        T operator = (const T &value)
        {
            m_internal->SetValue(value);
            return m_internal->GetValue();
		}
		/// \brief Constructor
        /// \param init Initial value.
        IVar(const T &init) : m_internal(make_shared<IVar_Proxy<T>>(init))
        {
        }
        /// \brief Denstructor
        ~IVar() {}
    private:
        shared_ptr<IVar_Proxy<T>> m_internal;
	};

	/// Inherited dependent types
    using DInt      =       DVar<int>;
    using DUInt     =       DVar<unsigned int>;
    using DInt32    =       DVar<int32_t>;
    using DUInt32   =       DVar<uint32_t>;
    using DInt64    =       DVar<int64_t>;
    using DUInt64   =       DVar<uint64_t>;
    using DFloat    =       DVar<float>;
    using DDouble   =       DVar<double>;

    /// Inherited independent types
    using IInt      =       IVar<int>;
    using IUInt     =       IVar<unsigned int>;
    using IInt32    =       IVar<int32_t>;
    using IUInt32   =       IVar<uint32_t>;
    using IInt64    =       IVar<int64_t>;
    using IUInt64   =       IVar<uint64_t>;
    using IFloat    =       IVar<float>;
    using IDouble   =       IVar<double>;


    class Var_Proxy
    {
    public:
        virtual ~Var_Proxy() {}
        template<typename T>
        friend class DVar_Proxy;
        template<typename T>
        friend class IVar_Proxy;
    protected:
        list<shared_ptr<Var_Proxy>> m_dependency;
        virtual void m_UnmarkUpdate() = 0;
        Var_Proxy() {}
    };

    template <class T>
    class TVar_Proxy : public Var_Proxy
    {
    public:
        virtual T GetValue() = 0;
        virtual ~TVar_Proxy() {}
    protected:
        T m_value;
        TVar_Proxy() {}
    };

    template <class T>
    class DVar_Proxy : public TVar_Proxy<T>
    {
    public:
        T GetValue() override
        {
            if (!m_updated)
            {
                this->m_value = m_func();
                m_updated = true;
            }
            return this->m_value;
        }
        DVar_Proxy(function<T()> func)
        : m_func(func)
        {
        }
        ~DVar_Proxy() {}
    private:
        template <typename U>
        friend class DVar;
        void SetDependentList(const vector<shared_ptr<Var_Proxy>> &depend_list, shared_ptr<DVar_Proxy<T>> p)
        {
            for (auto &i : depend_list)
            {
                i->m_dependency.push_back(p);
            }
            this->m_value = m_func();
            m_updated = true;
        }
        void m_UnmarkUpdate() override
        {
            m_updated = false;
            for (auto &i : this->m_dependency)
            {
                i->m_UnmarkUpdate();
            }
        }
        bool m_updated;
        function<T()> m_func;
    };

    template <class T>
    class IVar_Proxy : public TVar_Proxy<T>
    {
    public:
        T GetValue() override
        {
            return this->m_value;
        }
        void SetValue(const T &value)
        {
            this->m_value = value;
            m_UnmarkUpdate();
        }
        IVar_Proxy(const T &init)
        {
            SetValue(init);
        }
        ~IVar_Proxy() {}
    private:
        void m_UnmarkUpdate() override
        {
            for (auto &i : this->m_dependency)
            {
                i->m_UnmarkUpdate();
            }
        }
    };
}

#endif
