#ifndef _INCLUDE_SIGSEGV_PROP_H_
#define _INCLUDE_SIGSEGV_PROP_H_


#include "mem/extract.h"


namespace Prop
{
	void PreloadAll();
	
	bool FindOffset(int& off, const char *obj, const char *var);
	int FindOffsetAssert(const char *obj, const char *var);
}


class IProp : public AutoList<IProp>
{
public:
	enum class State : int
	{
		INITIAL,
		OK,
		FAIL,
	};
	
	virtual const char *GetObjectName() const = 0;
	virtual const char *GetMemberName() const = 0;
	virtual const char *GetKind() const = 0;
	
	void Preload() { this->DoCalcOffset(); }
	
	bool GetOffset(int& off);
	
	State GetState() const { return this->m_State; }
	
protected:
	IProp() {}
	
	virtual bool CalcOffset(int& off) const = 0;
	
private:
	void DoCalcOffset();
	
	State m_State = State::INITIAL;
	int m_Offset = -1;
};

inline bool IProp::GetOffset(int& off)
{
	State state = this->m_State;
	
	if (state == State::INITIAL) {
		this->DoCalcOffset();
		state = this->m_State;
	}
	
	if (state != State::OK) {
		return false;
	}
	
	off = this->m_Offset;
	return true;
}

inline void IProp::DoCalcOffset()
{
	if (this->m_State == State::INITIAL) {
		if (this->CalcOffset(this->m_Offset)) {
			this->m_State = State::OK;
		} else {
			this->m_State = State::FAIL;
		}
	}
}


// template: AVOID IF POSSIBLE
// ctor:     OKAY
// dtor:     OKAY
// virtual:  OKAY
// members:  OKAY
template<typename T>
class IPropTyped : public IProp
{
public:
	virtual const char *GetObjectName() const override { return this->m_pszObjName; }
	virtual const char *GetMemberName() const override { return this->m_pszMemName; }
	
protected:
	IPropTyped(const char *obj, const char *mem) :
		m_pszObjName(obj), m_pszMemName(mem) {}
	
private:
	const char *m_pszObjName;
	const char *m_pszMemName;
};


template<typename T>
class CProp_SendProp : public IPropTyped<T>
{
public:
	CProp_SendProp(const char *obj, const char *mem, const char *sv_class, void (*sc_func)(void *, void *), const char *remote_name = nullptr) :
		IPropTyped<T>(obj, mem), m_pszServerClass(sv_class), m_pStateChangedFunc(sc_func), m_pszRemoteName(remote_name) {}
	
	virtual const char *GetKind() const override { return "SENDPROP"; }
	
	void StateChanged(void *obj, void *var)
	{
		(*this->m_pStateChangedFunc)(obj, var);
	}
	
private:
	virtual bool CalcOffset(int& off) const override
	{
		sm_sendprop_info_t info;
		if (!gamehelpers->FindSendPropInfo(this->m_pszServerClass, this->GetSendPropMemberName(), &info)) {
			DevMsg("CProp_SendProp: %s::%s FAIL: in FindSendPropInfo\n", this->GetObjectName(), this->GetMemberName());
			return false;
		}
		
		off = info.prop->GetOffset();
		return true;
	}
	
	const char *GetSendPropMemberName() const
	{
		if (this->m_pszRemoteName != nullptr) {
			return this->m_pszRemoteName;
		} else {
			return this->GetMemberName();
		}
	}
	
	const char *m_pszServerClass;
	void (*m_pStateChangedFunc)(void *, void *);
	const char *m_pszRemoteName;
};


template<typename T>
class CProp_DataMap : public IPropTyped<T>
{
public:
	CProp_DataMap(const char *obj, const char *mem) :
		IPropTyped<T>(obj, mem) {}
	
	virtual const char *GetKind() const override { return "DATAMAP"; }
	
	void StateChanged(void *obj, void *var) {}
	
private:
	virtual bool CalcOffset(int& off) const override
	{
		char str_DataMap[1024];
		snprintf(str_DataMap, sizeof(str_DataMap), "%s::m_DataMap", this->GetObjectName());
		
		datamap_t *map = (datamap_t *)AddrManager::GetAddr(str_DataMap);
		if (map == nullptr) {
			DevMsg("CProp_DataMap: %s::%s FAIL: no addr for %s\n", this->GetObjectName(), this->GetMemberName(), str_DataMap);
			return false;
		}
		
		sm_datatable_info_t info;
		if (!gamehelpers->FindDataMapInfo(map, this->GetMemberName(), &info)) {
			DevMsg("CProp_DataMap: %s::%s FAIL: in FindDataMapInfo\n", this->GetObjectName(), this->GetMemberName());
			return false;
		}
		
		off = GetTypeDescOffs(info.prop);
		return true;
	}
};


