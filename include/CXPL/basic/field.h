#ifndef __CXPL_BASIC_FIELD_H__
#define __CXPL_BASIC_FIELD_H__

#include <functional>

namespace CXPL
{
	/// \class Field
	/// \brief Base template class for field implementations.
	///
	/// \tparam InputType the type of independent variable of the field
	/// \tparam OutputType the type of dependent variable of the field
	///
	template <class InputType, class OutputType>
	class Field
	{
	public:
		/// \brief Calculate the feild value of given point
		///
		/// \param position the given point
		/// \return feild value
		OutputType GetValue(InputType position) {return m_fieldFunc(position);}
		/// Interface for inheritance
		virtual ~Field() {}
	protected:
		/// Field function container
		function<OutputType(InputType)> m_fieldFunc;
		/// Indicate that field function should be implemented within the class
		Field(const function<OutputType(InputType)> &fieldFunc)
		: m_fieldFunc(fieldFunc) {}
	};

	/// \class VariantField
	/// \brief Base template class for variant field implementations.
	///
	/// \tparam InputType the type of independent variable of the field
	/// \tparam OutputType the type of dependent variable of the field
	/// \tparam ParamType the type of parameter of the field
	///
	template <class InputType, class OutputType, class ParamType>
	class VariantField : public Field<InputType, OutputType>
	{
	public:
		/// \brief Update the variant field
		///
		/// Set up current parameter to the field
		/// \param current parameter
		void Update(ParamType time) {return m_updateFunc(time);}
		/// \brief Constructor
		///
		/// \param fieldFunc the function of the field
		/// \param updateFunc the function to update the field
		VariantField(function<OutputType(InputType)> &fieldFunc, function<void(ParamType)> &updateFunc)
		: Field<InputType, OutputType>::m_fieldFunc(fieldFunc), m_updateFunc(updateFunc) {}
		/// Interface to inheritance
		virtual ~VariantField() {};
	protected:
		function<void(ParamType)> m_updateFunc;
		VariantField() {}
	};

	/// \class VariantField
	/// \brief Base template class for invariant field implementations.
	///
	/// \tparam InputType the type of independent variable of the field
	/// \tparam OutputType the type of dependent variable of the field
	///
	template <class InputType, class OutputType>
	class InvariantField : public Field<InputType, OutputType>
	{
	public:
		/// \brief Constructor
		///
		/// \param fieldFunc the function of the field
		InvariantField(const function<OutputType(InputType)> &fieldFunc)
		: Field<InputType, OutputType>(fieldFunc) {}
		/// Interface to inheritance
		virtual ~InvariantField() {}
	};

}

#endif
