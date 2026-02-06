#pragma once 

#include <cassert> 
#include <initializer_list> 
#include <algorithm> 
#include <stdexcept> 
#include <utility> 
#include "array_ptr.h" 

struct ReserveProxyObj {
    size_t capacity_to_reserve;
    explicit ReserveProxyObj(size_t capacity) : capacity_to_reserve(capacity) {}
};

inline ReserveProxyObj Reserve(size_t capacity_to_reserve) {
    return ReserveProxyObj(capacity_to_reserve);
}

template <typename Type>
class SimpleVector {
public:
    using Iterator = Type*;
    using ConstIterator = const Type*;

    SimpleVector() noexcept = default;

    explicit SimpleVector(size_t size)
        : size_(size), capacity_(size), data_(size) {
        std::fill(data_.Get(), data_.Get() + size_, Type{});
    }

    SimpleVector(size_t size, const Type& value)
        : size_(size), capacity_(size), data_(size) {
        std::fill(data_.Get(), data_.Get() + size_, value);
    }

    SimpleVector(std::initializer_list<Type> init)
        : size_(init.size()), capacity_(init.size()), data_(init.size()) {
        std::copy(init.begin(), init.end(), data_.Get());
    }

    SimpleVector(const SimpleVector& other)
        : size_(other.size_), capacity_(other.capacity_), data_(other.capacity_) {
        std::copy(other.data_.Get(), other.data_.Get() + size_, data_.Get());
    }

    SimpleVector(SimpleVector&& other) noexcept
        : size_(std::exchange(other.size_, 0)),
        capacity_(std::exchange(other.capacity_, 0)),
        data_(std::move(other.data_)) {
    }

    explicit SimpleVector(ReserveProxyObj reserve_proxy)
        : size_(0), capacity_(reserve_proxy.capacity_to_reserve), data_(reserve_proxy.capacity_to_reserve) {
    }

    SimpleVector& operator=(const SimpleVector& rhs) {
        if (this != &rhs) {
            SimpleVector tmp(rhs);
            swap(tmp);
        }
        return *this;
    }

    SimpleVector& operator=(SimpleVector&& rhs) noexcept {
        if (this != &rhs) {
            data_ = std::move(rhs.data_);
            size_ = std::exchange(rhs.size_, 0);
            capacity_ = std::exchange(rhs.capacity_, 0);
        }
        return *this;
    }

    void PushBack(const Type& item) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = item;
    }

    void PushBack(Type&& item) {
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = std::move(item);
    }

    void Reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            ArrayPtr<Type> new_data(new_capacity);
            std::move(data_.Get(), data_.Get() + size_, new_data.Get());
            data_ = std::move(new_data);
            capacity_ = new_capacity;
        }
    }

    Iterator Insert(ConstIterator pos, const Type& value) {
        assert(pos >= begin() && pos <= end());
        size_t index = pos - data_.Get();
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        Iterator insert_pos = data_.Get() + index;
        std::copy_backward(insert_pos, data_.Get() + size_, data_.Get() + size_ + 1);
        data_[index] = value;
        ++size_;
        return data_.Get() + index;
    }

    Iterator Insert(ConstIterator pos, Type&& value) {
        assert(pos >= begin() && pos <= end());
        size_t index = pos - data_.Get();
        if (size_ == capacity_) {
            Reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        Iterator insert_pos = data_.Get() + index;
        std::move_backward(insert_pos, data_.Get() + size_, data_.Get() + size_ + 1);
        data_[index] = std::move(value);
        ++size_;
        return data_.Get() + index;
    }

    void PopBack() noexcept {
        assert(size_ > 0);
        --size_;
    }

    Iterator Erase(ConstIterator pos) {
        assert(pos >= data_.Get() && pos < data_.Get() + size_);
        Iterator nonconst_pos = data_.Get() + (pos - data_.Get());
        std::move(nonconst_pos + 1, data_.Get() + size_, nonconst_pos);
        --size_;
        return nonconst_pos;
    }

    void swap(SimpleVector& other) noexcept {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        data_.swap(other.data_);
    }

    size_t GetSize() const noexcept {
        return size_;
    }

    size_t GetCapacity() const noexcept {
        return capacity_;
    }

    bool IsEmpty() const noexcept {
        return size_ == 0;
    }

    Type& operator[](size_t index) noexcept {
        return data_[index];
    }

    const Type& operator[](size_t index) const noexcept {
        return data_[index];
    }

    Type& At(size_t index) {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    const Type& At(size_t index) const {
        if (index >= size_) throw std::out_of_range("Index out of range");
        return data_[index];
    }

    void Clear() noexcept {
        size_ = 0;
    }

    void Resize(size_t new_size) {
        if (new_size <= size_) {
            size_ = new_size;
        }
        else {
            if (new_size > capacity_) {
                ArrayPtr<Type> new_data(new_size);
                std::move(data_.Get(), data_.Get() + size_, new_data.Get());
                for (size_t i = size_; i < new_size; ++i) {
                    new_data[i] = Type{};
                }
                data_ = std::move(new_data);
                capacity_ = new_size;
            }
            else {
                for (size_t i = size_; i < new_size; ++i) {
                    data_[i] = Type{};
                }
            }
            size_ = new_size;
        }
    }

    Iterator begin() noexcept {
        return data_.Get();
    }

    Iterator end() noexcept {
        return data_.Get() + size_;
    }

    ConstIterator begin() const noexcept {
        return data_.Get();
    }

    ConstIterator end() const noexcept {
        return data_.Get() + size_;
    }

    ConstIterator cbegin() const noexcept {
        return data_.Get();
    }

    ConstIterator cend() const noexcept {
        return data_.Get() + size_;
    }

private:
    size_t size_ = 0;
    size_t capacity_ = 0;
    ArrayPtr<Type> data_;
};

template <typename Type>
inline bool operator==(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return lhs.GetSize() == rhs.GetSize() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename Type>
inline bool operator!=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs == rhs);
}

template <typename Type>
inline bool operator<(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename Type>
inline bool operator<=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(rhs < lhs);
}

template <typename Type>
inline bool operator>(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return rhs < lhs;
}

template <typename Type>
inline bool operator>=(const SimpleVector<Type>& lhs, const SimpleVector<Type>& rhs) {
    return !(lhs < rhs);
}