template<typename T>
class CProp_Extract : public IPropTyped<T>
{
public:
	CProp_Extract(const char *obj, const char *mem, IExtract<T *> *extractor) :
		IPropTyped<T>(obj, mem), m_Extractor(extractor) {}
	virtual ~CProp_Extract()
	{
		if (this->m_Extractor != nullptr) {
			delete this->m_Extractor;
		}
	}
	
	virtual const char *GetKind() const override { return "EXTRACT"; }
	
	void StateChanged(void *obj, void *var) {}
	
private:
	virtual bool CalcOffset(int& off) const override
	{
		if (!this->m_Extractor->Init()) {
			DevMsg("CProp_Extract: %s::%s FAIL: in extractor Init\n", this->GetObjectName(), this->GetMemberName());
			return false;
		}
		
		if (!this->m_Extractor->Check()) {
			DevMsg("CProp_Extract: %s::%s FAIL: in extractor Check\n", this->GetObjectName(), this->GetMemberName());
			return false;
		}
		
		off = (int)this->m_Extractor->Extract();
		return true;
	}
	
	IExtract<T *> *m_Extractor;
};


// template: OKAY
// ctor:     NOPE
// dtor:     NOPE
// virtual:  NOPE
// members:  NOPE
template<typename T, typename IPROP, IPROP *PROP, const size_t *ADJUST>
class CPropAccessor_Base
{
public:
	CPropAccessor_Base() = delete;
	
	void *GetBasePtr() const
	{
		return (void *)((uintptr_t)this - *ADJUST);
	}
	
	int GetOffset() const
	{
		int off = -1;
		assert(PROP->GetOffset(off));
		return off;
	}
	
	T *GetPtr() const
	{
//		DevMsg("CPropAccessor_Base::GetPtr: base %08x off %08x size %08x dword %08x\n", base, off, sizeof(T), *(uint32_t *)(base + off));
		return reinterpret_cast<T *>((uintptr_t)this->GetBasePtr() + this->GetOffset());
	}
	T& GetRef() const
	{
		return *this->GetPtr();
	}
};


template<typename T, typename IPROP, IPROP *PROP, const size_t *ADJUST>
class CPropAccessor_Read : public CPropAccessor_Base<T, IPROP, PROP, ADJUST>
{
public:
	CPropAccessor_Read() = delete;
	
	operator const T&() const   { return this->GetRef(); }
	const T* operator->() const { return this->GetPtr(); } /* dubious */
	const T& operator=(const T& val) = delete;
};
/* specialization for CHandle<U> */
template<typename U, typename IPROP, IPROP *PROP, const size_t *ADJUST>
class CPropAccessor_Read<CHandle<U>, IPROP, PROP, ADJUST> : public CPropAccessor_Base<CHandle<U>, IPROP, PROP, ADJUST>
{
public:
	CPropAccessor_Read() = delete;
	
	operator U*() const { return this->GetRef(); }
	U* operator=(U* val) = delete;
};
/* specialization for CUtlVector<U> */
template<typename U, typename IPROP, IPROP *PROP, const size_t *ADJUST>
class CPropAccessor_Read<CUtlVector<U>, IPROP, PROP, ADJUST> : public CPropAccessor_Base<CUtlVector<U>, IPROP, PROP, ADJUST>
{
public:
	using T = CUtlVector<U>;
	
	CPropAccessor_Read() = delete;
	
	operator const T&() const = delete;
	const T* operator->() const { return this->GetPtr(); } /* dubious */
	const T& operator=(const T& val) = delete;
	
	const U& operator[](int i) const { return this->GetRef()[i]; }
	U& operator[](int i)             { return this->GetRef()[i]; }
};


template<typename T, typename IPROP, IPROP *PROP, const size_t *ADJUST, bool NET = false>
class CPropAccessor_Write : public CPropAccessor_Read<T, IPROP, PROP, ADJUST>
{
public:
	CPropAccessor_Write() = delete;
	
