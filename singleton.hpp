#ifndef SINGLETON_HPP
#define SINGLETON_HPP

/*  @brief:
        class An provides single access to object T in one-hread application.
    @usage:
        //Object Manager requires single access:

        // in .hpp:
        class Manager; //Forward declaration;
        DECLARE_IMPL(Manager);

        // in .cpp:
        class Manager 
        { 
            //...
        };
        BIND_SELF_TO_IMPL_SINGLE(Manager);

        // somewhere in code:
        An<Manager> g_manager;
        g_manager->someAction();
*/
template<typename T>
class An
{
public:
    An() : m_pData(0)                   { }

    T* operator->()                     { return get(); }
    const T* operator->() const         { return get(); }

    void operator=(T* t)                { m_pData = t; }
    
    inline bool isEmpty() const         { return m_pData == 0; }
    void init()                         { if (isEmpty()) reinit(); }
    void reinit()                       { anFill(*this); }
    
private:
    T* get() const
    {
        const_cast<An*>(this)->init();
        return m_pData;
    }

    T* m_pData;
};

#include <string>
#include <stdexcept>

template <typename T>
void anFill(An<T> &)
{
    throw std::runtime_error(
        std::string("Cannot find implementation for interface") + 
        std::string(typeid(T).name()));
}

template<typename T>
T& single()
{
    static T t;
    return t;
}

#define PROTO_IFACE(T) template<> void anFill(An<T> &a)
#define DECLATE_IMPL(T) PROTO_IFACE(T);

#define BIND_TO_IMPL_SINGLE(Iface, Impl) PROTO_IFACE(Iface) { a = &single<Impl>(); }
#define BIND_SELF_TO_IMPL_SINGLE(Impl) BIND_TO_IMPL_SINGLE(Impl, Impl)

#endif //SINGLETON_HPP