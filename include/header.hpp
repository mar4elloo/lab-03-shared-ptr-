// Copyright 2020 Your Name <a.mark.2001@mail.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <utility>
#include <cstdio>

template <typename T>

class SharedPtr {
public:
    SharedPtr()
    {
        the_object = nullptr;
        the_number_of_obj = nullptr;
    }

    explicit SharedPtr(T* ptr)
    {
        the_object = ptr;
        the_number_of_obj = new The_number_of_objects;
        the_number_of_obj->the_incr();
    }

    SharedPtr(const SharedPtr& r)
    {
        the_object = r.the_object;
        the_number_of_obj = r.the_number_of_obj;
        the_number_of_obj->the_incr();
    }

    SharedPtr(SharedPtr&& r) noexcept
    {
        the_object = std::move(r.the_object);
        the_number_of_obj = std::move(r.the_number_of_obj);
    }

    ~SharedPtr()
    {
        if (the_number_of_obj != nullptr) {
            if (!the_number_of_obj->the_decr()) {
                delete the_object;
                delete the_number_of_obj;
            }
        }
    }

    auto operator=(const SharedPtr& r) -> SharedPtr&
    {
        the_object = r.the_object;
        the_number_of_obj = r.the_number_of_obj;
        the_number_of_obj->the_incr();
        return *this;
    }

    auto operator=(SharedPtr&& r) noexcept -> SharedPtr&
    {
        std::swap(the_object, r.the_object);
        std::swap(the_number_of_obj, r.the_number_of_obj);
        return *this;
    }

    explicit operator bool() const
    {
        return the_object != nullptr;
    }

    auto operator*() const -> T&
    {
        return *the_object;
    }

    auto operator->() const -> T*
    {
        return the_object;
    }

    auto get() -> T*
    {
        return the_object;
    }

    void reset()
    {
        if (the_number_of_obj != nullptr
            && the_number_of_obj->the_decr() == 0) {
            delete the_object;
            delete the_number_of_obj;
            the_object = nullptr;
            the_number_of_obj = nullptr;
        }
    }

    void reset(T* ptr)
    {
        reset();
        the_object = ptr;
        the_number_of_obj = new The_number_of_objects;
        the_number_of_obj->the_incr();
    }

    void swap(SharedPtr& r)
    {
        if (the_object != r.the_object) {
            std::swap(the_object, r.the_object);
            std::swap(the_number_of_obj, r.the_number_of_obj);
        }
    }

    [[nodiscard]] auto use_count() const -> size_t
    {
        return the_number_of_obj->get_the_number();
    }

private:
    T* the_object;

    class The_number_of_objects {
        int the_number_of_objects;

    public:
        The_number_of_objects()
        {
            the_number_of_objects = 0;
        }

        int get_the_number() {
            return the_number_of_objects;
        }

        int the_incr() {
            ++the_number_of_objects;
            return the_number_of_objects;
        }

        int the_decr() {
            --the_number_of_objects;
            return the_number_of_objects;
        }
    } * the_number_of_obj;
};

#endif // INCLUDE_HEADER_HPP_