	const T& operator=(const T& val)
	{
		T *ptr = this->GetPtr();
		
		if (NET) {
			if (memcmp(ptr, &val, sizeof(T)) != 0) {
				void *obj = this->GetBasePtr();
				void *var = (void *)((uintptr_t)obj + this->GetOffset());
				
				PROP->StateChanged(obj, var);
			}
		}
		
		*ptr = val;
		return val;
	}
	T* operator->() { return this->GetPtr(); } /* dubious */
};
/* specialization for CHandle<U> */
template<typename U, typename IPROP, IPROP *PROP, const size_t *ADJUST, bool NET>
class CPropAccessor_Write<CHandle<U>, IPROP, PROP, ADJUST, NET> : public CPropAccessor_Read<CHandle<U>, IPROP, PROP, ADJUST>
{
public:
	CPropAccessor_Write() = delete;
	
	U* operator=(U* val)
	{
		U *ptr = this->GetPtr();
		
		if (NET) {
			if (memcmp(ptr, &val, sizeof(U)) != 0) {
				void *obj = this->GetBasePtr();
				void *var = (void *)((uintptr_t)obj + this->GetOffset());
				
				PROP->StateChanged(obj, var);
			}
		}
		
		*ptr = val;
		return val;
	}
};


#define DECL_SENDPROP(TYPE, PROPNAME) \
	typedef CProp_SendProp<TYPE> _type_prop_##PROPNAME; \
	static _type_prop_##PROPNAME s_prop_##PROPNAME; \
	const static size_t _adj_##PROPNAME; \
	typedef CPropAccessor_Write<TYPE, _type_prop_##PROPNAME, &s_prop_##PROPNAME, &_adj_##PROPNAME, true> _type_accessor_##PROPNAME; \
	_type_accessor_##PROPNAME PROPNAME; \
	static_assert(std::is_empty<_type_accessor_##PROPNAME>::value, "Prop accessor isn't an empty type")

#define DECL_DATAMAP(TYPE, PROPNAME) \
	typedef CProp_DataMap<TYPE> _type_prop_##PROPNAME; \
	static _type_prop_##PROPNAME s_prop_##PROPNAME; \
	const static size_t _adj_##PROPNAME; \
	typedef CPropAccessor_Write<TYPE, _type_prop_##PROPNAME, &s_prop_##PROPNAME, &_adj_##PROPNAME, false> _type_accessor_##PROPNAME; \
	_type_accessor_##PROPNAME PROPNAME; \
	static_assert(std::is_empty<_type_accessor_##PROPNAME>::value, "Prop accessor isn't an empty type")

#define DECL_EXTRACT(TYPE, PROPNAME) \
	typedef CProp_Extract<TYPE> _type_prop_##PROPNAME; \
	static _type_prop_##PROPNAME s_prop_##PROPNAME; \
	const static size_t _adj_##PROPNAME; \
	typedef CPropAccessor_Write<TYPE, _type_prop_##PROPNAME, &s_prop_##PROPNAME, &_adj_##PROPNAME, false> _type_accessor_##PROPNAME; \
	_type_accessor_##PROPNAME PROPNAME; \
	static_assert(std::is_empty<_type_accessor_##PROPNAME>::value, "Prop accessor isn't an empty type")


// for IMPL_SENDPROP, add an additional argument for the "remote name" (e.g. in CBaseEntity, m_MoveType's remote name is "movetype")
#define IMPL_SENDPROP(TYPE, CLASSNAME, PROPNAME, SVCLASS, ...) \
	void NetworkStateChanged_##CLASSNAME##_##PROPNAME(void *obj, void *var) { reinterpret_cast<CLASSNAME *>(obj)->NetworkStateChanged(var); } \
	const size_t CLASSNAME::_adj_##PROPNAME = offsetof(CLASSNAME, PROPNAME); \
	CProp_SendProp<TYPE> CLASSNAME::s_prop_##PROPNAME(#CLASSNAME, #PROPNAME, #SVCLASS, &NetworkStateChanged_##CLASSNAME##_##PROPNAME, ##__VA_ARGS__)
#define IMPL_DATAMAP(TYPE, CLASSNAME, PROPNAME) \
	const size_t CLASSNAME::_adj_##PROPNAME = offsetof(CLASSNAME, PROPNAME); \
	CProp_DataMap<TYPE> CLASSNAME::s_prop_##PROPNAME(#CLASSNAME, #PROPNAME)
#define IMPL_EXTRACT(TYPE, CLASSNAME, PROPNAME, EXTRACTOR) \
	const size_t CLASSNAME::_adj_##PROPNAME = offsetof(CLASSNAME, PROPNAME); \
	CProp_Extract<TYPE> CLASSNAME::s_prop_##PROPNAME(#CLASSNAME, #PROPNAME, EXTRACTOR)


#endif