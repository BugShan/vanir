#ifndef	_VANIR_CLASS_H_
#define	_VANIR_CLASS_H_

#include <vanir/Type.h>
#include <vector>

namespace vanir
{
	class Field;
	class Method;
	class Class final : public Type
	{
	public:
		Class(const std::string& fullName);
		virtual ~Class(void) override;

	public:
		/**
		 * Get the name lists of all base type
		 */
		inline const std::vector<std::string>& GetAllBaseTypeNameVec(void) const;
		/**
		 * Get the Field of this Type.
		 * @return: the vector of the Field pointer
		 */
		inline const std::vector<const Field*>& GetFieldPtrVec(void)  const;
		/**
		 * Get the Methods of this Type.
		 * @return: the vector of the Method pointer
		 */
		inline const std::vector<const Method*>& GetMethodPtrVec(void) const;

	public:
		/**
		 * Get all base type registered in vanir runtime.
		 * !There is some case as some type not registered int runtime.
		 */
		const std::vector<const Class*> GetAllBaseTypeVec(void) const;
		/**
		 * Get a Field defined in this class by name.
		 * @param fieldName: the name of the Field to found
		 * @return: if not found return null pointer
		 */
		const Field*  const GetFieldPtr(const std::string& fieldName) const;
		/**
		 * Get a Method defiend in this class by name.
		 * @param methodName: the name of the Method to found
		 * @return: if not found return null pointer
		 */
		const Method* const GetMethodPtr(const std::string& methodName) const;

	public:
		/**
		 * Set all the base type of this class
		 * @baseTypeName: the r-value of this name vector
		 */
		inline void SetBaseTypeNameVec(std::vector<std::string>&& baseTypeNameVec);
		/**
		 * Add a Field defined in this class.
		 * @param fieldPtr: the pointer of this field
		 */
		inline void DefienField(const Field* const fieldPtr);
		/**
		 * Add a Method defiend in this class.
		 * @param methodPtr: the pointer of the method
		 */
		inline void DefineMethod(const Method* const methodPtr);

	private:
		std::vector<std::string>			mBaseTypeNameVec;
		std::vector<const Method*>			mMethodPtrVec;
		std::vector<const Field*>			mFieldPtrVec;
	};//class Class

	inline const std::vector<std::string>& Class::GetAllBaseTypeNameVec(void) const
	{ return this->mBaseTypeNameVec; }
	inline const std::vector<const Field*>& Class::GetFieldPtrVec(void) const
	{ return this->mFieldPtrVec; }
	inline const std::vector<const Method*>& Class::GetMethodPtrVec(void) const
	{ return this->mMethodPtrVec; }

	inline void Class::SetBaseTypeNameVec(std::vector<std::string>&& baseTypeNameVec)
	{
		mBaseTypeNameVec.swap(baseTypeNameVec);
	}
	inline void Class::DefienField(const Field* const fieldPtr)
	{
		this->mFieldPtrVec.push_back(fieldPtr);
	}
	inline void Class::DefineMethod(const Method* const methodPtr)
	{
		this->mMethodPtrVec.push_back(methodPtr);
	}
};//namespace vanir
#endif//_VANIR_CLASS_H_
